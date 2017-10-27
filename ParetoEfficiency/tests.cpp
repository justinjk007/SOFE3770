#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <chrono>
#include <iostream>
#include "ConvexHull.hpp"
#include "Pareto.hpp"
#include "Plot.hpp"
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

TEST_CASE("Testing least dominant point")
{
    vector<Point> points = {{0, 0}, {2, 2},  {3, 6},  {2, 10}, {6, 4}, {9, 2},
                            {9, 9}, {11, 5}, {11, 7}, {13, 6}, {14, 2}};
    Point result         = pointSmallestXY(points);
    Point testResult(0, 0);

    // REQUIRE(result == testResult);
}

TEST_CASE("Testing Small X Large Y point function")
{
    vector<Point> points = {{0, 0}, {2, 2},  {3, 6},  {2, 10}, {6, 4}, {9, 2},
                            {9, 9}, {11, 5}, {11, 7}, {13, 6}, {14, 2}};
    Point result         = pointSmallestLargestXY(points);
    Point testResult(2, 10);

    // REQUIRE(result == testResult);
}

TEST_CASE("Testing Large X Small Y point function")
{
    vector<Point> points = {{0, 0}, {2, 2},  {3, 6},  {2, 10}, {6, 4}, {9, 2},
                            {9, 9}, {11, 5}, {11, 7}, {13, 6}, {14, 2}};
    Point result         = pointLargestSmallestXY(points);
    Point testResult(14, 2);

    // REQUIRE(result == testResult);
}

TEST_CASE("Testing Most dominant point")
{
    vector<Point> points = {{0, 0}, {2, 2},  {3, 6},  {2, 10}, {6, 4}, {9, 2},
                            {9, 9}, {11, 5}, {11, 7}, {13, 6}, {14, 2}};

    Point result = pointLargestXY(points);
    Point testResult(13, 6);

    // REQUIRE(result == testResult);
}

/**
 * I will add assertion here later when your methods are fixed.
 */
TEST_CASE("Testing Integration low low")
{
    cout << "Testing Integration low low\n";
    vector<Point> points = {{0, 0}, {2, 2},  {3, 6},  {2, 10}, {6, 4}, {9, 2},
                            {9, 9}, {11, 5}, {11, 7}, {13, 6}, {14, 2}};

    vector<Point> frontier = getParetoFrontierLL(points);
    print(frontier);
    draw(points, frontier);
}

TEST_CASE("Testing Integration high high")
{
    cout << "Testing Integration high high\n";
    vector<Point> points = {{0, 0}, {2, 2},  {3, 6},  {2, 10}, {6, 4}, {9, 2},
                            {9, 9}, {11, 5}, {11, 7}, {13, 6}, {14, 2}};

    vector<Point> frontier = getParetoFrontierHH(points);
    print(frontier);
    draw(points, frontier);
}

TEST_CASE("Testing Integration low high")
{
    cout << "Testing Integration low high\n";
    vector<Point> points = {{0, 0}, {2, 2},  {3, 6},  {2, 10}, {6, 4}, {9, 2},
                            {9, 9}, {11, 5}, {11, 7}, {13, 6}, {14, 2}};

    vector<Point> frontier = getParetoFrontierLH(points);
    print(frontier);
    draw(points, frontier);
}

TEST_CASE("Testing Integration high low")
{
    cout << "Testing Integration high low\n";
    vector<Point> points = {{0, 0}, {2, 2},  {3, 6},  {2, 10}, {6, 4}, {9, 2},
                            {9, 9}, {11, 5}, {11, 7}, {13, 6}, {14, 2}};

    vector<Point> frontier = getParetoFrontierHL(points);
    print(frontier);
    draw(points, frontier);
}

TEST_CASE("Sets of Point Vectors")
{
    // Set 1
    vector<int> uValues = {0, 12, 2, 5, 8, 12, 8, 4, 3, 10, 11, 6, 2, 4, 8, 10, 10, 3, 2, 6};
    vector<int> vValues = {0, 1, 2, 2, 2, 3, 4, 4, 5, 5, 6, 6, 8, 8, 8, 8, 10, 10, 12, 11};
    // convex hull values should be 0,0  12,1  12,3  11,6  10,10  6,11  2,12

    // Set 2
    vector<int> xValues = {0, 2, 2, 3, 4, 4, 4, 5, 6, 6, 6, 7, 8, 8, 8, 8, 9, 10, 10, 11};
    vector<int> yValues = {0, 5, 10, 8, 3, 6, 9, 7, 1, 5, 8, 7, 4, 6, 9, 10, 5, 2, 7, 3};
    // convex hull values should be 0,0  6,1  10,2  11,3  10,7  8,10  2,10

    // Set 3
    vector<int> aValues = {0, 1, 1, 2, 2, 2, 3, 3, 3, 3, 4, 4, 5, 5, 5, 5, 7, 8, 9, 10};
    vector<int> bValues = {0, 2, 4, 3, 5, 7, 1, 2, 4, 10, 3, 4, 1, 3, 6, 8, 5, 2, 8, 4};
    // convex hull values should be 0,0  3,1  5,1  8,2  10,4  9,8  5,8  3,10  2,7  1,4

    // Set 4
    vector<int> sValues = {0, 2, 2, 3, 3, 5, 5, 6, 6, 7, 7, 7, 7, 8, 8, 8, 9, 10, 10, 11};
    vector<int> tValues = {0, 9, 10, 2, 5, 5, 7, 4, 6, 3, 5, 7, 8, 3, 4, 5, 2, 3, 5, 2};
    // convex hull values should be 0,0  11,2  10,5  7,8  2,10
}
