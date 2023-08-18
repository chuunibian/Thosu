#pragma once

#include <stdio.h>

#include <SFML/System.hpp>
#include<SFML/Graphics.hpp>

#include "PlayerController.h"

#define SCREEN_HEIGHT 850
#define SCREEN_WIDTH 1000
#define FRAME_LIMIT 60

using namespace sf;

class Game
{
private:
	RenderWindow* window;
	Event exit_event;
	VideoMode screen_size;

	//Compositional Objects
	//GUI game_gui;
	PlayerController player_controller;
	//Enemy enemies;
	//CollisionController collision_controller;
	//ScoreController score_controller;



	//Initializers
	void initVariables();
	void initWindow();



public:

	Game();
	~Game();

	//Accessors
	bool isOpen();

	void pollEvents();

	void update();
	void render();

};

