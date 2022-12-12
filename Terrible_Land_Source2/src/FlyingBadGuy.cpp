// FlyingBadGuy.cpp

#include "../include/FlyingBadGuy.h"

// Single-screen BadGuy constructor.
FlyingBadGuy::FlyingBadGuy(	int inX,
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

	allAnimations[BAD_GUY_ATTACKING_LEFT] = new Animation( screen1, "FlyingBadGuy", "attacking_left", 4 );
	allAnimations[BAD_GUY_ATTACKING_RIGHT] = new Animation( screen1, "FlyingBadGuy", "attacking_right", 4 );
	allAnimations[BAD_GUY_WALKING_LEFT] = new Animation( screen1, "FlyingBadGuy", "walking_left", 4 );
	allAnimations[BAD_GUY_WALKING_RIGHT] = new Animation( screen1, "FlyingBadGuy", "walking_right", 4 );

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
}

// Update FlyingBadGuy positions
void FlyingBadGuy::update(Player * player) {

	switch (moveState) {

		case BAD_GUY_ATTACKING_LEFT :
							break;

		case BAD_GUY_ATTACKING_RIGHT :
							break;

		case BAD_GUY_WALKING_LEFT :
							break;

		case BAD_GUY_WALKING_RIGHT :
							break;
	}

	// Advance animation every few frames
	badGuyFrameCount++;
	if (badGuyFrameCount == BAD_GUY_GAME_FRAMES_PER_ANIM_FRAME) {
		allAnimations[moveState]->advanceFrame();
		badGuyFrameCount = 0;
	}

	surface = allAnimations[moveState]->getCurrentSDL_Surface();

	if (dead) {
		y+=10;
	} else {
		// Make FlyingBadGuy do rounds
		if (!attacking) {
			if (	badGuyHustleDirection == 1) {
				if (badGuyHustlePosition < BAD_GUY_HUSTLE) {
					x += 1;
					badGuyHustlePosition += BAD_GUY_WALK_SPEED;
				} else {
					badGuyHustleDirection = -1;
					setMoveState(BAD_GUY_WALKING_LEFT);
				}
			} else if (badGuyHustleDirection == -1) {
				if (badGuyHustlePosition > 0) {
					x -= 1;
					badGuyHustlePosition -= BAD_GUY_WALK_SPEED;
				} else {
					badGuyHustleDirection = 1;
					setMoveState(BAD_GUY_WALKING_RIGHT);
				}
			}

			if (!attacking && y > 25) {
				y -= 1;
			}
		}

		// Check to see if attacking player
		int playerDistanceX = x - player->getX();
		int playerDistanceY = y - player->getY();

		if (fabs(playerDistanceX) < ATTACK_DISTANCE) {

			attacking = true;

			if (y + height == groundLevel) {
				jump(BAD_GUY_JUMP_HEIGHT);
			}

			if (playerDistanceX >= 0) {
				if (moveState != BAD_GUY_ATTACKING_LEFT) {
					setMoveState(BAD_GUY_ATTACKING_LEFT);
				}
				x -= BAD_GUY_ATTACK_SPEED;
			} else {
				if (moveState != BAD_GUY_ATTACKING_RIGHT) {
					setMoveState(BAD_GUY_ATTACKING_RIGHT);
				}
				x += BAD_GUY_ATTACK_SPEED;
			}

			if (playerDistanceY > 0) {
				y -= BAD_GUY_ATTACK_SPEED;
			} else {
				y += BAD_GUY_ATTACK_SPEED;
			}

		} else {
			attacking = false;
		}
	}
}

