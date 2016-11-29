//! @file 
//! @brief Header file for the Dice class  
//!
//! 1) The rules of using the Dice in the game are:
//! The player first needs to choose the type of dice, the number of times he wants to roll it and his boost.
//! 2) In my design, the player can enter a string with spaces and it will still be accepted. First off, the player enter the dice string in the form of "xdy+z" following the game rules defined.
//! Next the program has a function isValid that takes the entered string and matches a regex pattern that follows the desired string format. This is done after parsing the stringt o remove any whitespace.
//! The roll function, which accepts the string "xdy+z" uses the isValid function firstly to validate the string, if invalid -1 is returned. 
//! If the string is valid, then the digits x, y, z are stored in a vector at there distinctive position following their order in th string.
//! The roll method then generates a random number for each dice roll (value x) and sums them all together and returns the total value summedd with the oprional z.
//! 3) No libraries were used.
#pragma once

#include <stdio.h>
#include <string>
#include <tchar.h>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <regex>
#include <sstream>
#include <algorithm>
#include <string.h>
#include <string>
#include <vector>

using namespace std;

//! class that implements the rolling of Dice 
class Dice
{
public:
	Dice();
	static int roll(string diceString);
	static bool isValid(string test);

private:
	//! variable to keep track of the total value after a roll
	int rollResult;
};