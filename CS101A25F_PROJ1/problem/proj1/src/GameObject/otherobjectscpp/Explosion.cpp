#include "pvz/otherobjectshpp/Explosion.hpp"
#include "pvz/otherobjectshpp/Zombie.hpp"
#include "pvz/utils.hpp"

Explosion::Explosion(int x, int y)
    : Projectile(ImageID::EXPLOSION, x, y, LayerID::PROJECTILES,
                 3 * LAWN_GRID_WIDTH, 3 * LAWN_GRID_HEIGHT, AnimID::NO_ANIMATION),
      m_lifeRemaining(3)
{
}

void Explosion::Update()
{
    // 减少生命周期
    m_lifeRemaining--;

    // 生命周期结束时死亡
    if (m_lifeRemaining <= 0)
    {
        MarkDead();
    }
}

void Explosion::OnClick()
{
    // 爆炸不响应点击
}

void Explosion::OnHit(Zombie &zombie)
{
    zombie.MarkDead();
}

bool Explosion::CollidesWith(const Zombie &zombie) const
{
    return Projectile::CollidesWith(zombie);
}
