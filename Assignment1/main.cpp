// main.cpp : Defines the entry point for the console application.

#include <chrono>  // This is for measuring thread running time
#include <iostream>
#include <vector>
#include "geometry.hpp"

using namespace std;

int main()
{
    // Declaring and Initializng variables
    int polygon_Vertices;
    vector<int> x_Points;
    vector<int> y_Points;
    vector<Point> given_points;

    cout << "Please enter the number of Vertices (3 < _ < 200): ";
    cin >> polygon_Vertices;
    // Error checking for incorrect input
    while (polygon_Vertices > 200 || polygon_Vertices < 3) {
        cout << "Please enter a valid number: ";
        cin >> polygon_Vertices;
    }

    cout << "Enter the vertices co-ordinates starting with x then y ";
    cout << "for each pair in a counter-clockwise order. \n";
    cout << "Please enter integer pairs equal to or less than 10^6 separated by a space. \n";
    for (int count = 0; count < polygon_Vertices; count++) {
        int x_Temp;
        cin >> x_Temp;
        x_Points.push_back(x_Temp);
        if (x_Temp > 1000000) {
            cout << "Error";
            cin >> x_Temp;
        }
        int y_Temp;
        cin >> y_Temp;
        y_Points.push_back(y_Temp);
        if (y_Temp > 1000000) {
            cout << "Error";
            cin >> y_Temp;
        }
        // Populates vector with point objects using user defined x and y coordinates
        given_points.push_back(Point(x_Points[count], y_Points[count]));
    }

    auto start = chrono::high_resolution_clock::now();  // Start clock

    // Identify largest segment in polygon
    Segment result = getBiggestSegmentPossible(given_points);

    auto finish                      = chrono::high_resolution_clock::now();  // Stop clock
    chrono::duration<double> elapsed = finish - start;                        // Mesure time elapsed

    //	Output length and start/end points of largest segment
    cout << "Longest segment found: \n";
    cout << "Length: " << result.getLength() << "\n";
    cout << "Points: " << result.start << " -      " << result.end;
    cout << "\n------ Elapsed time: " << elapsed.count() << " s ------\n";

    vector<Segment> edges = generateEdges(given_points);
    writeToFile(edges, result);
    draw();

    return 0;
}
