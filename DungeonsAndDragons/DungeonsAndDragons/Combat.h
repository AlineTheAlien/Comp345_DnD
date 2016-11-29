//! @file 
//! @brief Header file for the Combat class  
//!
//! The combat mechanism is separated into its own class, to hide details of the combat. It contains two static
//! classes, thus the creation of a Combat object is not needed and these methods are called by classes.
//! Following the game rules, the steps for combat is as follows:
//! 1. Player chooses a target within range (assuming a player can fight only one enemy at a time for the simplicity of the assignment)
//! 2. Roll initiative
//!		Assuming all characters are aware of each other (no surprise round), each characters in combat will roll initiative (1d20 dice) by making a Dexterity check.
//!		The character with the highest Dexterity check total will begin the first round of combat.
//! 3. Take turns
//!		Each character will take turns in the combats, in descending initiative order. During the turn, character can move up to their 'speed' and take one action.
//!		According to the rules, if the D&D game is grid-based as it is the case, a grid represents a movement of 5 ft. A fighter character has a speed of 30ft, thereby
//!		can only move up to a maximum of 6 grids.
//!		For the scope of the assignment, an action can be only either a movement (up to their speed), an attack or use an object (such as a weapon).
//!		Attack: If attacking, program will check if enemy is within range (within range top, bottom, left, right, diagonals squares), if not, program will ask to do other actions.
//!			Otherwise, make an attack roll. It determines if attack hits or misses. (roll 1d20 and add modifiers + attack bonus)
//!			If the total of roll + modifiers is higher than the enemy's Armor Class, it hits. If roll 20, it will hit and it is a critical hit. If roll 1, it will miss.
//!			As for critical hit, the character will roll damage dice twice and add damage bonus (based on Strength modifier).
//! 4. Begin the next round
//!		The same character that had the highest initiative begins each round and combat continues until
//!		one of the character's HP is 0.
#pragma once
#include "MapObject.h"
#include "Map.h"

//! Class for the implementation of the combat mechanism
class Combat {
public:
	static void startCombat(Map*, MapObject*, MapObject*);
	static void moveAlongPath(Map* map, MapObject* character, MapObject* target);
	static void activateNPC(Map* map, MapObject* player);
};