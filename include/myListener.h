#include "Box2D/Box2D.h"
#include <queue>

class myListener : public b2ContactListener
{
    public :
   		queue< pair<int,int> > Queue;
    	void BeginContact(b2Contact* contact);
};