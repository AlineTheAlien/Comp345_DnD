#include "MapPlay.h"
#include "ConsoleView.h"
#include <iostream>
using namespace std;

int main(void) {
	
	MapPlay *aMap = new MapPlay;
  
	ConsoleView *view1 = new ConsoleView(aMap);

	
	int ROW = 5;
	int COL = 10;
	//char p = p;
	
	aMap->fillCell(ROW, COL);

	return 0;
}