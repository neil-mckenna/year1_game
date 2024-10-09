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
		cout << "Game Initilaised" << endl;

		// grab textures
		_data->assets.LoadTexture("Game Background", GAME_BACKGROUND_FILEPATH);
		_data->assets.LoadTexture("Pipe Up", PIPE_UP_FILEPATH);
		_data->assets.LoadTexture("Pipe Down", PIPE_DOWN_FILEPATH);
		_data->assets.LoadTexture("Land", LAND_FILEPATH);

		_data->assets.LoadTexture("Bird Frame 1", BIRD_FRAME_1_FILEPATH);
		_data->assets.LoadTexture("Bird Frame 2", BIRD_FRAME_2_FILEPATH);
		_data->assets.LoadTexture("Bird Frame 3", BIRD_FRAME_3_FILEPATH);
		_data->assets.LoadTexture("Bird Frame 4", BIRD_FRAME_4_FILEPATH);

		pipe = new Pipe( _data );
		land = new Land( _data );
		bird = new Bird( _data );

		// assign to variables
		_background.setTexture(this->_data->assets.GetTexture("Game Background"));


	}

	void GameState::HandleInput()
	{
		sf::View view = this->_data->window.getDefaultView();

		Event event;
		while (_data->window.pollEvent(event))
		{
			if (Event::Closed == event.type)
			{
				_data->window.close();
			}

			/*if (_data->input.IsSpriteClicked(_background, Mouse::Left, _data->window))
			{
				cout << "Go to Game Over screen." << endl;

				// test to click to game over screen
				_data->machine.AddState(StateRef(new GameOverState(_data)), true);
			}*/


			//
			if (_data->input.IsSpriteClicked(_background, Mouse::Left, _data->window))
			{
				bird->Tap();
			}

			if (event.type == sf::Event::Resized) {
				// resize my view
				view.setSize({
						static_cast<float>(event.size.width),
						static_cast<float>(event.size.height)
					});
				this->_data->window.setView(view);
				// and align shape
			}


		}
	}

	void GameState::Update(float dt)
	{
		pipe->MovePipes(dt);
		land->MoveLand(dt);

		if (clock.getElapsedTime().asSeconds() > PIPE_SPAWN_FREQUENCY)
		{
			pipe->RandomizePipeOffset();

			pipe->SpawnTopPipe();
			pipe->SpawnBottomPipe();
			pipe->SpawnInvisiblePipe();

			clock.restart();

		}

		bird->Animate(dt);
		bird->Update(dt);

	}

	void GameState::Draw(float dt)
	{
		_data->window.clear();

		_data->window.draw(_background);

		pipe->DrawPipes();
		land->DrawLand();
		bird->Draw();


		_data->window.display();
	}



}


