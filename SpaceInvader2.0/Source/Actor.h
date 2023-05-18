#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <memory>
//#include "Components/RenderComponent.h"
//#include "Components/InputComponent.h"
enum struct bulletOwner { oInvader, oPlayer };

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

class Actor
{
public:
	// state
	//enum State {
	//	eDead,
	//	eAlive
	//};
	Actor() :
		mPosition(glm::vec2(-1000.0f, -1000.0f)),
		mRotation(0.0f),
		mActive(false),
		mSize(glm::vec2(15.0f, 40.0f))
	{
	}
	~Actor() {

	}
	glm::vec2 mPosition;
	float mRotation;
	glm::vec2 mSize;
	Hitbox mHitbox;
	float mSpeed = 0;
	bool mActive;
};

