#include "MainGame.h"

MainGame::MainGame()
{
	gameState = GameState::PLAY;
	timer = 0;
	timerSpeed = 0.0003f;
}

MainGame::~MainGame()
{
}

void MainGame::startGame()
{
	initialise();		//Initialises important objects.
	gameLoop();		//Starts the game loop, input processing and drawing of the game.
}

void MainGame::initialise()
{
	//Initialising game display and camera.
	gameDisplay.initialiseDisplay();
	playerCamera.initialiseCamera(glm::vec3(0, 0, 0), 70.0f, (float)(gameDisplay.getWidth() / gameDisplay.getHeight()), 0.01f, 1000.0f);

	//Initialising shaders, audio and the game objects.
	loadShaders();
	loadAudio();
	spawnObjects();

	playBackgroundMusic();		//Starting the background music.
	printControls();		//Printing a formatted list of game controls to the console.
}

void MainGame::loadShaders()
{
	//Initialising the shader used by most objects in the game.
	defaultShader.initialiseShader("..\\res\\shader");

	//Initialising the shader used by the sun game object.
	sunShader.initialiseShader("..\\res\\sunShader");
}

void MainGame::loadAudio()
{
	gameAudio.addAudioTrack("..\\res\\ambient.mp3");		//Loading background music.

	gameAudio.addAudioClip("..\\res\\pop.mp3");		//Loading 'pop' sound effect.
}

void MainGame::spawnObjects()
{
	//SPAWNING SUN
	sun.spawn(glm::vec3(100, 0, 0), glm::vec3(0, 0, 0), glm::vec3(20, 20, 20), "..\\res\\player.obj", "..\\res\\placeholderTexture.jpg", 400);

	//SPAWNING GROUND
	ground.spawn(glm::vec3(0,0,20), glm::vec3(0,0,0), glm::vec3(1,1,1), "..\\res\\ground.obj", "..\\res\\ground.jpg", 1);

	//SPAWNING PLAYER
	player.spawn(glm::vec3(0,2,0), glm::vec3(0,0,0), glm::vec3(1,1,1), "..\\res\\player.obj", "..\\res\\player.jpg", 1);

	//SPAWNING MONKEY HEAD
	monkeyHead.spawn(glm::vec3(0, 2.5f, 30), glm::vec3(0, 3.14f, 0), glm::vec3(1, 1, 1), "..\\res\\monkey.obj", "..\\res\\fur.jpg", 1);
}

void MainGame::playBackgroundMusic()
{
	gameAudio.playAudioTrack();
}

void MainGame::printControls()
{
	cout << endl;
	cout << "O--------------------------------------O" << endl;
	cout << "|             GAME CONTROLS            |" << endl;
	cout << "O--------------------------------------O" << endl;
	cout << "| W/UP ARROW     -  MOVE FORWARD       |" << endl;
	cout << "| A/LEFT ARROW   -  MOVE LEFT          |" << endl;
	cout << "| S/DOWN ARROW   -  MOVE DOWN          |" << endl;
	cout << "| D/RIGHT ARROW  -  MOVE RIGHT         |" << endl;
	cout << "| SPACE          -  MOVE UP            |" << endl;
	cout << "| LEFT CTRL      -  MOVE DOWN          |" << endl;
	cout << "| MOUSE WHEEL    -  CHANGE WORLD SPEED |" << endl;
	cout << "O--------------------------------------O" << endl;
}

void MainGame::gameLoop()
{
	while (gameState != GameState::EXIT)
	{
		processInput();
		drawGame();
	}
}

void MainGame::processInput()
{
	//Tracks user input.
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_MOUSEWHEEL:		//If user scrolls the mouse wheel up or down, change timerSpeed accordingly.
				if (event.wheel.y != 0)
				{
					timerSpeed += (event.wheel.y * 0.0001f);
				}
				break;


			case SDL_KEYDOWN:		//If player presses a key down, set a boolean variable for their movement.
				switch (event.key.keysym.sym)
				{
					case SDLK_UP:
					case SDLK_w:
						playerMovingForward = true;
						break;

					case SDLK_DOWN:
					case SDLK_s:
						playerMovingBack = true;
						break;

					case SDLK_LEFT:
					case SDLK_a:
						playerMovingLeft = true;
						break;

					case SDLK_RIGHT:
					case SDLK_d:
						playerMovingRight = true;
						break;

					case SDLK_SPACE:
						playerMovingUp = true;
						break;

					case SDLK_LCTRL:
						playerMovingDown = true;
						break;
				}
				break;


			case SDL_KEYUP:		//If player releases a movement key, revert the matching boolean variable to false.
				switch (event.key.keysym.sym)
				{
					case SDLK_UP:
					case SDLK_w:
						playerMovingForward = false;
						break;

					case SDLK_DOWN:
					case SDLK_s:
						playerMovingBack = false;
						break;

					case SDLK_LEFT:
					case SDLK_a:
						playerMovingLeft = false;
						break;

					case SDLK_RIGHT:
					case SDLK_d:
						playerMovingRight = false;
						break;

					case SDLK_SPACE:
						playerMovingUp = false;
						break;

					case SDLK_LCTRL:
						playerMovingDown = false;
						break;
				}
				break;


			case SDL_QUIT:
				gameState = GameState::EXIT;
				break;
		}
	}

	collisionChecking();		//Checks if player is colliding with other game objects.
	playerMovement();		//Moves player according to the boolean variables above.
	cameraMovement();		//Moves camera to follow the player.
}

void MainGame::collisionChecking()
{
	if (player.checkCollisions(&ground))		//Bounce player away from the ground if they collide with it.
	{
		cout << "Player collided with ground!" << endl;
		bouncePlayer(&ground.transform);
	}
	if (player.checkCollisions(&sun))		//Bounce player away from the sun if they collide with it.
	{
		cout << "Player collided with sun!" << endl;
		bouncePlayer(&sun.transform);
	}
	else if (player.checkCollisions(&monkeyHead))		//Pop the monkey head if the player collides with it.
	{
		cout << "Player collided with monkey!" << endl;
		popMonkey();
	}
}

void MainGame::bouncePlayer(Transform* otherObject)
{
	//Move the player in the opposite direction of the other game object.
	glm::vec3 bounceDirection = normalize(*player.transform.getPos() - *otherObject->getPos());
	player.moveObject(*player.transform.getPos() + (bounceDirection));
}

void MainGame::popMonkey()
{
	//Hide the monkey head, disable its colliders and play a sound effect.
	monkeyHead.colliderRadius = 0;
	gameAudio.playAudioClip(0);

	monkeyPopped = true;
}

void MainGame::playerMovement()
{
	glm::vec3 newPosition;
	newPosition = *player.transform.getPos();

	if (playerMovingLeft)
	{
		newPosition.x += 0.005f;
	}
	if (playerMovingRight)
	{
		newPosition.x -= 0.005f;
	}

	if (playerMovingUp)
	{
		newPosition.y += 0.005f;
	}
	if (playerMovingDown)
	{
		newPosition.y -= 0.005f;
	}

	if (playerMovingForward)
	{
		newPosition.z += 0.005f;
	}
	if (playerMovingBack)
	{
		newPosition.z -= 0.005f;
	}

	player.moveObject(newPosition);

}

void MainGame::cameraMovement()
{
	//Camera follows player with an offset position.
	glm::vec3 newPosition = *player.transform.getPos();
	newPosition.y += 2;
	newPosition.z -= 8;

	playerCamera.moveCamera(newPosition);
}

void MainGame::drawGame()
{
	//Update shader uniforms to keep lighting up-to-date.
	defaultShader.setVec3Uniform("sunPos", *sun.transform.getPos());
	defaultShader.setVec3Uniform("cameraPos", *playerCamera.getPosition());

	gameDisplay.clearDisplay(0.4f, 0.6f, 0.6f, 1.0f);		//Clear the display, filling in the blank space (the 'sky') with a colour using the specified RGBA values.

	sunOrbit();		//Move sun object.
	drawSun();		//Draw sun object.
	drawGround();		//Draw ground object.
	drawPlayer();		//Draw player object.
	if (!monkeyPopped) { drawMonkey(); }		//If the monkey hasn't been popped, draw monkey object.

	timer += timerSpeed;		//Increment timer.

	gameDisplay.swapBuffer();
}

void MainGame::sunOrbit()
{
	glm::vec3 newPosition(60 * sin(timer), 60 * cos(timer), 0);
	sun.moveObject(newPosition);
}

void MainGame::drawSun()
{
	sunShader.bind();		//Bind sun shader as the active shader.
	sunShader.update(sun.transform, playerCamera);

	sun.texture.bind(0);		//Set sun texture as active texture.

	sun.mesh.draw();		//Draw the mesh
}

void MainGame::drawGround()
{
	defaultShader.bind();		//Bind default shader as the active shader.
	defaultShader.update(ground.transform, playerCamera);

	ground.texture.bind(0);		//Set ground texture as active texture.

	ground.mesh.draw();		//Draw the mesh.
}

void MainGame::drawPlayer()
{
	defaultShader.update(player.transform, playerCamera);

	player.texture.bind(0);		//Set player texture as active texture.

	player.mesh.draw();		//Draw the mesh.
}

void MainGame::drawMonkey()
{
	defaultShader.update(monkeyHead.transform, playerCamera);

	monkeyHead.texture.bind(0);

	monkeyHead.mesh.draw();
}