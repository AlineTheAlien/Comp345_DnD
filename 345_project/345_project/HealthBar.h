#pragma once
#include <SFML/Graphics.hpp>
#include "Character.h"

class HealthBar
{
public:
	HealthBar(void);
	~HealthBar(void);
	HealthBar(sf::RenderWindow &window, Character &cr);
	//void Draw();
private:
	sf::RenderWindow * swindow;
	sf::Text stext;
};