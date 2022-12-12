// BadGuy.h

#ifndef BadGuy_H

#define BadGuy_H

#include "Entity.h"
#include "Animation.h"
#include "Player.h"
#include <math.h>

#define NUM_BAD_GUY_ANIMATIONS	4
#define BAD_GUY_JUMP_SPEED		5
#define ATTACK_DISTANCE		  150
#define BAD_GUY_HUSTLE        200

#define BAD_GUY_ATTACK_SPEED    2
#define BAD_GUY_JUMP_HEIGHT    30
#define BAD_GUY_WALK_SPEED      1

#define BAD_GUY_ATTACKING_LEFT          0
#define BAD_GUY_ATTACKING_RIGHT         1
#define BAD_GUY_WALKING_LEFT            2
#define BAD_GUY_WALKING_RIGHT           3

#define BAD_GUY_GAME_FRAMES_PER_ANIM_FRAME      12

class BadGuy : public Entity {

	public:

	/*
	 *       Special Functions.
	 *
	 */

	// No-arg constructor
	BadGuy();

	// Single-screen constructor
	BadGuy(	int inX,
			int inY, 
			int inWidth, 
			int inHeight,
			int inGroundLevel,
			SDL_Surface * inScreen1 );

	// Split-screen constructor
	BadGuy(	int inX,
			int inY, 
			int inWidth, 
			int inHeight,
			int inGroundLevel,
			SDL_Surface * inScreen1,
			SDL_Surface * inScreen2 );

	// Destructor.  Overridden because of the dynamic allocation done during
	// construction.  Should not be explicitly called during the program, but
	// is necessary anyway.
	~BadGuy();

	void jump(int inJumpHeight);
	void update(Player * player);

	// Getters
	bool getJumping();
	bool getFalling();
	int getMoveState();
	int getJumpHeight();
	bool getOnLedge();
	bool getDead();
	int getLife();

	// Setters
	void setJumping(bool inJumping);
	void setFalling(bool inFalling);
	void setMoveState(int inMoveState);
	void setJumpHeight(int inJumpHeight);
	void setOnLedge(bool inOnLedge);
	void setDead(bool inDead);
	void setLife(int inLife);
	void changeLife(int change);

	protected:
		bool jumping;
		bool falling;
		int moveState;
		int jumpHeight;
		Animation * allAnimations[NUM_BAD_GUY_ANIMATIONS];
		bool onLedge;
		bool attacking;
		int badGuyFrameCount;
		int badGuyHustlePosition;
		int badGuyHustleDirection;
		bool dead;
		int life;

	private:

		// Helper function to deallocate space from a existing Entity.
		// Used by both assignment operator and destructor.
		void deallocate();
};

#endif
