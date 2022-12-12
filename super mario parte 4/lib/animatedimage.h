/*
 * animatedimage.h
 *
 *  Created on: 20/10/2011
 *      Author: sergiosvieira
 */

#ifndef ANIMATEDIMAGE_H_
#define ANIMATEDIMAGE_H_

#include "staticimage.h"
#include <iostream>
#include <SDL/SDL.h>
#include <vector>


class AnimatedImage: public StaticImage {
protected:
	Uint16 fwidth, fheight;
	double aspeed;
	Uint16 fframe, lframe, tframe, cframe;
	std::vector<SDL_Rect> clip;
	Uint32 start;
public:
	AnimatedImage(std::string filename, Sint16 x, Sint16 y, Uint8 z,
			Uint16 frame_width, Uint16 frame_height, Uint16 current_frame,
			double animated_speed);
	void show(SDL_Surface* screen);
	void setFrame(Uint16 first_frame, Uint16 frame_count);
};

#endif /* ANIMATEDIMAGE_H_ */
