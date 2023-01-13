#pragma once
#include <glm\glm.hpp>
#include <GL\glew.h>
#include <vector>
#include <string>
#include "obj_loader.h"
#include "Vertex.h"

class Mesh
{
public:
	Mesh();
	~Mesh();

	void draw();		//Draws the mesh to the screen.
	void loadModel(const std::string& filePath);		//Loads a .obj model from a given file path.
	void initialise(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices);	//Initialises a model from a set of vertices and indices.

private:
	void initModel(const IndexedModel& model);		//Generates and fills vertex arrays and buffers for the mesh data.

	enum          //The different vertex buffers in the correct order. Enum helps scalability and readability of code.
	{
		POSITION_VERTEXBUFFER,
		TEXCOORD_VERTEXBUFFER,
		NORMAL_VERTEXBUFFER,
		INDEX_VERTEXBUFFER,
		NUM_BUFFERS
	};

	GLuint vertexArrayObject;		//ID of the vertex array object.
	GLuint vertexArrayBuffers[NUM_BUFFERS];		//ID of the vertex buffer object.
	unsigned int drawCount;
};