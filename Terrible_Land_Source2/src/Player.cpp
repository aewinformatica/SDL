// Player.cpp

#include "../include/Player.h"

// No-arg constructor
Player::Player() : Entity() {}

// Single-screen Player constructor.
Player::Player(	int inX,
				int inY, 
				int inWidth, 
				int inHeight,
				int inGroundLevel,
				char playerName[],
				int inName,
				SDL_Surface * inScreen1 ) {

	x = inX;
	y = inY;
	width = inWidth;
	height = inHeight;
	groundLevel = inGroundLevel;
	screen1 = inScreen1;
	name = inName;

	allAnimations[IDLE_STANDING_LEFT] = new Animation( screen1, playerName, "idle_standing_left", 1 );
	allAnimations[IDLE_STANDING_RIGHT] = new Animation( screen1, playerName, "idle_standing_right", 1 );
	allAnimations[IDLE_CROUCHING] = new Animation( screen1, playerName, "idle_crouching", 1 );
	allAnimations[WALKING_LEFT] = new Animation( screen1, playerName, "walking_left", 5 );
	allAnimations[WALKING_RIGHT] = new Animation( screen1, playerName, "walking_right", 5 );

	jumping = false;
	falling = false;
	moveState = IDLE_STANDING_RIGHT;

	surface = allAnimations[moveState]->getCurrentSDL_Surface();

	gameFrameCount = 0;
	moveSpeed = 0;
	onLedge = false;
	jumpSpeed = 20;
	life = MAX_LIFE;
	invincibleAfterBeingHit = false;
	invincibleAfterHitCount = 0;
	hasCandyCane = false;
}

// Split-screen Player constructor.
Player::Player(	int inX,
				int inY, 
				int inWidth, 
				int inHeight,
				int inGroundLevel,
				char playerName[],
				SDL_Surface * inScreen1,
				SDL_Surface * inScreen2 ) {

	x = inX;
	y = inY;
	width = inWidth;
	height = inHeight;
	groundLevel = inGroundLevel;
	screen1 = inScreen1;
	screen2 = inScreen2;

	allAnimations[IDLE_STANDING_LEFT] = new Animation( screen1, playerName, "idle_standing_left", 1 );
	allAnimations[IDLE_STANDING_RIGHT] = new Animation( screen1, playerName, "idle_standing_right", 1 );
	allAnimations[IDLE_CROUCHING] = new Animation( screen1, playerName, "idle_crouching", 1 );
	allAnimations[WALKING_LEFT] = new Animation( screen1, playerName, "walking_left", 5 );
	allAnimations[WALKING_RIGHT] = new Animation( screen1, playerName, "walking_right", 5 );

	jumping = false;
	falling = false;
	moveState = IDLE_STANDING_RIGHT;
	jumpHeight = 0;

	surface = allAnimations[moveState]->getCurrentSDL_Surface();

	gameFrameCount = 0;
	moveSpeed = 0;
	onLedge = false;
	life = 100;
	invincibleAfterBeingHit = false;
	invincibleAfterHitCount = 0;
}

void Player::resetForNewLevel() {

	x = 100;

	jumping = false;
	falling = true;
	moveState = IDLE_STANDING_RIGHT;

	surface = allAnimations[moveState]->getCurrentSDL_Surface();

	gameFrameCount = 0;
	moveSpeed = 0;
	onLedge = false;
	invincibleAfterBeingHit = false;
	invincibleAfterHitCount = 0;
	hasCandyCane = false;
}

// Destructor
void Player::deallocate() {

	for (int i = 0; i < NUM_PLAYER_ANIMATIONS; i++) {
		delete allAnimations[i];
	}
}

// Destructor.  Overridden because of the dynamic allocation done during
// construction.  Should not be explicitly called during the program, but
// is necessary anyway.
Player::~Player() {

	deallocate();

}

// Throw Candy Cane
void Player::throwCandyCane() {
	if (hasCandyCane) {
		if (	moveState == IDLE_STANDING_RIGHT
			||	moveState == WALKING_RIGHT ) {
			candyCane->throwCandyCane(CANDY_CANE_THROW_SPEED);

		} else if (	moveState == IDLE_STANDING_LEFT
			||	moveState == WALKING_LEFT ) {
			candyCane->throwCandyCane(-CANDY_CANE_THROW_SPEED);
		}
		candyCane->setAttachedToPlayer(false);
		candyCane->setDeadly(true);
		hasCandyCane = false;
	}
}

// Getters
bool Player::getJumping() { return jumping; }
bool Player::getFalling() { return falling; }
int Player::getMoveState() { return moveState; }
int Player::getJumpHeight() { return jumpHeight; }
int Player::getMoveSpeed() { return moveSpeed; }
bool Player::getOnLedge() { return onLedge; }
int Player::getLife() { return life; }
bool Player::getInvincibleAfterBeingHit() { return invincibleAfterBeingHit; }
bool Player::getHasCandyCane() { return hasCandyCane; }
int Player::getYSpeed() { return ySpeed; }
int Player::getMaxLife() { return MAX_LIFE; }
int Player::getName() { return name; }

// Setters
void Player::setLife(int inLife) { life = inLife; }
void Player::setJumping(bool inJumping) { jumping = inJumping; }
void Player::setFalling(bool inFalling) { falling = inFalling; }
void Player::setJumpHeight(int inJumpHeight) { jumpHeight = inJumpHeight; }
void Player::changeMoveSpeed(int changeMoveSpeed) { moveSpeed += changeMoveSpeed; }
void Player::setOnLedge(bool inOnLedge) { onLedge = inOnLedge; }
void Player::changeLife(int changeLife) { life += changeLife; }
void Player::setYSpeed(int inYSpeed) { ySpeed = inYSpeed; }
void Player::setInvincibleAfterBeingHit() { invincibleAfterBeingHit = true;
											invincibleAfterHitCount = INVINCIBLE_AFTER_HIT_COUNT; }
void Player::setHasCandyCane(bool inHasCandyCane) { hasCandyCane = inHasCandyCane; }

void Player::pickUpCandyCane(CandyCane * inCandyCane) {
	candyCane = inCandyCane;
	candyCane->setAttachedToPlayer(true);
	candyCane->setReturnToPlayer(false);
	candyCane->setDeadly(false);
	hasCandyCane = true;
}

void Player::setMoveState(int inMoveState) {
	allAnimations[moveState]->setCurrentFrame(0);
	moveState = inMoveState;
}

// Update player positions
void Player::update() {

	if (invincibleAfterBeingHit) {
		invincibleAfterHitCount--;

		if (invincibleAfterHitCount == 0) {
			invincibleAfterBeingHit = false;
		}
	}
		
	Entity::changeX(moveSpeed);

	if (hasCandyCane) {
		if (moveSpeed < 0 || moveState == IDLE_STANDING_LEFT) {
			candyCane->setX(x);
		} else {
			candyCane->setX(x + 50); 
		}
		candyCane->setY(y + height/2 - candyCane->getHeight() );
	}
	moveSpeed = 0;

	switch (moveState) {

		case IDLE_STANDING_LEFT :
							break;

		case IDLE_STANDING_RIGHT :
							break;

		case IDLE_CROUCHING :
							break;

		case WALKING_LEFT :
							break;

		case WALKING_RIGHT :
							break;

	}

	gameFrameCount++;
	if (gameFrameCount == GAME_FRAMES_PER_ANIM_FRAME) {
		allAnimations[moveState]->advanceFrame();
		gameFrameCount = 0;
	}

	surface = allAnimations[moveState]->getCurrentSDL_Surface();
	if (y + height != groundLevel) {
		ySpeed -= 1;
		y -= ySpeed;
		if (ySpeed > 0) falling = true;
	}
	if (y + height >= groundLevel) {
		ySpeed = 0;
		y = groundLevel - height;
		falling = false;
	}
}

// Jump
void Player::jump(int inJumpHeight) {
	y -= 1; // stupid hack. poorly coded.
	ySpeed = jumpSpeed;
}

