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
        for (int i = 1; i < bodyParts.size(); i++) {
            bodyParts[i].setPosition(position.x - (i * followDistance), position.y);
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
        initialize(Vector2f(400, 200));
    }

    ECE_Centipede(int num, Vector2f position) {
        bodyParts.assign(num, Sprite());
        initialize(position);
    }

    Vector2f getHeadPosition() {
        return bodyParts[0].getPosition();
    }

    direction moveCentipede() {

        bool down = true, left = true, right = true;
        direction dir;
        float negative = followDistance * -1;
        for (int i = 0; i < mushrooms.size(); i++) {
            // Explore right
            bodyParts[0].move(followDistance, 0);
            if (bodyParts[0].getTextureRect().intersects((IntRect) mushrooms[i].spriteMushroom.getGlobalBounds()) ||
                bodyParts[0].getTextureRect().intersects() {
                right = false;
            }
            bodyParts[0].move(negative, followDistance);
            if (bodyParts[0].getTextureRect().intersects((IntRect)mushrooms[i].spriteMushroom.getGlobalBounds())) {
                down = false;
            }
            bodyParts[0].move(negative, negative);
            if (bodyParts[0].getTextureRect().intersects((IntRect)mushrooms[i].spriteMushroom.getGlobalBounds())) {
                left = false;
            }
            bodyParts[0].move(followDistance, 0);
        }
        if (1) {
            bodyParts[0].move(followDistance * -1, 0);
            return updateBodyPositions(direction::RIGHT);
        }
        return direction::NONE;
    }
};