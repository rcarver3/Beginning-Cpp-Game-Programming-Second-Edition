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
#include <string>

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
	HEAD,
	BODY,
	MUSHROOM,
	SPIDER,
	STARSHIP
} entity_t;

typedef struct entity {
	Sprite spriteEntity = Sprite();
	entity_t entityType = NOTHING;
	state currentState = HEALTHY;
} entity;

const int NUM_MUSHROOMS = 30;
const int NUM_BODIES = 12;
const int NUM_SHIPS = 1;
const int NUM_SPIDERS = 1;
const int NUM_TOTAL_ENTITIES = NUM_MUSHROOMS + NUM_BODIES + NUM_SHIPS + NUM_SPIDERS;

const int NUM_LIVES = 3;
extern vector<Sprite> lives(NUM_LIVES);

const int X_RESOLUTION = 1080;
const int Y_RESOLUTION = 1080;

const Color DARK_YELLOW = Color(112, 119, 24);

extern direction prevDir = LEFT;

typedef unordered_map<Vector2f, entity, hash<Vector2f>> whereabouts;
extern whereabouts entities = whereabouts(NUM_TOTAL_ENTITIES);

template <>
struct hash<Vector2f>
{
	size_t operator()(const Vector2f& k) const
	{
		using std::size_t;
		using std::hash;
		using std::string;

		// Compute individual hash values for first,
		// second and third and combine them using XOR
		// and bit shifting:

		return ((hash<string>()(to_string(k.x))
			^ (hash<string>()(to_string(k.y)) << 1)) >> 1);
	}
};

extern Clock sfClock;
extern direction movement = NONE;
extern float elapsedTime = 0.f;
extern bool paused = true;
extern bool acceptInput = false;

Vector2f calculateOrigin(entity Entity) {
	return Entity.spriteEntity.getLocalBounds().getSize() * 0.5f;
}

int roundByFifty(int num) {
	return ((num + 25) / 50) * 50;
}