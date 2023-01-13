#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

struct Camera
{
public:
	Camera() 
	{
	}

	//Sets camera variables to equal the parameters given
	void initialiseCamera(const glm::vec3& position, float fov, float aspectRatio, float nearClip, float farClip)
	{
		this->position = position;
		this->up = glm::vec3(0.0f, 1.0f, 0.0f);
		this->forward = glm::vec3(0.0f, 0.0f, 1.0f);
		this->projection = glm::perspective(fov, aspectRatio, nearClip, farClip);
	};

	//Returns the camera's view matrix.
	inline glm::mat4 getView() const
	{
		return glm::lookAt(position, position + forward, up);
	}

	//Returns the camera's perspective projection matrix.
	inline glm::mat4 getProjection() const
	{
		return projection;
	}

	//Returns the pointer to the camera's position vector.
	inline glm::vec3* getPosition()
	{
		return &position;
	}

	//Sets camera position to the vector3 passed into the function.
	void moveCamera(glm::vec3 newPosition)
	{
		position = newPosition;
	}

private:
	glm::vec3 position;
	glm::vec3 up;
	glm::vec3 forward;
	glm::mat4 projection;
};