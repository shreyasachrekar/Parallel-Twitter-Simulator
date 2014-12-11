#ifndef Probability_h
#define Probability_h
#include <string>
#include <vector>
#include<map>
#include<iostream>
#include<math.h>

/*
 * Class containing methods to determine probabilites of nodes.
 */
using namespace std;




/*
 * Class containing methods to determine probabilites of nodes.
 */




/*******************/

class Probability {


private:

	static double infoRange;
	static double socRange;


	/*
	 * Method to update the social and information probability of every node in the network.
	 * Accepts and returns the updated node list.
	 */
public:
	void updateProbability(int totalInfo,int totalSocia,int id,vector<double> *nodeProbSocio,vector<double> *nodeProbInfo,vector<int>*nodeSocioCount,vector<int> *nodeInfoCount,int inital);
	void updateTreeMap(vector<int> nodeList,vector<double>nodeProbInfo,vector<double>nodeProbSocio,int limit,map<double,int> *infoTreeMap,map<double,int> *socTreeMap );



};


#endif

