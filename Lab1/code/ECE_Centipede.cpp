#include <SFML/Graphics.hpp>
#include <vector>

using namespace sf;
using namespace std;

class ECE_Centipede : Sprite {
public:
    const float particleRadius = 10.f;
    const float speed = 200.f;
    const float followDistance = 20.f;
    vector<Sprite> bodyParts;

    enum class direction {
        NONE,
        UP,
        DOWN,
        LEFT,
        RIGHT
    };

private:
    void initialize() {
        Texture textureCentipedeHead;
        Texture textureCentipedeBody;
        textureCentipedeHead.loadFromFile("graphics/CentipedeHead.png");
        textureCentipedeBody.loadFromFile("graphics/CentipedeBody.png");

        bodyParts[0].setTexture(textureCentipedeHead);
        bodyParts[0].setPosition(0, 400);
        for (int i = 1; i < bodyParts.size(); i++) {
            bodyParts[i].setTexture(textureCentipedeBody);
            bodyParts[i].setPosition(i * followDistance, 400);
        }
    }

public:
    ECE_Centipede() {
        vector<Sprite> bodyParts(12);
        initialize();
    }

    ECE_Centipede(int numP) {
        vector<Sprite> bodyParts(numP);
        initialize();
    }

    void moveCentipede(direction dir = direction::NONE) {
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
        // If dir is not NONE, for each particle except
        // the lead one make it follow the one ahead
        if (velocity != Vector2f(0.f, 0.f)) {
            for (int i = bodyParts.size() - 1; i > 0; i--) {
                bodyParts[i].setPosition(bodyParts[i - 1].getPosition());
            }
            // Finally, move the lead particle by velocity amount
            bodyParts[0].move(velocity);
        }
    }
    /*
    Clock clock;
    float elapsedTime = 0.f;

    // Time delta for determining update rate
    float deltaTime = clock.restart().asSeconds();

    // If enough time has passed for 5 fps:
    if (elapsedTime >= 0.2f) {
        // Velocity vector value depends on key pressed


        // Reset elapsed time
        elapsedTime = 0.f;
    }
    else {
        elapsedTime += deltaTime;
    }
}
**/
};