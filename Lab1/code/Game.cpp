/*
Author: Rhett Carver
Class: ECE4122
Last Date Modified: 10/2/24
Description:
The main function, consisting of initialization and the game loop.
*/

#include "types.h"
#include "constants.h"
#include "Game.h"
#include <iostream>

using namespace sf;
using namespace std;

std::vector<Sprite> lives(NUM_LIVES);
whereabouts entities = whereabouts(NUM_TOTAL_ENTITIES);

int score = 0;

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

	// Make spider entity
	entity* entitySpider = new entity(Sprite(textureSpider), SPIDER);
	Vector2f spiderPosition = Vector2f(roundByPixel(X_RESOLUTION * 0.5), roundByPixel(Y_RESOLUTION * 0.50));
	entitySpider->spriteEntity.setPosition(spiderPosition);
	entities.insert({ spiderPosition, entitySpider });

	entity* spider = entitySpider;

	// Random position generator
	default_random_engine generator;
    uniform_int_distribution<int> mushroomPositionX(0, X_RESOLUTION);
	uniform_int_distribution<int> mushroomPositionY(Y_RESOLUTION * 0.15, Y_RESOLUTION * 0.88);

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
	Clock spiderTimer;
	ECE_Centipede centipedeController = ECE_Centipede();
	Laser laser = Laser();

	direction prevDir = RIGHT;
	direction movement = NONE;
	pair<direction, direction> spiderMovement = { UP, RIGHT };

	float spiderTime = 0;
	float deltaSpiderTime = 0;

	bool acceptInput = false;
	bool unopened = true;
	bool paused = true;

	float deltaTime = 0;
	float elapsedTime = 0;

	Vector2f spiderPos;
	Vector2f spiderVelocity;

	int deaths = 0;

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
				}
			}
			else if (Keyboard::isKeyPressed(Keyboard::Return))
			{
				movement = NONE;
				acceptInput = false;
				paused = !paused;
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
			else if (Keyboard::isKeyPressed(Keyboard::Space))
			{
				movement = NONE;
				laser.fireLaser(entityStarship->spriteEntity.getPosition());
				acceptInput = false;
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
		else if (deaths == NUM_LIVES)
		{
			window.clear();
			window.draw(startupScreenSprite);
			window.display();
			paused = true;
		}
		else 
		{	
			Vector2f centipedePrevPos;
			deltaSpiderTime = spiderTimer.restart().asSeconds();
			deltaTime = timer.restart().asSeconds();
			// If enough time has passed for 5 fps:
			if (elapsedTime >= 0.2f) {
				for (int i = 0; i < centipedes.size(); i++) {
					prevDir = centipedeController.moveCentipede(prevDir, centipedes[i]);
					if (prevDir == GAMEOVER) {
						lives[deaths].setColor(Color::Transparent);
						deaths++;
						Vector2f position = Vector2f(roundByPixel(X_RESOLUTION * 0.5), roundByPixel((Y_RESOLUTION * 0.95)));
						entityStarship->spriteEntity.setPosition(position);
					}
				}
				elapsedTime = 0;
			}
			elapsedTime += deltaTime;

			movePlayer(entityStarship, movement, deltaTime);

			spiderPos = spider->spriteEntity.getPosition();
			spiderVelocity = Vector2f(0, 0);
			spiderTime += deltaSpiderTime;

			if (spiderPos.x <= 0) {
				spiderMovement = { UP, RIGHT };
			}
			else if (spiderPos.x >= X_RESOLUTION) {
				spiderMovement = { DOWN, LEFT };
			}
			else if (spiderPos.y <= Y_RESOLUTION * 0.1) {
				spiderMovement = { DOWN, LEFT };
			}
			else if (spiderPos.y >= Y_RESOLUTION) {
				spiderMovement = { UP, RIGHT };
			}
			else if (spiderTime >= 1)
			{
				direction choice;
				srand(chrono::system_clock::now().time_since_epoch().count());
				choice = (direction)(rand() % 4);
				switch (choice) {
				case UP:
					spiderMovement.first = UP;
					break;
				case DOWN:
					spiderMovement.first = DOWN;
					break;
				case LEFT:
					spiderMovement.first = LEFT;
					break;
				case RIGHT:
					spiderMovement.first = RIGHT;
					break;
				default:
					spiderMovement.first = DOWN;
					break;
				}

				choice = (direction)(rand() % 4);
				switch (choice) {
				case UP:
					spiderMovement.second = UP;
					break;
				case DOWN:
					spiderMovement.second = DOWN;
					break;
				case LEFT:
					spiderMovement.second = LEFT;
					break;
				case RIGHT:
					spiderMovement.second = RIGHT;
					break;
				default:
					spiderMovement.second = DOWN;
					break;
				}
				spiderTime = 0;
			}			

			switch (spiderMovement.first) {
			case UP:
				spiderVelocity += Vector2f(0, SPEED * deltaSpiderTime * -1);
				break;
			case DOWN:
				spiderVelocity += Vector2f(0, SPEED * deltaSpiderTime);
				break;
			case LEFT:
				spiderVelocity += Vector2f(SPEED * deltaSpiderTime * -1, 0);
				break;
			case RIGHT:
				spiderVelocity += Vector2f(SPEED * deltaSpiderTime, 0);
				break;
			default:
				spiderVelocity += Vector2f(0, SPEED * deltaSpiderTime);
				break;
			}
			switch (spiderMovement.second) {
			case UP:
				spiderVelocity += Vector2f(0, SPEED * deltaSpiderTime * -1);
				break;
			case DOWN:
				spiderVelocity += Vector2f(0, SPEED * deltaSpiderTime);
				break;
			case LEFT:
				spiderVelocity += Vector2f(SPEED * deltaSpiderTime * -1, 0);
				break;
			case RIGHT:
				spiderVelocity += Vector2f(SPEED * deltaSpiderTime, 0);
				break;
			default:
				spiderVelocity += Vector2f(0, SPEED * deltaSpiderTime);
				break;
			}

			spider->spriteEntity.move(spiderVelocity);
			Vector2f newPosition = spider->spriteEntity.getPosition();
			Vector2f roundedPosition = Vector2f(roundByPixel(newPosition.x), roundByPixel(newPosition.y));

			cout << "Spider New Position: " << newPosition.x << ", " << newPosition.y << endl;
			for (int i = 0; i < laser.lasers.size(); i++) {
				if (spider->spriteEntity.getGlobalBounds().intersects(laser.lasers[i].getGlobalBounds())) {
					spider->currentState = EMPTY;
					score += 300;
				}
			}
			if (entities.count(roundedPosition)) {
				if (entities.at(roundedPosition)->entityType == SPIDER) {
				entities.erase(Vector2f(roundByPixel(spiderPos.x), roundByPixel(spiderPos.y))); // Erase the old position
				// Erase the old position
				entities[roundedPosition] = spider;
				}
				else if (entities.at(roundedPosition)->entityType == MUSHROOM) {
					entities.at(roundedPosition)->currentState = EMPTY;
					entities.erase(roundedPosition);
				}
				else if (entities.at(roundedPosition)->entityType == STARSHIP) {
					lives[deaths].setColor(Color::Transparent);
					deaths++;
					spider->spriteEntity.setPosition(X_RESOLUTION * 0.5, Y_RESOLUTION * 0.5);
					Vector2f position = Vector2f(roundByPixel(X_RESOLUTION * 0.5), roundByPixel((Y_RESOLUTION * 0.95)));
					entityStarship->spriteEntity.setPosition(position);
				}
				else {
					entities.erase(Vector2f(roundByPixel(spiderPos.x), roundByPixel(spiderPos.y))); // Erase the old position
					// Erase the old position
					entities[roundedPosition] = spider;
				}
			}
				//spider->spriteEntity.setPosition(spiderPos + Vector2f(50, 50));
				//newPosition = spider->spriteEntity.getPosition();
				//entities.erase(spiderPos);
				//entities[newPosition] = spider;
			
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
			scoreText.setString(to_string(score));
			window.draw(scoreText);

			// Iterate over map and draw entities
			whereabouts::iterator it;
			vector<pair<Vector2f, entity*>> updates;
			for (it = entities.begin(); it != entities.end(); it++) {
				Sprite subject = it->second->spriteEntity;
				if (it->second->entityType == MUSHROOM) {
					if (it->second->currentState == DAMAGED) {
						subject.setTexture(textureHalfMushroom);
					}
					else if (it->second->currentState == EMPTY) {
						entities.erase(it->first);
						continue;
					}
				}
				window.draw(subject);
				if (it->second->moved) {
					it->second->moved = false;
					//updates.push_back({ Vector2f(roundByPixel(it->second->spriteEntity.getPosition().x), roundByPixel(it->second->spriteEntity.getPosition().y)), it->second });
				}
			}

			for (pair<Vector2f, entity*> update : updates) {
				Vector2f oldPos = update.second->spriteEntity.getPosition();
				Vector2f newPos = update.first;
				entities.erase(oldPos);
				entities[newPos] = update.second;
			}
			
			laser.moveLasers(deltaTime);
            for (int i = 0; i < laser.lasers.size(); i++) {
                sf::RectangleShape laserRect(sf::Vector2f(8, 20));
                laserRect.setFillColor(sf::Color::Red);
                laserRect.setPosition(laser.lasers[i].getPosition().x, laser.lasers[i].getPosition().y);
                window.draw(laserRect);
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

void movePlayer(entity* player, direction dir, float deltaTime)
{
	Vector2f prevPos = player->spriteEntity.getPosition();
	player->moved = true;
	switch (dir) {
	case UP:
		player->spriteEntity.move(0, SPEED * deltaTime * -1);
		if (player->spriteEntity.getPosition().y <= Y_RESOLUTION * 0.9)
		{
			player->spriteEntity.setPosition(prevPos);
			player->moved = false;
		}
		break;
	case DOWN:
		player->spriteEntity.move(0, SPEED * deltaTime);
		if (player->spriteEntity.getPosition().y >= Y_RESOLUTION)
		{
			player->spriteEntity.setPosition(prevPos);
			player->moved = false;
		}
		break;
	case LEFT:
		player->spriteEntity.move(SPEED * deltaTime * -1, 0);
		if (player->spriteEntity.getPosition().x <= 0)
		{
			player->spriteEntity.setPosition(prevPos);
			player->moved = false;
		}
		break;
	case RIGHT:
		player->spriteEntity.move(SPEED * deltaTime, 0);
		if (player->spriteEntity.getPosition().x >= X_RESOLUTION)
		{
			player->spriteEntity.setPosition(prevPos);
			player->moved = false;
		}
		break;
	default:
		break;
	}

	if (player->moved) {
		entities.erase(prevPos);
		Vector2f newPos = Vector2f(roundByPixel(player->spriteEntity.getPosition().x), roundByPixel(player->spriteEntity.getPosition().y));
		entities[player->spriteEntity.getPosition()] = player;
	}
}