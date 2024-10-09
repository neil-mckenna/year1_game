#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.hpp"

using namespace sf;
using namespace std;

constexpr auto SCREEN_WIDTH = 1024;;
constexpr auto SCREEN_HEIGHT = 1024;;


int main()
{
	Flappy::Game(1024, 1024, "Flappy Bord");

	return EXIT_SUCCESS;
}