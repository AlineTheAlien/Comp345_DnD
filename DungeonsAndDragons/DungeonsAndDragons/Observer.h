//! @file 
//! @brief Header file for Observer class

#pragma once

//! Abstract class that implements an Observer
class Observer
{
public:
	~Observer();
	virtual void Update() = 0;
	virtual void UpdateGUI() = 0; // Since sharing the same observer classes for two different subjects. This one is for PlayGUI class.
protected:
	Observer();
};

