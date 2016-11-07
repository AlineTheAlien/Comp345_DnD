#include "stdafx.h"
#include "Resources.h"

#include <iostream>
using std::cout;

//! Implementation of the default constructor of the Resources class
Resources::Resources()
{

	if (!groundTexture.loadFromFile("Textures/GroundTile.png"))
	{
		//error
		cout << "Error loading texture..." << endl;
		exit(1);
	}

	if (!wallTexture.loadFromFile("Textures/WallTile.png"))
	{
		//error
		cout << "Error loading texture..." << endl;
		exit(1);
	}

	if (!treasureTexture.loadFromFile("Textures/TreasureTile.png"))
	{
		//error
		cout << "Error loading texture..." << endl;
		exit(1);
	}

	if (!doorTexture.loadFromFile("Textures/DoorTile.png"))
	{
		//error
		cout << "Error loading texture..." << endl;
		exit(1);
	}

	if (!playerTexture.loadFromFile("Textures/PlayerTile.png"))
	{
		//error
		cout << "Error loading texture..." << endl;
		exit(1);
	}

	if (!enemyTexture.loadFromFile("Textures/EnemyTile.png"))
	{
		//error
		cout << "Error loading texture..." << endl;
		exit(1);
	}
}


//! Implementation of getPlayerTexture to access the playerTexture
//! @return : a sf::Texture reference to the player texture
const sf::Texture& Resources::getPlayerTexture()
{
	return playerTexture;
}

//! Implementation of getEnemyTexture to access the enemyTexture
//! @return : a sf::Texture reference to the enemy texture
const sf::Texture& Resources::getEnemyTexture()
{
	return enemyTexture;
}

//! Implementation of getDoorTexture to access the doorTexture
//! @return : a sf::Texture reference to the door texture
const sf::Texture&  Resources::getDoorTexture()
{
	return doorTexture;
}

//! Implementation of getTreasureTexture to access the treasureTexture
//! @return : a sf::Texture reference to the treasure texture
const sf::Texture&  Resources::getTreasureTexture()
{
	return treasureTexture;
}

//! Implementation of getGroundTexture to access the groundTexture
//! @return : a sf::Texture reference to the ground texture
const sf::Texture&  Resources::getGroundTexture()
{
	return groundTexture;
}

//! Implementation of getWallTexture to access the wallTexture
//! @return : a sf::Texture reference to the wall texture
const sf::Texture&  Resources::getWallTexture()
{
	return wallTexture;
}

Resources::~Resources()
{
}
