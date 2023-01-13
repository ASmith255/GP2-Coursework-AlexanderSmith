#pragma once
#include <string>
#include <GL\glew.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "Transform.h"
#include "Camera.h"

class Shader
{
public:
	Shader();
	~Shader();

	void initialiseShader(const std::string& filePath);		//Loads a vertex and fragment shader using the given file path and makes sure data is passed to them properly.
	void bind();		//Set this shader as the active shader in the GPU.
	void update(const Transform& transform, const Camera& camera);		//Passes updated data of the camera and model position to the shaders.

	void setFloatUniform(const std::string& uniform, float newValue);		//Sets the value of a specified uniform with the float data type.
	void setVec3Uniform(const std::string& uniform, glm::vec3 newValue);		//Sets the value of a specified uniform with the vec3 data type.

private:
	std::string loadShader(const std::string& fileName);		//Reads a shader from file.
	void checkShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);		//Checks for errors, prints error message if an issue is found.
	GLuint createShader(const std::string& text, unsigned int type);		//Creates a shader of a given type (e.g. vertex or fragment) using data from loadShader().

	static const unsigned int NUM_SHADERS = 2;		//Number of shaders. 2 in this case as we're only using a vertex and fragment shader.

	enum {		//The uniforms required for the update() function.
		MODELTRANSFORM_UNI,
		CAMERAPROJECTION_UNI,
		CAMERAVIEW_UNI,
		NUM_UNIFORMS
	};

	GLuint shaderProgram;		//ID of the OpenGL shader program.
	GLuint shaders[NUM_SHADERS];		//ID of the shaders,
	GLuint uniforms[NUM_UNIFORMS];		//The uniforms in update(), uses the enums.
};