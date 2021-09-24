/** @file */
#pragma once
#include"Structures.h"

/** Function check if the input data is in correct format and if so it counts the number of the clients 
*	return the number of the clients
	@param input name of the input file
*/
int numberOfClients(std::string input);

/** Function creates and fills Clients structure with number of clients
	@param root pointer to the first element of the Clients structure
	@param number number of all clients
*/
void fillStructs(Clients*& root, int number);

/** Funciton creates and fills Distances structure with number of clients 
	@param root pointer to the specified Clients struct element
	@param number number of all clients
*/
Distances* fillDistances(Distances*& root, int number);

/** Function remove recursively all of the nodes od Clients structure
	@param root pointer to the first elements of the Clients structure
*/
void removeClients(Clients*& root);

/** Function remove recursively all of the nodes of Distances structure 
	@param root pointer to the first elements of Distances structure
*/
void removeDistances(Distances*& root);

/** Function reads input data and search for the type of connection between two of the clients, their numbers and distance between them 
	@param root pointer to the first elements of Clients structure
	@param inpute name of the input file
*/
void readFile(Clients*& root, std::string input);

/** Function searches for the client
*	returns pointer to the searched element
	@param root pointer to the first elements of Clients structure
	@param number number of the searched element
*/
Clients* ClientsSearch(Clients*& root, int number);

/** Function fills the Distance structure with distances between clients
	@param root pointer to the first elements of Distances structure
	@param number number of the searched element
	@param distance distance between current client and searched client
*/
void addDistances(Distances*& root, int number, double distance);

/** Function fills the path with number of the clients nad marks the ones that are being visited
	@param root pointer to the first elements of Clients structure
	@param greedy_path vector of the path that is being created
	@param num_client number of the current visited client
	@param all_clients number of all clients
	@param total_distance sum of the distances
*/
void minimalRoute(Clients*& root, std::vector<int>& greedy_path, int num_client, int all_clients, double& total_distance, int count_covered);

/** Function searches for the nearest client
	@param root pointer to the first elements of Clients structure
	@param num_client number of the current client
	@param total_distance distance sum of the distances
*/
int nearestNeighbour(Clients*& root, int num_client, double& total_distance);

/** Function creates the vector of all clients exept first one, function also creates a vector of size equal to numebr of clients
	@param root pointer to the first element of Clients structure
	@param brute_path vector for the path created by the algorithm
	@param num_client number of the first client
	@param all_clients number of all clients
	@param total_brute total distance of the path 
*/
void findPermut(Clients*& root, std::vector<int>& brute_path, int num_client, int all_clients, double& total_brute);

/** Function creates all possible permutatations of the clients (2...all_clients)
	@param root pointer to the first client
	@param arr vector of the clients
	@param brute_path vector for the path created by the algorithm
	@param index number of the current vector index
	@param num_elements number of the elements int the arr vector
	@param total_brute total distance of the path

*/
void permutation(Clients*& root, std::vector<int>& arr, std::vector<int>& brute_path, int index, int num_elements, double& total_brute);

/** Function create path vectors and create final path
	@param root pointer to the first client
	@param arr vector of the clients
	@param brute_path vector for the path created by the algorithm
	@param num_elements number of the elements int the arr vector
	@param total_brute total distance of the path
*/
void createPath(Clients*& root, std::vector<int>& arr, std::vector<int>& brute_path, int num_elements, double& total_brute);

/** Function check if current path permutation is a valid path
	@param root pointer to the first client
	@param num_client number of the current client
	@param curr_path vector of the current path
	@param temp_min vector of the current minimal path
	@param index number of the current vector index
	@param all_clients number of all elements
	@param total_distance total distance of the path
	@param counter counts all recursive repeats to check if all clients were visited
*/
void checkPath(Clients*& root, int num_client, std::vector<int>& curr_path, std::vector<int>& temp_min, int index, int all_clients, double& total_distance, int& counter);

/** Function takes the vectors of paths created by two algorithm, total distances of both and also time measured for their execution
	@param file file in which result is printed
	@param greedy_path vector of path created by greedy algorithn
	@param total_greedy value of distance counted by greedy algorithm
	@param time_greedy time in seconds that greedy algorithm took to count the path and distance
	@param brute_path vector of path created by brute force algorithn
	@param total_brute value of distance counted by brute force algorithm
	@param time_brute time in seconds that brute force algorithm took to count the path and distance
	@param all_clients number of all clients
*/
void filePaths(std::ofstream& file, std::vector<int> greedy_path, double total_greedy, double time_greedy, std::vector<int> brute_path, double total_brute, double time_brute, int all_clients);