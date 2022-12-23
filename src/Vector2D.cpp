#include "Vector2D.h"
#include <iostream>
using namespace std;

Vector2D::Vector2D()
{
	x = 0.0;
	y = 0.0;
}

Vector2D::Vector2D(double in_x, double in_y)
{
	x = in_x;
	y = in_y;
}

Vector2D operator*(const Vector2D& v1, const double d)
{
	double newX = v1.x * d;
	double newY = v1.y * d;
	Vector2D retVec(newX, newY);
	return retVec;
}

Vector2D operator/(const Vector2D& v1, const double d)
{
	if (d != 0)
	{
		double newX = (double)v1.x / d;
		double newY = (double)v1.y / d;
		Vector2D retVec(newX, newY);
		return retVec;
	}
	return v1;
}

ostream& operator<<(ostream& cout, const Vector2D& v1)
{
	cout << "<" << v1.x << ", " << v1.y << ">" << endl;
	return cout;
}
