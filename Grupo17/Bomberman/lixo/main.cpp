#include <stdio.h>
#include <string.h>
#include <SDL.h>
#include <SDL_image.h>

int quit = 0;
int i = 0;

#include "menu.h"

//constantes
#define SCREEN_W 680
#define SCREEN_H 520


int main(int argc, char** argv)
{
	SDL_Surface* screen;
	SDL_Surface* fundo;

	SDL_Event event;


	SDL_Init(SDL_INIT_VIDEO);
	screen = SDL_SetVideoMode(SCREEN_W, SCREEN_H, 16, SDL_SWSURFACE);
	SDL_WM_SetCaption("Bomberman!","Bomberman!");
	SDL_Rect dst_rectbomber = {0, 0, 0, 0}; //destino do blit

	while (!quit)
	{
		while(SDL_PollEvent(&event)) // checar eventos
		{
			switch(event.type)
			{
				case SDL_QUIT:
				quit=1;
				break;
            }

            if(!i)
            {
                switch(event.type)
                {

                        case SDL_KEYDOWN:
                            switch(event.key.keysym.sym)
							{
								case SDLK_ESCAPE:
	                            quit = 1;
	                            break;
	                            default:
	                            i = 1;
	                            break;
							}
						default: break;
                }
                fundo = SDL_LoadBMP("imagens/bomber.bmp");
                SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
                SDL_BlitSurface(fundo, NULL, screen, &dst_rectbomber);
                SDL_Flip(screen);
            }
            else if (i != 0 && i!= 3)	menu();
        }
	}

    SDL_Quit();
	return 0;
}
