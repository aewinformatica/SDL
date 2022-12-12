// CandyCane.h

#ifndef CandyCane_H

#define CandyCane_H

#include "Entity.h"
#include "Animation.h"

#define NUM_ROTATING_FRAMES      4
#define CANDY_CANE_GAME_FRAMES_PER_ANIM_FRAME        5

class CandyCane : public Entity {

	public:

	/*
	 *       Special Functions.
	 *
	 */

	// Single-screen constructor
	CandyCane(	int inX,
				int inY, 
				int inWidth, 
				int inHeight,
				SDL_Surface * inScreen1 );

	// Split-screen constructor
	CandyCane(	int inX,
				int inY, 
				int inWidth, 
				int inHeight,
				SDL_Surface * inScreen1,
				SDL_Surface * inScreen2 );

	~CandyCane();

	// Throw weapon with a given xSpeed
	void update(int playerX, int playerY);

	// Getters
	bool getAttachedToPlayer();
	bool getCandyCaneThrown();
	bool getReturnToPlayer();
	bool getDeadly();

	// Setters
	void setAttachedToPlayer(bool inAttachedToPlayer);
	void setCandyCaneThrown(bool inCandyCaneThrown);
	void setReturnToPlayer(bool inReturnToPlayer);
	void setDeadly(bool inDeadly);

	void throwCandyCane(int inXSpeed);

	protected:
		bool attachedToPlayer;
		bool candyCaneThrown;
		int xSpeed;
		bool returnToPlayer;
		bool deadly;
		Animation * rotating;
		SDL_Surface * regularSurface;
		int candyCaneFrameCount;

	private:
		void deallocate();

};

#endif
