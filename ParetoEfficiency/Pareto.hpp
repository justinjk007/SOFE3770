#ifndef PARETO_HPP  // These are file guards (prevent compiler from including it multiple times).
#define PARETO_HPP

#include <iostream>
#include <vector>

using namespace std;

/*
 * This class is an implementation of the Point object with two constructors, one empty and one
 * requiring specific x and y values as parameters. Each object keeps track of its x and y
 * coordinates.
 */
class Point
{
   private:
    double x, y;

   public:
    // Defines os << operator for a Point object.
    friend ostream& operator<<(ostream& os, const Point&);
    // Defines == operator for a Point object.
    friend bool operator==(const Point&, const Point&);

    // Accessors to the private attributes
    double getX();
    double getY();

    // Empty/Default Constructor.
    Point()
    {
        this->x = 0;
        this->y = 0;
    }

    // Constructor with specified x and y coordinates.
    Point(double x_value, double y_value)
    {
        this->x = x_value;
        this->y = y_value;
    }
};

// Create list of Point objects from user input for manipulation.

vector<Point> populateList(vector<int> xValues, vector<int> yValues);

// Create sorted list by X value or by Y value respectively.

vector<Point> sortedPointList(vector<Point> all_points, char axis);

// Sort parameter identifiers for std::sort

bool compareByX(Point a, Point b);
bool compareByY(Point a, Point b);

// Identifies the point of best fit.

Point pointSmallestXY(vector<Point> convexHull);
Point pointLargestSmallestXY(vector<Point> convexHull);
Point pointSmallestLargestXY(vector<Point> convexHull);
Point pointLargestXY(vector<Point> convexHull);

#endif /* PARETO_HPP */
