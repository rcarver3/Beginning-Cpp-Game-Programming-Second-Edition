#pragma once
#include "types.h"
#include "constants.h"
#include "Game.h"
#include <SFML/Graphics.hpp>
#include <vector>

class ECE_Centipede {
public:
    std::vector<sf::Sprite> bodyParts;

private:
    const float particleRadius = 10.f;
    const float speed = 200.f;
    const float followDistance = 20.f;

    void initialize(sf::Vector2f position);
    direction updateBodyPositions(direction dir);

public:
    ECE_Centipede();
    ECE_Centipede(int num, sf::Vector2f position);
    sf::Vector2f getHeadPosition();
    direction moveCentipede(direction prevDir);
};