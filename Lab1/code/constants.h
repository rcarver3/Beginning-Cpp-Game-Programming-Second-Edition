/*
Author: Rhett Carver
Class: ECE4122
Last Date Modified: 10/2/24
Description:
Holds the constant values used throughout the program.
*/

#pragma once
#include <SFML/Graphics.hpp>

const int NUM_MUSHROOMS = 30;
const int NUM_BODIES = 12;
const int NUM_SHIPS = 1;
const int NUM_SPIDERS = 1;
const int NUM_TOTAL_ENTITIES = NUM_MUSHROOMS + NUM_BODIES + NUM_SHIPS + NUM_SPIDERS;

const int NUM_LIVES = 3;

const unsigned int X_RESOLUTION = 1920;
const unsigned int Y_RESOLUTION = 1080;

const float PIXEL_SCALE = 25;
const sf::IntRect ENTITY_RECT = sf::IntRect(0, 0, PIXEL_SCALE, PIXEL_SCALE);
const sf::Vector2f ENTITY_ORIGIN = sf::Vector2f(PIXEL_SCALE / 2, PIXEL_SCALE / 2);

const float SPEED = 200;

const sf::Color DARK_YELLOW = sf::Color(112, 119, 24);