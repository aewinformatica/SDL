// BadGuyBoss.h

#ifndef BadGuyBoss_H

#define BadGuyBoss_H

#include "BadGuy.h"

class BadGuyBoss : public BadGuy {

	public:

	/*
	 *       Special Functions.
	 *
	 */

	// Single-screen constructor
	BadGuyBoss(	int inX,
			int inY, 
			int inWidth, 
			int inHeight,
			int inGroundLevel,
			SDL_Surface * inScreen1 );

	// Destructor.  Overridden because of the dynamic allocation done during
	// construction.  Should not be explicitly called during the program, but
	// is necessary anyway.
	~BadGuyBoss();

	protected:

	private:
};

#endif
