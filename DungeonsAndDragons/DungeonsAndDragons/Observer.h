//! @file 
//! @brief Header file for Observer class

#pragma once

//! Abstract class that implements an Observer
class Observer
{
public:
	~Observer();
	virtual void Update() = 0;
protected:
	Observer();
};

