#ifndef GAMEOBJECT_HPP__
#define GAMEOBJECT_HPP__

#include "pvz/Framework/ObjectBase.hpp"
#include <memory>

// Forward declarations to avoid circular dependencies.
class GameWorld;
class Plant;
class Zombie;
class Projectile;
using pGameWorld = std::shared_ptr<GameWorld>;

class GameObject : public ObjectBase, public std::enable_shared_from_this<GameObject>
{
    // Use shared_from_this() instead of "this" to create a pointer to oneself.
public:
    // 构造函数支持不同的参数组合
    GameObject(ImageID imageID, int x, int y, LayerID layer, int width, int height, AnimID animID)
        : ObjectBase(imageID, x, y, layer, width, height, animID), HP(0) {}

    GameObject(ImageID imageID, int x, int y, LayerID layer, int width, int height, AnimID animID, int hp)
        : ObjectBase(imageID, x, y, layer, width, height, animID), HP(hp) {}

    // 纯虚函数
    virtual bool isPlant() const = 0;
    virtual bool isZombie() const = 0;
    virtual bool isSeed() const = 0;
    virtual bool isProjectile() const = 0;
    virtual void Update() {}
    virtual void OnClick() {}

    // 类型识别接口，使用虚函数避免 RTTI。
    virtual Plant *AsPlant() { return nullptr; }
    virtual const Plant *AsPlant() const { return nullptr; }
    virtual Zombie *AsZombie() { return nullptr; }
    virtual const Zombie *AsZombie() const { return nullptr; }
    virtual Projectile *AsProjectile() { return nullptr; }
    virtual const Projectile *AsProjectile() const { return nullptr; }

    void SetHP(int hp) { HP = hp; }
    int GetHP() const { return HP; }

    void MarkDead() { m_isDead = true; }
    bool IsDead() const { return m_isDead; }

    using std::enable_shared_from_this<GameObject>::shared_from_this;

protected:
    int HP = 0; // Initialize HP to 0 to fix the error
    bool m_isDead = false;
};

/// @brief 背景
class Background : public GameObject
{
public:
    Background() : GameObject(ImageID::BACKGROUND, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, LayerID::BACKGROUND, WINDOW_WIDTH, WINDOW_HEIGHT, AnimID::NO_ANIMATION, 1)
    {
    }

    void Update() override {}
    void OnClick() override {}

    bool isPlant() const override { return false; }
    bool isZombie() const override { return false; }
    bool isSeed() const override { return false; }
    bool isProjectile() const override { return false; }
};

/// @brief PlantingSpot
class PlantingSpot : public GameObject
{
public:
    PlantingSpot(int x, int y) : GameObject(ImageID::NONE, x, y, LayerID::UI, 60, 80, AnimID::NO_ANIMATION, 1)
    {
    }

    void Update() override {}
    void OnClick() override;

    // 设置所属的 GameWorld
    void SetGameWorld(std::weak_ptr<GameWorld> world) { m_world = world; }

    bool isPlant() const override { return false; }
    bool isZombie() const override { return false; }
    bool isSeed() const override { return false; }
    bool isProjectile() const override { return false; }

private:
    std::weak_ptr<GameWorld> m_world;
    void PlantAt(std::shared_ptr<class Seed> seed);
};

#endif // !GAMEOBJECT_HPP__
