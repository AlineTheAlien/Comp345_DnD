//! @file 
//! @brief Header file for Concrete Map Observer class  
#pragma once
#include <iostream>
#include <string>
#include "Observer.h"
#include "MapPlay.h"
using namespace std;

//! Class that inherits from Observer 
class ConsoleView : public Observer {
public:
	ConsoleView();
	ConsoleView(MapPlay* s);
	~ConsoleView();
	void Update();
	void display();
private:
	const int ROWS = 20;
	const int COLS = 20;
	MapPlay *_subject;
};