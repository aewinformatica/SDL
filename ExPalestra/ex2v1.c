
/*
	Arquivo: ex2.c
	Autor: Bruno Bottino Ferreira

	Exemplifica transparências
*/

#include <SDL.h> //usaremos funcoes da SDL
#include <SDL_image.h> //e SDL_image

#define SCREEN_W 640 //tamanho da janela que sera criada
#define SCREEN_H 480

typedef struct _OBJETO
{
	SDL_Surface *imagem;
	SDL_Rect posicao;
	int incx, incy;
} OBJETO;


void update_positions(OBJETO *b)
{
	
	//atualizar a superficie BMP
	b->posicao.x += b->incx;
	b->posicao.y += b->incy;
	if((b->posicao.x > (SCREEN_W - b->imagem->w)) || (b->posicao.x < 0)) b->incx = -b->incx;
	if((b->posicao.y > (SCREEN_H - b->imagem->h)) || (b->posicao.y < 0)) b->incy = -b->incy;
}

int main(int argc, char** argv) //funcao de entrada
{
    SDL_Surface* screen; //superficie que representa a tela do computador
    SDL_Event event; //um evento enviado pela SDL
    int quit = 0; //devemos encerrar o programa?    
	//SDL_Color cor_fundo;
	Uint32 cor_fundo;

	OBJETO bmp, png, alpha;

    SDL_Init(SDL_INIT_VIDEO); //inicializar a SDL
    screen = SDL_SetVideoMode(SCREEN_W, SCREEN_H, 16, SDL_SWSURFACE); //criar uma janela 640x480x16bits

	bmp.imagem = SDL_LoadBMP("pic3.bmp"); //quadro rosa, transparencia sera setada
	png.imagem = IMG_Load("pic4.png"); //quadro cinza, transparencia guardada no arquivo
	alpha.imagem = IMG_Load("pic5.gif"); //computador, transparencia guardada no arquivo + geral sera setada

	//setar a transparência do arquivo carregado do BMP
	SDL_SetColorKey(bmp.imagem, SDL_SRCCOLORKEY, SDL_MapRGB(bmp.imagem->format, 255, 0, 255));
	
	//setar a transparência geral da superficie alpha
	SDL_SetAlpha(alpha.imagem, SDL_SRCALPHA, 128);

	// preparar uma cor para o fundo
	cor_fundo = SDL_MapRGB(screen->format, 5, 50, 100);

	// coloca imagens nas posicoes iniciais
	bmp.posicao.x = 70; //destino do blit da superficie BMP (w, h sao ignorados)
	bmp.posicao.y = 30;

	png.posicao.x = 250;
	png.posicao.y = 100; //destino do blit da superficie BMP (w, h sao ignorados)

	alpha.posicao.x = 250;
	alpha.posicao.x = 250; //destino do blit da superficie com alpha (w, h sao ignorados)

	// inicia velocidades das imagens
	bmp.incx = 1; bmp.incy = 1;
	png.incx = 1; png.incy = -1;
	alpha.incx = -1; alpha.incy = 1;


    while(!quit) //rodar enquanto nao for para encerrar :)
    {
		while(SDL_PollEvent(&event)) //checar eventos
		{
			if(event.type == SDL_QUIT) //fechar a janela?
			{
				quit = 1; //sair do loop principal
			}
		}
		//pequena animacao
		update_positions(&bmp);
		update_positions(&png);
		update_positions(&alpha);
		
		//limpar a tela
		SDL_FillRect(screen, NULL, cor_fundo);

		//copiar as imagens
		SDL_BlitSurface(bmp.imagem, NULL, screen, &bmp.posicao);
		SDL_BlitSurface(png.imagem, NULL, screen, &png.posicao);
		SDL_BlitSurface(alpha.imagem, NULL, screen, &alpha.posicao);

		SDL_Flip(screen); //atualizar a tela
	}

    SDL_Quit(); //encerrar a SDL

    return 0;
}
