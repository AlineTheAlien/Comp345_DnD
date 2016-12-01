#include "stdafx.h"
#include "GameLogger.h"


GameLogger::GameLogger()
{
}


GameLogger::~GameLogger()
{
}


//! Implementation of writeToLogFile
//! @param : string value representing the text to write to the file
void GameLogger::writeToLogFile(string text)
{
		ofstream myfile;
		myfile.open("GameLog.txt", std::ios_base::app);
		myfile << text << "\n";
		myfile.close();
}