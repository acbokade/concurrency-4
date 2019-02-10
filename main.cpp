#include "SFML/Graphics.hpp"
#include "Box2D/Box2D.h"
#include "player.h"
#include "game.h"
#include <bits/stdc++.h>
using namespace std;
#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f

const float SCALE = 30.f;

int main()
{   
    Game gameState;
    //creating ground
    gameState.ground = gameState.createGround(b2Vec2(400.f/SCALE, 550.f/SCALE));
    gameState.gameLoop();
    return 0;
}
