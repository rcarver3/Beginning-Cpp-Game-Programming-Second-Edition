#pragma once
#include "types.h"
#include "constants.h"
#include "Game.h"
#include <SFML/Graphics.hpp>
#include <vector>

class ECE_Centipede {
private:
    direction updateBodyPositions(direction dir, std::vector<entity>& bodyPartsTest);

public:
    //ECE_Centipede(int num, sf::Vector2f position);
    direction moveCentipede(direction prevDir, std::vector<entity>& bodyPartsTest);
};