#pragma once
#include "Subject.h"
#include <iostream>

class MapPlay : public Subject {
public: 
	MapPlay();
	~MapPlay();
	void fillCell(int row, int col);
	char getcMap(int row, int col); 
private:
	char cMap[20][20];
	const char PLAYER = 'P';
	//const char WALLS = 'W';
	const int ROWS = 20;
	const int COLS = 20;
};
