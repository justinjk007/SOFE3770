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

TEST_CASE("Testing compareSegments()")
{
    Point a1;
    Point a2(2, 0);

    Point b1;
    Point b2(3, 0);

    Segment begin(a1, a2);
    Segment other(b1, b2);

    Segment ans = compareSegments(begin, other);

    REQUIRE(ans.getLength() == other.getLength());
}

TEST_CASE("Testing generateDiagonals()")
{
    std::vector<Point> square   = {{7, 4}, {29, 4}, {29, 26}, {7, 26}};
    std::vector<Point> pentagon = {{7, 4}, {29, 4}, {29, 26}, {22, 30}, {7, 26}};

    vector<Segment> diagonals1 = generateDiagonals(pentagon);
    vector<Segment> answer1    = {{
                                   {7, 4},
                                   {29, 26},
                               },
                               {
                                   {7, 4},
                                   {22, 30},
                               },
                               {
                                   {29, 4},
                                   {22, 30},
                               },
                               {
                                   {29, 4},
                                   {7, 26},
                               },
                               {{29, 26}, {7, 26}}};

    vector<Segment> diagonals2 = generateDiagonals(square);
    vector<Segment> answer2    = {{
                                   {7, 4},
                                   {29, 26},
                               },
                               {{29, 4}, {7, 26}}};

    REQUIRE(diagonals1 == answer1);
    REQUIRE(diagonals2 == answer2);
}

TEST_CASE("Checking intersection methods")
{
    vector<Point> pentagon    = {{7, 4}, {29, 4}, {29, 26}, {22, 30}, {7, 26}};
    vector<Segment> edges     = generateEdges(pentagon);
    vector<Segment> diagonals = generateDiagonals(pentagon);

    Segment dummy = {{0, 5}, {0, 10}};

    Segment single1 = {{-1, -2}, {3, 2}};
    Segment single2 = {{-3, -2}, {1, -2}};

    REQUIRE(doIntersect(single1, single2) == true);
    REQUIRE(doIntersect(edges.front(), diagonals) == false);
    REQUIRE(doIntersect(dummy, diagonals) == false);
}

TEST_CASE("Testing to see of the point is inside or outside the polygon")
{
    Point test2(10, 7);
    Point test1(0, 0);
    vector<Point> pentagon = {{7, 4}, {29, 4}, {29, 26}, {22, 30}, {7, 26}};
    vector<Point> square   = {{7, 4}, {29, 4}, {29, 26}, {7, 26}};

    bool ans1 = pointIsOutside(test2, square);
    bool ans2 = pointIsOutside(test1, pentagon);

    REQUIRE(ans2 == true);
    REQUIRE(ans1 == false);
}

TEST_CASE("Integration test")  // TODO
{
    /**
     * As per the assignment document
     * Answer1 should be 76.157731059
     * Answer2 should be 4510.149110617
     */
    std::vector<Point> input1 = {{0, 20}, {40, 0}, {40, 20}, {70, 50}, {50, 70}, {30, 50}, {0, 50}};
    std::vector<Point> input2 = {{0, 2017}, {-2017, -2017}, {2017, 0}};
}
