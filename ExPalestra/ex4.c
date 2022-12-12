/*
	Arquivo: ex4.c
	Autor: Bruno Bottino Ferreira

	Exemplifica leitura do mouse
*/

#include <SDL.h> //usaremos funcoes da SDL
#include <SDL_image.h> //e SDL_image

#define SCREEN_W 640 //tamanho da janela que sera criada
#define SCREEN_H 480
#define ERRO -1

SDL_Surface* my_surf; //superficie que sera movimentada pelo teclado
SDL_Rect dst_rect = {100, 100, 0, 0}; //destino da copia

int mouse_pressed = 0;

int main(int argc, char** argv) //funcao de entrada
{
    SDL_Surface* screen; //superficie que representa a tela do computador
    SDL_Event event; //um evento enviado pela SDL
    int quit = 0; //devemos encerrar o programa?

    if (-1 == SDL_Init(SDL_INIT_VIDEO)) //inicializar a SDL
    {
		printf("Nao consegui inicializar. SDL error=%s\n", SDL_GetError());
		exit(ERRO);
	}
	
	screen = SDL_SetVideoMode(SCREEN_W, SCREEN_H, 16, SDL_SWSURFACE); //criar uma janela 640x480x16bits
	if (!screen)	
	{
		printf("Nao consegui iniciar modo de video. SDL error=%s\n", SDL_GetError());
		exit(ERRO);
	}	

	//carregar as imagens
	my_surf = IMG_Load("sdl.png");
	if (!my_surf)
	{		
		printf("Nao consegui carregar imagem sdl.png\n");
		exit(ERRO);
	}	

    while(!quit) //rodar enquanto nao for para encerrar :)
    {
		while(SDL_PollEvent(&event)) //checar eventos
		{
			switch(event.type)
			{
				case SDL_QUIT: quit = 1; break;//sair do loop principal
				case SDL_KEYDOWN: if(event.key.keysym.sym == SDLK_ESCAPE) quit = 1; break;
				case SDL_MOUSEMOTION:
					if(mouse_pressed) //atualizar valores
					{
						dst_rect.x += event.motion.xrel;
						dst_rect.y += event.motion.yrel;

						if(dst_rect.x < 0) dst_rect.x = 0;
						if(dst_rect.y < 0) dst_rect.y = 0;
					}
					break;
				case SDL_MOUSEBUTTONDOWN:
					if(event.button.button == SDL_BUTTON_LEFT) mouse_pressed = 1;
					break;
				case SDL_MOUSEBUTTONUP:
					if(event.button.button == SDL_BUTTON_LEFT) mouse_pressed = 0;
					break;
				default: break;
			}
		}

		//limpar a tela
		if (-1 == SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 5, 50, 100)))
   		{
			printf("Nao consegui encher o retangulo. SDL error=%s\n", SDL_GetError());
			exit(ERRO);
		}
		//copiar a imagem para a tela
		if (-1 == SDL_BlitSurface(my_surf, NULL, screen, &dst_rect))
		{
			printf("Sem blit. SDL error=%s\n", SDL_GetError());
			exit(ERRO);
		}
		if (-1 == SDL_Flip(screen)) //atualizar a tela
		{
			printf("Nao consegui fazer flip. SDL error=%s\n", SDL_GetError());
			exit(ERRO);
		}

	}

    SDL_Quit(); //encerrar a SDL

    return 0;
}
