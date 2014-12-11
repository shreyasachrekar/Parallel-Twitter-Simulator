#ifndef Node_h
#define Node_h
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
using namespace std;

class Node {

private:
	int nodeId;
	char *userName;
	char *handle;
	int socialCount;
	int infoCount;
	int infoOutCount;
	double infoProb;
	double socProb;
	double infoOutProb;
	vector<string> tweets;
	vector<string> newsFeed;
	vector<int> following;
	vector<int> followers;

public:

	Node(void);

	int getInfoOutCount() ;

	/**
	 * @param infoOutCount the infoOutCount to set
	 */
public:
	void setInfoOutCount(int infoOutCount1) ;

	/**
	 * @return the infoOutProb
	 */
public:
	double getInfoOutProb() ;

	/**
	 * @param infoOutProb the infoOutProb to set
	 */
public:
		void setInfoOutProb(double infoOutProb1) ;
	/**
	 * @return the infoProb
	 */
public:
	double getInfoProb() ;
	/**
	 * @param infoProb
	 *            the infoProb to set
	 */
public:
	void setInfoProb(double infoProb1) ;

	/**
	 * @return the socProb
	 */
public:
	double getSocProb();

	/**
	 * @param socProb
	 *            the socProb to set
	 */
public:
	void setSocProb(double socProb1) ;

	/**
	 * @return the socialCount
	 */
public:
	int getSocialCount() ;

	/**
	 * @param socialCount
	 *            the socialCount to set
	 */
public:
	void setSocialCount(int socialCount1) ;

	/**
	 * @return the infoCount
	 */
public:
	int getInfoCount();
	/**
	 * @param infoCount
	 *            the infoCount to set
	 */
public:
	void setInfoCount(int infoCount1) ;

	/**
	 * @return the nodeId
	 */
public:
	int getNodeId();

	/**
	 * @param nodeId
	 *            the nodeId to set
	 */
public:
	void setNodeId(int nodeId1) ;

	/**
	 * @return the userName
	 */
public:
	char* getUserName();

	/**
	 * @param userName
	 *            the userName to set
	 */
public:
	void setUserName(char* userName1);

	/**
	 * @return the handle
	 */
public:
	char* getHandle() ;

	/**
	 * @param handle
	 *            the handle to set
	 */
public:
	void setHandle(char* handle1);

	/**
	 * @return the nodeType
	 */

	/**
	 * @return the following
	 */
public:
	vector<int> getFollowing();

	/**
	 * @param following
	 *            the following to set
	 */
public:
	void setFollowing(vector<int> following1) ;

	/**
	 * @return the followers
	 */
public:
	vector<int> getFollowers();

	/**
	 * @param followers
	 *            the followers to set
	 */
public:
	void setFollowers(vector<int> followers1);
public:
	void addFollowers(int followers1);
	void addFollowing(int following1);
	int followersSize();

	void deleteFollowing();
		void deleteFollowers();

};

#endif
