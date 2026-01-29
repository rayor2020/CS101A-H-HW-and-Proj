#include "pvz/otherobjectshpp/Shovel.hpp"
#include "pvz/GameWorld/GameWorld.hpp"
#include "pvz/utils.hpp"

Shovel::Shovel()
    : GameObject(ImageID::SHOVEL, 600, WINDOW_HEIGHT - 40, LayerID::UI, 50, 50, AnimID::NO_ANIMATION)
{
}

void Shovel::Update()
{
    // 铲子不需要更新
}

void Shovel::OnClick()
{
    auto world = m_world.lock();
    if (!world)
        return;

    // 如果玩家拿着种子，点击铲子无效
    if (world->IsHoldingSeed())
    {
        return;
    }

    // 切换铲子的状态（拿起/放下）
    world->ToggleShovel();
}
