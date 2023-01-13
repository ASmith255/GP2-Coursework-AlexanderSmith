#include "Mesh.h"

Mesh::Mesh()
{
	drawCount = NULL;
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &vertexArrayObject);
	glDeleteBuffers(1, vertexArrayBuffers);
}

void Mesh::draw()
{
	glBindVertexArray(vertexArrayObject);		//Binding VAO.
	glDrawElements(GL_TRIANGLES, drawCount, GL_UNSIGNED_INT, 0);		//Drawing the mesh using the VAO.
	glBindVertexArray(0);		//Unbinding VAO.
}

void Mesh::initialise(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices)
{
	IndexedModel model;

	//Storing vertex data in the model.
	for (unsigned int i = 0; i < numVertices; i++)
	{
		model.positions.push_back(*vertices[i].getPos());
		model.texCoords.push_back(*vertices[i].getTexCoord());
		model.normals.push_back(*vertices[i].getNormal());
	}

	//Storing indices in the model.
	for (unsigned int i = 0; i < numIndices; i++)
	{
		model.indices.push_back(indices[i]);
	}

	initModel(model);
}

void Mesh::loadModel(const std::string& filePath)
{
	IndexedModel model = OBJModel(filePath).ToIndexedModel();		//Load a .obj file as an indexed model.
	initModel(model);
}

void Mesh::initModel(const IndexedModel& model)
{
	drawCount = model.indices.size();		//Number of vertices that need to be drawn.

	glGenVertexArrays(1, &vertexArrayObject);		//Generating a vertex array, storing in array object.
	glGenBuffers(NUM_BUFFERS, vertexArrayBuffers);		//Generating buffers based on our array of data.

	glBindVertexArray(vertexArrayObject);		//Binding to the array object so we can work with it.

	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[POSITION_VERTEXBUFFER]);		//Binding the buffer, specifying data type (in this case, array) and passing the data so we can work in specified position.
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.positions[0]), &model.positions[0], GL_STATIC_DRAW);		//Moving data to the GPU, specifying data type, size of data, starting address (pointer) and storing address.
	glEnableVertexAttribArray(0);		//Tell OpenGL how many attributes there are in our object
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);		//Telling OpenGL how to read the above data

	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[TEXCOORD_VERTEXBUFFER]); //tell opengl what type of data the buffer is(GL_ARRAY_BUFFER), and pass the data
	glBufferData(GL_ARRAY_BUFFER, model.texCoords.size() * sizeof(model.texCoords[0]), &model.texCoords[0], GL_STATIC_DRAW); //move the data to the GPU - type of data, size of data, starting address (pointer) of data, where do we store the data on the GPU
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[NORMAL_VERTEXBUFFER]);
	glBufferData(GL_ARRAY_BUFFER, model.normals.size() * sizeof(model.normals[0]) , &model.normals[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexArrayBuffers[INDEX_VERTEXBUFFER]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(model.indices[0]), &model.indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);		//Unbinding vertex array when we're done with it.
}