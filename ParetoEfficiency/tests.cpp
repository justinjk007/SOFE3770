#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <chrono>
#include <iostream>
#include "ConvexHull.hpp"
#include "Pareto.hpp"
#include "catch.hpp"
#include "Plot.hpp"

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

    Point result         = pointLargestXY(points);
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
    draw(points,frontier);
}

TEST_CASE("Testing Integration high high")
{
    cout << "Testing Integration high high\n";
    vector<Point> points = {{0, 0}, {2, 2},  {3, 6},  {2, 10}, {6, 4}, {9, 2},
                            {9, 9}, {11, 5}, {11, 7}, {13, 6}, {14, 2}};

    vector<Point> frontier = getParetoFrontierHH(points);
    print(frontier);
    draw(points,frontier);
}

TEST_CASE("Testing Integration low high")
{
    cout << "Testing Integration low high\n";
    vector<Point> points = {{0, 0}, {2, 2},  {3, 6},  {2, 10}, {6, 4}, {9, 2},
                            {9, 9}, {11, 5}, {11, 7}, {13, 6}, {14, 2}};

    vector<Point> frontier = getParetoFrontierLH(points);
    print(frontier);
    draw(points,frontier);
}

TEST_CASE("Testing Integration high low")
{
    cout << "Testing Integration high low\n";
    vector<Point> points = {{0, 0}, {2, 2},  {3, 6},  {2, 10}, {6, 4}, {9, 2},
                            {9, 9}, {11, 5}, {11, 7}, {13, 6}, {14, 2}};

    vector<Point> frontier = getParetoFrontierHL(points);
    print(frontier);
    draw(points,frontier);
}
