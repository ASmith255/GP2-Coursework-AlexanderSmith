#pragma once
#include <SDL/SDL.h>
#include <GL\glew.h>
#include <iostream>
using namespace std;

class Display
{
public:
	Display();
	~Display();

	void initialiseDisplay();		//initialises the game window and OpenGL Context, and sets important attributes.
	void swapBuffer();		//Updates the window.
	void clearDisplay(float redValue, float greenValue, float blueValue, float alpha);		//Clears the display, filling the 'empty space' with colour (depends on values passed in).

	float getWidth() { return screenWidth;}		//Returns screenWidth value.
	float getHeight() { return screenHeight; }		//Returns screenHeight value.

private:
	void returnError(std::string errorString);		//Prints error message to the screen and quits program in case of errors in the initialiseDisplay() function.

	SDL_Window* window;		//Pointer to the game window.
	SDL_GLContext glContext;		//The OpenGL Context.
	float screenWidth;
	float screenHeight;
};