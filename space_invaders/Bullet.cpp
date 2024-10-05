// bullet.cpp
#include "Bullet.hpp"
#include "Game.hpp"
#include <iostream>

using namespace sf;
using namespace std;

bool _mode = false;

Texture texture;

Bullet::Bullet()
{
	_mode = false;
}

Bullet::Bullet(const sf::Vector2f &pos, const bool mode) : _mode(mode)
{
	sf::IntRect spriteRect(0, 0, 32, 32);

	if (!mode)
	{
		spriteRect = IntRect(32, 32, 32, 32);
	}
	else
	{
		spriteRect = IntRect(64, 32, 32, 32);
	}


	if (!texture.loadFromFile("../res/img/invaders_sheet.png", spriteRect))
	{
		cerr << "Failed to load texture for Bullet in Bullet.cpp" << endl;
	}

	setTexture(texture);
	setPosition(pos.x, pos.y + -5.0f);

}


void Bullet::Update(const float &dt)
{
	// shoot up or down
	move(Vector2f(0, dt * 200.0f * (_mode ? 1.0 : -1.0f)));

}

void Bullet::Fire(const sf::Vector2f& pos, const bool mode)
{
	cout << "Mode" << mode << " POS " << pos.x << "|" << pos.y << endl;

	Bullet::Bullet(pos, mode);

}