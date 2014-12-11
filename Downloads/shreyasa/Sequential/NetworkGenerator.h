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
vector<Node> createNodes(int networkSize,int initialNetworkSize, int links, double ratio, int flag);
void printFollowers(vector<Node*> address);
vector<Node> createInitialNetwork(int initialNetworkSize) ;
void dfs(vector<Node*> address,int start,vector<int> *visited,int depth);
};
#endif
