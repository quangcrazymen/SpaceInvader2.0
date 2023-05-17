#pragma once
#include "Actor.h"
class Bullet :
    public Actor
{
    Bullet() {
        mPosition = glm::vec2(-1000.0f, -1000.0f);
        mRotation = 0.f;
        mActive = false;
        mSize = glm::vec2(15.0f, 40.0f);
        mSpeed = 300.f;
    }
    bulletOwner mBulletOwner;
};

