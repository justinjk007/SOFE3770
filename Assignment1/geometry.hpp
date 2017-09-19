#ifndef GEOMETRY_HPP  // These are file guards
#define GEOMETRY_HPP

#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

class Point
{
   public:
    int x;
    int y;
    friend ostream& operator<<(ostream& os, const Point&);  // define os << operator for point
    friend bool operator==(const Point&, const Point&);     // Defines == for Point
    Point()
    {
        /**
         * This is the default constructor
         */
        this->x = 0;
        this->y = 0;
    }
    Point(int x_cord, int y_cord)
    {
        /**
         * This constructor creates objects with the values passed in
         */
        this->x = x_cord;
        this->y = y_cord;
    }
};

// Make Line class here.
class Segment
{
   private:
    double length;

   public:
    Point start;
    Point end;
    double getLength();                                       // Returns the length of the line
    Point getMidpoint();
    friend ostream& operator<<(ostream& os, const Segment&);  // define os << operator for Segment
    friend bool operator==(const Segment&, const Segment&);   // Defines == for Segment
    Segment()
    {
        Point default_set = {0, 0};
        this->start       = default_set;
        this->end         = default_set;
        this->length      = 0;
    }
    Segment(Point a, Point b)
    {
        this->start  = a;
        this->end    = b;
        double diff1 = a.x - b.x;
        double diff2 = a.y - b.y;
        double sum   = pow(diff1, 2) + pow(diff2, 2);
        this->length = sqrt(sum);
    }
};

// George will implement these
Segment compareSegments(Segment a, Segment b);
std::vector<Segment> generateEdges(std::vector<Point>);
Segment findBiggestEdge(std::vector<Segment> all_edges);

// Justin will implement these
double getEuclideanDistance(Point, Point);
std::vector<Segment> generateDiagonals(std::vector<Point>);
Segment findBiggestSegment(std::vector<Segment>);
bool onSegment(Point, Point, Point);
int orientation(Point, Point, Point);
int isLeft(Point, Point, Point);
bool pointIsOutside(Point, std::vector<Point>);
bool doIntersect(Segment, Segment);
bool doIntersect(Segment, std::vector<Segment>, std::vector<Point>);
Segment getBiggestSegmentPossible(std::vector<Point>); // Everything integrated

#endif /* GEOMETRY_HPP */
