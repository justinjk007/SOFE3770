#ifndef GEOMETRY_HPP  // These are file guards
#define GEOMETRY_HPP


class Point
{
   public:
    double x;
    double y;
    Point()
    {
	/**
	 * This is the default constructor
	 */
        this->x = 0.0;
        this->y = 0.0;
    }
    Point(double x_cord, double y_cord)
    {
	/**
	 * This constructor creates objects with the values passed on
	 */
        this->x = x_cord;
        this->y = y_cord;
    }
};

// Make Line class here.

// Add method declarations(prototypes) here. For example
double getEuclideanDistance (Point, Point); // Implementations are in geometry.cpp

#endif /* GEOMETRY_HPP */
