#pragma once
#include "ProgramInfo.h"

extern class ECE_Centipede {
public:
    vector<sf::Sprite> bodyParts;

private:
    const float particleRadius = 10.f;
    const float speed = 200.f;
    const float followDistance = 20.f;

    void initialize(sf::Vector2f position);
    direction updateBodyPositions(direction dir);

public:
    ECE_Centipede();
    ECE_Centipede(int num, Vector2f position);
    Vector2f getHeadPosition();
    direction moveCentipede(direction prevDir);
};