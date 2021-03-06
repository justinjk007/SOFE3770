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
    double diff1    = a.x - b.x;
    double diff2    = a.y - b.y;
    double sum      = pow(diff1, 2) + pow(diff2, 2);
    double distance = sqrt(sum);
    return distance;
}

std::ostream& operator<<(std::ostream& os, const Point& point)
{
    /**
     * Implements the output operator for the Point class.
     */
    os << "(" << point.x << ',' << point.y << ")" << endl;
    return os;
}

std::ostream& operator<<(std::ostream& os, const Segment& segment)
{
    /**
     * Implements the output operator for the Segment class.
     */
    os << "(" << segment.start.x << ',' << segment.start.y << ")";
    os << " ------ ";
    os << "(" << segment.end.x << ',' << segment.end.y << ")" << endl;
    return os;
}

bool operator==(const Point& one, const Point& two)
{
    if (one.x == two.x && one.y == two.y) return true;
    return false;
}

bool operator==(const Segment& one, const Segment& two)
{
    if (one.start == two.start && one.end == two.end)
        return true;
    else if (one.start == two.end && one.end == two.start)
        return true;
    return false;
}

Segment compareSegments(Segment a, Segment b)
{
    /*
     * Returns the Segment object with the largest length.
     */
    if (a.getLength() >= b.getLength())
        return a;
    else
        return b;
}

bool compareSeg(Segment a, Segment b)
{
    /**
     * This was written for vector::sort
     */
    return (a.getLength() < b.getLength());
}

double Segment::getLength()
{
    /**
     * Returns the length of the line given
     */
    return this->length;
}

Point Segment::getMidpoint()
{
    /**
     * Returns the midpoint of this segment
     */
    int mx, my;
    mx = (int)(double)(this->start.x + this->end.x) / 2;  // Calculate the mid-point of the line
    my = (int)(double)(this->start.y + this->end.y) / 2;

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
            vector<Point>::iterator temp_it = it1;  // Temporarily store it until the end;
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

//===================================================================
// a Point is defined by its coordinates {int x, y;}

int isLeft(Point P0, Point P1, Point P2)
{
    /**
     *isLeft(): tests if a point is Left|On|Right of an infinite line.
     */
    return ((P1.x - P0.x) * (P2.y - P0.y) - (P2.x - P0.x) * (P1.y - P0.y));
}

bool pointIsOutside(Point P, std::vector<Point> polygon)
{
    /**
     * Crossing number test to see if the given point lines inside the polygon.
     * This code is patterned after [Franklin, 2000]
     */
    int cn = 0;  // the  crossing number counter

    for (auto V = polygon.begin(); V < polygon.end() - 1; ++V) {
        if (((V[0].y <= P.y) && (V[1].y > P.y))        // an upward cross0ng
            || ((V[0].y > P.y) && (V[1].y <= P.y))) {  // a downward cross0ng
            // compute  the actual edge-ray intersect x-coordinate
            float vt = (float)(P.y - V[0].y) / (V[1].y - V[0].y);
            if (P.x < V[0].x + vt * (V[1].x - V[0].x))  // P.x < 0ntersect
                ++cn;                                   // a valid crossing of y=P.y right of P.x
        }
    }

    // 0 if even (out), and 1 if  odd (in)
    if ((cn & 1) == 0) return true;
    return false;
}

bool onSegment(Point p, Point q, Point r)
{
    /**
     * Check if point r is on the line segment made by point p and q.
     */
    if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) && q.y <= max(p.y, r.y) &&
        q.y >= min(p.y, r.y))
        return true;
    return false;
}

int orientation(Point p, Point q, Point r)
{
    /**
     * To find orientation of ordered triplet (p, q, r).
     * The function returns following values
     * 0 --> p, q and r are colinear
     * 1 --> Clockwise
     * 2 --> Counterclockwise
     */
    int val = (int)(double)(q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    // Cast explicitly without warnings
    if (val == 0) return 0;    // colinear
    return (val > 0) ? 1 : 2;  // clock or counterclock wise
}

bool doIntersect(Segment a, Segment b)
{
    /**
     * Find the four orientations needed for general and special
     * cases, and returns true if the line segments intersect.
     */
    Point p1 = a.start;
    Point q1 = a.end;
    Point p2 = b.start;
    Point q2 = b.end;

    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    // General case
    if (o1 != o2 && o3 != o4) return true;
    // Special Cases
    // p1, q1 and p2 are colinear and p2 lies on segment p1q1
    if (o1 == 0 && onSegment(p1, p2, q1)) return true;
    // p1, q1 and p2 are colinear and q2 lies on segment p1q1
    if (o2 == 0 && onSegment(p1, q2, q1)) return true;
    // p2, q2 and p1 are colinear and p1 lies on segment p2q2
    if (o3 == 0 && onSegment(p2, p1, q2)) return true;
    // p2, q2 and q1 are colinear and q1 lies on segment p2q2
    if (o4 == 0 && onSegment(p2, q1, q2)) return true;
    return false;  // Doesn't fall in any of the above cases
}

bool isGoodDiagonal(Segment segment, std::vector<Segment> checkable, std::vector<Point> polygon)
{
    /**
     * Check if the given segment intersects with any of the given lines
     */
    for (auto& checking : checkable) {
        if (pointIsOutside(segment.getMidpoint(), polygon))
            return true;
        else if (checking.start == segment.start || checking.end == segment.end ||
                 checking.start == segment.end || checking.end == segment.start)
            return false;  // Special case where the intersection is happening at the end/start
        else if (doIntersect(checking, segment))
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
     */																			// Big-O Analysis
    Segment biggest_line;														//	1 -constant time
    size_t num              = points.size();  // Get the vectors size			//	1
    vector<Segment> polygon = generateEdges(points);							//	n
    biggest_line            = findBiggestEdge(polygon);							//	n	
																				//	--
    if (num <= 2) {																//	1
        cout << "\nINVALID POLYGON\n";											//	1
        exit(1);																//	1
    }																			//	--
    if (num == 3) {																//	1
        return biggest_line;													//	1
    }																			//	--
																				//	--
    vector<Segment> diagonals = generateDiagonals(points);						//	[n*(n-3)]/2
    std::sort(diagonals.begin(), diagonals.end(), compareSeg);					//	n log n
																				//	--
    while (diagonals.size() > 0) {												//	[n*(n-3)]/2
        Segment current = diagonals.back();										//	([n*(n-3)]/2) - 1
        diagonals.pop_back();													//	([n*(n-3)]/2) - 1
        if (!isGoodDiagonal(current, polygon, points)) {						//	([n*(n-3)]/2) - 1
            if (current.getLength() > biggest_line.getLength()) return current;	//	([n*(n-3)]/2) - 1
        } else {																//	--
            continue;															//	1
        }																		//	--
    }																			//	--
    return biggest_line;														//	1
}																				// Final runtime: O(n^2)

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
    myfile << diagonal.start.x << "," << diagonal.start.y << "\n";
    myfile << diagonal.end.x << "," << diagonal.end.y << "\n";

    // Write edges of the polygon
    vector<Segment>::iterator it = polygon.begin();
    while (it != polygon.end()) {
        myfile << it->start.x << "," << it->start.y << "\n";
        myfile << it->end.x << "," << it->end.y << "\n";
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
