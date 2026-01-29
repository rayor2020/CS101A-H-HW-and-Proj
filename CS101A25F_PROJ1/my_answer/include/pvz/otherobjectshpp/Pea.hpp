#ifndef PEA_HPP__
#define PEA_HPP__

#include "pvz/otherobjectshpp/Projectile.hpp"
#include <memory>

/// @brief 豌豆类 - 豌豆射手发射的投射物
class Pea : public Projectile {
public:
    /// @param x 起始X坐标
    /// @param y 起始Y坐标
    Pea(int x, int y);

    void Update() override;
    void OnClick() override;

    void OnHit(Zombie& zombie) override;

    int GetDamage() const { return m_damage; }

private:
    int m_damage; // 豌豆伤害值
};

/// @brief 红色豌豆类 - 红色双发射手发射的投射物
class RedPea : public Projectile {
public:
    /// @param x 起始X坐标
    /// @param y 起始Y坐标
    RedPea(int x, int y);

    void Update() override;
    void OnClick() override;

    void OnHit(Zombie& zombie) override;

    int GetDamage() const { return m_damage; }

private:
    int m_damage; // 豌豆伤害值
};

#endif // !PEA_HPP__
