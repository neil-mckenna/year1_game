// ship.hpp
#pragma once
#include <SFML/Graphics.hpp>

class Ship : public sf::Sprite
{
public:
	// A constructor that takes a sprite
	explicit Ship(sf::IntRect ir);

	// pure virtual void desconstructor -- makes this an abstract and avoid undefined behaviour
	virtual ~Ship() = 0;

	// Update, virtual so can be overridden, but not pure virtual
	virtual void Update(const float &dt);

protected:
	sf::IntRect _sprite;

	// Default constructor is hidden
	Ship();

};
