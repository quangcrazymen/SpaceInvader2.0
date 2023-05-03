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

	return true;
}

void Game::RunLoop()
{
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

	VertexArray mSpriteVerts = VertexArray(vertices, 4, indices, 6);
	mSpriteVerts.Enable();
	Shader shader;
	shader.Load("Shaders/Shader.vert", "Shaders/Shader.frag");
	// Load Texture
	Texture texture;
	// How to use glActive texture? //////////////////////////////////////
	glActiveTexture(GL_TEXTURE0);
	texture.Load("Assets/graphics/a1.png");
	glBindTexture(GL_TEXTURE_2D, texture.mTextureID);
	//texture.Enable();
	glActiveTexture(GL_TEXTURE1);
	texture.Load("Assets/graphics/Bullet1.png");
	glBindTexture(GL_TEXTURE_2D, texture.mTextureID);
	glActiveTexture(GL_TEXTURE1);
	//texture.Enable();

	// camera (projection)
	glm::mat4 projection = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);
	shader.Enable();
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(200.0f, 200.0f,0.0f));
	model = glm::rotate(model, glm::radians(45.f), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, glm::vec3(100.0f, 100.0f,0.0f));

	shader.SetMatrix4("model", model);
	shader.SetMatrix4("projection", projection);
	while (mIsRunning)
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput(shader,mSpriteVerts);
	}
}

void Game::ProcessInput() {
	// Using event queue
	SDL_Event event;
	//SDL_Event user_event;
	//user_event.user.type = SDL_USEREVENT;
	//user_event.user.code = 2;
	//user_event.user.data1 = NULL;
	// check the documentation if it's already a event queue
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			mIsRunning = false;
			break;
		case SDL_KEYDOWN:
			if (event.key.keysym.sym==100) {
				std::cout << "Key is pressed" << event.key.keysym.sym << std::endl;
			}
			if (event.key.keysym.sym == 101) {
				std::cout << "Key is pressed" << event.key.keysym.sym << std::endl;
			}
			break;
		}
	}
}
void Game::UpdateGame() {
	// lock fps :)
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16))
		;
	Uint32 deltaTime = SDL_GetTicks() - mTicksCount;
	//std::cout << 1000/ deltaTime << '\n';
	mTicksCount = SDL_GetTicks();
}

void Game::GenerateOutput(Shader& shader,VertexArray& vert) {
	// Set the clear color to grey
	glClearColor(0.86f, 0.86f, 0.86f, 1.0f);
	// Clear the color buffer
	glClear(GL_COLOR_BUFFER_BIT);

	// Update something
	for (short i = 0; i < 2; ++i) {
		glm::mat4 model = glm::mat4(1.0);

	}


	// Draw all sprite components
	// Enable alpha blending on the color buffer
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//shader.Enable();
	//vert.Enable();
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(200.f, 300.f, 0.f));
	model = glm::scale(model, glm::vec3(30.f, 40.f, 0.f));
	shader.SetMatrix4("model", model);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(400.f, 300.f, 0.f));
	model = glm::scale(model, glm::vec3(30.f, 40.f, 0.f));
	shader.SetMatrix4("model", model);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	SDL_GL_SwapWindow(mWindow);
}
