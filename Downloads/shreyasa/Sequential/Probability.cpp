#include <string>
#include <vector>
#include<map>
#include<iostream>
#include<math.h>
#include "Probability.h"
#include "Node.h"
/*
 * Class containing methods to determine probability of nodes.
 */
using namespace std;


/*******************/

double Probability::totalInfoSum;
double Probability::totalSocialSum;
double Probability::infoRange;
double Probability::socRange;
double Probability::totalOutInfoSum;
double Probability::totalOutSocialSum;


vector<Node> Probability::updateProbability(vector<Node> nodeList,int inital) {
		if(nodeList.size()==inital){
			Probability::totalInfoSum = inital*(inital-1)-8;
			Probability::totalSocialSum =inital*(inital-1)-4;
		}
		Probability::totalInfoSum = Probability::totalInfoSum+8;
		Probability::totalSocialSum = Probability::totalSocialSum +4;
		//cout<<"Total info sum:"<<Probability::totalInfoSum<<"Total social sum"<<Probability::totalSocialSum<<endl;
		for (std::vector<Node>::iterator node = nodeList.begin(); node != nodeList.end(); node++) {
			node->setInfoProb((node->getInfoCount() + node->getSocialCount())/ Probability::totalInfoSum);
			node->setSocProb(node->getSocialCount() / Probability::totalSocialSum);
		}
		return nodeList;
	}

	/*
	 * Method to update social and information probability of every node in the network for nodes already
	 * in the network. Accepts and returns updated node list.
	 *
	 */

vector<Node> Probability::updateOutProbability(vector<Node> nodeList) {

		for (int i = 0; i < nodeList.size(); i++) {
			totalInfoSum = totalInfoSum + nodeList.at(i).getInfoOutCount()+ nodeList.at(i).getSocialCount();
		}
		for (std::vector<Node>::iterator node = nodeList.begin(); node != nodeList.end(); ++node) {
			node->setInfoOutProb(
					(node->getInfoOutCount() + node->getSocialCount())
							/ totalInfoSum);
		}
		totalInfoSum = 0;
		totalSocialSum = 0;

		return nodeList;
	}

	/*
	 * Method accepts the node list as input and returns a TreeMap with information probability range as key
	 * and node id as value.
	 */

void Probability::updateTreeMap(vector<Node> nodeList, map<double,int> *infoTreeMap, map<double,int> *socTreeMap ) {

	for (std::vector<Node>::iterator n = nodeList.begin(); n != nodeList.end();	++n) {
		socTreeMap->insert(pair<double, int>(Probability::socRange, n->getNodeId()));
		Probability::socRange = Probability::socRange + n->getSocProb();
		infoTreeMap->insert(pair<double, int>(Probability::infoRange, n->getNodeId()));
		Probability::infoRange = Probability::infoRange + n->getInfoProb();

	}
	Probability::socRange = 0.0;
	Probability::infoRange = 0.0;
}

	/*
	 * Method accepts the node list as input and returns a TreeMap with social probability range as key
	 * and node id as value.
	 */


	/*
	 * Method accepts the node list as input and returns a TreeMap with information probability range as key
	 * and node id as value, for dynamic following of nodes.
	 */

map<double, int> Probability:: updateInfoOutTreeMap(vector<Node> nodeList) {

		map<double, int> infoOutTreeMap;

		for (std::vector<Node>::iterator n = nodeList.begin(); n != nodeList.end(); ++n) {
			infoOutTreeMap.insert(pair<double,int>(Probability::infoRange, n->getNodeId()));
			Probability::infoRange = Probability::infoRange + n->getInfoOutProb();
		}
		Probability::infoRange = 0.0;
		return infoOutTreeMap;
	}



