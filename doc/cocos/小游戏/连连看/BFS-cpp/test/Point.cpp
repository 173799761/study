#include "stdafx.h"
#include "Point.h"

Point::~Point(void)
{
}

Point::Point( int x,int y )
	:m_x(x)
	,m_y(y)

{

}

Point::Point()
	:m_x(0)
	,m_y(0)
{

}

bool Point::isEqual( Point dst )
{
	return ((m_x == dst.m_x) && (m_y == dst.m_y)) ;
}

std::string Point::toString()
{
	std::string _str("");
	_str = "(" + intToStr(m_x) + "," + intToStr(m_y) + ")";
	return _str;
}

std::string Point::intToStr( int x )
{
	std::stringstream ss;

	ss << x;

	return ss.str();
}

