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

	fighter.displayAbilityScores(fighter);

	if (fighter.validateNewCharacter()) {
		std::cout << "\nThis character  is valid!" << endl;
	}
	else {
		std::cout << "\nThis character  is invalid!" << endl;
	}

	fighter.displayAbilityModifiers(fighter);

	// std::cout << fighter.rollSixSidedDie(); debbugging purposes

	//std::cout << "   my first c++ program" << std::endl; testing purposes

	getchar();
	return 0;
}

