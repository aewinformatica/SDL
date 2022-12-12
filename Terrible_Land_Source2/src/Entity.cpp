// Entity.cpp

#include "../include/Entity.h"

// No-arg Constructor.  Added so that this is a legal class.
Entity::Entity() {
	x = 0;
	y = 0;
	width = 0;
	height = 0;
	rect.x = x;
	rect.y = y;
}

// Regular Entity constructor.
Entity::Entity(	int inX,
				int inY, 
				int inWidth, 
				int inHeight,
				char image [],
				SDL_Surface * inScreen1 )
{
	x = inX;
	y = inY;
	width = inWidth;
	height = inHeight;
	surface = SDL_LoadBMP(image);
	screen1 = inScreen1;

	int colorkey = SDL_MapRGB(screen1->format, 255, 255, 255);
	SDL_SetColorKey(surface, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
}

// Split-screen constructor
Entity::Entity(	int inX,
				int inY, 
				int inWidth, 
				int inHeight,
				char image[],
				SDL_Surface * inScreen1,
				SDL_Surface * inScreen2 )
{
	x = inX;
	y = inY;
	width = inWidth;
	height = inHeight;
	surface = SDL_LoadBMP(image);
	screen1 = inScreen1;
	screen2 = inScreen2;
}

// Helper function.  Copies attributes of one Entity over to those of this one.
void Entity::copy(const Entity & t) {

	// copy all attributes

}

// Helper function to free all space dynamically allocated for Entity
void Entity::deallocate() {

	SDL_FreeSurface(surface);
	delete surface;
}

// Copy constructor.  Necessarily overridden because construction involves
// dynamic allocation.  Should not need to be used during the lab, but is
// included for completeness.
Entity::Entity(const Entity & t) { copy(t); }

// Destructor.  Overridden because of the dynamic allocation done during
// construction.  Should not be explicitly called during the program, but
// is necessary anyway.
Entity::~Entity() {

	deallocate();

}

// Assignment operator overload.  Necessary due to dynamic allocation.
// Should not be needed during this lab, but is included for completeness.
Entity & Entity::operator=(const Entity & t) {

	// Deallocate space already used by the current object.
	deallocate();

	// Now copy as if this were a brand new Entity object.
	copy(t);

	// Return reference to this object for cascading.
	return *this;

}

void Entity::displaySingleScreen() {

	
	rect.x = x;
	rect.y = y;
	SDL_BlitSurface(surface, NULL, screen1, &rect);
}

void Entity::displaySplitScreen() {

	rect.x = x;
	rect.y = y;
	SDL_BlitSurface(surface, NULL, screen1, &rect);

	rect.x = x + 320;
	SDL_BlitSurface(surface, NULL, screen2, &rect);
}

// Getters
int Entity::getX() { return x; }
int Entity::getY() { return y; }
int Entity::getYSpeed() { return ySpeed; }
int Entity::getXSpeed() { return xSpeed; }
int Entity::getWidth() { return width; }
int Entity::getHeight() { return height; }
int Entity::getGroundLevel() { return groundLevel; }
SDL_Rect Entity::getRect() { return rect; }

// Setters
void Entity::setX(int inX) { x = inX; }
void Entity::setY(int inY) { y = inY; }
void Entity::setWidth(int inWidth) { width = inWidth; }
void Entity::setHeight(int inHeight) { height = inHeight; }
void Entity::setGroundLevel(int inGroundLevel) { groundLevel = inGroundLevel; }
void Entity::setRect(SDL_Rect & inRect) { rect = inRect; }

void Entity::changeX(int changeX) {
	x += changeX;
}
void Entity::changeY(int changeY) {
	y += changeY;
}
