#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Game.h"
#include "Utils/Shader.h"
#include "Utils/VertexArray.h"
#include "Utils/Texture.h"
bool Game::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	// Set OpenGL attributes
	// Use the core OpenGL profile
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	// Specify version 3.3
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	// Request a color buffer with 8-bits per RGBA channel
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	// Enable double buffering
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	// Force OpenGL to use hardware acceleration
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

	mWindow = SDL_CreateWindow("Game Programming in C++ (Chapter 5)", 100, 100,
		1024, 768, SDL_WINDOW_OPENGL);
	if (!mWindow)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}

	// Create an OpenGL context
	mContext = SDL_GL_CreateContext(mWindow);

	// Initialize GLEW
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		SDL_Log("Failed to initialize GLEW.");
		return false;
	}

	// On some platforms, GLEW will emit a benign error code,
	// so clear it
	glGetError();

	// Make sure we can create/compile shaders
	//if (!LoadShaders())
	//{
	//	SDL_Log("Failed to load shaders.");
	//	return false;
	//}

	// Create quad for drawing sprites

	mTicksCount = SDL_GetTicks();

	float vertices[] = {
	-0.5f,  0.5f, 0.f, 0.f, 0.f, // top left
	 0.5f,  0.5f, 0.f, 1.f, 0.f, // top right
	 0.5f, -0.5f, 0.f, 1.f, 1.f, // bottom right
	-0.5f, -0.5f, 0.f, 0.f, 1.f  // bottom left
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};
	mVertexArray = new VertexArray(vertices, 4, indices, 6);
	mShader.Load("Shaders/Shader.vert", "Shaders/Shader.frag");
	mTexture["Player"].Load("Assets/graphics/player.png");
	mTexture["Invader"].Load("Assets/graphics/a1.png");
	mTexture["Bullet"].Load("Assets/graphics/bulletRemake.png");
	mSpeed = 400.0f;

	mBullets.reserve(1000);
	mBullets = std::vector<Bullet>(10, Bullet());
	//for (auto& i : mBullets) {
	//	i = Bullet();
	//}
	mTimeBetweenShots = 500;

	// Player
	return true;
}

void Game::RunLoop()
{
	mVertexArray->Enable();
	// Load Texture
	Texture texture;
	// How to use glActive texture? //////////////////////////////////////
	//glActiveTexture(GL_TEXTURE0);
	//texture.Load("Assets/graphics/player.png");
	//glBindTexture(GL_TEXTURE_2D, texture.mTextureID);
	//Texture texture2;
	//texture2.Load("Assets/graphics/a1.png");
	//glBindTexture(GL_TEXTURE_2D, texture2.mTextureID);
	
	// projection
	//glm::mat4 projection = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);
	//for (int i = 0; i < 4; ++i) {
	//	for (int j = 0; j < 4; ++j) {
	//		std::cout << projection[i][j] << ' ';
	//	}
	//	std::cout << '\n';
	//}
	mShader.Enable();
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(200.0f, 200.0f,0.0f));
	model = glm::rotate(model, glm::radians(45.f), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, glm::vec3(100.0f, 100.0f,0.0f));

	// This is projection
	glm::mat4 projection = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);
	mShader.SetMatrix4("projection", projection);
	// view matrix (camera)
	// try to use lookAt
	glm::vec3 cameraPos = glm::vec3(0.f, 0.f, -0.5f);
	glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);
	// right axis
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
	//up axis
	glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);
	// view matrix (camera)
	glm::mat4 view;
	//view = glm::mat4(1.0f);
	//view = glm::translate(view, glm::vec3(800.f/2, 400.0f/2, -0.10f));
	//view = glm::translate(view, glm::vec3(-800.f/2, -400.0f/2, -0.10f));
	// change coordinate system with the player ship being the origin/////////////////////////
	view = glm::lookAt(cameraPos, cameraTarget, cameraUp);
	view = glm::translate(view, glm::vec3(-400.f, 300.0f, 0.0f));
	view = glm::rotate(view, glm::radians(-180.0f), glm::vec3(0.f, 0.f, 1.f));
	mShader.SetMatrix4("view", view);
	mShader.SetMatrix4("model", model);
	mShader.SetMatrix4("projection", projection);
	while (mIsRunning)
	{
		Uint32 deltaTime = SDL_GetTicks() - mTicksCount;
		//std::cout << 1000/ deltaTime << '\n';
		mTicksCount = SDL_GetTicks();
		ProcessInput(deltaTime);
		UpdateGame(deltaTime);
		GenerateOutput();
	}
}

void Game::ProcessInput(Uint32 deltaMilliseconds) {
	// Using event queue
	SDL_Event event;
	// check the documentation if it's already a event queue
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			mIsRunning = false;
			break;
		}
	}
	const Uint8* keyState = SDL_GetKeyboardState(nullptr);
	if (keyState[SDL_SCANCODE_ESCAPE]) {
		mIsRunning = false;
	}
	if (keyState[SDL_SCANCODE_W]) {
		mPlayer.mPosition.y += mSpeed * deltaMilliseconds / (float)1000.0;
	}

	if (keyState[SDL_SCANCODE_S]) {
		mPlayer.mPosition.y -= mSpeed * deltaMilliseconds / (float)1000.0;
	}

	if (keyState[SDL_SCANCODE_D]) {
		mPlayer.mPosition.x += mSpeed * deltaMilliseconds / (float)1000.0;
	}

	if (keyState[SDL_SCANCODE_A]) {
		mPlayer.mPosition.x -= mSpeed * deltaMilliseconds / (float)1000.0;
	}
	mTimeSinceLastShot += deltaMilliseconds;

	if (keyState[SDL_SCANCODE_SPACE]) {
		//mBullets[0].mPosition.y += mSpeed * deltaMilliseconds / (float)1000.0;
		if (mBulletIndex == mBullets.size()) mBulletIndex = 0;
		if (mTimeSinceLastShot >= mTimeBetweenShots) {
			mBullets[mBulletIndex].mPosition = mPlayer.mPosition;
			mBullets[mBulletIndex].mActive = true;
			mBulletIndex++;
			mTimeSinceLastShot = 0;
		}
	}
}
void Game::UpdateGame(Uint32 deltaTime) {
	// lock fps :)
	//while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16))
	//	;
	if (mTimeSinceLastShot < mTimeBetweenShots) {

	}
	for (auto& bullet : mBullets) {
		if (bullet.mActive){
			bullet.mPosition.y += mSpeed * deltaTime/(float)1000.0;
		}
		if (bullet.mPosition.y > 300) {
			bullet.mPosition.y = -1000;
			bullet.mPosition.x = -1000;
			bullet.mActive = false;
		}
	}
	mTimeSinceLastShot += deltaTime;


}

void Game::GenerateOutput() {
	// Set the clear color to grey
	glClearColor(0.86f, 0.86f, 0.86f, 1.0f);
	// Clear the color buffer
	glClear(GL_COLOR_BUFFER_BIT);

	// Draw all sprite components
	// Enable alpha blending on the color buffer
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// This is the ship
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3( mPlayer.mPosition.x ,mPlayer.mPosition.y, 0.f));
	//model = glm::rotate(model, glm::radians(20.f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(100.f, 100.f, 0.f));
	mShader.SetMatrix4("model", model);
	mTexture["Player"].Enable();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


	// This is a enemy
	
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.f, 200.f, 0.f));
	model = glm::scale(model, glm::vec3(30.f, 40.f, 0.f));
	mShader.SetMatrix4("model", model);
	mTexture["Invader"].Enable();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	// This is bullets
	for (auto& bullet :mBullets) {
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(bullet.mPosition, 0.0f));
		model = glm::scale(model, glm::vec3(15.f, 40.0f, 0.0f));
		mShader.SetMatrix4("model", model);
		mTexture["Bullet"].Enable();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
	SDL_GL_SwapWindow(mWindow);
}
