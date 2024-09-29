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

    const int numParticles = 10;
    const float particleRadius = 10.f;
    const float speed = 200.f;
    const float followDistance = 30.f; // Distance each particle tries to maintain from the one in front

    // Create particles (lead particle + followers)
    std::vector<CircleShape> particles(numParticles);
    for (int i = 0; i < numParticles; ++i) {
        particles[i].setRadius(particleRadius);
        particles[i].setFillColor(Color::White);
        particles[i].setOrigin(particleRadius, particleRadius); // Center origin for proper movement
        particles[i].setPosition(400.f, 300.f + i * followDistance); // Position them initially in a vertical line
    }

    Clock clock;

    // Main loop
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }

        // Time delta for smooth movement
        float deltaTime = clock.restart().asSeconds();

        // Control the lead particle (the first one)
        if (Keyboard::isKeyPressed(Keyboard::Up)) {
            particles[0].move(0, -speed * deltaTime);
        }
        if (Keyboard::isKeyPressed(Keyboard::Down)) {
            particles[0].move(0, speed * deltaTime);
        }
        if (Keyboard::isKeyPressed(Keyboard::Left)) {
            particles[0].move(-speed * deltaTime, 0);
        }
        if (Keyboard::isKeyPressed(Keyboard::Right)) {
            particles[0].move(speed * deltaTime, 0);
        }

        // For each particle except the lead one, make it follow the one ahead
        for (int i = 1; i < numParticles; ++i) {
            Vector2f dir = particles[i - 1].getPosition() - particles[i].getPosition();
            float dist = distance(particles[i - 1].getPosition(), particles[i].getPosition());

            if (dist > followDistance) {
                // Normalize the direction vector and move the particle towards the one ahead
                particles[i].move(normalize(dir) * (speed * deltaTime));
            }
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
