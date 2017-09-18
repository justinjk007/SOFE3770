#include "geometry.hpp"
#include <algorithm>

using namespace std;

double getEuclideanDistance(Point a, Point b)
{
    /**
     * This method returns the distance between two points.
     */
    double diff1    = a.x - b.x;
    double diff2    = a.y - b.y;
    double sum      = pow(diff1, 2) + pow(diff2, 2);
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

std::ostream& operator<<(std::ostream& os, const Segment& segment)
{
    /**
     * Implements the output operator for the Segment class.
     */
    os << "(" << segment.start.x << ',' << segment.start.y << ")";
    os << " ------ ";
    os << "(" << segment.end.x << ',' << segment.end.y << ")" << endl;
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
    return this->length;
}

Segment findBiggestEdge(std::vector<Segment> all_edges)
{
    Segment current_biggest = all_edges[1];
    for (auto& segment : all_edges) {
        current_biggest = (compareSegments(current_biggest, segment));
    }
    return current_biggest;
}

std::vector<Segment> generateDiagonals(std::vector<Point> polygon)
{
    /**
     * Generate and return a list segments that represents all the
     * possible diagonals that can be generated from the given list of
     * points which make up the polygon. The points are expected to be
     * sorted counterclockwise and more than 3 in size(No diagonals
     * otherwise).
     */

    vector<Segment> diagonals;  // This will contain all the diagonals generated
    for (vector<Point>::iterator it1 = polygon.begin(); it1 != polygon.end(); it1++) {
	Point one = *it1;
        vector<Point>::iterator temp_it = it1;  // Temporarily store it until the end;
        if (++it1 != polygon.end())
            it1++;  // Skip a point
        else
            break;  // We are at the last point, all diagonals are made
        for (vector<Point>::iterator it2 = it1; it2 != polygon.end(); it2++) {
        }
        it1 = temp_it;  // Reset it11 to its begining position
    }

    return diagonals;
}
