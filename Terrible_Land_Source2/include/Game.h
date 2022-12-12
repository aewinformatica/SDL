// Game.h

#ifndef Game_H

#define Game_H

#include "General.h"

#define NUM_LEVELS				4

#define NUM_MENU_BUTTONS		NUM_PLAYERS + 4

#define MENU_BUTTON_START		0
#define MENU_BUTTON_TRISTAN		1
#define MENU_BUTTON_PATRICK		2
#define MENU_TITLE				3
#define MENU_BUTTON_QUIT		4
#define MENU_BUTTON_ABOUT		5


class Game {

	public:

	/*
	 *       Special Functions.
	 *
	 */

	// Single-screen constructor
	Game(	SDL_Surface * inScreen1 );

	// Split-screen constructor
	Game(	SDL_Surface * inScreen1,
			SDL_Surface * inScreen2 );

	// Copy constructor.  Necessarily overridden because construction involves
	// dynamic allocation.  Should not need to be used during the lab, but is
	// included for completeness.
	Game(const Game & t);

	// Destructor.  Overridden because of the dynamic allocation done during
	// construction.  Should not be explicitly called during the program, but
	// is necessary anyway.
	~Game();

	// Assignment operator overload.  Necessary due to dynamic allocation.
	// Should not be needed during this lab, but is included for completeness.
	Game & operator=(const Game & t);

	int runGameLoop();
	int setLevel(int nextLevel);
	void nextLevel();
	int checkForMenuSelections(int buttonArrayNum, SDL_Cursor * cursor);
	void blitYouDied();
	void readNumLevels();

	// Getters
	bool getMouseButtonDown();
	int getLevelNumber();
	int getPlayerLife();
	bool getDisplayAbout();
	bool getDisplayYouWon();

	// Setters
	void setMouseButtonDown(bool inMouseButtonDown);
	void setLevelNumber(int inLevelNumber);
	void setDisplayAbout(bool inDisplayAbout);
	void setDisplayYouWon(bool inDisplayYouWon);


	protected:
		SDL_Surface * screen1;
		SDL_Surface * screen2;
		bool singleScreen;

	private:
		SDL_Event event;
		Uint8 *keystate;
		int colorkey;
		bool mouseButtonDown;
		bool playerDead;
		bool displayAbout;
		bool displayYouWon;

		SDL_Surface * youDiedSurface;
		SDL_Rect messageRect;

		SDL_Surface * aboutSurface;
		SDL_Surface * youWonSurface;

		// Set up implementation of new classes
		Level * level;
		int levelNumber;
		int numLevels;
		Player * player;
		Ledge * ledge;
		Ledge * ledge2;
		Tile * skyTile;
		Tile * sandTile;
		GUI * gui;
		Entity * menuButtons [NUM_MENU_BUTTONS];

		//Sound
		Mix_Music *music;
		Mix_Chunk *boing;
		Mix_Chunk *antsong;
		Mix_Chunk *youDied;
		Mix_Chunk *funeralMarch;
		Mix_Chunk *patrickAwesome;
		Mix_Chunk *tristanFool;

		// Helper function to copy grid and map from existing Game.
		// Used by both copy constructor and assignment operator.
		void copy(const Game & g);

		// Helper function to deallocate space from a existing Game.
		// Used by both assignment operator and destructor.
		void deallocate();

};

#endif
