#include "pvz/otherobjectshpp/Seeds.hpp"

#include "pvz/GameWorld/GameWorld.hpp"
#include "pvz/otherobjectshpp/Plants.hpp"
#include "pvz/utils.hpp"

SunflowerSeed::SunflowerSeed()
    : Seed(ImageID::SEED_SUNFLOWER, 130, WINDOW_HEIGHT - 44, 50, 70)
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

PeashooterSeed::PeashooterSeed()
    : Seed(ImageID::SEED_PEASHOOTER, 190, WINDOW_HEIGHT - 44, 50, 70)
{
    PlayAnimation(AnimID::NO_ANIMATION);
}

void PeashooterSeed::OnPurchase()
{
}

std::shared_ptr<Plant> PeashooterSeed::CreatePlant(int x, int y, std::shared_ptr<GameWorld> world)
{
    return std::make_shared<PeaShooter>(x, y, world);
}

WallnutSeed::WallnutSeed()
    : Seed(ImageID::SEED_WALLNUT, 250, WINDOW_HEIGHT - 44, 50, 70)
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

CherryBombSeed::CherryBombSeed()
    : Seed(ImageID::SEED_CHERRY_BOMB, 310, WINDOW_HEIGHT - 44, 50, 70)
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

RepeaterSeed::RepeaterSeed()
    : Seed(ImageID::SEED_REPEATER, 370, WINDOW_HEIGHT - 44, 50, 70)
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
