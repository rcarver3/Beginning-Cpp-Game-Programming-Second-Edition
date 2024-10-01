#include "materials.h"

using namespace sf;

Texture textureStarship;
Texture textureSpider;
Texture textureStartup;
Texture textureFullMushroom;
Texture textureHalfMushroom;
Texture textureCentipedeHead;
Texture textureCentipedeBody;

Font font;

static void loadMaterials() {
	// Prepare textures
	textureStarship.loadFromFile("graphics/Starship.png");
	textureSpider.loadFromFile("graphics/spider.png");
	textureStartup.loadFromFile("graphics/startup.png");
	textureFullMushroom.loadFromFile("graphics/Mushroom0.png");
	textureHalfMushroom.loadFromFile("graphics/Mushroom1.png");
	textureCentipedeHead.loadFromFile("graphics/CentipedeHead.png");
	textureCentipedeBody.loadFromFile("graphics/CentipedeBody.png");

	// Prepare font
	font.loadFromFile("font/SEGOEPRB.TTF");
}