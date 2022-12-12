
/*
	Arquivo: ex1.c
	Autor: Bruno Bottino Ferreira

	Exemplifica carregamento de imagens e blits
*/

#include <SDL.h> //usaremos funcoes da SDL
#include <SDL_image.h> //e SDL_image

#define SCREEN_W 640 //tamanho da janela que sera criada
#define SCREEN_H 480

#define ERRO -1

int main(int argc, char** argv) //funcao de entrada
{
    SDL_Surface* screen; //superficie que representa a tela do computador
    SDL_Event event; //um evento enviado pela SDL
    int quit = 0; //devemos encerrar o programa?

	SDL_Surface* my_surfbmp; //superficie que sera carregada de um BMP
	SDL_Surface* my_surfpng; //superficie que sera carregada de um PNG
	SDL_Rect dst_rectbmp = {50, 50, 0, 0}; //destino do blit da superficie BMP (w, h sao ignorados)
	SDL_Rect dst_rectpng = {300, 50, 0, 0}; //destino do blit da superficie BMP (w, h sao ignorados)

    //inicializar a SDL
 	if (-1 == SDL_Init(SDL_INIT_VIDEO))
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
	my_surfbmp = SDL_LoadBMP("pic1.bmp");
	if (!my_surfbmp)
	{
		printf("Nao consegui carregar imagem pic1.bmp\n");
		exit(ERRO);
	}	
	
	my_surfpng = IMG_Load("pic2.png");
	if (!my_surfpng)
	{
		printf("Nao consegui carregar imagem pic2.bmp\n");
		exit(ERRO);
	}

	//copiar as imagens para a tela
	if (-1 == SDL_BlitSurface(my_surfbmp, NULL, screen, &dst_rectbmp))
	{
		printf("Nao consegui blit. SDL error=%s\n", SDL_GetError());
		exit(ERRO);
	}
	if (-1 == SDL_BlitSurface(my_surfpng, NULL, screen, &dst_rectpng))
	{
		printf("Nao consegui blit. SDL error=%s\n", SDL_GetError());
		exit(ERRO);
	}
    
	while(!quit) //rodar enquanto nao for para encerrar :)
    {
		while(SDL_PollEvent(&event)) //checar eventos
		{
			if(event.type == SDL_QUIT) //fechar a janela?
			{
				quit = 1; //sair do loop principal				
			}
		}
		if (-1 == SDL_Flip(screen)) //atualizar a tela
		{
			printf("Nao consegui fazer flip. SDL error=%s\n", SDL_GetError());
		}

	}

    SDL_Quit(); //encerrar a SDL

    return 0;
}
