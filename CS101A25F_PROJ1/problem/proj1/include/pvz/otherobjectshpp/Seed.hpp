#pragma once

#include "pvz/GameObject/GameObject.hpp"
#include <memory>

// 前向声明
class GameWorld;

/**
 * @class Seed
 * @brief 种子的基类，代表植物的种子包按钮
 *
 * 种子可以被点击来选择种植植物。每种种子有不同的冷却时间和花费。
 * 使用模板设计模式实现种子功能。
 */
class Seed : public GameObject
{
public:
    virtual ~Seed() = default;

    // GameObject 虚函数实现
    void Update() override;
    void OnClick() override;
    bool isPlant() const override { return false; }
    bool isZombie() const override { return false; }
    bool isProjectile() const override { return false; }
    bool isSeed() const override { return true; }

    // Seed 特定接口
    virtual int GetCost() const = 0;         // 花费的阳光数
    virtual int GetCooldownTime() const = 0; // 冷却时间（tick）
    virtual void OnPurchase() = 0;           // 购买时的操作（生成植物类型的选择）

    // 创建对应的植物（在 PlantingSpot 点击时调用）
    virtual std::shared_ptr<class Plant> CreatePlant(int x, int y, std::shared_ptr<GameWorld> world) = 0;

    // 冷却状态查询
    bool IsInCooldown() const { return m_cooldownRemaining > 0; }
    void ResetCooldown() { m_cooldownRemaining = GetCooldownTime(); }

    // 设置所属的 GameWorld
    void SetGameWorld(std::weak_ptr<GameWorld> world) { m_world = world; }

protected:
    Seed(ImageID imageID, int x, int y, int width, int height)
        : GameObject(imageID, x, y, LayerID::UI, width, height, AnimID::NO_ANIMATION),
          m_cooldownRemaining(0) {}

    std::weak_ptr<GameWorld> m_world;
    int m_cooldownRemaining; // 剩余冷却时间

private:
    // 禁止复制
    Seed(const Seed &) = delete;
    Seed &operator=(const Seed &) = delete;
};
