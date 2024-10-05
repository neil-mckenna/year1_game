// Main.cpp
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Ship.hpp"
#include "Invader.hpp"
#include "Game.hpp"
#include "Player.hpp"
#include "Bullet.hpp"


using namespace std;
using namespace sf;


std::vector<Ship *> ships;
// 0 = 1 player
std::vector<Ship *> players (0);

static std::vector<Bullet*> bullets;
std::vector<Bullet*> bulletsToRemove;


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

	// create a player which inherits from Ship / Sprite
	Player* player = new Player();

	// adjust player position to center bottom
	player->setPosition(gameWidth * 0.5f, gameHeight - 50);

	// add back to vector list
	players.push_back(player);

	cout << "Ships Count : " << ships.size() << endl;
	cout << "Players Vector List : " << players.size() << endl;
	cout << "Player Pos : " << player->getPosition().x << " | " << player->getPosition().y << endl;

}

void Render(RenderWindow &window)
{
	// draw invaders ships
	for (const auto s : ships)
	{
		window.draw(*s);
	}

	// draw players
	for (const auto p : players)
	{
		window.draw(*p);
	}

	// draw bullets
	for (const auto b : bullets)
	{
		window.draw(*b);
	}


}

void Update(RenderWindow &window)
{
	// Reset clock, recalculate deltatime
	static Clock clock;
	float dt = clock.restart().asSeconds();
	static float timeSinceLastBullet = 0.0f;  // Timer for bullet firing
	const float bulletCooldown = 0.6f;         // 1 second cooldown

	// Increment the bullet timer
	timeSinceLastBullet += dt;

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

	// player shooting
	if (Keyboard::isKeyPressed(Keyboard::Space) && timeSinceLastBullet >= bulletCooldown)
	{
		cout << "Bullet Fired" << " Bullet Size " << bullets.size() << endl;
		if (players.size() > 0)
		{


			auto bullet = new Bullet(players[0]->getPosition(), false);
			bullet->Fire(players[0]->getPosition(), false);
			bullets.push_back(bullet);
		}

		timeSinceLastBullet = 0.0f;  // Reset the timer
	}

	// invaders
	for (auto &s : ships)
	{
		s->Update(dt);
	}

	// players
	for (auto &p : players)
	{
		p->Update(dt);
	}

	// bullets
	for (auto& b : bullets)
	{
		// Check if the bullet is off-screen
		if (b->getPosition().y < 0) {
			bulletsToRemove.push_back(std::move(b)); // Mark bullet for removal
		}

		b->Update(dt);
	}

	// Remove the marked bullets
	for (auto& b : bulletsToRemove) {
		bullets.erase(std::remove(bullets.begin(), bullets.end(), b), bullets.end());
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
