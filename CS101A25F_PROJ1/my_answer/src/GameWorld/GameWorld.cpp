#include "pvz/GameWorld/GameWorld.hpp"
#include "pvz/GameObject/GameObject.hpp"
#include "pvz/otherobjectshpp/otherobjects.hpp"

#include <cmath>
#include <cstdlib>

#include "pvz/utils.hpp"

// 声明外部函数
void UpdateShovelMousePosition(int x, int y);

namespace {
constexpr int kInitialSunCooldown = 90;
constexpr int kSkySunInterval = 150;
constexpr int kInitialZombieDelay = 1000;
constexpr int kBaseZombieInterval = 900;
constexpr int kMinimumZombieInterval = 150;
constexpr int kPlantingToleranceX = LAWN_GRID_WIDTH / 2;
constexpr int kPlantingToleranceY = LAWN_GRID_HEIGHT / 2;
}

void GameWorld::Init()
{
    // 清空对象容器
    mlist.clear();
    m_SunCount = 50;
    m_WaveCount = 0;
    m_nextZombieTick = kInitialZombieDelay;
    m_SunDropCD = kInitialSunCooldown;
    m_holdingSeed = nullptr;
    m_holdingShovel = false;

    // 添加背景
    auto pbackground = std::make_shared<Background>();
    Add(pbackground);

    // 创建UI文本：显示阳光数量
    m_sunText = std::make_shared<TextBase>(60, WINDOW_HEIGHT - 80, "Initial Sun Text.");
    m_sunText->SetColor(0.11, 0.45, 0.14);
    m_sunText->SetCentering(true);

    // 创建UI文本：显示波数
    m_waveText = std::make_shared<TextBase>(WINDOW_WIDTH - 160, 8, "Initial Wave Text.");
    m_waveText->SetColor(0.19, 0.19, 0.81);
    m_waveText->SetCentering(false);

    // 创建种植点
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 9; j++) {
            int x = 75 + j * 80;
            int y = 75 + i * 100;
            auto spot = std::make_shared<PlantingSpot>(x, y);
            spot->SetGameWorld(shared_from_this());
            Add(spot);
        }
    }

    // 创建种子按钮
    auto sunflowerSeed = std::make_shared<SunflowerSeed>(LayerID::UI);
    sunflowerSeed->SetGameWorld(shared_from_this());
    Add(sunflowerSeed);

    auto peashooterSeed = std::make_shared<PeashooterSeed>(LayerID::UI);
    peashooterSeed->SetGameWorld(shared_from_this());
    Add(peashooterSeed);

    auto wallnutSeed = std::make_shared<WallnutSeed>(LayerID::UI);
    wallnutSeed->SetGameWorld(shared_from_this());
    Add(wallnutSeed);
    // 如果WallnutSeed有初始冷却时间，则设置初始冷却
    if (wallnutSeed->GetStartCooldown() > 0) {
        wallnutSeed->SetStartCooldown();
    }

    auto cherryBombSeed = std::make_shared<CherryBombSeed>(LayerID::UI);
    cherryBombSeed->SetGameWorld(shared_from_this());
    Add(cherryBombSeed);
    // 如果CherryBombSeed有初始冷却时间，则设置初始冷却
    if (cherryBombSeed->GetStartCooldown() > 0) {
        cherryBombSeed->SetStartCooldown();
    }

    auto repeaterSeed = std::make_shared<RepeaterSeed>(LayerID::UI);
    repeaterSeed->SetGameWorld(shared_from_this());
    Add(repeaterSeed);
    // 如果RepeaterSeed有初始冷却时间，则设置初始冷却
    if (repeaterSeed->GetStartCooldown() > 0) {
        repeaterSeed->SetStartCooldown();
    }

    auto redRepeaterSeed = std::make_shared<RedRepeaterSeed>(LayerID::UI);
    redRepeaterSeed->SetGameWorld(shared_from_this());
    Add(redRepeaterSeed);
    // 如果RedRepeaterSeed有初始冷却时间，则设置初始冷却
    if (redRepeaterSeed->GetStartCooldown() > 0) {
        redRepeaterSeed->SetStartCooldown();
    }

    // 创建铲子
    auto shovel = std::make_shared<Shovel>(LayerID::UI);
    shovel->SetGameWorld(shared_from_this());
    Add(shovel);
}

LevelStatus GameWorld::Update()
{
    UpdateAllObjects();
    SpawnSunIfNeeded();
    SpawnZombiesIfNeeded();
    ResolveProjectileZombieCollisions();
    ResolveZombiePlantCollisions();

    if (HasZombieBreached()) {
        return LevelStatus::LOSING;
    }

    RemoveDeadObjects();
    UpdateUiText();
    return LevelStatus::ONGOING;
}

void GameWorld::UpdateAllObjects()
{
    for (auto& obj : mlist) {
        obj->Update();
    }
}

void GameWorld::SpawnSunIfNeeded()
{
    if (m_SunDropCD > 0) {
        --m_SunDropCD;
        return;
    }

    GenerateSun();
    ScheduleNextSkySun();
}

void GameWorld::SpawnZombiesIfNeeded()
{
    if (m_nextZombieTick > 0) {
        --m_nextZombieTick;
        return;
    }

    const int zombieCount = std::max(1, (15 + m_WaveCount) / 10);
    for (int i = 0; i < zombieCount; ++i) {
        const int laneIndex = randInt(0, GAME_ROWS - 1);
        const int zombieY = FIRST_ROW_CENTER + laneIndex * LAWN_GRID_HEIGHT;
        const int spawnX = randInt(WINDOW_WIDTH + 10, WINDOW_WIDTH + 40);

        const int pRegular = 20;
        const int pPole = 2 * std::max(m_WaveCount - 4, 0);
        const int pBucket = 3 * std::max(m_WaveCount - 15, 0);
        const int total = pRegular + pPole + pBucket;
        if (total <= 0) {
            continue;
        }
        const int roll = randInt(0, total - 1);

        if (roll < pRegular) {
            Add(std::make_shared<RegularZombie>(spawnX, zombieY, shared_from_this()));
        } else if (roll < pRegular + pPole) {
            Add(std::make_shared<PoleVaultingZombie>(spawnX, zombieY, shared_from_this()));
        } else {
            Add(std::make_shared<BucketHeadZombie>(spawnX, zombieY, shared_from_this()));
        }
    }

    ++m_WaveCount;
    ScheduleNextZombieWave();
}

void GameWorld::ResolveProjectileZombieCollisions()
{
    for (auto& projectileObj : mlist) {
        auto projectile = projectileObj->AsProjectile();
        if (!projectile || projectile->IsDead()) {
            continue;
        }

        for (auto& zombieObj : mlist) {
            auto zombie = zombieObj->AsZombie();
            if (!zombie || zombie->IsDead()) {
                continue;
            }

            if (projectile->CollidesWith(*zombie)) {
                projectile->OnHit(*zombie);
                if (!projectile->AllowMultipleHits() || projectile->IsDead()) {
                    break;
                }
            }
        }
    }
}

void GameWorld::ResolveZombiePlantCollisions()
{
    for (auto& zombieObj : mlist) {
        auto zombie = zombieObj->AsZombie();
        if (!zombie || zombie->IsDead() || zombie->GetTargetPlant()) {
            continue;
        }

        for (auto& plantObj : mlist) {
            auto plant = plantObj->AsPlant();
            if (!plant || !plant->IsAlive()) {
                continue;
            }

            const int dx = plantObj->GetX() - zombieObj->GetX();
            const int dy = plantObj->GetY() - zombieObj->GetY();
            const int collisionSq = (plantObj->GetWidth() / 2 + zombieObj->GetWidth() / 2);

            if (dx * dx + dy * dy < collisionSq * collisionSq) {
                zombie->SetTargetPlant(std::static_pointer_cast<Plant>(plantObj));
                break;
            }
        }
    }
}

void GameWorld::RemoveDeadObjects()
{
    mlist.remove_if([](const auto& obj) { return obj->IsDead(); });
}

bool GameWorld::HasZombieBreached()
{
    for (auto& obj : mlist) {
        auto zombie = obj->AsZombie();
        if (!zombie) {
            continue;
        }

        if (zombie->HasBreached() || zombie->GetX() < 0) {
            return true;
        }
    }
    return false;
}

void GameWorld::UpdateUiText()
{
    if (m_sunText) {
        m_sunText->SetText(std::to_string(m_SunCount));
    }
    if (m_waveText) {
        m_waveText->SetText("Wave: " + std::to_string(GetWaveCount()));
    }
}

void GameWorld::ScheduleNextSkySun()
{
    m_SunDropCD = kSkySunInterval;
}

void GameWorld::ScheduleNextZombieWave()
{
    m_nextZombieTick = kBaseZombieInterval - 15 * GetWaveCount();
    if (m_nextZombieTick < kMinimumZombieInterval) {
        m_nextZombieTick = kMinimumZombieInterval;
    }
    ChangeWave();
}

void GameWorld::CleanUp()
{
    mlist.clear();
    m_holdingSeed = nullptr;
    m_holdingShovel = false;
}

/// @brief 生成新的阳光
void GameWorld::GenerateSun()
{
    const int x = randInt(75, WINDOW_WIDTH - 75);
    const int y = WINDOW_HEIGHT - 1;
    Add(std::make_shared<Sun>(x, y, true, shared_from_this()));
}

/// @brief 生成冷却遮盖物（已弃用，由Seed::OnClick直接创建）
void GameWorld::GenerateCooldownMask(int x, int y, Seed* seed)
{
    // 此方法已由 Seed::OnClick 的直接创建替代
}

std::shared_ptr<Plant> GameWorld::GetPlantAt(int x, int y) const
{
    for (const auto& obj : mlist) {
        if (!obj->isPlant()) {
            continue;
        }

        if (obj->IsDead()) {
            continue;
        }

        if (std::abs(obj->GetX() - x) <= kPlantingToleranceX && std::abs(obj->GetY() - y) <= kPlantingToleranceY) {
            return std::dynamic_pointer_cast<Plant>(obj);
        }
    }

    return nullptr;
}

bool GameWorld::HasPlantAt(int x, int y) const
{
    return static_cast<bool>(GetPlantAt(x, y));
}

bool GameWorld::HasZombieAhead(int laneY, int fromX) const
{
    for (const auto& obj : mlist) {
        auto zombie = obj->AsZombie();
        if (!zombie || zombie->IsDead()) {
            continue;
        }

        if (std::abs(zombie->GetY() - laneY) <= LAWN_GRID_HEIGHT / 2 && zombie->GetX() > fromX) {
            return true;
        }
    }
    return false;
}

void GameWorld::HideUiText()
{
    if (m_sunText) {
        m_sunText->SetText("");
    }
    if (m_waveText) {
        m_waveText->SetText("");
    }
}

void GameWorld::UpdateShovelMousePosition(int x, int y)
{
    ::UpdateShovelMousePosition(x, y);
}
