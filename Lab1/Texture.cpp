#include "Texture.h"

Texture::Texture()
{
}

void Texture::initialise(const std::string& filePath)
{
	int height;
	int width;
	int numberComponents;

	//Load image from file, passing the addresses of the image attributes.
	unsigned char* imageData = stbi_load((filePath).c_str(), &width, &height, &numberComponents, 4);
	if (imageData == NULL)
	{
		std::cerr << "Texture load failed " << filePath << std::endl;
	}

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	//Setting parameters to control texture wrapping & linear filtering.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);		//Wrap texture outside width.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);		//Wrap texture outside height.
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);		//Linear filtering for minification (texture smaller than area).
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);		//Linear filtering for magnification (texture larger than area).

	//Sending the texture to the GPU.
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

	stbi_image_free(imageData);		//Deleting the data from the CPU
}

Texture::~Texture()
{
	//Deleting our textures
	glDeleteTextures(1, &textureID);		//Number of textures, Address of textures
}

void Texture::bind(unsigned int unit)
{
	assert(unit >= 0 && unit <= 31);		//Check we are working with one of the 32 textures

	glActiveTexture(GL_TEXTURE0 + unit);		//Set active texture unit to the texture with the specified index.
	glBindTexture(GL_TEXTURE_2D, textureID);		//Bind texture.
}