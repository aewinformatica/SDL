// FlyingBadGuy.h

#ifndef FlyingBadGuy_H

#define FlyingBadGuy_H

#include "BadGuy.h"

#define NUM_FLYING_BAD_GUY_ANIMATIONS	4

class FlyingBadGuy : public BadGuy {

	public:

	/*
	 *       Special Functions.
	 *
	 */
	FlyingBadGuy(	int inX,
					int inY, 
					int inWidth, 
					int inHeight,
					int inGroundLevel,
					SDL_Surface * inScreen1 );

	void update(Player * player);

	protected:

	private:
};

#endif
