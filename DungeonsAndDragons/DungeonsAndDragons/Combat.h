//! @file 
//! @brief Header file for the Combat class  
//!
//! The combat mechanism is separated into its own class, to hide details of the combat. It contains static methods
//! thus the creation of a Combat object is not needed and these methods are called by classes. One method
//! is used to start the combat, the other one is is an iterative method that decides where the NPCs will next move. The third one 
//! is used to trigger all the NPCs in side the map to move closer and closer to the player everytime the player moves. 
//! 
//! Steps of the combat:
//! 1. Player chooses a target by trying to move to the grid where the enemy is (assuming a player can fight only one enemy at a time)
//! 2. Roll initiative
//!		Assuming all characters are aware of each other (no surprise round), each characters in combat will roll initiative (1d20 dice) by making a Dexterity check.
//!		The character with the highest Dexterity check total will begin the first round of combat.
//! 3. Take turns
//!		Each character will take turns in the combats, in descending initiative order. During the turn, character can move up to their 'speed' and take one action.
//!		According to the rules, if the D&D game is grid-based as it is the case, a grid represents a movement of 5 ft. A fighter character has a speed of 30ft, thereby
//!		can only move up to a maximum of 6 grids.
//!		For the scope of the project, an action is either a movement (up to 6 grids), an attack or modification of an equipment.
//!			Attack: If attacking, the program will check if enemy is within range (within top, bottom, left, right, diagonals grids)
//!			if the opponent is not within range, the program will ask to do other actions. (move or modify equipment)
//!			If an attack is possible, the character will make an attack roll by rolling a 1d20 die and add attack bonus (which is the sum of Strength and Dexterity modifiers)
//!			This determines if attack hits or misses. If the total of the attack roll + modifiers is higher than the enemy's Armor Class, attack will hit.
//!			If a 20 is rolled, the attack automatically hits and this is a critical hit. If a 1 is rolled, the attack misses.
//!			When there is a critical hit, the character will do a damage roll twice (a 2d20 or 2x 1d20) and add damage bonus (based on Strength modifier only).
//! 4. Begin the next round
//!		The same character that had the highest initiative begins each round and combat continues until
//!		one of the character's HP is 0.As soon as the character finishes his turn, then it is the other character's turn.
#pragma once
#include "MapObject.h"
#include "Map.h"

//! Class for the implementation of the combat mechanism
class Combat {
public:
	static void startCombat(Map*, MapObject*, MapObject*);
	static void moveAlongPath(Map* map, MapObject* character, MapObject* target);
	static void activateNPC(Map* map, MapObject* player);
	static void setLogCombat(bool);
	static bool logCombat;
};