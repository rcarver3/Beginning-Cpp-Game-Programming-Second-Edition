// Include important C++ libraries here
#include <sstream>
#include <SFML/Graphics.hpp>
#include "ECE_Centipede.hpp"
#include <vector>
#include <random>
#include <list>
#include <chrono>

// Make code easier to type with "using namespace"
using namespace sf;

enum class state {
	EMPTY,
	HEALTHY_MUSHROOM,
	DESTROYED_MUSHROOM
};

struct mushroom {
	Sprite spriteMushroom;
	state currentState;
};

// Function declaration
// void updateBranches(int seed);

const int NUM_MUSHROOMS = 30;

// Where is the player/branch? 
// Left or Right
//enum class side { LEFT, RIGHT, NONE };
//side branchPositions_remove[NUM_MUSHROOMS];


int main()
{
	// Create and open a window for the game
	RenderWindow window(VideoMode(1920, 1080), "Centipede", Style::Fullscreen);

	// Create a sprite
	Sprite spriteBackground;

	// Attach the texture to the sprite
	spriteBackground.setColor(Color::Black);

	// Set the spriteBackground to cover the screen
	spriteBackground.setScale(1920, 1080);
	spriteBackground.setPosition(0, 0);

	// Make a tree sprite
	Texture textureStarship;
	textureStarship.loadFromFile("graphics/Starship.png");
	Sprite spriteStarship;
	spriteStarship.setScale(Vector2f(1.5, 1.5));
	spriteStarship.setTexture(textureStarship);
	spriteStarship.setOrigin(Vector2f(7, 11));
	spriteStarship.setPosition(960, 1000);

	// Prepare the bee
	Texture textureSpider;
	textureSpider.loadFromFile("graphics/spider.png");
	Sprite spriteSpider;
	spriteSpider.setTexture(textureSpider);
	spriteSpider.setPosition(0, 800);


	//// Position the clouds off screen
	//spriteCloud1.setPosition(0, 0);
	//spriteCloud2.setPosition(0, 150);
	//spriteCloud3.setPosition(0, 300);

	//// Are the clouds currently on screen?
	//bool cloud1Active = false;
	//bool cloud2Active = false;
	//bool cloud3Active = false;

	//// How fast is each cloud?
	//float cloud1Speed = 0.0f;
	//float cloud2Speed = 0.0f;
	//float cloud3Speed = 0.0f;

	// Variables to control time itself
	Clock clock;

	// Bottom and top of screen
	RectangleShape screenBottom;
	screenBottom.setSize(Vector2f(1920, 100));
	screenBottom.setFillColor(Color::Yellow);
	screenBottom.setPosition(0, 980);

	RectangleShape screenTop;
	screenTop.setSize(Vector2f(1920, 100));
	screenTop.setFillColor(Color::Yellow);
	screenTop.setPosition(0, 0);

	Time gameTimeTotal;
	float timeRemaining = 6.0f;

	// Track whether the game is running
	bool paused = true;
	// Draw some text
	int score = 0;

	sf::Text messageText;
	sf::Text scoreText;

	// We need to choose a font
	sf::Font font;
	font.loadFromFile("fonts/JOKERMAN.ttf");

	// Set the font to our message
	messageText.setFont(font);
	scoreText.setFont(font);

	// Assign the actual message
	messageText.setString("Press Enter to start!");
	scoreText.setString("Score = 0");

	// Make it really big
	messageText.setCharacterSize(75);
	scoreText.setCharacterSize(100);

	// Choose a color
	messageText.setFillColor(Color::White);
	scoreText.setFillColor(Color::White);

	// Position the text
	FloatRect textRect = messageText.getLocalBounds();

	messageText.setOrigin(textRect.left +
		textRect.width / 2.0f,
		textRect.top +
		textRect.height / 2.0f);

	messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);

	scoreText.setPosition(20, 20);

	// Random position generator
	default_random_engine generator;
	generator.seed(chrono::system_clock::now().time_since_epoch().count());
	uniform_int_distribution mushroomPositionX(0, 1920);
	uniform_int_distribution mushroomPositionY(120, 960);

	// Prepare two different textures for mushroom
	Texture textureMushroom;
	textureMushroom.loadFromFile("graphics/Mushroom0.png");

	map<pair<float, float>, mushroom> mushrooms;

	// Initialize each mushroom into the map
	for (int i = 0; i < NUM_MUSHROOMS; i++) {
		Vector2f position = Vector2f(mushroomPositionX(generator), mushroomPositionY(generator));
		mushroom oneMushroom;
		oneMushroom.spriteMushroom.setTexture(textureMushroom);
		oneMushroom.currentState = state::HEALTHY_MUSHROOM;
		oneMushroom.spriteMushroom.setOrigin(11, 12);
		oneMushroom.spriteMushroom.setPosition(position);

		mushrooms.insert({ pair(position.x, position.y), oneMushroom });
	}

	// Some other useful log related variables
	bool logActive = false;
	float logSpeedX = 1000;
	float logSpeedY = -1500;
	
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
			timeRemaining = 6;

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
		if (!paused)
		{

			// Measure time
			Time dt = clock.restart();

			// Subtract from the amount of time remaining
			timeRemaining -= dt.asSeconds();


			if (timeRemaining <= 0.0f) {

				// Pause the game
				paused = true;

				// Change the message shown to the player
				messageText.setString("Out of time!!");

				//Reposition the text based on its new size
				FloatRect textRect = messageText.getLocalBounds();
				messageText.setOrigin(textRect.left +
					textRect.width / 2.0f,
					textRect.top +
					textRect.height / 2.0f);

				messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
			}


			//// Setup the bee
			//if (!beeActive)
			//{

			//	// How fast is the bee
			//	srand((int)time(0) * 10);
			//	beeSpeed = (rand() % 200) + 200;

			//	// How high is the bee
			//	srand((int)time(0) * 10);
			//	float height = (rand() % 500) + 500;
			//	spriteSpider.setPosition(2000, height);
			//	beeActive = true;

			//}
			//else
			//	// Move the bee
			//{

			//	spriteSpider.setPosition(
			//		spriteSpider.getPosition().x -
			//		(beeSpeed * dt.asSeconds()),
			//		spriteSpider.getPosition().y);

			//	// Has the bee reached the right hand edge of the screen?
			//	if (spriteSpider.getPosition().x < -100)
			//	{
			//		// Set it up ready to be a whole new cloud next frame
			//		beeActive = false;
			//	}
			//}

			// Manage the clouds
			// Cloud 1
			//if (!cloud1Active)
			//{

			//	// How fast is the cloud
			//	srand((int)time(0) * 10);
			//	cloud1Speed = (rand() % 200);

			//	// How high is the cloud
			//	srand((int)time(0) * 10);
			//	float height = (rand() % 150);
			//	spriteCloud1.setPosition(-200, height);
			//	cloud1Active = true;


			//}
			//else
			//{

			//	spriteCloud1.setPosition(
			//		spriteCloud1.getPosition().x +
			//		(cloud1Speed * dt.asSeconds()),
			//		spriteCloud1.getPosition().y);

			//	// Has the cloud reached the right hand edge of the screen?
			//	if (spriteCloud1.getPosition().x > 1920)
			//	{
			//		// Set it up ready to be a whole new cloud next frame
			//		cloud1Active = false;
			//	}
			//}
			//// Cloud 2
			//if (!cloud2Active)
			//{

			//	// How fast is the cloud
			//	srand((int)time(0) * 20);
			//	cloud2Speed = (rand() % 200);

			//	// How high is the cloud
			//	srand((int)time(0) * 20);
			//	float height = (rand() % 300) - 150;
			//	spriteCloud2.setPosition(-200, height);
			//	cloud2Active = true;


			//}
			//else
			//{

			//	spriteCloud2.setPosition(
			//		spriteCloud2.getPosition().x +
			//		(cloud2Speed * dt.asSeconds()),
			//		spriteCloud2.getPosition().y);

			//	// Has the cloud reached the right hand edge of the screen?
			//	if (spriteCloud2.getPosition().x > 1920)
			//	{
			//		// Set it up ready to be a whole new cloud next frame
			//		cloud2Active = false;
			//	}
			//}

			//if (!cloud3Active)
			//{

			//	// How fast is the cloud
			//	srand((int)time(0) * 30);
			//	cloud3Speed = (rand() % 200);

			//	// How high is the cloud
			//	srand((int)time(0) * 30);
			//	float height = (rand() % 450) - 150;
			//	spriteCloud3.setPosition(-200, height);
			//	cloud3Active = true;


			//}
			//else
			//{

			//	spriteCloud3.setPosition(
			//		spriteCloud3.getPosition().x +
			//		(cloud3Speed * dt.asSeconds()),
			//		spriteCloud3.getPosition().y);

			//	// Has the cloud reached the right hand edge of the screen?
			//	if (spriteCloud3.getPosition().x > 1920)
			//	{
			//		// Set it up ready to be a whole new cloud next frame
			//		cloud3Active = false;
			//	}
			//}

			// Update the score text
			std::stringstream ss;
			ss << "Score = " << score;
			scoreText.setString(ss.str());

			//// update the branch sprites
			//for (int i = 0; i < NUM_MUSHROOMS; i++)
			//{

			//	float height = i * 150;

			//	if (branchPositions_remove[i] == side::LEFT)
			//	{
			//		// Move the sprite to the left side
			//		mushrooms[i].setPosition(610, height);
			//		// Flip the sprite round the other way
			//		mushrooms[i].setOrigin(220, 40);
			//		mushrooms[i].setRotation(180);
			//	}
			//	else if (branchPositions_remove[i] == side::RIGHT)
			//	{
			//		// Move the sprite to the right side
			//		mushrooms[i].setPosition(1330, height);
			//		// Set the sprite rotation to normal
			//		mushrooms[i].setOrigin(220, 40);
			//		mushrooms[i].setRotation(0);

			//	}
			//	else
			//	{
			//		// Hide the branch
			//		mushrooms[i].setPosition(3000, height);
			//	}
			//}

			// Handle a flying log				
			//if (logActive)
			//{

			//	spriteLog.setPosition(
			//		spriteLog.getPosition().x + (logSpeedX * dt.asSeconds()),
			//		spriteLog.getPosition().y + (logSpeedY * dt.asSeconds()));

			//	// Has the insect reached the right hand edge of the screen?
			//	if (spriteLog.getPosition().x < -100 ||
			//		spriteLog.getPosition().x > 2000)
			//	{
			//		// Set it up ready to be a whole new cloud next frame
			//		logActive = false;
			//		spriteLog.setPosition(810, 720);
			//	}
			//}

			// has the player been squished by a branch?
			//if (branchPositions_remove[5] == playerSide)
			//{
			//	// death
			//	paused = true;
			//	acceptInput = false;

			//	// Draw the gravestone
			//	spriteRIP.setPosition(525, 760);

			//	// hide the player
			//	spritePlayer.setPosition(2000, 660);

			//	// Change the text of the message
			//	messageText.setString("SQUISHED!!");

			//	// Center it on the screen
			//	FloatRect textRect = messageText.getLocalBounds();

			//	messageText.setOrigin(textRect.left +
			//		textRect.width / 2.0f,
			//		textRect.top + textRect.height / 2.0f);

			//	messageText.setPosition(1920 / 2.0f,
			//		1080 / 2.0f);

			//}


		}// End if(!paused)

		 /*
		 ****************************************
		 Draw the scene
		 ****************************************
		 */

		 // Clear everything from the last frame
		window.clear();

		// Draw our game scene here
		window.draw(spriteBackground);

		// Draw the screen bottom and top
		window.draw(screenBottom);
		window.draw(screenTop);

		// Draw the clouds
		/*window.draw(spriteCloud1);
		window.draw(spriteCloud2);
		window.draw(spriteCloud3);*/

		// Draw the branches
		/*for (int i = 0; i < NUM_MUSHROOMS; i++) {
			window.draw(mushrooms[i]);
		}*/

		// Draw the starship
		window.draw(spriteStarship);

		// Draw the spider
		window.draw(spriteSpider);

		// Draw the score
		window.draw(scoreText);


		// Iterate over map and draw mushrooms
		map<pair<float, float>, mushroom>::iterator it;
		for (it = mushrooms.begin(); it != mushrooms.end(); it++) {
			window.draw(it->second.spriteMushroom);
		}

		if (paused)
		{
			// Draw our message
			window.draw(messageText);
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



