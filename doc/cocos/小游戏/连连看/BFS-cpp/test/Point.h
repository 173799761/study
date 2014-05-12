#ifndef POINT_HPP
#define POINT_HPP
#include <string>
#include <sstream>
struct Point
{
public:
	Point(int x ,int y);
	Point();
	~Point(void);
public:
	bool isEqual(Point dst);
	std::string toString();
private:
	std::string intToStr(int x);
public:
	int m_x;
	int m_y;
};

#endif // !POINT_HPP