#ifndef GAME_H
#define GAME_H
#include "SFML/Graphics.hpp"
#include "Box2D/Box2D.h"
#include "player.h"
#include "myListener.h"
#include "SFML/Network.hpp"
#include "SFML/Audio.hpp"
#include <queue>
#include <time.h>
#include <sys/time.h>
#include <thread>
#include <queue>
#include <mutex>
#include "State.hpp"
#include "Game.hpp"
#include <utility>
#include <string>
#include <bits/stdc++.h>

namespace stickman {
/**@class Game
* @brief Contains all basic entities required in game like window, players object, TcpListener, Send and receive sockets, Box2D world, walls,ground, 
*	sprites of all bodies to be displayed in window and functions to check collision, decrease health points, sending and receving packets from client to 
* 	server and vice versa, worker threads which checks for collision and gem thread used to generate gem.
*      
*/	
class Game
{
public:
	/** @brief Constructor for game.
	*
    *	@param data Contains StateMachine of Game, Render Window, over which game is displayed, AssetManager of game, InputManager of Game.
    *	@param s Contains name of player.
    *	@param client Boolean which is true if its client, false for server.
    *	@param myip Contains IP over which server hosts the server used by client to connect to.
    */
	Game(GameDataRef data,std::string s,bool client,std::string myip);
	/** @brief Destructor for game.
    */
	~Game();
	/** @brief The main SFML window of type RenderWindow
 	* 			over which game is displayed.
    */
	sf::RenderWindow *window ;
	/** @brief Denotes the IP Address over which server hosts.
    *	 	   	
    */
	sf::IpAddress ip;
	/** @brief  Basically, it is a TCP listener listens to a particular port and accepts if client connects. 
    */
	sf::TcpListener tcplistener;
	/** @brief It is a TCP listener whichlistens to a particular port and accepts if client connects.
    */
	sf::TcpListener tcplistener1;
	/** @brief It is a TCP Socket used for sending packets from server side and receiving packets in client side.
    */
	sf::TcpSocket sendSocket;
	/** @brief It is a TCP Socket used for sending packets from client side and receving packets in client side.
    */
	sf::TcpSocket listenSocket;
	/** @brief It is Box2D world object pointer where all the bodies of player reside.
    */
	b2World* world;
	/** @brief It is a Box2D body object pointer which is denoting the ground situated in world. 
    */
	b2Body* ground;
	/** @brief It is a Box2D body object pointer which is denoting the upper wall situated in world.
    */
	b2Body* wall1;
	/** @brief It is a Box2D body object pointer which is denoting the left most wall situated in world.
    */
	b2Body* wall2;
	/** @brief It is a Box2D body object pointer which is denoting the right most wall situated in world.
    */
	b2Body* wall3;
	/** @brief It is a string containing IP Address of server.
    */
	std::string myip;
	/** @brief Contains the userData of ground
	*
   	* 		Used to detect rcollision of a body part of player with ground.
    */
	int groundUserData;
	/** @brief Denotes texture of ground where images of ground is to loaded.
    */
	sf::Texture groundTexture;
	/** @brief Denotes texture of upper wall where image of ground is to loaded.
    */
	sf::Texture wall1Texture;
	/** @brief Denotes texture of left most wall where image of wall is to loaded.
    */
	sf::Texture wall2Texture;
	/** @brief Denotes texture of right most wall where image of wall is to loaded.
    */
	sf::Texture wall3Texture;
	/** @brief Denotes texture of background where number of rounds won by each player is displayed.
    */
	sf::Texture roundTexture;
	/** @brief Denotes texture of gem which gets generated in the game every 5 seconds.
    */
	sf::Texture gemTexture;
	/** @brief Denotes Sprite of ground used to display ground in window.
    */
	sf::Sprite groundSprite;
	/** @brief Denotes Sprite of upper wall used to display upper wall in window.
    */
	sf::Sprite wall1Sprite;
	/** @brief Denotes Sprite of lefmost wall used to display leftmost wall in window.
    */
	sf::Sprite wall2Sprite;
	/** @brief Denotes Sprite of rightmost wall used to display rightmost wall in window. 
    */
	sf::Sprite wall3Sprite;
	/** @brief Denotes Sprite of background where number of rounds won by first player is displayed.
    */
	sf::Sprite player1RoundsSprite;
	/** @brief Denotes Sprite of background where number of rounds won by second player is displayed.
    */
	sf::Sprite player2RoundsSprite;
	/** @brief Denotes Sprite of gem which gets generated in the game every 5 seconds used to display gem in window.
    */
	sf::Sprite gemSprite;
	/** @brief Denotes the iterations count of velocity in velocity phase of constraint solver in Box2D.
	*
	*	In the velocity phase the solver computes the impulses necessary for the bodies to move correctly.
    */
	int velocityIterations = 10;
	/** @brief Denotes the iterations count of position in position phase of constraint solver in Box2D.
	*
	*	In the position phase the solver adjusts the positions of the bodies to reduce overlap and joint detachment.
    */
	int positionIterations = 10;
	/** @brief Timestemp for Box2D integrator.
    */
	float timeStep = 1.0f / 240.0f;
	/** @brief Pointer to object listener of class type myListener of Box2D.
	*
	*	It is used to detect collisions between bodies and give the information about the point of contact of colliding 
	*	bodies and impulse applied during collision. 
    */
	myListener* listener;
	/** @brief Worker threads initialized to 30.
	*	
	*	Used to detect collision between multiple body parts of two players or body parts of a player with ground or walls 
	* 	and modify health points accordingly simultaneously.
    */
	std::thread worker[30];
	/** @brief Thread used to generate gem in window.
	*
	*	Thread generates gem in window after every 5 seconds and checks if gem has been consumed by player or not.
	*	Thread runs until game is finished and joins with the main thread.
    */
	std::thread gemThread;
	/** @brief Denotes Sprite of gem which gets generated in the game every 5 seconds used to display gem in window.
    */
	bool isClient;
	/** @brief Boolean variable which is true if gem exists in window, else false.
	*
	*	Used to display the gem in window if the boolean is true.
    */
	bool gemExists;
	/** @brief Boolean variable which is true until game finishes.
	*
	*	Used to generate and display gem until the boolean is true.
    */
	bool isPlaying;
	/** @brief Boolean variable which is true while window is open, and becomes false when window is closed.
	*
	*	Used to run game loop until window is closed or either of player wins the game.
    */
	bool isExiting;
	/** @brief Mutex lock used to protect and avoid simultaneous access to shared variable of first player health points
	* 	and second player health points by multiple threads.
    */
	std::mutex m;
	/** @brief Mutex lock used to protect and avoid simultaneous access to shared boolean variable gemExists by multiple threads.
    */
	std::mutex m1;
    /** @brief Pointer to first player's Player object. It contains information about everything about first player.
    *
    *	Pointer is needed to move and rotate the player, set its health points.  
    */
    Player* player1;
    /** @brief Pointer to second player's Player object. It contains information about everything about second player.
    *
    *	Pointer is needed to move and rotate the player, set its health points.  
    */
    Player* player2;
    /** @brief Pair of integers where first paramter contains user data of body part of first player and second parameter
    *	contains user data of body part of second player which were involved in collision. 
    */
    std::pair<int,int> p;
    /** @brief Denotes the number of rounds won by first player.
    */
    int player1Rounds;
    /** @brief Denotes the number of rounds won by second player.
    */
    int player2Rounds;
	/** @brief structure of timeval which gives the current time in seconds and microseconds.
	*	Used to store current time to check collision.
    */
	struct timeval current_time;
	/** @brief structure of timeval which gives the current time in seconds and microseconds.
	*	Used to store previous time to check collision.
    */
	struct timeval prev_time;
	/** @brief structure of timeval which gives the current time in seconds and microseconds.
	*	Used to store current time to generate gem.
    */
	struct timeval current_time1;
	/** @brief structure of timeval which gives the current time in seconds and microseconds.
	*	Used to store previous time to generate gem.
    */
	struct timeval prev_time1;
	/** @brief Used to check collision when time difference becomes greater than 100 milliseconds that is after every 100 milliseconds. 
    */
	double time_difference;
	/** @brief Used to generate gem when time difference becomes greater than 5 seconds that is after every 5 seconds.  
    */
	double time_difference1;
	/** @brief It is used to create ground Box2D body in the Box2D world.
	*	@param position Denotes the position of ground to be set in world.
	*	@param angle Denotes the angle of ground with respect to X-axis.
    */
	b2Body* createGround(b2Vec2 position,int angle);
	/** @brief Initialization of player object.
	*
	*	Used to create Box2D bodies of head, body, hands, legs and set their user data.
	*	@param player Takes pointer of onject player whose initalization is to done.
	*	@param X Denotes inital X coordinate of player during initialization.
	*	@param offset Used to set the user data for differnt bodies of each player. For first player offset is 0 and for 
	*	second player it is 1.
    */
	void initPlayer(Player *player, float X, int offset);
	/** @brief Game loop which runs until game is finished.
	*
	*	Separate game loop for client and server.
    */
	void gameLoop();
	/** @brief It is used to update positions and angle of all body parts of each player after each time frame.
    */
	void updatePlayer(Player *player);
	/** @brief It is used to draw different body parts like head, body, hands and legs of player in window.
	*	@param player Takes pointer of object player to update its position.
    */
	void draw(Player *player);
	/** @brief It checks collision between body parts of first player and second player.
	*
	* 	Here, Worker threads call the function decrease hp, for all type collisions happened simultaneously betweeen different
	*	body parts of first and second player. After collisions are handled, the worker threads are joined with main thread.
    */
	void checkcollision();
	/** @brief It is used to decrease health point of player according to collision of different body parts of each player.
	*	@param a Denotes User Data of body part of first player in collision.
	*	@param b Denotes User Data of body part of second player in collision.
    */
	void decrease_hp(int a, int b);
	/** @brief It generates gem at random positions in the window after every 5 seconds and checks if any player has collected gem and 
	*	accordingly increases its health points by 5.
	*
	* 	It runs on separate thread until game is running.
    */
	void generateGem();
	/** @brief Cacluclates distance between two points in the window.
	*
	*	Used to check if gem overlaps with head of any player and accordingly increase the player's health points.
	*	@param x1 X-coordinate of first point.
	*	@param y1 Y-coordinate of first point.
	* 	@param x2 X-coordinate of second point.
	* 	@param y2 Y-coordinate of second point.
    */
	float distance(int x1, int y1, int x2, int y2);
	/** @brief Used to send packets of information like position of all body parts of each player and position of gem
	*	from server side to client side.
    */
	void server_send();
	/** @brief Used to receive packets of information in server side of the key pressed by client so that server can 
	* 			simulate it in its world. 
    */
	void server_receive();
	/** @brief Used to send packets of information like the key pressed by client to move the player in client side to server side.
    */
	void client_send();
	/** @brief Used to reveive packets of information like both player's position, angle, hp and gem's position in client side from server side.
	*	@param x It is an array consisting of x coordinates of different body parts of first and second player's position in the world.
	* 	@param y It is an array consisting of y coordinates of different body parts of first and second player's position in the world.
	*	@param angle It is an array consisting of angle of different body parts of first and second player's position in the world.
	*	@param hp It is an array consisting of health points of first and second player.
    *	@param gempos It is an array consisting of x and y coordinates of gem in the window.
    */
	void client_receive(float* x,float* y,float* angle,int* hp,float* gempos);
	/** @brief In server side, TCP listener listens to client on first and second port and on client side, it is used
	*	to connect to IP address of server and the two ports.
    */
	void connect();
	/** @brief Used to destroy Box2D bodies that is head, body, right and left hand and legs of player object.  
    */
	void destroyBody();
	/** @brief TCP listener on server side listens if client has connected to any port on server's IP Address.
		@param flag If flag is false, TCP listener listens on first port and if flag is true, it listens on second port.
    */
	void serverListen(bool flag);
    /** @brief It returns number of rounds won by player.
		@param flag if player is true, it returns rounds won by first player, else second player.
    */
    int getPlayerRounds(bool player);
    /** @brief	Sets the number of rounds won by player
		@param player if player is true, it sets rounds of first player, else second player.
		@param rounds Number of rounds to be set.
    */
    void setPlayerRounds(bool player, int rounds);
	bool accept=false;
	/** @brief Boolean variable containing status of connection of client to second port of server intialized to false 
	*			Contains status of connection of client to server. It becomes true if client connects to second port and TCP
	*			listener on server side accepts it. 
    */
	bool accept1=false;
	/** @brief SFML Clock
    *	 	   	Used to display text about result of round after every round is finished for stipulated amount of time, here 3 seconds. 
    */
	sf::Clock _clock;
	/** @brief SFML Text 
    *	 	   	Text containing string "ROUND OVER" displayed after every round is finished.
    */
	sf::Text rtext;
	/** @brief SFML Text 
    *	 	   	Text containing the string "first player's name wins" displayed after round is over if first player wins that round.
    */
	sf::Text rtext1;
	/** @brief SFML Text 
    *	 	   	Text containing the string "second player's name wins" displayed after round is over if second player wins that round.
    */
	sf::Text rtext2;
	/** @brief SFML Text 
    *	 	   	TText containing string "TIE" displayed if result of round is tie.
    */
	sf::Text rtext3;
	/** @brief SFML Text 
    *	 	   	Text containing first player name which is displayed on window.
    */
	sf::Text player1NameText;
	/** @brief SFML Text 
    *	 	   	Text containing second player name which is displayed on window.
    */
	sf:: Text player2NameText;
	/** @brief SFML Text 
    *	 	   	Text containing number of rounds won by second player which is displayed on window.
    */ 
	sf:: Text player1RoundsText;
	/** @brief SFML Text 
    *	 	   	Text containing number of rounds won by second player which is displayed on window.
    */
	sf:: Text player2RoundsText;
	/** @brief SFML Font 
    *	 	   	Contains the font which is to be loaded to text to display it on window.
    */
	sf::Font font;
private:
	/** @brief Contains StateMachine of Game, Render Window, over which game is displayed, AssetManager of game, InputManager of Game.
    */
	GameDataRef _data;
};
}

#endif
