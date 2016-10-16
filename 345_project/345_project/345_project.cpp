// 345_project.cpp : Defines the entry point for the console application.
// hello
// hello!!!!!!
//

#include "stdafx.h"
#include "Character.h"
#include <iostream>
#include <ctime>
#include <string>
using namespace std;


int main()
{
	//Initializes the seed used for the random dice rolls
	srand(time(NULL));

	Character fighter = Character();
	fighter.displayCharacterInfo();
	fighter.displayEquipment();

	if (fighter.validateNewCharacter()) {
		std::cout << "\nThis character  is valid!\n\n" << endl;
	}
	else {
		std::cout << "\nThis character  is invalid!\n\n" << endl;
	}

	// std::cout << "\n\nTest ability modifier is:" << fighter.generateAbilityModifier(3);  for testing purpose, make test case to test the lowest possible dice roll
	// std::cout << fighter.rollSixSidedDie(); debbugging purposes

	string equips[6] = { "Heavy Armor", "Silver Shield", "Crystal Longsword", "Leather Boots", "Saphire Ring", "Brass Helmet" };
	Character fighter2 = Character(equips, 5, 500, 17, 16, 13, 9, 9, 10);
	fighter2.displayCharacterInfo();
	fighter2.displayEquipment();

	if (fighter.validateNewCharacter()) {
		std::cout << "\nThis character  is valid!\n\n" << endl;
	}
	else {
		std::cout << "\nThis character  is invalid!\n\n" << endl;
	}

	getchar();
	return 0;
}

