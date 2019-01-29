#include "SFML/Graphics.hpp"
#include "Box2D/Box2D.h"
#include <iostream>
#include <thread>
#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f
using namespace std;

const float SCALE = 30.f;

b2Vec2 Gravity(0.f, 0.f);
b2World world(Gravity);
b2Body *body1,*body2,*body3,*body4,*body5,*body6,*Body,*Body1;

void CreateGround(b2World& World,float X, float Y)
{
    b2BodyDef BodyDef;
    BodyDef.position = b2Vec2(X/30.f, Y/30.f);
    BodyDef.type = b2_staticBody;
    Body = World.CreateBody(&BodyDef);
    b2PolygonShape Shape;
    Shape.SetAsBox((800.f/2)/SCALE, (16.f/2)/SCALE);
    b2FixtureDef FixtureDef;
    FixtureDef.restitution=1;
    FixtureDef.density = 0.f;
    FixtureDef.shape = &Shape;
    Body->CreateFixture(&FixtureDef);
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600, 32), "SFML works!");
    window.setFramerateLimit(120);
    float timeStep = 1.0f / 120.0f;
    int velocityIterations = 10;
    int positionIterations = 10;

    sf::Texture texture;
    texture.loadFromFile("face.png");

    //setting lower wall
    CreateGround(world,400.f, 550.f);
    sf::Texture GroundTexture;
    GroundTexture.loadFromFile("ground.png");
    sf::Sprite GroundSprite;
    GroundSprite.setTexture(GroundTexture);
    GroundSprite.setOrigin(400.f, 8.f);
    GroundSprite.setPosition(Body->GetPosition().x * SCALE, Body->GetPosition().y * SCALE);
    GroundSprite.setRotation(180/b2_pi * Body->GetAngle());

    //creating upper wall
    b2BodyDef BodyDef1;
    BodyDef1.position = b2Vec2(400.f/30.f, 0.f/30.f);
    BodyDef1.type = b2_staticBody;
    Body1 = world.CreateBody(&BodyDef1);
    b2PolygonShape Shape1;
    Shape1.SetAsBox((800.f/2)/SCALE, (16.f/2)/SCALE);
    b2FixtureDef FixtureDef;
    FixtureDef.restitution=1;
    FixtureDef.density = 0.f;
    FixtureDef.shape = &Shape1;
    Body1->CreateFixture(&FixtureDef);

    //setting upper wall
    sf::Texture GroundTexture1;
    GroundTexture1.loadFromFile("ground.png");
    sf::Sprite GroundSprite1;
    GroundSprite1.setTexture(GroundTexture1);
    GroundSprite1.setOrigin(400.f, 8.f);
    GroundSprite1.setPosition(Body1->GetPosition().x * SCALE, Body1->GetPosition().y * SCALE);
    GroundSprite1.setRotation(180/b2_pi * Body1->GetAngle());


    //creating circle
    b2BodyDef bodydef1;
    bodydef1.position=b2Vec2(200.f/SCALE,220.f/SCALE);
    bodydef1.type = b2_dynamicBody;
    body1 = world.CreateBody(&bodydef1);
    b2CircleShape circle;
    //circle.m_p.Set(200.f/SCALE,260.f/SCALE);
    circle.m_radius = 40.f/SCALE;
    b2FixtureDef FixtureDef1;
    FixtureDef1.restitution=1;
    FixtureDef1.density = 1.f;
    FixtureDef1.friction = 0.7f;
    FixtureDef1.shape = &circle;
    body1->CreateFixture(&FixtureDef1);
    //body1->SetLinearVelocity( b2Vec2( 5, 0 ) ); //moving up and left 5 units per second
    //body1->SetAngularVelocity( -90 * DEGTORAD ); //90 degrees per second clockwise
    //body1->ApplyForce( b2Vec2(0,50), body1->GetWorldCenter(),true);

    //creating body
    b2BodyDef bodydef2;
    bodydef2.position=b2Vec2(200.f/SCALE,350.f/SCALE);
    bodydef2.type = b2_dynamicBody;
    body2 = world.CreateBody(&bodydef2);
    b2PolygonShape rect;
    rect.SetAsBox((20.f/2)/SCALE, (180.f/2)/SCALE);
    b2FixtureDef FixtureDef2;
    FixtureDef2.restitution=1;
    FixtureDef2.density = 1.f;
    FixtureDef2.friction = 0.7f;
    FixtureDef2.shape = &rect;
    body2->CreateFixture(&FixtureDef2);
    //body2->SetLinearVelocity( b2Vec2( 5, 0) ); //moving up and left 5 units per second
    //body2->SetAngularVelocity( -90 * DEGTORAD ); //90 degrees per second clockwise

    float temp = 40/sqrt(2);
    //creating joint betweem head and body
    b2RevoluteJointDef jointDef;
    jointDef.bodyA= body1;
    jointDef.bodyB= body2;
    jointDef.collideConnected = true;
    jointDef.localAnchorA.Set(0.f,40.0f/SCALE);//the top right corner of the box
    jointDef.localAnchorB.Set(0.f,-80.0f/SCALE);//center of the circle*/
    jointDef.enableLimit = true;
    jointDef.lowerAngle = 0 * DEGTORAD;
    jointDef.upperAngle = 0 * DEGTORAD;
    b2RevoluteJoint* joint = (b2RevoluteJoint*)world.CreateJoint(&jointDef);

    //creating legs
    b2BodyDef bodydef3;
    bodydef3.position=b2Vec2((200.f-temp)/SCALE,(440.f+temp)/SCALE);
    bodydef3.type = b2_dynamicBody;
    body3 = world.CreateBody(&bodydef3);
    b2PolygonShape rect1;
    rect1.SetAsBox((15.f/2)/SCALE, (80.f/2)/SCALE);
    b2FixtureDef FixtureDef3;
    FixtureDef3.restitution=1;
    FixtureDef3.density = 1.f;
    FixtureDef3.friction = 0.7f;
    FixtureDef3.shape = &rect1;
    body3->CreateFixture(&FixtureDef3);
    float angle1 = 45 * DEGTORAD;
    body3->SetTransform(b2Vec2(((body3->GetPosition().x)),(body3->GetPosition().y)),angle1);

    //creating legs
    b2BodyDef bodydef4;
    bodydef4.position=b2Vec2((200.f+temp)/SCALE,(440.f+temp)/SCALE);
    bodydef4.type = b2_dynamicBody;
    body4 = world.CreateBody(&bodydef4);
    b2PolygonShape rect2;
    rect2.SetAsBox((15.f/2)/SCALE, (80.f/2)/SCALE);
    b2FixtureDef FixtureDef4;
    FixtureDef4.restitution=1;
    FixtureDef4.density = 1.f;
    FixtureDef4.friction = 0.7f;
    FixtureDef4.shape = &rect2;
    body4->CreateFixture(&FixtureDef4);
    float angle2 = -45 * DEGTORAD;
    body4->SetTransform(b2Vec2(((body4->GetPosition().x)),(body4->GetPosition().y)),angle2);

    //creating hands
    b2BodyDef bodydef5;
    bodydef5.position=b2Vec2((200.f-temp)/SCALE,(260.f+temp)/SCALE);
    bodydef5.type = b2_dynamicBody;
    body5 = world.CreateBody(&bodydef5);
    b2PolygonShape rect3;
    rect3.SetAsBox((5.f/2)/SCALE, (80.f/2)/SCALE);
    b2FixtureDef FixtureDef5;
    FixtureDef5.restitution=1;
    FixtureDef5.density = 1.f;
    FixtureDef5.friction = 0.7f;
    FixtureDef5.shape = &rect1;
    body5->CreateFixture(&FixtureDef5);
    float angle3 = 45 * DEGTORAD;
    body5->SetTransform(b2Vec2(((body5->GetPosition().x)),(body5->GetPosition().y)),angle3);

    //creating hands
    b2BodyDef bodydef6;
    bodydef6.position=b2Vec2((200.f+temp)/SCALE,(260.f+temp)/SCALE);
    bodydef6.type = b2_dynamicBody;
    body6 = world.CreateBody(&bodydef6);
    b2PolygonShape rect4;
    rect4.SetAsBox((5.f/2)/SCALE, (80.f/2)/SCALE);
    b2FixtureDef FixtureDef6;
    FixtureDef6.restitution=1;
    FixtureDef6.density = 1.f;
    FixtureDef6.friction = 0.7f;
    FixtureDef6.shape = &rect4;
    body6->CreateFixture(&FixtureDef6);
    float angle4 = -45 * DEGTORAD;
    body6->SetTransform(b2Vec2(((body6->GetPosition().x)),(body6->GetPosition().y)),angle4);

    //creating joint between bodya and legs
    b2RevoluteJointDef jointDef1;
    jointDef1.bodyA= body2;
    jointDef1.bodyB= body3;
    //jointDef1.collideConnected = false;
    jointDef1.localAnchorA.Set(0.f/SCALE,105.0f/SCALE);//the top right corner of the box
    jointDef1.localAnchorB.Set((temp-7.f)/SCALE,-temp/SCALE);//center of the circle
    jointDef1.referenceAngle=0.0;
    jointDef1.enableLimit = true;
    jointDef1.enableMotor=true;
    jointDef1.collideConnected = false;
    jointDef1.lowerAngle = 30 * DEGTORAD;
    jointDef1.upperAngle = 60 * DEGTORAD;
    b2RevoluteJoint* joint1 = (b2RevoluteJoint*)world.CreateJoint(&jointDef1);

    b2RevoluteJointDef jointDef2;
    jointDef2.bodyA= body2;
    jointDef2.bodyB= body4;
    //jointDef2.collideConnected = false;
    jointDef.enableMotor=true;
    jointDef2.localAnchorA.Set(0.f/SCALE,105.0f/SCALE);//the top right corner of the box
    jointDef2.localAnchorB.Set(-(temp-7.f)/SCALE,-temp/SCALE);//center of the circle
    jointDef2.enableLimit = true;
    jointDef2.referenceAngle=0.0;
    jointDef2.enableMotor=true;
    jointDef2.collideConnected = false;
    jointDef2.lowerAngle = -30 * DEGTORAD;
    jointDef2.upperAngle = -60 * DEGTORAD;
    b2RevoluteJoint* joint2 = (b2RevoluteJoint*)world.CreateJoint(&jointDef2);

     //creating joint between body and hands
    b2RevoluteJointDef jointDef3;
    jointDef3.bodyA= body2;
    jointDef3.bodyB= body5;
    jointDef3.collideConnected = false;
    jointDef3.localAnchorA.Set(0.f/SCALE,-60.0f/SCALE);//the top right corner of the box
    jointDef3.localAnchorB.Set((temp-2.f)/SCALE,-temp/SCALE);//center of the circle
    jointDef3.referenceAngle=0.0;
    jointDef3.enableLimit = true;
    jointDef3.enableMotor=true;
    jointDef3.collideConnected = false;
    jointDef3.lowerAngle = 30 * DEGTORAD;
    jointDef3.upperAngle = 60 * DEGTORAD;
    b2RevoluteJoint* joint3 = (b2RevoluteJoint*)world.CreateJoint(&jointDef3);

    b2RevoluteJointDef jointDef4;
    jointDef4.bodyA= body2;
    jointDef4.bodyB= body6;
    jointDef4.collideConnected = false;
    jointDef4.localAnchorA.Set(0.f/SCALE,-60.0f/SCALE);//the top right corner of the box
    jointDef4.localAnchorB.Set(-(temp-2.f)/SCALE,-temp/SCALE);//center of the circle
    jointDef4.referenceAngle=0.0;
    jointDef4.enableMotor=true;
    jointDef4.enableLimit = true;
    jointDef4.collideConnected = false;
    jointDef4.lowerAngle = -30 * DEGTORAD;
    jointDef4.upperAngle = -60 * DEGTORAD;
    b2RevoluteJoint* joint4 = (b2RevoluteJoint*)world.CreateJoint(&jointDef4);

    sf::CircleShape shape(40.f);
    shape.setFillColor(sf::Color(0, 250, 0));

    sf::RectangleShape recta(sf::Vector2f(20, 180));
    recta.setFillColor(sf::Color(150, 0, 0));

    sf::RectangleShape recta1(sf::Vector2f(15, 80));
    recta1.setFillColor(sf::Color(0, 0, 150));

    sf::RectangleShape recta2(sf::Vector2f(15, 80));
    recta2.setFillColor(sf::Color(0, 0, 150));

    sf::RectangleShape recta3(sf::Vector2f(5, 80));
    recta3.setFillColor(sf::Color(0, 0, 150));

    sf::RectangleShape recta4(sf::Vector2f(5, 80));
    recta4.setFillColor(sf::Color(0, 0, 150));


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            // left key is pressed: move our character
            body2->SetAngularVelocity(30*DEGTORAD);
            //body2->SetTransform(b2Vec2(((body2->GetPosition().x-0.1)),(body2->GetPosition().y)),angle);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            // left key is pressed: move our character
            body2->SetAngularVelocity(-30*DEGTORAD);
            //body2->SetTransform(b2Vec2(((body2->GetPosition().x-0.1)),(body2->GetPosition().y)),angle);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            // left key is pressed: move our character
            float angle = body2->GetAngle();
            //body1->SetLinearVelocity(b2Vec2(-1,0));
            body1->SetLinearVelocity(b2Vec2(-4,0));
            //body2->SetTransform(b2Vec2(((body2->GetPosition().x-0.1)),(body2->GetPosition().y)),angle);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            // left key is pressed: move our character
            float angle = body2->GetAngle();
            //body1->SetLinearVelocity(b2Vec2(1,0));
            body1->SetLinearVelocity(b2Vec2(4,0));
            //body2->SetTransform(b2Vec2(((body2->GetPosition().x+0.1)),(body2->GetPosition().y)),angle);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            // left key is pressed: move our character
            float angle = body2->GetAngle();
            //body1->SetLinearVelocity(b2Vec2(0,-1));
            body1->SetLinearVelocity(b2Vec2(0,-4));
            //body2->SetTransform(b2Vec2(((body2->GetPosition().x)),(body2->GetPosition().y)-0.1),angle);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            // left key is pressed: move our character
            float angle = body2->GetAngle();
            //body1->SetLinearVelocity(b2Vec2(0,1));
            body1->SetLinearVelocity(b2Vec2(0,4));
            //body2->SetTransform(b2Vec2(((body2->GetPosition().x)),(body2->GetPosition().y)+0.1),angle);
        }

        world.Step(timeStep, velocityIterations, positionIterations);

        shape.setOrigin(shape.getRadius(),shape.getRadius());
        shape.setPosition(body1->GetPosition().x*SCALE,body1->GetPosition().y*SCALE);
        shape.setRotation(body1->GetAngle() * (180/b2_pi));

        recta.setOrigin(recta.getSize()/2.f);
        recta.setPosition(body2->GetPosition().x*SCALE,body2->GetPosition().y*SCALE);
        recta.setRotation(body2->GetAngle() * (180/b2_pi));

        recta1.setOrigin(recta1.getSize()/2.f);
        recta1.setPosition(body3->GetPosition().x*SCALE,body3->GetPosition().y*SCALE);
        recta1.setRotation(body3->GetAngle() * (180/b2_pi));

        recta2.setOrigin(recta2.getSize()/2.f);
        recta2.setPosition(body4->GetPosition().x*SCALE,body4->GetPosition().y*SCALE);
        recta2.setRotation(body4->GetAngle() * (180/b2_pi));

        recta3.setOrigin(recta3.getSize()/2.f);
        recta3.setPosition(body5->GetPosition().x*SCALE,body5->GetPosition().y*SCALE);
        recta3.setRotation(body5->GetAngle() * (180/b2_pi));

        recta4.setOrigin(recta4.getSize()/2.f);
        recta4.setPosition(body6->GetPosition().x*SCALE,body6->GetPosition().y*SCALE);
        recta4.setRotation(body6->GetAngle() * (180/b2_pi));

        GroundSprite.setPosition(Body->GetPosition().x * SCALE, Body->GetPosition().y * SCALE);
        GroundSprite.setRotation((180/b2_pi) * Body->GetAngle());

        GroundSprite1.setPosition(Body1->GetPosition().x * SCALE, Body1->GetPosition().y * SCALE);
        GroundSprite1.setRotation((180/b2_pi) * Body1->GetAngle());

        window.clear(sf::Color::White);
        window.draw(recta);
        window.draw(recta1);
        window.draw(recta2);
        window.draw(recta3);
        window.draw(recta4);
        window.draw(shape);
        window.draw(GroundSprite);
        window.draw(GroundSprite1);
        window.display();

    }

    return 0;
}
