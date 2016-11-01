
#include <SFML/Graphics.hpp>
#include "stdafx.h"
#include "HealthBar.h"
#include "CharacterObserver.h"
#include "Character.h"
sf::Text stext;

HealthBar::HealthBar(sf::RenderWindow &window, Character &cr)
{
	sf::Font font;

	if (!font.loadFromFile("Fonts/pc.ttf")) {
		// TODO: Error..
	}

	//Create text objecct using our font and size 
	sf::Text text("HP Goes here", font, 18);
	sf::Text text2("Strength Score", font, 18);
	sf::Text text3("Level", font, 18);

	text.setString("Character's HP is:" + std::to_string(cr.getHitPoints()) + "/" + std::to_string(cr.getMaxHitPoints()));
	text2.setString("Character's Strength Score is:" + std::to_string(cr.getStrengthScore()));
	text3.setString("Character's Level is:" + std::to_string(cr.getCurrentLevel()));

	//text.setPosition(window.getSize().x / 2 - (bounds.left + bounds.width),
		//window.getSize().y / 2 - (bounds.top - bounds.height * 5));

	sf::FloatRect bounds = text.getLocalBounds();
	text.setOrigin(bounds.left + bounds.width,
		bounds.top + bounds.height);
	text.setPosition(sf::Vector2f(window.getSize().x, window.getSize().y));

	//How to display the rest below it? text2 and text3

		//window.clear(sf::Color::White);
		//Draw our text object to the window

		window.draw(text);
		//window.display();
	
}

HealthBar::HealthBar() {

}

HealthBar::~HealthBar() {

}