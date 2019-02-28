#ifndef LISTENER_H
#define LISTENER_H
#include "Box2D/Box2D.h"
#include <queue>
#include <utility>
#include <iostream>
namespace stickman{
	/**@class myListener
	 * @brief Listens to collision between any two objects in Box2D world.
 	*
 	*	   Subclass of b2ContactListener which implements the virtual method BeginContact 	
 	*
 	*      Contains the queue in which id of body part is stored which is further processed to decrease health point
 	*      
	*/
	class myListener : public b2ContactListener
	{

	    public :
		    /**
	     	* @brief Constructor for listener.
	    	*/
	    	myListener();
	    	/**
	     	* @brief Destructor for listener.
	    	*/
	    	~myListener();
	    	/**
	     	* @brief Stores the id of two body parts which collided.
	    	*/
	   		std::queue< std::pair<int,int> > Queue;
	   		/**
	     	* @brief Called when an object starts collision with other object.
	     	* @param contact Stores the contact information of two objects in Box2D world.
	    	*/
	    	void BeginContact(b2Contact* contact);
	};
}

#endif