#include "pvz/otherobjectshpp/Zombie.hpp"
#include "pvz/GameWorld/GameWorld.hpp"
#include "pvz/otherobjectshpp/Plant.hpp"

Zombie::Zombie(ImageID imageID, int x, int y, LayerID layer, int width, int height, AnimID animID, int hp, int damage, int walkSpeed)
    : GameObject(imageID, x, y, layer, width, height, animID, hp)
    , m_damage(damage)
    , m_walkSpeed(walkSpeed)
{
}

void Zombie::Update()
{
    if (IsDead()) {
        return;
    }

    if (GetHP() <= 0) {
        MarkDead();
        return;
    }

    if (m_targetPlant && (!m_targetPlant->IsAlive())) {
        m_targetPlant = nullptr;
        PlayAnimation(AnimID::WALK);
    }

    if (m_targetPlant) {
        m_targetPlant->TakeDamage(m_damage);
        if (!m_targetPlant || !m_targetPlant->IsAlive()) {
            m_targetPlant = nullptr;
            PlayAnimation(AnimID::WALK);
        }
        return;
    }

    const int speed = GetCurrentSpeed();
    if (speed > 0) {
        MoveTo(GetX() - speed, GetY());
    }

    if (GetX() < 0) {
        m_hasBreached = true;
    }
}

void Zombie::OnClick()
{
    // 僵尸默认不响应点击
}

void Zombie::TakeDamage(int damage)
{
    if (damage <= 0 || IsDead()) {
        return;
    }
    SetHP(GetHP() - damage);
    if (GetHP() <= 0) {
        MarkDead();
        m_targetPlant = nullptr;
    }
}

// 击退
void Zombie::KnockBack(int distance)
{
    MoveTo(GetX() + distance, GetY());
}

void Zombie::SetTargetPlant(std::shared_ptr<Plant> plant)
{
    m_targetPlant = plant;
    if (m_targetPlant) {
        PlayAnimation(AnimID::EAT);
    } else {
        PlayAnimation(AnimID::WALK);
    }
}
