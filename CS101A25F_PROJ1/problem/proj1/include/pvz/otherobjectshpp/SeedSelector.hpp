#pragma once

#include "pvz/GameObject/GameObject.hpp"
#include <memory>

class GameWorld;
class Seed;

/**
 * @class SeedSelector
 * @brief 隐形的种子选择器，玩家拿着时可以种植植物
 *
 * 这是"隐形的兔子"模式的应用。
 * 当玩家点击种子包时，会生成这个对象。
 * 玩家点击 PlantingSpot 时会种植对应的植物。
 */
class SeedSelector : public GameObject
{
public:
    SeedSelector(std::shared_ptr<Seed> relatedSeed);
    ~SeedSelector() = default;

    void Update() override;
    void OnClick() override;
    bool isPlant() const override { return false; }
    bool isZombie() const override { return false; }
    bool isProjectile() const override { return false; }
    bool isSeed() const override { return false; }

    std::shared_ptr<Seed> GetRelatedSeed() const { return m_relatedSeed; }
    void SetGameWorld(std::weak_ptr<GameWorld> world) { m_world = world; }

private:
    std::shared_ptr<Seed> m_relatedSeed;
    std::weak_ptr<GameWorld> m_world;

    SeedSelector(const SeedSelector &) = delete;
    SeedSelector &operator=(const SeedSelector &) = delete;
};
