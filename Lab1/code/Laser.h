/*
Author: Rhett Carver
Class: ECE4122
Last Date Modified: 10/2/24
Description:
Controls the functionality of the laser.
*/

#pragma once
#include "types.h"
#include "constants.h"
#include "Game.h"
#include <SFML/Graphics.hpp>
#include <vector>

class Laser {
public:
	std::vector<sf::Sprite> lasers;

    void moveLasers(float deltaTime);
    void fireLaser(sf::Vector2f source);
};