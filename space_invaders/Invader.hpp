// Invader.hpp
#pragma once  // Ensure the header file is included only once in the build
#include <SFML/Graphics.hpp>  // Example of including SFML dependencies
#include "Ship.hpp"

class Invader : public Ship
{
public:
	static bool direction;
	static float speed;

	Invader(sf::IntRect ir, sf::Vector2f pos);
	Invader();
	void Update(const float& dt) override;

};