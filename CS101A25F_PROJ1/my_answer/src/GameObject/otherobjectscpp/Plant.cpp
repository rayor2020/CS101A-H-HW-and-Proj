#include "pvz/otherobjectshpp/Plant.hpp"
#include "pvz/GameWorld/GameWorld.hpp"

Plant::Plant(ImageID imageID, int x, int y, LayerID layer, int width, int height, AnimID animID, int hp, int cost)
    : GameObject(imageID, x, y, layer, width, height, animID)
    , m_cost(cost)
{
    SetHP(hp);
}

void Plant::Update()
{
    // 默认实现，子类可以重写
}

void Plant::TakeDamage(int amount)
{
    if (GetHP() > 0) {
        SetHP(GetHP() - amount);
        if (GetHP() <= 0) {
            MarkDead();
        }
    }
}

void Plant::OnClick()
{
    auto world = m_world.lock();
    if (!world) {
        return;
    }

    if (!world->IsHoldingShovel()) {
        return;
    }

    MarkDead();
    // 不再调用world->ReleaseShovel()，保持铲子状态以便连续使用
    // 不再清除铲子预览，保持预览直到用户放下铲子
}