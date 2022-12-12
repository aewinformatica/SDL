// Animation.h

#ifndef Animation_H

#define Animation_H

#include "SDL.h"
#include <string>

using std::string;

#define NUM_FRAMES          2

class Animation {

	public:

	/*
	 *       Special Functions.
	 *
	 */

	// No-arg constructor
	Animation();

	// Single-screen constructor
	Animation(	SDL_Surface * inScreen1,
				string animSubFolder,
				string animName,
				int inNumFrames );

	// Copy constructor.  Necessarily overridden because construction involves
	// dynamic allocation.  Should not need to be used during the lab, but is
	// included for completeness.
	Animation(const Animation & t);

	// Destructor.  Overridden because of the dynamic allocation done during
	// construction.  Should not be explicitly called during the program, but
	// is necessary anyway.
	~Animation();

	// Assignment operator overload.  Necessary due to dynamic allocation.
	// Should not be needed during this lab, but is included for completeness.
	Animation & operator=(const Animation & t);

	// Getters
	SDL_Surface ** getFrames();
	int getNumFrames();
	int getCurrentFrame();
	SDL_Surface * Animation::getCurrentSDL_Surface();

	// Setters
	void setNumFrames(int inNumFrames);
	void setCurrentFrame(int inCurrentFrame);

	// Advance animation one frame forward
	void advanceFrame();

	protected:
		SDL_Surface * screen1;
		SDL_Surface ** frames;
		int numFrames;
		int currentFrame;

	private:
		// Helper function to copy grid and map from existing Animation.
		// Used by both copy constructor and assignment operator.
		virtual void copy(const Animation & t);

		// Helper function to deallocate space from a existing Animation.
		// Used by both assignment operator and destructor.
		virtual void deallocate();

};

#endif
