// player.cpp
#include "Player.hpp"
#include "Game.hpp"

using namespace sf;
using namespace std;

// create the player sprite from the hard coded spritesheet
Player::Player() : Ship(IntRect(Vector2(160, 32), Vector2(32, 32)))
{
	// put the sprite in the middle botton of the screen
	setPosition({ gameWidth * .5f, gameHeight - 32.f });
}

void Player::Update(const float& dt)
{
	Ship::Update(dt);

	if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		move(-5, 0);
	}

	if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		move(5, 0);
	}

}

