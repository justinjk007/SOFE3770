// sofe3770uAssign1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include "geometry.hpp"

using namespace std;

int main()
{
	// Declaring and Initializng variables
	int polygonVertices;
	vector<int> xPoints;
	vector<int> yPoints;

	/*
	Point a;
	cout << "The co-ordinates of a are " << a.x << " & " << a.y << "\n";
	cout << "Why are they both 0 GEORGE ?\n"; // Because the point object has a constructor that has default values.
											 // See here: http://sandbox.mc.edu/~bennet/cs220/codeex/cl0_cc.html
	*/

	cout << "Please enter the number of Vertices (3 < _ < 200): ";
	cin >> polygonVertices;
	// Error checking for incorrect input
	while (polygonVertices > 200 || polygonVertices < 3)
	{
		cout << "Please enter a valid number: ";
		cin >> polygonVertices;
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
		int xTemp;
		cin >> xTemp;
		xPoints.push_back(xTemp);
		if (xTemp > 1000000)
		{
			cout << "Error";
			cin >> xTemp;
		}
		int yTemp;
		cin >> yTemp;
		yPoints.push_back(yTemp);
		if (yTemp > 1000000)
		{
			cout << "Error";
			cin >> yTemp;
		}
	}



	// keeps window open
	int dummy;
	cin >> dummy; 
	
	return 0;
}

