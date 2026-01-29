#include "pvz/otherobjectshpp/Plant.hpp"
#include "pvz/GameWorld/GameWorld.hpp"

Plant::Plant(ImageID imageID, int x, int y, LayerID layer, int width, int height, AnimID animID, int hp, int cost)
    : GameObject(imageID, x, y, layer, width, height, animID, hp),
      m_cost(cost)
{
}

void Plant::Update()
{
    if (GetHP() <= 0)
    {
        MarkDead();
    }
}

void Plant::OnClick()
{
    auto world = m_world.lock();
    if (!world)
    {
        return;
    }

    if (!world->IsHoldingShovel())
    {
        return;
    }

    MarkDead();
    world->ReleaseShovel();
}

void Plant::TakeDamage(int amount)
{
    if (amount <= 0 || IsDead())
    {
        return;
    }
    SetHP(GetHP() - amount);
    if (GetHP() <= 0)
    {
        MarkDead();
    }
}
