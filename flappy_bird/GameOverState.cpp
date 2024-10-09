#include <sstream>
#include "DEFINTIONS.hpp"
#include <iostream>
#include "GameOverState.hpp"

using namespace sf;
using namespace std;

namespace Flappy
{
	GameOverState::GameOverState(GameDataRef data) : _data(data)
	{
	}

	void GameOverState::Init()
	{
		// grab textures
		_data->assets.LoadTexture("Game Over Background", GAME_OVER_BACKGROUND_FILEPATH);


		// assign to variables
		_background.setTexture(this->_data->assets.GetTexture("Game Over Background"));

		cout << "Game Over Initilaised" << endl;


	}

	void GameOverState::HandleInput()
	{
		Event event;
		while (_data->window.pollEvent(event))
		{
			if (Event::Closed == event.type)
			{
				_data->window.close();
			}

			/*if (_data->input.IsSpriteClicked(_playButton, Mouse::Left, _data->window))
			{
				cout << "Go to game screen." << endl;

			}*/


		}
	}

	void GameOverState::Update(float dt)
	{
	}

	void GameOverState::Draw(float dt)
	{
		_data->window.clear();

		_data->window.draw(_background);


		_data->window.display();
	}



}