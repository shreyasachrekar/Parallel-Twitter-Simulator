#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <vector>
#include "Node.h"
using namespace std;



	Node::Node() {
		socialCount = 0;
		infoCount = 0;
		infoOutCount = 0;
		//cout<<"\nPAss by value";
		//vector<char*> tweets;
		//vector<char*> newsFeed;
		/*following = new ArrayList<int>();
		 followers = new ArrayList<int>();
		 tweets = new ArrayList<string>();
		 newsFeed = new ArrayList<string>();
		 */
	}

	/**
	 * @return the infoOutCount
	 */

	int Node:: getInfoOutCount() {
		return infoOutCount;
	}

	/**
	 * @param infoOutCount the infoOutCount to set
	 */

	void Node:: setInfoOutCount(int infoOutCount1) {
		infoOutCount = infoOutCount1;
	}

	/**
	 * @return the infoOutProb
	 */

	double Node:: getInfoOutProb() {
		return infoOutProb;
	}

	/**
	 * @param infoOutProb the infoOutProb to set
	 */

		void Node:: setInfoOutProb(double infoOutProb1) {
		infoOutProb = infoOutProb1;
	}

	/**
	 * @return the infoProb
	 */

	double Node:: getInfoProb() {
		return infoProb;
	}

	/**
	 * @param infoProb
	 *            the infoProb to set
	 */

	void Node:: setInfoProb(double infoProb1) {
		infoProb = infoProb1;
	}

	/**
	 * @return the socProb
	 */

	double Node:: getSocProb() {
		return socProb;
	}

	/**
	 * @param socProb
	 *            the socProb to set
	 */

	void Node:: setSocProb(double socProb1) {
		socProb = socProb1;
	}

	/**
	 * @return the socialCount
	 */

	int Node:: getSocialCount() {
		return socialCount;
	}

	/**
	 * @param socialCount
	 *            the socialCount to set
	 */

	void Node:: setSocialCount(int socialCount1) {
		socialCount = socialCount1;
	}

	/**
	 * @return the infoCount
	 */

	int Node:: getInfoCount() {
		return infoCount;
	}

	/**
	 * @param infoCount
	 *            the infoCount to set
	 */

	void Node:: setInfoCount(int infoCount1) {

		infoCount = infoCount1;
		//cout<<"\nNew info count is "<<infoCount<<" for "<<getNodeId();
	}

	/**
	 * @return the nodeId
	 */

	int Node:: getNodeId() {
		return nodeId;
	}

	/**
	 * @param nodeId
	 *            the nodeId to set
	 */

	void Node:: setNodeId(int nodeId1) {
		nodeId = nodeId1;
	}

	/**
	 * @return the userName
	 */

	char* Node:: getUserName() {
		return userName;
	}

	/**
	 * @param userName
	 *            the userName to set
	 */

	void Node:: setUserName(char* userName1) {
		userName = userName1;
	}

	/**
	 * @return the handle
	 */

	char* Node:: getHandle() {
		return handle;
	}

	/**
	 * @param handle
	 *            the handle to set
	 */

	void Node:: setHandle(char* handle1) {
		handle = handle1;
	}

	/**
	 * @return the nodeType
	 */


	/**
	 * @return the following
	 */

	vector<int> Node:: getFollowing() {
		return following;
	}
	void Node:: deleteFollowing() {
			following.clear();
		}
	void Node:: deleteFollowers() {
				followers.clear();
			}
	/**
	 * @param following
	 *            the following to set
	 */

	void Node:: setFollowing(vector<int> following1) {
		following = following1;
		//cout<<"\nSize of following is "<<following.size()<<"for node id"<<getNodeId();
	}
	void Node:: addFollowing(int following1) {

		following.push_back(following1);
		//cout<<"\nSize of following is "<<following.size()<<"for node id"<<getNodeId();
		}
	/**
	 * @return the followers
	 */

	vector<int> Node:: getFollowers() {
		return followers;
	}

	int Node::followersSize()
	{
		return followers.size();
	}
	/**
	 * @param followers
	 *            the followers to set
	 */

	void Node:: setFollowers(vector<int> followers1) {
		followers = followers1;

	}

	void Node::addFollowers(int followers1) {
		followers.push_back(followers1);
	}

