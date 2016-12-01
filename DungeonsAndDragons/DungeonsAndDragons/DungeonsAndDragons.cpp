//! @file 
//! @brief Driver file to create and execute the test suite and driver that defines the entry point for the console application.
//!
//! Brief instruction on how to set CppUnit:
//! from: http ://www.comp.nus.edu.sg/~cs3215/tools/cppunitAll.html
//!
//!	First, to install cppUnit :
//!
//!	 1. Unpack the CppUnit archive (https://sourceforge.net/projects/cppunit/files/cppunit/1.12.1/) to a directory of your choice, in this example I assume it is D:\. 
//!  2. Go to D:/cppunit-1.12.1/src and open the CppUnitLibraries.dsw in Visual Studio.
//!  3. Select the cppunit project in the Solution Explorer and go to 'Project > Properties > Configuration Properties > Librarian > General. Put "Debug\cppunit.lib" in the ‘Output File’ textbox. 
//!  4. Right-click on the cppunit project in the Solution Explorer pane and choose Build.
//!  5. After successful compilation, D:/cppunit-1.12.1/lib/cppunit.lib is produced which you then need to setup the Visual Studio Linker with (see below).

//!
//! To setup a project from scratch for Compilation / Linking:
//!
//!	  1. Activate 'Project > Properties > C/C++ >  Code Generation > Runtime Library > Multi - threaded Debug DLL'
//!	  2. Go to 'Project > Properties > C/C++ > General'. Put "D:\cppunit-1.12.1\include" in the 'Additional Include Directories' text box.
//!	  3. Go to 'Project > Properties > Linker > Input'. Put "D:\cppunit-1.12.1\lib\cppunit.lib" in the 'Additional Dependences' text box.
//!	  4. Go to 'Project > Properties > Build Events > Post-Build Event'. Put '"$(TargetPath)"' in the 'Command Line' textbox.Put 'Unit Tests...' in the 'Description' textbox.

#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include "stdafx.h"
#include "ItemContainer.h"
#include "CharacterObserver.h"
#include "Item.h"
#include "Character.h"
#include "Enhancement.h"
#include <Vector>
#include "Shield.h"
#include "Armor.h"
#include "Belt.h"
#include "Boots.h"
#include "Helmet.h"
#include "Ring.h"
#include "Weapon.h"
#include <ctime>
#include <iostream>
#include <fstream>
#include "MapObject.h"
#include <string>
#include "Launch.h"
#include "ContentBuilder.h"
#include "ConcreteContentBuilder.h"
// include headers that implement a archive in simple text format
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
using namespace std;

int main(int argc, char* argv[])
{
	srand(time(NULL));

	//// Get the top level suite from the registry
	//CppUnit::Test *suite = CppUnit::TestFactoryRegistry::getRegistry().makeTest();

	//// Adds the test to the list of test to run
	//CppUnit::TextUi::TestRunner runner;
	//runner.addTest(suite);

	//// Change the default outputter to a compiler error format outputter
	//runner.setOutputter(new CppUnit::CompilerOutputter(&runner.result(),
	//	std::cerr));
	//// Run the tests.
	//bool wasSuccessful = runner.run();

	//getchar();

	//// Return error code 1 if the one of test failed.
	//return wasSuccessful ? 0 : 1;

	
	Launch game;
	game.Start();
	return 0;
	
}