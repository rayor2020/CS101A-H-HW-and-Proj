#include "pvz/otherobjectshpp/Pea.hpp"
#include "pvz/otherobjectshpp/Zombie.hpp"
#include "pvz/utils.hpp"

Pea::Pea(int x, int y)
    : Projectile(ImageID::PEA, x, y, LayerID::PROJECTILES, 28, 28, AnimID::NO_ANIMATION)
    , m_damage(20)
{
}

void Pea::Update()
{
    // 豌豆向右移动
    int newX = GetX() + 6;
    MoveTo(newX, GetY());

    // 如果豌豆飞出屏幕右边，则消失
    if (GetX() > WINDOW_WIDTH + 50) {
        MarkDead();
    }
}

void Pea::OnClick()
{
    // 豌豆不能被点击
}

void Pea::OnHit(Zombie& zombie)
{
    zombie.TakeDamage(m_damage);
    // zombie.KnockBack(5); // 击退测试
    MarkDead();
}

// 红色双发射手
RedPea::RedPea(int x, int y)
    : Projectile(ImageID::RED_PEA, x, y, LayerID::PROJECTILES, 28, 28, AnimID::NO_ANIMATION)
    , m_damage(15)
{
}

void RedPea::Update()
{
    // 豌豆向右移动
    int newX = GetX() + 8;
    MoveTo(newX, GetY());

    // 如果豌豆飞出屏幕右边，则消失
    if (GetX() > WINDOW_WIDTH + 50) {
        MarkDead();
    }
}

void RedPea::OnClick()
{
    // 豌豆不能被点击
}

void RedPea::OnHit(Zombie& zombie)
{
    zombie.TakeDamage(m_damage);
    zombie.KnockBack(10);
    MarkDead();
}
