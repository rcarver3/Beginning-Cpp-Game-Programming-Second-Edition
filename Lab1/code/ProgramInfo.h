#pragma once
#include <sstream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include <list>
#include <chrono>
#include <cmath>
#include <array>
#include <unordered_map>

using namespace sf;
using namespace std;

typedef enum state {
	EMPTY,
	HEALTHY,
	DAMAGED,
	CENTIPEDE
} state;

typedef enum direction {
	NONE,
    DOWN,
    LEFT,
    RIGHT,
	UP
} direction;

typedef enum entity_t {
	NOTHING,
	CENTIPEDE,
	MUSHROOM,
	SPIDER,
	STARSHIP
} entity_t;

typedef struct entity {
	Sprite spriteEntity = Sprite();
	entity_t entityType;
	state currentState = EMPTY;
} entity;

typedef unordered_map<Vector2f, entity> whereabouts; 

const int NUM_MUSHROOMS = 30;
const int NUM_BODIES = 12;
const int NUM_SHIPS = 1;
const int NUM_SPIDERS = 1;
const int NUM_LIVES = 3;

const int X_RESOLUTION = 1080;
const int Y_RESOLUTION = 1080;

extern whereabouts entities = whereabouts(NUM_MUSHROOMS + NUM_BODIES + NUM_SHIPS + NUM_SPIDERS);
extern whereabouts::iterator it;

const Color DARK_YELLOW = Color(112, 119, 24);