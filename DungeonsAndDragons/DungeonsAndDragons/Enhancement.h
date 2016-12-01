//! @file 
//! @brief Header file for the Enhancement class  
//!

/**!
1) Game rules:
- An item may enhance the following character's characteristics: 'STRENGTH', 'DEXTERITY'
'CONSTITUTION', 'INTELLIGENCE', 'WISDOM', 'CHARISMA', 'ARMOR CLASS', 'ATTACK BONUS' and 'DAMAGE BONUS'.
- The type of the enhancement as well as the bonus value should be obtainable in order to apply it to
the character's statistics.
2) Design:
- An Enhancement object represents one character statistic that an item can influence, along with the
bonus value, ranging from +1 to +5.
- Each Enhancement object can be added to an item, by adding it to the item's list of enhancements (a vector)
via a method inside the Item class.
- The class contains methods to access the stats type and the bonus value of an Enhancement object.
3) Libraries:
- Standard libraries were used.
- Boost was used for serialization.
- In the .cpp file, iostream was included to output strings to the stream. Enhancements and their bonus can be easily displayed to the stream.
**/

#ifndef ENHANCEMENT_H
#define ENHANCEMENT_H
// include headers that implement a archive in simple text format
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

#include <string>

using namespace std;

//! Class for the implementation of an enhancement, i.e. a stat influenced by an item, as well as the bonus it gives
class Enhancement
{
private:
	string type;
	int bonus;
	// Serialization
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & type;
		ar & bonus;
	}

public:
	// Default constructor
	Enhancement();
	// Constructor
	Enhancement(string, int);
	// Method to get the enhancement type of the item
	string getType();
	// Method to get the bonus of the enhancement
	int getBonus();
	// Method to set the bonus of the enhancement
	void setBonus(int);

};

#endif