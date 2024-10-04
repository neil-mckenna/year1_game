// Main.cpp
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Ship.hpp"
#include "Invader.hpp"
#include "Game.hpp"
#include "Player.hpp"


using namespace std;
using namespace sf;


std::vector<Ship *> ships;

sf::Texture spritesheet;
sf::Sprite invader;

void Load()
{
	if (!spritesheet.loadFromFile("../res/img/invaders_sheet.png"))
	{
		cerr << "Failed to load spritesheet" << endl;
	}


	//Invader* inv1 = new Invader(sf::IntRect(Vector2(0, 0), Vector2(32, 32)), { 100, 100 });
	//Invader* inv2 = new Invader(sf::IntRect(Vector2(0, 0), Vector2(32, 32)), { 200, 200 });

	//ships.push_back(inv1);
	//ships.push_back(inv2);

	// Spawning a wave of invaders
	for (int r = 0; r < invader_rows; ++r)
	{
		auto rect = IntRect(Vector2(32, 0), Vector2(32, 32));
		for (int c = 0; c < invader_columns; c++)
		{
			Vector2f position(32.0f * c, 32.0f * r);
			auto inv = new Invader(rect, position);

			ships.push_back(inv);
		}
	}

	Player* player = new Player();
	player->setColor(Color::Cyan);

	ships.push_back(player);

	cout << "Ships Count : " << ships.size() << endl;
	cout << "Player Pos : " << player->getPosition().x << " | " << player->getPosition().y << endl;
	cout << "Player Pos : " << ships[60]->getPosition().x << " | " << ships[60]->getPosition().y << endl;

}

void Render(RenderWindow &window)
{
	for (const auto s : ships)
	{
		window.draw(*s);
	}


}

void Update(RenderWindow &window)
{
	// Reset clock, recalculate deltatime
	static Clock clock;
	float dt = clock.restart().asSeconds();

	// check and consume events
	Event event;
	while (window.pollEvent(event))
	{
		if (event.type == Event::Closed)
		{
			window.close();
			return;
		}
	}

	// Quit Via ESC key
	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
		window.close();
	}

	for (auto& s : ships)
	{
		s->Update(dt);
	}


}

int main()
{
	RenderWindow window(VideoMode(gameWidth, gameHeight), "Space Invaders");

	Load();

	while (window.isOpen())
	{
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}

	return 0;


}
