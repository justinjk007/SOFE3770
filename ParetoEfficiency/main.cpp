#include <iostream>
#include <vector>
#include "Pareto.cpp"

using namespace std;

int main()
{
	// Declaring and initializing variables
	vector <int> uValues;
	vector <int> vValues;
	int sizeOfVectors;

	cout << "Size of vectors: ";
	cin >> sizeOfVectors;
	cout << "";
	// Asking for 'x' value vector
	cout << "Please enter the u values separated with a space: \n";
	int tempCounterX = 0;
	while (tempCounterX < sizeOfVectors)
	{
		int temp;
		cin >> temp;
		uValues.push_back(temp);
		tempCounterX++;
	}

	// Asking for 'y' value vector
	cout << "Please enter the v values separated with a space: \n";
	int tempCounterY = 0;
	while (tempCounterY < sizeOfVectors)
	{
		int temp;
		cin >> temp;
		vValues.push_back(temp);
		tempCounterY++;
	}

	// Creates Point objects from the given vectors.
	vector<Point> pointList = populateList(uValues, vValues);

	// Ask for which case user wants
	cout << "Case '1' - low u low v \n";
	cout << "Case '2' - low u high v \n";
	cout << "Case '3' - high u low v \n";
	cout << "Case '4' - high u high v \n";
	cout << "Please select which case you would like: ";
	int caseNum;
	cin >> caseNum;
	vector <Point> result;

	// Calls appropriate pareto front.
	if (caseNum == 1)
	{
		result = getParetoFrontierLL(pointList);
	}
	else if (caseNum == 2)
	{
		result = getParetoFrontierLH(pointList);
	}
	else if (caseNum == 3)
	{
		result = getParetoFrontierHL(pointList);
	}
	else if (caseNum == 4)
	{
		result = getParetoFrontierHH(pointList);
	}

	
    return 0;
}
