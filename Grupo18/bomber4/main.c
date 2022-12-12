#include "global.h"
#include "prototipos.h"


int main(int argc, char** argv)
{
	
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER); //INICIALIZA A SDL
    screen = SDL_SetVideoMode(SCREEN_W, SCREEN_H, 32, SDL_SWSURFACE);
	controlador = 1;

	f_introducao();

	f_menu();
	
	return 0;
}
