#include "pvz/otherobjectshpp/Shovel.hpp"
#include "pvz/GameWorld/GameWorld.hpp"
#include "pvz/utils.hpp"
#include <memory>

// 添加静态变量用于跟踪当前的预览铲子
static std::shared_ptr<Shovel> s_previewShovel = nullptr;

// 添加静态变量存储鼠标位置（默认位置）
static int s_mouseX = 0;
static int s_mouseY = 0;

// 提供设置鼠标位置的公共方法（在其他地方调用）
void UpdateShovelMousePosition(int x, int y)
{
    s_mouseX = x;
    s_mouseY = y;

    // 更新预览铲子位置
    if (s_previewShovel) {
        s_previewShovel->MoveTo(s_mouseX, s_mouseY);
    }
}

// 提供清理预览铲子的公共方法
void ClearPreviewShovel()
{
    if (s_previewShovel) {
        s_previewShovel->MarkDead();
        s_previewShovel = nullptr;
    }
}

Shovel::Shovel(LayerID layer)
    : GameObject(ImageID::SHOVEL, 600, WINDOW_HEIGHT - 40, layer, 70, 70, AnimID::NO_ANIMATION)
{
}

void Shovel::Update()
{
    // 更新预览铲子位置（额外保障）
    if (s_previewShovel) {
        s_previewShovel->MoveTo(s_mouseX, s_mouseY);
    }
}

void Shovel::OnClick()
{
    auto world = m_world.lock();
    if (!world)
        return;

    // 如果玩家拿着种子，点击铲子无效
    if (world->IsHoldingSeed()) {
        return;
    }

    // 如果这是预览铲子，不响应点击事件
    if (GetHP() == -1) {
        return;
    }

    // 如果玩家已经拿着铲子，则放下铲子
    if (world->IsHoldingShovel()) {
        // 删除预览铲子
        ClearPreviewShovel();
        world->ReleaseShovel();
    }
    // 如果玩家没有拿着铲子，则拿起铲子
    else {
        // 设置玩家拿着铲子的状态
        world->ToggleShovel();

        // 创建预览铲子
        auto newPreviewShovel = std::make_shared<Shovel>(LayerID::PREVIEW);

        // 设置为预览状态（HP为-1表示特殊对象，不会被自动清理）
        newPreviewShovel->SetHP(-1);
        // 设置预览铲子的位置
        newPreviewShovel->MoveTo(s_mouseX, s_mouseY);
        s_previewShovel = newPreviewShovel;
        world->Add(s_previewShovel);
    }
}