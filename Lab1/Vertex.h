#pragma once
#include "obj_loader.h"

struct Vertex
{
public:
	Vertex(const glm::vec3& pos, const glm::vec2& texCoord, const glm::vec3& normal)
	{
		this->pos = pos;
		this->texCoord = texCoord;
		this->normal = normal;
	}

	//Variable Getters. Returns pointers to the variables.
	glm::vec3* getPos()
	{
		return &pos;
	};
	glm::vec2* getTexCoord()
	{
		return &texCoord;
	};
	glm::vec3* getNormal()
	{
		return &normal;
	}

private:
	glm::vec3 pos;
	glm::vec2 texCoord;
	glm::vec3 normal;
};