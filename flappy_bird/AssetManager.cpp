#include "AssetManager.hpp"

namespace Flappy
{
	void AssetManager::LoadTexture(std::string name, std::string fileName)
	{
		Texture tex;

		if (tex.loadFromFile(fileName))
		{
			this->_textures[name] = tex;
		}
	}

	void AssetManager::LoadFont(std::string name, std::string fileName)
	{
		Font font;

		if (font.loadFromFile(fileName))
		{
			this->_fonts[name] = font;
		}
	}

	Texture& AssetManager::GetTexture(std::string name)
	{
		return this->_textures.at(name);
	}

	Font &AssetManager::GetFont(std::string name)
	{
		return this->_fonts.at(name);
	}




}