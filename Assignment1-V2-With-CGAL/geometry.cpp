#include "geometry.hpp"
#include <algorithm>
#include <cstdlib>
#include <fstream>

using namespace std;

double getEuclideanDistance(Point a, Point b)
{
    /**
     * This method returns the distance between two points.
     */
    double diff1    = a.x() - b.x();
    double diff2    = a.y() - b.y();
    double sum      = pow(diff1, 2) + pow(diff2, 2);
    double distance = sqrt(sum);
    return distance;
}

Segment compareSegments(Segment a, Segment b)
{
    /*
     * Returns the Segment object with the largest length.
     */
    if (getLength(a) >= getLength(b))
        return a;
    else
        return b;
}

bool compareSeg(Segment a, Segment b)
{
    /**
     * This was written for vector::sort
     */
    return (getLength(a) < getLength(b));
}

double getLength(Segment line)
{
    /**
     * Returns the length of the line given
     */
    double s_l = line.squared_length();  // Sqaured length of the line
    return sqrt(s_l);                    // Return length
}

Point getMidpoint(Segment line)
{
    /**
     * Returns the midpoint of this segment
     */
    int mx, my;
    mx = (int)(double)(line.source().x() + line.target().x()) /
         2;  // Calculate the mid-point of the line
    my = (int)(double)(line.source().y() + line.target().y()) / 2;

    Point point(mx, my);
    return point;
}

Segment findBiggestEdge(std::vector<Segment> all_edges)
{
    /**
     * Returns the biggest edge of the polygon as a segment object.
     */
    Segment current_biggest = all_edges[1];
    for (auto& segment : all_edges)  // access vector by reference to avoid copying
    {
        current_biggest = (compareSegments(current_biggest, segment));
    }
    return current_biggest;
}

std::vector<Segment> generateDiagonals(std::vector<Point> polygon)
{
    /**
     * Generate and return a list segments that represents all the
     * possible diagonals that can be generated from the given list of
     * points which make up the polygon. The points are expected to be
     * sorted counterclockwise and more than 3 in size(No diagonals
     * otherwise).
     */

    vector<Segment> diagonals;  // This will contain all the diagonals generated

    {
        // Generate diagonals from the first point of the polygon
        vector<Point>::iterator it1 = polygon.begin();
        Point point_one             = *it1;
        std::advance(it1, 2);  // Skip a point
        for (vector<Point>::iterator it2 = it1; it2 != polygon.end(); it2++) {
            Segment diagonal_line = {point_one, *it2};
            diagonals.push_back(diagonal_line);
        }
        diagonals.pop_back();  // Remove the last line it is an edge
    }
    {
        // This is for rest of the points in the polygon
        vector<Point>::iterator it1 = polygon.begin();
        for (it1 = ++it1; it1 != polygon.end(); it1++) {
            Point point_one                 = *it1;
            vector<Point>::iterator temp_it = it1;  // Temporarily store it until the target();
            if (++it1 != polygon.end())
                it1++;  // Skip a point
            else
                break;  // We are at the last point, all diagonals are made
            for (vector<Point>::iterator it2 = it1; it2 != polygon.end(); it2++) {
                Segment diagonal_line = {point_one, *it2};
                diagonals.push_back(diagonal_line);
            }
            it1 = temp_it;  // Reset it1 to its begining position
        }
    }

    return diagonals;
}

std::vector<Segment> generateEdges(std::vector<Point> all_points)
{
    vector<Segment> polygon;
    Point current = all_points[0];
    Point next;
    // Generates edges except for the last edge of the polygon
    for (int count = 1; count < all_points.size(); count++) {
        next = all_points[count];
        polygon.push_back(Segment(current, next));
        current = all_points[count];
    }
    // Creates the last segment (connects to starting point)
    next = all_points[0];
    polygon.push_back(Segment(current, next));
    return polygon;
}

bool pointIsOutside(Point point, Polygon_2 polygon)
{
    /**
     * Check if the given point is outside a polygon
     */
    CGAL::Bounded_side bside = polygon.bounded_side(point);
    if (bside == CGAL::ON_BOUNDED_SIDE) {
        // point inside
	return false;
    } else if (bside == CGAL::ON_BOUNDARY) {
        // point on the border
	return false;
    } else if (bside == CGAL::ON_UNBOUNDED_SIDE) {
        // point outside
	return true;
    }
    std::cout << "IT got here, this is bad ans should not happen\n";
    return false;
}

bool isGoodDiagonal(Segment segment, std::vector<Segment> checkable, std::vector<Point> polygon)
{
    /**
     * Check if the given segment intersects with any of the given lines
     */
    // Create cgal polygon
    Polygon_2 poly(polygon.begin(),polygon.end());

    for (auto& checking : checkable) {
        if (pointIsOutside(getMidpoint(segment), poly))
            return false;
        else if (checking.source() == segment.source() || checking.target() == segment.target() ||
                 checking.source() == segment.target() || checking.target() == segment.source())
            return false;  // Special case where the intersection is happening at the end/start
        else if (CGAL::do_intersect(checking, segment))
            return true;
        else
            return false;  // No intersections
    }
    return false;  // No intersections
}

Segment getBiggestSegmentPossible(std::vector<Point> points)
{
    /**
     * This method integrates all other method to find the biggest
     * line that can draw along a polygon.
     */                                                         // Big-O Analysis
    Segment biggest_line;                                       //	1 -constant time
    size_t num              = points.size();                    // Get the vectors size			//	1
    vector<Segment> polygon = generateEdges(points);            //	n
    biggest_line            = findBiggestEdge(polygon);         //	n
                                                                //	--
    if (num <= 2) {                                             //	1
        cout << "\nINVALID POLYGON\n";                          //	1
        exit(1);                                                //	1
    }                                                           //	--
    if (num == 3) {                                             //	1
        return biggest_line;                                    //	1
    }                                                           //	--
                                                                //	--
    vector<Segment> diagonals = generateDiagonals(points);      //	[n*(n-3)]/2
    std::sort(diagonals.begin(), diagonals.end(), compareSeg);  //	n log n
                                                                //	--
    while (diagonals.size() > 0) {                              //	[n*(n-3)]/2
        Segment current = diagonals.back();                     //	([n*(n-3)]/2) - 1
        diagonals.pop_back();                                   //	([n*(n-3)]/2) - 1
        if (!isGoodDiagonal(current, polygon, points)) {        //	([n*(n-3)]/2) - 1
            if (getLength(current) > getLength(biggest_line))
                return current;  //	([n*(n-3)]/2) - 1
        } else {                 //	--
            continue;            //	1
        }                        //	--
    }                            //	--
    return biggest_line;         //	1
}  // Final runtime: O(n^2)

void writeToFile(std::vector<Segment> polygon, Segment diagonal)
{
    /**
     * Write the lines list to file in raw, meaning the coordinates of
     * points of each line in the list.
     */
    ofstream myfile;
    string file_name = "rawData.csv";
    myfile.open(file_name);
    myfile << "x,y\n";
    // Write Diagonal
    myfile << diagonal.source().x() << "," << diagonal.source().y() << "\n";
    myfile << diagonal.target().x() << "," << diagonal.target().y() << "\n";

    // Write edges of the polygon
    vector<Segment>::iterator it = polygon.begin();
    while (it != polygon.end()) {
        myfile << it->source().x() << "," << it->source().y() << "\n";
        myfile << it->target().x() << "," << it->target().y() << "\n";
        ++it;
    }
    myfile.close();
}

void draw()
{
    /**
     * Draw the polygon and the diagonal using mat plot lib and hacked up code ran using system()
     */
    cout << "\nDrawing polygon in matplotlib\n";
    system("python plot_lines.py");
}
