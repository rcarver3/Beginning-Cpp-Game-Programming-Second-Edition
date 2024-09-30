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
    const int initialCount = 12;

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
        bodyParts.assign(initialCount, Sprite());
        initialize(Vector2f(300, 110));
    }

    ECE_Centipede(int num, Vector2f position) {
        bodyParts.assign(num, Sprite());
        initialize(position);
    }

    Vector2f getHeadPosition() {
        return bodyParts[0].getPosition();
    }

    direction moveCentipede(direction prev) {
        bool down = true, left = true, right = true;
        Sprite head = bodyParts[0];
        FloatRect boundary = head.getGlobalBounds();
        Vector2f prevPos = head.getPosition();

        for (int i = 0; i < mushrooms.size(); i++) {
            FloatRect mushroomBox = mushrooms[i].spriteMushroom.getGlobalBounds();

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
                if (boundary.intersects(mushroomBox)) {
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
        }

        switch (prev) {
        case direction::RIGHT:
            if (right) {
                return updateBodyPositions(direction::RIGHT);
            }
            else if (down) {
                return updateBodyPositions(direction::DOWN);
            }
            else if (left) {
                return updateBodyPositions(direction::LEFT);
            }
            break;
        case direction::DOWN:
            if (left) {
                return updateBodyPositions(direction::LEFT);
            }
            else if (right) {
                return updateBodyPositions(direction::RIGHT);
            }
            else if (down) {
                return updateBodyPositions(direction::DOWN);
            }
            break;
        case direction::LEFT:
            if (left) {
                return updateBodyPositions(direction::LEFT);
            }
            else if (down) {
                return updateBodyPositions(direction::DOWN);
            }
            else if (right) {
                return updateBodyPositions(direction::RIGHT);
            }
            break;
        default:
            return updateBodyPositions(direction::DOWN);
        }
    }
};