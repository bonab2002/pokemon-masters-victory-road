#ifndef POINT2D_H
#define POINT2D_H
#include <iostream>
#include "Vector2D.h"
using namespace std;

class Point2D
{
	public:
		double x;
		double y;
		Point2D();
		Point2D(double, double);
		
};

double GetDistanceBetween(Point2D, Point2D);
ostream& operator<< (ostream&, const Point2D&);
Point2D operator+ (const Point2D&, const Point2D&);
Vector2D operator-(const Point2D&, const Point2D&);
#endif
