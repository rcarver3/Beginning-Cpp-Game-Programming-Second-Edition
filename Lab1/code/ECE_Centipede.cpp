#include "ECE_Centipede.h"
#include <iostream>

using namespace sf;
using namespace std;

//void ECE_Centipede::initialize(Vector2f position) {
//
//}

direction ECE_Centipede::updateBodyPositions(direction dir, vector<entity> &bodyPartsTest) {
    Vector2f velocity;
    switch (dir) {
    case UP:
        velocity = Vector2f(0.f, FOLLOW_DISTANCE * -1);
        break;
    case DOWN:
        velocity = Vector2f(0.f, FOLLOW_DISTANCE);
        break;
    case LEFT:
        velocity = Vector2f(FOLLOW_DISTANCE * -1, 0.f);
        break;
    case RIGHT:
        velocity = Vector2f(FOLLOW_DISTANCE, 0.f);
        break;
    case NONE:
        velocity = Vector2f(0.f, 0.f);
        break;
    default:
        velocity = Vector2f(0.f, 0.f);
        break;
    }
    for (int i = bodyPartsTest.size() - 1; i > 0; i--) {
        bodyPartsTest[i].spriteEntity.setPosition(bodyPartsTest[i - 1].spriteEntity.getPosition());
		bodyPartsTest[i].moved = true;
    }

    // Finally, move the lead particle by velocity amount
    bodyPartsTest[0].spriteEntity.move(velocity);
    bodyPartsTest[0].moved = true;
    return dir;
}

//ECE_Centipede::ECE_Centipede(vector<entity>* body) {
//	for (int i = 0; i < body->size(); i++) {
//		// bodyParts[i] = body->at(i);
//	}
//}

//ECE_Centipede::ECE_Centipede(int num, vector<entity>* body) {
//    for (int i = 0; i < body->size(); i++) {
//        // bodyParts[i] = body;
//    }
//}

//Vector2f ECE_Centipede::getHeadPosition() {
//    // return bodyParts[0].getPosition();
//}

direction ECE_Centipede::moveCentipede(direction prevDir, vector<entity>& bodyPartsTest) {
    bool choose[4] = {};
    Sprite head = bodyPartsTest[0].spriteEntity;

    FloatRect boundary = head.getGlobalBounds();
    Vector2f prevPos = head.getPosition();

    // Explore right
    head.move(FOLLOW_DISTANCE, 0);
    choose[RIGHT] = head.getPosition().x < X_RESOLUTION && head.getPosition().x > 0 && !entities.count(head.getPosition());
    head.setPosition(prevPos);

    // Explore down
    head.move(0, FOLLOW_DISTANCE);
    choose[DOWN] = head.getPosition().y < Y_RESOLUTION && head.getPosition().y > 0 && !entities.count(head.getPosition());
    head.setPosition(prevPos);

    // Explore left
    head.move(-1 * FOLLOW_DISTANCE, 0);
    choose[LEFT] = head.getPosition().x < X_RESOLUTION && head.getPosition().x > 0 && !entities.count(head.getPosition());
    head.setPosition(prevPos);

    // Explore up
    head.move(0, -1 * FOLLOW_DISTANCE);
	choose[UP] = head.getPosition().y < Y_RESOLUTION && head.getPosition().y > 0 && !entities.count(head.getPosition());
    head.setPosition(prevPos);

    direction choice = DOWN;
    srand(chrono::system_clock::now().time_since_epoch().count());
    if (choose[UP] && !choose[DOWN] && !choose[LEFT] && !choose[RIGHT]) { choice = UP; }
    else {
        if (prevDir == RIGHT) {
            if (choose[RIGHT]) { choice = RIGHT; }
            else { choice = DOWN; }
        }
        else if (prevDir == LEFT) {
            if (choose[LEFT]) { choice = LEFT; }
            else { choice = DOWN; }
        }
        else if (prevDir == DOWN || prevDir == UP) {
            if (choose[LEFT] && choose[RIGHT]) {
                rand() % 2 == 0 ? choice = LEFT : choice = RIGHT;
            }
            else {
                if (choose[LEFT]) { choice = LEFT; }
                else if (choose[RIGHT]) { choice = RIGHT; }
                else { choice = DOWN; }
            }
        } //down left right up
        return updateBodyPositions(choice, bodyPartsTest);
    }
}