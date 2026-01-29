#include "pvz/otherobjectshpp/Seed.hpp"
#include "pvz/otherobjectshpp/CooldownMask.hpp"
#include "pvz/GameWorld/GameWorld.hpp"

void Seed::Update()
{
    // 如果处于冷却状态，减少冷却时间
    if (m_cooldownRemaining > 0)
    {
        m_cooldownRemaining--;
    }
}

void Seed::OnClick()
{
    // 如果正在冷却或玩家拿着铲子或种子，则不能购买
    auto world = m_world.lock();
    if (!world || IsInCooldown() || world->IsHoldingShovel() || world->IsHoldingSeed())
    {
        return;
    }

    // 检查阳光是否足够
    if (world->GetSunCount() >= GetCost())
    {
        // 花费阳光
        world->ChangeSun(-GetCost());

        // 进入冷却状态
        ResetCooldown();

        // 生成冷却遮盖物，将 shared_ptr<GameObject> 转换为 shared_ptr<Seed>
        auto mask = std::make_shared<CooldownMask>(GetX(), GetY(),
                                                   std::static_pointer_cast<Seed>(shared_from_this()));
        world->Add(mask);

        // 设置玩家拿着种子的状态
        world->SetHoldingSeed(this);

        // 调用种子特定的购买逻辑（可由子类重写）
        OnPurchase();
    }
}
