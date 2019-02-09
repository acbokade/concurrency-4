#ifndef MYLISTENER_H
#define MYLISTENER_H
#include "mylistener.h"
#include "Box2D/Box2D.h"

myListener::BeginContact(b2Contact* contact);
{
	int a = *(int *)contact->GetFixtureA()->GetBody()->GetUserData();
	int b = *(int *)contact->GetFixtureB()->GetBody()->GetUserData();
    if(contact->IsTouching() == true && a!=-1 && b!=-1)
    {    
        this->Queue.push({*(int *)a->GetUserData(),*(int *)b->GetUserData()});
    }
}

#endif MYLISTENER_H