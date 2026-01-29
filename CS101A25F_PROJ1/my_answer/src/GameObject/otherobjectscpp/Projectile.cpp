#include "pvz/otherobjectshpp/Projectile.hpp"

#include <cmath>

#include "pvz/otherobjectshpp/Zombie.hpp"

bool Projectile::CollidesWith(const Zombie &zombie) const
{
    const int dx = std::abs(GetX() - zombie.GetX());
    const int dy = std::abs(GetY() - zombie.GetY());
    const int halfWidth = (GetWidth() + zombie.GetWidth()) / 2;
    const int halfHeight = (GetHeight() + zombie.GetHeight()) / 2;
    return dx <= halfWidth && dy <= halfHeight;
}
