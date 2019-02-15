#include "player.h"
#include "SFML/Graphics.hpp"
#include "SFML/Network.hpp"
#include "game.h"
#include "Box2D/Box2D.h"
#include "myListener.h"
#include <iostream>
using namespace std;
#define DEGTORAD 0.0174532925199432957f

const float SCALE = 30.f;
float temp1 = ((75/2)/sqrt(2));
float temp2 = (60/2);

namespace stickman{
Game::Game(GameDataRef data): _data(data)
{
	this->window = &(_data->window);
	b2Vec2 gravity(0.0f, 0.0f);
	this->world = new b2World(gravity);
    this->listener = new myListener();
	this->world->SetContactListener(listener);
	this->player1 = new Player();
	this->player2 = new Player();
    this->groundTexture.loadFromFile("res/g1.png");
    this->groundSprite.setTexture(groundTexture);
    this->groundSprite.setOrigin(620.f, 8.f);
    this->wall1Texture.loadFromFile("res/g1.png");
    this->wall1Sprite.setTexture(wall1Texture);
    this->wall1Sprite.setOrigin(620.f, 8.f);
    this->wall2Texture.loadFromFile("res/g2.png");
    this->wall2Sprite.setTexture(wall2Texture);
    this->wall2Sprite.setOrigin(314.f, 8.f);
    this->wall3Texture.loadFromFile("res/g2.png");
    this->wall3Sprite.setTexture(wall3Texture);
    this->wall3Sprite.setOrigin(314.f, 8.f);
    this->gemTexture.loadFromFile("res/gem1.png");
    this->gemSprite.setTexture(gemTexture);
    this->gemSprite.setOrigin((sf::Vector2f)gemTexture.getSize()/2.f);
    this->player1->init(true);
	this->player2->init(false);
	this->gemExists = true;
};

void Game::gameLoop()
{
	srand(time(0));
	char con;
	cout<<"(s) for server (c) for client\n";
	this->ip=sf::IpAddress::getLocalAddress();
	cin>>con;
	//cout<<ip;
	if(!this->buffer.loadFromFile("res/punch.wav"))
        std::cout<<"error in loading sound"<<std::endl;
    this->sound.setBuffer(buffer);
	if(con=='s')
	{
		this->isClient=false;
		cout<<this->ip<<endl;
		sf::TcpListener tcplistener;
		tcplistener.listen(3002);
		tcplistener.accept(this->socket);
	}
	else
	{
		this->isClient=true;
		this->socket.connect(this->ip,3002);
	}

	this->socket.setBlocking(false);

	if(!isClient)
	{
		initPlayer(player1, 200.f,0);
		initPlayer(player2, 500.f,4);
	    player1->setHealth(100);
	    player2->setHealth(100);
	    gettimeofday(&prev_time,NULL);
	    gettimeofday(&prev_time1, NULL);
	    sf::Texture texture;
		texture.setRepeated(true);

		if (!texture.loadFromFile("res/texture.png"))
		{
			std::cout << "Error loading texture" << std::endl;
		}

		sf::Sprite sprite;
		sprite.setTexture(texture);
		sprite.setTextureRect(sf::IntRect(0, 0, 1366, 768));
		sprite.setColor(sf::Color(255,255,255,40));
		texture.setSmooth(true);
		while(window->isOpen())
		{
			sf::Event event;
	        while (window->pollEvent(event))
	        {
	            if (event.type == sf::Event::Closed)
	                window->close();
	        }
			this->world->Step(timeStep, velocityIterations, positionIterations);

			gettimeofday(&current_time,NULL);
			gettimeofday(&current_time1, NULL);
	        time_difference = (double) ((current_time.tv_sec * 1000000 + current_time.tv_usec) - (prev_time.tv_sec * 1000000 + prev_time.tv_usec)) / 1000.0;

	        if(time_difference > 100)
	        {
	            checkcollision();
	            gettimeofday(&prev_time,NULL);
	        }

	        time_difference1 = (double) ((current_time1.tv_sec * 1000000 + current_time1.tv_usec) - (prev_time1.tv_sec * 1000000 + prev_time1.tv_usec)) / 1000.0;
	        
	        if(time_difference1 > 5000)
	        {
	        	this->Thread = std::thread(&Game::generateGem, this);
	        	this->Thread.join();
	        	gettimeofday(&prev_time1, NULL);
	        }

	        if(gemExists)
	        {
	        	this->Thread1 = std::thread(&Game::isGemCollected, this);
	        	this->Thread1.join();
	        	if(!gemExists)
	        		gettimeofday(&prev_time1, NULL);
	        }
			
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

	        std::thread thr1,thr2;
	        thr1=std::thread(&Game::server_send,this);
	        thr2=std::thread(&Game::server_receive,this);
	        thr1.join();
	        thr2.join();

	        updatePlayer(player1);
	        updatePlayer(player2);
	      	groundSprite.setPosition(this->ground->GetPosition().x * SCALE, this->ground->GetPosition().y * SCALE);
	    	groundSprite.setRotation((180/b2_pi) * this->ground->GetAngle());
	    	wall1Sprite.setPosition((this->wall1->GetPosition().x * SCALE), this->wall1->GetPosition().y * SCALE);
    		wall1Sprite.setRotation((180/b2_pi) * this->wall1->GetAngle());
    		wall2Sprite.setPosition(this->wall2->GetPosition().x * SCALE, (this->wall2->GetPosition().y * SCALE));
    		wall2Sprite.setRotation((180/b2_pi) * this->wall2->GetAngle());
    		wall3Sprite.setPosition(((this->wall3->GetPosition().x) * SCALE), ((this->wall3->GetPosition().y )* SCALE));
    		wall3Sprite.setRotation((180/b2_pi) * this->wall3->GetAngle());
			window->clear();
			window->draw(sprite);
			draw(player1);
			draw(player2);
			window->draw(this->groundSprite);
	        window->draw(this->wall1Sprite);
      		window->draw(this->wall2Sprite);
      		window->draw(this->wall3Sprite);

	        window->draw(this->groundSprite);
	        if(gemExists)
	        	window->draw(this->gemSprite);
	        window->display();
		}
	}
	else
	{
		float x[12],y[12],angle[12];
		while(window->isOpen())
		{
			sf::Event event;

	        while (window->pollEvent(event))
	        {
	            if (event.type == sf::Event::Closed)
	                window->close();
	        }
	        std::thread thr1,thr2;
	        thr1=std::thread(&Game::client_send,this);
	        thr2=std::thread(&Game::client_receive,this,x,y,angle);
	        thr1.join();
	        thr2.join();
	        sf::Texture texture;
			texture.setRepeated(true);
			if (!texture.loadFromFile("res/texture.png"))
			{
				std::cout << "Error loading texture" << std::endl;
			}
	        sf::Sprite sprite;
			sprite.setTexture(texture);
			sprite.setTextureRect(sf::IntRect(0, 0, 1366, 768));
			sprite.setColor(sf::Color(255,255,255,40));
			texture.setSmooth(true);
			groundSprite.setPosition(this->ground->GetPosition().x * SCALE, this->ground->GetPosition().y * SCALE);
	    	groundSprite.setRotation((180/b2_pi) * this->ground->GetAngle());
	    	wall1Sprite.setPosition((this->wall1->GetPosition().x * SCALE), this->wall1->GetPosition().y * SCALE);
    		wall1Sprite.setRotation((180/b2_pi) * this->wall1->GetAngle());
    		wall2Sprite.setPosition(this->wall2->GetPosition().x * SCALE, (this->wall2->GetPosition().y * SCALE));
    		wall2Sprite.setRotation((180/b2_pi) * this->wall2->GetAngle());
    		wall3Sprite.setPosition(((this->wall3->GetPosition().x) * SCALE), ((this->wall3->GetPosition().y )* SCALE));
    		wall3Sprite.setRotation((180/b2_pi) * this->wall3->GetAngle());
			window->clear();
			window->draw(sprite);
			draw(player1);
			draw(player2);
			window->draw(this->groundSprite);
	        window->draw(this->wall1Sprite);
      		window->draw(this->wall2Sprite);
      		window->draw(this->wall3Sprite);
	        window->display();

		}	
	}
}

void Game::generateGem()
{
	int x = rand();
	int y = rand();
	x = 100 + x % 1000;
	y = 50 + y % 500; 
	//std::cout<<x<<" "<<y<<std::endl;
	this->gemSprite.setPosition(x,y);
	this->gemExists = true;
}

void Game::isGemCollected()
{
	int gemPositionX = gemSprite.getPosition().x;
	int gemPositionY = gemSprite.getPosition().y;
	int p1PositionX = player1->head->GetPosition().x*SCALE;
	int p1PositionY = player1->head->GetPosition().y*SCALE;
	int p2PositionX = player2->head->GetPosition().x*SCALE;
	int p2PositionY = player2->head->GetPosition().y*SCALE;
	//std::cout<<gemPositionX<<" "<<gemPositionY<<" "<<p1PositionX<< " "<<p1PositionY<<" "<<p2PositionX<<" "<<p2PositionY<<std::endl;
	if(distance(gemPositionX, gemPositionY, p1PositionX, p1PositionY) <= 50)
	{
		//std::cout<<distance(gemPositionX, gemPositionY, p1PositionX, p1PositionY)<<std::endl;
		player1->setHealth(player1->getHealth()+5);
		this->gemExists = false;
	}
	else if(distance(gemPositionX, gemPositionY, p2PositionX, p2PositionY) <= 50)
	{
		//std::cout<<distance(gemPositionX, gemPositionY, p2PositionX, p2PositionY)<<std::endl;
		player2->setHealth(player2->getHealth()+5);
		this->gemExists = false;
	}
}

float Game::distance(int x1, int y1, int x2, int y2)
{
	if(abs(x2-x1) > 50)
		return 51;
	if(abs(y2-y1) >50)
		return 51;
	return sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
}

b2Body* Game::createGround(b2Vec2 position,int angle)
{
    this->groundUserData = -1;
	b2BodyDef BodyDef;
    BodyDef.position = position;
    BodyDef.type = b2_staticBody;
    BodyDef.angle=angle *DEGTORAD;
    b2Body* Body = world->CreateBody(&BodyDef);
    b2PolygonShape Shape;
    Shape.SetAsBox((1366.f/2)/SCALE, (16.f/2)/SCALE);
    b2FixtureDef FixtureDef;
    FixtureDef.restitution=1;
    FixtureDef.density = 0.f;
    FixtureDef.shape = &Shape;
    Body->CreateFixture(&FixtureDef);
    Body->SetUserData(&this->groundUserData);
   	return Body;
}

void Game::initPlayer(Player *player, float X, int offset)
{
    player->headUserData = 1+offset;
    player->bodyUserData = 2+offset;
    player->left_handUserData = 3+offset;
    player->right_handUserData = 3+offset;
    player->left_legUserData = 4+offset;
    player->right_legUserData = 4+offset;
	player->head = player->createhead(world, b2Vec2(X/SCALE,200.f/SCALE), 0, 25.f, 1.f, 1.f);
    player->body = player->createbody(world, b2Vec2(X/SCALE,270.f/SCALE), 0, 20.f, 90.f, 1.f, 1.f);
    player->left_hand = player->createbody(world, b2Vec2((X-40.f)/SCALE,(230.f)/SCALE), 0, 60.f, 10.f, 1.f, 1.f);
    player->right_hand = player->createbody(world, b2Vec2((X+40.f)/SCALE,(230.f)/SCALE), 0, 60.f, 10.f, 1.f, 1.f);
    player->left_leg = player->createbody(world, b2Vec2((X-temp1)/SCALE,(315.f+temp1)/SCALE), 0, 10.f, 75.f, 1.f, 1.f);
    player->right_leg = player->createbody(world, b2Vec2((X+temp1)/SCALE,(315.f+temp1)/SCALE), 0, 10.f, 75.f, 1.f, 1.f);
    player->headJoint = player->createRevoluteJoint(world, player->head, player->body, b2Vec2(0.f,25.0f/SCALE), b2Vec2(0.f,-45.0f/SCALE), 0, 0);
    player->left_legJoint = player->createRevoluteJoint(world, player->body, player->left_leg, b2Vec2(0.f/SCALE,45.0f/SCALE), b2Vec2((temp1-12)/SCALE,-temp1/SCALE), 30, 60);
    player->right_legJoint = player->createRevoluteJoint(world, player->body, player->right_leg, b2Vec2(0.f/SCALE,45.0f/SCALE), b2Vec2(-(temp1-12)/SCALE,-temp1/SCALE), -60, -30);
    player->left_handJoint = player->createRevoluteJoint(world, player->body, player->left_hand, b2Vec2(-10.f/SCALE,-40.0f/SCALE), b2Vec2(25.f/SCALE,0.f/SCALE), -10, 10);
    player->right_handJoint = player->createRevoluteJoint(world, player->body, player->right_hand, b2Vec2(10.f/SCALE,-40.0f/SCALE), b2Vec2(-25.f/SCALE,0.f/SCALE), -10, 10);
    player->head->SetUserData(&player->headUserData);
    player->body->SetUserData(&player->bodyUserData);
    player->left_hand->SetUserData(&player->left_handUserData);
    player->right_hand->SetUserData(&player->right_handUserData);
    player->left_leg->SetUserData(&player->left_legUserData);
    player->right_leg->SetUserData(&player->right_legUserData);
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

void Game::checkcollision()
{
	int r1=(listener->Queue).size();
    if(r1 > 30)
        r1=30;
    for(int i=0;i<r1;i++)
    {
        p = (listener->Queue).front();
        (listener->Queue).pop();
        worker[i]=std::thread(&Game::decrease_hp,this,p.first,p.second);
    }
    for(int i=0;i<r1;i++)
        worker[i].join();
}

void Game::decrease_hp(int a,int b)
{
	int damage1=0,damage2=0;
	int new_hp1,new_hp2;
	if( (a==1 && b==5) || (a==5 && b==1) )
	{
		damage1=10;
		damage2=10;
	}
	else if( (a==1 && b==7) || (a==7 && b==1) )
	{
		damage1=10;
	}
	else if( (a==2 && b==8) || (a==8 && b==2) )
	{
		damage1=10;
	}
	else if( (a==2 && b==7) || (a==7 && b==2) )
	{
		damage1=5;
	}
	else if( (a==2 && b==8) || (a==8 && b==2) )
	{
		damage1=5;
	}
	else if( (a==3 && b==5) || (a==5 && b==3) )
	{
		damage2=10;
	}
	else if( (a==4 && b==5) || (a==5 && b==4) )
	{
		damage2=10;
	}
	else if( (a==3 && b==6) || (a==6 && b==3) )
	{
		damage2=5;
	}
	else if( (a==4 && b==6) || (a==6 && b==4) )
	{
		damage2=5;
	}
	m.lock();
	new_hp1 = player1->getHealth() - damage1;
	new_hp2 = player2->getHealth() - damage2;
	player1->setHealth(new_hp1);
	player2->setHealth(new_hp2);
	m.unlock();
}
void Game::server_send()
{

	sf::Packet packet2;
    packet2<<player1->head->GetPosition().x*SCALE<<player1->head->GetPosition().y*SCALE<<player1->head->GetAngle() * (180/b2_pi);
    packet2<<player1->body->GetPosition().x*SCALE<<player1->body->GetPosition().y*SCALE<<player1->body->GetAngle() * (180/b2_pi);
    packet2<<player1->left_leg->GetPosition().x*SCALE<<player1->left_leg->GetPosition().y*SCALE<<player1->left_leg->GetAngle() * (180/b2_pi);
    packet2<<player1->right_leg->GetPosition().x*SCALE<<player1->right_leg->GetPosition().y*SCALE<<player1->right_leg->GetAngle() * (180/b2_pi);
    packet2<<player1->left_hand->GetPosition().x*SCALE<<player1->left_hand->GetPosition().y*SCALE<<player1->left_hand->GetAngle() * (180/b2_pi);	
    packet2<<player1->right_hand->GetPosition().x*SCALE<<player1->right_hand->GetPosition().y*SCALE<<player1->right_hand->GetAngle() * (180/b2_pi);

    packet2<<player2->head->GetPosition().x*SCALE<<player2->head->GetPosition().y*SCALE<<player2->head->GetAngle() * (180/b2_pi);
    packet2<<player2->body->GetPosition().x*SCALE<<player2->body->GetPosition().y*SCALE<<player2->body->GetAngle() * (180/b2_pi);
    packet2<<player2->left_leg->GetPosition().x*SCALE<<player2->left_leg->GetPosition().y*SCALE<<player2->left_leg->GetAngle() * (180/b2_pi);
    packet2<<player2->right_leg->GetPosition().x*SCALE<<player2->right_leg->GetPosition().y*SCALE<<player2->right_leg->GetAngle() * (180/b2_pi);
    packet2<<player2->left_hand->GetPosition().x*SCALE<<player2->left_hand->GetPosition().y*SCALE<<player2->left_hand->GetAngle() * (180/b2_pi);	
    packet2<<player2->right_hand->GetPosition().x*SCALE<<player2->right_hand->GetPosition().y*SCALE<<player2->right_hand->GetAngle() * (180/b2_pi);
    packet2<<player1->getHealth()<<player2->getHealth();

    socket.send(packet2);
}

void Game::server_receive()
{
	sf::Packet packet1;
	socket.receive(packet1);
    std::string s;
    packet1>>s;
    if (s=="D")
    {
        player2->body->SetAngularVelocity(60*DEGTORAD);
    }

    else if (s=="A")
    {
        player2->body->SetAngularVelocity(-60*DEGTORAD);
    }

    else if (s=="L")
    {
        player2->body->SetLinearVelocity(b2Vec2(-4,0));
        player2->body->SetLinearVelocity(b2Vec2(-4,0));
    }

    else if (s=="R")
    {
        player2->body->SetLinearVelocity(b2Vec2(4,0));
        player2->body->SetLinearVelocity(b2Vec2(4,0));
    }

    else if (s=="U")
    {
        player2->body->SetLinearVelocity(b2Vec2(0,-4));
        player2->body->SetLinearVelocity(b2Vec2(0,-4));
    }

    else if (s=="B")
    {
        player2->head->SetLinearVelocity(b2Vec2(0,4));
        player2->body->SetLinearVelocity(b2Vec2(0,4));
    }
}

void Game::client_send()
{
	sf::Packet packet2;
	std::string s="M";

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) )
    {
        s="D";
        packet2<<s;
    }

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) )
    {
    	s="A";
    	packet2<<s;
    }

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
    	s="L";
    	packet2<<s;
    }

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
    	s="R";
    	packet2<<s;
    }

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
    	s="U";
    	packet2<<s;
    }

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
    	s="B";
    	packet2<<s;
    }
	socket.send(packet2);
}

void Game::client_receive(float* x,float* y ,float* angle)
{
	sf::Packet packet1;
	int hp1,hp2;
	socket.receive(packet1);
	for(int i=0;i<12;i++)
		packet1>>x[i]>>y[i]>>angle[i];
	packet1>>hp1>>hp2;

	player1->headSprite.setPosition(x[0],y[0]);
    player1->headSprite.setRotation(angle[0]);

    player1->bodySprite.setPosition(x[1],y[1]);
    player1->bodySprite.setRotation(angle[1]);

    player1->left_legSprite.setPosition(x[2],y[2]);
    player1->left_legSprite.setRotation(angle[2]);

    player1->right_legSprite.setPosition(x[3],y[3]);
    player1->right_legSprite.setRotation(angle[3]);

    player1->left_handSprite.setPosition(x[4],y[4]);
    player1->left_handSprite.setRotation(angle[4]);

    player1->right_handSprite.setPosition(x[5],y[5]);
    player1->right_handSprite.setRotation(angle[5]);

    player2->headSprite.setPosition(x[6],y[6]);
    player2->headSprite.setRotation(angle[6]);

    player2->bodySprite.setPosition(x[7],y[7]);
    player2->bodySprite.setRotation(angle[7]);

    player2->left_legSprite.setPosition(x[8],y[8]);
    player2->left_legSprite.setRotation(angle[8]);

    player2->right_legSprite.setPosition(x[9],y[9]);
    player2->right_legSprite.setRotation(angle[9]);

    player2->left_handSprite.setPosition(x[10],y[10]);
    player2->left_handSprite.setRotation(angle[10]);

    player2->right_handSprite.setPosition(x[11],y[11]);
    player2->right_handSprite.setRotation(angle[11]);

    player1->setHealth(hp1);
    player2->setHealth(hp2);

}
}