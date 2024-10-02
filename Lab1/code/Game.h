#pragma once
#include "types.h"
#include "constants.h"
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

sf::Vector2f calculateOrigin(entity Entity);
int roundByPixel(float num);