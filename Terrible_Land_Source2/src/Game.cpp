/**************************************************************************

TUCKEY SIDE_SCROLLER!!!!!!!!!!!!!!!!!!!!!!!!!


**************************************************************************/

#include "../include/Game.h"

// Single-screen constructor
Game::Game(	SDL_Surface * inScreen1 ) {

	screen1 = inScreen1;
	singleScreen = true;

	readNumLevels();

	level = new Level(0, 2800, screen1);

	player = new Player(	SCREEN_WIDTH/2 - SPRITE_WIDTH,
							level->getCurrentGameGroundLevel() - SPRITE_HEIGHT,
							SPRITE_WIDTH,
							SPRITE_HEIGHT,
							level->getCurrentGameGroundLevel(),
							"Player_Patrick",
							PATRICK,
							screen1
						);

	levelNumber = 0;
	level->loadLevel( levelNumber );

	gui = new GUI(player, screen1);

	menuButtons[MENU_BUTTON_START] = new Entity(	SCREEN_WIDTH/2 - 100, 
													SCREEN_HEIGHT - 100,
													200, 
													100,
													"images/menu_button_start.bmp",
													screen1 );

	menuButtons[MENU_BUTTON_PATRICK] = new Entity(	25, 
													25,
													115, 
													143,
													"images/menu_button_patrick.bmp",
													screen1 );

	menuButtons[MENU_BUTTON_TRISTAN] = new Entity(	SCREEN_WIDTH - 125, 
													25,
													114, 
													155,
													"images/menu_button_tristan.bmp",
													screen1 );

	menuButtons[MENU_TITLE] = new Entity(	SCREEN_WIDTH/2 - 200, 
											75,
											400, 
											100,
											"images/menu_title.bmp",
											screen1 );

	menuButtons[MENU_BUTTON_QUIT] = new Entity(	SCREEN_WIDTH - 150, 
												SCREEN_HEIGHT - 75,
												100, 
												50,
												"images/menu_button_quit.bmp",
												screen1 );

	menuButtons[MENU_BUTTON_ABOUT] = new Entity(	0, 
												SCREEN_HEIGHT - 75,
												150, 
												75,
												"images/menu_button_about.bmp",
												screen1 );

	if(Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 2048) < 0)
	{
		printf("Warning: Couldn't set 44100 Hz 16-bit audio\n- Reason: %s\n",
								SDL_GetError());
	}

	mouseButtonDown = false;
	playerDead = false;
	displayAbout = false;
	displayYouWon = false;

	youDiedSurface = SDL_LoadBMP("images/youdied.bmp");
	aboutSurface = SDL_LoadBMP("images/about.bmp");
	youWonSurface = SDL_LoadBMP("images/you_won.bmp");
	colorkey = SDL_MapRGB(screen1->format, 255, 255, 255);
	SDL_SetColorKey(youDiedSurface, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
	SDL_SetColorKey(aboutSurface, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
	SDL_SetColorKey(youWonSurface, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
	messageRect.x = SCREEN_WIDTH/2 - 225;
	messageRect.y = SCREEN_HEIGHT/2 - 225;

	// Load in the music
	music = Mix_LoadMUS("Sound/Music/tropical_islands.xm");
	// And sound effects
	boing = Mix_LoadWAV("Sound/FX/boing.wav");
	antsong = Mix_LoadWAV("Sound/Music/antsong_compressed.wav");
	youDied = Mix_LoadWAV("Sound/FX/youdied.wav");
	funeralMarch = Mix_LoadWAV("Sound/Music/funeralMarch.wav");
	patrickAwesome = Mix_LoadWAV("Sound/FX/patrick_is_awesome.wav");
	tristanFool = Mix_LoadWAV("Sound/FX/tristan_is_a_fool.wav");

	Mix_PlayChannel(1,antsong,-1);

}

// Split-screen constructor
Game::Game(	SDL_Surface * inScreen1,
			SDL_Surface * inScreen2 ) {

	/*  If we really want to make it splitscreen, we need to add
		a second player, and makes the appropriate changes to level
		constructors   */

	screen1 = inScreen1;
	screen2 = inScreen2;
	singleScreen = false;

	level = new Level(0, DEFAULT_LEVEL_LENGTH, screen1, screen2);

	player = new Player(	100,
							level->getCurrentGameGroundLevel() - SPRITE_HEIGHT,
							SPRITE_WIDTH,
							SPRITE_HEIGHT,
							level->getCurrentGameGroundLevel(),
							"Player_Patrick",
							PATRICK,
							screen1
						);

	levelNumber = 0;
	level->loadLevel( levelNumber );

	mouseButtonDown = false;

	//gui = new GUI(player, player2, screen1);
}

void Game::nextLevel() {
	displayAbout = false;
	levelNumber++;
	if (levelNumber < numLevels) {
		setLevel(levelNumber);
		if (displayYouWon) displayYouWon = false;
	} else {
		setLevel(0);
		displayYouWon = true;
	}
}

int Game::setLevel(int nextLevel) {

	if (player->getLife() < 1) {
		player->setLife(player->getMaxLife() );
		playerDead = false;
	}

	levelNumber = nextLevel;

	level->emptyAll();

	//delete level;
	level = new Level(0, DEFAULT_LEVEL_LENGTH, screen1);
	level->loadLevel(levelNumber);

	player->resetForNewLevel();
	player->setY(-SPRITE_HEIGHT);

	if (levelNumber == 0) {
		Mix_HaltMusic();
		player->setX(SCREEN_WIDTH/2);
		Mix_PlayChannel(1,antsong,-1);
		SDL_ShowCursor(1);
	} else {
		// If we aren't playing music at the moment
		SDL_ShowCursor(0);
	}

	return 1;
}

// Destructor
void Game::deallocate() {
	// for deallocating dynamically allocated shoitE$
	// Should we be deallocating player/level/gui here?

	Mix_FreeMusic(music);
	Mix_FreeChunk(boing);
	Mix_FreeChunk(antsong);
	Mix_FreeChunk(youDied);
	Mix_FreeChunk(funeralMarch);
	Mix_FreeChunk(patrickAwesome);
	Mix_FreeChunk(tristanFool);

	SDL_FreeSurface(youDiedSurface);
	SDL_FreeSurface(aboutSurface);
	SDL_FreeSurface(youWonSurface);
}

// Destructor.  Overridden because of the dynamic allocation done during
// construction.  Should not be explicitly called during the program, but
// is necessary anyway.
Game::~Game() {

	deallocate();

}

// Helper function.  Copies attributes of one Game over to those of this one.
void Game::copy(const Game & g) {

	// copy all attributes

}

// Copy constructor.  Necessarily overridden because construction involves
// dynamic allocation.  Should not need to be used during the lab, but is
// included for completeness.
Game::Game(const Game & g) { copy(g); }

// Handle Menu Selections
int Game::checkForMenuSelections(int menuButtonArrayNum, SDL_Cursor * cursor) {

	int mouseX, mouseY = 0;
	int playerX, playerY = 0;

	Entity * entity = menuButtons[menuButtonArrayNum];

	playerX = player->getX();
	playerY = player->getY();

	SDL_GetMouseState(&mouseX, &mouseY);

	if (	mouseX > entity->getX()
		&&	mouseX < entity->getX() + entity->getWidth()
		&&	mouseY > entity->getY()
		&&	mouseY < entity->getY() + entity->getHeight()
		) {

		switch (menuButtonArrayNum) {
	
			case MENU_BUTTON_START :
										nextLevel();
										break;

			case MENU_BUTTON_QUIT :
										return 0;

			case MENU_BUTTON_ABOUT :
										displayAbout = !displayAbout;
										break;

			case MENU_BUTTON_PATRICK :
										Mix_PlayChannel(0,patrickAwesome,0);
										player = new Player(	playerX,
																playerY,
																SPRITE_WIDTH,
																SPRITE_HEIGHT,
																level->getCurrentGameGroundLevel(),
																"Player_Patrick",
																PATRICK,
																screen1
															);
										break;

			case MENU_BUTTON_TRISTAN :
										Mix_PlayChannel(0,tristanFool,0);
										player = new Player(	playerX,
																playerY,
																SPRITE_WIDTH,
																SPRITE_HEIGHT,
																level->getCurrentGameGroundLevel(),
																"Player_Tristan",
																TRISTAN,
																screen1
															);
										break;
	
		}
	}

	return 1;
}

void Game::blitYouDied() {
	SDL_BlitSurface(youDiedSurface, NULL, screen1, &messageRect);
	Mix_PlayChannel(0,youDied,0);
	Mix_PlayChannel(1,funeralMarch,-1);
}


// Game Loop Function
int Game::runGameLoop() {

	if (levelNumber == 0) {
		if (mouseButtonDown) {
			for (int i = 0; i < NUM_MENU_BUTTONS; i++) {
				if (checkForMenuSelections(i, SDL_GetCursor() ) == 0) {
					return 0;
				}
			}

			mouseButtonDown = false;
		}
	}

	if (player->getLife() < 1) {

		if (!playerDead) {
			playerDead = true;
			Mix_HaltMusic();	
			blitYouDied();
			SDL_UpdateRect(screen1,0,0,0,0);
		}

		return 1;
	}

	// Collision detection
	level->handleCollisions(player);

	// handle sprite movement
	keystate = SDL_GetKeyState(NULL);

	// Space bar
	if (	keystate[SDLK_SPACE]
		&&	player->getHasCandyCane()
		) {
		player->throwCandyCane();
		Mix_PlayChannel(0,boing,0);
	}

	// Space bar
	if (	keystate[SDLK_s]
		) {
		Mix_PlayChannel(0,boing,0);
	}

	// Left arrow
	if (	keystate[SDLK_LEFT]
		&&	(		player->getMoveState() == IDLE_STANDING_LEFT
				||	player->getMoveState() == IDLE_STANDING_RIGHT
				||	player->getMoveState() == WALKING_LEFT
				||	player->getJumping() 
				||	player->getFalling() )
		)
	{
		player->changeMoveSpeed( -MOVE_SPEED/10 );
		if (player->getMoveState() != WALKING_LEFT) {
			player->setMoveState(WALKING_LEFT);
		}
	} else if (player->getMoveState() == WALKING_LEFT) {
		player->setMoveState(IDLE_STANDING_LEFT);
	}

	// Right arrow
	if (	keystate[SDLK_RIGHT]
		&&	(		player->getMoveState() == IDLE_STANDING_LEFT
				||	player->getMoveState() == IDLE_STANDING_RIGHT
				||	player->getMoveState() == WALKING_RIGHT
				||	player->getJumping() 
				||	player->getFalling()
			)
		)
	{
		player->changeMoveSpeed( MOVE_SPEED/10 );
		if (player->getMoveState() != WALKING_RIGHT) {
			player->setMoveState(WALKING_RIGHT);
		}
	} else if (player->getMoveState() == WALKING_RIGHT) {
		player->setMoveState(IDLE_STANDING_RIGHT);
	}

	// Up arrow
	if (	keystate[SDLK_UP]
		&&	player->getY() + player->getHeight() == player->getGroundLevel()
		) {
		player->jump( NORMAL_JUMP_HEIGHT );
		player->setFalling(false);
	}

	// Down arrow
	if (keystate[SDLK_DOWN] ) {
		if (player->getMoveState() != IDLE_CROUCHING) {
			player->setMoveState(IDLE_CROUCHING);
		}
	} else if (player->getMoveState() == IDLE_CROUCHING) {
		player->setMoveState(IDLE_STANDING_RIGHT);
	}

	// account for player being on ledge
	if (player->getOnLedge() ) {
		player->changeMoveSpeed(MOVE_SPEED/20);
	}

	// update and draw level
	if (levelNumber != 0) {
		level->update(player);
	}
	level->display(player);

	// Prevent player from leaving screen

	// If game is on pause/intro screen
	if (levelNumber == 0) {
		if (player->getX() < SCROLL_LENGTH_MENU_SCREEN) {
			player->setX(SCROLL_LENGTH_MENU_SCREEN);
		} else if (player->getX() > SCREEN_WIDTH - SCROLL_LENGTH_MENU_SCREEN - player->getWidth() ) {
			player->setX(SCREEN_WIDTH - SCROLL_LENGTH_MENU_SCREEN - player->getWidth());
		}

	// Else proceed like normal on a level
	} else {
		if (	level->getCurrentX() <= 0) {
			if (player->getX() < 0) {
				player->setX(0);
			}

		} else if (	level->getCurrentX() >= level->getEndX() ) { 
			if (	player->getX() > SCREEN_WIDTH ) {
				nextLevel();
			}

		} else {
			if (	player->getX() < SCROLL_LENGTH
				&&		level->getCurrentX() != 0 ) {
				player->setX(SCROLL_LENGTH);	

			} else if (	player->getX() > SCREEN_WIDTH - SCROLL_LENGTH - player->getWidth()
					&&	level->getCurrentX() != level->getEndX() ) {
				player->setX(SCREEN_WIDTH - SCROLL_LENGTH - player->getWidth());		
			}
		}
	}

	player->update();

	if (levelNumber != 0) {
		// draw the sprite / gui
		if (singleScreen) {
			gui->displaySingleScreen(player);
		} else {
			gui->displaySingleScreen(player);
		}
	} else {
		for (int i = 0; i < NUM_MENU_BUTTONS; i++) {
			menuButtons[i]->displaySingleScreen();
		}
		if (displayAbout) {
			SDL_BlitSurface(aboutSurface, NULL, screen1, &messageRect);
		} else if (displayYouWon) {
			SDL_BlitSurface(youWonSurface, NULL, screen1, &messageRect);
		}
	}

	// update the screen 
	SDL_UpdateRect(screen1,0,0,0,0);
	//SDL_UpdateRect(screen2,0,0,0,0);

	if (levelNumber != 0) {
		if(!Mix_PlayingMusic())
		{
		  //then start playing it.
			Mix_PlayChannel(1,boing,0);
			Mix_PlayMusic(music, 0);
		}
	}

	return 1;

}

/* Set numLevels to value found in numLevels.txt in Levels folder */
void Game::readNumLevels() {

	string fileName = "Levels/numLevels.txt";

	ifstream levelFile( fileName.c_str(), ios::in );
	if ( !levelFile ) {
		cerr << "File could not be opened" << endl;
	}

	levelFile >> numLevels;

	return;
}

// Getters
bool Game::getMouseButtonDown() { return mouseButtonDown; }
int Game::getLevelNumber() { return levelNumber; }
bool Game::getDisplayAbout() { return displayAbout; }
bool Game::getDisplayYouWon() { return displayYouWon; }

// Setters
void Game::setMouseButtonDown(bool inMouseButtonDown) {
	mouseButtonDown = inMouseButtonDown;
}
void Game::setLevelNumber(int inLevelNumber) {
	levelNumber = inLevelNumber;
}
void Game::setDisplayAbout(bool inDisplayAbout) { displayAbout = inDisplayAbout; }
void Game::setDisplayYouWon(bool inDisplayYouWon) { displayYouWon = inDisplayYouWon; }
