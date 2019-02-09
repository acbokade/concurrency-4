#ifndef GAME_H
#define GAME_H
#include "SFML/Graphics.hpp"
#include "Box2D/Box2D.h"
#include "player.h"

class Game
{
public:
	Game();
	sf::RenderWindow *window ;
	b2World *world;
	sf::Texture groundTexture;
	sf::Sprite groundSprite;
	int velocityIterations = 10;
	int positionIterations = 10;
	float timeStep = 1.0f / 120.0f;
	void createGround(b2Vec2 position);
	void gameLoop();
};

#endif