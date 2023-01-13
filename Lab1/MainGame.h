#pragma once
#include <SDL\SDL.h>
#include <GL/glew.h>
#include <iostream>
#include "Display.h"
#include "Camera.h"
#include "Shader.h"
#include "GameObject.h"
#include "AudioManager.h"

enum class GameState { PLAY, EXIT };

class MainGame
{
public:
	MainGame();
	~MainGame();

	void startGame();		//Starts the game off.

private:
	void initialise();		//Initialises objects and calls  load functions.
	void loadShaders();		//Initialises the game's shaders.
	void loadAudio();		//Initialises the game's audio track and clips.
	void spawnObjects();		//Initialises the game objects.
	void playBackgroundMusic();
	void printControls();		//Prints a guide to the game's controls to the console.
	void gameLoop();		//Keeps the game running while the GameState is Play.
	void processInput();		//Tracks user input.
	void collisionChecking();		//Checks whether the player is colliding with other objects in the scene.
	void bouncePlayer(Transform* otherObject);		//Moves the player away from an object it collides with. Pointer to the object's transform is passed in.
	void popMonkey();		//'Pops' the monkey when the player collides with it.
	void playerMovement();		//Moves the player according to input from processInput().
	void cameraMovement();		//Moves the camera to follow the player.
	void drawGame();		//Clears the display, passes data to shaders and draws game objects.
	void sunOrbit();		//Moves the sun around the map.
	void drawSun();		//Draws the sun mesh.
	void drawGround();		//Draws the ground mesh.
	void drawPlayer();		//Draws the player mesh.
	void drawMonkey();		//Draws the monkey mesh.

	GameState gameState;		//If 'PLAY', game keeps running. Else it stops.

	Display gameDisplay;
	Camera playerCamera;
	
	AudioManager gameAudio;

	Shader defaultShader;		//Shader applied to most objects in the scene. Simulates fog and basic lighting.
	Shader sunShader;		//Shader applied to the sun object. Ignores fog and light, all fragments are the same colour.

	GameObject sun;		//Light source in the scene. Orbits the scene at a speed defined by timerSpeed.
	GameObject ground;
	GameObject player;		//Controllable through the processInput() and playerMovement() functions.
	GameObject monkeyHead;
	bool monkeyPopped = false;		//Monkey head is only drawn in the scene while this = false.

	//Bools tracking which direction the player is wanting to move in.
	bool playerMovingForward;
	bool playerMovingBack;
	bool playerMovingLeft;
	bool playerMovingRight;
	bool playerMovingUp;
	bool playerMovingDown;

	float timer;		//Starts at 0, timerSpeed added to it every frame in drawScene();
	float timerSpeed;		//Value added to timer every frame.
};