#include "player.h"
#include "SFML/Graphics.hpp"
#include "game.h"
#include "Box2D/Box2D.h"
#include "myListener.h"


const float SCALE = 30.f;
float temp1 = (75/2)/sqrt(2);
float temp2 = (60/2);

Game::Game()
{
	this->window = new sf::RenderWindow(sf::VideoMode(800, 600, 32), "StickMan Fighter");
	this->window->setFramerateLimit(240);
	b2Vec2 gravity(0.0f,0.0f);
	this->listener = new myListener();
	this->world = new b2World(gravity);
	this->world->SetContactListener(&listener);
	this->player1 = new player();
	this->player2 = new player();
    this->groundTexture.loadFromFile("res/ground.png");
    this->groundSprite.setTexture(groundTexture);
    this->groundSprite.setOrigin((sf::Vector2f)(groundTexture.getSize())/2.f);
};

void Game::gameLoop()
{
    //creating player 1
    player1.head = player1.createhead(world, b2Vec2(200.f/SCALE,200.f/SCALE), 0, 25.f, 1.f, 1.f, 1);
    player1.body = player1.createbody(world, b2Vec2(200.f/SCALE,270.f/SCALE), 0, 20.f, 90.f, 1.f, 1.f, 2);
    player1.left_hand = player1.createbody(world, b2Vec2((170.f)/SCALE,(225.f)/SCALE), 0, 10.f, 60.f, 1.f, 1.f, 3);
    player1.right_hand = player1.createbody(world, b2Vec2((230.f)/SCALE,(225.f)/SCALE), 0, 10.f, 60.f, 1.f, 1.f, 3);
    player1.left_leg = player1.createbody(world, b2Vec2((200.f-temp1)/SCALE,(315.f+temp1)/SCALE), 0, 10.f, 75.f, 1.f, 1.f, 4);
    player1.right_leg = player1.createbody(world, b2Vec2((200.f+temp1)/SCALE,(315.f+temp1)/SCALE), 0, 10.f, 75.f, 1.f, 1.f, 4);
    player1.init();

    gettimeofday(&prev_time,NULL);
	while(window->isOpen())
	{
		sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();
        }
		world->Step(timeStep, velocityIterations, positionIterations);

		gettimeofday(&current_time,NULL);
        time_difference = (double) ((current_time.tv_sec * 1000000 + current_time.tv_usec) - (prev_time.tv_sec * 1000000 + prev_time.tv_usec)) / 1000.0;

        if(time_difference > 100)
        {
            checkcollision();
            gettimeofday(&current_time,NULL);
        }
		
		player1.headSprite.setPosition(player1.head->GetPosition().x*SCALE,player1.head->GetPosition().y*SCALE);
        player1.headSprite.setRotation(player1.head->GetAngle() * (180/b2_pi));

        player1.bodySprite.setPosition(player1.body->GetPosition().x*SCALE,player1.body->GetPosition().y*SCALE);
        player1.bodySprite.setRotation(player1.body->GetAngle() * (180/b2_pi));

        player1.left_legSprite.setPosition(player1.left_leg->GetPosition().x*SCALE,player1.left_leg->GetPosition().y*SCALE);
        player1.left_legSprite.setRotation(player1.left_leg->GetAngle() * (180/b2_pi));
  
        player1.right_legSprite.setPosition(player1.right_leg->GetPosition().x*SCALE,player1.right_leg->GetPosition().y*SCALE);
        player1.right_legSprite.setRotation(player1.right_leg->GetAngle() * (180/b2_pi));

        player1.left_handSprite.setPosition(player1.left_hand->GetPosition().x*SCALE,player1.left_hand->GetPosition().y*SCALE);
        player1.left_handSprite.setRotation(player1.left_hand->GetAngle() * (180/b2_pi));
   
        player1.right_handSprite.setPosition(player1.right_hand->GetPosition().x*SCALE,player1.right_hand->GetPosition().y*SCALE);
        player1.right_handSprite.setRotation(player1.right_hand->GetAngle() * (180/b2_pi));

		window->clear(sf::Color::White);
        window->draw(player1.headSprite);
        window->draw(player1.bodySprite);
        window->draw(player1.left_legSprite);
        window->draw(player1.right_legSprite);
        window->draw(player1.left_handSprite);
        window->draw(player1.right_handSprite);
        window->display();
	}
}

void Game::createGround(b2Vec2 position,int data)
{

	b2BodyDef BodyDef;
    BodyDef.position = position;
    BodyDef.type = b2_staticBody;
    b2Body* Body = world->CreateBody(&BodyDef);
    b2PolygonShape Shape;
    Shape.SetAsBox((800.f/2)/SCALE, (16.f/2)/SCALE);
    b2FixtureDef FixtureDef;
    FixtureDef.restitution=1;
    FixtureDef.density = 0.f;
    FixtureDef.shape = &Shape;
    Body->CreateFixture(&FixtureDef);
    Body->SetUserData(&data);
}

void Game::checkcollision()
{
	int r1=listener.Queue.size();
    if(r1 > 30)
        r1=30;
    for(int i=0;i<r1;i++)
    {
        pair<int,int> p = listener.Q.front();
        listener.Q.pop();
        worker[i]=thread(decrease_hp,p.first,p.second);
    }
    for(int i=0;i<r1;i++)
        worker[i].join();
}

void Game::decrease_hp(int a,int b)
{
	if( (a==1 && b==5) || (a==5 && b==1) )
	{
		m.lock();
		int new_hp1 = player1->getHealth() - 10;
		int new_hp2 = player2->getHealth() - 10;
		player1->setHealth(new_hp1);
		player2->setHealth(new_hp2);
		m.unlock();
	}
	else if( (a==1 && b==7) || (a==7 && b==1) )
	{
		m.lock();
		int new_hp1 = player1->getHealth() - 10;
		player1->setHealth(new_hp1);
		m.unlock();
	}
	else if( (a==2 && b==8) || (a==8 && b==2) )
	{
		m.lock();
		int new_hp1 = player1->getHealth() - 10;
		player1->setHealth(new_hp1);
		m.unlock();
	}
	else if( (a==2 && b==7) || (a==7 && b==2) )
	{
		m.lock();
		int new_hp1 = player1->getHealth() - 5;
		player1->setHealth(new_hp1);
		m.unlock();
	}
	else if( (a==2 && b==8) || (a==8 && b==2) )
	{
		m.lock();
		int new_hp1 = player1->getHealth() - 5;
		player1->setHealth(new_hp1);
		m.unlock();
	}
	else if( (a==3 && b==5) || (a==5 && b==3) )
	{
		m.lock();
		int new_hp2 = player2->getHealth() - 10;
		player2->setHealth(new_hp2);
		m.unlock();
	}
	else if( (a==4 && b==5) || (a==5 && b==4) )
	{
		m.lock();
		int new_hp2 = player2->getHealth() - 10;
		player2->setHealth(new_hp2);
		m.unlock();
	}
	else if( (a==3 && b==6) || (a==6 && b==3) )
	{
		m.lock();
		int new_hp2 = player2->getHealth() - 5;
		player2->setHealth(new_hp2);
		m.unlock();
	}
	else if( (a==4 && b==6) || (a==6 && b==4) )
	{
		m.lock();
		int new_hp2 = player2->getHealth() - 10;
		player2->setHealth(new_hp2);
		m.unlock();
	}

}
