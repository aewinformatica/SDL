// Tree.cpp

#include "../include/Tree.h"

// Single-screen Tree constructor.
Tree::Tree(		int inX,
				int inY, 
				int inWidth, 
				int inHeight,
				char image [],
				SDL_Surface * inScreen1 ) {

	x = inX;
	y = inY;
	width = inWidth;
	height = inHeight;
	surface = SDL_LoadBMP(image);
	screen1 = inScreen1;

	int colorkey = SDL_MapRGB(screen1->format, 255, 255, 255);
	SDL_SetColorKey(surface, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
}

// Split-screen Tree constructor.
Tree::Tree(		int inX,
				int inY, 
				int inWidth, 
				int inHeight,
				char image [],
				SDL_Surface * inScreen1,
				SDL_Surface * inScreen2 ) {

	x = inX;
	y = inY;
	width = inWidth;
	height = inHeight;
	surface = SDL_LoadBMP(image);
	screen1 = inScreen1;
	screen2 = inScreen2;

	int colorkey = SDL_MapRGB(screen1->format, 255, 255, 255);
	SDL_SetColorKey(surface, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
}
