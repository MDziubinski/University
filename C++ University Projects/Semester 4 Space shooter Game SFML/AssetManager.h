#pragma once
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Text.hpp>
#include <map>
#include <memory>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include "State.h"



namespace Engine
{
	class AssetManager
	{
		std::map<int, std::unique_ptr<sf::Texture>> s_textures;
		std::map<int, std::unique_ptr<sf::Font>> s_fonts;

	public:
		AssetManager();
		~AssetManager();

		void Add_Texture(const std::string& Ftext_path, int ID); //Adding texture
		void Add_Font(const std::string& Ffont_path, int ID); //Adding font

		const sf::Texture& Get_Texture(int ID) const; //Getting the textures
		const sf::Font& Get_Font(int ID) const; //Getting the fonts
		
	};
}