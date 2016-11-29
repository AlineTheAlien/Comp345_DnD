//! @file 
//! @brief Implementation file for Subject class

#include "stdafx.h"
#include "Subject.h"
#include "Observer.h"

//! Default constructor for Subject
//! On instantiation, creates a new list of observers as one subject can have many observers
Subject::Subject()
{
	_observers = new list<Observer*>;
}

//! Destructor for Subject
//! When called, deletes the list of observers that was previously instantiated 
Subject::~Subject()
{
	delete _observers;
}

//! Attach function that attaches an observer to the subject
//! @param o: Pointer to an object with supertype Observer
void Subject::Attach(Observer* o) {
	_observers->push_back(o);
};

//! Detach function that removes observer referenced by the parameter from the list of the Subject's observers
//! @param o: Pointer to an object with supertype Observer
void Subject::Detach(Observer* o) {
	_observers->remove(o);
};

//! Notify function that triggers an update for every observer that is attached to the subject
void Subject::Notify() {
	list <Observer *>::iterator i = _observers->begin();
	for (; i != _observers->end(); ++i) {
		(*i)->Update();
	}
}

//! Notify function that triggers an update for every observer that is attached to the subject
void Subject::NotifyGUI() {
	list <Observer *>::iterator i = _observers->begin();
	for (; i != _observers->end(); ++i) {
		(*i)->UpdateGUI();
	}
}

//! For debugging purposes, returns the number of observers attached to the calling subject
//! return int, number of observers in the list of observers of a given subject
int Subject::getNumberObservers() {
	int ctr = 0;
	list <Observer *>::iterator i = _observers->begin();
	for (; i != _observers->end(); ++i) {
		ctr++;
	}
	return ctr;
}

