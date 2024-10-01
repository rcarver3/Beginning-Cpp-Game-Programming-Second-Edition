#include "ECE_Centipede.h"

using namespace sf;
using namespace std;

void ECE_Centipede::initialize(Vector2f position) {
    bodyParts[0].setPosition(position);
    bodyParts[0].setTextureRect(IntRect(Vector2i(0, 0), Vector2i(23, 24)));
    for (int i = 1; i < bodyParts.size(); i++) {
        bodyParts[i].setPosition(position.x - (i * followDistance), position.y);
        bodyParts[i].setTextureRect(IntRect(Vector2i(0, 0), Vector2i(23, 24)));
    }
}

direction ECE_Centipede::updateBodyPositions(direction dir) {
    Vector2f velocity;
    switch (dir) {
    case UP:
        velocity = Vector2f(0.f, followDistance * -1);
        break;
    case DOWN:
        velocity = Vector2f(0.f, followDistance);
        break;
    case LEFT:
        velocity = Vector2f(followDistance * -1, 0.f);
        break;
    case RIGHT:
        velocity = Vector2f(followDistance, 0.f);
        break;
    case NONE:
        velocity = Vector2f(0.f, 0.f);
        break;
    default:
        velocity = Vector2f(0.f, 0.f);
        break;
    }
    for (int i = bodyParts.size() - 1; i > 0; i--) {
        bodyParts[i].setPosition(bodyParts[i - 1].getPosition());
    }

    // Finally, move the lead particle by velocity amount
    bodyParts[0].move(velocity);
    return dir;
}

ECE_Centipede::ECE_Centipede() {
    bodyParts.assign(NUM_BODIES, Sprite());
    initialize(Vector2f(300, 110));
}

ECE_Centipede::ECE_Centipede(int num, Vector2f position) {
    bodyParts.assign(num, Sprite());
    initialize(position);
}

Vector2f ECE_Centipede::getHeadPosition() {
    return bodyParts[0].getPosition();
}

direction ECE_Centipede::moveCentipede(direction prevDir) {
    bool down = true, left = true, right = true, up = true;
    Sprite head = bodyParts[0];

    FloatRect boundary = head.getGlobalBounds();
    Vector2f prevPos = head.getPosition();

    // Explore right
    if (right) {
        head.move(followDistance, 0);
        try {
            entities.at(head.getPosition());
            right = false;
            head.setPosition(prevPos);
        }
        catch (out_of_range e) {
            head.setPosition(prevPos);
        }
    }

    // Explore down
    if (down) {
        head.move(0, followDistance);
        try {
            entities.at(head.getPosition());
            down = false;
            head.setPosition(prevPos);
        }
        catch (out_of_range e) {
            head.setPosition(prevPos);
        }
    }

    // Explore left
    if (left) {
        head.move(-1 * followDistance, 0);
        try {
            entities.at(head.getPosition());
            left = false;
            head.setPosition(prevPos);
        }
        catch (out_of_range e) {
            head.setPosition(prevPos);
        }
    }

    // Explore up
    if (up) {
        head.move(0, -1 * followDistance);
        try {
            entities.at(head.getPosition());
            up = false;
            head.setPosition(prevPos);
        }
        catch (out_of_range e) {
            head.setPosition(prevPos);
        }
    }

    vector<bool> choose = { false, false, false };
    vector<direction> next = { RIGHT, DOWN, LEFT, UP };
    if (right) { choose[0] = true; }
    if (down) { choose[1] = true; }
    if (left) { choose[2] = true; }
    if (up) { choose[3] = true; }
    choose[(int)prevDir] = false;

    int choice;
    srand(chrono::system_clock::now().time_since_epoch().count());
    if (!choose[0] && !choose[1] && !choose[2]) { choice = 1; }
    else {
        choice = rand() % choose.size();
        if (!choose[choice]) { choice = (choice + 1) % 3; }
        if (!choose[choice]) { choice = (choice + 1) % 3; }
    }

    switch (next[choice]) {
    case RIGHT:
        return updateBodyPositions(RIGHT);
    case DOWN:
        return updateBodyPositions(DOWN);
    case LEFT:
        return updateBodyPositions(LEFT);
    case UP:
        return updateBodyPositions(UP);
    default:
        return updateBodyPositions(DOWN);
    }
}
