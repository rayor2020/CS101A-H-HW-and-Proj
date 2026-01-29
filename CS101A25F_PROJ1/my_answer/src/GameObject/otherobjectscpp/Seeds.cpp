#include "pvz/otherobjectshpp/Seeds.hpp"

#include "pvz/GameWorld/GameWorld.hpp"
#include "pvz/otherobjectshpp/Plants.hpp"
#include "pvz/utils.hpp"

SunflowerSeed::SunflowerSeed(LayerID layer)
    : Seed(ImageID::SEED_SUNFLOWER, 130, WINDOW_HEIGHT - 44, layer, 50, 70)
{
    PlayAnimation(AnimID::NO_ANIMATION);
}

void SunflowerSeed::OnPurchase()
{
}

std::shared_ptr<Plant> SunflowerSeed::CreatePlant(int x, int y, std::shared_ptr<GameWorld> world)
{
    return std::make_shared<Sunflower>(x, y, world);
}

PeashooterSeed::PeashooterSeed(LayerID layer)
    : Seed(ImageID::SEED_PEASHOOTER, 190, WINDOW_HEIGHT - 44, layer, 50, 70)
{
    PlayAnimation(AnimID::NO_ANIMATION);
}

void PeashooterSeed::OnPurchase()
{
}

std::shared_ptr<Plant> PeashooterSeed::CreatePlant(int x, int y, std::shared_ptr<GameWorld> world)
{
    return std::make_shared<Peashooter>(x, y, world);
}

WallnutSeed::WallnutSeed(LayerID layer)
    : Seed(ImageID::SEED_WALLNUT, 250, WINDOW_HEIGHT - 44, layer, 50, 70)
{
    PlayAnimation(AnimID::NO_ANIMATION);
}

void WallnutSeed::OnPurchase()
{
}

std::shared_ptr<Plant> WallnutSeed::CreatePlant(int x, int y, std::shared_ptr<GameWorld> world)
{
    return std::make_shared<Wallnut>(x, y, world);
}

CherryBombSeed::CherryBombSeed(LayerID layer)
    : Seed(ImageID::SEED_CHERRY_BOMB, 310, WINDOW_HEIGHT - 44, layer, 50, 70)
{
    PlayAnimation(AnimID::NO_ANIMATION);
}

void CherryBombSeed::OnPurchase()
{
}

std::shared_ptr<Plant> CherryBombSeed::CreatePlant(int x, int y, std::shared_ptr<GameWorld> world)
{
    return std::make_shared<CherryBomb>(x, y, world);
}

RepeaterSeed::RepeaterSeed(LayerID layer)
    : Seed(ImageID::SEED_REPEATER, 370, WINDOW_HEIGHT - 44, layer, 50, 70)
{
    PlayAnimation(AnimID::NO_ANIMATION);
}

void RepeaterSeed::OnPurchase()
{
}

std::shared_ptr<Plant> RepeaterSeed::CreatePlant(int x, int y, std::shared_ptr<GameWorld> world)
{
    return std::make_shared<Repeater>(x, y, world);
}

RedRepeaterSeed::RedRepeaterSeed(LayerID layer)
    : Seed(ImageID::SEED_RED_REPEATER, 430, WINDOW_HEIGHT - 44, layer, 50, 70)
{
    PlayAnimation(AnimID::NO_ANIMATION);
}

void RedRepeaterSeed::OnPurchase()
{
}

std::shared_ptr<Plant> RedRepeaterSeed::CreatePlant(int x, int y, std::shared_ptr<GameWorld> world)
{
    return std::make_shared<RedRepeater>(x, y, world);
}