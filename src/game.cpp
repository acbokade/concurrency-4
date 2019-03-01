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
	this->player1->setName(s);
	
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


    this->player1RoundsText.setPosition(630.f,15.f);
	this->player1RoundsText.setCharacterSize(35);
	this->player1RoundsText.setFont(this->font);
    this->player1RoundsText.setColor(sf::Color::Red);
    this->player1RoundsText.setString(std::to_string(this->player1Rounds));

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
    this->player1->init(true);
	this->ground = this->createGround(b2Vec2(683.f/SCALE, 70.f/SCALE),0);
	this->wall1 = this->createGround(b2Vec2(683.f/SCALE, 698.f/SCALE),0);
	this->wall2 = this->createGround(b2Vec2(71.f/SCALE, 384.f/SCALE),90);
	this->wall3 = this->createGround(b2Vec2(1295.f/SCALE, 384.f/SCALE),90);
	this->gemExists = false;
	this->isExiting = false;
	setPlayerRounds(true, 0);
};

Game::~Game()
{
}





void Game::gameLoop()
{
	srand(time(0));
	char con;
	this->numBots++;
	this->bott=new botSom(numBots);
	if(!isClient)
	{
		this->isPlaying = true;
		initPlayer(player1, 200.f,0);
		for(size_t i = 0; i < numBots; i++)
		{
			initPlayer(&(this->bott->player[i]),400.f+(50*i),4*(i+1));
			this->bott->player[i].setHealth(100);
		}
		
	    player1->setHealth(100);
		std::string myName;
		myName = player1->getName();
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
		this->gemThread = std::thread(&Game::generateGem, this);
		this->rtext1.setString(player1->getName() + " Wins!!!");
		this->rtext2.setString(player1->getName() + " Loses!!!");
		this->player1NameText.setString(player1->getName());
		while(window->isOpen())
		{	
			sf::Event event;
	        while (window->pollEvent(event))
	        {
	            if (event.type == sf::Event::Closed)
	            {
	                this->isExiting = true;
					window->close();
	            }
	        }

	        if(player1->getHealth()>=0 && player1->getHealth()<=100)
	        	barsprite1.setScale((float) player1->getHealth()/100.f,1.f);
	        if(player1->getHealth()<=50)
	        	barsprite1.setColor(sf::Color(255,0,0,255));
	    	else if(player1->getHealth()>50)
	    	{
	    		barsprite1.setColor(sf::Color(255,255,255,255));
	    	}
	    	
	        
			this->world->Step(timeStep, velocityIterations, positionIterations);
			gettimeofday(&current_time,NULL);
	        time_difference = (double) ((current_time.tv_sec * 1000000 + current_time.tv_usec) - (prev_time.tv_sec * 1000000 + prev_time.tv_usec)) / 1000.0;

	        if(time_difference > 100)
	        {
	            checkcollision();
	            gettimeofday(&prev_time,NULL);
	        }
			

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::X) )
	        {
	            this->isExiting=true;
				break;
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

	        for(size_t i = 0; i < numBots; i++)
			{
				if(this->bott->player[i].isDestroyed==false)
				{
				b2Vec2 tmp1=this->player1->head->GetPosition()-this->bott->player[i].head->GetPosition();
				float small=rand()%3;
				
				if(((int)rand())%3==0)
				{
					tmp1.x=((int)(tmp1.x-small))%10;
					tmp1.y=((int)(tmp1.y-small))%10;
					this->bott->player[i].body->SetLinearVelocity(tmp1);
				}
				else if(((int)rand())%3==1)
				{
					tmp1.x=((int)(tmp1.x+small))%10;
					tmp1.y=((int)(tmp1.y+small))%10;
					this->bott->player[i].body->SetLinearVelocity(tmp1);
				}
				else this->bott->player[i].body->SetAngularVelocity((rand()%120)*DEGTORAD);
				}

				/*
				Easy Mode
				if(((int)rand())%6==0)
				{
					b2Vec2 tmp1=this->player1->head->GetPosition()-this->bott->player[i].head->GetPosition();
					tmp1.x=((int)(tmp1.x))%10;
					tmp1.y=((int)(tmp1.y))%10;
					this->bott->player[i].body->SetLinearVelocity(tmp1);
				}
				else if(((int)rand())%6==1)
				{
					b2Vec2 tmp1=this->player1->left_hand->GetPosition()-this->bott->player[i].head->GetPosition();
					tmp1.x=((int)(tmp1.x))%10;
					tmp1.y=((int)(tmp1.y))%10;
					this->bott->player[i].body->SetLinearVelocity(tmp1);
				}
				else if(((int)rand())%6==2)
				{
					b2Vec2 tmp1=this->player1->left_leg->GetPosition()-this->bott->player[i].head->GetPosition();
					tmp1.x=((int)(tmp1.x));
					tmp1.y=((int)(tmp1.y));
					this->bott->player[i].body->SetLinearVelocity(-tmp1);
				}
				else if(((int)rand())%6==3)
				{
					b2Vec2 tmp1=this->player1->right_hand->GetPosition()-this->bott->player[i].head->GetPosition();
					tmp1.x=((int)(tmp1.x));
					tmp1.y=((int)(tmp1.y));
					this->bott->player[i].body->SetLinearVelocity(-tmp1);
				}
				else if(((int)rand())%6==4)
				{
					b2Vec2 tmp1=this->player1->right_leg->GetPosition()-this->bott->player[i].head->GetPosition();
					tmp1.x=((int)(tmp1.x));
					tmp1.y=((int)(tmp1.y));
					this->bott->player[i].body->SetLinearVelocity(-tmp1);
				}
				else this->bott->player[i].body->SetAngularVelocity((rand()%360)*DEGTORAD);

				*/
			}
			
			updatePlayer(player1);
			for(size_t i = 0; i < numBots; i++)
			{
				updatePlayer(&(this->bott->player[i]));
			}
			
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
			for(size_t i = 0; i < numBots; i++)
			{
				if(this->bott->player[i].isDestroyed==false)draw(&(this->bott->player[i]));
			}
			
			window->draw(this->groundSprite);
	        window->draw(this->wall1Sprite);
      		window->draw(this->wall2Sprite);
      		window->draw(this->wall3Sprite);
	        window->draw(this->groundSprite);
	        window->draw(this->player1RoundsSprite);
	        window->draw(barsprite1);
	        window->draw(this->player1NameText);
	        window->draw(this->player1RoundsText);
	        m1.lock();
	        if(gemExists)
	        	window->draw(this->gemSprite);
	        m1.unlock();
	        window->display();

	        		
			if(player1->health <= 0)
	        {
	        	int success=0;
				for(size_t i = 0; i < numBots; i++)
				if((this->bott->player[i]).health>0)success++;
				if(success>0)
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
					destroyBody();
					setPlayerRounds(true,getPlayerRounds(true)+1);
					break;
				}
				
	        }
	        else if(player1->health > 0 )
	        {
	        	int success=0;
				for(size_t i = 0; i < numBots; i++)if((this->bott->player[i]).health<=0)success++;
				if(success==numBots)
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
					destroyBody();
					setPlayerRounds(true,getPlayerRounds(true)+1);
					break;
				}
				
	        }
	        else if (player1->health <= 0 )
	        {
	        	int success=0;
				for(size_t i = 0; i < numBots; i++)
				if((this->bott->player[i]).health<=0)success++;

				if(success==numBots)
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
					destroyBody();
					setPlayerRounds(true,getPlayerRounds(true)+1);
					break;
				}
				
	        }
	        this->player1RoundsText.setString(std::to_string(this->player1Rounds));

		}
		this->isPlaying = false;
		this->gemThread.join();
	}

	
}


int Game::getPlayerRounds(bool player)
{
	if(player)
		return this->player1Rounds;
}

void Game::setPlayerRounds(bool player, int rounds)
{
	if(player)
		this->player1Rounds = rounds;
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
		   	int tmpS=rand();
			int numC=tmpS%numBots;
			int gemPositionX = gemSprite.getPosition().x;
			int gemPositionY = gemSprite.getPosition().y;
			int p1PositionX = player1->head->GetPosition().x*SCALE;
			int p1PositionY = player1->head->GetPosition().y*SCALE;
			int p2PositionX = this->bott->player[numC].head->GetPosition().x*SCALE;
			int p2PositionY = this->bott->player[numC].head->GetPosition().y*SCALE;
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
				if(this->bott->player[numC].getHealth()<=95)
					this->bott->player[numC].setHealth(this->bott->player[numC].getHealth()+5);
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
	for(size_t i = 0; i < numBots; i++)
	{
		if(this->bott->player[i].isDestroyed==false)
		{
			world->DestroyBody(this->bott->player[i].head);
			world->DestroyBody(this->bott->player[i].body);
			world->DestroyBody(this->bott->player[i].left_hand);
			world->DestroyBody(this->bott->player[i].right_hand);
			world->DestroyBody(this->bott->player[i].left_leg);
			world->DestroyBody(this->bott->player[i].right_leg);
			this->bott->player[i].isDestroyed=true;
		}
	}
	for(size_t i = 0; i < numBots; i++)this->bott->player[i].isDestroyed=false;
	
	
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
	float tmp=rand()%10;
	player->head = player->createhead(world, b2Vec2(X/SCALE+tmp,200.f/SCALE+tmp), 0, 25.f, 1.f, 1.f);
    player->body = player->createbody(world, b2Vec2(X/SCALE+tmp,270.f/SCALE+tmp), 0, 20.f, 90.f, 1.f, 1.f);
    player->left_hand = player->createbody(world, b2Vec2((X-40.f)/SCALE+tmp,(230.f)/SCALE+tmp), 0, 60.f, 10.f, 1.f, 1.f);
    player->right_hand = player->createbody(world, b2Vec2((X+40.f)/SCALE+tmp,(230.f)/SCALE+tmp), 0, 60.f, 10.f, 1.f, 1.f);
    player->left_leg = player->createbody(world, b2Vec2((X-temp1)/SCALE+tmp,(315.f+temp1)/SCALE+tmp), 0, 10.f, 75.f, 1.f, 1.f);
    player->right_leg = player->createbody(world, b2Vec2((X+temp1)/SCALE+tmp,(315.f+temp1)/SCALE+tmp), 0, 10.f, 75.f, 1.f, 1.f);
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
	int damage1=0,damage2=0,playerNum=0;
	float btmp=(float)b/4.f;
	float atmp=(float)a/4.f;
	if(a>=1&&a<=4)
	{playerNum=ceil(btmp)-2;b=4+(b%4);}
	else{playerNum=ceil(atmp)-2;a=4+(a%4);}
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
		cout<<"triggered"<<endl;
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
	new_hp2 = this->bott->player[playerNum].getHealth() - damage2;
	player1->setHealth(new_hp1);
	this->bott->player[playerNum].setHealth(new_hp2);
	cout<<playerNum<<"health is "<<this->bott->player[playerNum].getHealth()<<endl;
	if(this->bott->player[playerNum].getHealth()<=0 && this->bott->player[playerNum].isDestroyed==false)
	{
		this->bott->player[playerNum].isDestroyed=true;
		world->DestroyBody(this->bott->player[playerNum].head);
		world->DestroyBody(this->bott->player[playerNum].body);
		world->DestroyBody(this->bott->player[playerNum].left_hand);
		world->DestroyBody(this->bott->player[playerNum].right_hand);
		world->DestroyBody(this->bott->player[playerNum].left_leg);
		world->DestroyBody(this->bott->player[playerNum].right_leg);
	}
	m.unlock();
}



}