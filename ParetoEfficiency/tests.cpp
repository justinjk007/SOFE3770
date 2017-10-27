#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <chrono>
#include <iostream>
#include "ConvexHull.hpp"
#include "Pareto.hpp"
#include "catch.hpp"

using namespace std;

TEST_CASE("Sample Test")  // Delete this
{
    int a = 1, b = 0;
    REQUIRE(b == 0);
    REQUIRE(a == Approx(1).epsilon(0.0001));  // Epsilon is tolerance
}

TEST_CASE("Check conversion methods")
{
    vector<Point> points        = {{0, 0}, {2, 2},  {3, 6},  {2, 10}, {6, 4}, {9, 2},
                            {9, 9}, {11, 5}, {11, 7}, {13, 6}, {14, 2}};
    vector<Point_2> cgal_points = changePointType(points);
    vector<Point> points_after  = changePointType(cgal_points);
}

TEST_CASE("Convex Hull")
{
    vector<Point> points   = {{0, 0}, {2, 2},  {3, 6},  {2, 10}, {6, 4}, {9, 2},
                            {9, 9}, {11, 5}, {11, 7}, {13, 6}, {14, 2}};
    vector<Point> hull_gen = getConvexHull(points);
    vector<Point> hull     = {{0, 0}, {14, 2}, {13, 6}, {9, 9}, {2, 10}};  // Correct hull

    REQUIRE(hull_gen == hull);
}

TEST_CASE("Testing Smallest Point identifier function")
{
    vector<Point> test = {{0, 0}, {9, 2}, {14, 2}, {13, 6}, {11, 7}, {9, 9}, {2, 10}};
    Point result       = pointSmallestXY(test);
    Point testResult(0, 0);

    REQUIRE(result == testResult);
}
