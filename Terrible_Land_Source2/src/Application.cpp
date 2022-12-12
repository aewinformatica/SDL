/**************************************************************************

     APPLICATION FOR RUNNING GAMES CREATED WITH TERRIBLE_LAND
                           2D GAME ENGINE

**************************************************************************/

#include "SDL.h"
#include "../include/Game.h"

int main(int argc, char* argv[])
{
	SDL_Event event;

	/* initialize video system */
	SDL_Init(SDL_INIT_VIDEO);

	/* set the title bar */
	SDL_WM_SetCaption("Adventures in terrible land!!!", "SDL Move");

	/* create window */
	SDL_Surface * screen1;
	screen1 = SDL_SetVideoMode(	SCREEN_WIDTH,
								SCREEN_HEIGHT, 
								0,  
										SDL_FULLSCREEN
									//	SDL_RESIZABLE
									//|	SDL_DOUBLEBUF
									//|	SDL_ANYFORMAT
							 );
/*
	SDL_Surface * screen2;
	screen2 = SDL_SetVideoMode(	SCREEN_WIDTH * 2,
								SCREEN_HEIGHT, 
								0,  
									//	SDL_FULLSCREEN
										SDL_RESIZABLE
									|	SDL_DOUBLEBUF
									|	SDL_ANYFORMAT
							 );
*/
	int exitApplication = 0;
	double startTime = SDL_GetTicks();

	Game game = Game(screen1);
	//Game game = Game(screen1, screen2);

	// Hide cursor
	SDL_ShowCursor(1);

	/* message pump */
	while (!exitApplication)
	{
		/* look for an event */
		if (SDL_PollEvent(&event)) {
			/* an event was found */
			switch (event.type) {
				/* close button clicked */
				case SDL_QUIT:
					exitApplication = 1;
					break;

				/* handle the keyboard */
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym) {

						case SDLK_ESCAPE:
							if (game.getDisplayAbout() || game.getDisplayYouWon() ) {
								game.setDisplayAbout(false);
								game.setDisplayYouWon(false);
								break;
							}
							if (game.getLevelNumber() != 0) {
								game.setLevel(0);
							} else {
								exitApplication = 1;
							}
							break;
					}
					break;

				// If the mouse button has been pressed
				case SDL_MOUSEBUTTONDOWN:
					game.setMouseButtonDown(true);
					break;
			}
		}

		if ( SDL_GetTicks() - startTime > TIME_DELAY ) {

			startTime = SDL_GetTicks();

			switch (game.runGameLoop() ) {
				// deal with game error
				// NOTE: Error-handling is for the weak
				
				case (-1) :  // error
							break;

				case (0) :	exitApplication = 1;
							break;

				case (1) :	// run game loop again
							break;

				default :	exitApplication = 1;
			}
		}
	}

	/* clean up */
	SDL_Quit();

	return 0;
}
