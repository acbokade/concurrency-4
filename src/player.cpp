#include "player.h"
#include "SFML/Graphics.hpp"
#include "Box2D/Box2D.h"
#define DEGTORAD 0.0174532925199432957f

const float SCALE = 30.f;

Player::Player()
{

}

Player::~Player()
{

}

b2Body* Player:: createbody(b2World* world, b2Vec2 position, bool isStatic, float length, float width, float restitution, float density)
{
	b2BodyDef bodyDef;
    bodyDef.position = position;
    bodyDef.type = (isStatic)?b2_staticBody:b2_dynamicBody;
    b2Body* body = world->CreateBody(&bodyDef);
    b2FixtureDef FixtureDef;
    FixtureDef.restitution = restitution;
    FixtureDef.density = density;
    b2PolygonShape shape1;	
    shape1.SetAsBox((length/2)/SCALE, (width/2)/SCALE);
    FixtureDef.shape = &shape1;
    body->CreateFixture(&FixtureDef);
    return body;
}

b2Body* Player::createhead(b2World* world, b2Vec2 position, bool isStatic, float radius, float restitution, float density)
{
	b2BodyDef bodyDef;
    bodyDef.position = position;
    bodyDef.type = (isStatic)?b2_staticBody:b2_dynamicBody;
    b2Body* body = world->CreateBody(&bodyDef);
    b2FixtureDef FixtureDef;
    FixtureDef.restitution = restitution;
    FixtureDef.density = density;
    b2CircleShape shape1;	
    shape1.m_radius = radius/SCALE;
    FixtureDef.shape = &shape1;
    body->CreateFixture(&FixtureDef);
    return body;
}

b2RevoluteJoint* Player::createRevoluteJoint(b2World *world, b2Body* body1, b2Body* body2, b2Vec2 anchorPoint1, b2Vec2 anchorPoint2, float lowerLimit, float upperLimit)
{
    b2RevoluteJointDef jointDef;
    jointDef.bodyA= body1;
    jointDef.bodyB= body2;
    jointDef.collideConnected = false;
    jointDef.localAnchorA.Set(anchorPoint1.x,anchorPoint1.y);
    jointDef.localAnchorB.Set(anchorPoint2.x,anchorPoint2.y);
    jointDef.enableLimit = true;
    jointDef.referenceAngle = 0 * DEGTORAD;  
    jointDef.lowerAngle = lowerLimit * DEGTORAD;
    jointDef.upperAngle = upperLimit * DEGTORAD;
    b2RevoluteJoint* joint = (b2RevoluteJoint*)world->CreateJoint(&jointDef);
    return joint;
}

void Player::setHealth(int health)
{
	this->health = health;
}

int Player::getHealth()
{
	return this->health;
}

void Player::setName(std::string name)
{
    this->name = name;
}

std::string Player::getName()
{
    return this->name;
}

void Player::init(bool firstPlayer)
{
	(firstPlayer)?this->headTexture.loadFromFile("res/head1.png"):this->headTexture.loadFromFile("res/head2.png");
    (firstPlayer)?this->bodyTexture.loadFromFile("res/body1.png"):this->bodyTexture.loadFromFile("res/body2.png");
    (firstPlayer)?this->handTexture.loadFromFile("res/hand3.png"):this->handTexture.loadFromFile("res/hand4.png");
    (firstPlayer)?this->legTexture.loadFromFile("res/leg1.png"):this->legTexture.loadFromFile("res/leg2.png");
    this->headSprite.setTexture(headTexture);
    this->headSprite.setOrigin((sf::Vector2f)(headTexture.getSize())/2.f);
    this->bodySprite.setTexture(bodyTexture);
    this->bodySprite.setOrigin((sf::Vector2f)(bodyTexture.getSize())/2.f);
    this->left_handSprite.setTexture(handTexture);
    this->left_handSprite.setOrigin((sf::Vector2f)(handTexture.getSize())/2.f);
    this->right_handSprite.setTexture(handTexture);
    this->right_handSprite.setOrigin((sf::Vector2f)(handTexture.getSize())/2.f);
    this->left_legSprite.setTexture(legTexture);
    this->left_legSprite.setOrigin((sf::Vector2f)(legTexture.getSize())/2.f);
    this->right_legSprite.setTexture(legTexture);
    this->right_legSprite.setOrigin((sf::Vector2f)(legTexture.getSize())/2.f);
}
