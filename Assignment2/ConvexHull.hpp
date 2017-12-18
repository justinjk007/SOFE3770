#ifndef CONVEXHULL_HPP
#define CONVEXHULL_HPP

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/ch_graham_andrew.h> // Convex hull lib
#include <vector>
#include "Pareto.hpp"

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;

typedef K::Point_2 Point_2;

std::vector<Point> getConvexHull(const std::vector<Point>&); // n log n
std::vector<Point_2> changePointType(const std::vector<Point>&); // n
std::vector<Point> changePointType(const std::vector<Point_2>& points); // n
void print(const std::vector<Point>& points);//n

#endif /* CONVEXHULL_HPP */
