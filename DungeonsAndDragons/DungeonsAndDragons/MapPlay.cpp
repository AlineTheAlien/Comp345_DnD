//! @file 
//! @brief Implementation file for the MapPlay class  
//!

#include "MapPlay.h"

///default constructor creates a map
MapPlay::MapPlay() {
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			cMap[i][j] = ' ';
		}
	}
};

///default destructor
MapPlay::~MapPlay() {};

///method to modify a cell of the map 
void MapPlay::fillCell(int row, int col) {
	cMap[row][col] = PLAYER;
	///The Observable object notifies all its registered observers
	Notify();
};

char MapPlay::getcMap(int row, int col) {
	return cMap[row][col];
};