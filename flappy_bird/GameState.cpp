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

		_data->assets.LoadTexture("Scoring Pipe", SCORING_PIPE_FILEPATH);

		_data->assets.LoadTexture("Bird Frame 1", BIRD_FRAME_1_FILEPATH);
		_data->assets.LoadTexture("Bird Frame 2", BIRD_FRAME_2_FILEPATH);
		_data->assets.LoadTexture("Bird Frame 3", BIRD_FRAME_3_FILEPATH);
		_data->assets.LoadTexture("Bird Frame 4", BIRD_FRAME_4_FILEPATH);

		pipe = new Pipe( _data );
		land = new Land( _data );
		bird = new Bird( _data );

		// flash
		flash = new Flash(_data);

		// assign to variables
		_background.setTexture(this->_data->assets.GetTexture("Game Background"));

		_score = 0;

		_gameState = GameStates::eReady;


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
				if (GameStates::eGameOver != _gameState)
				{
					_gameState = GameStates::ePlaying;
					bird->Tap();

				}

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
		if (GameStates::eGameOver != _gameState)
		{
			bird->Animate(dt);
			land->MoveLand(dt);

		}

		if (GameStates::ePlaying == _gameState)
		{
			pipe->MovePipes(dt);

			if (clock.getElapsedTime().asSeconds() > PIPE_SPAWN_FREQUENCY)
			{
				pipe->RandomizePipeOffset();

				pipe->SpawnTopPipe();
				pipe->SpawnBottomPipe();
				pipe->SpawnInvisiblePipe();
				pipe->SpawnScoringPipe();

				clock.restart();

			}

			bird->Update(dt);

			// collision with ground
			vector<Sprite> landSprites = land->GetSprites();
			for (int i = 0; i < landSprites.size(); i++)
			{
				if (collision.CheckSpriteCollision(
					bird->GetSprite(),
					0.75f,
					landSprites.at(i),
					1.0f
					))
				{
					_gameState = GameStates::eGameOver;

				}
			}

			// collision with pipes
			vector<Sprite> pipeSprites = pipe->GetSprites();
			for (int i = 0; i < pipeSprites.size(); i++)
			{
				if (collision.CheckSpriteCollision(
					bird->GetSprite(),
					0.625f,
					pipeSprites.at(i),
					1.0f
					))
				{
					_gameState = GameStates::eGameOver;
				}
			}

			// collision with scoring pipes
			if (GameStates::ePlaying == _gameState)
			{
				vector<Sprite> scoringSprites = pipe->GetScoringSprites();
				for (int i = 0; i < scoringSprites.size(); i++)
				{
					if (collision.CheckSpriteCollision(
						bird->GetSprite(),
						0.625f,
						scoringSprites.at(i),
						1.0f
					))
					{
						_score++;

						//cout << "Score is : " << _score << endl;

						scoringSprites.erase(scoringSprites.begin() + i);
					}
				}

			}


		}

		if (GameStates::eGameOver == _gameState)
		{
			flash->Show(dt);
		}


	}

	void GameState::Draw(float dt)
	{
		_data->window.clear();

		_data->window.draw(_background);

		pipe->DrawPipes();
		land->DrawLand();
		bird->Draw();
		flash->Draw(dt);


		_data->window.display();
	}



}


