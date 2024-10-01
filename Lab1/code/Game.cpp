#include "ProgramInfo.h"
#include "ECE_Centipede.h"
#include "materials.h"

using namespace sf;
using namespace std;

int main() {
	// Create and open a window for the game
	RenderWindow window(VideoMode(X_RESOLUTION, Y_RESOLUTION), "Centipede", Style::Default);

	// Prepare font
	font.loadFromFile("fonts/SEGOEPRB.TTF");

	// Prepare textures
	textureStarship.loadFromFile("graphics/Starship.png");
	textureSpider.loadFromFile("graphics/spider.png");
	textureStartup.loadFromFile("graphics/startup.png");
	textureFullMushroom.loadFromFile("graphics/Mushroom0.png");
	textureHalfMushroom.loadFromFile("graphics/Mushroom1.png");
	textureCentipedeHead.loadFromFile("graphics/CentipedeHead.png");
	textureCentipedeBody.loadFromFile("graphics/CentipedeBody.png");

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

	// Make a starship sprite
	Sprite spriteStarship;
	spriteStarship.setTexture(textureStarship);
	spriteStarship.setScale(Vector2f(2, 2));
	Vector2f position = Vector2f(X_RESOLUTION * 0.5, Y_RESOLUTION * 0.95);
	entities.insert({ position, Entity(spriteStarship, position, STARSHIP)});

	// Make a spider sprite
	Sprite spriteSpider;
	spriteSpider.setTexture(textureSpider);
	entities.insert({ spriteSpider.getPosition(), Entity(spriteSpider, spriteSpider.getPosition(), SPIDER) });

	float elapsedTime = 0.f;
	bool paused = true;

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
		lives[i].setPosition(X_RESOLUTION * 0.75 + (i * 50), (Y_RESOLUTION * 0.02) + 20);
	}

	// Random position generator
	default_random_engine generator;
	generator.seed(chrono::system_clock::now().time_since_epoch().count());
	uniform_int_distribution mushroomPositionX(0, X_RESOLUTION);
	uniform_int_distribution mushroomPositionY((int)(Y_RESOLUTION * 0.11), (int)(Y_RESOLUTION * 0.88));

	// Initialize each mushroom into the map
	for (int i = 0; i < NUM_MUSHROOMS; i++) {
		Vector2f position = Vector2f(((mushroomPositionX(generator) + 25) / 50) * 50, ((mushroomPositionY(generator) + 25) / 50) * 50);
		entities.insert({ position, Entity(Sprite(textureFullMushroom), position, MUSHROOM)});
	}
;

	direction prevDir = direction::LEFT;

	// Control the player input
	bool acceptInput = false;

	while (window.isOpen())
	{
		// score ++;
		Event event;
		while (window.pollEvent(event))
		{


			if (event.type == Event::KeyReleased && !paused)
			{
				// Listen for key presses again
				acceptInput = true;

				// hide the axe
				/*spriteAxe.setPosition(2000,
					spriteAxe.getPosition().y);
			}*/

			}

			/*
			****************************************
			Handle the players input
			****************************************
			*/

			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				window.close();
			}

			// Start the game
			if (Keyboard::isKeyPressed(Keyboard::Return))
			{
				paused = false;

				// Reset the time and the score
				score = 0;

				// Make all the branches disappear
			/*	for (int i = 1; i < NUM_MUSHROOMS; i++)
				{
					branchPositions_remove[i] = side::NONE;
				}*/

				acceptInput = true;


			}

			// Wrap the player controls to
			// Make sure we are accepting input
			if (acceptInput)
			{
				// More code here next...
				// First handle pressing the right cursor key
				if (Keyboard::isKeyPressed(Keyboard::Right))
				{
					// Make sure the player is on the right
					//playerSide = side::RIGHT;

					//score++;

					//// Add to the amount of time remaining
					//timeRemaining += (2 / score) + .15;

					//spriteAxe.setPosition(AXE_POSITION_RIGHT,
					//	spriteAxe.getPosition().y);

					//

					//spritePlayer.setPosition(1200, 720);

					//// update the branches
					//updateBranches(score);

					//// set the log flying to the left
					//spriteLog.setPosition(810, 720);
					//logSpeedX = -5000;
					//logActive = true;


					acceptInput = false;

				}

				//// Handle the left cursor key
				//if (Keyboard::isKeyPressed(Keyboard::Left))
				//{
				//	// Make sure the player is on the left
				//	playerSide = side::LEFT;

				//	score++;

				//	// Add to the amount of time remaining
				//	timeRemaining += (2 / score) + .15;

				//	spriteAxe.setPosition(AXE_POSITION_LEFT,
				//		spriteAxe.getPosition().y);


				//	spritePlayer.setPosition(580, 720);

				//	// update the branches
				//	updateBranches(score);

				//	// set the log flying
				//	spriteLog.setPosition(810, 720);
				//	logSpeedX = 5000;
				//	logActive = true;


				acceptInput = false;

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

			// Draw the starship
			//window.draw(spriteStarship);

			// Draw the spider
			//window.draw(spriteSpider);

			// Draw the score
			window.draw(scoreText);

			// Iterate over map and draw mushrooms
			for (int i = 0; i < entities.size(); i++) {
				window.draw(entities[i].spriteEntity);
			}

			//for (int i = 0; i < centipedes.size(); i++) {
			//	vector<Sprite> bodyParts = centipedes[i].bodyParts;
			//	bodyParts[0].setTexture(textureCentipedeHead);
			//	window.draw(bodyParts[0]);
			//	for (int j = 1; j < bodyParts.size(); j++) {
			//		bodyParts[j].setTexture(textureCentipedeBody);
			//		window.draw(bodyParts[j]);
			//	}
			//}

			// Draw lives in the corner
			for (int i = 0; i < NUM_LIVES; i++) {
				window.draw(lives[i]);
			}
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



