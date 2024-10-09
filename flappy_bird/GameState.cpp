#include <sstream>
#include "GameState.hpp"
#include "GameOverState.hpp"
#include "DEFINTIONS.hpp"
#include <iostream>

using namespace sf;
using namespace std;

namespace Flappy
{
	GameState::GameState(GameDataRef data) : _data(data)
	{
	}

	void GameState::Init()
	{
		// grab textures
		_data->assets.LoadTexture("Game Background", GAME_BACKGROUND_FILEPATH);


		// assign to variables
		_background.setTexture(this->_data->assets.GetTexture("Game Background"));

		cout << "Game Initilaised" << endl;


	}

	void GameState::HandleInput()
	{
		Event event;
		while (_data->window.pollEvent(event))
		{
			if (Event::Closed == event.type)
			{
				_data->window.close();
			}

			if (_data->input.IsSpriteClicked(_background, Mouse::Left, _data->window))
			{
				cout << "Go to Game Over screen." << endl;

				// test to click to game over screen
				_data->machine.AddState(StateRef(new GameOverState(_data)), true);
			}


		}
	}

	void GameState::Update(float dt)
	{
	}

	void GameState::Draw(float dt)
	{
		_data->window.clear();

		_data->window.draw(_background);


		_data->window.display();
	}



}


