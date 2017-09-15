#ifndef GEOMETRY_HPP  // These are file guards
#define GEOMETRY_HPP

#include <iostream>

class Point
{
public:
	int x;
	int y;
	friend std::ostream& operator<<(std::ostream& os, const Point& point);  // Define os << operator fo Point
	Point()
	{
		/**
		 * This is the default constructor
		 */
		this->x = 0;
		this->y = 0;
	}
	Point(int x_cord, int y_cord)
	{
		/**
		 * This constructor creates objects with the values passed on
		 */
		this->x = x_cord;
		this->y = y_cord;
	}
};

// Make Line class here.
class Segment
{
public:
	Point start;
	Point end;

	// put functions here

	Segment()
	{
		Point default_set = { 0, 0 };
		this->start = default_set;
		this->end = default_set;
	}

	Segment(Point a, Point b)
	{
		this->start = a;
		this->end = b;
	}

};

// Add method declarations(prototypes) here. For example
double getEuclideanDistance(Point, Point);  // Implementations are in geometry.cpp

#endif /* GEOMETRY_HPP */
