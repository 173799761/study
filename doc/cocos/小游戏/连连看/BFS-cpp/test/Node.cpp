#include "stdafx.h"
#include "Node.h"


Node::Node( Point point )
	:m_point(point)
	,m_next(nullptr)
{
	
}

bool Node::isEqual( Node * dst )
{
	return this->m_point.isEqual(dst->getPoint()) ;
}

bool Node::isPointEqual( Point dst )
{
	return m_point.isEqual(dst);
}


