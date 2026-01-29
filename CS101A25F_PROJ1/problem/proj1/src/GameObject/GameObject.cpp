#include "pvz/GameObject/GameObject.hpp"
#include "pvz/GameWorld/GameWorld.hpp"
#include "pvz/otherobjectshpp/Plants.hpp"
#include "pvz/otherobjectshpp/Seeds.hpp"
#include "pvz/utils.hpp"

// PlantingSpot 的实现
void PlantingSpot::OnClick()
{
    auto world = m_world.lock();
    if (!world)
        return;

    if (world->IsHoldingShovel())
    {
        if (auto plant = world->GetPlantAt(GetX(), GetY()))
        {
            plant->MarkDead();
        }
        world->ReleaseShovel();
        return;
    }

    Seed *heldSeed = world->GetHoldingSeed();
    if (!heldSeed)
    {
        return;
    }

    if (world->HasPlantAt(GetX(), GetY()))
    {
        return;
    }

    auto plant = heldSeed->CreatePlant(GetX(), GetY(), world);
    if (plant)
    {
        world->Add(plant);
        world->ClearHoldingSeed();
    }
}