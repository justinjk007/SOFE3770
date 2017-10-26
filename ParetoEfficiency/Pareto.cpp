#include "Pareto.hpp"
#include <algorithm>
#include <vector>

using namespace std;

/*
 * Method used to access private attribute of a Point object.
 */
int Point::getX()
{
    return this->x;
}

/*
 * Method used to access private attribute of a Point object.
 */
int Point::getY()
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
 * Description
 */
Point pointOfBestFit(vector<Point> convexHull)
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
