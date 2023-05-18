#pragma once
#include "Actor.h"
#include <glm/gtc/random.hpp>

class Invader :
    public Actor
{
public:
	Invader(){
		mSize = glm::vec2(30.f, 40.f);
		mPosition = glm::vec2(200.f, 200.f);
		mSpeed = 120.f;
		mActive = true;
	}
	Invader(glm::vec2 pos) {
		Invader();
		mPosition = pos;
	}
	// Time to shoot
	int mTimeToShoot = glm::linearRand(1, 6);
	float mElapsedTime = 0.f;

};

