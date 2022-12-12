// Ledge.h

#ifndef Ledge_H

#define Ledge_H

#include "Entity.h"

#define NUM_SDL_ANIMS      2

class Ledge : public Entity {

	public:

	/*
	 *       Special Functions.
	 *
	 */

	// Single-scree constructor
	Ledge(	int inX,
			int inY, 
			int inWidth, 
			int inHeight,
			char image[],
			SDL_Surface * inScreen1,
			bool inMoving );

	// Split-screen constructor
	Ledge(	int inX,
			int inY, 
			int inWidth, 
			int inHeight,
			char image[],
			SDL_Surface * inScreen1,
			SDL_Surface * inScreen2,
			bool inMoving );

	// Getters
	bool getMoving();

	// Setters
	void setMoving(bool inMoving);

	protected:
		bool moving;

	private:

};

#endif
