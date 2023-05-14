#include <iostream>
#include "Texture.h"
#include <SOIL/SOIL2.h>
#include <glew/glew.h>
#include <SDL/SDL.h>

Texture::Texture()
	:mTextureID(0)
	, mWidth(0)
	, mHeight(0)
{
	std::cout << "Texture constructed\n";
}

Texture::~Texture()
{
	glDeleteTextures(1, &mTextureID);
	std::cout << "Texture destructed\n";
}

auto Texture::Load(const std::string& fileName) -> bool // trailing return type
{
	int channels = 0;

	unsigned char* image = SOIL_load_image(fileName.c_str(),
		&mWidth, &mHeight, &channels, SOIL_LOAD_AUTO);

	if (!image)
	{
		SDL_Log("SOIL failed to load image %s: %s", fileName.c_str(), SOIL_last_result());
		return false;
	}

	int format = channels == 4 ? GL_RGBA : GL_RGB;

	glGenTextures(1, &mTextureID);
	glBindTexture(GL_TEXTURE_2D, mTextureID);

	glTexImage2D(GL_TEXTURE_2D, 0, format, mWidth, mHeight, 0, format,
		GL_UNSIGNED_BYTE, image);

	SOIL_free_image_data(image);

	// Enable bilinear filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	return true;
}

void Texture::Enable()
{
	glBindTexture(GL_TEXTURE_2D, mTextureID);
}

void Texture::Disable() {
	glBindTexture(GL_TEXTURE_2D,0);
}
