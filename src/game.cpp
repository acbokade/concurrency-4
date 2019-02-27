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
Game::Game(GameDataRef data,string s,bool client,string myip): _data(data)
{
	this->window = &(_data->window);
	b2Vec2 gravity(0.0f, 0.0f);
	this->world = new b2World(gravity);
    this->listener = new myListener();
	this->world->SetContactListener(listener);
	this->player1 = new Player();
	this->player2 = new Player();
	this->myip = myip;

	if(client==false)
		this->player1->setName(s);
	else
		this->player2->setName(s);

	if(!this->font.loadFromFile("res/arial.ttf"))
		std::cerr<<"Failed to load font!"<<std::endl;
	this->rtext.setPosition(420,180);
	this->rtext.setCharacterSize(60);
	this->rtext.setFont(this->font);
    this->rtext.setColor(sf::Color::White);
    this->rtext.setString("ROUND OVER!!!");

    this->rtext1.setPosition(500,300);
	this->rtext1.setCharacterSize(60);
	this->rtext1.setFont(this->font);
    this->rtext1.setColor(sf::Color::White);

    this->rtext2.setPosition(500,300);
	this->rtext2.setCharacterSize(60);
	this->rtext2.setFont(this->font);
    this->rtext2.setColor(sf::Color::White);

    this->rtext3.setPosition(500,300);
	this->rtext3.setCharacterSize(60);
	this->rtext3.setFont(this->font);
    this->rtext3.setColor(sf::Color::White);
    this->rtext3.setString("TIE");

    this->player1NameText.setPosition(350,2);
	this->player1NameText.setCharacterSize(25);
	this->player1NameText.setFont(this->font);
    this->player1NameText.setColor(sf::Color::Red);

    this->player2NameText.setPosition(966,2);
	this->player2NameText.setCharacterSize(25);
	this->player2NameText.setFont(this->font);
    this->player2NameText.setColor(sf::Color::Red);

    setPlayerRounds(true, 0);
    setPlayerRounds(false, 0);

    this->player1RoundsText.setPosition(630.f,15.f);
	this->player1RoundsText.setCharacterSize(35);
	this->player1RoundsText.setFont(this->font);
    this->player1RoundsText.setColor(sf::Color::Red);
    this->player1RoundsText.setString(std::to_string(this->player1Rounds));

    this->player2RoundsText.setPosition(725.f,15.f);
	this->player2RoundsText.setCharacterSize(35);
	this->player2RoundsText.setFont(this->font);
    this->player2RoundsText.setColor(sf::Color::Red);
    this->player2RoundsText.setString(std::to_string(this->player2Rounds));

	this->isClient = client;
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
    this->roundTexture.loadFromFile("res/box2.png");
    this->player1RoundsSprite.setTexture(roundTexture);
    this->player1RoundsSprite.setOrigin((sf::Vector2f)roundTexture.getSize()/2.f);
    this->player1RoundsSprite.setPosition(640.f,35.f);
    this->player2RoundsSprite.setTexture(roundTexture);
    this->player2RoundsSprite.setOrigin((sf::Vector2f)roundTexture.getSize()/2.f);
    this->player2RoundsSprite.setPosition(736.f,35.f);
    this->player1->init(true);
	this->player2->init(false);
	this->gemExists = false;
	this->isExiting = false;
};

Game::~Game()
{
}

void Game::connect()
{
	if(!isClient)
	{
		std::thread t1(&Game::serverListen,this,false);
		std::thread t2(&Game::serverListen,this,true);
		sf::Event event1;
		int flag =0;
		while(!(this->accept) || !(this->accept1))
		{
			window->pollEvent(event1);
            if(event1.type==sf::Event::Closed)
            {
            	this->tcplistener.close();
				this->tcplistener1.close();
            	this->sendSocket.disconnect();
				this->listenSocket.disconnect();
				window->close();
				flag=1;
                break;
			}
		}
		if(flag==0)
		{
			t1.join();
			t2.join();
		}
	}
	else
	{
		if(this->sendSocket.connect(this->myip,5080)!=sf::Socket::Done)
			std::cerr<<"Failed to connect!"<<std::endl;
		if(this->listenSocket.connect(this->myip,6080)!=sf::Socket::Done)
			std::cerr<<"Failed to connect!"<<std::endl;
	}
    this->sendSocket.setBlocking(true);
	this->listenSocket.setBlocking(true);
}

void Game::serverListen(bool flag)
{
	if(flag == false)
	{
		if(tcplistener.listen(5080)!=sf::Socket::Done)
			std::cerr<<"Server error while listening !"<<std::endl;
		if(tcplistener.accept(sendSocket)!=sf::Socket::Done)
			std::cerr<<"Error while accepting conection !"<<std::endl;	
		this->accept =true;
	}
	else
	{
		if(tcplistener1.listen(6080)!=sf::Socket::Done)
			std::cerr<<"Server error while listening !"<<std::endl;
		if(tcplistener1.accept(listenSocket)!=sf::Socket::Done)
			std::cerr<<"Error while accepting conection !"<<std::endl;
		this->accept1 =true;
    }
}

void Game::gameLoop()
{
	srand(time(0));
	char con;
	if(!isClient)
	{
		this->isPlaying = true;
		initPlayer(player1, 200.f,0);
		initPlayer(player2, 500.f,4);
	    player1->setHealth(100);
	    player2->setHealth(100);
	    sf::Packet packet1,packet2;
		if(listenSocket.receive(packet1)!=sf::Socket::Done)
			std::cerr<<"Error while receiving packet !"<<std::endl;
		std::string myName;
		packet1>>myName;
		player2->setName(myName);
		myName = player1->getName();
		packet2<<myName;
		if(sendSocket.send(packet2)!=sf::Socket::Done)
			std::cerr<<"Error while sending packet !"<<std::endl;
	    gettimeofday(&prev_time,NULL);
	    gettimeofday(&prev_time1, NULL);
	    sf::Texture texture;
		texture.setRepeated(true);

		if (!texture.loadFromFile("res/texture.png"))
		{
			std::cerr<<"Failed to load texture!"<<std::endl;
		}

		sf::Sprite sprite;
		sprite.setTexture(texture);
		sprite.setTextureRect(sf::IntRect(0, 0, 1366, 768));
		sprite.setColor(sf::Color(255,255,255,40));
		texture.setSmooth(true);
		sf::Texture bar1;
		sf::Texture bar2;
    	bar1.loadFromFile("res/bar.png");
    	bar2.loadFromFile("res/bar.png");
    	sf::Sprite barsprite1;
    	barsprite1.setTexture(bar1);
    	sprite.setColor(sf::Color(255,255,255,100));
    	barsprite1.setOrigin(260.f,6.f);
    	barsprite1.setPosition(350.f,35.f);
    	sf::Sprite barsprite2;
    	barsprite2.setTexture(bar2);
    	sprite.setColor(sf::Color(255,255,255,100));
    	barsprite2.setOrigin(260.f,6.f);
    	barsprite2.setPosition(1026.f,35.f);
		this->gemThread = std::thread(&Game::generateGem, this);
		this->rtext1.setString(player1->getName() + " Wins!!!");
		this->rtext2.setString(player2->getName() + " Wins!!!");
		this->player1NameText.setString(player1->getName());
		this->player2NameText.setString(player2->getName());
		while(window->isOpen())
		{	
			sf::Event event;
	        while (window->pollEvent(event))
	        {
	            if (event.type == sf::Event::Closed)
	            {
	            	this->tcplistener.close();
					this->tcplistener1.close();
	            	this->sendSocket.disconnect();
					this->listenSocket.disconnect();
					this->isExiting = true;
	                window->close();
	            }
	        }

	        if(player1->getHealth()>=0 && player1->getHealth()<=100)
	        	barsprite1.setScale((float) player1->getHealth()/100.f,1.f);
	        if(player2->getHealth()>=0 && player2->getHealth()<=100)
	        	barsprite2.setScale((float) player2->getHealth()/100.f,1.f);
	        if(player1->getHealth()<=50)
	        	barsprite1.setColor(sf::Color(255,0,0,255));
	    	else if(player1->getHealth()>50)
	    	{
	    		barsprite1.setColor(sf::Color(255,255,255,255));
	    	}
	    	if(player2->getHealth()<=50)
	        	barsprite2.setColor(sf::Color(255,0,0,255));
	    	else if(player2->getHealth()>50)
	    	{
	    		barsprite2.setColor(sf::Color(255,255,255,255));
	    	}
	        
			this->world->Step(timeStep, velocityIterations, positionIterations);
			gettimeofday(&current_time,NULL);
	        time_difference = (double) ((current_time.tv_sec * 1000000 + current_time.tv_usec) - (prev_time.tv_sec * 1000000 + prev_time.tv_usec)) / 1000.0;


	        if(time_difference > 100)
	        {
	            checkcollision();
	            gettimeofday(&prev_time,NULL);
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
	        }

	        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	        {
	            player1->body->SetLinearVelocity(b2Vec2(4,0));
	        }

	        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	        {
	            player1->body->SetLinearVelocity(b2Vec2(0,-4));
	        }

	        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	        {
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
	        window->draw(this->player1RoundsSprite);
	        window->draw(this->player2RoundsSprite);
	        window->draw(barsprite1);
	        window->draw(barsprite2);
	        window->draw(this->player1NameText);
	        window->draw(this->player2NameText);
	        window->draw(this->player1RoundsText);
	        window->draw(this->player2RoundsText);
	        m1.lock();
	        if(gemExists)
	        	window->draw(this->gemSprite);
	        m1.unlock();
	        window->display();

	        if(player1->health <= 0 && player2->health >0)
	        {
	        	while(!(listener->Queue).empty())
	        	{
	        		(listener->Queue).pop();
	        	}
	        	this->_clock.restart();
	        	while(this->_clock.getElapsedTime().asSeconds() < 3)
	        	{
	        		window->clear(sf::Color::Black);
	        		window->draw(rtext);
	        		window->draw(rtext2);
	        		window->display();
	        	}
	        	setPlayerRounds(false,getPlayerRounds(false)+1);
	        	destroyBody();
	        	break;
	        }
	        else if(player1->health > 0 && player2->health <= 0)
	        {
	        	while(!(listener->Queue).empty())
	        	{
	        		(listener->Queue).pop();
	        	}
	        	this->_clock.restart();
	        	while(this->_clock.getElapsedTime().asSeconds() < 3)
	        	{
	        		window->clear(sf::Color::Black);
	        		window->draw(rtext);
	        		window->draw(rtext1);
	        		window->display();
	        	}
	        	setPlayerRounds(true,getPlayerRounds(true)+1);
	        	destroyBody();
	        	break;
	        }
	        else if (player1->health <= 0 && player2->health <=0)
	        {
	        	while(!(listener->Queue).empty())
	        	{
	        		(listener->Queue).pop();
	        	}
	        	this->_clock.restart();
	        	while(this->_clock.getElapsedTime().asSeconds() < 3)
	        	{
	        		window->clear(sf::Color::Black);
	        		window->draw(rtext);
	        		window->draw(rtext3);
	        		window->display();
	        	}
	        	setPlayerRounds(false,getPlayerRounds(false)+1);
	        	setPlayerRounds(true,getPlayerRounds(true)+1);
	        	destroyBody();
	        	break;
	        }
	        this->player1RoundsText.setString(std::to_string(this->player1Rounds));
	        this->player2RoundsText.setString(std::to_string(this->player2Rounds));

		}
		this->isPlaying = false;
		this->gemThread.join();
	}

	else
	{
		float x[12],y[12],angle[12],gempos[2];
		int hp[2];
		hp[0]=100;
		hp[1]=100;
		sf::Packet packet1,packet2;
		std::string myName;
		myName = player2->getName();
		packet2<<myName;
		if(listenSocket.send(packet2)!=sf::Socket::Done)
			std::cerr<<"Error while sending packet !"<<std::endl;
		if(sendSocket.receive(packet1)!=sf::Socket::Done)
			std::cerr<<"Error while receiving packet !"<<std::endl;
		packet1>>myName;
		player1->setName(myName);
		this->rtext1.setString(player1->getName() + " Wins!!!");
		this->rtext2.setString(player2->getName() + " Wins!!!");
		this->player1NameText.setString(player1->getName());
		this->player2NameText.setString(player2->getName());
		while(window->isOpen())
		{
			sf::Event event;

	        while (window->pollEvent(event))
	        {
	            if (event.type == sf::Event::Closed)
	            {
	            	this->tcplistener.close();
					this->tcplistener1.close();
	            	this->sendSocket.disconnect();
					this->listenSocket.disconnect();
					this->isExiting = true;
	                window->close();
	            }
	        }
	        std::thread thr1,thr2;
	        thr1=std::thread(&Game::client_send,this);
	        thr2=std::thread(&Game::client_receive,this,x,y,angle,hp,gempos);
	        thr1.join();
	        thr2.join();
	        sf::Texture texture;
			texture.setRepeated(true);
			if (!texture.loadFromFile("res/texture.png"))
			{
				std::cerr<<"Failed to load texture!"<<std::endl;
			}
	        sf::Sprite sprite;
			sprite.setTexture(texture);
			sprite.setTextureRect(sf::IntRect(0, 0, 1366, 768));
			sprite.setColor(sf::Color(255,255,255,40));
			texture.setSmooth(true);
			sf::Texture bar1;
			sf::Texture bar2;
    		if(!bar1.loadFromFile("res/bar.png"))
    			std::cerr<<"Failed to load texture!"<<std::endl;
    		if(!bar2.loadFromFile("res/bar.png"))
    			std::cerr<<"Failed to load texture!"<<std::endl;
    		sf::Sprite barsprite1;
    		barsprite1.setTexture(bar1);
    		sprite.setColor(sf::Color(255,255,255,100));
    		barsprite1.setOrigin(260.f,6.f);
    		barsprite1.setPosition(350.f,35.f);

    		sf::Sprite barsprite2;
    		barsprite2.setTexture(bar2);
    		sprite.setColor(sf::Color(255,255,255,100));
    		barsprite2.setOrigin(260.f,6.f);
    		barsprite2.setPosition(1026.f,35.f);

    		if(player1->getHealth()>=0 && player1->getHealth()<=100)
    			barsprite1.setScale((float) player1->getHealth()/100.f,1.f);
	        if(player2->getHealth()>=0 && player2->getHealth()<=100)
	        	barsprite2.setScale((float) player2->getHealth()/100.f,1.f);
	        if(player1->getHealth()<=50)
	        	barsprite1.setColor(sf::Color(255,0,0,255));
	    	else if(player1->getHealth()>50)
	    		barsprite1.setColor(sf::Color(255,255,255,255));
	    	if(player2->getHealth()<=50)
	        	barsprite2.setColor(sf::Color(255,0,0,255));
	    	else if(player2->getHealth()>50)
	    		barsprite2.setColor(sf::Color(255,255,255,255));

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
			if(gemExists)
				window->draw(this->gemSprite);
			window->draw(this->groundSprite);
	        window->draw(this->wall1Sprite);
      		window->draw(this->wall2Sprite);
      		window->draw(this->wall3Sprite);
      		window->draw(barsprite1);
	        window->draw(barsprite2);
	        window->draw(this->player1RoundsSprite);
	        window->draw(this->player2RoundsSprite);
	        window->draw(this->player1NameText);
	        window->draw(this->player2NameText);
	        window->draw(this->player1RoundsText);
	        window->draw(this->player2RoundsText);
	        window->display();
	        if(player1->health <= 0 && player2->health >0)
	        {
	        	this->_clock.restart();
	        	while(this->_clock.getElapsedTime().asSeconds() < 3)
	        	{
	        		window->clear(sf::Color::Black);
	        		window->draw(rtext);
	        		window->draw(rtext2);
	        		window->display();
	        	}
	        	setPlayerRounds(false,getPlayerRounds(false)+1);
	        	break;
	        }
	        else if(player1->health > 0 && player2->health <= 0)
	        {
	        	this->_clock.restart();
	        	while(this->_clock.getElapsedTime().asSeconds() < 3)
	        	{
	        		window->clear(sf::Color::Black);
	        		window->draw(rtext);
	        		window->draw(rtext1);
	        		window->display();
	        	}
	        	setPlayerRounds(true,getPlayerRounds(true)+1);
	        	break;
	        }
	        else if (player1->health <= 0 && player2->health <=0)
	        {
	        	this->_clock.restart();
	        	while(this->_clock.getElapsedTime().asSeconds() < 3)
	        	{
	        		window->clear(sf::Color::Black);
	        		window->draw(rtext);
	        		window->draw(rtext3);
	        		window->display();
	        	}
	        	setPlayerRounds(false,getPlayerRounds(false)+1);
	        	setPlayerRounds(true,getPlayerRounds(true)+1);
	        	break;
	        }
	        this->player1RoundsText.setString(std::to_string(this->player1Rounds));
	        this->player2RoundsText.setString(std::to_string(this->player2Rounds));
		}	
	}
}

int Game::getPlayerRounds(bool player)
{
	if(player)
		return this->player1Rounds;
	else
		return this->player2Rounds;
}

void Game::setPlayerRounds(bool player, int rounds)
{
	if(player)
		this->player1Rounds = rounds;
	else
		this->player2Rounds = rounds;
}

void Game::generateGem()
{
	while(isPlaying)
	{
		gettimeofday(&current_time1, NULL);
		time_difference1 = (double) ((current_time1.tv_sec * 1000000 + current_time1.tv_usec) - (prev_time1.tv_sec * 1000000 + prev_time1.tv_usec)) / 1000.0;
			        
		if(time_difference1 > 5000)
		{
	      	int x = rand();
			int y = rand();
			x = 100 + x % 550;
			y = 100 + y % 1100; 
			this->gemSprite.setPosition(x,y);
			m1.lock();
			this->gemExists = true;
			m1.unlock();
		    gettimeofday(&prev_time1, NULL);
		}

		if(gemExists)
		{
		   	int gemPositionX = gemSprite.getPosition().x;
			int gemPositionY = gemSprite.getPosition().y;
			int p1PositionX = player1->head->GetPosition().x*SCALE;
			int p1PositionY = player1->head->GetPosition().y*SCALE;
			int p2PositionX = player2->head->GetPosition().x*SCALE;
			int p2PositionY = player2->head->GetPosition().y*SCALE;
			if(distance(gemPositionX, gemPositionY, p1PositionX, p1PositionY) <= 50)
			{
				m.lock();
				if(player1->getHealth()<=95)
					player1->setHealth(player1->getHealth()+5);
				m.unlock();
				m1.lock();
				this->gemExists = false;
				m1.unlock();
			}
			else if(distance(gemPositionX, gemPositionY, p2PositionX, p2PositionY) <= 50)
			{
				m.lock();
				if(player2->getHealth()<=95)
					player2->setHealth(player2->getHealth()+5);
				m.unlock();
				m1.lock();
				this->gemExists = false;
				m1.unlock();
			}
			m1.lock();
		    if(!gemExists)
		    	gettimeofday(&prev_time1, NULL);
		    m1.unlock();
		}
	}	
}

void Game::destroyBody()
{
	world->DestroyBody(player1->head);
	world->DestroyBody(player1->body);
	world->DestroyBody(player1->left_hand);
	world->DestroyBody(player1->right_hand);
	world->DestroyBody(player1->left_leg);
	world->DestroyBody(player1->right_leg);
	world->DestroyBody(player2->head);
	world->DestroyBody(player2->body);
	world->DestroyBody(player2->left_hand);
	world->DestroyBody(player2->right_hand);
	world->DestroyBody(player2->left_leg);
	world->DestroyBody(player2->right_leg);
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
		damage1=5;
		damage2=5;
	}
	else if( (a==1 && b==7) || (a==7 && b==1) )
	{
		damage1=5;
	}
	else if( (a==1 && b==8) || (a==8 && b==1) )
	{
		damage1=5;
	}
	else if( (a==2 && b==8) || (a==8 && b==2) )
	{
		damage1=3;
	}
	else if( (a==2 && b==7) || (a==7 && b==2) )
	{
		damage1=3;
	}
	else if( (a==3 && b==5) || (a==5 && b==3) )
	{
		damage2=5;
	}
	else if( (a==4 && b==5) || (a==5 && b==4) )
	{
		damage2=5;
	}
	
	else if( (a==3 && b==6) || (a==6 && b==3) )
	{
		damage2=3;
	}
	else if( (a==4 && b==6) || (a==6 && b==4) )
	{
		damage2=3;
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
    packet2<<gemExists<<gemSprite.getPosition().x<<gemSprite.getPosition().y;
    if(sendSocket.send(packet2)!=sf::Socket::Done)
		std::cerr<<"Error while sending packet from server !"<<std::endl;
}

void Game::server_receive()
{
	sf::Packet packet1;
	if(listenSocket.receive(packet1)!=sf::Socket::Done)
		std::cerr<<"Error while receiving packet from client!"<<std::endl;
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
    }

    else if (s=="R")
    {
        player2->body->SetLinearVelocity(b2Vec2(4,0));
    }

    else if (s=="U")
    {
        player2->body->SetLinearVelocity(b2Vec2(0,-4));
    }

    else if (s=="B")
    {
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
	if(listenSocket.send(packet2)!=sf::Socket::Done)
			std::cerr<<"Error while sending packet from client !"<<std::endl;
}

void Game::client_receive(float* x,float* y ,float* angle,int* hp,float* gempos)
{
	sf::Packet packet1;
	if(sendSocket.receive(packet1)!=sf::Socket::Done)
			std::cerr<<"Error while receiving packet from server!"<<std::endl;
	for(int i=0;i<12;i++)
		packet1>>x[i]>>y[i]>>angle[i];
	packet1>>hp[0]>>hp[1];
	packet1>>this->gemExists>>gempos[0]>>gempos[1];

	this->gemSprite.setPosition(gempos[0],gempos[1]);

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

    player1->setHealth(hp[0]);
    player2->setHealth(hp[1]);

}
}