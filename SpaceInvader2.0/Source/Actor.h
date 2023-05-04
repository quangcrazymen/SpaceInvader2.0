#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <memory>
#include "Components/RenderComponent.h"
#include "Components/InputComponent.h"
class Actor
{
public:
	// state
	enum State {
		eDead,
		eAlive
	};
	Actor(std::unique_ptr<std::vector<RenderComponent>> renderer) {
		mPosition = glm::vec2(200, 200);
		mScale = glm::vec2(100, 100);
		mRotation = 0;

	}
	~Actor() {

	}

	int mIndex = 0;
	glm::vec2 mPosition;
	glm::vec2 mScale;
	float mRotation;

};

