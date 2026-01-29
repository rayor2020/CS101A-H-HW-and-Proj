#include "pvz/otherobjectshpp/CooldownMask.hpp"
#include "pvz/otherobjectshpp/Seed.hpp"
#include "pvz/utils.hpp"

CooldownMask::CooldownMask(int x, int y, std::shared_ptr<Seed> relatedSeed)
    : GameObject(ImageID::COOLDOWN_MASK, x, y, LayerID::COOLDOWN_MASK, 50, 70, AnimID::NO_ANIMATION),
      m_relatedSeed(relatedSeed)
{
}

void CooldownMask::Update()
{
    // 如果关联的种子不再冷却，标记自己为死亡
    if (m_relatedSeed && !m_relatedSeed->IsInCooldown())
    {
        MarkDead();
    }
}

void CooldownMask::OnClick()
{
    // 冷却遮盖物不响应点击
}
