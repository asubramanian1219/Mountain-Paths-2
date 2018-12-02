#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>
#include <string>
#include <fstream>
#include "functions.h"

using namespace std;

int getMax(vector<vector<int>> vec) {
	int max = vec.at(0).at(0);
	for (int r = 0; r < vec.size(); r++) {
		for (int c = 0; c < vec.at(r).size(); c++) {
			if (vec.at(r).at(c) > max)
				max = vec.at(r).at(c);

		}
	}
	return max;
}
int getMin(vector<vector<int>> vec) {
	int min = vec.at(0).at(0);
	for (int r = 0; r < vec.size(); r++) {
		for (int c = 0; c < vec.at(r).size(); c++) {
			if (vec.at(r).at(c) < min)
				min = vec.at(r).at(c);

		}
	}
	return min;
}
int findMin(vector<int> vec) {
	int index = 0;
	int min = vec.at(0);
	for (int i = 0; i < vec.size(); i++) {
		if (vec.at(i) < min) {
			min = vec.at(i);
			index = i;
		}
		
	}
	return index;
}


int main() {
	ifstream fileOpen;
	int numRows;
	int numCols;
	int num;
	int count = 0;
	int elements;
	string fileName;

	cout << "Enter the number of rows: " << endl;
	cin >> numRows;

	cout << "Enter the number of columns: " << endl;
	cin >> numCols;

	cout << "Enter the file name: " << endl;
	cin >> fileName;

	vector<vector<int>> heights(numRows, vector<int>(numCols));

	fileOpen.open(fileName);
	if (fileOpen.fail()) {
		cerr << "File does not exist. ";
	}
	else {
		while (!fileOpen.eof()) {
			fileOpen >> num;
			count++;
		}
		
		elements = numRows * numCols;
		if (elements > count) {
			cerr << "Unequal number of rows and columns." << endl;
		}
		else {

			fileOpen.clear();

			fileOpen.seekg(0, ios::beg);

			for (int r = 0; r<numRows; r++) {
				for (int c = 0; c < numCols; c++) {
					fileOpen >> num;
					heights.at(r).at(c) = num;


				}
			}
			int max = getMax(heights);
			int min = getMin(heights);
			double numerator;
			vector<vector<int>>shadesOfGray(numRows, vector<int>(numCols));
			double denom = max - min;
			for (int r = 0; r < numRows; r++) {
				for (int c = 0; c < numCols; c++) {
					numerator = (heights.at(r).at(c) - min)*255.0;
					shadesOfGray.at(r).at(c) = numerator / denom;
				}
			}
			vector<vector<int>>red = shadesOfGray;
			vector<vector<int>>green = shadesOfGray;
			vector<vector<int>>blue = shadesOfGray;

			vector<int> pathLengths;
			for (int i = 0; i < red.size(); i++) {
				pathLengths.push_back(colorPath(heights, red, green, blue, 252, 25, 63, i));
			}

			colorPath(heights, red, green, blue, 31, 253, 13, findMin(pathLengths));
			int minimum=findMin(pathLengths);
			string outputFileName = fileName + ".ppm";
			ofstream outputFile(outputFileName);
			if (!outputFile.is_open()) {
				cerr << "Error: File could not be opened";
			}

			outputFile << "P3" << endl;
			outputFile << numCols << " " << numRows << endl;
			outputFile << 255 << endl;

			for (int r = 0; r < red.size(); r++) {
				for (int c = 0; c < red.at(r).size(); c++) {
					outputFile << red.at(r).at(c) << " " << green.at(r).at(c) << " " << blue.at(r).at(c) << " ";

				}
				outputFile << endl;
			}
			outputFile.clear();



		}


	}
	system("pause");

}