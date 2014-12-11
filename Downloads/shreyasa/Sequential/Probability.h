#ifndef Probability_h
#define Probability_h
#include <string>
#include <vector>
#include<map>
#include<iostream>
#include<math.h>
#include "Node.h"
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
	static double totalInfoSum;
	static double totalSocialSum;
	static double infoRange;
	static double socRange;
	static double totalOutInfoSum;
	static double totalOutSocialSum;

	/*
	 * Method to update the social and information probability of every node in the network.
	 * Accepts and returns the updated node list.
	 */
public:
	vector<Node> updateProbability(vector<Node> nodeList,int inital);

			/*
			 * Method to update social and information probability of every node in the network for nodes already
			 * in the network. Accepts and returns updated node list.
			 *
			 */
		public:
			vector<Node> updateOutProbability(vector<Node> nodeList) ;

			/*
			 * Method accepts the node list as input and returns a TreeMap with information probability range as key
			 * and node id as value.
			 */
		public:
			void updateTreeMap(vector<Node> nodeList,map<double,int> *infoTreeMap,map<double,int> *socTreeMap );

			/*
			 * Method accepts the node list as input and returns a TreeMap with information probability range as key
			 * and node id as value, for dynamic following of nodes.
			 */
		public:
			map<double, int> updateInfoOutTreeMap(vector<Node> nodeList);


};


#endif

