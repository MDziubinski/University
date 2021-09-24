#include "Functions.h"

struct AtExit
{
	~AtExit() { _CrtDumpMemoryLeaks(); }
} doAtExit;

int main(int argc, char* argv[])
{
	std::string input, output, argument;
	for (int i = 0; i < argc; i++)
	{
		argument = argv[i];
		if (argument == "-i")
		{
			input = argv[i + 1];
		}
		if (argument == "-d")
		{
			output = argv[i + 1];
		}
	}
	
	if (!input.empty() && !output.empty())
	{
		int number_of_clients = numberOfClients(input);
		if (numberOfClients > 0)
		{
			clock_t start_greedy, stop_greedy, star_brute, stop_brute;
			double time_greedy, time_brute;
			Clients* root = nullptr;
			fillStructs(root, number_of_clients);
			readFile(root, input);
			double total_greedy = 0;
			double total_brute = INFINITY;
			std::vector<int> greedy_path;
			std::vector<int> brute_path;
			start_greedy = clock();
			minimalRoute(root, greedy_path, 1, number_of_clients, total_greedy, 0);
			stop_greedy = clock();
			time_greedy = ((double)stop_greedy - (double)start_greedy) / CLOCKS_PER_SEC;
			star_brute = clock();
			if (number_of_clients < 13)
			{
				findPermut(root, brute_path, 1, number_of_clients, total_brute);
			}
			stop_brute = clock();
			time_brute = ((double)stop_brute - (double)star_brute) / CLOCKS_PER_SEC;
			std::ofstream(file); file.open(output);
			filePaths(file, greedy_path, total_greedy, time_greedy, brute_path, total_brute, time_brute, number_of_clients);
			file.close();
			removeClients(root);
		}
		else
			return -1;
	}
	else
		return -1;
	return 0;
}