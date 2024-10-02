#pragma once
#include <SFML/Graphics.hpp>

const int NUM_MUSHROOMS = 30;
const int NUM_BODIES = 12;
const int NUM_SHIPS = 1;
const int NUM_SPIDERS = 1;
const int NUM_TOTAL_ENTITIES = NUM_MUSHROOMS + NUM_BODIES + NUM_SHIPS + NUM_SPIDERS;

const int NUM_LIVES = 3;

const unsigned int X_RESOLUTION = 1080;
const unsigned int Y_RESOLUTION = 1080;

const float ENTITY_SIZE = 25;
const float FOLLOW_DISTANCE = 50;
const float SPEED = 200;

const sf::Color DARK_YELLOW = sf::Color(112, 119, 24);