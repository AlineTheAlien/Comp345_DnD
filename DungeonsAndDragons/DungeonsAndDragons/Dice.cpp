//! @file 
//! @brief Implementation file for Dice class

// Dice.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "Dice.h"

Dice::Dice() : rollResult(0)
{}

//! Checks if input string is syntatically valid
/// @param test : a string test that needs to be validated
/// @return true or false
bool Dice::isValid(string test)
{
	//remove all whitespaces, meaning a string such as "3    d    6    +  1" can be accepted
	test.erase(remove(test.begin(), test.end(), ' '), test.end());
	smatch narrowMatch;
	regex rx("^\\d+d([4|6|8]{1}|[1|2]{1}[0]{1}|[1]{1}[2]{1}|[1]{1}[0]{2})(([+]\\d+)?)$");
	//test if regex pattern is found in string test
	bool found = regex_match(test, narrowMatch, rx);
	return found;
}

//! Main funtion to roll the dice
/// @param diceString : string input containing dice info
/// @return result of the roll
int Dice::roll(string diceString)
{
	Dice myDice;
	myDice.rollResult = 0;
	//validate input string with previous function
	if (isValid(diceString)) {
		vector<int> arr;
		const std::regex r("[0-9]+");
		//if valid, store all thedigits from the string into a vector of size max 3, containing the values x, y, and optionally, z.
		for (std::sregex_iterator N(diceString.begin(), diceString.end(), r); N != std::sregex_iterator(); ++N)
		{
			std::stringstream SS(*N->begin());
			int Current = 0;
			SS >> Current;
			arr.push_back(Current);
		}

		for (int a = 0; a < arr[0]; a++) {
			//seed the random number generator
			//srand(static_cast<unsigned int>(time(0)));
			//generate random number between 1 and x, holding the second position in the vector 
			myDice.rollResult += (rand() % arr[1]) + 1;
		}

		//if z is specified
		if (arr.size() == 3) {
			myDice.rollResult += myDice.rollResult + arr[2];
		}
		return myDice.rollResult;
	}

	else
		return -1;
}