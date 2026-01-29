#include "pvz/GameObject/GameObject.hpp"
#include "pvz/GameWorld/GameWorld.hpp"
#include "pvz/otherobjectshpp/CooldownMask.hpp"
#include "pvz/otherobjectshpp/Plants.hpp"
#include "pvz/otherobjectshpp/Seeds.hpp"
#include "pvz/utils.hpp"

// PlantingSpot 的实现
void PlantingSpot::OnClick()
{
    auto world = m_world.lock();
    if (!world)
        return;

    if (world->IsHoldingShovel()) {
        if (auto plant = world->GetPlantAt(GetX(), GetY())) {
            plant->MarkDead();
        }
        // 清除铲子预览状态
        ClearPreviewSeed();
        // 不再调用world->ReleaseShovel()，保持铲子状态以便连续使用
        return;
    }

    Seed* heldSeed = world->GetHoldingSeed();
    if (!heldSeed) {
        return;
    }

    if (world->HasPlantAt(GetX(), GetY())) {
        return;
    }

    // 检查阳光是否足够（再次检查，防止在选择和种植之间阳光数量发生变化）
    if (world->GetSunCount() < heldSeed->GetCost()) {
        return;
    }

    auto plant = heldSeed->CreatePlant(GetX(), GetY(), world);
    if (plant) {
        // 花费阳光
        world->ChangeSun(-heldSeed->GetCost());

        // 进入冷却状态
        heldSeed->ResetCooldown();

        // 生成冷却遮盖物
        auto mask = std::make_shared<CooldownMask>(heldSeed->GetX(), heldSeed->GetY(),
            std::static_pointer_cast<Seed>(heldSeed->shared_from_this()));
        world->Add(mask);

        // 删除预览种子
        ClearPreviewSeed();

        world->Add(plant);
        world->ClearHoldingSeed();
    }
}