#pragma once

#include "pvz/GameObject/GameObject.hpp"
#include <memory>

class GameWorld;

/**
 * @class Shovel
 * @brief 铲子，用于铲除植物
 *
 * 点击铲子后，可以点击植物来铲除它。
 * 铲掉一个植物后，铲子会自动放下。
 */
class Shovel : public GameObject
{
public:
    Shovel();
    ~Shovel() = default;

    void Update() override;
    void OnClick() override;
    bool isPlant() const override { return false; }
    bool isZombie() const override { return false; }
    bool isProjectile() const override { return false; }
    bool isSeed() const override { return false; }

    void SetGameWorld(std::weak_ptr<GameWorld> world) { m_world = world; }

private:
    std::weak_ptr<GameWorld> m_world;

    Shovel(const Shovel &) = delete;
    Shovel &operator=(const Shovel &) = delete;
};
