// player.hpp
#pragma once
#include <SFML/Graphics.hpp>
#include "Ship.hpp"

class Player : public Ship
{


public:
	Player();
	void Update(const float& dt);


};