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

	// std::cout << fighter.rollSixSidedDie();

	//std::cout << "   my first c++ program" << std::endl;

	getchar();
	return 0;
}

