// Player.h

#ifndef Player_H

#define Player_H

#include "Entity.h"
#include "Animation.h"
#include "CandyCane.h"

#define NUM_PLAYER_ANIMATIONS			5
#define JUMP_SPEED						5
#define INVINCIBLE_AFTER_HIT_COUNT    150
#define CANDY_CANE_THROW_SPEED          5
#define MAX_LIFE					  100

#define IDLE_STANDING_LEFT      0
#define IDLE_STANDING_RIGHT     1
#define IDLE_CROUCHING          2
#define WALKING_LEFT            3
#define WALKING_RIGHT           4
/*
#define IDLE_STANDING_LEFT      1
#define IDLE_STANDING_RIGHT     2
#define IDLE_CROUCHING          3
#define WALKING_LEFT            4
#define WALKING_RIGHT           5
*/
#define PLAYER_HIT_IDLE_STANDING_LEFT      -1
#define PLAYER_HIT_IDLE_STANDING_RIGHT     -2
#define PLAYER_HIT_IDLE_CROUCHING          -3
#define PLAYER_HIT_WALKING_LEFT            -4
#define PLAYER_HIT_WALKING_RIGHT           -5
#define PLAYER_HIT_CROUCHING_MOVING_LEFT   -6
#define PLAYER_HIT_CROUCHING_MOVING_RIGHT  -7
#define PLAYER_HIT_JUMPING_LEFT            -8
#define PLAYER_HIT_JUMPING_RIGHT           -9

#define GAME_FRAMES_PER_ANIM_FRAME    8

class Player : public Entity {

	public:

	/*
	 *       Special Functions.
	 *
	 */

	// No-arg constructor
	Player();

	// Single-screen constructor
	Player(	int inX,
			int inY, 
			int inWidth, 
			int inHeight,
			int inGroundLevel,
			char playerName[],
			int inName,
			SDL_Surface * inScreen1 );

	// Split-screen constructor
	Player(	int inX,
			int inY, 
			int inWidth, 
			int inHeight,
			int inGroundLevel,
			char playerName[],
			SDL_Surface * inScreen1,
			SDL_Surface * inScreen2 );

	// Destructor.  Overridden because of the dynamic allocation done during
	// construction.  Should not be explicitly called during the program, but
	// is necessary anyway.
	~Player();

	void resetForNewLevel();
	void jump(int inJumpHeight);
	void update();
	void throwCandyCane();
	void pickUpCandyCane(CandyCane * inCandyCane);

	// Getters
	bool getJumping();
	bool getFalling();
	int getMoveState();
	int getJumpHeight();
	int getMoveSpeed();
	bool getOnLedge();
	int getLife();
	bool getInvincibleAfterBeingHit();
	bool getHasCandyCane();
	int getYSpeed();
	int getMaxLife();
	int getName();

	// Setters
	void setJumping(bool inJumping);
	void setFalling(bool inFalling);
	void setMoveState(int inMoveState);
	void setJumpHeight(int inJumpHeight);
	void changeMoveSpeed(int changeMoveSpeed);
	void setOnLedge(bool inOnLedge);
	void changeLife(int changeLife);
	void setInvincibleAfterBeingHit();
	void setHasCandyCane(bool inHasCandyCane);
	void setYSpeed(int inYSpeed);
	void setLife(int inLife);

	// Helper function to deallocate space from a existing Entity.
	// Used by both assignment operator and destructor.
	void deallocate();

	protected:
		bool jumping;
		bool falling;
		int moveState;
		int jumpHeight;
		Animation * allAnimations[NUM_PLAYER_ANIMATIONS];
		int moveSpeed;
		bool onLedge;
		int life;
		bool invincibleAfterBeingHit;
		bool hasCandyCane;
		CandyCane * candyCane;
		int name;

	private:
		int gameFrameCount;
		int invincibleAfterHitCount;
};

#endif
