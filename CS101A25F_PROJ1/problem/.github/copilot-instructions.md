# PvZ Game Framework - AI Coding Agent Guide

## 项目概览

这是一个**植物大战僵尸**克隆游戏的 C++ OpenGL 实现项目。游戏使用基于 ticks（刻）的帧循环架构，提供了完整的渲染、动画和交互框架，开发者需要实现游戏逻辑。

**核心技术栈**: C++17 + CMake + OpenGL + FreeGLUT + SOIL

## 架构与关键概念

### 1. 分层对象系统（Object Hierarchy）

```
ObjectBase (Framework layer)
  ↓ (game logic layer)
GameObject (base for all game objects)
  ├── Background
  ├── PlantingSpot (invisible "rabbit")
  ├── Plant (base)
  │   ├── Sunflower
  │   ├── PeaShooter
  │   └── ...
  ├── Zombie (base)
  │   ├── RegularZombie
  │   ├── BucketHeadZombie
  │   └── ...
  └── Projectile
      ├── Pea
      └── ...
```

**关键原则**:

- `ObjectBase`（in `Framework/ObjectBase.hpp`）包装底层渲染和碰撞检测，**不可修改**
- `GameObject`是所有游戏对象的基类，实现多态虚函数：`isPlant()`, `isZombie()`, `isProjectile()`, `isSeed()`
- **不要使用类型转换**识别对象类型，**必须用虚函数**（如示例中的 `IsBeverage()` 而非 `IsCocaCola()`）

### 2. 游戏循环（Game Loop Tick-Based）

每帧执行顺序（由 GameManager 驱动，频率 ~30 FPS）：

1. **GameWorld::Update()** → 调用所有 GameObject 的 `Update()`
2. **检测失败条件** → 僵尸到达屏幕左边则失败
3. **生成新对象** → 阳光、僵尸、投射物
4. **清理死对象** → 标记为死亡的对象从容器移除
5. **渲染** → GameManager 调用 `DisplayAllObjects()`，按 layer 从高到低绘制

### 3. GameWorld 的容器管理职责

```cpp
// GameWorld maintains object container
std::list<std::shared_ptr<GameObject>> mlist;

// Lifecycle methods (called by GameManager, NOT directly)
virtual void Init() override;     // Level initialization
virtual LevelStatus Update() override; // Per-tick update
virtual void CleanUp() override;  // Clean up for next round
```

**关键设计**:

- GameWorld 是**唯一的对象生命周期管理者**
- GameObject 不能直接新增/删除对象，必须通过 `shared_from_this()` 通知 GameWorld
- 使用 `std::list` 支持迭代过程中的安全移除

### 4. 隐形的兔子（Invisible Objects Pattern）

PlantingSpot 是看不见的占位符（`ImageID::NONE`），代表可种植区域：

- 玩家点击空地时实际点击的是 PlantingSpot 对象
- PlantingSpot 的 `OnClick()` 通知 GameWorld 创建植物
- **模式**：复杂功能不一定需要可见表现

## 关键文件与模式

### 文件结构

```
proj1/
├── src/
│   ├── main.cpp                 # 入口，创建 GameWorld 并启动
│   ├── Framework/               # 游戏框架（勿修改核心）
│   │   ├── ObjectBase.cpp/.hpp
│   │   ├── GameManager.cpp/.hpp (渲染循环管理)
│   │   ├── SpriteManager.cpp/.hpp (sprite sheet动画)
│   │   ├── TextBase.cpp/.hpp    (UI文字)
│   │   └── WorldBase.hpp        (抽象基类)
│   ├── GameObject/              # 游戏对象实现（主要编辑区域）
│   │   ├── GameObject.cpp/.hpp  (基类 + Background/PlantingSpot)
│   │   └── otherobjectscpp/     (具体游戏对象)
│   └── GameWorld/
│       ├── GameWorld.cpp/.hpp   (核心管理类)
│       └── CMakeLists.txt
├── include/pvz/
│   ├── utils.hpp                # 全局常量、枚举、工具函数
│   │   └── ImageID, AnimID, LayerID, randInt()
│   ├── Containers/              # 自定义容器实现（数据结构作业）
│   └── [Framework/GameObject/GameWorld/].hpp (头文件镜像)
├── assets/                      # 图片、动画资源
├── third_party/                 # FreeGLUT, SOIL 库
└── build/                       # CMake 输出目录
```

### 编译与构建

```powershell
# Windows (使用 Visual Studio)
cd proj1
mkdir build; cd build
cmake .. -G "Visual Studio 16 2019"  # 或 2022
cmake --build . --config Debug
.\bin\Debug\PvZ.exe

# macOS/Linux
cd proj1
mkdir build; cd build
cmake .. && make -j
./bin/PvZ
```

**CMake 模式**：

- 主 `CMakeLists.txt` 定义 Framework/GameObject/GameWorld 子库
- 各子目录有独立 `CMakeLists.txt`：`add_library(...) STATIC` → 编译为静态库
- 依赖关系：Framework ← GameObject ← GameWorld ← main
- **新增模块必须**：(1) 创建子目录 (2) 加 `CMakeLists.txt` (3) 在主 CMakeLists.txt 加 `add_subdirectory()`

### 关键 API

#### ObjectBase 属性（不要重复存储）

```cpp
int GetX() const;
int GetY() const;
void MoveTo(int x, int y);
int GetWidth() const;
int GetHeight() const;
void SetWidth/Height(int);
AnimID GetCurrentAnimation() const;
void PlayAnimation(AnimID animID);  // 从第一帧播放
void ChangeImage(ImageID imageID);  // 仅坚果墙/铁桶僵尸用
```

#### GameObject 虚函数（所有子类必实现）

```cpp
virtual void Update() override;   // 每刻调用
virtual void OnClick() override;  // 被点击时调用
virtual bool isPlant() const = 0;
virtual bool isZombie() const = 0;
virtual bool isProjectile() const = 0;
virtual bool isSeed() const = 0;
```

#### GameWorld 管理接口

```cpp
void Add(pGameObject obj);              // 添加对象
void Remove(pGameObject obj);           // 移除对象
int GetSunCount() const;
void ChangeSun(int delta);              // 修改阳光数
void GenerateSun();                     // 生成掉落阳光
int GetNextZombieTick() const;
void ChangeNextZombieTick(int delta=1);
```

## 常见模式

### 对象间通信（推荐模式）

❌ **反面示例**：

```cpp
// GameObject 直接访问 GameWorld 容器
for (auto& obj : gameWorld->GetAllObjects()) { ... }
```

✅ **正面示例**：

```cpp
// 植物/僵尸通过 shared_from_this() 调用 GameWorld 提供的方法
class PeaShooter : public Plant {
    void Update() override {
        if (shouldShoot) {
            auto pea = std::make_shared<Pea>(...);
            auto world = m_world.lock();  // weak_ptr 安全获取
            world->Add(pea);
        }
    }
};
```

### 数据结构选择

**使用自定义容器替代 STL**（作业要求）：

- **Background/PlantingSpot 存储**: 可用数组（固定数量）
- **GameObject 容器**: 优先用**双向链表**（支持遍历中删除）
- **优先级队列**（阳光倒计时）：可用二叉堆

### 对象死亡处理

```cpp
class GameObject : public ObjectBase {
protected:
    bool m_isDead = false;
public:
    void MarkDead() { m_isDead = true; }
    bool IsDead() const { return m_isDead; }
};

// 在 GameWorld::Update()
void GameWorld::Update() {
    // ... 更新所有对象 ...

    // 清理死对象
    mlist.remove_if([](const auto& obj) {
        return obj->IsDead();
    });
}
```

## 项目特定约定

### 1. 坐标系

- **原点**: 屏幕左下角 (0, 0)
- **正方向**: X 向右，Y 向上
- **草坪网格**: 9 列 × 5 行，每格 80×100 像素

### 2. 图层系统（LayerID）

```cpp
enum class LayerID {
    SUN = 0,           // 最前面（先绘制）
    ZOMBIES,
    PROJECTILES,
    PLANTS,
    COOLDOWN_MASK,
    UI,
    BACKGROUND = 6,    // 最后面
};
```

### 3. 资源路径

```cpp
// utils.hpp 中定义的 ASSET_DIR（平台相关）
#ifdef __APPLE__
static const std::string ASSET_DIR = "../../assets/";
#else
static const std::string ASSET_DIR = "../assets/";  // Windows/Linux
#endif
```

### 4. 随机数工具

```cpp
int random = randInt(min, max);  // [min, max] 闭区间均匀分布
```

## 常见调试陷阱

| 问题         | 原因                                      | 解决方案                          |
| ------------ | ----------------------------------------- | --------------------------------- |
| 对象不显示   | 未加入 GameWorld 容器                     | 用 `Add()` 添加，确保不是临时变量 |
| 点击无响应   | OnClick() 为空或碰撞盒设置错误            | 检查 width/height，碰撞检测为圆形 |
| 对象跳帧消失 | 对象被删除但仍被引用                      | 检查是否有野指针或 double-free    |
| 动画不播放   | 未调用 `PlayAnimation()` 或 AnimID 不存在 | 检查 AnimID 枚举定义              |
| 链接错误     | CMakeLists.txt 依赖配置错误               | 检查 `target_link_libraries` 顺序 |
| 资源加载失败 | ASSET_DIR 路径错误（特别是 macOS）        | 检查相对路径或使用绝对路径        |

## 推荐实现流程

1. **Background** → 验证渲染管道
2. **PlantingSpot + Sunflower** → 理解对象系统和多态
3. **Sun（天降 & 植物生成）** → 掌握 GameWorld 消息机制
4. **Zombie + 碰撞检测** → 实现对象间交互
5. **Projectile（豌豆）+ 伤害系统** → 完成核心游戏逻辑
6. **其他植物/僵尸** → 复用模式扩展

## 性能考量

- **Update 每刻执行**：保持 O(n) 复杂度，n=对象数（通常 <100）
- **OnClick** 遍历图层从顶到底，命中首个碰撞体返回
- **动画帧计数**：由 ObjectBase 内部管理，不应手动修改
- **内存**: 所有 GameObject 用 `shared_ptr` 管理，引用计数自动清理

## 参考文档

- **项目说明**: `1-Project1-概览.md`（中文详细设计文档）
- **游戏参考**: `2-样例游戏参考.md`
- **常见问题**: `5-FAQ.md`
- **评分标准**: `4-grading.md`
