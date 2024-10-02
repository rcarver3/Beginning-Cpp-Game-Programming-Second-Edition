#include "types.h"
#include "constants.h"
#include "ECE_Centipede.h"
#include "Game.h"
#include <iostream>

using namespace sf;
using namespace std;

std::vector<Sprite> lives(NUM_LIVES);
whereabouts entities = whereabouts(NUM_TOTAL_ENTITIES);

Vector2f calculateOrigin(entity object) {
	return object.spriteEntity.getLocalBounds().getSize() * 0.5f;
}

int roundByPixel(float num) {
	return (((static_cast<int>(num) + (static_cast<int>(PIXEL_SCALE) / 2)) / static_cast<int>(PIXEL_SCALE)) * static_cast<int>(PIXEL_SCALE));
}

int main() {
	// Create and open a window for the game
	RenderWindow window(VideoMode((int)X_RESOLUTION, (int)Y_RESOLUTION), "Centipede!!", Style::Fullscreen);

	// Create Texture and Font objects
	Texture textureStarship;
	Texture textureSpider;
	Texture textureStartup;
	Texture textureFullMushroom;
	Texture textureHalfMushroom;
	Texture textureCentipedeHead;
	Texture textureCentipedeBody;
	Font font;

	// Prepare textures and fonts
	textureStarship.loadFromFile("graphics/Starship.png");
	textureSpider.loadFromFile("graphics/spider.png");
	textureStartup.loadFromFile("graphics/startup.png");
	textureFullMushroom.loadFromFile("graphics/Mushroom0.png");
	textureHalfMushroom.loadFromFile("graphics/Mushroom1.png");
	textureCentipedeHead.loadFromFile("graphics/CentipedeHead.png");
	textureCentipedeBody.loadFromFile("graphics/CentipedeBody.png");
	font.loadFromFile("fonts/SEGOEPRB.TTF");

	// Create a background sprite
	Sprite spriteBackground;
	spriteBackground.setColor(Color::Black);
	spriteBackground.setScale(X_RESOLUTION, Y_RESOLUTION);
	spriteBackground.setPosition(0, 0);

	// Make a startup screen sprite
	Sprite startupScreenSprite;
	startupScreenSprite.setTexture(textureStartup);

	// Figure out how to scale startup texture
	float x = (textureStartup.getSize().x > X_RESOLUTION) ? (static_cast<float>(X_RESOLUTION) / textureStartup.getSize().x) : (static_cast<float>(textureStartup.getSize().x) / X_RESOLUTION);
	float y = (textureStartup.getSize().y > Y_RESOLUTION) ? (static_cast<float>(Y_RESOLUTION) / textureStartup.getSize().y) : (static_cast<float>(textureStartup.getSize().y) / Y_RESOLUTION);
	startupScreenSprite.setScale(x, y);
	startupScreenSprite.setPosition(0, 0);

	// Create bottom and top of screen
	RectangleShape screenBottom;
	screenBottom.setSize(Vector2f(X_RESOLUTION, Y_RESOLUTION * 0.1));
	screenBottom.setFillColor(DARK_YELLOW);
	screenBottom.setPosition(0, Y_RESOLUTION * 0.9);

	RectangleShape screenTop;
	screenTop.setSize(Vector2f(X_RESOLUTION, Y_RESOLUTION * 0.1));
	screenTop.setFillColor(DARK_YELLOW);
	screenTop.setPosition(0, 0);

	// Create score counter at top of screen
	int score = 0;
	Text scoreText;
	scoreText.setFont(font);
	scoreText.setString(to_string(score));
	scoreText.setCharacterSize(50);
	scoreText.setOrigin(scoreText.getLocalBounds().getSize() * 0.5f);
	scoreText.setFillColor(Color::White);
	scoreText.setPosition(X_RESOLUTION * 0.5, Y_RESOLUTION * 0.02);

	// Initialize lives separate from entities 
	// because its not important to the field
	for (int i = 0; i < NUM_LIVES; i++) {
		lives[i].setTexture(textureStarship);
		lives[i].setOrigin(lives[i].getLocalBounds().getSize() * 0.5f);
		lives[i].setScale(PIXEL_SCALE / textureStarship.getSize().x, PIXEL_SCALE / textureStarship.getSize().y);
		lives[i].scale(1.5, 1.5);
		lives[i].setPosition((X_RESOLUTION * 0.75 + (i * 50)), (Y_RESOLUTION * 0.02) + 20);
	}

	// Make starship entity
	entity* entityStarship = new entity(Sprite(textureStarship), STARSHIP);
	Vector2f position = Vector2f(roundByPixel(X_RESOLUTION * 0.5), roundByPixel((Y_RESOLUTION * 0.95)));
	entityStarship->spriteEntity.setPosition(position);
	entityStarship->spriteEntity.scale(1.5, 1.5);
	entities.insert({ position, entityStarship });

	// Make spider entities
	for (int i = 0; i < NUM_SPIDERS; i++) {
		entity* entitySpider = new entity(Sprite(textureSpider), SPIDER);
		Vector2f position = Vector2f(roundByPixel((X_RESOLUTION * 0.5) + (i * 200)), roundByPixel((Y_RESOLUTION * 0.50) + (i * 50)));
		entitySpider->spriteEntity.setPosition(position);
		entities.insert({ position, entitySpider });
	}

	// Random position generator
	default_random_engine generator;
    uniform_int_distribution<int> mushroomPositionX(0, X_RESOLUTION);
	uniform_int_distribution<int> mushroomPositionY(Y_RESOLUTION * 0.11, Y_RESOLUTION * 0.88);

	// Initialize each mushroom into the map
	for (int i = 0; i < NUM_MUSHROOMS; i++) {
		entity* entityMushroom = new entity(Sprite(textureFullMushroom), MUSHROOM);
		generator.seed(chrono::system_clock::now().time_since_epoch().count());
		Vector2f position = Vector2f(roundByPixel(mushroomPositionX(generator)), roundByPixel(mushroomPositionY(generator)));
		entityMushroom->spriteEntity.setPosition(position);

		entities.insert({ position, entityMushroom });
	}

	vector<vector<entity>> centipedes = { vector<entity>(NUM_BODIES, entity(Sprite(textureCentipedeBody), BODY)) };

	centipedes[0][0].spriteEntity.setTexture(textureCentipedeHead);
	centipedes[0][0].spriteEntity.setPosition(roundByPixel(X_RESOLUTION * 0.55), roundByPixel(Y_RESOLUTION * 0.11));
	centipedes[0][0].entityType = HEAD;

	entities.insert({ centipedes[0][0].spriteEntity.getPosition(), &centipedes[0][0] });

	for (int i = 1; i < NUM_BODIES; i++) {
		//centipedes[0][i].spriteEntity.setTexture(textureCentipedeBody);
		//centipedes[0][i].spriteEntity.setOrigin(calculateOrigin(centipedes[0][i]));
		//centipedes[0][i].spriteEntity.setScale(Vector2f(ENTITY_SCALE, ENTITY_SCALE));
		centipedes[0][i].spriteEntity.setPosition(roundByPixel(X_RESOLUTION * 0.55) - (i * PIXEL_SCALE), roundByPixel(Y_RESOLUTION * 0.11));

		entities.insert({ centipedes[0][i].spriteEntity.getPosition(), &centipedes[0][i] });
	} // End of initialization

	Event event;
	Clock timer;
	direction prevDir = RIGHT;
	ECE_Centipede centipedeController = ECE_Centipede();

	direction movement = NONE;
	bool acceptInput = false;
	bool unopened = true;
	bool paused = true;

	float deltaTime = 0;
	float elapsedTime = 0;

	// Update Loop
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape)) {
				window.close();
			}
			else if (!acceptInput)
			{
				if (event.type == Event::KeyReleased) {
					acceptInput = true;
					paused = !paused;
				}
			}
			else if (Keyboard::isKeyPressed(Keyboard::Return))
			{
				movement = NONE;
				acceptInput = false;
			}
			else if (Keyboard::isKeyPressed(Keyboard::Right))
			{
				movement = RIGHT;
			}
			else if (Keyboard::isKeyPressed(Keyboard::Down))
			{
				movement = DOWN;
			}
			else if (Keyboard::isKeyPressed(Keyboard::Left))
			{
				movement = LEFT;
			}
			else if (Keyboard::isKeyPressed(Keyboard::Up))
			{
				movement = UP;
			}
			else {
				movement = NONE;
			}
		}

		/*
		****************************************
		Update the scene
		****************************************
		*/
		if (paused)
		{
			window.clear();
			window.draw(startupScreenSprite);
			window.display();
		}
		else 
		{
			deltaTime = timer.restart().asSeconds();
			// If enough time has passed for 5 fps:
			if (elapsedTime >= 0.2f) {
				for (int i = 0; i < centipedes.size(); i++) {
					prevDir = centipedeController.moveCentipede(prevDir, centipedes[i]);
				}
				elapsedTime = 0;
			}
			elapsedTime += deltaTime;

			if (movement != NONE) {
				Vector2f prevPos = entityStarship->spriteEntity.getPosition();
				entityStarship->moved = true;
				switch (movement) {
				case UP:
					entityStarship->spriteEntity.move(0, SPEED * deltaTime * -1);
					if (entityStarship->spriteEntity.getPosition().y <= Y_RESOLUTION * 0.9)
					{
						entityStarship->spriteEntity.setPosition(prevPos);
					}
					break;
				case DOWN:
					entityStarship->spriteEntity.move(0, SPEED * deltaTime);
					if (entityStarship->spriteEntity.getPosition().y >= Y_RESOLUTION)
					{
						entityStarship->spriteEntity.setPosition(prevPos);
					}
					break;
				case LEFT:
					entityStarship->spriteEntity.move(SPEED * deltaTime * -1, 0);
					if (entityStarship->spriteEntity.getPosition().x <= 0)
					{
						entityStarship->spriteEntity.setPosition(prevPos);
					}
					break;
				case RIGHT:
					entityStarship->spriteEntity.move(SPEED * deltaTime, 0);
					if (entityStarship->spriteEntity.getPosition().x >= X_RESOLUTION)
					{
						entityStarship->spriteEntity.setPosition(prevPos);
					}
					break;
				default:
					break;
				}
			}

			/*
			****************************************
			Draw the scene
			****************************************
			*/
			window.clear();

			// Draw our game scene here
			window.draw(spriteBackground);

			// Draw the screen bottom and top
			window.draw(screenBottom);
			window.draw(screenTop);

			// Draw the score
			window.draw(scoreText);

			// Iterate over map and draw entities
			whereabouts::iterator it;
			vector<pair<Vector2f, entity*>> updates;
			for (it = entities.begin(); it != entities.end(); it++) {
				Sprite subject = it->second->spriteEntity;
				window.draw(subject);
				if (it->second->moved) {
					it->second->moved = false;
					updates.push_back({ it->second->spriteEntity.getPosition(), it->second });
				}
			}

			for (pair<Vector2f, entity*> update : updates) {
				entities.erase(update.second->spriteEntity.getPosition());
				entities[update.first] = update.second;

			}

			// Draw lives in the corner
			for (int i = 0; i < NUM_LIVES; i++) {
				window.draw(lives[i]);
			}

			// Show everything we just drew
			window.display();
		}
	}
	return 0;
}