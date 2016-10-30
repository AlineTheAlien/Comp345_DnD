
#include <SFML/Graphics.hpp>
#include "stdafx.h"
#include "HealthBar.h"
#include "Character.h"
sf::Text stext;

HealthBar::HealthBar(sf::RenderWindow &window, Character &cr)
{
	sf::Font font;

	if (!font.loadFromFile("arial.ttf")) {
		// TODO: Error..
	}

	//Create Hello World text objecct using our font and size 128pt
	sf::Text text("40/100", font, 100);

	text.setString("Hehehehe");

	sf::FloatRect bounds(text.getLocalBounds());

	text.setPosition(window.getSize().x / 2 - (bounds.left + bounds.width / 2),
		window.getSize().y / 2 - (bounds.top + bounds.height / 2));

	while (window.isOpen()) {

		sf::Event event;

		while (window.pollEvent(event)) {

			if (event.type == sf::Event::EventType::Closed)
			{
				window.close();
			}
		}

		//window.clear(sf::Color::White);
		//Draw our text object to the window

		window.draw(text);
		window.display();
	}
}

HealthBar::~HealthBar() {}