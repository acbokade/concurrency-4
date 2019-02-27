#ifndef PLAYER_H
#define PLAYER_H
#include "SFML/Graphics.hpp"
#include "Box2D/Box2D.h"
#include "string"
#include <iostream>
/**@class Player
 * @brief Contains all the information about the player.
 *
 *      Contains information about the player including its name, health point, textures, sprites and Box2D body
 *      pointers along with some joints.
 *      
*/
class Player 
{
public:
	/** @brief Health of player
    *	 	   	Contains the current health point of player. 
    */
	int health;

	/** @brief Head of player
    *	 		Contains the Box2D pointer of the object denoting player's head. 
     */
	b2Body* head;
	/** @brief 
    *	 	Contains the userData of head 
    *
    *		Used to detect head in collision of two body parts. 
     */
	int headUserData;
	/** 
    *	 @brief SFML Texture to be loaded for head of player.
     */
	sf::Texture headTexture;
	/** 
    *	 @brief SFML Sprite to be displayed for head of player.
     */
	sf::Sprite headSprite;
	/** @brief Body of player
    *	 		Contains the Box2D pointer of the object denoting player's body. 
     */
	b2Body* body;
	/** @brief 
    *	 	Contains the userData of body 
    *
    *		Used to detect body in collision. 
     */
	int bodyUserData;
	/** 
    *	 @brief SFML Texture to be loaded for body of player.
     */
	sf::Texture bodyTexture;
	/** 
    *	 @brief SFML Sprite to be displayed for body of player.
     */
	sf::Sprite bodySprite;
	/** @brief Left Hand of player
    *	 		Contains the Box2D pointer of the object denoting player's left hand. 
     */
	b2Body* left_hand;
	/** @brief 
    *	 	Contains the userData of player's left hand
    *
    *	    Used to detect left hand in collision
     */
	int left_handUserData;
	/** 
    *	 @brief SFML Texture to be loaded for both the hands of player.
     */
	sf::Texture handTexture;
	/** 
    *	 @brief SFML Sprite to be displayed for left hand of player.
     */
	sf::Sprite left_handSprite;
	/** @brief Right Hand of player
    *	 		Contains the Box2D pointer of the object denoting player's right hand. 
     */
	b2Body* right_hand;
	/** @brief 
    *	 	Contains the userData of player's right hand 
    *
  	*  		Used to detect right hand in collision of two body parts. 
     */
	int right_handUserData;
	/** 
    *	 @brief SFML Sprite to be displayed for right hand of player.
     */
	sf::Sprite right_handSprite;
	/** @brief Left Leg of player
    *	 		Contains the Box2D pointer of the object denoting player's left leg. 
     */
	b2Body* left_leg;
	/** @brief 
    *	 	Contains the userData of player's left leg
    *
   	* 		Used to detect left leg in collision of two body parts. 
     */
	int left_legUserData;
	/** 
    *	 @brief SFML Texture to be loaded for both the legs of player.
     */
	sf::Texture legTexture;
	/** 
    *	 @brief SFML Sprite to be displayed for left leg of player.
     */
	sf::Sprite left_legSprite;
	/** @brief Right Leg of player
    *	 		Contains the Box2D pointer of the object denoting player's right leg. 
     */
	b2Body* right_leg;
	/** @brief 
    *	 	Contains the userData of player's right leg
    *
   	* 		Used to detect right leg in collision of two body parts. 
     */
	int right_legUserData;
	/** 
    *	 @brief SFML Sprite to be displayed for right leg of player.
     */
	sf::Sprite right_legSprite;
	/** 
    *	 @brief Represents Revolute Joint between head and body of player.
     */
	b2RevoluteJoint* headJoint;
	/** 
    *	 @brief Represents Revolute Joint between right hand and body of player.
     */
	b2RevoluteJoint* right_handJoint;
	/** 
    *	 @brief Represents Revolute Joint between left hand and body of player.
     */
	b2RevoluteJoint* left_handJoint;
	/** 
    *	 @brief Represents Revolute Joint between right leg and body of player.
     */
	b2RevoluteJoint* right_legJoint;
	/** 
    *	 @brief Represents Revolute Joint between left leg and body of player.
     */
	b2RevoluteJoint* left_legJoint;
	/** @brief Name of player
    *	 	   	Stores the name of player. 
     */
	std::string name;
	/**
     * @brief Constructor for player.
    */
	Player();
	/**
     * @brief Destructor for player.
    */
	~Player();
	/**
     * @brief Creates a circular Box2D object for head of player.
     * @param world Box2D world in which player is initialised.
     * @param position Contains the position where head is to be created.
     * @param isStatic Denotes whether the object is static or dynamic.
     * @param radius Contains the radius of head of player.
     * @param restitution Contains the coefficient of restituion for head of player.
     * @param density Stores the density of head of player.
     * @return Box2D object pointer of head.
     */
	b2Body* createhead(b2World* world, b2Vec2 position, bool isStatic, float radius, float restitution, float density);
	/**
     * @brief Creates a rectangular Box2D object for each body part(body, hands, legs) of player.
     * @param world Box2D world in which player is initialised.
     * @param position Contains the position where body part is to be created.
     * @param isStatic Denotes whether the object is static or dynamic.
     * @param length Contains the length of body part of player.
     * @param length Contains the width of body part of player.
     * @param restitution Contains the coefficient of restituion of body part of player.
     * @param density Stores the density of body part of player.
     * @return Box2D object pointer of body part.
     */
	b2Body* createbody(b2World* world, b2Vec2 position, bool isStatic, float length, float width, float restitution, float density);
	/**
     * @brief Revolute joints can be think of as hinge which allows rotation of body parts.
     *         Creates a Revolute joint between two body parts.
     * @param world Box2D world in which player is initialised.
     * @param body1 Contains the Box2D object pointer denoting the first body part in joint.
     * @param body2 Contains the Box2D object pointer denoting the second body part in joint.
     * @param anchorPoint1 Contains the local position in first body where joint has to be initialised.
     * @param anchorPoint2 Contains the local position in second body where joint has to be initialised.
     * @param lowerLimit Stores the lower limit of angle of rotation for the Revolute joint.
     * @param upperLimit Stores the upper limit of angle of rotation for the Revolute joint.
     * @return Box2D Revolute joint pointer denoting the joint.
     */
	b2RevoluteJoint* createRevoluteJoint(b2World *world, b2Body* body1, b2Body* body2, b2Vec2 anchorPoint1, b2Vec2 anchorPoint2, float lowerLimit, float upperLimit);
	/**
	*	@brief Sets the health point of player.
	*	@param health Stores the health to be set.
	*/
	void setHealth(int health);
	/**
	*	@brief Sets the name of player.
	*	@param name Stores the name to be set.
	*/
	void setName(std::string name);
	/**
	*	@brief Returns the name of player.
	*	@return Name of player.
	*/
	std::string getName();
	/**
	*	@brief Returns the health of player.
	*	@return Health point of player.
	*/
	int getHealth();
	/**
	*	@brief Initialises the textures and sprites of a player.
	*	@param firstPlayer Stores the information whether the player is first player or second.
	*/
	void init(bool firstPlayer);
};

#endif