// CandyCane.cpp

#include "../include/CandyCane.h"

// Single-screen CandyCane constructor.
CandyCane::CandyCane(		int inX,
							int inY, 
							int inWidth, 
							int inHeight,
							SDL_Surface * inScreen1 ) {

	x = inX;
	y = inY;
	width = inWidth;
	height = inHeight;
	regularSurface = SDL_LoadBMP("images/candycane.bmp");
	surface = regularSurface;
	screen1 = inScreen1;

	int colorkey = SDL_MapRGB(screen1->format, 255, 255, 255);
	SDL_SetColorKey(regularSurface, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
	SDL_SetColorKey(surface, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);

	attachedToPlayer = false;
	candyCaneThrown = false;
	returnToPlayer = false;
	deadly = false;
	candyCaneFrameCount = 0;

	xSpeed = 0;

	rotating = new Animation( screen1, "CandyCane", "rotating", NUM_ROTATING_FRAMES );
}

// Split-screen CandyCane constructor.
CandyCane::CandyCane(		int inX,
							int inY, 
							int inWidth, 
							int inHeight,
							SDL_Surface * inScreen1,
							SDL_Surface * inScreen2 ) {

	x = inX;
	y = inY;
	width = inWidth;
	height = inHeight;
	surface = SDL_LoadBMP("images/candycane.gif");
	screen1 = inScreen1;
	screen2 = inScreen2;

	int colorkey = SDL_MapRGB(screen1->format, 255, 255, 255);
	SDL_SetColorKey(surface, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
}

// Destructor
void CandyCane::deallocate() {

	delete rotating;
}

// Destructor.  Overridden because of the dynamic allocation done during
// construction.  Should not be explicitly called during the program, but
// is necessary anyway.
CandyCane::~CandyCane() {

	deallocate();

}

void CandyCane::update(int playerX, int playerY) {

	if (candyCaneThrown) {
		x += xSpeed;

	} else if (returnToPlayer) {
		if (x - playerX > 0) {
			if (xSpeed > 0) {
				xSpeed *= -1;
			}
		} else {
			if (xSpeed < 0) {
				xSpeed *= -1;
			}
		}

		x += xSpeed;
	}

	if (deadly) {
		// Advance animation every few frames
		candyCaneFrameCount++;
		if (candyCaneFrameCount == CANDY_CANE_GAME_FRAMES_PER_ANIM_FRAME) {
			rotating->advanceFrame();
			candyCaneFrameCount = 0;
		}
		surface = rotating->getCurrentSDL_Surface();
	} else {
		if (surface != regularSurface) {
			surface = regularSurface;
		}
	}
}

// Getters
bool CandyCane::getAttachedToPlayer() { return attachedToPlayer; }
bool CandyCane::getCandyCaneThrown() { return candyCaneThrown; }
bool CandyCane::getReturnToPlayer() { return returnToPlayer; }
bool CandyCane::getDeadly() { return deadly; }

// Setters
void CandyCane::setAttachedToPlayer(bool inAttachedToPlayer) { attachedToPlayer = inAttachedToPlayer; }
void CandyCane::setCandyCaneThrown(bool inCandyCaneThrown) { candyCaneThrown = inCandyCaneThrown; }
void CandyCane::setReturnToPlayer(bool inReturnToPlayer) { returnToPlayer = inReturnToPlayer; }
void CandyCane::setDeadly(bool inDeadly) { deadly = inDeadly; }

void CandyCane::throwCandyCane(int inXSpeed) {
	candyCaneThrown = true; 
	xSpeed = inXSpeed;
}
