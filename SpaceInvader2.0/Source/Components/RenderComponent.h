#pragma once
#include <array>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../Utils/Shader.h"
#include "../Utils/VertexArray.h"
#include "../Utils/Texture.h"
class RenderComponent
{
public:
	RenderComponent(const glm::vec2 & position) :mPosition(position){
		std::cout << "Render constructed\n"; 
		mVertices = {
			-0.5f,  0.5f, 0.f, 0.f, 0.f, // top left
			 0.5f,  0.5f, 0.f, 1.f, 0.f, // top right
			 0.5f, -0.5f, 0.f, 1.f, 1.f, // bottom right
			-0.5f, -0.5f, 0.f, 0.f, 1.f  // bottom left
		};

		mIndices = {
			0, 1, 2,
			2, 3, 0
		};
		mSpriteVerts = new VertexArray(mVertices, 4, mIndices, 6);

		mShader.Load("Shaders/Shader.vert", "Shaders/Shader.frag");
		// Load Texture
		// How to use glActive texture? //////////////////////////////////////
		glActiveTexture(GL_TEXTURE0);
		mTexture.Load("Assets/graphics/a1.png");
		glBindTexture(GL_TEXTURE_2D, mTexture.mTextureID);
		mProjectionMatrix = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);

	}
	~RenderComponent() {
		std::cout << "Render destructed\n";
		delete mSpriteVerts;
	}


	void render() {
		mSpriteVerts->Enable();
		mShader.Enable();
		mTexture.Enable();

		glm::mat4 model = glm::mat4(1.0f);
		mShader.SetMatrix4("projection", mProjectionMatrix);
		mShader.SetMatrix4("model", model);
		model = glm::translate(model, glm::vec3(mPosition, 0.0f));
		model = glm::rotate(model, glm::radians(45.f), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(100.0f, 100.0f, 0.0f));
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(200.f, 300.f, 0.f));
		model = glm::scale(model, glm::vec3(30.f, 40.f, 0.f));
		mShader.SetMatrix4("model", model);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//model = glm::mat4(1.0f);
		//model = glm::translate(model, glm::vec3(400.f, 300.f, 0.f));
		//model = glm::scale(model, glm::vec3(30.f, 40.f, 0.f));
		//mShader.SetMatrix4("model", model);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
	//void update() {

	//}
	Shader mShader;
	Texture mTexture;
	std::array<float,20> mVertices;
	std::array<unsigned int, 6> mIndices;
	glm::mat4 mProjectionMatrix;
	VertexArray* mSpriteVerts; 

	//Position of objects
	glm::vec2 mPosition;
};

