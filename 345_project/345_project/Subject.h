#pragma once
#include "Observer.h"
#include <list>
using namespace std;

class Subject
{
public:
	Subject();
	~Subject();
	virtual void Attach(Observer* o);
	virtual void Detach(Observer* o);
	virtual void Notify();
private:
	list <Observer*> *_observers;
};

