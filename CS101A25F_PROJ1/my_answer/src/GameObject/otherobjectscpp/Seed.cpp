#include "pvz/otherobjectshpp/Seed.hpp"
#include "pvz/GameWorld/GameWorld.hpp"
#include "pvz/otherobjectshpp/CooldownMask.hpp"
#include "pvz/otherobjectshpp/Plants.hpp"
#include "pvz/otherobjectshpp/Seeds.hpp"
#include "pvz/otherobjectshpp/Shovel.hpp"
#include "pvz/utils.hpp"
#include <memory>

// 添加静态变量用于跟踪当前的预览种子
static std::shared_ptr<Seed> s_previewSeed = nullptr;

// 添加静态变量存储鼠标位置（默认位置）
static int s_mouseX = 0;
static int s_mouseY = 0;

// 提供设置鼠标位置的公共方法（在其他地方调用）
void UpdateSeedMousePosition(int x, int y)
{
    s_mouseX = x;
    s_mouseY = y;

    // 更新预览种子位置
    if (s_previewSeed) {
        s_previewSeed->MoveTo(s_mouseX, s_mouseY);
    }

    // 同时更新预览铲子位置
    UpdateShovelMousePosition(x, y);
}

// 提供清理预览种子的公共方法
void ClearPreviewSeed()
{
    if (s_previewSeed) {
        s_previewSeed->MarkDead();
        s_previewSeed = nullptr;
    }
}

void Seed::Update()
{
    // 如果处于冷却状态，减少冷却时间
    if (m_cooldownRemaining > 0) {
        m_cooldownRemaining--;

        // 检查是否已存在冷却遮罩，如果不存在则创建一个
        bool hasCooldownMask = false;
        if (auto world = m_world.lock()) {
            for (const auto& obj : world->GetObjects()) {
                if (auto mask = std::dynamic_pointer_cast<CooldownMask>(obj)) {
                    if (mask->GetX() == GetX() && mask->GetY() == GetY()) {
                        hasCooldownMask = true;
                        break;
                    }
                }
            }

            // 如果没有冷却遮罩且处于冷却状态，则创建一个
            if (!hasCooldownMask) {
                auto mask = std::make_shared<CooldownMask>(GetX(), GetY(),
                    std::static_pointer_cast<Seed>(shared_from_this()));
                world->Add(mask);
            }
        }
    }

    // 更新预览种子位置（额外保障）
    if (s_previewSeed) {
        s_previewSeed->MoveTo(s_mouseX, s_mouseY);
    }
}

void Seed::OnClick()
{
    // 如果正在冷却，则不能购买
    auto world = m_world.lock();
    if (!world || IsInCooldown()) {
        return;
    }

    // 如果玩家已经拿着铲子，则不能购买
    if (world->IsHoldingShovel()) {
        return;
    }

    // 如果玩家已经拿着种子
    if (world->IsHoldingSeed()) {
        // 如果再次点击相同的种子，则取消放置
        if (world->GetHoldingSeed() == this) {
            // 删除预览种子
            if (s_previewSeed) {
                s_previewSeed->MarkDead(); // 标记为死亡，让系统自动清理
                s_previewSeed = nullptr;
            }
            world->ClearHoldingSeed();
        }
        // 如果点击的是不同种子，应该放下当前种子而不是切换到新种子
        else {
            // 不管阳光是否足够，都放下当前种子（即清除持有状态）
            // 删除预览种子
            if (s_previewSeed) {
                s_previewSeed->MarkDead(); // 标记为死亡，让系统自动清理
                s_previewSeed = nullptr;
            }
            world->ClearHoldingSeed();
        }
        return;
    }

    // 检查阳光是否足够
    if (world->GetSunCount() >= GetCost()) {
        // 设置玩家拿着种子的状态
        world->SetHoldingSeed(this);

        // 创建预览种子
        std::shared_ptr<Seed> newPreviewSeed = nullptr;
        if (dynamic_cast<SunflowerSeed*>(this)) {
            newPreviewSeed = std::make_shared<SunflowerSeed>(LayerID::PREVIEW);
        } else if (dynamic_cast<PeashooterSeed*>(this)) {
            newPreviewSeed = std::make_shared<PeashooterSeed>(LayerID::PREVIEW);
        } else if (dynamic_cast<WallnutSeed*>(this)) {
            newPreviewSeed = std::make_shared<WallnutSeed>(LayerID::PREVIEW);
        } else if (dynamic_cast<CherryBombSeed*>(this)) {
            newPreviewSeed = std::make_shared<CherryBombSeed>(LayerID::PREVIEW);
        } else if (dynamic_cast<RepeaterSeed*>(this)) {
            newPreviewSeed = std::make_shared<RepeaterSeed>(LayerID::PREVIEW);
        } else if (dynamic_cast<RedRepeaterSeed*>(this)) {
            newPreviewSeed = std::make_shared<RedRepeaterSeed>(LayerID::PREVIEW);
        }

        if (newPreviewSeed) {
            // 设置为预览状态（HP为-1表示特殊对象，不会被自动清理）
            newPreviewSeed->SetHP(-1);
            // 设置预览种子的位置
            newPreviewSeed->MoveTo(s_mouseX, s_mouseY);
            s_previewSeed = newPreviewSeed;
            world->Add(s_previewSeed);
        }

        // 调用种子特定的购买逻辑（可由子类重写）
        OnPurchase();
    }
}