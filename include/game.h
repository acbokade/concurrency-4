#ifndef GAME_H
#define GAME_H
#include "SFML/Graphics.hpp"
#include "Box2D/Box2D.h"
#include "player.h"
#include "myListener.h"
#include <queue>
#include <time.h>
#include <sys/time.h>

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
	myListener* listener;
	std::thread worker[30];
	std::mutex m;
    Player* player1;
    Player* player2;
	struct timeval current_time,prev_time;
	double time_difference;
	void createGround(b2Vec2 position);
	void gameLoop();
	void checkcollision();
	void decrease_hp();
};

#endif