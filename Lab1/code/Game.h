/*
Author: Rhett Carver
Class: ECE4122
Last Date Modified: 10/2/24
Description:
The main function, consisting of initialization and the game loop.
*/

#pragma once
#include "types.h"
#include "constants.h"
#include "ECE_Centipede.h"
#include "Laser.h"
#include <random>
#include <list>
#include <chrono>
#include <cmath>
#include <array>
#include <unordered_map>
#include <string>

extern std::vector<sf::Sprite> lives;
extern direction prevDir;
extern float elapsedTime;
extern whereabouts entities;
extern whereabouts::iterator it;
extern int score;

void movePlayer(entity* player, direction dir, float elapsedTime);
sf::Vector2f calculateOrigin(entity Entity);
int roundByPixel(float num);