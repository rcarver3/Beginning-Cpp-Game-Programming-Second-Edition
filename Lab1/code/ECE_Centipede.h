/*
Author: Rhett Carver
Class: ECE4122
Last Date Modified: 10/2/24
Description:
Controls the motion and body positions of the centipede.
*/


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
	// void newCentipede(int num, std::vector<std::vector<entity>>& bodyPartsTest);
    direction moveCentipede(direction prevDir, std::vector<entity>& bodyPartsTest);
};