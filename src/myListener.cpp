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
    if(contact->IsTouching() == true && ( (a>=1 && a<=4 && b>=5 && b<=8) || ( a>=5 && a<=8 && b>=1 && b<=4 ) ) )
    {    
        this->Queue.push(std::make_pair(a,b));
        b2WorldManifold worldManifold;
        contact->GetWorldManifold(&worldManifold);
        b2Body* bodya = contact->GetFixtureA()->GetBody();
        b2Body* bodyb = contact->GetFixtureB()->GetBody();
        b2Vec2 impulse = (10*worldManifold.normal.x,10*worldManifold.normal);
        b2Vec2 impulse2 = (-10*worldManifold.normal.x,-10*worldManifold.normal);
        bodya->ApplyLinearImpulse(impulse,bodya->GetWorldCenter(),true);
        bodyb->ApplyLinearImpulse(impulse2,bodyb->GetWorldCenter(),true);
    }
}
