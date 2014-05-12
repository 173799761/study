#ifndef MAP_HPP
#define  MAP_HPP

#define XLEN 4
#define YLEN 4 
#define MAXNUM 10000 
#include "Point.h"
#include <vector>
class Node;

class Map
{
public:
	Map(void);
	~Map(void);
public:
	typedef std::vector<Node *> NodeVecPtr;
public:
	void init(Node * pSrcNode);
	void find(Node * pNodeSrc1,Node * pNodeDst1);
	void checkDup();
	void setPath(Node * pNodeSrc,Point dstPoint);
	void setCost(Node * pNodeSrc,Point dstPoint,int value);
	void pushBack();
	void getCachVec(NodeVecPtr & output);
	bool isFindTarget();
	int getCost();
	std::string getPath(Point src,Point dst);
private:
	NodeVecPtr m_cacheVec;
	NodeVecPtr m_sNodeVec;
	Node * m_pSrcNode;
	Node * m_pDstNode;

};


#endif // !MAP_HPP



