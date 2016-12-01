//! @file 
//! @brief Header file for Subject class

#pragma once
#include "Observer.h"
#include <list>
using namespace std;

//! Abstract class that implements a Subject
class Subject
{
public:
	Subject();
	~Subject();
	virtual void Attach(Observer* o);
	virtual void Detach(Observer* o);
	virtual void Notify();
	virtual void NotifyGUI(); // Since sharing the same observer classes for two different subjects. This one is for PlayGUI class.
	int getNumberObservers();
	//list <Observer*> getObservers();
private:
	list <Observer*> *_observers;
};

