#include "myListener.h"
#include "Box2D/Box2D.h"

myListener::myListener()
{
}

myListener::~myListener()
{
}

void myListener::BeginContact(b2Contact* contact)
{
	int a = *(int *)contact->GetFixtureA()->GetBody()->GetUserData();
	int b = *(int *)contact->GetFixtureB()->GetBody()->GetUserData();
    if(contact->IsTouching() == true && a!=-1 && b!=-1)
    {    
        this->Queue.push(std::make_pair(a,b));
    }
}
