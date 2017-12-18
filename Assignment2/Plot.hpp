#ifndef PLOT_HPP
#define PLOT_HPP

#include "Pareto.hpp"
using namespace std;

void writeToFile(vector<Point> points, vector<Point> frontier); // Don't call this
void draw(const vector<Point>& points, const vector<Point>& frontier); // Call this

#endif /* PLOT_HPP */
