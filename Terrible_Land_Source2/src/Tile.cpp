// Tile.cpp

#include "../include/Tile.h"

// Single-screen Entity constructor.
Tile::Tile(		int inX,
				int inEndX,
				int inY,
				int inEndY,
				int inWidth,
				int inHeight,
				char image [],
				SDL_Surface * inScreen1 ) {

	x = inX;
	endX = inEndX;
	y = inY;
	endY = inEndY;
	width = inWidth;
	height = inHeight;
	surface = SDL_LoadBMP(image);
	screen1 = inScreen1;
}

// Single-screen Entity constructor.
Tile::Tile(		int inX,
				int inEndX,
				int inY,
				int inEndY,
				int inWidth,
				int inHeight,
				char image [],
				SDL_Surface * inScreen1,
				SDL_Surface * inScreen2 ) {

	x = inX;
	endX = inEndX;
	y = inY;
	endY = inEndY;
	width = inWidth;
	height = inHeight;
	surface = SDL_LoadBMP(image);
	screen1 = inScreen1;
	screen2 = inScreen2;
}

// Getters
int Tile::getEndX() { return endX; }
int Tile::getEndY() { return endY; }

// Setters
void Tile::setEndX(int inEndX) { endX = inEndX; }
void Tile::setEndY(int inEndY) { endY = inEndY; }

void Tile::changeX(int changeX) {
	x = (x + changeX)%width - width;
}
void Tile::changeY(int changeY) {
	y = (y + changeY)%height - height;
}

// Display tiles to fill in box defined by coords single-screen
void Tile::displaySingleScreen() {
	for (int row = x; row < endX; row+=width) {
		for (int col = y; col < endY; col+=height) {
			rect.x = row;
			rect.y = col;
			SDL_BlitSurface(surface, NULL, screen1, &rect);
		}
	}
}

// Display tiles to fill in box defined by coords split-screen
void Tile::displaySplitScreen() {

	for (int row = x; row < endX; row+=width) {
		for (int col = y; col < endY; col+=height) {
			rect.x = row;
			rect.y = col;
			SDL_BlitSurface(surface, NULL, screen1, &rect);

			rect.x += 320;
			SDL_BlitSurface(surface, NULL, screen2, &rect);
		}
	}
}
