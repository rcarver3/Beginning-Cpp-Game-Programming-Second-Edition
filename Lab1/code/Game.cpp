#include "types.h"
#include "constants.h"
#include "ECE_Centipede.h"
#include "Game.h"
#include <iostream>

using namespace sf;
using namespace std;

std::vector<Sprite> lives(NUM_LIVES);
direction movement = NONE;
float elapsedTime = 0.f;
bool paused = true;
bool acceptInput = false;
whereabouts entities = whereabouts(NUM_TOTAL_ENTITIES);

Vector2f calculateOrigin(entity object) {
	return object.spriteEntity.getLocalBounds().getSize() * 0.5f;
}

int roundBy25(float num) {
	return (((static_cast<int>(num) + (25 / 2)) / 25) * 25);
}

int main() {
	// Create and open a window for the game
	RenderWindow window(VideoMode((int)X_RESOLUTION, (int)Y_RESOLUTION), "Centipede!!", Style::Default);

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
		lives[i].setScale(Vector2f(2, 2));
		lives[i].setPosition((X_RESOLUTION * 0.75 + (i * 50)), (Y_RESOLUTION * 0.02) + 20);
	}

	// Make starship entities
	for (int i = 0; i < NUM_SHIPS; i++) {
		entity entityStarship;
		Vector2f position = Vector2f(roundBy25(X_RESOLUTION * 0.5), roundBy25((Y_RESOLUTION * 0.95) + (i * 50)));

		entityStarship.spriteEntity.setTexture(textureStarship);
		entityStarship.spriteEntity.setOrigin(calculateOrigin(entityStarship));
		entityStarship.spriteEntity.setScale(Vector2f(2, 2));
		entityStarship.spriteEntity.setPosition(position);
		entityStarship.entityType = STARSHIP;

		entities.insert({ position, &entityStarship });
	}

	// Make spider entities
	for (int i = 0; i < NUM_SPIDERS; i++) {
		entity entitySpider;
		Vector2f position = Vector2f(roundBy25((X_RESOLUTION * 0.5) + (i * 200)), roundBy25((Y_RESOLUTION * 0.50) + (i * 50)));

		entitySpider.spriteEntity.setTexture(textureSpider);
		entitySpider.spriteEntity.setOrigin(calculateOrigin(entitySpider));
		entitySpider.spriteEntity.setScale(Vector2f(2, 2));
		entitySpider.spriteEntity.setPosition(position);
		entitySpider.entityType = SPIDER;

		entities.insert({ position, &entitySpider });
	}

	// Random position generator
	default_random_engine generator;
    uniform_int_distribution<int> mushroomPositionX(0, X_RESOLUTION);
	uniform_int_distribution<int> mushroomPositionY(Y_RESOLUTION * 0.11, Y_RESOLUTION * 0.88);

	// Initialize each mushroom into the map
	for (int i = 0; i < NUM_MUSHROOMS; i++) {
		entity* entityMushroom = new entity();
		generator.seed(chrono::system_clock::now().time_since_epoch().count());
		Vector2f position = Vector2f(roundBy25(mushroomPositionX(generator)), roundBy25(mushroomPositionY(generator)));
		// cout << "x: " + to_string(position.x) + " y: " + to_string(position.y) + '\n';

		entityMushroom->spriteEntity.setTexture(textureFullMushroom);
		entityMushroom->spriteEntity.setOrigin(calculateOrigin(*entityMushroom));
		entityMushroom->spriteEntity.setScale(Vector2f(2, 2));
		entityMushroom->spriteEntity.setPosition(position);
		entityMushroom->entityType = MUSHROOM;
		entityMushroom->currentState = HEALTHY;

		entities.insert({ position, entityMushroom });
	}

	vector<vector<entity>> centipedes = { vector<entity>(NUM_BODIES, entity()) };

	centipedes[0][0].spriteEntity.setTexture(textureCentipedeHead);
	centipedes[0][0].spriteEntity.setOrigin(calculateOrigin(centipedes[0][0]));
	centipedes[0][0].spriteEntity.setScale(Vector2f(2, 2));
	centipedes[0][0].spriteEntity.setPosition(roundBy25(X_RESOLUTION * 0.55), roundBy25(Y_RESOLUTION * 0.11));
	centipedes[0][0].entityType = HEAD;
	centipedes[0][0].currentState = HEALTHY;

	entities.insert({ centipedes[0][0].spriteEntity.getPosition(), &centipedes[0][0] });

	for (int i = 1; i < NUM_BODIES; i++) {
		centipedes[0][i].spriteEntity.setTexture(textureCentipedeBody);
		centipedes[0][i].spriteEntity.setOrigin(calculateOrigin(centipedes[0][i]));
		centipedes[0][i].spriteEntity.setScale(Vector2f(2, 2));
		centipedes[0][i].spriteEntity.setPosition(roundBy25(X_RESOLUTION * 0.55) - (i * FOLLOW_DISTANCE), roundBy25(Y_RESOLUTION * 0.11));
		centipedes[0][i].entityType = BODY;
		centipedes[0][i].currentState = HEALTHY;

		entities.insert({ centipedes[0][i].spriteEntity.getPosition(), &centipedes[0][i] });
	} // End of initialization

	Event event = Event();
	Clock clock = Clock();
	direction prevDir = RIGHT;
	ECE_Centipede centipedeController = ECE_Centipede();

	bool acceptInput = true;
	bool unopened = true;
	bool paused = true;

	// Update Loop
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) {
				window.close();
			}
			if (!unopened && event.type == Event::KeyReleased) {
				paused = !paused;
				acceptInput = true;
			}
			if (acceptInput)
			{
				if (unopened) {
					if (Keyboard::isKeyPressed(Keyboard::Return)) {
						unopened = false;
						acceptInput = false;
					}
				}
				else if (!paused)
				{
					if (Keyboard::isKeyPressed(Keyboard::Escape))
					{
						movement = NONE;
						acceptInput = false;
					}
					else if (Keyboard::isKeyPressed(Keyboard::Right))
					{
						movement = RIGHT;
						acceptInput = false;
					}
					else if (Keyboard::isKeyPressed(Keyboard::Down))
					{
						movement = DOWN;
						acceptInput = false;
					}
					else if (Keyboard::isKeyPressed(Keyboard::Left))
					{
						movement = LEFT;
						acceptInput = false;
					}
					else if (Keyboard::isKeyPressed(Keyboard::Up))
					{
						movement = UP;
						acceptInput = false;
					}
					else if (Keyboard::isKeyPressed(Keyboard::Escape) || Keyboard::isKeyPressed(Keyboard::Return)) {
						acceptInput = false;
					}
					else {
						movement = NONE;
					}
				}
			}
		}

		/*
		****************************************
		Update the scene
		****************************************
		*/
		if (paused) {
			window.clear();
			window.draw(startupScreenSprite);
			window.display();
		}
		else {
			// If enough time has passed for 5 fps:
			if (clock.getElapsedTime().asSeconds() >= 0.2f) {
				for (int i = 0; i < centipedes.size(); i++) {
					prevDir = centipedeController.moveCentipede(prevDir, centipedes[i]);
				}
				clock.restart();
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