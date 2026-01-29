cmake_minimum_required(VERSION 3.16)

add_library(
  GameObject
  STATIC
  GameObject.cpp
  otherobjectscpp/Sun.cpp
  otherobjectscpp/Plant.cpp
  otherobjectscpp/Plants.cpp
  otherobjectscpp/Projectile.cpp
  otherobjectscpp/Pea.cpp
  otherobjectscpp/Explosion.cpp
  otherobjectscpp/Zombie.cpp
  otherobjectscpp/Zombies.cpp
  otherobjectscpp/Seed.cpp
  otherobjectscpp/Seeds.cpp
  otherobjectscpp/CooldownMask.cpp
  otherobjectscpp/Shovel.cpp
)

target_link_libraries(
  GameObject
  Framework
)
