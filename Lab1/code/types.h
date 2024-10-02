#pragma once
#include "constants.h"
#include <SFML/Graphics.hpp>
#include <unordered_map>

typedef enum state {
	EMPTY,
	HEALTHY,
	DAMAGED,
	CENTIPEDE
} state;

typedef enum direction {
	NONE = -1,
	DOWN = 0,
	LEFT = 1,
	RIGHT = 2,
	UP = 3
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
	sf::Sprite spriteEntity = sf::Sprite();
	entity_t entityType = NOTHING;
	state currentState = HEALTHY;
	bool moved = false;
} entity;

template <>
struct std::hash<sf::Vector2f>
{
	std::size_t operator()(const sf::Vector2f& k) const
	{
		return ((std::hash<float>()(k.x) + std::hash<float>()(k.y)) % (X_RESOLUTION + Y_RESOLUTION));
	}
};

typedef std::unordered_map<sf::Vector2f, entity*> whereabouts;