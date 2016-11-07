//! @file 
//! @brief Implementation file for the Item class  
//!

#include "stdafx.h"
#include "Enhancement.h"
#include <iostream>

using namespace std;
// Default constructor
Enhancement::Enhancement()
{
	type = "";
	bonus = 0;
}

//! Constructor that takes an item type as a string and a bonus value as an int
//! @param type : Type of the item
//! @param bonus : Bonus given by the item [1..5]
Enhancement::Enhancement(string type, int bonus)
{
	if (bonus >= 1 && bonus <= 5)
	{
		this->type = type;
		this->bonus = bonus;
	}
	else
	{
		cout << "Enhancement bonus can only be between 1 and 5 inclusive." << endl;
		cout << "(For demo purpose, no error occurs when instantiating an invalid item)" << endl;
	}
}

//! Method to get the enhancement type of the item
//! @return Type of the enhancement
string Enhancement::getType()
{
	return type;
}

//! Method to get the bonus of the enhancement
//! @return Enhancement bonus given by the item
int Enhancement::getBonus()
{
	return bonus;
}