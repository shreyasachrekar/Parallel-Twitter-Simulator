/**
 * Include all the files and packages here
 */
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <algorithm>
#include <stdbool.h>
#include <map>
#include <stdio.h>
#include<sys/time.h>
#include "NetworkGenerator.h"
#include "mpi.h"
/**
 * @author Shreyas Achrekar & Pratik Deshpande
 *
 */

/*
 * Method accepts a Map and key as input and returns the node id which falls under the range in the key.
 *
 */

int myid, numproc;
vector<vector<int> > followers;
vector<vector<int> > following;
vector<int> nodeInfoCount;
vector<int> nodeSocioCount;
vector<double> nodeProbInfo;
vector<double> nodeProbSocio;

int mappedValue(map<double, int> map1, double key, vector<int> nodeList) {
	int id, i;
//cout<<"\nInside mapped value"<<endl;
	std::map<double, int>::iterator itprev, it;
	for (it = map1.begin(); it != map1.end();) {
		itprev = it;
		it++;
		if (itprev->first < key && key < it->first) {
			id = itprev->second;
		}
	}
	for (i = 0; i < nodeList.size(); i++) {
		if (nodeList.at(i) == id)
			return i;
	}
	return 0;
}

/*
 * Method accepts network size, initial network size, number of links to be
 * formed by each node and social ratio as input parameters. It calls
 * createInitialNetwork method to create initial network and then push_backs each
 * incoming node to the network, forming links based on preferential
 * attachment model. Returns list of nodes populated with their respective
 * node information.
 */
void NetworkGenerator::initiliazeMaster(int networkSize) {
	int i, j;
	vector<int> tempfollowers;
	vector<int> tempfollowing;
	for (i = 0; i < networkSize; i++) {

		tempfollowers.push_back(i);
		tempfollowing.push_back(i);

		nodeSocioCount.push_back(0);
		nodeInfoCount.push_back(0);
		nodeProbSocio.push_back(0);
		nodeProbInfo.push_back(0);
		followers.push_back(tempfollowers);
		following.push_back(tempfollowing);
		tempfollowers.clear();
		tempfollowing.clear();
	}

}

void NetworkGenerator::initiliazeWorkers(int networkSize) {
	int i, j;

	for (i = 0; i < networkSize; i++) {

		nodeSocioCount.push_back(0);
		nodeInfoCount.push_back(0);
		nodeProbSocio.push_back(0);
		nodeProbInfo.push_back(0);

	}

}

vector<int> NetworkGenerator::createNodes(int networkSize, int localNetworkSize,
		int initialNetworkSize, int links, double ratio, int flag) {
	vector<int> nodeList1;
	map<double, int> infoTreeMap;
	map<double, int> socTreeMap;
	map<double, int> infoOutTreeMap;
	Probability prob;
	//only create initial network of following and followers for rank=1
	int step = 0;
	if (myid == 1) {
		nodeList1 = createInitialNetwork(localNetworkSize);
		updateNetwork(nodeList1.size(), 0, initialNetworkSize);
		//update node Probabilities initially
		Probability prob;
		/*prob.updateProbability(myid,&nodeProbInfo, &nodeProbSocio, &nodeSocioCount,
		 &nodeInfoCount, initialNetworkSize);*/

	}
	int i, j, k, l;
	int infoLinks = 4;
	int socialLinks = 2;

//take initial networks in terms of node ids
	//the initial network is the one which is made locally

	//receive list of social and info links
	int totalLinks[10];
	int loopflag = 1;
	double socialInfo[2 * localNetworkSize];
	int recvFor;//representing the twitter node for whom the message was intended
	MPI_Recv(&totalLinks, 10, MPI_INT, 0, 666, MPI_COMM_WORLD,
			MPI_STATUS_IGNORE);

	int totalInfo = 0;
	int totalSocio = 0;
	if (totalLinks[6] == -1)
		loopflag = 0;
	int count = 0;
	int sendUpdate = 0;
	while (loopflag == 1) {

		if (totalLinks[6] == -1) {
			cout << "\nTime to exit the loop\n";
			loopflag = 0;
			break;
		}

		else {
			step++;
			/*cout << "\nI am:[" << myid << "] and and got " << totalLinks[6]
			 << "\nMy Links are:";*/
			/*for (i = 0; i < 6; i++)
			 cout << myid << ":[" << totalLinks[i] << "]" << "\t";*/
			recvFor = totalLinks[6];
			totalInfo = totalLinks[7];
			totalSocio = totalLinks[8];
			sendUpdate = totalLinks[9];

			/*the following condition should be kept in mind after receiving
			 1)check if the value of twitter node falls in your own range
			 2)update followers,following accordingly if it does
			 3)check if your value is present anywhere in these links
			 4)if yes you need to update probability
			 5)if no you still got to update probability
			 6)once updated all these updated values need to be sent to master
			 7)Master needs to receive them and update them accordingly
			 */
			if (recvFor < myid * localNetworkSize
					&& recvFor >= (myid - 1) * localNetworkSize) {
				//cout << myid << ":This value is in my range"<<recvFor<<"\n";
				//we need to update its followers and following
				int localrecvFor = recvFor % localNetworkSize;
				for (j = 0; j < 6; j++) {
					int currnode = totalLinks[j];
					if (j < 4)	//social links
							{

						nodeSocioCount.at(localrecvFor) = nodeSocioCount.at(
								localrecvFor) + 1;
						/*cout << "\nUpdating social count for " << recvFor
						 <<"to"<<nodeSocioCount.at(recvFor) << endl;*/
					}
					//social+info links
					//following[localrecvFor].push_back(currnode);

					//we also need to update probability
				}
			}

			else {

				//this means that the message was not meant for me
				//now i need to check whether I am present in the social of info links
				int currnode;
				for (j = 0; j < 6; j++) {
					currnode = totalLinks[j];
					int localcurrnode = currnode % localNetworkSize;
					if (recvFor != currnode) {
						if (currnode < myid * localNetworkSize
								&& currnode > (myid - 1) * localNetworkSize) {
							if (j < 4)	//social node
									{
								//cout << "\n" << currnode << ":adding  "
								//<< recvFor
								//<< "as my follower and following\n";

								nodeSocioCount.at(localcurrnode) =
										nodeSocioCount.at(localcurrnode) + 1;
								/*cout << "\nUpdating social count for "
								 << currnode<<"to"<<nodeSocioCount.at(currnode) << endl;*/
								//update probability accordingly
							} else {
								//cout << "\n" << currnode << ":adding  "
								//<< recvFor << "as my follower\n";
								//only info link

								//update probability accordingly
								nodeInfoCount.at(localcurrnode) =
										nodeInfoCount.at(localcurrnode) + 1;
								/*	cout << "\nUpdating Info count for " << currnode
								 << "to" << nodeInfoCount.at(currnode)
								 << endl;*/
							}
						}

						//we also need to update probability
					}
				}
			}
			//update the total probability
			//cout << "\n" << myid << ":Done with one loop,updating probability"
			//	<< endl;
			prob.updateProbability(totalInfo, totalSocio, myid, &nodeProbInfo,
					&nodeProbSocio, &nodeSocioCount, &nodeInfoCount,
					localNetworkSize);
			//once updated send social and info probabilities
			int k;

			count = 0;

//sending step
			if (sendUpdate == 1) {
				for (k = 0; k < localNetworkSize; k++) {

					if (k < nodeProbSocio.size()) {
						socialInfo[count] = nodeProbSocio.at(k);

						socialInfo[localNetworkSize + count] = nodeProbInfo.at(
								k);

					} else {
						socialInfo[count] = 0;

						socialInfo[localNetworkSize + count] = 0;

					}/*cout << "\nSending social values[" << myid << "]"
					 << social[count] << endl;*/
					count = count + 1;

				}
				MPI_Send(&socialInfo, 2 * localNetworkSize, MPI_DOUBLE, 0, 666,
						MPI_COMM_WORLD);

				sendUpdate = 0;

			}

		}
//understand how to go non blocking...that can be done by listening threads
		MPI_Recv(&totalLinks, 10, MPI_INT, 0, 666, MPI_COMM_WORLD,
				MPI_STATUS_IGNORE);

	}
	cout << myid << ":My work here is done\n";

	return nodeList1;
}
/*
 * Method accepts initial network size as input parameter. Creates a fully
 * connected social network for the given input network size. Returns the
 * list of nodes populated with respective node information.
 */
vector<int> NetworkGenerator::createInitialNetwork(int localNetworkSize) {

	vector<int> nodeList2;
	vector<int> tempfollowing;
	vector<int> tempfollowers;
	int i, j;
	for (i = 0; i < localNetworkSize; i++) {

		nodeList2.push_back(i + (myid * localNetworkSize));

	}

	return nodeList2;

}

void NetworkGenerator::updateNetwork(int limit, int id,
		int initialNetworkSize) {
	vector<int> tempfollowing;
	vector<int> tempfollowers;
	int i, j;

	for (i = 0; i < limit; i++) {
		for (j = 0; j < limit; j++) {
			if (j != i) {
				//add followers and following
				/*cout << "Adding:[" << ((myid * localNetworkSize + j))
				 << "]As follower and following for["
				 << (myid * localNetworkSize) + i << "]\n";*/
				tempfollowers.push_back(j);
				tempfollowing.push_back(j);

//update the social count also

			}
		}
		if (id == 1) {
			followers.at(i) = (tempfollowers);
			following.at(i) = (tempfollowing);
		}
		nodeSocioCount.at(i) = initialNetworkSize - 1;
		nodeProbSocio.at(i) = (double) 1 / initialNetworkSize;
		nodeProbInfo.at(i) = (double) 1 / initialNetworkSize;
		// we can change this later
		tempfollowers.clear();
		tempfollowing.clear();
	}

}

/*
 * This method just prints followers of the Node passed to it.
 *
 */

/*
 *
 * This function takes in the addresses of all the nodes and a start point and
 * performs Depth First Search in the graph. At every depth, the probability of re-tweet will decrease exponentially.
 * Hence the pow() function
 *
 */
vector<int> NetworkGenerator::master(int localNetworkSize,
		int initialNetworkSize, int networkSize, int step) {

	int nodeNum;
	int totalSocio = (initialNetworkSize) * (initialNetworkSize - 1);
	int totalInfo = (initialNetworkSize) * (initialNetworkSize - 1);
	int i, j;

	vector<int> nodeList1;
	for (i = 0; i < initialNetworkSize; i++) {
		nodeList1.push_back(i);
	}
	/*display all nodes*/
	/*cout << "******************************\n" << "Displaying all nodes\n"
	 << "******************************\n";
	 for (i = 0; i < allNodes.size(); i++) {
	 cout << allNodes.at(i) << endl;
	 }*/
	//updating follower and following values of initial network
	map<double, int> infoTreeMap;
	map<double, int> socTreeMap;

	updateNetwork(initialNetworkSize, 1, initialNetworkSize);
	Probability prob;
	prob.updateProbability(totalInfo, totalSocio, 1, &nodeProbInfo,
			&nodeProbSocio, &nodeSocioCount, &nodeInfoCount,
			initialNetworkSize);
	//updating probabiity

	/*display all followers and following uptil now of each node*/
	/*cout << "******************************\n"
	 << "Displaying all followers and following\n"
	 << "******************************\n";
	 for (i = 0; i < followers.size() && i < following.size(); i++) {
	 for (j = 0; j < followers[i].size() && j < following[i].size(); j++) {
	 if (i != j) {
	 cout << "[" << followers[i].at(j) << "]is follower of[" << i
	 << "]\n";

	 cout << "[" << following[i].at(j) << "]is being followed by["
	 << i << "]\n";
	 }
	 }
	 }*/
	vector<int> temp1;
	vector<int> temp2;

	int socialLinks = 4;	//number of social links
	int infoLinks = 2;	//number of info links
	int totalLinks[10];
	int socNum;
	int infoNum;
	int node = 0;
	int currnode = 0;
	int sendToNode = 0;	//this represents ccr node
	int count = 0;
	int k;

	vector<int> selected;
	double start, finish;
	double socialInfo[2 * localNetworkSize];
	start = MPI_Wtime();
	for (i = initialNetworkSize; i < networkSize; i++) {
		socNum = 0;
		infoNum = 0;

		//cout<<"Added node number"<<i<<endl;
		selected.clear();
		step++;
		prob.updateTreeMap((nodeList1), nodeProbInfo, nodeProbSocio,
				nodeList1.size(), &infoTreeMap, &socTreeMap);
		while (socNum < socialLinks) {
			/*if (socNum < 3)
			 currnode = rand() % initialNetworkSize;
			 else
			 currnode = rand() % nodeList1.size();*/
			//cout<<"Picked node:"<<currnode<<endl;
			double pickedNumber = ((double) rand() / (RAND_MAX));
			//cout<<"Random number picked:"<<pickedNumber<<endl;
			currnode = mappedValue(socTreeMap, pickedNumber, nodeList1);
			//currnode=rand()%nodeList1.size();
			if (currnode > nodeList1.size())
				continue;			//some rubbish number
			if (std::find(selected.begin(), selected.end(), currnode)
					!= selected.end()) {
				//cout << "\nAlready present\n";
				continue;//already present
			}
			//cout << "Adding social link:" << currnode << endl;
			selected.push_back(currnode);//adding current node to selected nodes
			totalLinks[socNum] = currnode;	//adding current node for sending
			++socNum;			//increment the number of social links
			followers[i].push_back(currnode);
			following[i].push_back(currnode);

		}
		totalSocio += 8;
		while (infoNum < infoLinks) {
			/*	if (infoNum == 0)
			 currnode = rand() % initialNetworkSize;
			 else
			 currnode = rand() % nodeList1.size();*/
			double pickedNumber = ((double) rand() / (RAND_MAX));
			currnode = mappedValue(infoTreeMap, pickedNumber, nodeList1);//picking a random number from our list
			//currnode=rand()%nodeList1.size();
			if (currnode > nodeList1.size())
				continue;			//some rubbish number
			//cout << "\nThis is node for info:" << currnode <<"\t"<<i<< endl;
			if (std::find(selected.begin(), selected.end(), currnode)
					!= selected.end()) {
				//cout << "\nAlready present\n";
				continue;//already present
			}
			//cout << "Adding info link :" << currnode << endl;
			selected.push_back(currnode);		//adding current node to send
			totalLinks[socNum + infoNum] = currnode;//adding current node to send
			++infoNum;			//increment the number of social links
			followers[currnode].push_back(i);
			//cout<<"Done adding followers"<<endl;
		}
		totalInfo += 4;
		totalLinks[6] = i;//marking the last value as the id for which the message was meant
		//cout << "\nSending message for[" << totalLinks[6] << "]to["
		//	<< sendToNode << "]\n";
		totalLinks[8] = totalSocio;
		totalLinks[7] = totalInfo;
		if (i % step == 0)
			totalLinks[9] = 1;
		else
			totalLinks[9] = 0;
		for (j = 1; j < numproc; j++) {
			//cout<<"sending message to all the ccr nodes"<<endl;
			if (i >= j * localNetworkSize - 1)
				MPI_Send(&totalLinks, 10, MPI_INT, j, 666, MPI_COMM_WORLD);
		}

		nodeList1.push_back(i);

		//now receive from everyone their updated social and and info probabilities

		//first start with social
//receiveing if step

		if (totalLinks[9] == 1) {
			//cout << "\nStuck here" << step << endl;
			for (j = 1; j < numproc; j++) {
				count = 0;
				if (i >= j * localNetworkSize - 1) {
					MPI_Recv(&socialInfo, 2 * localNetworkSize, MPI_DOUBLE, j,
							666, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

					//add these values into our required probability
					for (k = (j - 1) * localNetworkSize;
							k < (j) * localNetworkSize; k++) {
						nodeProbSocio.at(k) = socialInfo[count];
						nodeProbInfo.at(k) =
								socialInfo[localNetworkSize + count];
						//cout << "\nRecived social value " << social[count] << endl;
						count++;
					}

				}
			}
		}

		if (i % 100 == 0) {
			finish = MPI_Wtime();
			cout << "Time taken for " << i << " th node " << i << " to join is "
					<< (finish - start) << endl;
		}
	}

	//after all the things are done send a message so that everything closes down
	for (j = 1; j < numproc; j++) {
		//sending message to all the ccr nodes
		totalLinks[6] = -1;		//indicating to exit

		MPI_Send(&totalLinks, 10, MPI_INT, j, 666, MPI_COMM_WORLD);
	}

	cout << "\n***********************Let there be light*******************\n";
	return nodeList1;
}

void NetworkGenerator::dfs(vector<int> address, int start, vector<int> *visited,
		int depth, vector<vector<int> > followers) {
	visited->at(start) = 1;
	//cout<<"\ninside dfs";
	int temp = address.at(start);
	vector<int> foll = followers.at(temp);
	for (std::vector<int>::iterator temp1 = foll.begin(); temp1 != foll.end();
			++temp1) {
		int id = *temp1;
		if (visited->at(id) == 0) {
			visited->at(id) = 1;
			if (pow(((double) rand() / (RAND_MAX)), depth) > 0.66) {
				//cout<<"Visiting node:"<<*temp1<<endl;//<<" which is follower of:"<<start<<endl;
				depth++;
				dfs(address, id, visited, depth, followers);
			}

		}
	}

}

int main(int argc, char **argv) {

	MPI_Init(&argc, &argv);

	double tstart, tend;

	int ierr;
	MPI_Comm_size(MPI_COMM_WORLD, &numproc);
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);
	if (argc < 3) {
		cout << "\nEnter the ./program [NetworkSize] [step]" << endl;
		return 0;
	}

	int networkSize = atoi(argv[1]);	//total network size
	int step = atoi(argv[2]);
	int localNetworkSize = networkSize / (numproc - 1);	//node network on each ccr node

	int initialNetworkSize;
	if (networkSize <= 1000)
		initialNetworkSize = networkSize / 10;//initially connected network,ie network on node 1
	else
		initialNetworkSize = 1000;
	if (myid == 0)
		cout << "\nNetwork size is:" << networkSize;
	int links = 6;
	int nodeId = 0;
	double ratio = 0.3;
	int gamma = 0;
	int flag = 1;
	int depth = 1;
	char response[20];
	NetworkGenerator netGen;
//if I am the 0th node
	vector<int> mainList;
	if (myid == 0) {
		tstart = MPI_Wtime();	//Start the simulator
		netGen.initiliazeMaster(networkSize);
		mainList = netGen.master(localNetworkSize, initialNetworkSize,
				networkSize, step);

	} else {
		//create a network
		netGen.initiliazeWorkers(localNetworkSize);
		vector<int> nodeList = netGen.createNodes(networkSize, localNetworkSize,
				initialNetworkSize, links, ratio, flag);
	}

	cout << "\nNetwork of size is generated\n";

	int l, m;

	if (myid == 0) {

		/*for (l = 0; l < networkSize; l++) {
		 //cout << "\nSocial probability for[" << l << "] is"<< nodeProbSocio.at(l) << endl;
		 //cout << "Info probability for[" << l << "] is"<< nodeProbInfo.at(l) << endl;
		 cout << "Followers for [" << l << "] are" << followers[l].size()<<endl;
		 //cout<<"\nFollowing for ["<<l<<"] are"<<following[l].size();

		 }*/
		tend = MPI_Wtime();	//Start the simulator
		double tweetStart, tweetEnd;

		tweetStart = MPI_Wtime();	//time to start tweet
		vector<int> visited;
		for (l = 0; l < networkSize; l = l + 200) {

			for (m = 0; m < networkSize; m++) {
				if (l == 0)
					visited.push_back(0);
				else
					visited.at(m) = 0;
			}

			//cout<<"\nStart node is:"<<l<<endl;
			netGen.dfs(mainList, l, &visited, depth, followers);
		}
		tweetEnd = MPI_Wtime();	//time to start tweet
		cout << "Time required for creating network:" << tend - tstart << endl;
		cout << "Time required for tweet propogation:" << tweetEnd - tweetStart
				<< endl;
	}
	MPI_Finalize();
	return 0;

}
