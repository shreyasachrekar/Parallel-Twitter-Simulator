#ifndef NetworkGenerator_h
#define NetworkGenerator_h
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <stdbool.h>
#include <map>
#include "Probability.h"
using namespace std;
class NetworkGenerator{



public:
	vector<int> createNodes(int networkSize,int localNetworkSize,int initialNetworkSize, int links, double ratio, int flag);
	void dfs(vector<int> address, int start,
			vector<int>* visited, int depth,vector<vector<int> > followers);
	void initiliazeMaster(int networkSize);
	void initiliazeWorkers(int networkSize);
vector<int> createInitialNetwork(int initialNetworkSize) ;

vector<int> master(int localNetworkSize,int initialNetworkSize,int networkSize,int step);
void updateNetwork(int limit,int id,int initialNetworkSize);
};
#endif
