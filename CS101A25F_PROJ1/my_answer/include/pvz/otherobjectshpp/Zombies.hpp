#ifndef PVZ_ZOMBIES_HPP
#define PVZ_ZOMBIES_HPP

#include "pvz/otherobjectshpp/Zombie.hpp"
#include <memory>

class GameWorld;

class RegularZombie : public Zombie
{
public:
    RegularZombie(int x, int y, std::shared_ptr<GameWorld> world);
};

class BucketHeadZombie : public Zombie
{
public:
    BucketHeadZombie(int x, int y, std::shared_ptr<GameWorld> world);

    void Update() override;

private:
    bool m_bucketIntact = true;
};

class PoleVaultingZombie : public Zombie
{
public:
    PoleVaultingZombie(int x, int y, std::shared_ptr<GameWorld> world);

    void Update() override;
    int GetCurrentSpeed() const override;
    void SetTargetPlant(std::shared_ptr<Plant> plant) override;

private:
    enum class VaultState
    {
        Running,
        Jumping,
        Walking
    };

    VaultState m_state;
    int m_jumpTimer;
};

#endif // PVZ_ZOMBIES_HPP
