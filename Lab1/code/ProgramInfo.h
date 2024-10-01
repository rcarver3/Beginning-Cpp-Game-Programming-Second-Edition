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

class Entity {
	Sprite spriteEntity = Sprite();
	Vector2f position = Vector2f(0, 0);
	Vector2f scale = Vector2f(1, 1);
	entity_t entityType = NOTHING;
	state currentState = HEALTHY;

	// Default: initialize empty sprite with default params
	Entity() {
		spriteEntity.setScale(scale);
		spriteEntity.setOrigin(spriteEntity.getLocalBounds().getSize() * 0.5f);
	}

	Entity(Sprite sprite, Vector2f position) : Entity() {
		spriteEntity = sprite;
		spriteEntity.setPosition(position);
	}

	Entity(Sprite sprite, Vector2f position, Vector2f scale) : Entity(sprite, position) {
		spriteEntity.setScale(scale);
	}

	Entity(Sprite sprite, Vector2f position, Vector2f scale, entity_t type, state status) : Entity(sprite, position, scale) {
		entityType = type;
		currentState = status;
	}

	void setTexture(Texture texture) {
		spriteEntity.setTexture(texture);
	}

	void setScale(Vector2f newScale) {
		scale = newScale;
		spriteEntity.setScale(scale);
	}

	void setPosition(Vector2f newPosition) {
		newPosition = position;
		spriteEntity.setPosition(newPosition);
	}

	void setType(entity_t type) {
		entityType = type;
	}

	void setStatus(state status) {
		currentState = status;
	}
};

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

typedef unordered_map<Vector2f, Entity> whereabouts; 

extern whereabouts entities = whereabouts(NUM_TOTAL_ENTITIES);
extern whereabouts::iterator it;