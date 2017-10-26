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
