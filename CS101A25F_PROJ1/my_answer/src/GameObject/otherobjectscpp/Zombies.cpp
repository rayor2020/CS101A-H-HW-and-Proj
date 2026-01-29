#include "pvz/otherobjectshpp/Zombies.hpp"

#include "pvz/GameWorld/GameWorld.hpp"
#include "pvz/otherobjectshpp/Plant.hpp"

RegularZombie::RegularZombie(int x, int y, std::shared_ptr<GameWorld> world)
    : Zombie(ImageID::REGULAR_ZOMBIE, x, y, LayerID::ZOMBIES, 20, 80, AnimID::WALK, 200, 4, 1)
{
    SetWorld(world);
    PlayAnimation(AnimID::WALK);
}

BucketHeadZombie::BucketHeadZombie(int x, int y, std::shared_ptr<GameWorld> world)
    : Zombie(ImageID::BUCKET_HEAD_ZOMBIE, x, y, LayerID::ZOMBIES, 20, 80, AnimID::WALK, 1300, 4, 1)
{
    SetWorld(world);
    PlayAnimation(AnimID::WALK);
}

void BucketHeadZombie::Update()
{
    if (GetHP() <= 200 && m_bucketIntact) {
        ChangeImage(ImageID::REGULAR_ZOMBIE);
        m_bucketIntact = false;
    }
    Zombie::Update();
}

PoleVaultingZombie::PoleVaultingZombie(int x, int y, std::shared_ptr<GameWorld> world)
    : Zombie(ImageID::POLE_VAULTING_ZOMBIE, x, y, LayerID::ZOMBIES, 20, 80, AnimID::RUN, 1600, 4, 1)
    , m_state(VaultState::Running)
    , m_jumpTimer(0)
{
    SetWorld(world);
    PlayAnimation(AnimID::RUN);
}

void PoleVaultingZombie::Update()
{
    if (IsDead()) {
        return;
    }

    if (m_state == VaultState::Jumping) {
        if (--m_jumpTimer <= 0) {
            MoveTo(GetX() - 150, GetY());
            m_state = VaultState::Walking;
            PlayAnimation(AnimID::WALK);
        }
        return;
    }

    if (m_state == VaultState::Running) {
        if (auto world = m_world.lock()) {
            auto plantAhead = world->GetPlantAt(GetX() - 40, GetY());
            if (plantAhead && plantAhead->IsAlive()) {
                m_state = VaultState::Jumping;
                m_jumpTimer = 42;
                PlayAnimation(AnimID::JUMP);
                return;
            }
        }
    }

    Zombie::Update();
}

int PoleVaultingZombie::GetCurrentSpeed() const
{
    switch (m_state) {
    case VaultState::Running:
        return 2;
    case VaultState::Walking:
        return 1;
    case VaultState::Jumping:
    default:
        return 0;
    }
}

void PoleVaultingZombie::SetTargetPlant(std::shared_ptr<Plant> plant)
{
    if (m_state == VaultState::Jumping && plant) {
        return;
    }
    Zombie::SetTargetPlant(plant);
    if (plant) {
        m_state = VaultState::Walking;
    }
}
