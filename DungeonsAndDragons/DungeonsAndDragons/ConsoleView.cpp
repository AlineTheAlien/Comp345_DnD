#include "stdafx.h"
#include "ConsoleView.h"

ConsoleView::ConsoleView() {
};

ConsoleView::ConsoleView(MapPlay* s) {
	_subject = s;
	_subject->Attach(this);
};

ConsoleView::~ConsoleView() {
	_subject->Detach(this);
};

void ConsoleView::Update() {
	//fix this and
	//MapPlay aMap;
	display();
};

void ConsoleView::display() {
	//this
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			cout << _subject->getcMap(i,j);
		}
		cout << endl;
	}
};