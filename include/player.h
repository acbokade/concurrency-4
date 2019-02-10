#ifndef PLAYER_H
#define PLAYER_H
#include "SFML/Graphics.hpp"
#include "Box2D/Box2D.h"

class Player 
{
public:
	//health
	int health;
	//head
	b2Body* head;
	sf::Texture headTexture;
	sf::Sprite headSprite;
	//body
	b2Body* body;
	sf::Texture bodyTexture;
	sf::Sprite bodySprite;
	//hands
	b2Body* left_hand;
	sf::Texture handTexture;
	sf::Sprite left_handSprite;
	b2Body* right_hand;
	sf::Sprite right_handSprite;
	//legs
	b2Body* left_leg;
	sf::Texture legTexture;
	sf::Sprite left_legSprite;
	b2Body* right_leg;
	sf::Sprite right_legSprite;
	//head joint
	b2RevoluteJoint* headJoint;
	//hand joints
	b2RevoluteJoint* right_handJoint;
	b2RevoluteJoint* left_handJoint;
	//leg joints
	b2RevoluteJoint* right_legJoint;
	b2RevoluteJoint* left_legJoint;

	Player();
	~Player();
	b2Body* createhead(b2World* world, b2Vec2 position, bool isStatic, float radius, float restitution, float density, int data);
	b2Body* createbody(b2World* world, b2Vec2 position, bool isStatic, float length, float width, float restitution, float density, int data);
	b2RevoluteJoint* createRevoluteJoint(b2World *world, b2Body* body1, b2Body* body2, b2Vec2 anchorPoint1, b2Vec2 anchorPoint2, float lowerLimit, float upperLimit);
	void setHealth(int health);
	int getHealth();

	void setPosition(b2Vec2 position);
	b2Vec2 getPosition();

	void setAngle(float angle);
	float getAngle();

	void updatePosition(b2Vec2 position);
	void init();
};

#endif