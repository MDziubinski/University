#include "Functions.h"


int numberOfClients(std::string input)
{
	int counter = 0;
	char unused_chars, pointBreak;
	int client_one;
	int client_two;
	std::string direction;
	std::ifstream(file);
	double dist;
	
	file.open(input);

	if (file.good())
	{
		while (!file.eof())
		{
			file >> unused_chars >> client_one >> direction >> client_two >> unused_chars >> dist >> unused_chars >> pointBreak;

			if (direction != "->" && direction != "-")
			{
				std::cout << "No path!" << std::endl;
				return -1;
			}
			if (counter < std::max(client_one, client_two))
			{
				counter = std::max(client_one, client_two);
			}
			if (counter == 0)
			{
				std::cout << "No Clients!" << std::endl;
				return -1;
			}
		};
	}
	file.close();
	return counter;
}

void fillStructs(Clients*& root, int number)
{
	Clients* pNew=nullptr, * temp=nullptr;
	for (int i = 1; i <= number; i++)
	{
		if (root && temp)
		{
			pNew = new Clients{ i, 0, nullptr,nullptr };
			pNew->distances = fillDistances(pNew->distances, number);
			temp->next = pNew;
			temp = temp->next;
		}
		else
		{
			pNew = new Clients{ i,0,nullptr,nullptr };
			pNew->distances = fillDistances(pNew->distances, number);
			temp = pNew;
			root = pNew;
		}
	}
}

Distances* fillDistances(Distances*& root, int number)
{
	Distances* pNew = nullptr, * temp = nullptr, *first = nullptr;
	for (int i = 1; i <= number; i++)
	{
		if (temp)
		{
			pNew = new Distances{ i,0, nullptr};
			temp->next = pNew;
			temp = temp->next;
		}
		else
		{
			pNew = new Distances{ i,0, nullptr};
			temp = pNew;
			first = pNew;
		}

	}
	return first;
}

void removeClients(Clients*& root)
{
	if (root)
	{	
		
		removeClients(root->next);
		removeDistances(root->distances);
		delete root;
	}
}

void removeDistances(Distances*& root)
{
	auto temp = root;

	if (temp)
	{
		removeDistances(temp->next);
		delete root;
	}
}

void readFile(Clients*& root, std::string input)
{
	int counter = 0;
	char unused_chars, pointBreak;
	int client_one;
	int client_two;
	std::string direction;
	std::ifstream(file);
	double dist;

	file.open(input);
	while (!file.eof()) 
	{
		file >> unused_chars >> client_one >> direction >> client_two >> unused_chars >> dist >> unused_chars >> pointBreak;
		auto searched_client1 = ClientsSearch(root, client_one);
		auto searched_client2 = ClientsSearch(root, client_two);
		if (direction == "-")
		{
			addDistances(searched_client1->distances, client_two, dist);
			addDistances(searched_client2->distances, client_one, dist);
		}
		if (direction == "->")
		{
			addDistances(searched_client1->distances, client_two, dist);
			addDistances(searched_client2->distances, client_one, INFINITY);
		}
		if(direction !="-" && direction != "->")
		{
			return;
		}
	}
	file.close();
}

Clients* ClientsSearch(Clients*& root, int number)
{
	auto temp = root;
	if (temp)
	{
		while (temp)
		{
			if (temp->num_client == number) 
			{
				return temp;
			}
			else {
				temp = temp->next;
			}
		}

	}
	return nullptr;
}

void addDistances(Distances*& root, int number, double distance)
{
	auto temp = root;
	if (temp)
	{

			while (temp->num_client != number)
			{
				temp = temp->next;
			}
			temp->dist = distance;
	}
}


/*##################################################################################################################################
####################################################################################################################################
                                                    GREEDY ALGORITHM
####################################################################################################################################
####################################################################################################################################*/


void minimalRoute(Clients*& root, std::vector<int>& greedy_path, int num_client, int all_clients, double& total_distance, int count_covered)
{
	if (!root)
	{
		return;
	}
	Clients* temp = root;
	temp = ClientsSearch(root, num_client);
	temp->covered = true;
	greedy_path.push_back(num_client);
	//count_covered += 1;
	int nextClient = nearestNeighbour(root, num_client, total_distance);
	if (total_distance == 0)
	{
		return;
	}
	if (nextClient == INT_MAX)
	{
		if (count_covered < all_clients)
		{
			return;
		}
	}
	minimalRoute(root,greedy_path, nextClient, all_clients, total_distance, count_covered+1);
}

int nearestNeighbour(Clients*& root, int num_client, double& total_distance)
{
	if (root)
	{
		auto tmp = ClientsSearch(root, num_client);
		auto distance = tmp->distances;
		auto temp = root;
		int next_client = INT_MAX;
		double currentMIN = INFINITY;
		while (distance)
		{
			if (distance->dist != 0 && distance->dist != INFINITY)
			{
				if (currentMIN > distance->dist)
				{
					temp = ClientsSearch(root, distance->num_client);
						if (temp->covered == 0)
						{
							currentMIN = distance->dist;
							next_client = distance->num_client;
						}
				}
			}
			distance = distance->next;
		}
		if (currentMIN != INFINITY)
		{
			total_distance += currentMIN;
		}
		return next_client;
	}
	return 0;
}



/*##################################################################################################################################
####################################################################################################################################
                                                        BRUTE FORCE
####################################################################################################################################
####################################################################################################################################*/

void permutation(Clients*& root, std::vector<int>& arr, std::vector<int>& brute_path, int index, int num_elements, double& total_brute)
{
	if (index < num_elements - 1)
	{
		for (int i = index; i < num_elements; i++)
		{
			std::swap(arr[index], arr[i]);
			permutation(root, arr,brute_path, index + 1, num_elements, total_brute);
			std::swap(arr[index], arr[i]);
		}
	}
	else
		createPath(root,arr,brute_path,num_elements, total_brute);
	
}

void findPermut(Clients*& root, std::vector<int>& brute_path, int num_client, int all_clients, double& total_brute)
{
	std::vector<int>permutArray;
	int curr_clients = all_clients - 1;
	for (int i = 0; i < curr_clients; i++)
	{
		permutArray.push_back(i + 2);
	}
	for (int i = 0; i < all_clients; i++)
	{
		brute_path.push_back(1);
	}
	permutation(root, permutArray,brute_path, 0, curr_clients,total_brute);
}

void createPath(Clients*& root, std::vector<int>& arr, std::vector<int>& brute_path, int num_elements, double& total_brute)
{	
	
	std::vector<int> temp_min;
	std::vector<int> curr_path;
	for (int i = 0; i < num_elements; i++)
	{
		temp_min.push_back(i);
		curr_path.push_back(arr[i]);
	}
	double total_dist = 0;
	int counter = 0;
	checkPath(root, 1, curr_path, temp_min, 0, num_elements, total_dist, counter);
	if (counter == num_elements)
	{
		if (total_brute > total_dist)
		{
			brute_path[0] = 1;
			for (int i = 0; i < num_elements; i++)
			{
				brute_path[i + 1] = temp_min[i];
			}
			total_brute = total_dist;
		}
	}
}


void checkPath(Clients*& root,int num_client, std::vector<int>& curr_path, std::vector<int>& temp_min, int index, int all_clients,double& total_distance, int& counter)
{
	if (root)
	{
		auto temp = ClientsSearch(root,num_client);
		auto distances = temp->distances;
		if (index < all_clients)
		{
			while (distances)
			{
				if (distances->num_client == curr_path[index])
				{
					if (distances->dist != 0 && distances->dist != INFINITY)
					{
						temp_min[index] = curr_path[index];
						total_distance += distances->dist;
						counter++;
						checkPath(root, curr_path[index], curr_path, temp_min, index + 1, all_clients, total_distance,counter);
					}
					else
						return;
				}
				distances = distances->next;
			}
		}
	}
}


void filePaths(std::ofstream& file, std::vector<int> greedy_path, double total_greedy, double time_greedy, std::vector<int> brute_path, double total_brute, double time_brute, int all_clients)
{
	if (total_greedy > 0)
	{
		if (greedy_path.size() == all_clients)
		{
			file << "Path created by greedy algorithm: " << std::endl;
			for (int i = 0; i < all_clients; i++)
			{
				file << greedy_path[i] << " ";

			}
			file << std::endl << "Total distance by greedy algorithm: " << total_greedy << std::endl;
			file << "Time taken by the algorithm in seconds: " << time_greedy << std::endl;
		}
		else
			file << "No Path found by greedy Algorithm" << std::endl;
	}
	else
		file << "Something wrong with the greedy algorithm path"<< std::endl;
	if (all_clients < 13)
	{
		if (total_brute > 0)
		{
			file << "Path created by brute force algorithm: " << std::endl;
			for (int i = 0; i < all_clients; i++)
			{
				file << brute_path[i] << " ";
			}
			file << std::endl << "Total distance by brute force algorithm: " << total_brute << std::endl;
			file << "Time taken by the algorithm in seconds: " << time_brute << std::endl;
		}
		else
			file << "Something wrong with the brute force algorithm path" << std::endl;
	}
	else
		file << "Brute force algorithm was not executed as number of clients exceeds 12, higher number of clients would use too much of the ressources." << std::endl;
}