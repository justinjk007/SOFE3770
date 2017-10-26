#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <chrono>
#include <iostream>
#include "Pareto.hpp"
#include "catch.hpp"

using namespace std;

TEST_CASE("Sample Test")  // Delete this
{
    int a = 1, b = 0;
    REQUIRE(b == 0);
    REQUIRE(a == Approx(1).epsilon(0.0001));  // Epsilon is tolerance
}

TEST_CASE("Testing PointOfBestFit")
{
    vector<Point> test = {{0, 0}, {9, 2}, {14, 2}, {13, 6}, {11, 7}, {9, 9}, {2, 10}};
    Point result       = pointOfBestFit(test);
    Point testResult(0, 0);

    REQUIRE(result == testResult);
}
