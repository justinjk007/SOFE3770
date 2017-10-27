#include "Pareto.hpp"
#include <algorithm>
#include <vector>
#include "ConvexHull.hpp"

using namespace std;

/*
 * Method used to access private attribute of a Point object.
 */
double Point::getX()
{
    return this->x;
}

/*
 * Method used to access private attribute of a Point object.
 */
double Point::getY()
{
    return this->y;
}

/*
 * Implementation specific to Point objects.
 */
std::ostream& operator<<(std::ostream& os, const Point& point)
{
    /**
     * Implements the output operator for the Point class.
     */
    os << "(" << point.x << ',' << point.y << ")" << endl;
    return os;
}

/*
 * Implementation specific to Point objects.
 */
bool operator==(const Point& one, const Point& two)
{
    if (one.x == two.x && one.y == two.y) return true;
    return false;
}

/*
 * Takes two given vectors representing the x and y value pairs and creates
 * a vector of Point objects.
 */
vector<Point> populateList(vector<int> u, vector<int> v)
{
    vector<Point> masterList;
    // Can check to make sure u and v are the same length if needed
    // here~~~~~~~

    // Access vector by reference to avoid copying.
    for (int coordinate = 0; coordinate < u.size(); coordinate++) {
        masterList.push_back(Point(u[coordinate], v[coordinate]));
    }

    return masterList;
}

/*
 * Creates and sorts a vector using the list of all Point objects by using
 * std::sort with a char input representing which axis to be sorted by.
 */
vector<Point> sortedPointList(vector<Point> masterList, char axis)
{
    // Creates a new vector by copying original vector to new one.
    vector<Point> sortedList(masterList);
    if (axis == 'x')
        std::sort(sortedList.begin(), sortedList.end(), compareByX);
    else
        std::sort(sortedList.begin(), sortedList.end(), compareByY);

    return sortedList;
}

/*
 * Function that sorts objects by x attribute when called by std::sort.
 */
bool compareByX(Point a, Point b)
{
    return a.getX() < b.getX();
}

/*
 * Function that sorts objects by y attribute when called by std::sort.
 */
bool compareByY(Point a, Point b)
{
    return a.getY() < b.getY();
}

/*
 * Traverses all convex hull points to find smallest x and y value point.
 */
Point pointSmallestXY(vector<Point> convexHull)
{
    Point bestFit = convexHull[0];
    for (auto& point : convexHull) {
        // Checking which point has the smallest value to be the best point.
        if (point.getX() < bestFit.getX()) {
            bestFit = point;
        }
        // If both have the same value, check a secondary value to determine which point is the best
        // point.
        else if (point.getX() == bestFit.getX()) {
            // Check secondary value
            if (point.getY() < bestFit.getY()) {
                bestFit = point;
            }
            // No else if here because it is not possible to have two points with identical x AND y
            // values.
        }
    }
    return bestFit;
}

/*
 * Traverses all convex hull points to find largest x and smallest y value point.
 */
Point pointLargestSmallestXY(vector<Point> convexHull)
{
    Point bestFit = convexHull[0];
    for (auto& point : convexHull) {
        // Checking which point has the largest value to be the best point.
        if (point.getX() > bestFit.getX()) {
            bestFit = point;
        }
        // If both have the same value, check a secondary value to determine which point is the best
        // point.
        else if (point.getX() == bestFit.getX()) {
            // Check secondary value
            if (point.getY() < bestFit.getY()) {
                bestFit = point;
            }
            // No else if here because it is not possible to have two points with identical x AND y
            // values.
        }
    }
    return bestFit;
}

/*
 * Traverses all convex hull points to find smallest x and largest y value point.
 */
Point pointSmallestLargestXY(vector<Point> convexHull)
{
    Point bestFit = convexHull[0];
    for (auto& point : convexHull) {
        // Checking which point has the smallest value to be the best point.
        if (point.getX() < bestFit.getX()) {
            bestFit = point;
        }
        // If both have the same value, check a secondary value to determine which point is the best
        // point.
        else if (point.getX() == bestFit.getX()) {
            // Check secondary value
            if (point.getY() > bestFit.getY()) {
                bestFit = point;
            }
            // No else if here because it is not possible to have two points with identical x AND y
            // values.
        }
    }
    return bestFit;
}

/*
 * Traverses all convex hull points to find largest x and y value point.
 */
Point pointLargestXY(vector<Point> convexHull)
{
    Point bestFit = convexHull[0];
    for (auto& point : convexHull) {
        // Checking which point has the largest value to be the best point.
        if (point.getX() > bestFit.getX()) {
            bestFit = point;
        }
        // If both have the same value, check a secondary value to determine which point is the best
        // point.
        else if (point.getX() == bestFit.getX()) {
            // Check secondary value
            if (point.getY() > bestFit.getY()) {
                bestFit = point;
            }
            // No else if here because it is not possible to have two points with identical x AND y
            // values.
        }
    }
    return bestFit;
}

vector<Point> getParetoFrontierLL(vector<Point> points)
{
    /**
     * Get the Pareto Frontier where X and Y and supposed to be LOW to be dominant
     */
    vector<Point> frontier;
    vector<Point> hull = getConvexHull(points);
    int h_size         = hull.size();

    // Find the end points of the dominant frontier
    Point start = pointSmallestLargestXY(hull);
    Point end   = pointLargestSmallestXY(hull);

    // Find the index of the start point
    int start_i = find(hull.begin(), hull.end(), start) - hull.begin();  // Big-O(n)

    // Now traverse through the convex hull from start to end point to get the frontier
    Point current = hull[start_i];
    int i;
    for (i = start_i; !(current == end);) {
        frontier.push_back(current);
        i++;
        current = hull[i % h_size];  // This will make the iteration wrap around like a circle
    }
    frontier.push_back(end);          // Add the last point
    number_of_frontier_points = ++i;  // Don't delete this we need it

    return frontier;
}

vector<Point> getParetoFrontierHH(vector<Point> points)
{
    /**
     * Get the Pareto Frontier where X and Y and supposed to be HIGH to be dominant
     */
    vector<Point> frontier;
    vector<Point> hull = getConvexHull(points);
    int h_size         = hull.size();

    // Find the end points of the dominant frontier
    Point start = pointLargestSmallestXY(hull);
    Point end   = pointSmallestLargestXY(hull);

    // Find the index of the start point
    int start_i = find(hull.begin(), hull.end(), start) - hull.begin();  // Big-O(n)

    // Now traverse through the convex hull from start to end point to get the frontier
    Point current = hull[start_i];
    int i;
    for (i = start_i; !(current == end);) {
        frontier.push_back(current);
        i++;
        current = hull[i % h_size];  // This will make the iteration wrap around like a circle
    }
    frontier.push_back(end);          // Add the last point
    number_of_frontier_points = ++i;  // Don't delete this we need it

    return frontier;
}

vector<Point> getParetoFrontierLH(vector<Point> points)
{
    /**
     * Get the Pareto Frontier where X and Y and supposed to be LOW
     * and HIGH respectively to be dominant
     */
    vector<Point> frontier;
    vector<Point> hull = getConvexHull(points);
    int h_size         = hull.size();

    // Find the end points of the dominant frontier
    Point start = pointLargestXY(hull);
    Point end   = pointSmallestXY(hull);

    // Find the index of the start point
    int start_i = find(hull.begin(), hull.end(), start) - hull.begin();  // Big-O(n)

    // Now traverse through the convex hull from start to end point to get the frontier
    Point current = hull[start_i];
    int i;
    for (i = start_i; !(current == end);) {
        frontier.push_back(current);
        i++;
        current = hull[i % h_size];  // This will make the iteration wrap around like a circle
    }
    frontier.push_back(end);          // Add the last point
    number_of_frontier_points = ++i;  // Don't delete this we need it

    return frontier;
}

vector<Point> getParetoFrontierHL(vector<Point> points)
{
    /**
     * Get the Pareto Frontier where X and Y and supposed to be HIGH
     * and LOW respectively to be dominant
     */
    vector<Point> frontier;
    vector<Point> hull = getConvexHull(points);
    int h_size         = hull.size();

    // Find the end points of the dominant frontier
    Point start = pointSmallestXY(hull);
    Point end   = pointLargestXY(hull);

    // Find the index of the start point
    int start_i = find(hull.begin(), hull.end(), start) - hull.begin();  // Big-O(n)

    // Now traverse through the convex hull from start to end point to get the frontier
    Point current = hull[start_i];
    int i;
    for (i = start_i; !(current == end);) {
        frontier.push_back(current);
        i++;
        current = hull[i % h_size];  // This will make the iteration wrap around like a circle
    }
    frontier.push_back(end);          // Add the last point
    number_of_frontier_points = ++i;  // Don't delete this we need it

    return frontier;
}
