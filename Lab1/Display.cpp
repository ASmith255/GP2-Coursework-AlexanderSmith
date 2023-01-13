#include "Display.h"

Display::Display()
{
	window = nullptr;
	screenWidth = 1024.0f;		//Width and height of our game window.
	screenHeight = 768.0f;
}

Display::~Display()
{
	SDL_DestroyWindow(window);
	SDL_GL_DeleteContext(glContext);
	SDL_Quit();
}

void Display::initialiseDisplay()
{
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);		//Defining space in memory for colours.
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);		//Enabling double buffers.

	//Creating the window, OpenGL Context and initialising GLEW.
	window = SDL_CreateWindow("AlexanderSmith GP2 Coursework", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, (int)screenWidth, (int)screenHeight, SDL_WINDOW_OPENGL);
	glContext = SDL_GL_CreateContext(window);
	GLenum error = glewInit();

	//Checking for errors in any of the above initialisations.
	if (window == nullptr)
	{
		returnError("There was a problem creating the window.");
	}
	if (glContext == nullptr)
	{
		returnError("There was a problem creating the GL Context.");
	}
	if (error != GLEW_OK)
	{
		returnError("There was a problem initialising GLEW.");
	}

	glEnable(GL_DEPTH_TEST);		//Enables Z-Buffering.
	glEnable(GL_CULL_FACE);		//Enables culling faces that aren't pointing at camera.
}

void Display::swapBuffer()
{
	SDL_GL_SwapWindow(window);
}

void Display::clearDisplay(float redValue, float greenValue, float blueValue, float alpha)
{
	glClearColor(redValue, greenValue, blueValue, alpha);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		//Clear colour and depth buffer - set colour to colour defined in glClearColor
}

void Display::returnError(std::string errorString)
{
	cout << errorString << endl;
	cout << "press any key to quit...";

	char userInput;
	cin >> userInput;		//Wait for user to input a key
	SDL_Quit();		//Quit game after the key has been input
}