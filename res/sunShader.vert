#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 normals;

out vec2 texCoord0;

uniform mat4 modelTransform;
uniform mat4 cameraProjection;
uniform mat4 cameraView;

void main()
{
	//All similar to the base shader, simply excluding all calculations and variables related to fog or lighting effects.

	vec4 positionRelativeToCam = cameraView * modelTransform * vec4(position, 1.0);
	gl_Position =  cameraProjection * positionRelativeToCam;

	texCoord0 = texCoord;
}