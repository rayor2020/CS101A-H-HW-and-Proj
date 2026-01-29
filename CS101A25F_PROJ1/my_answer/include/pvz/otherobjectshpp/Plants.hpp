#ifndef PVZ_PLANTS_HPP
#define PVZ_PLANTS_HPP

#include "pvz/otherobjectshpp/Plant.hpp"
#include <memory>

class GameWorld;

class Sunflower : public Plant {
public:
    Sunflower(int x, int y, std::shared_ptr<GameWorld> world);

    void Update() override;
    void OnClick() override;

private:
    int m_sunGenerateCD;
};

class Peashooter : public Plant {
public:
    Peashooter(int x, int y, std::shared_ptr<GameWorld> world);

    void Update() override;
    void OnClick() override;

private:
    int m_shootCD;
};

class Wallnut : public Plant {
public:
    Wallnut(int x, int y, std::shared_ptr<GameWorld> world);

    void Update() override;
    void OnClick() override;

private:
    bool m_isCracked;
};

class CherryBomb : public Plant {
public:
    CherryBomb(int x, int y, std::shared_ptr<GameWorld> world);

    void Update() override;
    void OnClick() override;

private:
    int m_explosionCD;
};

class Repeater : public Plant {
public:
    Repeater(int x, int y, std::shared_ptr<GameWorld> world);

    void Update() override;
    void OnClick() override;

private:
    int m_shootCD;
    int m_secondShotCD;
};

class RedRepeater : public Plant {
public:
    RedRepeater(int x, int y, std::shared_ptr<GameWorld> world);

    void Update() override;
    void OnClick() override;

private:
    int m_shootCD;
    int m_secondShotCD;
};

#endif // PVZ_PLANTS_HPP
