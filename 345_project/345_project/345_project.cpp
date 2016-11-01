//! @file 
//! @brief Entry point for the console application

#include "stdafx.h"
#include "Character.h"
#include <iostream>
#include <ctime>
#include <string>
using namespace std;
#include "HealthBar.h"
#include "SFML/Graphics.hpp"

#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>


int main()
{
	sf::RenderWindow window(sf::VideoMode(660, 1100), "Kirby practice");
	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);

	sf::Texture background;
	if (!background.loadFromFile("Images/Floor.png")) {
		//window.close();
	}
	background.setRepeated(true); // repeat tile over sprite height

	//Initializes the seed used for the random dice rolls
	std::srand(time(NULL));

	//Displaying default constructor...
	Character fighter = Character();
	fighter.displayCharacterInfo();
	fighter.displayEquipment();

	if (fighter.validateNewCharacter()) {
		std::cout << "\nThis character  is valid!\n\n" << endl;
	}
	else {
		std::cout << "\nThis character  is invalid!\n\n" << endl;
	}

	sf::Texture kirby;
	if (!kirby.loadFromFile("Images/Kirby.png")) {
		//window.close();
	}

	sf::Sprite bg(background);
	bg.setPosition(0, 0);
	bg.setTexture(background);
	bg.setTextureRect(sf::IntRect(0, 0, 660, 660));

	sf::Sprite sprite(kirby);
	sprite.setPosition(0, 0);


	while (window.isOpen()) {
		sf::Event event;

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::EventType::Closed)
			{
				window.close();
			}

			if (event.type == sf::Event::EventType::KeyPressed)
			{
				// Event driven input handling
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
					sprite.move(-30, 0);
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
					sprite.move(30, 0);
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
					sprite.move(0, -30);
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
					sprite.move(0, 30);
			}
		}
		// Polled input handling -- mouse coordinates are in screen space, not window space
		//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		//	sprite.setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));//Absolute transform

		window.clear(sf::Color::Black);
		window.draw(bg);
		window.draw(sprite);
		HealthBar(window, fighter);
		//window.display();
		window.display();

	}


	/*
	//Displaying nondefault constructor...
	Character fighter2 = Character(17, 16, 13, 9, 9, 10);
	fighter2.displayCharacterInfo();
	fighter2.displayEquipment();

	if (fighter.validateNewCharacter()) {
		std::cout << "\nThis character  is valid!\n\n" << endl;
	}
	else {
		std::cout << "\nThis character  is invalid!\n\n" << endl;
	}
	*/


	getchar();
	return 0;
}


//All code below this is the main function to run the test cases
//Code should be uncommented to be executed, and the driver's main function should be commented

/*

//! main() function. Entry point of the program
//! It does the following:
//! 1. Create a test suite object from the registry as populated by the code in the Test Classes
//! 2. Create a test runner that will execute all the tests in the registry
//! 3. (optionally) sets an outputter that will output the results
//! 4. Run the test cases.
int main(int argc, char* argv[])
{
	// Get the top level suite from the registry
	CppUnit::Test *suite = CppUnit::TestFactoryRegistry::getRegistry().makeTest();

	// Adds the test to the list of test to run
	CppUnit::TextUi::TestRunner runner;
	runner.addTest(suite);

	// Change the default outputter to a compiler error format outputter
	runner.setOutputter(new CppUnit::CompilerOutputter(&runner.result(),
		std::cerr));
	// Run the tests.
	bool wasSucessful = runner.run();

	getchar();

	// Return error code 1 if the one of test failed.
	return wasSucessful ? 0 : 1;
}

*/