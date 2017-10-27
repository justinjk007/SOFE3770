#include "Plot.hpp"
#include <cstdlib>  // For sys calls
#include <fstream>

void writeToFile(vector<Point> points, vector<Point> frontier)
{
    /**
     * Write the data to file
     */
    ofstream myfile;
    string file_name = "data.csv";
    myfile.open(file_name);
    myfile << "x,y\n";
    myfile << frontier.size() << "\n";  // Write the number of frontier points

    // Write frontier points
    auto it = frontier.begin();
    while (it != frontier.end()) {
        myfile << it->getX() << "," << it->getY() << "\n";
        ++it;
    }

    // Write all the points
    it = points.begin();
    while (it != points.end()) {
        myfile << it->getX() << "," << it->getY() << "\n";
        ++it;
    }

    myfile.close();
}

void draw(const vector<Point>& points, const vector<Point>& frontier)
{
    /**
     * Write the given data to file and invoke the python script to
     * plot them
     */
    writeToFile(points, frontier);
    cout << "\nDrawing polygon in matplotlib\n\n";
    system("python plot_lines.py");
}
