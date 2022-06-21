//History.cpp
#include <iostream>
#include "History.h"
//#include "globals.h"
//#include "Mesa.h"
using namespace std;

History::History(int nRows, int nCols) {  
	history_r = nRows;
	history_c = nCols;

	for (int i = 0; i < history_r; i++) {
		for (int j = 0; j < history_c; j++) {
			grid[i][j] = 0;
		}
	}
}

bool History::record(int r, int c) {
	if (r > history_r || c > history_c || r < 1 || c < 1) {
		return false;
	}
	grid[r - 1][c - 1] += 1; //not sure about this one
	return true;
}

void History::display() const {
	clearScreen();
	for (int i = 0; i < history_r; i++) {
		for (int j = 0; j < history_c; j++) {
			if (grid[i][j] == 0) {
				cout << '.';
			}
			else if (grid[i][j] >= 26) {
				cout << 'Z';
			}
			else {
				cout << char(grid[i][j] + 64);
			}
		}
		cout << endl;
	}
	cout << endl;
}
	