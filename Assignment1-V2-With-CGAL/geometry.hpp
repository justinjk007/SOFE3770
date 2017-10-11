#ifndef GEOMETRY_HPP  // These are file guards
#define GEOMETRY_HPP

#include <cmath>
#include <iostream>
#include <vector>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polygon_2.h>
#include <CGAL/Simple_cartesian.h>
#include <CGAL/algorithm.h>
#include <CGAL/bounding_box.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;

typedef K::FT FT;
typedef K::Point_2 Point;
typedef K::Segment_2 Segment;
typedef K::Iso_rectangle_2 Rect;
typedef CGAL::Polygon_2<K> Polygon_2;

using namespace std;

// George will implement these
Segment compareSegments(Segment, Segment);
std::vector<Segment> generateEdges(std::vector<Point>);
Segment findBiggestEdge(std::vector<Segment>);

// Justin will implement these
double getEuclideanDistance(Point, Point);
bool compareSeg(Segment, Segment);
std::vector<Segment> generateDiagonals(std::vector<Point>);
Segment findBiggestSegment(std::vector<Segment>);
int isLeft(Point, Point, Point);
bool pointIsOutside(Point, std::vector<Point>);
bool pointIsOutside(Point, Polygon_2);
bool isGoodDiagonal(Segment, std::vector<Segment>, std::vector<Point>);
Segment getBiggestSegmentPossible(std::vector<Point>);  // Everything integrated
void writeToFile(std::vector<Segment>, Segment);
double getLength(Segment);
Point getMidpoint(Segment);
void draw();

#endif /* GEOMETRY_HPP */
