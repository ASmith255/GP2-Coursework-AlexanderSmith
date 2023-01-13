#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 normals;

out vec2 texCoord0;
out vec3 normal;
out vec3 fragPos;

uniform mat4 modelTransform;
uniform mat4 cameraProjection;
uniform mat4 cameraView;

//Variables used for fog calculation.
out float visibility;		//The visibility of each vertex through the fog.
const float fogMinDistance = 30;		//The minimum distance beyond which fog will affect objects.
const float fogMaxDistance = 80;		//The maximum distance beyond which objects aren't visible.

void main()
{
	vec4 positionRelativeToCam = cameraView * modelTransform * vec4(position, 1.0);
	float distanceFromCam = length(positionRelativeToCam.xyz);

	//Calculating fog visibility and clamping between 0 and 1.
	visibility = 1 - ((distanceFromCam - fogMinDistance) / (fogMaxDistance - fogMinDistance));		//At max distance, visibility = 0. At min, visibility = 1.
	if (visibility > 1.0)
	{
		visibility = 1.0;
	}
	else if (visibility < 0.0)
	{
		visibility = 0.0;
	}

	gl_Position =  cameraProjection * positionRelativeToCam;
	texCoord0 = texCoord;
	normal = mat3(transpose(inverse(modelTransform))) * normals;
	fragPos = vec3(modelTransform * vec4(position, 1.0));
}