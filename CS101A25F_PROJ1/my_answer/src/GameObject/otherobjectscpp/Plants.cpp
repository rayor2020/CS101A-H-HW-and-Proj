#include "pvz/otherobjectshpp/Plants.hpp"

#include "pvz/GameWorld/GameWorld.hpp"
#include "pvz/otherobjectshpp/Explosion.hpp"
#include "pvz/otherobjectshpp/Pea.hpp"
#include "pvz/otherobjectshpp/Sun.hpp"
#include "pvz/utils.hpp"

namespace {
constexpr int kSunflowerFirstSunMin = 30;
constexpr int kSunflowerFirstSunMax = 300;
constexpr int kSunflowerSunInterval = 300;
constexpr int kPeashooterCooldown = 20;
constexpr int kCherryBombFuse = 15;
constexpr int kRepeaterCooldown = 20;
constexpr int kRepeaterSecondShotDelay = 5;
constexpr int kRedRepeaterCooldown = 16;
constexpr int kRedRepeaterSecondShotDelay = 4;
}

Sunflower::Sunflower(int x, int y, std::shared_ptr<GameWorld> world)
    : Plant(ImageID::SUNFLOWER, x, y, LayerID::PLANTS, 60, 80, AnimID::IDLE, 300, 50)
    , m_sunGenerateCD(randInt(kSunflowerFirstSunMin, kSunflowerFirstSunMax))
{
    SetWorld(world);
}

void Sunflower::Update()
{
    Plant::Update();
    if (IsDead()) {
        return;
    }

    if (m_sunGenerateCD > 0) {
        --m_sunGenerateCD;
    }

    if (m_sunGenerateCD == 0) {
        if (auto world = m_world.lock()) {
            world->Add(std::make_shared<Sun>(GetX(), GetY() + 50, false, world));
        }
        m_sunGenerateCD = kSunflowerSunInterval;
    }
}

void Sunflower::OnClick()
{
    Plant::OnClick();
}

Peashooter::Peashooter(int x, int y, std::shared_ptr<GameWorld> world)
    : Plant(ImageID::PEASHOOTER, x, y, LayerID::PLANTS, 60, 80, AnimID::IDLE, 300, 100)
    , m_shootCD(0)
{
    SetWorld(world);
}

void Peashooter::Update()
{
    Plant::Update();
    if (IsDead()) {
        return;
    }

    if (m_shootCD > 0) {
        --m_shootCD;
    }

    auto world = m_world.lock();
    if (!world) {
        return;
    }

    if (m_shootCD == 0 && world->HasZombieAhead(GetY(), GetX())) {
        world->Add(std::make_shared<Pea>(GetX() + 30, GetY() + 15));
        m_shootCD = kPeashooterCooldown;
    }
}

void Peashooter::OnClick()
{
    Plant::OnClick();
}

Wallnut::Wallnut(int x, int y, std::shared_ptr<GameWorld> world)
    : Plant(ImageID::WALLNUT, x, y, LayerID::PLANTS, 60, 80, AnimID::IDLE, 4000, 50)
    , m_isCracked(false)
{
    SetWorld(world);
}

void Wallnut::Update()
{
    Plant::Update();
    if (IsDead()) {
        return;
    }

    if (!m_isCracked && GetHP() <= 2000) {
        ChangeImage(ImageID::WALLNUT_CRACKED);
        m_isCracked = true;
    }
}

void Wallnut::OnClick()
{
    Plant::OnClick();
}

CherryBomb::CherryBomb(int x, int y, std::shared_ptr<GameWorld> world)
    : Plant(ImageID::CHERRY_BOMB, x, y, LayerID::PLANTS, 60, 80, AnimID::IDLE, -1, 150)
    , m_explosionCD(kCherryBombFuse)
{
    SetWorld(world);
}

void CherryBomb::Update()
{
    Plant::Update();
    if (IsDead()) {
        return;
    }

    if (--m_explosionCD <= 0) {
        if (auto world = m_world.lock()) {
            world->Add(std::make_shared<Explosion>(GetX(), GetY()));
        }
        MarkDead();
    }
}

void CherryBomb::OnClick()
{
    Plant::OnClick();
}

Repeater::Repeater(int x, int y, std::shared_ptr<GameWorld> world)
    : Plant(ImageID::REPEATER, x, y, LayerID::PLANTS, 60, 80, AnimID::IDLE, 400, 200)
    , m_shootCD(0)
    , m_secondShotCD(0)
{
    SetWorld(world);
    PlayAnimation(AnimID::IDLE);
}

void Repeater::Update()
{
    Plant::Update();
    if (IsDead()) {
        return;
    }

    auto world = m_world.lock();
    if (!world) {
        return;
    }

    if (m_shootCD > 0) {
        --m_shootCD;
    }

    if (m_secondShotCD > 0) {
        --m_secondShotCD;
        if (m_secondShotCD == 0 && world->HasZombieAhead(GetY(), GetX())) {
            world->Add(std::make_shared<Pea>(GetX() + 30, GetY() + 15));
        }
    }

    if (m_shootCD == 0 && world->HasZombieAhead(GetY(), GetX())) {
        world->Add(std::make_shared<Pea>(GetX() + 30, GetY() + 15));
        m_secondShotCD = kRepeaterSecondShotDelay;
        m_shootCD = kRepeaterCooldown;
    }
}

void Repeater::OnClick()
{
    Plant::OnClick();
}

// 红色双发射手
RedRepeater::RedRepeater(int x, int y, std::shared_ptr<GameWorld> world)
    : Plant(ImageID::RED_REPEATER, x, y, LayerID::PLANTS, 60, 80, AnimID::IDLE, 250, 200)
    , m_shootCD(0)
    , m_secondShotCD(0)
{
    SetWorld(world);
    PlayAnimation(AnimID::IDLE);
}

void RedRepeater::Update()
{
    Plant::Update();
    if (IsDead()) {
        return;
    }

    auto world = m_world.lock();
    if (!world) {
        return;
    }

    if (m_shootCD > 0) {
        --m_shootCD;
    }

    if (m_secondShotCD > 0) {
        --m_secondShotCD;
        if (m_secondShotCD == 0 && world->HasZombieAhead(GetY(), GetX())) {
            world->Add(std::make_shared<RedPea>(GetX() + 30, GetY() + 15));
        }
    }

    if (m_shootCD == 0 && world->HasZombieAhead(GetY(), GetX())) {
        world->Add(std::make_shared<RedPea>(GetX() + 30, GetY() + 15));
        m_secondShotCD = kRedRepeaterSecondShotDelay;
        m_shootCD = kRedRepeaterCooldown;
    }
}

void RedRepeater::OnClick()
{
    Plant::OnClick();
}
