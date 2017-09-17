#include "geometry.hpp"
#include <cmath>

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

double Segment::getLength() {
    /**
     * Returns the length of the line given
     */
    double length = getEuclideanDistance(this->start, this->end);
    return length;
}
