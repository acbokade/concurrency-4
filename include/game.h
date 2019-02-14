#ifndef GAME_H
#define GAME_H
#include "SFML/Graphics.hpp"
#include "Box2D/Box2D.h"
#include "player.h"
#include "myListener.h"
#include "SFML/Network.hpp"
#include "SFML/Audio.hpp"
#include <queue>
#include <time.h>
#include <sys/time.h>
#include <thread>
#include <queue>
#include <mutex>
#include "State.hpp"
#include "Game.hpp"
#include <utility>
#include <bits/stdc++.h>

namespace stickman {
class Game
{
public:
	Game(GameDataRef data);
	sf::RenderWindow *window ;
	sf::IpAddress ip;
	sf::TcpSocket socket;
	b2World* world;
	b2Body* ground;
	int groundUserData;
	sf::Texture groundTexture;
	sf::Sprite groundSprite;
	sf::Texture gemTexture;
	sf::Sprite gemSprite;
	int velocityIterations = 10;
	int positionIterations = 10;
	float timeStep = 1.0f / 240.0f;
	myListener* listener;
	std::thread worker[30];
	std::thread Thread, Thread1;
	bool isClient;
	bool gemExists;
	std::mutex m;
    Player* player1;
    Player* player2;
    std::pair<int,int> p;
    sf::SoundBuffer buffer;
    sf::Sound sound;
	struct timeval current_time,prev_time,current_time1, prev_time1;
	double time_difference, time_difference1;
	b2Body* createGround(b2Vec2 position);
	void initPlayer(Player *player, float X, int offset);
	void gameLoop();
	void updatePlayer(Player *player);
	void draw(Player *player);
	void checkcollision();
	void decrease_hp(int a, int b);
	void generateGem();
	void isGemCollected();
	float distance(int x1, int y1, int x2, int y2);
	void server_send();
	void server_receive();
	void client_send();
	void client_receive(float* x,float* y,float* angle);
private:
	GameDataRef _data;
};
}

#endif