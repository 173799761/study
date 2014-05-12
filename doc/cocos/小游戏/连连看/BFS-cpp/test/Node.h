#ifndef NODE_HPP
#define NODE_HPP
#include "Point.h"
class Node
{
public:
	Node(Point point);
	~Node(){}
public:
	bool isEqual(Node * dst);
	int getX(){return m_point.m_x;};
	int getY(){return m_point.m_y;}
	bool isPointEqual(Point dst);
	Point getPoint(){return m_point;}
private:
	Point m_point;
	Node * m_next;
};

#endif // !NODE_HPP






