#include <SDL.h>

#define ERRO -1

int main(int argc, char** argv) 
{
    SDL_Surface* screen;
    SDL_Event event;
    int quit = 0;

    if (-1 == SDL_Init(SDL_INIT_VIDEO))
    {
    	printf("Nao consegui inicializar. SDL error=%s\n", SDL_GetError());
  		exit(ERRO);
    }
    
    screen = SDL_SetVideoMode(640, 480, 8, 0);
	if (!screen)
	{
		printf("Nao consegui iniciar modo de video. SDL error=%s\n", SDL_GetError());
  		exit(ERRO);
	}

    while(!quit) 
    {
		while(SDL_PollEvent(&event)) 
		{
			if(event.type == SDL_QUIT)
			{
				quit = 1;
			}
		}
		if (-1 == SDL_Flip(screen))
		{
			printf("Nao consegui fazer flip. SDL error=%s\n", SDL_GetError());
			exit(ERRO);
		}
    }
    
    SDL_Quit();
    return 0;
}
