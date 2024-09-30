#include "ProgramInfo.h"

using namespace sf;
using namespace std;

class ECE_Centipede {
public:
    vector<Sprite> bodyParts;

private:
    const float particleRadius = 10.f;
    const float speed = 200.f;
    const float followDistance = 20.f;

    void initialize(Vector2f position) {
        bodyParts[0].setPosition(position);
        bodyParts[0].setTextureRect(IntRect(Vector2i(0, 0), Vector2i(23, 24)));
        for (int i = 1; i < bodyParts.size(); i++) {
            bodyParts[i].setPosition(position.x - (i * followDistance), position.y);
            bodyParts[i].setTextureRect(IntRect(Vector2i(0, 0), Vector2i(23, 24)));
        }
    }

    direction updateBodyPositions(direction dir) {
        Vector2f velocity;
        switch (dir) {
        case direction::UP:
            velocity = Vector2f(0.f, followDistance * -1);
            break;
        case direction::DOWN:
            velocity = Vector2f(0.f, followDistance);
            break;
        case direction::LEFT:
            velocity = Vector2f(followDistance * -1, 0.f);
            break;
        case direction::RIGHT:
            velocity = Vector2f(followDistance, 0.f);
            break;
        case direction::NONE:
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

public:
    ECE_Centipede() {
        bodyParts.assign(NUM_BODIES, Sprite());
        initialize(Vector2f(300, 110));
    }

    ECE_Centipede(int num, Vector2f position) {
        bodyParts.assign(num, Sprite());
        initialize(position);
    }

    Vector2f getHeadPosition() {
        return bodyParts[0].getPosition();
    }

    direction moveCentipede(direction prevDir) {
        bool down = true, left = true, right = true, up = true;
        Sprite head = bodyParts[0];

        FloatRect boundary = head.getGlobalBounds();
        Vector2f prevPos = head.getPosition();

        for (int i = 0; i < entities.size(); i++) {
            FloatRect mushroomBox = entities[i].spriteEntity.getGlobalBounds();

            // Explore right
            if (right) {
                head.move(followDistance, 0);
                if (boundary.intersects(mushroomBox) || head.getPosition().x >= X_RESOLUTION) {
                    right = false;
                }
                head.setPosition(prevPos);
            }

            // Explore down
            if (down) {
                head.move(0, followDistance);
                if (boundary.intersects(mushroomBox) || head.getPosition().y >= Y_RESOLUTION * 0.9) {
                    down = false;
                }
                head.setPosition(prevPos);
            }

            // Explore left
            if (left) {
                head.move(followDistance * -1, 0);
                if (boundary.intersects(mushroomBox) || head.getPosition().x <= 0) {
                    left = false;
                }
                head.setPosition(prevPos);
            }

            // Explore up
            if (up) {
                head.move(0, followDistance * -1);
                if (boundary.intersects(mushroomBox) || head.getPosition().y <= Y_RESOLUTION * 0.09) {
                    up = false;
                }
                head.setPosition(prevPos);
            }
        }

        vector<bool> choose = { false, false, false };
        vector<direction> next = { direction::RIGHT, direction::DOWN, direction::LEFT, direction::UP };
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
        case direction::RIGHT:
            /*if (right) {
                return updateBodyPositions(direction::RIGHT);
            }
            else if (down) {
                return updateBodyPositions(direction::DOWN);
            }
            else if (left) {
                return updateBodyPositions(direction::LEFT);
            }
            break;*/
            return updateBodyPositions(direction::RIGHT);
        case direction::DOWN:
            /*if (left) {
                return updateBodyPositions(direction::LEFT);
            }
            else if (right) {
                return updateBodyPositions(direction::RIGHT);
            }
            else if (down) {
                return updateBodyPositions(direction::DOWN);
            }
            break;*/
            return updateBodyPositions(direction::DOWN);
        case direction::LEFT:
            /*if (left) {
                return updateBodyPositions(direction::LEFT);
            }
            else if (down) {
                return updateBodyPositions(direction::DOWN);
            }
            else if (right) {
                return updateBodyPositions(direction::RIGHT);
            }
            break;*/
            return updateBodyPositions(direction::LEFT);
        case direction::UP:
            /*if (left) {
                return updateBodyPositions(direction::LEFT);
            }
            else if (down) {
                return updateBodyPositions(direction::DOWN);
            }
            else if (right) {
                return updateBodyPositions(direction::RIGHT);
            }
            break;*/
            return updateBodyPositions(direction::UP);
        default:
            return updateBodyPositions(direction::DOWN);
        }
    }
};