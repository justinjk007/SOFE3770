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

bool operator==(const Point& one, const Point& two)
{
    if (one.x == two.x && one.y == two.y) return true;
    return false;
}

bool operator==(const Segment& one, const Segment& two)
{
    if (one.start == two.start && one.end == two.end)
        return true;
    else if (one.start == two.end && one.end == two.start)
        return true;
    return false;
}

Segment compareSegments(Segment a, Segment b)
{
    /*
     * Returns the Segment object with the largest length.
     */
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
    /**
     * Returns the biggest edge of the polygon as a segment object.
     */
    Segment current_biggest = all_edges[1];
    for (auto& segment : all_edges)  // access vector by reference to avoid copying?
    {
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

    {
        // Generate diagonals from the first point of the polygon
        vector<Point>::iterator it1 = polygon.begin();
        Point point_one             = *it1;
	std::advance(it1,2);  // Skip a point
        for (vector<Point>::iterator it2 = it1; it2 != polygon.end(); it2++) {
            Segment diagonal_line = {point_one, *it2};
            diagonals.push_back(diagonal_line);
        }
	diagonals.pop_back(); // Remove the last line it is an edge
    }
    {
        // This is for rest of the points in the polygon
    	vector<Point>::iterator it1 = polygon.begin();
        for (it1 = ++it1; it1 != polygon.end(); it1++) {
            Point point_one                 = *it1;
            vector<Point>::iterator temp_it = it1;  // Temporarily store it until the end;
            if (++it1 != polygon.end())
                it1++;  // Skip a point
            else
                break;  // We are at the last point, all diagonals are made
            for (vector<Point>::iterator it2 = it1; it2 != polygon.end(); it2++) {
                Segment diagonal_line = {point_one, *it2};
                diagonals.push_back(diagonal_line);
            }
            it1 = temp_it;  // Reset it11 to its begining position
        }
    }

    return diagonals;
}

std::vector<Segment> generateEdges(std::vector<Point> all_points)
{
    vector<Segment> polygon;
    Point current = all_points[0];
    Point next;
    // Generates edges except for the last edge of the polygon
    for (int count = 1; count < all_points.size(); count++) {
        next = all_points[count];
        polygon.push_back(Segment(current, next));
        current = all_points[count];
    }
    // Creates the last segment (connects to starting point)
    next = all_points[0];
    polygon.push_back(Segment(current, next));
    return polygon;
}
