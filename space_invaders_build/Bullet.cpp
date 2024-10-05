// bullet.cpp
#include "Bullet.hpp"
#include "Game.hpp"

using namespace sf;
using namespace std;

Bullet::Bullet() : Sprite()
{

}

Bullet::Bullet(const sf::Vector2f& pos, const bool mode)
{

}

void Bullet::Update(const float &dt)
{
	// shoot up or down
	move(Vector2f(0, dt * 200.0f * (_mode ? 1.0 : -1.0f)));

}