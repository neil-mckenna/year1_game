// player.cpp
#include "Player.hpp"
#include "Game.hpp"
#include "Bullet.hpp"
#include <iostream>

using namespace sf;
using namespace std;

float moveSpeed = 25.0f;


// create the player sprite from the hard coded spritesheet
Player::Player() : Ship(IntRect(Vector2(160, 32), Vector2(32, 32)))
{
	// put the sprite in the middle botton of the screen
	setPosition({ gameWidth * .5f, gameHeight - 32.f });
	cout << "Player Pos X: " << getPosition().x << " | " << getPosition().y << endl;
	setColor(Color::White);

}

void Player::Update(const float& dt)
{
	Ship::Update(dt);

	// move the player to the left
	if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A))
	{
		if(getPosition().x > 0)
		{
			move(-10 * dt * moveSpeed, 0);

		}
	}

	// move the player to the right
	if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D))
	{
		if (getPosition().x < gameWidth - 32)
		{
			move(10 * dt * moveSpeed, 0);
		}
	}



}

