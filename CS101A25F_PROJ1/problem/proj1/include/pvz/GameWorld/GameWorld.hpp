#ifndef GAMEWORLD_HPP__
#define GAMEWORLD_HPP__

#include <memory>

#include "pvz/Framework/WorldBase.hpp"
#include "pvz/GameObject/GameObject.hpp"
#include "pvz/Containers/LinkedList.hpp"
#include "pvz/Framework/TextBase.hpp"
#include "pvz/utils.hpp"

using pGameWorld = std::shared_ptr<GameWorld>;
using pGameObject = std::shared_ptr<GameObject>;

class GameObject;

// 前向声明
class Seed;
class Plant;
class Shovel;

class GameWorld : public WorldBase, public std::enable_shared_from_this<GameWorld>
{
public:
  GameWorld() = default;
  ~GameWorld() = default;

  void Init() override;
  LevelStatus Update() override;
  void CleanUp() override;

  // 对象管理
  void Add(pGameObject obj) { mlist.push_back(obj); }
  void Remove(pGameObject obj) { mlist.remove(obj); }

  // 阳光管理
  int GetSunCount() const { return m_SunCount; }
  void ChangeSun(int delta) { m_SunCount += delta; }

  // 波数管理
  int GetWaveCount() const { return m_WaveCount; }
  void ChangeWave(int delta = 1) { m_WaveCount += delta; }

  // 僵尸生成管理
  int GetNextZombieTick() const { return m_nextZombieTick; }
  void ChangeNextZombieTick(int delta = 1) { m_nextZombieTick -= delta; }

  // 阳光生成管理
  int GetSunDropCD() const { return m_SunDropCD; }
  void ChangeSunDropCD() { m_SunDropCD -= 300; }

  void GenerateSun();

  // 网格查询
  std::shared_ptr<Plant> GetPlantAt(int x, int y) const;
  bool HasPlantAt(int x, int y) const;
  bool HasZombieAhead(int laneY, int fromX) const;
  void HideUiText();

  // 种子系统接口
  bool IsHoldingSeed() const { return m_holdingSeed != nullptr; }
  bool IsHoldingShovel() const { return m_holdingShovel; }
  Seed *GetHoldingSeed() const { return m_holdingSeed; }
  void SetHoldingSeed(Seed *seed) { m_holdingSeed = seed; }
  void ClearHoldingSeed() { m_holdingSeed = nullptr; }

  // 铲子系统接口
  void ToggleShovel() { m_holdingShovel = !m_holdingShovel; }
  void ReleaseShovel() { m_holdingShovel = false; }

  // 冷却遮盖物生成
  void GenerateCooldownMask(int x, int y, Seed *seed = nullptr);

  // 获取容器（仅供内部使用）
  const pvz::LinkedList<std::shared_ptr<GameObject>> &GetObjects() const { return mlist; }

private:
  void UpdateAllObjects();
  void SpawnSunIfNeeded();
  void SpawnZombiesIfNeeded();
  void ResolveProjectileZombieCollisions();
  void ResolveZombiePlantCollisions();
  void RemoveDeadObjects();
  bool HasZombieBreached();
  void UpdateUiText();
  void ScheduleNextSkySun();
  void ScheduleNextZombieWave();

  pvz::LinkedList<std::shared_ptr<GameObject>> mlist;
  int m_SunCount = 50;
  int m_WaveCount = 0;
  int m_nextZombieTick = 0;
  int m_SunDropCD = 0;

  // 种子和铲子状态
  Seed *m_holdingSeed = nullptr; // 当前选中的种子
  bool m_holdingShovel = false;  // 是否拿着铲子

  std::shared_ptr<class TextBase> m_sunText;
  std::shared_ptr<class TextBase> m_waveText;
};

#endif // !GAMEWORLD_HPP__
