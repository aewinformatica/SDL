// BadGuy.cpp

#include "../include/BadGuy.h"

// No-arg constructor
BadGuy::BadGuy() : Entity() {}

// Single-screen BadGuy constructor.
BadGuy::BadGuy(	int inX,
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

	allAnimations[BAD_GUY_ATTACKING_LEFT] = new Animation( screen1, "BadGuy", "attacking_left", 2 );
	allAnimations[BAD_GUY_ATTACKING_RIGHT] = new Animation( screen1, "BadGuy", "attacking_right", 2 );
	allAnimations[BAD_GUY_WALKING_LEFT] = new Animation( screen1, "BadGuy", "walking_left", 2 );
	allAnimations[BAD_GUY_WALKING_RIGHT] = new Animation( screen1, "BadGuy", "walking_right", 2 );

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

// Split-screen BadGuy constructor.
BadGuy::BadGuy(	int inX,
				int inY, 
				int inWidth, 
				int inHeight,
				int inGroundLevel,
				SDL_Surface * inScreen1,
				SDL_Surface * inScreen2 ) {

	x = inX;
	y = inY;
	width = inWidth;
	height = inHeight;
	groundLevel = inGroundLevel;
	screen1 = inScreen1;
	screen2 = inScreen2;

	allAnimations[BAD_GUY_ATTACKING_LEFT] = new Animation( screen1, "BadGuy", "attacking_left", 2 );
	allAnimations[BAD_GUY_ATTACKING_RIGHT] = new Animation( screen1, "BadGuy", "attacking_right", 2 );
	allAnimations[BAD_GUY_WALKING_LEFT] = new Animation( screen1, "BadGuy", "walking_left", 2 );
	allAnimations[BAD_GUY_WALKING_RIGHT] = new Animation( screen1, "BadGuy", "walking_right", 2 );

	jumping = false;
	falling = false;
	moveState = WALKING_LEFT;
	jumpHeight = 0;
	surface = allAnimations[moveState]->getCurrentSDL_Surface();

	badGuyFrameCount = 0;
	onLedge = false;
	badGuyHustlePosition = 0;
	badGuyHustleDirection = 1;
	attacking = false;
	dead = false;
}

// Destructor
void BadGuy::deallocate() {

	for (int i =0; i < NUM_BAD_GUY_ANIMATIONS; i++) {
		delete allAnimations[i];
	}
}

// Destructor.  Overridden because of the dynamic allocation done during
// construction.  Should not be explicitly called during the program, but
// is necessary anyway.
BadGuy::~BadGuy() {

	deallocate();

}

// Getters
bool BadGuy::getJumping() { return jumping; }
bool BadGuy::getFalling() { return falling; }
int BadGuy::getMoveState() { return moveState; }
int BadGuy::getJumpHeight() { return jumpHeight; }
bool BadGuy::getOnLedge() { return onLedge; }
bool BadGuy::getDead() { return dead; }
int BadGuy::getLife() { return life; }

// Setters
void BadGuy::setJumping(bool inJumping) { jumping = inJumping; }
void BadGuy::setFalling(bool inFalling) { falling = inFalling; }
void BadGuy::setJumpHeight(int inJumpHeight) { jumpHeight = inJumpHeight; }
void BadGuy::setOnLedge(bool inOnLedge) { onLedge = inOnLedge; }
void BadGuy::setDead(bool inDead) { dead = inDead; }
void BadGuy::setLife(int inLife) { life = inLife; }
void BadGuy::changeLife(int change) { life += change; }

void BadGuy::setMoveState(int inMoveState) {
	allAnimations[moveState]->setCurrentFrame(0);
	moveState = inMoveState;
}

// Update BadGuy positions
void BadGuy::update(Player * player) {

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

	// Make BadGuy do rounds
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
	}

	// Check to see if attacking player
	int playerDistance = x - player->getX();
	if (fabs(playerDistance) < ATTACK_DISTANCE) {

		attacking = true;

		if (y + height == groundLevel) {
			jump(BAD_GUY_JUMP_HEIGHT);
		}

		if (playerDistance >= 0) {
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

	} else {
		attacking = false;
	}
		
	if (y + height != groundLevel) {
		ySpeed -= 1;
		y -= ySpeed;
		if (ySpeed > 0) falling = true;
	}
	if (y + height >= groundLevel) {
		ySpeed = 0;
		y = groundLevel - height;
	}

	if (dead) y+=1;
}


// Jump
void BadGuy::jump(int inJumpHeight) {
	y -= 1; // stupid hack. poorly coded.
	ySpeed = jumpSpeed;
}


