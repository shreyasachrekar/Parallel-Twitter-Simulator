/**
 * Include all the files and packages here
 */
#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <vector>
#include <algorithm>
#include <stdbool.h>
#include <map>
#include <stdio.h>
#include<sys/time.h>
#include "NetworkGenerator.h"
using namespace std;
/**
 * @author Shreyas Achrekar & Pratik Deshpande
 *
 */

/*
 * Method accepts a Map and key as input and returns the node id which falls under the range in the key.
 *
 */
vector<Node*> addressVec;

Node mappedValue(map<double, int> map1, double key, vector<Node> nodeList) {
	std::vector<Node>::iterator node;
	std::map<double, int>::iterator itprev, it;
	int id;
	for (it = map1.begin(); it != map1.end();) {
		itprev = it;
		it++;
		if (itprev->first < key && key < it->first) {
			id = itprev->second;
		}
	}
	for (node = nodeList.begin();node != nodeList.end(); ++node) {
		if (node->getNodeId() == id)
			return *node;
	}
	return *node;
}

/*
 * Method accepts network size, initial network size, number of links to be
 * formed by each node and social ratio as input parameters. It calls
 * createInitialNetwork method to create initial network and then push_backs each
 * incoming node to the network, forming links based on preferential
 * attachment model. Returns list of nodes populated with their respective
 * node information.
 */

vector<Node> NetworkGenerator::createNodes(int networkSize,
		int initialNetworkSize, int links, double ratio, int flag) {
	vector < Node > nodeList1;
	nodeList1 = createInitialNetwork(initialNetworkSize);
	int i;
	int infoLinks = 4;
	int socialLinks = 2;
	Probability prob;
	Node node;
	struct timeval tstart1, tend1;
	for (i = initialNetworkSize; i < networkSize; i=i+1) {
		gettimeofday(&tstart1, NULL);
		Node newNode;
		//cout<<"Node"<<i<<"joining\n";
		vector<int> selected;
		map<double, int> infoTreeMap;
		map<double, int> socTreeMap;
		map<double, int> infoOutTreeMap;
		selected.clear();
		nodeList1 = prob.updateProbability(nodeList1,initialNetworkSize);
		prob.updateTreeMap(nodeList1,&infoTreeMap,&socTreeMap);
		//infoTreeMap = prob.updateInfoTreeMap((nodeList1));
		//socTreeMap = prob.updateSocTreeMap(nodeList1);

		int j = 0, k = 0;
		newNode.setNodeId(i);
		char* temp1="User";
		//strcat(temp1,"User");
		//char temp2[sizeof(int)];
		//sprintf(temp2, "%d", i);
		//strcat(temp1,temp2);
		char* temp="@user";
		//strcat(temp,"@user");
		//strcat(temp,temp2);
		newNode.setUserName(temp1);
		newNode.setHandle(temp);
		//newNode.deleteFollowers();
		//newNode.deleteFollowing();
		for (j = 0; j < infoLinks; j++) {
			double pickedNumber = ((double) rand() / (RAND_MAX));
			node = mappedValue(infoTreeMap, pickedNumber, nodeList1);

			if (std::find(selected.begin(), selected.end(), node.getNodeId())
					!= selected.end()) {
				j--;
				continue;
			}
			selected.push_back(node.getNodeId());
			newNode.addFollowing(node.getNodeId());
			for (std::vector<Node>::iterator temp = nodeList1.begin();	temp != nodeList1.end(); ++temp) {
				if (temp->getNodeId() == node.getNodeId()) {
					temp->setInfoCount((temp->getInfoCount()) + 1);
					temp->addFollowers(i);
				}
			}
		}

		for (k = 0; k < socialLinks; k++) {
			double pickedNumber = ((double) rand() / (RAND_MAX));
			node = mappedValue(socTreeMap, pickedNumber, nodeList1);
			if (std::find(selected.begin(), selected.end(), node.getNodeId())
					!= selected.end()) {
				k--;
				continue;
			}
			selected.push_back(node.getNodeId());

			for (std::vector<Node>::iterator temp = nodeList1.begin();
					temp != nodeList1.end(); ++temp) {
				if (temp->getNodeId() == node.getNodeId()) {
					temp->setSocialCount((temp->getSocialCount()) + 1);
					temp->addFollowers(i);
					temp->addFollowing(i);
				}
			}

			newNode.addFollowing(node.getNodeId());
			newNode.addFollowers(node.getNodeId());

		}
		vector<int> followers = newNode.getFollowers();
		newNode.setInfoOutCount(infoLinks);
		newNode.setSocialCount(socialLinks);
		nodeList1.push_back(newNode);
		gettimeofday(&tend1, NULL);
		cout<<"TIme taken for node number:"<<i<<" to join is "<<((tend1.tv_sec - tstart1.tv_sec) * 1000000.0 + (tend1.tv_usec - tstart1.tv_usec))/1000000 <<"secs\n";
	}
	for (vector<Node>::iterator it = nodeList1.begin(); it != nodeList1.end();++it) {
		Node* temp32 = new Node();
		temp32->setNodeId(it->getNodeId());
		temp32->setFollowers(it->getFollowers());
		temp32->setFollowing(it->getFollowing());
		addressVec.push_back(temp32);
	}
	return nodeList1;

}

/*
 * Method accepts initial network size as input parameter. Creates a fully
 * connected social network for the given input network size. Returns the
 * list of nodes populated with respective node information.
 */
vector<Node> NetworkGenerator::createInitialNetwork(int initialNetworkSize) {

	vector < Node > nodeList2;
	int i;
	for (i = 0; i < initialNetworkSize; i++) {
		Node node;
		node.setNodeId(i);
		char* temp1="User";
		//strcat(temp1, "User");
		//char* temp2="";//[sizeof(int)];
		//sprintf(temp2, "%d", i);
		//strcat(temp1, temp2);
		char* temp="@user";
		//strcat(temp, "@user");
		//strcat(temp,temp2);
		node.setUserName(temp1);
		node.setHandle(temp);
		nodeList2.push_back(node);
	}
	for (vector<Node>::iterator it = nodeList2.begin(); it != nodeList2.end();	++it) {
		for (i = 0; i < initialNetworkSize; i++) {
			if (i != it->getNodeId()) {
				it->addFollowers(i);
				it->addFollowing(i);
				it->setSocialCount(it->getSocialCount() + 1);
			}
		}
	}
	cout<<"\nDone with initial network\n";
	return nodeList2;
}
/*
 * This method just prints followers of the Node passed to it.
 *
 */
void NetworkGenerator::printFollowers(vector<Node*> address) {

	for (std::vector<Node*>::iterator temp = address.begin();
			temp != address.end(); ++temp)
		cout << "\nI am node id:" << (*temp)->getNodeId() << " and I have "
				<< (*temp)->getFollowers().size() << " followers";

}
/*
 *
 * This function takes in the addresses of all the nodes and a start point and
 * performs Depth First Search in the graph. At every depth, the probability of re-tweet will decrease exponentially.
 * Hence the pow() function
 *
 */
void NetworkGenerator::dfs(vector<Node*> address,int start,vector<int> *visited, int depth) {
	visited->at(start)=1;
	Node* temp= address.at(start);
	vector<int> foll=temp->getFollowers();
	for (std::vector<int>::iterator temp1 =foll.begin();temp1 != foll.end(); ++temp1){
		int id=*temp1;
		if(visited->at(id)==0){
			visited->at(id)=1;
			if(pow(((double) rand() / (RAND_MAX)),depth)>0.66){
				//cout<<"Visiting node:"<<*temp1<<endl;//<<" which is follower of:"<<start<<endl;
				depth++;
				dfs(address,id,visited,depth);
			}
		}
	}
}


int main(int argc, char**argv)
{
	struct timeval tstart, tend1, tend;
	gettimeofday(&tstart, NULL); //Start the simulator
	int networkSize = atoi(argv[1]);
	int initialNetworkSize;
	if(networkSize>10000)
		initialNetworkSize = 1000;
	else
		initialNetworkSize = networkSize/10;
	int links = 6;
	int nodeId = 0;
	double ratio = 0.3;
	int gamma = 0;
	int flag = 1;
	int depth=1;
	char response[20];
	NetworkGenerator netGen;
	vector < Node > nodeList = netGen.createNodes(networkSize,initialNetworkSize, links, ratio, flag);
	netGen.printFollowers(addressVec);
	cout << "\nNetwork of size " << nodeList.size() << " is generated\n";
	gettimeofday(&tend1, NULL); //Network creation is finished
	for(int i=0;i<networkSize;i++){
		vector<int> visited;
		for(int j=0;j<networkSize;j++)
			visited.push_back(0);
		//cout<<"\nStart node is:"<<i<<endl;
		netGen.dfs(addressVec,i,&visited,depth);
	}
	gettimeofday(&tend, NULL); //propagation of tweets is finished
	cout << "\nPropagation of tweets done \n\n";
	cout <<"Time required to create network:"<<((tend1.tv_sec - tstart.tv_sec) * 1000000.0 + (tend1.tv_usec - tstart.tv_usec))/1000000 <<"secs\n";
	cout <<"Time required to propagate tweets:"<<((tend.tv_sec - tend1.tv_sec) * 1000000.0 + (tend.tv_usec - tend1.tv_usec))/1000000<<" secs\n";

	return 0;

}
