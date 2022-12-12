// GUI.h

#ifndef GUI_H

#define GUI_H

#include "General.h"

#define GUI_START_X		25
#define GUI_START_Y		25

class GUI {

	public:

	/*
	 *       Special Functions.
	 *
	 */

	// No-arg constructor
	GUI();

	// Single-screen constructor
	GUI(	Player * inPlayer,
			SDL_Surface * inScreen1 );

	// Split-screen constructor
	GUI(	Player * inPlayer1,
			Player * inPlayer2,
			SDL_Surface * inScreen1,
			SDL_Surface * inScreen2 );

	// Copy constructor.  Necessarily overridden because construction involves
	// dynamic allocation.  Should not need to be used during the lab, but is
	// included for completeness.
	GUI(const GUI & t);

	// Destructor.  Overridden because of the dynamic allocation done during
	// construction.  Should not be explicitly called during the program, but
	// is necessary anyway.
	~GUI();

	// Assignment operator overload.  Necessary due to dynamic allocation.
	// Should not be needed during this lab, but is included for completeness.
	GUI & operator=(const GUI & t);

	void displaySingleScreen(Player * player);
	void displaySplitScreen();

	// Getters
	
	// Setters

	protected:
		Player * player1;
		Player * player2;

		SDL_Surface * screen1;
		SDL_Surface * screen2;;

		SDL_Rect rect;
		SDL_Surface * surface;

		Tile * lifeBar;

	private:

		// Helper function to copy grid and map from existing GUI.
		// Used by both copy constructor and assignment operator.
		virtual void copy(const GUI & t);

		// Helper function to deallocate space from a existing GUI.
		// Used by both assignment operator and destructor.
		virtual void deallocate();

};

#endif
