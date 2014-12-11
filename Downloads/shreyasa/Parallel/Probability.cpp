#include <string>
#include <vector>
#include<map>
#include<iostream>
#include<math.h>
#include "Probability.h"

/*
 * Class containing methods to determine probabilites of nodes.
 */
using namespace std;


/*******************/


double Probability::infoRange;
double Probability::socRange;



void Probability::updateProbability(int totalInfo,int totalSocia,int id,vector<double> *nodeProbSocio,vector<double> *nodeProbInfo,vector<int>*nodeSocioCount,vector<int> *nodeInfoCount,int inital) {
int i;

/*if(inital==10)
				{
	Probability::totalInfoSum = inital*(inital-1)-8;

				Probability::totalSocialSum =inital*(inital-1)-4;
				}
				Probability::totalInfoSum = Probability::totalInfoSum+8;
				Probability::totalSocialSum = Probability::totalSocialSum +4;*/
		//Node node;
		//cout<<"total info sum is:\t"<<totalInfoSum<<"\nTotal social sum is:\t"<<totalInfoSum<<endl;
				for(i=0;i<inital;i++)
				{
					//update both social and info prob

					nodeProbInfo->at(i)=((double)(nodeSocioCount->at(i)+nodeInfoCount->at(i))/ ((totalInfo+totalSocia)));
					nodeProbSocio->at(i)=((double)nodeSocioCount->at(i)/totalSocia);
					//cout<<"ID:"<<id<<":For node id:"<<i<<" Informational prob is:"<<nodeProbInfo->at(i)<<"\t"<<totalInfo<<"\t"<<nodeInfoCount->at(i)<<endl;
					//cout<<"ID:"<<id<<":For node id:"<<i<<" Social prob is:"<<nodeProbSocio->at(i)<<"\t"<<totalSocia<<"\t"<<nodeSocioCount->at(i)<<endl;

				}



	}

	/*
	 * Method to update social and information probability of every node in the network for nodes already
	 * in the network. Accepts and returns updated node list.
	 *
	 */



	/*
	 * Method accepts the node list as input and returns a TreeMap with information probability range as key
	 * and node id as value.
	 */

void Probability::updateTreeMap(vector<int> nodeList,vector<double>nodeProbInfo,vector<double>nodeProbSocio,int limit,map<double,int> *infoTreeMap,map<double,int> *socTreeMap ) {
int i;
Probability::socRange = 0.0;
Probability::infoRange = 0.0;
//cout<<"Inside map"<<endl;
for (i=0;i<limit;i++) {
socTreeMap->insert(pair<double, int>(Probability::socRange, nodeList.at(i)));
Probability::socRange = Probability::socRange + nodeProbSocio.at(i);
infoTreeMap->insert(	pair<double, int>(Probability::infoRange, nodeList.at(i)));
Probability::infoRange = Probability::infoRange + nodeProbInfo.at(i);
//cout<<"\nInserted Social Pair\t"<<nodeList.at(i)<<"\t"<<socRange<<endl;
//cout<<"\nInserted Info Pair\t"<<nodeList.at(i)<<"\t"<<infoRange<<endl;
}
Probability::socRange = 0.0;
Probability::infoRange = 0.0;
}

	/*
	 * Method accepts the node list as input and returns a TreeMap with information probability range as key
	 * and node id as value, for dynamic following of nodes.
	 */





