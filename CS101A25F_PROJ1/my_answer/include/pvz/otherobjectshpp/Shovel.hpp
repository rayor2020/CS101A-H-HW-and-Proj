#pragma once

#include "pvz/GameObject/GameObject.hpp"
#include <memory>

// 前向声明
class GameWorld;

// 函数声明，用于更新鼠标位置
void UpdateShovelMousePosition(int x, int y);

// 函数声明，用于清理预览铲子
void ClearPreviewShovel();

/**
 * @class Shovel
 * @brief 铲子，用于铲除植物
 *
 * 点击铲子后，可以点击植物来铲除它。
 * 铲掉一个植物后，铲子会自动放下。
 */
class Shovel : public GameObject {
public:
    Shovel(LayerID layer);
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

    Shovel(const Shovel&) = delete;
    Shovel& operator=(const Shovel&) = delete;
};