#include "pvz/otherobjectshpp/Sun.hpp"
#include "pvz/GameWorld/GameWorld.hpp"
#include "pvz/utils.hpp"

namespace {
constexpr int kSkySunLifetime = 600;
constexpr int kPlantSunLifetime = 600;
constexpr int kPlantSunDuration = 12;
constexpr int kPlantSunInitialVelocity = 4;
}

Sun::Sun(int x, int y, bool isDropping, std::shared_ptr<GameWorld> world)
    : GameObject(ImageID::SUN, x, y, LayerID::SUN, 80, 80, AnimID::IDLE, 1)
    , m_isFromPlant(!isDropping)
    , m_isDropping(isDropping)
    , m_isGrounded(false)
    , m_groundY(isDropping ? randInt(FIRST_ROW_CENTER, FIRST_ROW_CENTER + (GAME_ROWS - 1) * LAWN_GRID_HEIGHT) : y - 50)
    , m_groundLifetime(isDropping ? kSkySunLifetime : kPlantSunLifetime)
    , m_parabolaTimer(isDropping ? 0 : kPlantSunDuration)
    , m_verticalVelocity(isDropping ? 0 : kPlantSunInitialVelocity)
    , m_world(world)
{
}

void Sun::Update()
{
    if (m_isDropping) {
        int newY = GetY() - 2;
        if (newY <= m_groundY) {
            MoveTo(GetX(), m_groundY);
            m_isDropping = false;
            m_isGrounded = true;
            m_groundLifetime = kSkySunLifetime;
        } else {
            MoveTo(GetX(), newY);
        }
        return;
    }

    if (m_isFromPlant && !m_isGrounded) {
        MoveTo(GetX() - 1, GetY() + m_verticalVelocity);
        --m_verticalVelocity;
        if (--m_parabolaTimer <= 0) {
            MoveTo(GetX(), m_groundY);
            m_isGrounded = true;
            m_groundLifetime = kPlantSunLifetime;
        }
        return;
    }

    if (m_isGrounded) {
        if (--m_groundLifetime <= 0) {
            MarkDead();
        }
    }
}

void Sun::OnClick()
{
    auto world = m_world.lock();
    if (world) {
        world->ChangeSun(25); // 点击阳光获得25点阳光
        MarkDead(); // 阳光消失
    }
}
