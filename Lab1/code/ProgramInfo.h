#pragma once
#include <sstream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include <list>
#include <chrono>
#include <cmath>

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

const int X_RESOLUTION = 1080;
const int Y_RESOLUTION = 1080;

extern std::vector<mushroom> mushrooms(NUM_MUSHROOMS);
// extern sf::FloatRect head_bounding_box;

const sf::Color DARK_YELLOW = sf::Color(112, 119, 24);

// const sf::FloatRect SCREEN_BOUNDARY = sf::FloatRect(sf::Vector2f(0, 0), sf::Vector2f(X_RESOLUTION, Y_RESOLUTION));