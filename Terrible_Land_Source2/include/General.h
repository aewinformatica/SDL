// General globals

#ifndef General_H

#define General_H

#include "SDL.h"
#include "SDL_mixer.h"

#include "Entity.h"
#include "Player.h"
#include "Ledge.h"
#include "Level.h"
#include "Animation.h"
#include "Tree.h"
#include "Tile.h"
#include "BadGuy.h"
#include "FlyingBadGuy.h"
#include "GUI.h"
#include "CandyCane.h"
#include "BadGuyBoss.h"

#define GRAVITY				  1

#define SCREEN_WIDTH          640
#define SCREEN_HEIGHT         480

#define SPRITE_HEIGHT         200
#define SPRITE_WIDTH          100

#define BAD_GUY_HEIGHT        131
#define BAD_GUY_WIDTH          69

#define FLYING_BAD_GUY_HEIGHT  168
#define FLYING_BAD_GUY_WIDTH    93

#define BAD_GUY_BOSS_HEIGHT   220
#define BAD_GUY_BOSS_WIDTH    250

#define CANDY_CANE_HEIGHT      59
#define CANDY_CANE_WIDTH       59

#define PLAYER_START_LOC        0

#define TREE_HEIGHT           189
#define TREE_WIDTH            204

#define MOVE_SPEED             65
#define TIME_DELAY              6

#define JUMP_SPEED              5
#define NORMAL_JUMP_HEIGHT    140
#define COUNT_DOWN_GOING_UP   100

#define SCROLL_LENGTH		  220
#define SCROLL_LENGTH_MENU_SCREEN		  120

#define SPREAD_TREES          450

#define GROUND_LEVEL SCREEN_HEIGHT - 96

#define NUM_PLAYERS			    2

#define TRISTAN     0
#define PATRICK     1

#include <iostream>
#include <fstream>

using std::ofstream;
using std::cerr;
using std::endl;

// Redefining error???!  Presently kept locally in Game/Level, but should be here
//bool singleScreen = true;

/*
// Helper function for writing errors to file
void writeErrorToFile( char errorMessage [] ) {
	ofstream errorFile( "errorFile.txt" );
	if ( !errorFile ) {
		cerr << "File could not be opened" << endl;
	}

	errorFile << errorMessage;
}
/**/	
#endif
