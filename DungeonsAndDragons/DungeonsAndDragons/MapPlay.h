//! @file 
//! @brief Cpp file for MapPlay class, which is the concrete subject in the observer design pattern
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
	//default map size
	char cMap[20][20];
	const char PLAYER = 'P';
	const int ROWS = 20;
	const int COLS = 20;
};
