// GUI.cpp

#include "../include/GUI.h"

// Single-screen constructor
GUI::GUI(	Player * player,
			SDL_Surface * inScreen1 ) {

	screen1 = inScreen1;

	rect.x = GUI_START_X;
	rect.y = GUI_START_Y;

	lifeBar = new Tile(GUI_START_X, player->getLife(), GUI_START_Y, 32, 2, 32, "Images/lifebar.bmp", screen1);
}

// Split-screen constructor
GUI::GUI(	Player * inPlayer1,
			Player * inPlayer2,
			SDL_Surface * inScreen1,
			SDL_Surface * inScreen2 ) {

	player1 = inPlayer1;
	player2 = inPlayer2;
	screen1 = inScreen1;
	screen2 = inScreen2;

	surface = SDL_LoadBMP("Images/lifebar.bmp");
	
	rect.x = GUI_START_X;
}

// Helper function.  Copies attributes of one GUI over to those of this one.
void GUI::copy(const GUI & t) {

	// copy all attributes

}

// Helper function to free all space dynamically allocated for GUI
void GUI::deallocate() {

	// Remove lifeBar tile?
	SDL_FreeSurface(surface);
	delete surface;
}

// Copy constructor.  Necessarily overridden because construction involves
// dynamic allocation.  Should not need to be used during the lab, but is
// included for completeness.
GUI::GUI(const GUI & t) { copy(t); }

// Destructor.  Overridden because of the dynamic allocation done during
// construction.  Should not be explicitly called during the program, but
// is necessary anyway.
GUI::~GUI() {

	deallocate();

}

// Assignment operator overload.  Necessary due to dynamic allocation.
// Should not be needed during this lab, but is included for completeness.
GUI & GUI::operator=(const GUI & t) {

	// Deallocate space already used by the current object.
	deallocate();

	// Now copy as if this were a brand new GUI object.
	copy(t);

	// Return reference to this object for cascading.
	return *this;

}

void GUI::displaySingleScreen(Player * player) {

	// draw lifebar in loop for player life
	lifeBar->setEndX(player->getLife() * 2);
	lifeBar->displaySingleScreen();
}

void GUI::displaySplitScreen() {
	// should not be changing, so no need to re-assign rect.coords
	rect.x = 0;
	rect.w = player1->getLife() * 2;
	SDL_BlitSurface(surface, NULL, screen1, &rect);
	
	rect.x = 320;
	rect.w = player2->getLife() * 2;
	SDL_BlitSurface(surface, NULL, screen2, &rect);
}

// Getters

// Setters
