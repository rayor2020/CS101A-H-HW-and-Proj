#ifndef PLANT_HPP__
#define PLANT_HPP__

#include "pvz/GameObject/GameObject.hpp"
#include <memory>

class GameWorld;

/// @brief 植物基类
class Plant : public GameObject {
public:
    Plant(ImageID imageID, int x, int y, LayerID layer, int width, int height, AnimID animID, int hp, int cost);

    virtual void Update() override;
    virtual void OnClick() override;

    Plant* AsPlant() override { return this; }
    const Plant* AsPlant() const override { return this; }

    bool isPlant() const override { return true; }
    bool isZombie() const override { return false; }
    bool isSeed() const override { return false; }
    bool isProjectile() const override { return false; }

    int GetCost() const { return m_cost; }
    void SetWorld(std::shared_ptr<GameWorld> world) { m_world = world; }
    bool IsAlive() const { return !IsDead() && GetHP() > 0; }
    virtual void TakeDamage(int amount);

protected:
    int m_cost; // 种植消耗的阳光
    std::weak_ptr<GameWorld> m_world;
};

#endif // !PLANT_HPP__
