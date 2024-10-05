// bullet.hpp
#pragma once
#include<SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class Bullet : public Sprite
{
public:

	void Update(const float& dt);
	Bullet(const sf::Vector2f& pos, const bool mode);
	void Fire(const sf::Vector2f& pos, const bool mode);
	~Bullet() = default;

protected:
	Bullet();

	// false = player bullet, true = Enemy bullet
	bool _mode;
};
