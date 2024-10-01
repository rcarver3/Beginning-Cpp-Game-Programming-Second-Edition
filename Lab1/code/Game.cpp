#include "ECE_Centipede.h"
#include "materials.h"

using namespace sf;
using namespace std;

int main() {
	// Create and open a window for the game
	RenderWindow window(VideoMode(X_RESOLUTION, Y_RESOLUTION), "Centipede", Style::Default);

	// Create a background sprite
	Sprite spriteBackground;
	spriteBackground.setColor(Color::Black);
	spriteBackground.setScale(X_RESOLUTION, Y_RESOLUTION);
	spriteBackground.setPosition(0, 0);

	// Make a startup screen sprite
	Sprite startupScreenSprite;
	startupScreenSprite.setTexture(textureStartup);

	// Figure out how to scale startup texture
	float x = (textureStartup.getSize().x > X_RESOLUTION) ? ((float)X_RESOLUTION / textureStartup.getSize().x) : (textureStartup.getSize().x / (float)X_RESOLUTION);
	float y = (textureStartup.getSize().y > Y_RESOLUTION) ? ((float)Y_RESOLUTION / textureStartup.getSize().y) : (textureStartup.getSize().y / (float)Y_RESOLUTION);
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
		Vector2f position = Vector2f(roundByFifty(X_RESOLUTION * 0.5), roundByFifty((Y_RESOLUTION * 0.95) + (i * 50)));

		entityStarship.spriteEntity.setTexture(textureStarship);
		entityStarship.spriteEntity.setOrigin(calculateOrigin(entityStarship));
		entityStarship.spriteEntity.setScale(Vector2f(2, 2));
		entityStarship.spriteEntity.setPosition(position);
		entityStarship.entityType = STARSHIP;

		entities.insert({ position, entityStarship });
	}

	// Make spider entities
	for (int i = 0; i < NUM_SPIDERS; i++) {
		entity entitySpider;
		Vector2f position = Vector2f(roundByFifty((X_RESOLUTION * 0.5) + (i * 200)), roundByFifty((Y_RESOLUTION * 0.95) + (i * 50)));

		entitySpider.spriteEntity.setTexture(textureSpider);
		entitySpider.spriteEntity.setOrigin(calculateOrigin(entitySpider));
		entitySpider.spriteEntity.setScale(Vector2f(2, 2));
		entitySpider.spriteEntity.setPosition(position);
		entitySpider.entityType = SPIDER;

		entities.insert({ position, entitySpider });
	}

	// Random position generator
	default_random_engine generator;
	generator.seed(chrono::system_clock::now().time_since_epoch().count());
	uniform_int_distribution mushroomPositionX(0, X_RESOLUTION);
	uniform_int_distribution mushroomPositionY((int)(Y_RESOLUTION * 0.11), (int)(Y_RESOLUTION * 0.88));

	// Initialize each mushroom into the map
	for (int i = 0; i < NUM_MUSHROOMS; i++) {
		entity entityMushroom;
		int x = mushroomPositionX(generator);
		int y = mushroomPositionY(generator);
		Vector2f position = Vector2f(roundByFifty(x), roundByFifty(y));

		entityMushroom.spriteEntity.setTexture(textureSpider);
		entityMushroom.spriteEntity.setOrigin(calculateOrigin(entityMushroom));
		entityMushroom.spriteEntity.setScale(Vector2f(2, 2));
		entityMushroom.spriteEntity.setPosition(position);
		entityMushroom.entityType = MUSHROOM;
		entityMushroom.currentState = HEALTHY;

		entities.insert({ position, entityMushroom });
	} 

	vector<ECE_Centipede> centipedes = { ECE_Centipede() };
	entity entityHead;
	entityHead.spriteEntity = centipedes[0].bodyParts[0];
	entityHead.entityType = HEAD;
	entityHead.currentState = HEALTHY;

	entities.insert({ entityHead.spriteEntity.getPosition(), entityHead });

	for (int i = 1; i < NUM_BODIES; i++) {
		entity entityBody;
		entityBody.spriteEntity = centipedes[0].bodyParts[i];
		entityBody.entityType = BODY;
		entityBody.currentState = HEALTHY;

		entities.insert({ entityBody.spriteEntity.getPosition(), entityBody });
	}
	// End of initialization

	// Update Loop
	while (window.isOpen())
	{
		Event event;
		Clock clock;

		while (window.pollEvent(event))
		{	
			if (event.type == Event::Closed) {
				window.close();
			}
			if (event.type == Event::KeyReleased && !paused) {
				acceptInput = true;
				movement = NONE;
			}				
			if (event.type == Event::KeyReleased && paused) {
				acceptInput = true;
			}
			if (acceptInput)
			{
				if (!paused) 
				{
					if (Keyboard::isKeyPressed(Keyboard::Escape)) 
					{
						paused = true;
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
					else {
						movement = NONE;
					}
				}	
				else {
					if (Keyboard::isKeyPressed(Keyboard::Escape) || Keyboard::isKeyPressed(Keyboard::Return)) {
						acceptInput = false;
						paused = false;
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
		} else {
			// Measure time
			float deltaTime = clock.restart().asSeconds();

			// If enough time has passed for 5 fps:
			if (elapsedTime >= 0.2f) {
				for (int i = 0; i < centipedes.size(); i++) {
					prevDir = centipedes[i].moveCentipede(prevDir);
					elapsedTime = 0.f;
				}
			}
			else {
				elapsedTime += deltaTime;
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
		for (pair<Vector2f, entity> i : entities) {
			window.draw(i.second.spriteEntity);
			if (i.first != i.second.spriteEntity.getPosition()) {
				entity temp = i.second;
				Vector2f newPos = i.second.spriteEntity.getPosition();
				entities[newPos] = i.second;
				entities.erase(i.first);
			}
		}

		// Draw lives in the corner
		for (int i = 0; i < NUM_LIVES; i++) {
			window.draw(lives[i]);
		}

		// Show everything we just drew
		window.display();
	}
	return 0;
}

//// Function definition
//void updateBranches(int seed)
//{
//	// Move all the branches down one place
//	for (int j = NUM_MUSHROOMS - 1; j > 0; j--) {
//		branchPositions_remove[j] = branchPositions_remove[j - 1];
//	}
//
//	// Spawn a new branch at position 0
//	// LEFT, RIGHT or NONE
//	srand((int)time(0) + seed);
//	int r = (rand() % 5);
//
//	switch (r) {
//	case 0:
//		branchPositions_remove[0] = side::LEFT;
//		break;
//
//	case 1:
//		branchPositions_remove[0] = side::RIGHT;
//		break;
//
//	default:
//		branchPositions_remove[0] = side::NONE;
//		break;
//	}
//
//
//}



