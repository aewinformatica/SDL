/*
 * staticimage.cc
 *
 *  Created on: 16/10/2011
 *      Author: sergiosvieira
 */

#include "staticimage.h"

StaticImage::StaticImage(std::string filename, Sint16 x, Sint16 y, Uint8 z) {
	this->offset.x = x;
	this->offset.y = y;
	this->z = z;
	this->load_image(filename);
}


void StaticImage::show(SDL_Surface* screen) {
	SDL_BlitSurface(this->image, NULL, screen, &this->offset);
}

void StaticImage::setPos(Sint16 x, Sint16 y) {
	this->offset.x = x;
	this->offset.y = y;
}

SDL_Rect* StaticImage::getRect() {
	return &this->offset;
}

void StaticImage::load_image(std::string filename) {
	SDL_Surface* tmp = SDL_LoadBMP(filename.c_str());

	if (tmp == NULL) {
		fprintf(stderr, "Error: %s\n", SDL_GetError());
		exit(1);
	}
	this->image = SDL_DisplayFormat(tmp);
	SDL_SetColorKey(this->image, SDL_SRCCOLORKEY, SDL_MapRGB(this->image->format, 0xff, 0, 0xff));
	SDL_FreeSurface(tmp);
}


StaticImage::~StaticImage() {
	SDL_FreeSurface(this->image);
}

