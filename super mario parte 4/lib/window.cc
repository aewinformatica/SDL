/*
 * window.cc
 *
 *  Created on: 13/10/2011
 *      Author: sergio
 */

#include "window.h"

Window::Window(std::string title, int width, int height, int bpp) {
	this->title = title;
	this->width = width;
	this->height = height;
	this->bbp = bpp;
	init();
}

void Window::clear(char r, char g, char b) {
	SDL_FillRect(this->screen, NULL, SDL_MapRGB(this->screen->format, r, g, b));
}

void Window::show() {
	SDL_Flip(this->screen);
}

SDL_Surface* Window::getScreen() {
	return this->screen;
}

void Window::init() {
	if (SDL_Init(SDL_INIT_VIDEO)==-1) {
		fprintf(stderr, "Error: %s\n", SDL_GetError());
		exit(1);
	}

	this->screen = SDL_SetVideoMode(this->width, this->height, this->bbp, SDL_SWSURFACE);

	if (screen == NULL) {
		fprintf(stderr, "Error: %s\n", SDL_GetError());
		exit(1);
	}
	SDL_WM_SetCaption(this->title.c_str(), NULL);
}

Window::~Window() {
	SDL_FreeSurface(this->screen);
	SDL_Quit();
}
