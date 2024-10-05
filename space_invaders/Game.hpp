// Game.hpp
#pragma once
#include <SFML/Graphics.hpp>
#include "Ship.hpp"
#include "Bullet.hpp"

constexpr uint16_t gameWidth = 800;
constexpr uint16_t gameHeight = 600;
constexpr uint16_t invader_rows = 5;
constexpr uint16_t invader_columns = 12;

extern sf::Texture spritesheet;
extern std::vector<Ship *> ships;
extern std::vector<Ship *> players;
extern std::vector<Bullet *> bullets;




