// Main.cpp
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Ship.hpp"
#include "Invader.hpp"


using namespace std;
using namespace sf;

const int gameWidth = 800;
const int gameHeight = 600;


std::vector<Ship *> ships;

sf::Texture spritesheet;
sf::Sprite invader;

void Load()
{
	if (!spritesheet.loadFromFile("../res/img/invaders_sheet.png"))
	{
		cerr << "Failed to load spritesheet" << endl;
	}

	//invader.setTexture(spritesheet);
	//invader.setTextureRect(IntRect(Vector2i(0, 0), Vector2i(32, 32)));

	Invader* inv1 = new Invader(sf::IntRect(Vector2(0, 0), Vector2(32, 32)), { 100, 100 });
	Invader* inv2 = new Invader(sf::IntRect(Vector2(0, 0), Vector2(32, 32)), { 200, 200 });


	ships.push_back(inv1);
	ships.push_back(inv2);


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
