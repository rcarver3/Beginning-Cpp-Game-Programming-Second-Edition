#pragma once
#include <sstream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include <list>
#include <chrono>

enum class state {
	EMPTY,
	HEALTHY_MUSHROOM,
	DAMAGED_MUSHROOM
};

enum class direction {
    NONE,
    UP,
    DOWN,
    LEFT,
    RIGHT
};

struct mushroom {
	sf::Sprite spriteMushroom = sf::Sprite();
	state currentState = state::HEALTHY_MUSHROOM;
};

const int NUM_MUSHROOMS = 30;
const int NUM_LIVES = 3;

const int X_RESOLUTION = 1920;
const int Y_RESOLUTION = 1080;

extern std::vector<mushroom> mushrooms(NUM_MUSHROOMS);

const sf::Color DARK_YELLOW = sf::Color(112, 119, 24);

const sf::IntRect SCREEN_BOUNDARY = sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(X_RESOLUTION, Y_RESOLUTION));