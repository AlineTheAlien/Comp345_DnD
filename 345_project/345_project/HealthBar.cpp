
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

	//Create Hello World text objecct using our font and size 128pt
	sf::Text text("HP Goes here", font, 80);

	text.setString(std::to_string(cr.getHitPoints()) + "/" + std::to_string(cr.getMaxHitPoints()));

	sf::FloatRect bounds(text.getLocalBounds());

	text.setPosition(window.getSize().x / 2 - (bounds.left + bounds.width / 2),
		window.getSize().y / 2 - (bounds.top + bounds.height / 2));


		//window.clear(sf::Color::White);
		//Draw our text object to the window

		window.draw(text);
		//window.display();
	
}

HealthBar::HealthBar() {

}

HealthBar::~HealthBar() {

}