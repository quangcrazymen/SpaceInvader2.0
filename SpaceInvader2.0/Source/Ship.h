#pragma once
#include "Actor.h"
#include "SDL3/SDL.h"
class Ship :
    public Actor
{
public:
    Ship(){
        mPosition = glm::vec2(0.0f, 0.0f);
        mSize = glm::vec2(100.f, 100.f);
        mRotation = 0;
        mActive = true;
        mSpeed = 200.f;
    }
    //~Ship() {}

    short lives = 3;
    Uint32 invincibleTime = 0;
};

