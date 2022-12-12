// Ledge.cpp

#include "../include/Ledge.h"

// Single-screen Ledge constructor.
Ledge::Ledge(	int inX,
				int inY, 
				int inWidth, 
				int inHeight,
				char image [],
				SDL_Surface * inScreen1,
				bool inMoving ) {

	x = inX;
	y = inY;
	width = inWidth;
	height = inHeight;
	surface = SDL_LoadBMP(image);
	screen1 = inScreen1;
	moving = inMoving;
}

// Single-screen Ledge constructor.
Ledge::Ledge(	int inX,
				int inY, 
				int inWidth, 
				int inHeight,
				char image [],
				SDL_Surface * inScreen1,
				SDL_Surface * inScreen2,
				bool inMoving ) {

	x = inX;
	y = inY;
	width = inWidth;
	height = inHeight;
	surface = SDL_LoadBMP(image);
	screen1 = inScreen1;
	screen2 = inScreen2;
	moving = inMoving;
}

// Getters
bool Ledge::getMoving() { return moving; }

// Setters
void Ledge::setMoving(bool inMoving) { moving = inMoving; }

