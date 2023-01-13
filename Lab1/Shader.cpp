#include "Shader.h"

Shader::Shader()
{
}

Shader::~Shader()
{
	for (unsigned int i = 0; i < NUM_SHADERS; i++)
	{
		glDetachShader(shaderProgram, shaders[i]);
		glDeleteShader(shaders[i]);		//Detach and delete shaders.
	}

	glDeleteProgram(shaderProgram);		//Delete the shader program.
}

void Shader::initialiseShader(const std::string& filePath)
{
	shaderProgram = glCreateProgram();		//Create the shader program.

	//Create vertex and fragment shaders from the given file path.
	shaders[0] = createShader(loadShader(filePath + ".vert"), GL_VERTEX_SHADER);
	shaders[1] = createShader(loadShader(filePath + ".frag"), GL_FRAGMENT_SHADER);

	//Attach the shaders to the shader program.
	for (unsigned int i = 0; i < NUM_SHADERS; i++)
	{
		glAttachShader(shaderProgram, shaders[i]);
	}

	//Setting location of attributes.
	glBindAttribLocation(shaderProgram, 0, "position");
	glBindAttribLocation(shaderProgram, 1, "texCoord");
	glBindAttribLocation(shaderProgram, 2, "normals");

	//Creating executables that will run on GPU shaders.
	glLinkProgram(shaderProgram);
	checkShaderError(shaderProgram, GL_LINK_STATUS, true, "Error: Shader program linking failed");

	//Checking that the program is valid.
	glValidateProgram(shaderProgram);
	checkShaderError(shaderProgram, GL_VALIDATE_STATUS, true, "Error: Shader progrsm not valid");

	//Storing locations of important uniforms..
	uniforms[MODELTRANSFORM_UNI] = glGetUniformLocation(shaderProgram, "modelTransform");
	uniforms[CAMERAPROJECTION_UNI] = glGetUniformLocation(shaderProgram, "cameraProjection");
	uniforms[CAMERAVIEW_UNI] = glGetUniformLocation(shaderProgram, "cameraView");
}

void Shader::bind()
{
	glUseProgram(shaderProgram);		//Set these shaders as the active ones in OpenGL.
}

void Shader::update(const Transform& transform, const Camera& camera)
{
	//Pass uniform data to the shaders.
	glUniformMatrix4fv(uniforms[MODELTRANSFORM_UNI], 1, GLU_FALSE, &transform.getModel()[0][0]);
	glUniformMatrix4fv(uniforms[CAMERAPROJECTION_UNI], 1, GLU_FALSE, &camera.getProjection()[0][0]);
	glUniformMatrix4fv(uniforms[CAMERAVIEW_UNI], 1, GLU_FALSE, &camera.getView()[0][0]);
}

std::string Shader::loadShader(const std::string& fileName)
{
	std::ifstream file;
	file.open((fileName).c_str());

	std::string output;
	std::string line;

	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, line);
			output.append(line + "\n");
		}
	}
	else
	{
		std::cerr << "Unable to load shader: " << fileName << std::endl;
	}
	return output;
}

void Shader::checkShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isProgram)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader, flag, &success);

	if (success == GL_FALSE)
	{
		if (isProgram)
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		else
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);

		std::cerr << errorMessage << ": '" << error << "'" << std::endl;
	}
}

GLuint Shader::createShader(const std::string& text, unsigned int type)
{
	GLuint shader = glCreateShader(type);		//Create shader based on specified type

	if (shader == 0)		//If no shader created,
	{
		std::cerr << "Error type creation failed " << type << std::endl;
	}

	const GLchar* stringSource[1];		//Convert strings into list of c-strings
	stringSource[0] = text.c_str();
	GLint lengths[1];
	lengths[0] = text.length();

	glShaderSource(shader, 1, stringSource, lengths);		//Send source code to OpenGL
	glCompileShader(shader);		//Get OpenGL to compile shader code

	checkShaderError(shader, GL_COMPILE_STATUS, false, "Error compiling shaders!");		//Check for compile error

	return shader;
}

void Shader::setFloatUniform(const std::string& uniform, float newValue)		//Change the value of a specified uniform with the float data type.
{
	glUniform1f(glGetUniformLocation(shaderProgram, uniform.c_str()), newValue);
}

void Shader::setVec3Uniform(const std::string& uniform, glm::vec3 newValue)		//Change the value of a specified uniform with the vec3 data type.
{
	glUniform3fv(glGetUniformLocation(shaderProgram, uniform.c_str()), 1, &newValue[0]);
}