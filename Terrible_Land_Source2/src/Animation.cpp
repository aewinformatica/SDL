// Animation.cpp

#include "../include/Animation.h"

// No-arg Constructor.  Added so that this is a legal class.
Animation::Animation() {

}

// Regular Animation constructor.
Animation::Animation(	SDL_Surface * inScreen1,
						string animSubFolder,
						string animName,
						int inNumFrames )
{	
	screen1 = inScreen1;
	numFrames = inNumFrames;
	frames = new SDL_Surface * [numFrames];

	int colorkey = SDL_MapRGB(screen1->format, 255, 255, 255);
	string imageName;

	char buffer[256];

	for (int i = 0; i < numFrames; i++) {
		imageName = "animations/" + animSubFolder + "/" + animName;
		imageName = imageName + "/" + animSubFolder + "_" + animName + "_" + itoa(i, buffer, 10) + ".bmp";
		frames[i] = SDL_LoadBMP( imageName.c_str() );
		SDL_SetColorKey(frames[i], SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
	}

	currentFrame = 0;
}

// Helper function.  Copies attributes of one Animation over to those of this one.
void Animation::copy(const Animation & t) {

	// copy all attributes

}

// Helper function to free all space dynamically allocated for Animation
void Animation::deallocate() {

	for (int i = 0; i < NUM_FRAMES; i++) {
		SDL_FreeSurface(frames[i]);
	}
}

// Copy constructor.  Necessarily overridden because construction involves
// dynamic allocation.  Should not need to be used during the lab, but is
// included for completeness.
Animation::Animation(const Animation & t) { copy(t); }

// Destructor.  Overridden because of the dynamic allocation done during
// construction.  Should not be explicitly called during the program, but
// is necessary anyway.
Animation::~Animation() {

	deallocate();

}

// Assignment operator overload.  Necessary due to dynamic allocation.
// Should not be needed during this lab, but is included for completeness.
Animation & Animation::operator=(const Animation & t) {

	// Deallocate space already used by the current object.
	deallocate();

	// Now copy as if this were a brand new Animation object.
	copy(t);

	// Return reference to this object for cascading.
	return *this;

}

// Getters
SDL_Surface ** Animation::getFrames() { return frames; }
int Animation::getNumFrames() { return numFrames; }
int Animation::getCurrentFrame() { return currentFrame; }
SDL_Surface * Animation::getCurrentSDL_Surface() { return frames[currentFrame]; }

// Setters
void Animation::setNumFrames(int inNumFrames) { numFrames = inNumFrames; }
void Animation::setCurrentFrame(int inCurrentFrame) { currentFrame = inCurrentFrame; }

// Advance animation one frame forward
void Animation::advanceFrame() {
	if (currentFrame < numFrames - 1) {
		currentFrame++;
	} else {
		currentFrame = 0;
	}
}
