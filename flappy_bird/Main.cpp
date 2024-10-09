#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

constexpr auto SCREEN_WIDTH = 1024;;
constexpr auto SCREEN_HEIGHT = 1024;;


int main()
{
	RenderWindow window(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32), "Flappy Bird");

	while (window.isOpen())
	{
		Event event;

		while (window.pollEvent(event))
		{




		}

	}

	return 0;
}