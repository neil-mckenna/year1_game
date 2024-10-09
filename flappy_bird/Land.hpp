#pragma once

#include <SFML/Graphics.hpp>
#include "DEFINTIONS.hpp"
#include "Game.hpp"
#include <vector>
#include <iostream>

using namespace sf;
using namespace std;


namespace Flappy
{

	class Land
	{
	public:
		Land(GameDataRef data);
		~Land();

		void MoveLand(float dt);
		void DrawLand();

		const vector<Sprite>& GetSprites() const;

	private:
		GameDataRef _data;

		vector<Sprite> _landSprites;

	};



}

