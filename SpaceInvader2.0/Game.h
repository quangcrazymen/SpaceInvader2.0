#pragma once
#include "SDL.h"
#include <GL/glew.h>
#include <fstream>
#include <iostream>
#include <memory>

class Game
{
public:
	//bool Initialize();
	//void Update();
	//void Render();;;
	// https://stackoverflow.com/questions/29424877/couple-of-questions-about-sdl-window-and-unique-ptr
	Game():mWindow(nullptr){

	}
	bool Initialize();
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	void RunLoop();
	~Game() {
		std::cout << "Game destructed" << std::endl;
		SDL_DestroyWindow(mWindow);
	}
	Uint32 mTicksCount=0;
	SDL_Window* mWindow;
	SDL_GLContext mContext;

	bool mIsRunning = false;

};

