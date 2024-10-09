#include "Pipe.hpp"


namespace Flappy
{
	Pipe::Pipe(GameDataRef data) : _data( data )
	{

	}

	Pipe::~Pipe()
	{

	}

	void Pipe::SpawnBottomPipe()
	{
		Sprite sprite( _data->assets.GetTexture("Pipe Up"));
		sprite.setPosition(
			this->_data->window.getSize().x,
			this->_data->window.getSize().y - sprite.getGlobalBounds().height);

		pipeSprites.push_back(sprite);
	}

	void Pipe::SpawnTopPipe()
	{
		Sprite sprite(_data->assets.GetTexture("Pipe Down"));
		sprite.setPosition(
			this->_data->window.getSize().x,
			0);

		pipeSprites.push_back(sprite);
	}

	void Pipe::SpawnInvisiblePipe()
	{
		Sprite sprite(_data->assets.GetTexture("Pipe Up"));
		sprite.setPosition(
			this->_data->window.getSize().x,
			this->_data->window.getSize().y - sprite.getGlobalBounds().height);

		sprite.setColor(Color(0,0,0,0));

		pipeSprites.push_back(sprite);
	}

	void Pipe::MovePipes(float dt)
	{
		for (unsigned short int i = 0; i < pipeSprites.size(); i++)
		{
			if (pipeSprites.at(i).getPosition().x < 0 - pipeSprites.at(i).getGlobalBounds().width)
			{
				pipeSprites.erase(pipeSprites.begin() + i);
			}
			else
			{
				float movement = PIPE_MOVEMENT_SPEED * dt;

				pipeSprites.at(i).move(-movement, 0);

			}
		}

		//cout << pipeSprites.size() << endl;
	}

	void Pipe::DrawPipes()
	{
		for (unsigned short int i = 0; i < pipeSprites.size(); i++)
		{
			_data->window.draw(pipeSprites.at(i));

		}
	}



}


