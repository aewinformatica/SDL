/*
 * staticimage.h
 *
 *  Created on: 16/10/2011
 *      Author: sergiosvieira
 */

#ifndef STATICIMAGE_H_
#define STATICIMAGE_H_

#include <iostream>
#include <SDL/SDL.h>

class StaticImage {
protected:
	SDL_Rect offset;
	Uint8 z;
	SDL_Surface* image;
	void load_image(std::string filename);
public:
	StaticImage(std::string filename, Sint16 x, Sint16 y, Uint8 z);
	void show(SDL_Surface* screen);
	void setPos(Sint16 x, Sint16 y);
	SDL_Rect* getRect();
	virtual ~StaticImage();
};

#endif /* STATICIMAGE_H_ */
