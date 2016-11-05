#pragma once
#include <iostream>
#include <string>
#include "Observer.h"
#include "MapPlay.h"
using namespace std;

class ConsoleView : public Observer {
public:
	ConsoleView();
	ConsoleView(MapPlay* s);
	~ConsoleView();
	void update();
	void display();
private:
	const int ROWS = 20;
	const int COLS = 20;
	MapPlay *_subject;
};