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
        velocity = Vector2f(0, PIXEL_SCALE * -1);
        break;
    case DOWN:
        velocity = Vector2f(0, PIXEL_SCALE);
        break;
    case LEFT:
        velocity = Vector2f(PIXEL_SCALE * -1, 0);
        break;
    case RIGHT:
        velocity = Vector2f(PIXEL_SCALE, 0);
        break;
    case NONE:
        velocity = Vector2f(0, PIXEL_SCALE * 2);
        break;
    default:
        velocity = Vector2f(0, PIXEL_SCALE * 2);
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

direction ECE_Centipede::moveCentipede(direction prevDir, vector<entity>& bodyPartsTest) {
    bool choose[4] = {};
    Sprite head = bodyPartsTest[0].spriteEntity;

    FloatRect boundary = head.getGlobalBounds();
    Vector2f prevPos = head.getPosition();

    // Explore right
    head.move(PIXEL_SCALE, 0);
    choose[RIGHT] = head.getPosition().x < X_RESOLUTION && head.getPosition().x > 0 && !entities.count(head.getPosition());
    head.setPosition(prevPos);

    // Explore down
    head.move(0, PIXEL_SCALE);
    choose[DOWN] = head.getPosition().y < Y_RESOLUTION && head.getPosition().y > 0 && !entities.count(head.getPosition());
    head.setPosition(prevPos);

    // Explore left
    head.move(-1 * PIXEL_SCALE, 0);
    choose[LEFT] = head.getPosition().x < X_RESOLUTION && head.getPosition().x > 0 && !entities.count(head.getPosition());
    head.setPosition(prevPos);

    // Explore up
    head.move(0, -1 * PIXEL_SCALE);
	choose[UP] = head.getPosition().y < Y_RESOLUTION && head.getPosition().y > 0 && !entities.count(head.getPosition());
    head.setPosition(prevPos);

    direction choice = NONE;
    srand(chrono::system_clock::now().time_since_epoch().count());
    if (!choose[UP] && !choose[DOWN] && !choose[LEFT] && !choose[RIGHT]) { choice = NONE; }
    else if (choose[UP] && !choose[DOWN] && !choose[LEFT] && !choose[RIGHT]) { choice = UP; }
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
        }
    }
    return updateBodyPositions(choice, bodyPartsTest);
}