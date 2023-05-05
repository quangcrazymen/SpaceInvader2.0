#pragma once
#include "SDL/SDL.h"
#include <glew/glew.h>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include "Utils/Shader.h"
#include "Utils/VertexArray.h"
#include "Utils/Texture.h"

struct Bullet {
	Bullet() : 
		mPosition(glm::vec2(100.0f,100.0f))
		,mRotation(0.0f)
	{}
	float mSpeed = 0;
	glm::vec2 mPosition;
	float mRotation;
	bool mActive;
};
struct Invader {
	float mSpeed = 0;
	glm::vec2 mPosition;
	glm::vec2 mRotation;
};
class Game
{
public:
	// https://stackoverflow.com/questions/29424877/couple-of-questions-about-sdl-window-and-unique-ptr
	Game():mWindow(nullptr),mContext(nullptr),mVertexArray(nullptr){
		std::cout << "Game constructed" << std::endl;
	}
	bool Initialize();
	void ProcessInput(Uint32 deltaMilliseconds);
	void UpdateGame(Uint32 deltatime);
	void GenerateOutput();
	void RunLoop();
	~Game() {
		std::cout << "Game destructed" << std::endl;
		SDL_DestroyWindow(mWindow);
		delete mVertexArray;
	}
	Uint32 mTicksCount=0;
	SDL_Window* mWindow;
	SDL_GLContext mContext;

	bool mIsRunning = true;
	float mSpeed = 0;
	float mHorizontal = 0;
	float mVertical = 0;

	Shader mShader;
	VertexArray *mVertexArray;
	std::unordered_map<std::string,Texture> mTexture;
	std::vector<Bullet> mBullets;
	std::vector<Invader> mInvaders;
};

