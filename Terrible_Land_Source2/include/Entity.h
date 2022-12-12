// Entity.h

#ifndef Entity_H

#define Entity_H

#include "SDL.h"

class Entity {

	public:

	/*
	 *       Special Functions.
	 *
	 */

	// No-arg constructor
	Entity();

	// Single-screen constructor
	Entity(	int inX,
			int inY, 
			int inWidth, 
			int inHeight,
			char image[],
			SDL_Surface * inScreen1 );

	// Split-screen constructor
	Entity(	int inX,
			int inY, 
			int inWidth, 
			int inHeight,
			char image[],
			SDL_Surface * inScreen1,
			SDL_Surface * inScreen2 );

	// Copy constructor.  Necessarily overridden because construction involves
	// dynamic allocation.  Should not need to be used during the lab, but is
	// included for completeness.
	Entity(const Entity & t);

	// Destructor.  Overridden because of the dynamic allocation done during
	// construction.  Should not be explicitly called during the program, but
	// is necessary anyway.
	~Entity();

	// Assignment operator overload.  Necessary due to dynamic allocation.
	// Should not be needed during this lab, but is included for completeness.
	Entity & operator=(const Entity & t);

	virtual void displaySingleScreen();
	virtual void displaySplitScreen();

	// Getters
	virtual int getX();
	virtual int getY();
	virtual int getXSpeed();
	virtual int getYSpeed();
	virtual int getWidth();
	virtual int getHeight();
	virtual int getGroundLevel();
	virtual SDL_Rect getRect();

	// Setters
	virtual void setX(int inX);
	virtual void setY(int inY);
	virtual void setWidth(int inWidth);
	virtual void setHeight(int inHeight);
	virtual void setGroundLevel(int inGroundLevel);
	virtual void setRect(SDL_Rect & inRect);

	virtual void changeX(int changeX);
	virtual void changeY(int changeY);

	protected:
		int width, height;
		int groundLevel;
		int jumpSpeed;
		int x, y;
		int xSpeed, ySpeed;

		SDL_Surface * screen1;
		SDL_Surface * screen2;
		SDL_Rect rect;
		SDL_Surface * surface;

	private:

		// Helper function to copy grid and map from existing Entity.
		// Used by both copy constructor and assignment operator.
		virtual void copy(const Entity & t);

		// Helper function to deallocate space from a existing Entity.
		// Used by both assignment operator and destructor.
		virtual void deallocate();

};

#endif
