#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>

using namespace sf;

// Function to calculate the distance between two points
float distance(Vector2f a, Vector2f b) {
    return std::sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
}

// Function to normalize a vector
Vector2f normalize(Vector2f v) {
    float mag = std::sqrt(v.x * v.x + v.y * v.y);
    if (mag == 0) return Vector2f(0, 0);
    return Vector2f(v.x / mag, v.y / mag);
}

int main() {
    // Window setup
    RenderWindow window(VideoMode(800, 600), "Particle Chain Movement");

    const int numParticles = 20;
    const float particleRadius = 10.f;
    const float speed = 200.f;
    const float followDistance = 20.f; // Distance each particle tries to maintain from the one in front

    // Create particles (lead particle + followers)
    std::vector<CircleShape> particles(numParticles);
    for (int i = 0; i < numParticles; ++i) {
        particles[i].setRadius(particleRadius);
        particles[i].setFillColor(Color::White);
        particles[i].setOrigin(particleRadius, particleRadius); // Center origin for proper movement
        particles[i].setPosition(400.f, 300.f + i * followDistance); // Position them initially in a vertical line
    }

    Clock clock;
    float elapsedTime = 0.f;
    
    // Main loop
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }

        // Close on escape key press
        if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            window.close();
        }

        // Time delta for determining update rate
        float deltaTime = clock.restart().asSeconds();

        // Velocity vector for determining change
        Vector2f velocity = Vector2f(0.f, 0.f);

        // If enough time has passed for 5 fps:
        if (elapsedTime >= 0.2f) {
            // Velocity vector value depends on key pressed
            if (Keyboard::isKeyPressed(Keyboard::Up)) {
                velocity = Vector2f(0.f, followDistance * -1);
            }
            if (Keyboard::isKeyPressed(Keyboard::Down)) {
                velocity = Vector2f(0.f, followDistance);
            }
            if (Keyboard::isKeyPressed(Keyboard::Left)) {
                velocity = Vector2f(followDistance * -1, 0.f);
            }
            if (Keyboard::isKeyPressed(Keyboard::Right)) {
                velocity = Vector2f(followDistance, 0.f);
            }

            // If velocity is not 0, for each particle except
            // the lead one, make it follow the one ahead
            if (velocity != Vector2f(0.f, 0.f)) {
                for (int i = particles.size() - 1; i > 0; i--) {
                    particles[i].setPosition(particles[i - 1].getPosition());
                }
                // Finally, move the lead particle by velocity amount
                particles[0].move(velocity);
            }
            // Reset elapsed time
            elapsedTime = 0.f;
        }
        else {        
            elapsedTime += deltaTime;
        }

        // Rendering
        window.clear();

        // Draw particles
        for (int i = 0; i < numParticles; ++i) {
            window.draw(particles[i]);
        }

        window.display();
    }

    return 0;
}
