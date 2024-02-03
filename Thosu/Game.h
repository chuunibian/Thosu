#pragma once

#include <stdio.h>

#include <SFML/System.hpp>
#include<SFML/Graphics.hpp>

#include "PlayerController.h"
#include "WorldBackgroundController.h"
#include "EnemyController.h"
#include "EnemyProjectileController.h"

constexpr auto SCREEN_HEIGHT = 1000;
constexpr auto SCREEN_WIDTH = 1200;
constexpr auto FRAME_LIMIT = 60;

using namespace sf;

class Game
{
private:
	/////////////////////////////////////////
	// SFML classed objects mainly to hold OpenGL 
	// elements and some system events
	/////////////////////////////////////////
	RenderWindow* window;
	Event exit_event;
	VideoMode screen_size;
	Clock delta_clock;
	float dt = 0;

	/////////////////////////////////////////
	// Compositional Objects
	// 
	/////////////////////////////////////////
	//GUI game_gui;
	PlayerController player_controller; //NOTE: Automatic storage object deletes when OoS
	WorldBackgroundController world_bkgd_controller;
	EnemyController enemy_controller;
	EnemyProjectileController projectile_controller;

	//Enemy enemies;
	//CollisionController collision_controller; WHAT IF PLAYER AND PROJ HAD COLLISION CONTROLLER
	//ScoreController score_controller;


	/* ======== Initializers ======== */
	/////////////////////////////////////////
	// Initializes a variety of variables important
	// to state of being or numerical logic
	// 
	/////////////////////////////////////////
	void initVariables();

	/////////////////////////////////////////
	// Initializes a the size of the window and properties
	// and it sets the locked framerate of the game
	// 
	/////////////////////////////////////////
	void initWindow();
	/* ============================== */

public:
	/* ======== Con/Decon ======== */
	/////////////////////////////////////////
	// Default constructor
	// 
	/////////////////////////////////////////
	Game();

	/////////////////////////////////////////
	// Default deconstructor
	// 
	/////////////////////////////////////////
	~Game();
	/* =========================== */

	/////////////////////////////////////////
	// Checks if the game window is still open
	// by wrapping this method around a sfml method
	// for window status
	// 
	// @return window->isOpen()
	// 
	/////////////////////////////////////////
	bool isOpen();

	/////////////////////////////////////////
	// Polls for esc key press or exit button press
	// if any of those events are done then close window
	// 
	/////////////////////////////////////////
	void pollEvents();

	/* ======== Update/Render ======== */
	/////////////////////////////////////////////
	// Updates internal logic of the game object.
	// Player, background, enemy, all projectiles, GUI, and
	// more will all be updated. Specifically most update
	// functions are called from all controllers composed within
	// the game object
	// 
	// Calls: 	**TODO** (unfinished)
	// 
	//////////////////////////////////////////////
	void update();

	/////////////////////////////////////////////
	// Renders internal logic of the game graphically to
	// the window
	//////////////////////////////////////////////
	void render();
	/* =============================== */

};

