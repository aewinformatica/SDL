
/*
	Arquivo: ex2.c
	Autor: Bruno Bottino Ferreira

	Exemplifica transparências
*/

#include <SDL.h> //usaremos funcoes da SDL
#include <SDL_image.h> //e SDL_image

#define SCREEN_W 640 //tamanho da janela que sera criada
#define SCREEN_H 480

#define ERRO -1

typedef struct _OBJETO
{
	SDL_Surface *imagem;
	SDL_Rect posicao;
	int incx, incy;
} OBJETO;

OBJETO bmp, png, alpha;


void IniciaBMP (void)
{
	bmp.imagem = SDL_LoadBMP("pic3.bmp"); //quadro rosa, transparencia sera setada
	if (!bmp.imagem)	
	{
		printf("Nao consegui carregar imagem pic3.bmp\n");  		exit(ERRO);
	}	
	
	//setar a transparência do arquivo carregado do BMP
	if (-1 == SDL_SetColorKey(bmp.imagem, SDL_SRCCOLORKEY, SDL_MapRGB(bmp.imagem->format, 255, 0, 255)))
	{
		printf("Nao consegui color key. SDL error=%s\n", SDL_GetError());
	}

	// coloca imagens nas posicoes iniciais
	bmp.posicao.x = 70; //destino do blit da superficie BMP (w, h sao ignorados)
	bmp.posicao.y = 30;
	bmp.posicao.w = bmp.posicao.h = 0;
	
	// inicia velocidades das imagens
	bmp.incx = 1; bmp.incy = 1;
}

void IniciaPNG (void)
{
	png.imagem = IMG_Load("pic4.png"); //quadro cinza, transparencia guardada no arquivo
	if (!png.imagem)
	{
		printf("Nao consegui carregar imagem pic4.bmp\n");
  		exit(ERRO);
	}	

	png.posicao.x = 250;
	png.posicao.y = 100; //destino do blit da superficie BMP (w, h sao ignorados)
	png.posicao.w = png.posicao.h = 0;

	png.incx = 1; png.incy = -1;
}

void IniciaALPHA(void)
{
	//computador, transparencia guardada no arquivo + geral sera setada
	alpha.imagem = IMG_Load("pic5.gif"); 
	if (!alpha.imagem)
	{
		printf("Nao consegui carregar imagem pic5.bmp\n");
  		exit(ERRO);
	}	

	//setar a transparência geral da superficie alpha
	if (-1 == SDL_SetAlpha(alpha.imagem, SDL_SRCALPHA, 128))
	{
		printf("Nao consegui alpha. SDL error=%s\n", SDL_GetError());
	}

	alpha.posicao.x = 250;
	alpha.posicao.x = 250; //destino do blit da superficie com alpha (w, h sao ignorados)
	alpha.posicao.w = alpha.posicao.h = 0;
	
	alpha.incx = -1; alpha.incy = 1;

}

void update_positions(OBJETO *b)
{
	
	//atualizar a superficie BMP
	b->posicao.x += b->incx;
	b->posicao.y += b->incy;
	if((b->posicao.x > (SCREEN_W - b->imagem->w)) || (b->posicao.x < 0)) b->incx = -b->incx;
	if((b->posicao.y > (SCREEN_H - b->imagem->h)) || (b->posicao.y < 0)) b->incy = -b->incy;
}

void InicioImagens(void)
{
	IniciaBMP();
	IniciaPNG();
	IniciaALPHA();
}


int main(int argc, char** argv) //funcao de entrada
{
	Uint32 cor_fundo;
    SDL_Event event; //um evento enviado pela SDL
    int quit = 0; //devemos encerrar o programa? 
	SDL_Surface* screen; //superficie que representa a tela do computador

 	if (-1 == SDL_Init(SDL_INIT_VIDEO))
    {
    	printf("Nao consegui inicializar. SDL error=%s\n", SDL_GetError());
  		exit(ERRO);
    }

	//criar uma janela 640x480x16bits
    screen = SDL_SetVideoMode(SCREEN_W, SCREEN_H, 16, SDL_HWSURFACE | SDL_DOUBLEBUF);
   	if (!screen)
	{
		printf("Nao consegui iniciar modo de video. SDL error=%s\n", SDL_GetError());
  		exit(ERRO);
	}	
 
	cor_fundo = SDL_MapRGB(screen->format, 5, 50, 100);

	InicioImagens();
	
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
 		if (-1 == SDL_FillRect(screen, NULL, cor_fundo))
    	{
    		printf("Nao consegui encher o retangulo. SDL error=%s\n", SDL_GetError());
  			exit(ERRO);
    	}


		//copiar as imagens
		if (-1 == SDL_BlitSurface(bmp.imagem, NULL, screen, &bmp.posicao))
		{
			printf("Sem blit. SDL error=%s\n", SDL_GetError());
  			exit(ERRO);
		}
		
		if (-1 == SDL_BlitSurface(png.imagem, NULL, screen, &png.posicao))
		{
			printf("Sem blit. SDL error=%s\n", SDL_GetError());
  			exit(ERRO);
		}
		
		if (-1 == SDL_BlitSurface(alpha.imagem, NULL, screen, &alpha.posicao))
		{
			printf("Sem blit. SDL error=%s\n", SDL_GetError());
  			exit(ERRO);
		}

		//atualizar a tela
		if (-1 == SDL_Flip(screen))
		{
			printf("Nao consegui fazer flip. SDL error=%s\n", SDL_GetError());
			exit(ERRO);
		}

	}

    SDL_Quit(); //encerrar a SDL

    return 0;
}
