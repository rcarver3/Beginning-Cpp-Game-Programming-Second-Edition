/*
Author: Rhett Carver
Class: ECE4122
Last Date Modified: 10/2/24
Description:
Controls the functionality of the laser.
*/

#include "Laser.h"

using namespace sf;
using namespace std;

vector<Sprite> lasers;

void Laser::moveLasers(float deltaTime) {
	for (int i = 0; i < lasers.size(); i++) {
		Vector2f roundedPosition = Vector2f(roundByPixel(lasers[i].getPosition().x), roundByPixel(lasers[i].getPosition().y));
		lasers[i].move(0, SPEED * deltaTime * -10);
		if (lasers[i].getPosition().y < Y_RESOLUTION * 0.1) {
			lasers.erase(lasers.begin() + i);
		}
		else if (entities.count(roundedPosition)) {
			lasers.erase(lasers.begin() + i);
			entity* destroyed = entities.at(roundedPosition);
			if (destroyed->entityType == MUSHROOM) {
				if (destroyed->currentState == HEALTHY) {
					destroyed->currentState = DAMAGED;
				}
				else if (destroyed->currentState == DAMAGED) {
				destroyed->currentState = EMPTY;
				entities.erase(roundedPosition);
				score += 4;
				}
			}
			else if (destroyed->entityType == SPIDER) {
				destroyed->currentState = EMPTY;
				entities.erase(roundedPosition);
				score += 300;
			}
			else {
				destroyed->currentState = EMPTY;
				entities.erase(roundedPosition);
			}
		}
	}
}

void Laser::fireLaser(Vector2f source) {
	Sprite laser;
	laser.setColor(Color::Red);
	laser.setPosition(source);
	laser.setScale(1, 1);
	laser.setRotation(90);
	lasers.push_back(laser);
}