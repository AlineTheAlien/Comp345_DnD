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
	virtual void NotifyGUI();
	int getNumberObservers();
	//list <Observer*> getObservers();
private:
	list <Observer*> *_observers;
};

