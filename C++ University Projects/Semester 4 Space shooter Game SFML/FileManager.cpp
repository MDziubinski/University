#include "FileManager.h"

Engine::FileManager::FileManager()
	:score(0), read(false)
{
}
Engine::FileManager::~FileManager()
{
}

void Engine::FileManager::Read_File()
{
	try
	{
		if (read == false)
		{
			infile.open("scores.txt");
			if (infile.is_open())
			{
				leaderboards.clear();
				while (infile >> score >> Nick)
				{
					leaderboards.insert(std::make_pair(score, Nick));
				}
				Nick.clear();
				score = 0;
				read = true;
			}
			else
			infile.close();
		}
	}
	catch (...)
	{
	}
}

void Engine::FileManager::Sort_Results()
{	
	if(score != 0 && !Nick.empty())
	leaderboards.insert(std::make_pair(score, Nick));
}

void Engine::FileManager::Write_File()
{
	try
	{	
		outfile.open("scores.txt", std::ios::trunc);
		if (outfile.is_open())
			{
				for (auto const& element : leaderboards)
				{
					outfile << element.first << ' ' << element.second;
					outfile << std::endl;
				}
			}
		read = false;
		infile.close();
	}
	catch (...)
	{
	}
}
