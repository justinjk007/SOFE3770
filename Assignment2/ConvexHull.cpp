#include "ConvexHull.hpp"

using namespace std;

vector<Point> getConvexHull(const vector<Point>& raw_points)
{
    /**
     * Return the convex hull of the points given
     */

    vector<Point_2> points = changePointType(raw_points);
    vector<Point_2> raw_results;
    CGAL::ch_graham_andrew(points.begin(), points.end(), std::back_inserter(raw_results));  // Get convex hull
    vector<Point> result = changePointType(raw_results);
    return result;
}

std::vector<Point_2> changePointType(const std::vector<Point>& points)
{
    /**
     * Convert our Point type to cgal type Points so we use it with
     * CGAL methods
     */
    vector<Point_2> fixed_points;
    for (auto current : points) {
        double x = current.getX();
        double y = current.getY();
        Point_2 p(x, y);
        fixed_points.push_back(p);
    }

    return fixed_points;
}

std::vector<Point> changePointType(const std::vector<Point_2>& points)
{
    /**
     * Convert cgal type Points to our Point type so we use it with ou
     * functions
     */
    vector<Point> fixed_points;
    for (auto current : points) {
        double x = current.x();
        double y = current.y();
        Point p(x, y);
        fixed_points.push_back(p);
    }

    return fixed_points;
}


void print(const std::vector<Point>& points)
{
    /**
     * Print the given list
     */
    for (auto current : points) {
	cout << "Point ";
        cout << current.getX();
	cout << ", ";
        cout << current.getY();
	cout << "\n";
    }
}
