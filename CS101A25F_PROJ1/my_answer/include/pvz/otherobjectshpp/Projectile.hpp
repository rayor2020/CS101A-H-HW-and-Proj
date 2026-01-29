#pragma once

#include "pvz/GameObject/GameObject.hpp"

class Zombie;

/**
 * @class Projectile
 * @brief 游戏中所有投射物的基类，负责处理与僵尸的碰撞。
 */
class Projectile : public GameObject
{
public:
    Projectile(ImageID imageID, int x, int y, LayerID layer, int width, int height, AnimID animID)
        : GameObject(imageID, x, y, layer, width, height, animID)
    {
    }

    Projectile *AsProjectile() override { return this; }
    const Projectile *AsProjectile() const override { return this; }

    bool isPlant() const override { return false; }
    bool isZombie() const override { return false; }
    bool isSeed() const override { return false; }
    bool isProjectile() const override { return true; }

    /// @brief 检测与僵尸是否发生碰撞。
    virtual bool CollidesWith(const Zombie &zombie) const;

    /// @brief 与僵尸碰撞后的处理逻辑。
    virtual void OnHit(Zombie &zombie) = 0;

    /// @brief 是否在命中后继续保留以影响其他目标。
    virtual bool AllowMultipleHits() const { return false; }
};
