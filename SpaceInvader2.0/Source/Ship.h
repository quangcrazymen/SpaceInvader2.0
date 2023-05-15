#pragma once
#include "Actor.h"
#include "SDL3/SDL.h"
class Ship :
    public Actor
{
public:
    Ship(std::unique_ptr<std::vector<RenderComponent>> renderer) :Actor(std:: move(renderer)) {
        mIndex = 0;
        mPosition = glm::vec2(200, 200);
        mScale = glm::vec2(100, 100);
        mRotation = 0;
    }
    //~Ship() {

    //}
    void ActorInput(const Uint8* keyState) {
        float forwardSpeed = 0.0f;
        if (keyState[SDL_SCANCODE_W]) {
            mPosition.y += 10;
        }
        if (keyState[SDL_SCANCODE_S]) {
            mPosition.x -= 10;
        }
    }

    //std::unique_ptr<std::vector<RenderComponent>> renderer;
};

