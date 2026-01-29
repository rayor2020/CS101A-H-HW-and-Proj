#ifndef PVZ_PLANTS_HPP
#define PVZ_PLANTS_HPP

#include "pvz/otherobjectshpp/Plant.hpp"
#include <memory>

class GameWorld;

class Sunflower : public Plant
{
public:
    Sunflower(int x, int y, std::shared_ptr<GameWorld> world);

    void Update() override;
    void OnClick() override;

private:
    int m_sunGenerateCD;
};

class PeaShooter : public Plant
{
public:
    PeaShooter(int x, int y, std::shared_ptr<GameWorld> world);

    void Update() override;
    void OnClick() override;

private:
    int m_shootCD;
};

class Wallnut : public Plant
{
public:
    Wallnut(int x, int y, std::shared_ptr<GameWorld> world);

    void Update() override;
    void OnClick() override;

private:
    int m_maxHP;
    bool m_isCracked;
};

class CherryBomb : public Plant
{
public:
    CherryBomb(int x, int y, std::shared_ptr<GameWorld> world);

    void Update() override;
    void OnClick() override;

private:
    int m_explosionCD;
};

class Repeater : public Plant
{
public:
    Repeater(int x, int y, std::shared_ptr<GameWorld> world);

    void Update() override;
    void OnClick() override;

private:
    int m_shootCD;
    int m_secondShotCD;
};

#endif // PVZ_PLANTS_HPP
