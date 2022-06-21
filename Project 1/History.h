//history.h
#ifndef HISTORY_
#define HISTORY_
#include "globals.h"

class Mesa;

class History {
public:
	History(int nRows, int nCols);
	bool record(int r, int c);
	void display() const;

private:
	Mesa* history_mesa;
	int grid[MAXROWS][MAXCOLS];
	int history_r;
	int history_c;
};

#endif