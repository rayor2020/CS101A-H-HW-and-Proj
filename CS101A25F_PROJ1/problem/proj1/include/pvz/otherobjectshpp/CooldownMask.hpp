#pragma once

#include "pvz/GameObject/GameObject.hpp"
#include <memory>

class Seed;

/**
 * @class CooldownMask
 * @brief 冷却遮盖物，显示在种子上表示冷却中
 *
 * 当种子正在冷却时，会在其上方显示这个遮盖物。
 * 当关联的种子冷却完成时，遮盖物应该被删除。
 */
class CooldownMask : public GameObject
{
public:
    CooldownMask(int x, int y, std::shared_ptr<Seed> relatedSeed);
    ~CooldownMask() = default;

    void Update() override;
    void OnClick() override;
    bool isPlant() const override { return false; }
    bool isZombie() const override { return false; }
    bool isProjectile() const override { return false; }
    bool isSeed() const override { return false; }

private:
    std::shared_ptr<Seed> m_relatedSeed;

    // 禁止复制
    CooldownMask(const CooldownMask &) = delete;
    CooldownMask &operator=(const CooldownMask &) = delete;
};
