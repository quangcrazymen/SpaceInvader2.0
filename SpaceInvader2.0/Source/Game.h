#pragma once
#include <glew/glew.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_ttf.h>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include "Utils/Shader.h"
#include "Utils/VertexArray.h"
#include "Utils/Texture.h"
#include <glm/gtc/random.hpp>
#include "Ship.h"
#include "Bullet.h"
#include "Invader.h"

class Game
{
public:
	// https://stackoverflow.com/questions/29424877/couple-of-questions-about-sdl-window-and-unique-ptr
	Game():mWindow(nullptr),mContext(nullptr),mVertexArray(nullptr){
		std::cout << "Game constructed" << std::endl;
	}
	bool Initialize();
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	void RunLoop();
	~Game() {
		std::cout << "Game destructed" << std::endl;
		SDL_DestroyWindow(mWindow);
		delete mVertexArray;
		TTF_CloseFont(mFont);
	}
	Uint64 mTicksCount=0;
	SDL_Window* mWindow;
	SDL_GLContext mContext;
	Uint64 mDeltaMilliseconds = 0;

	bool mIsRunning = true;

	Shader mShader;
	Shader mShipShader;
	Shader mBoxShader;
	VertexArray *mVertexArray;
	std::unordered_map<std::string,Texture> mTexture;
	std::vector<Bullet> mBullets;

	// Bullet
	short mBulletIndex = 0;
	Uint64 mTimeSinceLastShot = 0;
	Uint64 mTimeBetweenShots = 3000;
	short mCurrentGunLevel = 2;
	
	// Player
	//Player mPlayer;
	Ship mShip;

	// Invaders
	std::vector<Invader> mInvaders;

	// Trajectory of invaders
	std::vector<glm::vec2> mFlyInPositions;
	int mPositionsIndex=0;
	
	float mTotalTimeToTravel = 0;
	// Items
	// @Todo: Add items into the game
	//std::vector<Item> mItems;

	// @Todo: make the UI
	//std::unordered_map<int, TTF_Font*> mFontData;
	TTF_Font* mFont;
	GLuint mFontTexture;
	GLfloat mFontTexCoord[4];
};

