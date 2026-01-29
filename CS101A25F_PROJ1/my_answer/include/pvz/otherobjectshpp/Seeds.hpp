#ifndef PVZ_SEEDS_HPP
#define PVZ_SEEDS_HPP

#include "pvz/otherobjectshpp/Seed.hpp"
#include <memory>

class Plant;
class GameWorld;

class SunflowerSeed : public Seed {
public:
    SunflowerSeed(LayerID layer);

    void OnPurchase() override;
    int GetCost() const override { return 50; }
    int GetCooldownTime() const override { return 225; }
    int GetStartCooldown() const override { return 0; }
    std::shared_ptr<Plant> CreatePlant(int x, int y, std::shared_ptr<GameWorld> world) override;
};

class PeashooterSeed : public Seed {
public:
    PeashooterSeed(LayerID layer);

    void OnPurchase() override;
    int GetCost() const override { return 100; }
    int GetCooldownTime() const override { return 225; }
    int GetStartCooldown() const override { return 0; }
    std::shared_ptr<Plant> CreatePlant(int x, int y, std::shared_ptr<GameWorld> world) override;
};

class WallnutSeed : public Seed {
public:
    WallnutSeed(LayerID layer);

    void OnPurchase() override;
    int GetCost() const override { return 50; }
    int GetCooldownTime() const override { return 900; }
    int GetStartCooldown() const override { return 600; }
    std::shared_ptr<Plant> CreatePlant(int x, int y, std::shared_ptr<GameWorld> world) override;
};

class CherryBombSeed : public Seed {
public:
    CherryBombSeed(LayerID layer);

    void OnPurchase() override;
    int GetCost() const override { return 150; }
    int GetCooldownTime() const override { return 1500; }
    int GetStartCooldown() const override { return 1050; }
    std::shared_ptr<Plant> CreatePlant(int x, int y, std::shared_ptr<GameWorld> world) override;
};

class RepeaterSeed : public Seed {
public:
    RepeaterSeed(LayerID layer);

    void OnPurchase() override;
    int GetCost() const override { return 200; }
    int GetCooldownTime() const override { return 225; }
    int GetStartCooldown() const override { return 200; }
    std::shared_ptr<Plant> CreatePlant(int x, int y, std::shared_ptr<GameWorld> world) override;
};

class RedRepeaterSeed : public Seed {
public:
    RedRepeaterSeed(LayerID layer);

    void OnPurchase() override;
    int GetCost() const override { return 200; }
    int GetCooldownTime() const override { return 225; }
    int GetStartCooldown() const override { return 300; }
    std::shared_ptr<Plant> CreatePlant(int x, int y, std::shared_ptr<GameWorld> world) override;
};

#endif // PVZ_SEEDS_HPP
