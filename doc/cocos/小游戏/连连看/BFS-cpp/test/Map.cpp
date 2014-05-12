#include "stdafx.h"
#include "Map.h"
#include "Node.h"

int g_matrix[XLEN][YLEN] = {{1,0,0,1},{1,1,0,1},{1,1,0,1},{1,0,0,1}};
Point Path[XLEN][YLEN];
int cost[XLEN][YLEN];

Map::Map(void)
{
}


Map::~Map(void)
{
}

void Map::init( Node * pSrcNode)
{
	//初始化矩阵
	for(int i=0;i<XLEN;i++)
	{
		for(int j=0;j<YLEN;j++)
		{
			cost[i][j] = MAXNUM;
		}
	}
	cost[pSrcNode->getX()][pSrcNode->getY()] = 0;
	m_sNodeVec.push_back(pSrcNode);

}



void Map::find( Node * pNodeSrc1,Node * pNodeDst1)
{
	m_pSrcNode = pNodeSrc1;
	m_pDstNode = pNodeDst1;
	
	m_cacheVec.clear();
	int xBottom = m_pSrcNode->getX() - 1;
	while(xBottom >= 0)
	{   
		Point _p;
		//扩展到第一个有图片的节点为止
		if(g_matrix[xBottom][m_pSrcNode->getY()] == 1)
		{   
			_p = Point(xBottom,m_pSrcNode->getY());
			if(cost[_p.m_x][_p.m_y]==MAXNUM||(m_pDstNode->isPointEqual(_p)))//未被扩展的节点或者是终点
			{
				Node* _pNode = new Node(_p);
				m_cacheVec.push_back(_pNode);
				if(cost[m_pSrcNode->getX()][m_pSrcNode->getY()] + m_pSrcNode->getX() - xBottom <cost[xBottom][m_pSrcNode->getY()])
				{
					setPath(m_pSrcNode,_p);
					setCost(m_pSrcNode , _p , m_pSrcNode->getX() - xBottom);
					
				}
			}
			break;
		}


		_p.m_x = xBottom;
		_p.m_y = m_pSrcNode->getY();

		if(cost[_p.m_x][_p.m_y] == MAXNUM || (m_pDstNode->isPointEqual(_p)))
		{
			Node* _pNode = new Node(_p);

			m_cacheVec.push_back(_pNode);	
			
			if(cost[m_pSrcNode->getX()][m_pSrcNode->getY()]  + m_pSrcNode->getX() - xBottom  < cost[xBottom][m_pSrcNode->getY()])
			{
				setPath(m_pSrcNode,_p);
				setCost(m_pSrcNode , _p , m_pSrcNode->getX() - xBottom);
			}
		}


		//路径问题
		xBottom--;
	}

	int xTop = m_pSrcNode->getX() + 1;
	while(xTop < XLEN)
	{   
		Point _p;
		//扩展到第一个有图片的节点为止
		if(g_matrix[xTop][m_pSrcNode->getY()] == 1)
		{   
			_p = Point(xTop,m_pSrcNode->getY());
			if(cost[_p.m_x][_p.m_y]==MAXNUM||(m_pDstNode->isPointEqual(_p)))//未被扩展的节点或者是终点
			{
				Node* _pNode = new Node(_p);
				m_cacheVec.push_back(_pNode);
				if(cost[m_pSrcNode->getX()][m_pSrcNode->getY()] + m_pSrcNode->getX() - xTop <cost[xTop][m_pSrcNode->getY()])
				{
					setPath(m_pSrcNode,_p);
					setCost(m_pSrcNode , _p , m_pSrcNode->getX() - xTop);

				}
			}
			break;
		}


		_p.m_x = xTop;
		_p.m_y = m_pSrcNode->getY();

		if(cost[_p.m_x][_p.m_y] == MAXNUM || (m_pDstNode->isPointEqual(_p)))
		{
			Node* _pNode = new Node(_p);

			m_cacheVec.push_back(_pNode);	

			if(cost[m_pSrcNode->getX()][m_pSrcNode->getY()]  + m_pSrcNode->getX() - xTop  < cost[xTop][m_pSrcNode->getY()])
			{
				setPath(m_pSrcNode,_p);
				setCost(m_pSrcNode , _p , m_pSrcNode->getX() - xTop);
			}
		}


		
		xTop++;
	}


	int yl = m_pSrcNode->getY() - 1;
	while(yl >= 0)
	{   
		Point _p;
		if(g_matrix[m_pSrcNode->getX()][yl] == 1)
		{
			_p = Point(m_pSrcNode->getX(),yl);

			if(cost[_p.m_x][_p.m_y] == MAXNUM || (m_pDstNode->isPointEqual(_p)))
			{
				Node* _pNode = new Node(_p);
				m_cacheVec.push_back(_pNode);	

				if(cost[m_pSrcNode->getX()][m_pSrcNode->getY()] + m_pSrcNode->getY() - yl < cost[m_pSrcNode->getX()][yl])
				{
					setPath(m_pSrcNode,_p);
					setCost(m_pSrcNode , _p , m_pSrcNode->getY() - yl);
				}
			}
			break;
		}

		_p = Point(m_pSrcNode->getX(),yl);

		if(cost[_p.m_x][_p.m_y] == MAXNUM || (m_pDstNode->isPointEqual(_p)))
		{
			Node* _pNode = new Node(_p);
			m_cacheVec.push_back(_pNode);

			if(cost[m_pSrcNode->getX()][m_pSrcNode->getY()] + m_pSrcNode->getY() - yl < cost[m_pSrcNode->getX()][yl])
			{
				setPath(m_pSrcNode,_p);
				setCost(m_pSrcNode , _p , m_pSrcNode->getY() - yl);
			}
		}
		yl--;

	}


	int yr = m_pSrcNode->getY() + 1;
	while(yr < YLEN )
	{   
		Point _p;
		if(g_matrix[m_pSrcNode->getX()][yr] == 1)
		{
			_p = Point(m_pSrcNode->getX(),yr);

			if(cost[_p.m_x][_p.m_y] == MAXNUM || (m_pDstNode->isPointEqual(_p)))
			{
				Node* _pNode = new Node(_p);
				m_cacheVec.push_back(_pNode);	

				if(cost[m_pSrcNode->getX()][m_pSrcNode->getY()] + m_pSrcNode->getY() - yr < cost[m_pSrcNode->getX()][yr])
				{
					setPath(m_pSrcNode,_p);
					setCost(m_pSrcNode , _p , m_pSrcNode->getY() - yr);
				}
			}
			break;
		}

		_p = Point(m_pSrcNode->getX(),yr);

		if(cost[_p.m_x][_p.m_y] == MAXNUM || (m_pDstNode->isPointEqual(_p)))
		{
			Node* _pNode = new Node(_p);
			m_cacheVec.push_back(_pNode);

			if(cost[m_pSrcNode->getX()][m_pSrcNode->getY()] + m_pSrcNode->getY() - yr < cost[m_pSrcNode->getX()][yr])
			{
				setPath(m_pSrcNode,_p);
				setCost(m_pSrcNode , _p , m_pSrcNode->getY() - yr);
			}
		}
		++yr;

	}
}

void Map::checkDup()
{
	for (NodeVecPtr::iterator itr = m_cacheVec.begin();itr != m_cacheVec.end();)
	{
		bool _flag(false);
		Node * _pNode = *itr;
		for (auto sItr : m_sNodeVec)
		{
			
			if ( _pNode->isEqual(sItr))
			{
				itr = m_cacheVec.erase(itr);
				_flag = true;
				break;
			}
		}

		if (_flag == true)
		{
			continue;
		}

		if (g_matrix[_pNode->getX()][_pNode->getY()] == 1)
		{
			itr = m_cacheVec.erase(itr);
			continue;
		}

		++itr;
	}
}

void Map::setPath( Node * pNodeSrc,Point dstPoint )
{
	Path[dstPoint.m_x][dstPoint.m_y] = pNodeSrc->getPoint();
}

void Map::setCost( Node * pNodeSrc,Point dstPoint,int value )
{
	cost[dstPoint.m_x][dstPoint.m_y] = cost[pNodeSrc->getX()][pNodeSrc->getY()] + abs(value);
}

bool Map::isFindTarget()
{
	
	
	for (auto itr : m_cacheVec)
	{
		if (itr->isEqual(m_pDstNode))
		{
			return true;
		}
	}

	return false;
}

void Map::pushBack()
{
	m_sNodeVec.insert(m_sNodeVec.end(),m_cacheVec.begin(),m_cacheVec.end());
}

int Map::getCost()
{
	return cost[m_pDstNode->getX()][m_pDstNode->getY()];
}

void Map::getCachVec( NodeVecPtr & output )
{
	output = m_cacheVec;
}

std::string Map::getPath(Point src,Point dst)
{
	//Point p = m_pDstNode->getPoint();
	std::string _str("");
	while(dst.isEqual(src) == false)
	{
		dst = Path[dst.m_x][dst.m_y];
		_str += dst.toString();
		_str += " ";
	}

	return _str;
}
