// SpaceInvader2.0.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <glew/glew.h>
#include <SDL3/SDL.h>
#include <glm/matrix.hpp>
#include "Game.h"

int main(int agrc, char* argv[])
{
    Game game;
    if (game.Initialize()) {
        game.RunLoop();
    }
    return 0;
}

