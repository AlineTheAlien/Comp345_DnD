// 345_project.cpp : Defines the entry point for the console application.
// hello
// hello!!!!!!
//

#include "stdafx.h"
#include "Character.h"
#include <iostream>
using namespace std; 



int main()
{

	Character fighter = Character();
	
	fighter.displayAbilityScores(fighter);

	std::cout << fighter.rollSixSidedDie();

	std::cout << "   my first c++ program" << std::endl;
	getchar();
    return 0;
}
