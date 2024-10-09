#pragma once

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"
#include "Pipe.hpp"
#include "Land.hpp"
#include "Bird.hpp"
#include <iostream>

using namespace sf;
using namespace std;

namespace Flappy
{
	class GameState : public State
	{
	public:
		GameState(GameDataRef data);

		void Init();

		void HandleInput();
		void Update(float dt);
		void Draw(float dt);

	private:
		GameDataRef _data;

		Sprite _background;

		Pipe *pipe;
		Land* land;
		Bird* bird;

		Clock clock;





	};


}
