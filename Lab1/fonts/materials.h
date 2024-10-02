#pragma once
#include "types.h"
#include <SFML/Graphics.hpp>

extern sf::Texture textureStarship;
extern sf::Texture textureSpider;
extern sf::Texture textureStartup;
extern sf::Texture textureFullMushroom;
extern sf::Texture textureHalfMushroom;
extern sf::Texture textureCentipedeHead;
extern sf::Texture textureCentipedeBody;

extern sf::Font font;

void loadMaterials();
void ensureMaterialsLoaded();