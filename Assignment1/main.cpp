// sofe3770uAssign1.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <vector>
#include "geometry.hpp"
#include <chrono> // This is for mesureing thread running time

using namespace std;

int main()
{
        auto start = chrono::high_resolution_clock::now(); // Start clock
	// Declaring and Initializng variables
	int polygon_Vertices;
	vector<int> x_Points;
	vector<int> y_Points;

	/*
	Point a;
	cout << "The co-ordinates of a are " << a.x << " & " << a.y << "\n";
	cout << "Why are they both 0 GEORGE ?\n"; // Because the point object has a constructor that has default values.
											 // See here: http://sandbox.mc.edu/~bennet/cs220/codeex/cl0_cc.html
	*/

	cout << "Please enter the number of Vertices (3 < _ < 200): ";
	cin >> polygon_Vertices;
	// Error checking for incorrect input
	while (polygon_Vertices > 200 || polygon_Vertices < 3)
	{
		cout << "Please enter a valid number: ";
		cin >> polygon_Vertices;
	}
	/*for (int xTemp, yTemp; cin >> xTemp >> yTemp;)
	{
		xPoints.push_back(xTemp);
		yPoints.push_back(yTemp);
	}*/
	cout << "Enter the vertices co-ordinates starting with x then y for each pair in a counter-clockwise order.";
	cout << "Please enter integers equal to or less than 10^6.";
	for (int count = 0; count < 7; count++)
	{
		int x_Temp;
		cin >> x_Temp;
		x_Points.push_back(x_Temp);
		if (x_Temp > 1000000)
		{
			cout << "Error";
			cin >> x_Temp;
		}
		int y_Temp;
		cin >> y_Temp;
		y_Points.push_back(y_Temp);
		if (y_Temp > 1000000)
		{
			cout << "Error";
			cin >> y_Temp;
		}
	}

	// Compare all sides of the polygon and determine largest of the sides


	// Compare each line segment withing the polygon skipping the first and last comparison (already compared as sides)
	//additionally, if a segment is larger than the current largest segment check for intersection.

	auto finish = chrono::high_resolution_clock::now(); // Stop clock
        chrono::duration<double> elapsed = finish - start; // Mesure time elapsed
        cout << "\n------ Elapsed time: " << elapsed.count() << " s ------\n";

	// keeps window open
	int dummy;
	cin >> dummy;

	return 0;
}
