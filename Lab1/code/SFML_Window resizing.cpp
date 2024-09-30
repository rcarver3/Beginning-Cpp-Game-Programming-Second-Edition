// Include important C++ libraries here
#include <SFML/Graphics.hpp>

// Make code easier to type with "using namespace"
using namespace sf;

int main()
{
	// Create a window
	sf::RenderWindow window(sf::VideoMode(800, 600), "Scale Image to Fit Rectangle");

	// Load an image into a texture
	sf::Texture texture;
	if (!texture.loadFromFile("graphics/background.png")) {
		return -1; // Error loading image
	}

	// Create a sprite and set the texture
	sf::Sprite sprite;
	sprite.setTexture(texture);

	// Define the target rectangle dimensions
	sf::FloatRect targetRect(0.f, 0.f, 800.f, 600.f); // Position (x, y) and size (width, height)

	// Get the original size of the sprite
	sf::FloatRect originalSize = sprite.getGlobalBounds();

	// Calculate scale factors
	float scaleX = targetRect.width / originalSize.width;
	float scaleY = targetRect.height / originalSize.height;

	// Set the scale of the sprite to fit the target rectangle
	sprite.setScale(scaleX, scaleY);

	// Set the position of the sprite to the target rectangle's position
	sprite.setPosition(targetRect.left, targetRect.top);


	// Main loop
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color::White);
		window.draw(sprite);
		window.display();
	}

	return 0;
}


