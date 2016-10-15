// 345_project.cpp : Defines the entry point for the console application.
// hello
// hello!!!!!!
//

#include "stdafx.h"
#include "Character.h"
#include <iostream>
#include <ctime>
using namespace std;


int main()
{
	//Initializes the seed used for the random dice rolls
	srand(time(NULL));

	Character fighter = Character();

	// Character fighter2 = Character(10, 9, 8, 7, 6, 5); testing

	fighter.displayCharacterInfo();

	if (fighter.validateNewCharacter()) {
		std::cout << "\nThis character  is valid!\n\n" << endl;
	}
	else {
		std::cout << "\nThis character  is invalid!\n\n" << endl;
	}

	// std::cout << "\n\nTest ability modifier is:" << fighter.generateAbilityModifier(3);  for testing purpose, make test case to test the lowest possible dice roll

	// std::cout << fighter.rollSixSidedDie(); debbugging purposes

	getchar();
	return 0;
}

