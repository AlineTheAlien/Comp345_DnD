#pragma once
#include <iostream>
#include <fstream>
#include <ostream>
#include <string>
using namespace std;

class GameLogger
{
public:
	GameLogger();
	~GameLogger();
	static void writeToLogFile(string);
};

