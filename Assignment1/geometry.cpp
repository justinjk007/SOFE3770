#include "geometry.hpp"
#include <cmath>
#include <windef.h>

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
	os << "(" << point.x << ',' << point.y << ")" << endl;
	return os;
}

double Segment::compareSegments(Segment a, Segment b)
{
	double a_length = getEuclideanDistance(a.start, a.end);
	double b_length = getEuclideanDistance(b.start, b.end);
	double largest_length = max(a_length, b_length);
	return largest_length;
}
