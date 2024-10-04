// Invader.cpp
#include <iostream>
#include "Invader.hpp"
#include "Ship.hpp"
#include "Game.hpp"

using namespace sf;
using namespace std;

bool Invader::direction;
bool movedDownThisCycle = false;
float Invader::speed = 35;


Invader::Invader() : Ship() {}

Invader::Invader(sf::IntRect ir, sf::Vector2f pos) : Ship(ir)
{
	setOrigin(Vector2f(16.f, 16.f));
	setPosition(pos);
}

void Invader::Update(const float& dt)
{
	//std::cout << "X: " << getPosition().x << " Y: " << getPosition().y << endl;
	Ship::Update(dt);

	move(Vector2f(dt * (direction ? 1.0f : -1.0f) * speed, 0.0f));

	if ((direction && getPosition().x > gameWidth - 16) || (!direction && getPosition().x < 16))
	{
		direction = !direction;

		if (!movedDownThisCycle)
		{
			float invaderRowHeight = 24.0f;

			for (int i = 0; i < ships.size(); ++i)
			{
				ships[i]->move(Vector2(0.0f, invaderRowHeight));

			}

			movedDownThisCycle = true;

		}
	}
	else
	{
		movedDownThisCycle = false;
	}


}