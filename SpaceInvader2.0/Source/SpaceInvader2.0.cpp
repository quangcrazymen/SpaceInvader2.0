// SpaceInvader2.0.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <glew/glew.h>
#include <SDL/SDL.h>
#include <glm/matrix.hpp>
#include "Game.h"

int main(int agrc, char* argv[])
{
    Game game;
    if (game.Initialize()) {
        game.RunLoop();
    }

    // 
    //for (float t = 0; t <= 1; t += 0.05f) {
    //    glm::vec2 result = de_castejau(t, testVec2s);
    //    std::cout << result.x << ' ' << result.y << std::endl;
    //}
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
