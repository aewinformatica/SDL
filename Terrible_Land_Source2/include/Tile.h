// Tile.h

#ifndef Tile_H

#define Tile_H

#include "Entity.h"

#define NUM_SDL_ANIMS      2

class Tile : public Entity {

	public:

	/*
	 *       Special Functions.
	 *
	 */

	// Single-scree constructor
	Tile(	int inStartX,
			int inEndX,
			int inStartY,
			int inEndY,
			int inWidth, 
			int inHeight,
			char image[],
			SDL_Surface * inScreen1 );

	// Split-scree constructor
	Tile(	int inStartX,
			int inEndX,
			int inStartY,
			int inEndY,
			int inWidth, 
			int inHeight,
			char image[],
			SDL_Surface * inScreen1,
			SDL_Surface * inScreen2 );

	// Getters
	int getEndX();
	int getEndY();

	// Setters
	void setEndX(int inEndX);
	void setEndY(int inEndY);

	void changeX(int changeX);
	void changeY(int changeY);

	// Display tiles to fill in box defined by coords
	void displaySingleScreen();
	void displaySplitScreen();

	protected:
		int endX, endY;

	private:

};

#endif
