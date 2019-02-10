#ifndef GAME_H
#define GAME_H
#include "SFML/Graphics.hpp"
#include "Box2D/Box2D.h"
#include "player.h"
#include "myListener.h"
#include <queue>
#include <time.h>
#include <sys/time.h>
#include <thread>
#include <queue>
#include <mutex>

class Game
{
public:
	Game();
	sf::RenderWindow *window ;
	b2World* world;
	b2Body* ground;
	sf::Texture groundTexture;
	sf::Sprite groundSprite;
	int velocityIterations = 10;
	int positionIterations = 10;
	float timeStep = 1.0f / 240.0f;
	myListener* listener;
	std::thread worker[30];
	std::mutex m;
    Player* player1;
    Player* player2;
	struct timeval current_time,prev_time;
	double time_difference;
	b2Body* createGround(b2Vec2 position, int data);
	void initPlayer(Player *player, float X);
	void gameLoop();
	void updatePlayer(Player *player);
	void draw(Player *player);
	void checkcollision();
	void decrease_hp(int a, int b);
};

#endif