#ifndef bot_h
#define bot_h
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


namespace stickman{


class botSom
{
	public:
		Player* player;
		int num;
		botSom(int n)
		{
			num=n;
			player=new Player [num];
			for (int j = 0; j < num; ++j)
			{
				player[j].init(false);
			}
		}


};

}



#endif