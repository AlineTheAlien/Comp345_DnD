//! @file 
//! @brief Implementation file for the ConsoleView class  
//!

#include "ConsoleView.h"

/// default constructor
ConsoleView::ConsoleView() {
};

///Upon instantiation, attaches itself to a MapPlay
///@param s = a MapPlay instance
ConsoleView::ConsoleView(MapPlay* s) {
	_subject = s;
	_subject->Attach(this);
};

///Upon destruction, detaches itself from MapPlay
ConsoleView::~ConsoleView() {
	_subject->Detach(this);
};

///method to update the view as the changes are made by concrete subject, after being notified by the latter
void ConsoleView::Update() {
	display();
};

///method to print double array on console
void ConsoleView::display() {
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			cout << _subject->getcMap(i, j);
		}
		cout << endl;
	}
};