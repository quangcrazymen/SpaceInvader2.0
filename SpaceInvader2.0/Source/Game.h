#pragma once
#include "SDL/SDL.h"
#include <glew/glew.h>
#include <fstream>
#include <iostream>
#include <memory>
#include "Utils/Shader.h"
#include "Utils/VertexArray.h"

class Game
{
public:
	// https://stackoverflow.com/questions/29424877/couple-of-questions-about-sdl-window-and-unique-ptr
	Game():mWindow(nullptr),mContext(NULL){
		std::cout << "Game constructed" << std::endl;
	}
	bool Initialize();
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput(Shader &shad,VertexArray &vert);
	void RunLoop();
	~Game() {
		std::cout << "Game destructed" << std::endl;
		SDL_DestroyWindow(mWindow);
	}
	Uint32 mTicksCount=0;
	SDL_Window* mWindow;
	SDL_GLContext mContext;

	bool mIsRunning = true;

};

