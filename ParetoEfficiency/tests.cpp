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
