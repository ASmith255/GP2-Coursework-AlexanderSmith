#pragma once
#include <string>
#include <GL\glew.h>
#include "stb_image.h"
#include <cassert>
#include <iostream>

class Texture
{
public:
	Texture();
	~Texture();

	void initialise(const std::string& filePath);		//Loads a texture from a given file path and sets GL texture attributes.
	void bind(unsigned int unit);		//Binds the texture with the corresponding index as the active texture in OpenGL. Only 0 is used in this as textures are stored in separate objects.

private:
	GLuint textureID;
};