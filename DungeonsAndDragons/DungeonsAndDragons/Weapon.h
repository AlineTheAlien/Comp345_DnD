//! @file
//! @brief Header file for the Weapon class
//!

//! This class represents a specific Item type. It is a subclass of Weapon.
#ifndef WEAPON_H
#define WEAPON_H

#include "Item.h"

using namespace std;

//! Class for the implementation of a weapon
class Weapon : public Item
{
public:
	// Default constructor
	Weapon();
	// Constructor
	Weapon(string name, int attackBonus, int damageBonus);
	// Constructor taking a vector of enhancements as parameter
	Weapon(string name, vector<Enhancement> enhancements);
	// Overrided method to validate that the armor only enhances 'ATTACK BONUS' and 'DAMAGE BONUS'and verify that the bonus values are within [1..5]
	bool validateItem();

private:
	//! serialization
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & boost::serialization::base_object<Item>(*this);
		ar & type;
		ar & name;
		ar & enhancements;
	}
};

#endif