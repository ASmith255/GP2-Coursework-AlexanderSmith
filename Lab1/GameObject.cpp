#include "GameObject.h"

GameObject::GameObject()
{
	//Default variable values.
	transform.setPos(glm::vec3(0, 0, 0));
	transform.setRot(glm::vec3(0, 0, 0));
	transform.setScale(glm::vec3(1, 1, 1));

	texture.initialise("..\\res\\placeholderTexture.jpg");

	colliderRadius = 0;
}

void GameObject::spawn(glm::vec3 startPosition, glm::vec3 startRotation, glm::vec3 startScale, const std::string& modelFileName, const std::string& textureFileName, float colliderRadius)
{
	//Set variables to match the values passed in to the function.
	transform.setPos(startPosition);
	transform.setRot(startRotation);
	transform.setScale(startScale);

	mesh.loadModel(modelFileName);

	texture.initialise(textureFileName);

	this->colliderRadius = colliderRadius;
}

GameObject::~GameObject()
{
}

void GameObject::moveObject(glm::vec3 newPosition)
{
	transform.setPos(newPosition);		//Moving the object's position to the new value passed in to the function.
}

bool GameObject::checkCollisions(GameObject* otherObject)		//Checks if the object is colliding with a specified object.
{
	bool colliding = false;
	float objectDistance = 0;

	if (otherObject->colliderRadius != 0)		//If the other object has a valid collider,
	{
		//Find the distance between the objects in all axes.
		float xDistance = (otherObject->transform.getPos()->x - transform.getPos()->x) * (otherObject->transform.getPos()->x - transform.getPos()->x);
		float yDistance = (otherObject->transform.getPos()->y - transform.getPos()->y) * (otherObject->transform.getPos()->y - transform.getPos()->y);
		float zDistance = (otherObject->transform.getPos()->z - transform.getPos()->z) * (otherObject->transform.getPos()->z - transform.getPos()->z);

		//Find the overall distance.
		objectDistance = xDistance + yDistance + zDistance;

		//If this distance is less than both objects' combined collider radius (i.e. if their colliders are intersecting), colliding = true.
		colliding = (objectDistance < (colliderRadius + otherObject->colliderRadius));
	}
	
	return colliding;
}