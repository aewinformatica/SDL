#include "meuinclude.h"

int main (int argc, char *argv[])
{
	SDL_Surface *screen;
	jogo.pontos=00;
	int fases=0;

	SDL_Init(SDL_INIT_EVERYTHING);
	if (Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 1024) < 0)  return -3;
	if(TTF_Init() == -1) return -1;

	Mix_AllocateChannels(16);

	screen=SDL_SetVideoMode(SCREEN_W,SCREEN_H,16,SDL_DOUBLEBUF|SDL_SWSURFACE);
	do {
		menu(screen);
		tempo_total=SDL_GetTicks();
		fases=Jogo(screen);
	} while(fases==666);




	return 0;
}
