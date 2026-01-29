#ifndef ZOMBIE_HPP__
#define ZOMBIE_HPP__

#include "pvz/GameObject/GameObject.hpp"
#include <memory>

class GameWorld;
class Plant;

/// @brief 僵尸基类
class Zombie : public GameObject {
public:
    Zombie(ImageID imageID, int x, int y, LayerID layer, int width, int height, AnimID animID, int hp, int damage, int walkSpeed = 1);

    virtual void Update() override;
    virtual void OnClick() override;

    Zombie* AsZombie() override { return this; }
    const Zombie* AsZombie() const override { return this; }

    bool isPlant() const override { return false; }
    bool isZombie() const override { return true; }
    bool isSeed() const override { return false; }
    bool isProjectile() const override { return false; }

    int GetDamage() const { return m_damage; }
    void SetWorld(std::shared_ptr<GameWorld> world) { m_world = world; }
    int GetWalkSpeed() const { return m_walkSpeed; }
    virtual int GetCurrentSpeed() const { return m_walkSpeed; }

    // 受到伤害
    void TakeDamage(int damage);

    void KnockBack(int distance);

    // 获取和设置目标植物
    std::shared_ptr<Plant> GetTargetPlant() const { return m_targetPlant; }
    virtual void SetTargetPlant(std::shared_ptr<Plant> plant);

    bool HasBreached() const { return m_hasBreached; }

protected:
    int m_damage; // 攻击力
    std::weak_ptr<GameWorld> m_world;
    std::shared_ptr<Plant> m_targetPlant; // 正在咀嚼的植物
    int m_walkSpeed;
    bool m_hasBreached = false;
};

#endif // !ZOMBIE_HPP__
