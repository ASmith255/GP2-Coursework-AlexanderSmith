#version 330 core

in vec2 texCoord0;
in vec3 normal;		//The normal of the fragment.
in vec3 fragPos;		//Position of the fragment, used for lighting calculations.
in float visibility;		//Visibility of the object through the fog. Calculated in vertex shader.

uniform sampler2D diffuse;
uniform vec3 sunPos;		//Position of the sun game object.
uniform vec3 cameraPos;		//Position of the camera.

void main()
{
	vec4 sunColour = vec4(1.0, 0.8, 0.4, 1.0);		//Set up sun colour vector, using RGBA values of the sun game object.

	gl_FragColor = texture2D(diffuse, texCoord0);		//Set up base fragment colour using the texture coordinates.


	//   LIGHTING
	//Ambient
	float ambientIntensity = 0.05;
	vec4 ambientLight = ambientIntensity * sunColour;

	//Diffuse
	vec3 norm = normalize(normal);
	vec3 lightDirection = normalize(sunPos - fragPos);		//Direction of the light hitting the fragment. Normalized to prevent distance from affecting light.
	float diffuseIntensity = max(dot(normal, lightDirection), 0.0);
	vec4 diffuseLight = diffuseIntensity * sunColour;

	//Specular
	float specularIntensity = 1;
	vec3 viewDirection = normalize(cameraPos - fragPos);		//Direction of the fragment from the camera. Normalized, as with lightDirection.
	vec3 reflectDirection = reflect(-lightDirection, normal);		//Direction that the light is reflecting from the fragment.
	float specular = pow(max(dot(viewDirection, reflectDirection), 0.0), 64);
	vec4 specularLight = specular * specularIntensity * sunColour;

	//Adding lighting effects to work together as a whole.
	gl_FragColor *= ambientLight + diffuseLight + specularLight;


	//   FOG
	//Linearly interpolating fragment colour between the texture (with lighting) and the fog/sky colour, using visibility as the interpolation level (at 0 it's textured, at 1 it's the fog).
	gl_FragColor = mix(vec4(0.4, 0.6, 0.6, 1.0), gl_FragColor, visibility);
}