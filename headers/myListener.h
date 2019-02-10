#ifndef LISTENER_H
#define LISTENER_H
#include "Box2D/Box2D.h"
#include <queue>
#include <utility>

class myListener : public b2ContactListener
{
    public :
   		std::queue< std::pair<int,int> > Queue;
    	void BeginContact(b2Contact* contact);
};

#endif