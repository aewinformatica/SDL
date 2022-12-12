// badGuyBoss.cpp

#include "../include/BadGuyBoss.h"

// Single-screen BadGuyBoss constructor.
BadGuyBoss::BadGuyBoss(	int inX,
						int inY, 
						int inWidth, 
						int inHeight,
						int inGroundLevel,
						SDL_Surface * inScreen1 ) {

	x = inX;
	y = inY;
	width = inWidth;
	height = inHeight;
	groundLevel = inGroundLevel;
	screen1 = inScreen1;

	allAnimations[BAD_GUY_ATTACKING_LEFT] = new Animation( screen1, "BadGuyBoss", "attacking_left", 2 );
	allAnimations[BAD_GUY_ATTACKING_RIGHT] = new Animation( screen1, "BadGuyBoss", "attacking_right", 2 );
	allAnimations[BAD_GUY_WALKING_LEFT] = new Animation( screen1, "BadGuyBoss", "walking_left", 2 );
	allAnimations[BAD_GUY_WALKING_RIGHT] = new Animation( screen1, "BadGuyBoss", "walking_right", 2 );

	jumping = false;
	falling = false;
	moveState = WALKING_LEFT;
	jumpHeight = 0;

	surface = allAnimations[moveState]->getCurrentSDL_Surface();

	jumpSpeed = 8;
	badGuyFrameCount = 0;
	onLedge = false;
	badGuyHustlePosition = 0;
	badGuyHustleDirection = 1;
	attacking = false;
	dead = false;

	life = 100;
}
