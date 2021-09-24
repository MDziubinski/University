#include "AssetManager.h"

Engine::AssetManager::AssetManager()
{
}
Engine::AssetManager::~AssetManager()
{
}

void Engine::AssetManager::Add_Texture(const std::string& Ftext_path, int ID)
{
	auto texture = std::make_unique<sf::Texture>();
	if (texture->loadFromFile(Ftext_path))
	{
		s_textures[ID] = std::move(texture);
	}
}
void Engine::AssetManager::Add_Font(const std::string& Ffont_path, int ID)
{
	auto font = std::make_unique<sf::Font>();
	if (font->loadFromFile(Ffont_path))
	{
		s_fonts[ID] = std::move(font);
	}
}

const sf::Texture& Engine::AssetManager::Get_Texture(int ID) const
{
	return *(s_textures.at(ID).get());
}
const sf::Font& Engine::AssetManager::Get_Font(int ID) const
{
	return *(s_fonts.at(ID).get());
}