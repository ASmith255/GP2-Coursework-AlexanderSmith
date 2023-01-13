#pragma once
#include "Transform.h"
#include "Mesh.h"
#include "Texture.h"

class GameObject
{
public:
	Transform transform;		//The transform (position, rotation, scale) of the game object.
	Mesh mesh;		//The mesh of the game object.
	Texture texture;		//The texture applied to the mesh of the game object.

	GameObject();
	~GameObject();

	//Initialises the game object with a specified transform, mesh and texture, as well as the radius of its collider.
	void spawn(glm::vec3 startPosition, glm::vec3 startRotation, glm::vec3 startScale, const std::string& modelFileName, const std::string& textureFileName, float colliderRadius);
	void moveObject(glm::vec3 newPosition);		//Sets the position of the game object to the new value passed into the function.
	bool checkCollisions(GameObject* otherObject);		//Checks whether the object is colliding with another specified game object (to which a pointer is passed in).

	float colliderRadius;		//Radius where an object is considered to collide with this object.
};