#include "Point2D.h"
#include <iostream>
#include <math.h>

using namespace std;

Point2D::Point2D()
{
	x = 0.0;
	y = 0.0;
}
Point2D::Point2D(double in_x, double in_y)
{
	x = in_x;
	y = in_y;
}
double GetDistanceBetween(Point2D p1, Point2D p2)
{
	double out = sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
	return out;
}
ostream& operator<<(ostream& cout, const Point2D& p1)
{
	cout << "(" << p1.x << ", " << p1.y << ")" << endl;
	return cout;
}
Point2D operator+(const Point2D& p1, const Point2D& v1) // 2nd variable change from v to p
{
	double newX = p1.x + v1.x;
	double newY = p1.y + v1.y;
	Point2D retPoint(newX, newY);
	return retPoint;
}
Vector2D operator-(const Point2D& p1, const Point2D& p2)
{
	double newX = p1.x - p2.x;
	double newY = p1.y - p2.y;
	Vector2D retVec(newX, newY);
	return retVec;
}

