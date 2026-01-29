#ifndef SUN_HPP__
#define SUN_HPP__

#include "pvz/GameObject/GameObject.hpp"
#include <memory>

class GameWorld;

/// @brief 阳光类
class Sun : public GameObject
{
public:
    /// @param x 起始X坐标
    /// @param y 起始Y坐标
    /// @param isDropping true=掉落的阳光，false=植物产生的阳光
    /// @param world GameWorld指针
    Sun(int x, int y, bool isDropping, std::shared_ptr<GameWorld> world);

    void Update() override;
    void OnClick() override;

    bool isPlant() const override { return false; }
    bool isZombie() const override { return false; }
    bool isSeed() const override { return false; }
    bool isProjectile() const override { return false; }

private:
    bool m_isFromPlant;     // 是否由植物生成
    bool m_isDropping;      // 是否正在从天上掉落
    bool m_isGrounded;      // 是否已经落地
    int m_groundY;          // 落地点Y坐标
    int m_groundLifetime;   // 落地后存在时间
    int m_parabolaTimer;    // 植物生成阳光的抛物线计时
    int m_verticalVelocity; // 植物阳光的初始竖直速度
    std::weak_ptr<GameWorld> m_world;
};

#endif // !SUN_HPP__
