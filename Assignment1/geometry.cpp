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
    /**
     * Implements the output operator for the Point class.
     */
	os << "(" << point.x << ',' << point.y << ")" << endl;
	return os;
}

<<<<<<< HEAD
double Segment::compareSegments(Segment a, Segment b)
{
	double a_length = getEuclideanDistance(a.start, a.end);
	double b_length = getEuclideanDistance(b.start, b.end);
	double largest_length = max(a_length, b_length);
	return largest_length;
=======
double Segment::getLength() {
    /**
     * Returns the length of the line given
     */
    double length = getEuclideanDistance(this->start, this->end);
    return length;
>>>>>>> 415bb857038d5367f1faa18daea3d0cbeb54cf9f
}
