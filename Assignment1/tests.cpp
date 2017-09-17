#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <iostream>
#include "catch.hpp"
#include "geometry.hpp"

using namespace std;

TEST_CASE("Testing EuclideanDistance()")
{
    Point a = {2, 3};
    Point b = {3, 3};

    Point c(7, 8);
    Point d(13, 4000);

    REQUIRE(getEuclideanDistance(a, b) == 1);
    REQUIRE(getEuclideanDistance(d, c) ==
            Approx(3992.004509).epsilon(0.0001));  // Epsilon is tolerance
}

TEST_CASE("Testing Segment::getLength()")
{
    Point c(7, 8);
    Point d(13, 4000);

    Segment line1(c, d);

    REQUIRE(line1.getLength() == Approx(3992.004509).epsilon(0.0001));  // Epsilon is tolerance
}
