#ifndef PVZ_SEEDS_HPP
#define PVZ_SEEDS_HPP

#include "pvz/otherobjectshpp/Seed.hpp"
#include <memory>

class Plant;
class GameWorld;

class SunflowerSeed : public Seed
{
public:
    SunflowerSeed();

    void OnPurchase() override;
    int GetCost() const override { return 50; }
    int GetCooldownTime() const override { return 240; }
    std::shared_ptr<Plant> CreatePlant(int x, int y, std::shared_ptr<GameWorld> world) override;
};

class PeashooterSeed : public Seed
{
public:
    PeashooterSeed();

    void OnPurchase() override;
    int GetCost() const override { return 100; }
    int GetCooldownTime() const override { return 240; }
    std::shared_ptr<Plant> CreatePlant(int x, int y, std::shared_ptr<GameWorld> world) override;
};

class WallnutSeed : public Seed
{
public:
    WallnutSeed();

    void OnPurchase() override;
    int GetCost() const override { return 50; }
    int GetCooldownTime() const override { return 900; }
    std::shared_ptr<Plant> CreatePlant(int x, int y, std::shared_ptr<GameWorld> world) override;
};

class CherryBombSeed : public Seed
{
public:
    CherryBombSeed();

    void OnPurchase() override;
    int GetCost() const override { return 150; }
    int GetCooldownTime() const override { return 1200; }
    std::shared_ptr<Plant> CreatePlant(int x, int y, std::shared_ptr<GameWorld> world) override;
};

class RepeaterSeed : public Seed
{
public:
    RepeaterSeed();

    void OnPurchase() override;
    int GetCost() const override { return 200; }
    int GetCooldownTime() const override { return 240; }
    std::shared_ptr<Plant> CreatePlant(int x, int y, std::shared_ptr<GameWorld> world) override;
};

#endif // PVZ_SEEDS_HPP
