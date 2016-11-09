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
	int rollResult;
};