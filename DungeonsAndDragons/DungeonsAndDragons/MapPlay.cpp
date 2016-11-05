#include "stdafx.h"
#include "MapPlay.h"

MapPlay::MapPlay() {
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
				cMap[i][j] = ' ';
			}
		}
};

MapPlay::~MapPlay() {};

void MapPlay::fillCell(int row, int col) {
		cMap[row][col] = PLAYER;
		Notify();
};

char MapPlay::getcMap(int row, int col) {
	return cMap[row][col];
};