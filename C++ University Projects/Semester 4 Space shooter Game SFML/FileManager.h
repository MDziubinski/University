#pragma once
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Text.hpp>
#include <fstream>
#include <map>
#include <memory>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include "State.h"

namespace Engine
{
	class FileManager
	{
		std::ifstream infile;
		std::ofstream outfile;
	
		bool read; //Bool variable to check if file was already read

	public:
		FileManager();
		~FileManager();

		std::string Nick;
		int score;
		std::multimap<int, std::string, std::greater<int>> leaderboards;

		void Read_File(); //Function to read file
		void Sort_Results(); //Function to add score to the leaderboards
		void Write_File(); //Saving score to the file
	};
}

