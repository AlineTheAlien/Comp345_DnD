#include "stdafx.h"
#include "GameLogger.h"


GameLogger::GameLogger()
{
}


GameLogger::~GameLogger()
{
}


void GameLogger::writeToLogFile(string text)
{
		ofstream myfile;
		myfile.open("GameLog.txt", std::ios_base::app);
		myfile << text << "\n";
		myfile.close();
}