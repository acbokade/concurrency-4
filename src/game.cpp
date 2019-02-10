#include "player.h"
#include "SFML/Graphics.hpp"
#include "game.h"
#include "Box2D/Box2D.h"
#include "myListener.h"
#define DEGTORAD 0.0174532925199432957f

const float SCALE = 30.f;
float temp1 = (75/2)/sqrt(2);
float temp2 = (60/2);

Game::Game()
{
	this->window = new sf::RenderWindow(sf::VideoMode(1920, 1080, 32), "StickMan Fighter");
	this->window->setFramerateLimit(240);
	b2Vec2 gravity(0.0f, 0.0f);
	//this->listener = new myListener();
	this->world = new b2World(gravity);
	//this->world->SetContactListener(&listener);
	this->player1 = new Player();
	this->player2 = new Player();
    this->groundTexture.loadFromFile("res/ground.png");
    this->groundSprite.setTexture(groundTexture);
    this->groundSprite.setOrigin(400.f, 8.f);
};

void Game::gameLoop()
{
	initPlayer(player1, 200.f);
	initPlayer(player2, 1400.f);
    //gettimeofday(&prev_time,NULL);
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

        /*if(time_difference > 100)
        {
            checkcollision();
            gettimeofday(&current_time,NULL);
        }*/
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) )
        {
            player1->body->SetAngularVelocity(60*DEGTORAD);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) )
        {
            player1->body->SetAngularVelocity(-60*DEGTORAD);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            player1->body->SetLinearVelocity(b2Vec2(-4,0));
            player1->body->SetLinearVelocity(b2Vec2(-4,0));
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            player1->body->SetLinearVelocity(b2Vec2(4,0));
            player1->body->SetLinearVelocity(b2Vec2(4,0));
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            player1->body->SetLinearVelocity(b2Vec2(0,-4));
            player1->body->SetLinearVelocity(b2Vec2(0,-4));
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            player1->head->SetLinearVelocity(b2Vec2(0,4));
            player1->body->SetLinearVelocity(b2Vec2(0,4));
        }
        updatePlayer(player1);
        updatePlayer(player2);
      	groundSprite.setPosition(this->ground->GetPosition().x * SCALE, this->ground->GetPosition().y * SCALE);
    	groundSprite.setRotation((180/b2_pi) * this->ground->GetAngle());
		window->clear(sf::Color::White);
		draw(player1);
		draw(player2);
        window->draw(this->groundSprite);
        window->display();
	}
}

b2Body* Game::createGround(b2Vec2 position, int data)
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
   	return Body;
}

void Game::initPlayer(Player *player, float X)
{
	player->head = player->createhead(world, b2Vec2(X/SCALE,200.f/SCALE), 0, 25.f, 1.f, 1.f, 1);
    player->body = player->createbody(world, b2Vec2(X/SCALE,270.f/SCALE), 0, 20.f, 90.f, 1.f, 1.f, 2);
    player->left_hand = player->createbody(world, b2Vec2((X-40.f)/SCALE,(230.f)/SCALE), 0, 60.f, 10.f, 1.f, 1.f, 3);
    player->right_hand = player->createbody(world, b2Vec2((X+40.f)/SCALE,(230.f)/SCALE), 0, 60.f, 10.f, 1.f, 1.f, 3);
    player->left_leg = player->createbody(world, b2Vec2((X-temp1)/SCALE,(315.f+temp1)/SCALE), 0, 10.f, 75.f, 1.f, 1.f, 4);
    player->right_leg = player->createbody(world, b2Vec2((X+temp1)/SCALE,(315.f+temp1)/SCALE), 0, 10.f, 75.f, 1.f, 1.f, 4);
    player->headJoint = player->createRevoluteJoint(world, player->head, player->body, b2Vec2(0.f,25.0f/SCALE), b2Vec2(0.f,-45.0f/SCALE), 0, 0);
    player->left_legJoint = player->createRevoluteJoint(world, player->body, player->left_leg, b2Vec2(0.f/SCALE,45.0f/SCALE), b2Vec2((temp1-12)/SCALE,-temp1/SCALE), 30, 60);
    player->right_legJoint = player->createRevoluteJoint(world, player->body, player->right_leg, b2Vec2(0.f/SCALE,45.0f/SCALE), b2Vec2(-(temp1-12)/SCALE,-temp1/SCALE), -60, -30);
    player->left_handJoint = player->createRevoluteJoint(world, player->body, player->left_hand, b2Vec2(-10.f/SCALE,-40.0f/SCALE), b2Vec2(25.f/SCALE,0.f/SCALE), -10, 10);
    player->right_handJoint = player->createRevoluteJoint(world, player->body, player->right_hand, b2Vec2(10.f/SCALE,-40.0f/SCALE), b2Vec2(-25.f/SCALE,0.f/SCALE), -10, 10);
    player->init();
}

void Game::updatePlayer(Player *player)
{
	player->headSprite.setPosition(player->head->GetPosition().x*SCALE,player->head->GetPosition().y*SCALE);
    player->headSprite.setRotation(player->head->GetAngle() * (180/b2_pi));

    player->bodySprite.setPosition(player->body->GetPosition().x*SCALE,player->body->GetPosition().y*SCALE);
    player->bodySprite.setRotation(player->body->GetAngle() * (180/b2_pi));

    player->left_legSprite.setPosition(player->left_leg->GetPosition().x*SCALE,player->left_leg->GetPosition().y*SCALE);
    player->left_legSprite.setRotation(player->left_leg->GetAngle() * (180/b2_pi));

    player->right_legSprite.setPosition(player->right_leg->GetPosition().x*SCALE,player->right_leg->GetPosition().y*SCALE);
    player->right_legSprite.setRotation(player->right_leg->GetAngle() * (180/b2_pi));

    player->left_handSprite.setPosition(player->left_hand->GetPosition().x*SCALE,player->left_hand->GetPosition().y*SCALE);
    player->left_handSprite.setRotation(player->left_hand->GetAngle() * (180/b2_pi));

    player->right_handSprite.setPosition(player->right_hand->GetPosition().x*SCALE,player->right_hand->GetPosition().y*SCALE);
    player->right_handSprite.setRotation(player->right_hand->GetAngle() * (180/b2_pi));
}

void Game::draw(Player* player)
{
	window->draw(player->left_legSprite);
    window->draw(player->right_legSprite);
    window->draw(player->left_handSprite);
    window->draw(player->right_handSprite);
    window->draw(player->headSprite);
    window->draw(player->bodySprite);
}

/*void Game::checkcollision()
{
	int r1=listener->Queue.size();
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
}*/

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
