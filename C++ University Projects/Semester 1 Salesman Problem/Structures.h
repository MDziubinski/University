/**@file */

#pragma once
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <time.h>
#include <vector>
#ifdef _DEBUG
	#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
	#define new DBG_NEW 
#endif

/** Strcuture describes list of distances from client to other clients*/
struct Distances
{
	/** Number of the client*/
	int num_client;
	/** Number of the client*/
	double dist;
	/** Number of the client*/
	Distances* next;
};
/** Structure describe list of clients */
struct Clients
{	
	/** Number of the client*/
	int num_client;
	/** Variable that describes if client war visited or not*/
	bool covered;
	/** Pointer to the next element of Clients structure*/
	Clients* next;
	/** Pointer to the first elements of Distances Structure*/
	Distances* distances;
};