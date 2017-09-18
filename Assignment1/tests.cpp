#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <iostream>
#include "catch.hpp"
#include "geometry.hpp"

using namespace std;

TEST_CASE("Testing EuclideanDistance()")
{
	Point a = { 2, 3 };
	Point b = { 3, 3 };

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
	double test_length = getEuclideanDistance(c, d);

	Segment line1(c, d, test_length);

	REQUIRE(line1.getLength() == Approx(3992.004509).epsilon(0.0001));  // Epsilon is tolerance
}

TEST_CASE("Testing compareSegments()")
{
	Point a1;
	Point a2(2, 0);

	Point b1;
	Point b2(3, 0);

	double test_length_a = getEuclideanDistance(a1, a2);
	double test_length_b = getEuclideanDistance(b1, b2);

	Segment begin(a1, a2, test_length_a);
	Segment other(b1, b2, test_length_b);

	Segment ans = compareSegments(begin, other);

	REQUIRE(ans.getLength() == other.getLength());
}