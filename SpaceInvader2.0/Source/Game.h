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
struct Hitbox {
	// https://www.amanotes.com/post/using-swept-aabb-to-detect-and-process-collision
	glm::vec2 mPosition;
	glm::vec2 mSize;
	bool isColliding(const Hitbox& other) {
		// because coordiate of object is located at the center of the obj
		float left = (other.mPosition.x - other.mSize.x / 2) - (mPosition.x + mSize.x / 2);
		float top = (other.mPosition.y + other.mSize.y / 2) - (mPosition.y - mSize.y / 2);
		float right = (other.mPosition.x + mSize.x / 2) - (mPosition.x - mSize.x / 2);
		float bottom = (other.mPosition.y - other.mSize.y / 2) - (mPosition.y + mSize.y / 2);

		return !(left > 0 || right < 0 || top < 0 || bottom>0);
	}
};
struct Bullet {
	Bullet() :
		mPosition(glm::vec2(-1000.0f, -1000.0f))
		, mRotation(0.0f),
		mActive(false),
		mSize(glm::vec2(15.0f, 40.0f))
	{}
	Hitbox mHitbox;
	float mSpeed = 0;
	glm::vec2 mPosition;
	float mRotation;
	bool mActive;
	glm::vec2 mSize;
};
struct Invader {
	Invader()
		:mSize(glm::vec2(30.f, 40.f))
		, mPosition(glm::vec2(200.f, 200.f))
		, mRotation(0.0f)
	{}
	Invader(glm::vec2 pos) {
		mPosition = pos;
		mSize = glm::vec2(30.f, 40.f);
	}
	float mSpeed = 0;
	glm::vec2 mPosition;
	float mRotation;
	bool isAlive = true;
	glm::vec2 mSize;
	Hitbox mHitbox;
};

struct Player {
	Player() :mPosition(glm::vec2(0.0f, 0.0f)){}
	Player(glm::vec2 pos):mPosition(pos){}
	float mSpeed = 0;
	glm::vec2 mPosition;
	bool isAlive = true;
	glm::vec2 mSize = glm::vec2(100.f,100.f);
	Hitbox mHitbox;
	short lives = 3;
	Uint32 invincibleTime = 0;
};

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
	}
	Uint32 mTicksCount=0;
	SDL_Window* mWindow;
	SDL_GLContext mContext;
	Uint32 mDeltaMilliseconds = 0;

	bool mIsRunning = true;
	float mSpeed = 0;
	float mHorizontal = 0;
	float mVertical = 0;

	Shader mShader;
	Shader mShipShader;
	VertexArray *mVertexArray;
	std::unordered_map<std::string,Texture> mTexture;
	std::vector<Bullet> mBullets;

	// Bullet
	short mBulletIndex = 0;
	Uint32 mTimeSinceLastShot = 0;
	Uint32 mTimeBetweenShots = 3000;
	
	// Player
	Player mPlayer;

	// Invaders
	Invader mInvader;
	std::vector<Invader> mInvaders;
};

