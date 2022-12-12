// Level.h

#ifndef Level_H

#define Level_H

#include "General.h"
#include <vector>
#include <iostream>
#include <fstream>

using std::ifstream;
using std::ofstream;
using std::ios;
using std::cerr;
using std::cout;
using std::cin;
using std::endl;

#include <string>
using std::string;

#define DEFAULT_LEVEL_LENGTH   2800

#define NUM_Z_LEVELS      9

#define Z_LEVEL_SKY       0
#define Z_LEVEL_TREES     1
#define Z_LEVEL_GROUND    2
#define Z_LEVEL_SIGNS	  3
#define Z_LEVEL_BAD_GUYS  4
#define Z_LEVEL_LEDGES	  5
#define Z_LEVEL_FLYING_BAD_GUYS		6
#define Z_LEVEL_WEAPONS   7
#define Z_LEVEL_BAD_GUY_BOSS   8

class Level {

	public:

	/*
	 *       Special Functions.
	 *
	 */

	// No-arg constructor
	Level();

	// Single-screen Constructor
	Level(	int inStartX,
			int inEndX,
			SDL_Surface * inScreen1 );

	// Split-screen Constructor
	Level(	int inStartX,
			int inEndX,
			SDL_Surface * inScreen1,
			SDL_Surface * inScreen2 );

	// Copy constructor.  Necessarily overridden because construction involves
	// dynamic allocation.  Should not need to be used during the lab, but is
	// included for completeness.
	Level(const Level & t);

	// Destructor.  Overridden because of the dynamic allocation done during
	// construction.  Should not be explicitly called during the program, but
	// is necessary anyway.
	~Level();

	// Assignment operator overload.  Necessary due to dynamic allocation.
	// Should not be needed during this lab, but is included for completeness.
	Level & operator=(const Level & t);

	// Detect Collisions between Entities in given location
	void handleCollisions(	Player * player );
	void emptyAll();

	// Getters
	int getStartX();
	int getEndX();
	int getCurrentX();
	bool getScrollScreenRight();
	bool getScrollScreenLeft();
	int getCurrentGameGroundLevel();

	// Setters
	void setStartX(int inStartX);
	void setEndX(int inEndX);
	void setCurrentX(int inCurrentX);
	void setScrollScreenRight(bool inScrollScreenRight);
	void setScrollScreenLeft(bool inScrollScreenLeft);
	void setCurrentGameGroundLevel(int inCurrentGameGroundLevel);

	void changeCurrentX(int changeCurrentX);

	void addEntity(	Entity * inEntity,
					int zCoord );

	void removeEntity(	Entity * inEntity );

	void checkForScrollScreen(Player * player);

	void loadLevel(int levelNumber);
	void update(Player * player);
	void display(Player * player);

	protected:
		int startX, endX, currentX;
		bool scrollScreenLeft, scrollScreenRight;
		std::vector< Entity * > allZ[NUM_Z_LEVELS];
		int currentGameGroundLevel;
		bool playerOnLedge;
		SDL_Surface * screen1;
		SDL_Surface * screen2;
		bool singleScreen;
		Mix_Chunk *gotHit;
		Mix_Chunk *ouch;
		Mix_Chunk *tristanOof;
		int playerName;

	private:

		// Helper function to copy grid and map from existing Level.
		// Used by both copy constructor and assignment operator.
		void copy(const Level & t);

		// Helper function to deallocate space from a existing Level.
		// Used by both assignment operator and destructor.
		void deallocate();

		

};

#endif
