
#include <SDL.h>
#include <SDL_image.h>

#define SCREEN_W 680
#define SCREEN_H 520
#define FIXO_W 40
#define FIXO_H 40
#define DEL 100

SDL_Surface* screen;

SDL_Surface* base;
SDL_Rect dst_base;

SDL_Surface* bomba;
SDL_Rect dst_bomba;

SDL_Rect dst_movel = {40, 40, 0, 0}; //posicao inicial do jogador
SDL_Rect dst_fixo = {0, 0, 0, 0};
SDL_Rect show_movel = {0, 0, FIXO_W, FIXO_H};
SDL_Rect dst_chao = {300, 0, 0, 0};
SDL_Rect dst_quebra = {100, 0, 0, 0};
SDL_Rect dst_borda = {200, 0, 0, 0};
SDL_Rect dst_forte = {300, 0, 0, 0};
SDL_Rect dst_fundo = {0, 0, 0, 0};


//funcoes

void mover(char *, int matriz[SCREEN_H/FIXO_H][SCREEN_W/FIXO_W], SDL_Surface *);
void CarregarMapa(int matriz[SCREEN_H/FIXO_H][SCREEN_W/FIXO_W], SDL_Surface* screen, SDL_Surface* chao, SDL_Surface* fixo, SDL_Surface* borda, SDL_Surface* quebra, SDL_Surface* forte);
void explode(int matriz[SCREEN_H/FIXO_H][SCREEN_W/FIXO_W]);
int bomb_mark(void);

void CarregarMapa(int matriz[SCREEN_H/FIXO_H][SCREEN_W/FIXO_W], SDL_Surface* screen, SDL_Surface* chao, SDL_Surface* fixo, SDL_Surface* borda, SDL_Surface* quebra, SDL_Surface* forte)
{
	int i,j;

	for(i=0;i<(SCREEN_H/FIXO_H);i++)
	{
		for(j=0;j<(SCREEN_W/FIXO_W);j++)
		{
			if(matriz[i][j] == 0)	{
				dst_chao.x = j*FIXO_W;
				dst_chao.y = i*FIXO_H;
				SDL_BlitSurface(chao, NULL, screen, &dst_chao);
			}
			else if(matriz[i][j] == 1) {
				dst_fixo.x = j*FIXO_W;
				dst_fixo.y = i*FIXO_H;
				SDL_BlitSurface(fixo, NULL, screen, &dst_fixo);
			}
			else if(matriz[i][j] == 4) {
				dst_borda.x = j*FIXO_W;
				dst_borda.y = i*FIXO_H;
				SDL_BlitSurface(borda, NULL, screen, &dst_borda);
			}
			else if(matriz[i][j] == 2) {
				dst_quebra.x = j*FIXO_W;
				dst_quebra.y = i*FIXO_H;
				SDL_BlitSurface(quebra, NULL, screen, &dst_quebra);
			}
			else if(matriz[i][j] == 3) {
				dst_forte.x = j*FIXO_W;
				dst_forte.y = i*FIXO_H;
				SDL_BlitSurface(forte, NULL, screen, &dst_forte);
			}
		}
	}
}

void mover(char *muv, int matriz[SCREEN_H/FIXO_H][SCREEN_W/FIXO_W], SDL_Surface* car)
{
	int posX, posY;


	posX=(dst_movel.y/FIXO_H);  //posicao do carro em relacao a linha da matriz
	posY=(dst_movel.x/FIXO_W); //posicao do carro em relacao a coluna da matriz


		if((*muv == 'u')&&(matriz[posX-1][posY]==0))
		{
			dst_movel.y -= 40;
		}
		else if ((*muv == 'd')&&(matriz[posX+1][posY]==0))
		{
			dst_movel.y += 40;
		}
		else if((*muv == 'l')&&(matriz[posX][posY-1]==0))
		{
			dst_movel.x -= 40;
		}
		else if ((*muv == 'r')&&(matriz[posX][posY+1]==0))
		{
			dst_movel.x += 40;
		}
}

int bomb_mark(void)
{
	int timerbomb;
	timerbomb=SDL_GetTicks();
	dst_bomba.x=dst_movel.x;
	dst_bomba.y=dst_movel.y;
	SDL_BlitSurface(bomba ,NULL, screen , &dst_bomba);
	return timerbomb;
}


void explode(int matriz[SCREEN_H/FIXO_H][SCREEN_W/FIXO_W])
{
	/*explode a bomba*/

	if ((matriz[dst_bomba.y/40][(dst_bomba.x/40) + 1] != 1)&&(matriz[dst_bomba.y/40][(dst_bomba.x/40) + 1] != 4))
	{
		matriz[dst_bomba.y/40][dst_bomba.x/40 + 1] =0;
		dst_base.x=dst_bomba.x + 40;
		dst_base.y=dst_bomba.y;
		SDL_BlitSurface(base, NULL, screen, &dst_base);
	}

	if ((matriz[dst_bomba.y/40 + 1][dst_bomba.x/40] != 1)&&(matriz[dst_bomba.y/40 + 1][dst_bomba.x/40] != 4))
	{
		matriz[dst_bomba.y/40 + 1][dst_bomba.x/40] = 0;
		dst_base.x=dst_bomba.x;
		dst_base.y=dst_bomba.y + 40;
		SDL_BlitSurface(base, NULL, screen, &dst_base);
	}

	if ((matriz[dst_bomba.y/40 - 1][dst_bomba.x/40] != 1)&&(matriz[dst_bomba.y/40 - 1][dst_bomba.x/40] != 4))
	{
		matriz[dst_bomba.y/40 - 1][dst_bomba.x/40] = 0;
		dst_base.x=dst_bomba.x;
		dst_base.y=dst_bomba.y - 40;
        SDL_BlitSurface(base, NULL, screen, &dst_base);

	}

	if ((matriz[dst_bomba.y/40][dst_bomba.x/40 - 1] != 1)&&(matriz[dst_bomba.y/40][dst_bomba.x/40 - 1] != 4))
	{
		matriz[dst_bomba.y/40][dst_bomba.x/40 - 1] = 0;
		dst_base.x=dst_bomba.x - 40;
		dst_base.y=dst_bomba.y;
        SDL_BlitSurface(base, NULL, screen, &dst_base);
	}

    dst_base.x=dst_bomba.x;
    dst_base.y=dst_bomba.y;
    SDL_BlitSurface(base, NULL, screen, &dst_base);

}


int main(int argc, char** argv)
{
	SDL_Surface* chao;
	SDL_Surface* movel;
	SDL_Surface* fixo;
	SDL_Surface* borda;
	SDL_Surface* quebra;
	SDL_Surface* forte;
	SDL_Surface* fundo;

	/*char *n="./fase1.txt";*/ //abre a matriz a partir do txt
	FILE *p;
	p=fopen("fase1.txt","r");
	if (!p) return -1;
	
	SDL_Event event;

	int timerbomb=-1;
	int bomba_colocada=0;
	int quit = 0;
	int i,j;
	char muv = 'n';
	int matriz[SCREEN_H/FIXO_H][SCREEN_W/FIXO_W]; // matriz q representa a tela

	// manipulando os valores da matriz
	for (i=0; i< SCREEN_H/FIXO_H; i++)
	{
		for (j=0; j<SCREEN_W/FIXO_W;j++)
		{
			fscanf(p,"%d",&matriz[i][j]);
		}
	}
	fclose(p);
	
	fixo = SDL_LoadBMP("imagens/fixo.bmp");
	chao = IMG_Load("imagens/chao.gif");
	borda =	IMG_Load("imagens/borda.jpg");
	quebra = IMG_Load("imagens/quebra.jpg");
	forte = SDL_LoadBMP("imagens/forte.bmp");
	movel = SDL_LoadBMP("imagens/movel.bmp");
	fundo = IMG_Load("imagens/fundo.gif");
	bomba = SDL_LoadBMP("imagens/bomba.bmp");
	base = SDL_LoadBMP("imagens/explo.bmp");

	SDL_Init(SDL_INIT_VIDEO);
	screen = SDL_SetVideoMode(SCREEN_W, SCREEN_H, 16, SDL_SWSURFACE);
	SDL_SetColorKey(movel, SDL_SRCCOLORKEY, SDL_MapRGB(movel->format, 255, 0, 255));
	SDL_SetColorKey(forte, SDL_SRCCOLORKEY, SDL_MapRGB(movel->format, 255, 0, 255));
	SDL_WM_SetCaption("Projeto Bomberman!","Bomberman");

		while (!quit)
	{
		while(SDL_PollEvent(&event)) // checar eventos
		{
			switch(event.type)
			{
				case SDL_QUIT: // sair do loop
					quit = 1;
					break;
				case SDL_KEYDOWN:
					switch(event.key.keysym.sym)
						{
							case SDLK_UP:
								muv = 'u';
								break;
							case SDLK_DOWN:
								muv = 'd';
								break;
							case SDLK_LEFT:
								muv = 'l';
								break;
							case SDLK_RIGHT:
								muv = 'r';
								break;

							case SDLK_ESCAPE:
								quit = 1;
								break;
							case SDLK_SPACE:
							if(bomba_colocada==0)
							{
							 	timerbomb = bomb_mark();
							 	bomba_colocada=1;
							}
                                break;
							default:
								break;

						}
					break;

				case SDL_KEYUP:
					switch(event.key.keysym.sym)
					{
                            case SDLK_UP:
								muv = 'p';
								break;
							case SDLK_DOWN:
								muv = 'p';
								break;
							case SDLK_LEFT:
								muv = 'p';
								break;
							case SDLK_RIGHT:
								muv = 'p';
								break;
							default:
								break;
					}
				default:
					break;
			}
		}
		
		SDL_BlitSurface(fundo, NULL, screen, NULL);
		SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 0, 255));
		CarregarMapa(matriz,screen,chao,fixo,quebra,borda,forte);
        mover(&muv, matriz, movel);

		
		
		if(bomba_colocada==1)
		{
			SDL_BlitSurface(bomba, NULL, screen, &dst_bomba);
		}
		SDL_BlitSurface(fixo, NULL, screen, &dst_fixo);
		//SDL_BlitSurface(destruct, NULL, screen, &dst_destruct);


		if ((SDL_GetTicks() >= timerbomb+3000)&& (bomba_colocada==1))
		{
			explode(matriz);
		}
		if ((SDL_GetTicks() >= timerbomb+4000)&& (bomba_colocada==1))
		{
			bomba_colocada=0;
		}
		
		SDL_BlitSurface(movel, &show_movel, screen, &dst_movel);
		
		SDL_Flip(screen);

	}
	SDL_Quit();

	return 0;
}
