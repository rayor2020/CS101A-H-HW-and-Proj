#pragma once

#include "pvz/otherobjectshpp/Projectile.hpp"

/**
 * @class Explosion
 * @brief 爆炸特效，由樱桃炸弹产生
 *
 * 存在3帧，在此期间杀死所有与其碰撞的僵尸。
 */
class Explosion : public Projectile
{
public:
    Explosion(int x, int y);
    ~Explosion() = default;

    void Update() override;
    void OnClick() override;
    void OnHit(Zombie &zombie) override;
    bool AllowMultipleHits() const override { return true; }
    bool CollidesWith(const Zombie &zombie) const override;

private:
    int m_lifeRemaining; // 剩余生命周期（3帧）

    Explosion(const Explosion &) = delete;
    Explosion &operator=(const Explosion &) = delete;
};
