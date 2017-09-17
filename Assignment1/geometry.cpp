#include "geometry.hpp"
#include <cmath>
#include <algorithm>

using namespace std;

double getEuclideanDistance(Point a, Point b)
{
	/**
	 * This method returns the distance between two points.
	 */
	double diff1 = a.x - b.x;
	double diff2 = a.y - b.y;
	double sum = pow(diff1, 2) + pow(diff2, 2);
	double distance = sqrt(sum);
	return distance;
}

std::ostream& operator<<(std::ostream& os, const Point& point)
{
	/**
	 * Implements the output operator for the Point class.
	 */
	os << "(" << point.x << ',' << point.y << ")" << endl;
	return os;
}

Segment compareSegments(Segment a, Segment b)
{
	if (a.getLength() >= b.getLength())
		return a;
	else
		return b;
}

double Segment::getLength()
{
	/**
	 * Returns the length of the line given
	 */
	return this->segment_length;
}

Segment findBiggestEdge(std::vector<Segment> all_edges)
{
	Segment current_biggest = all_edges[1];
	for (auto &segment : all_edges) //access vector by reference to avoid copying?
	{
		current_biggest = (compareSegments(current_biggest, segment));
	}
	return current_biggest;
}
