//! @file 
//! @brief Header file for the Resources class
//! The following class implements a Resources class used to load and get
//! the textures used for the GUI. A references of the loaded textures are
//! used every time they are accessed by another class.

#pragma once
#include <SFML/Graphics.hpp>
using namespace std;

class Resources
{
private:
	//!Ground texture
	sf::Texture groundTexture;
	//!Wall texture
	sf::Texture wallTexture;
	//!Treasure Texture
	sf::Texture treasureTexture;
	//!Door texture
	sf::Texture doorTexture;
	//!Player texture
	sf::Texture playerTexture;
	//!Enemy texture
	sf::Texture enemyTexture;
	//!Friendly texture
	sf::Texture friendlyTexture;
public:
	Resources();
	const sf::Texture& getPlayerTexture();
	const sf::Texture& getWallTexture();
	const sf::Texture& getTreasureTexture();
	const sf::Texture& getGroundTexture();
	const sf::Texture& getDoorTexture();
	const sf::Texture& getEnemyTexture();
	const sf::Texture& getFriendlyTexture();
	~Resources();
};

