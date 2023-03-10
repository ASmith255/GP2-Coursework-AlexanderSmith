#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

struct Transform
{
public:
	//Initialises variables based on parameters passed in.
	Transform(const glm::vec3& pos = glm::vec3(), const glm::vec3& rot = glm::vec3(), const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f))
	{
		this->pos = pos;
		this->rot = rot;
		this->scale = scale;
	}

	//Returns model Transform matrix.
	inline glm::mat4 getModel() const
	{
		glm::mat4 posMat = glm::translate(pos);

		glm::mat4 scaleMat = glm::scale(scale);

		glm::mat4 rotX = glm::rotate(rot.x, glm::vec3(1.0, 0.0, 0.0));
		glm::mat4 rotY = glm::rotate(rot.y, glm::vec3(0.0, 1.0, 0.0));
		glm::mat4 rotZ = glm::rotate(rot.z, glm::vec3(0.0, 0.0, 1.0));
		glm::mat4 rotMat = rotX * rotY * rotZ;

		return posMat * rotMat * scaleMat;
	}

	//Variable Getters. Returns pointers to the variables.
	inline glm::vec3* getPos() { return &pos; }
	inline glm::vec3* getRot() { return &rot; }
	inline glm::vec3* getScale() { return &scale; }

	//Variable Setters.
	inline void setPos(glm::vec3& pos) { this->pos = pos; }
	inline void setRot(glm::vec3& rot) { this->rot = rot; }
	inline void setScale(glm::vec3& scale) { this->scale = scale; }

private:
	glm::vec3 pos;
	glm::vec3 rot;
	glm::vec3 scale;
};