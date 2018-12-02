#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>
#include <string>
#include <fstream>
#include <cmath>
#include "functions.h"

using namespace std;

int colorPath(const vector<vector<int>>& heightMap, vector<vector<int>>& r, vector<vector<int>>& g, vector<vector<int>>& b, int color_r, int color_g, int color_b, int start_row) {
	int pathLength = 0;
	int elevChange1;
	int elevChange2;
	int elevChange3;
	int row = start_row;
	int col = 0;

	r.at(start_row).at(0) = color_r;
	g.at(start_row).at(0) = color_g;
	b.at(start_row).at(0) = color_b;
	
	
	while (col < heightMap.at(0).size()-1) {
		if ((row == 0 )) {
			elevChange1 = abs(heightMap.at(row).at(col) - heightMap.at(row).at(col + 1));
			elevChange2 = abs(heightMap.at(row).at(col) - heightMap.at(row + 1).at(col + 1));
			if (elevChange1 <= elevChange2) {
				col++;
				pathLength += elevChange1;
			}
			else {
				row++;
				col++;
				pathLength += elevChange2;
			}

		}
		else if (row == heightMap.size()-1) {
			elevChange1 = abs(heightMap.at(row).at(col) - heightMap.at(row - 1).at(col + 1));
			elevChange2 = abs(heightMap.at(row).at(col) - heightMap.at(row).at(col + 1));
			if (elevChange1 < elevChange2) {
				row--;
				col++;
				pathLength += elevChange1;
			}
			else {
				col++;
				pathLength += elevChange2;
			}
		}
		else {
			elevChange1= abs(heightMap.at(row).at(col) - heightMap.at(row - 1).at(col + 1));
			elevChange2 = abs(heightMap.at(row).at(col) - heightMap.at(row).at(col + 1));
			elevChange3 = abs(heightMap.at(row).at(col) - heightMap.at(row+1).at(col + 1));
			if ((elevChange1 < elevChange2) && (elevChange1 < elevChange3)) {
				row--;
				col++;
				pathLength += elevChange1;

			}
			else if ((elevChange3 < elevChange2) && (elevChange3 < elevChange1)) {
				row++;
				col++;
				pathLength += elevChange3;

			}
			else if (((elevChange2 < elevChange1) && (elevChange2 < elevChange3)) || ((elevChange2 == elevChange1) && (elevChange2 <= elevChange3)) || ((elevChange2 == elevChange3) && (elevChange2 <= elevChange1))) {
				col++;
				pathLength += elevChange2;
			}
			else if ((elevChange1 == elevChange3) && (elevChange1 < elevChange2)) {
				row++;
				col++;
				pathLength += elevChange3;
			}
				
		}
		r.at(row).at(col) = color_r;
		g.at(row).at(col) = color_g;
		b.at(row).at(col) = color_b;
		

	}
	return pathLength;
}