#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "geometry.hpp"

using namespace std;

TEST_CASE("Testing Euclidean distance method")
{
    Point a = {2,3};
    Point b = {3,3};

    Point c(7,8);
    Point d(13,4000);

    REQUIRE(getEuclideanDistance(a, b) == 1);
    REQUIRE(getEuclideanDistance(d, c) == Approx(3992.004509));
}
