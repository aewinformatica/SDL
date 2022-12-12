//constantes
#include <stdio.h>
#include <string.h>
#include <SDL.h>
#include <SDL_image.h>

#define SCREEN_W 680
#define SCREEN_H 520
#define FIXO_W 40
#define FIXO_H 40
#define DEL 100

SDL_Surface* screen;
SDL_Surface* movel;

SDL_Surface* base;
SDL_Rect dst_base;

SDL_Surface* base1;
SDL_Rect dst_base1;

SDL_Surface* base2;
SDL_Rect dst_base2;

SDL_Surface* base3;
SDL_Rect dst_base3;

SDL_Surface* base4;
SDL_Rect dst_base4;

SDL_Surface* vida3;
SDL_Rect dst_vida3;

SDL_Surface* vida2;
SDL_Rect dst_vida2;

SDL_Surface* vida1;
SDL_Rect dst_vida1;

SDL_Surface* saida;
SDL_Rect dst_saida;

SDL_Surface* bomba;
SDL_Rect dst_bomba;
SDL_Rect dst_movel= {0, 0, 0, 0};
SDL_Rect dst_fixo = {0, 0, 0, 0};
SDL_Rect show_movel = {0, 0, FIXO_W, FIXO_H};
SDL_Rect dst_chao = {300, 0, 0, 0};
SDL_Rect dst_quebra = {100, 0, 0, 0};
SDL_Rect dst_borda = {200, 0, 0, 0};
SDL_Rect dst_fundo = {0, 0, 0, 0};

void jogo(int nivel);

typedef struct{
    int nasceX;
    int nasceY;
} NASCE;

int morto = 0;
int vidas = 3;
NASCE k;

void menu()
{
	SDL_Surface* screen;
	SDL_Surface* fbomber;
	SDL_Surface* start;
	SDL_Surface* exit;
	SDL_Surface* seta;
	SDL_Surface* setar;
	SDL_Surface* fase;
	SDL_Surface* fase1;
	SDL_Surface* fase2;
	SDL_Surface* fase3;

	SDL_Rect dst_rectstart = {75, 150, 0, 0}; //destino do blit
	SDL_Rect dst_rectfase = {75, 225, 0, 0}; //destino do blit
	SDL_Rect dst_rectexit = {75, 300, 0, 0}; //destino do blit
	SDL_Rect dst_rectfbomber = {440, 200, 0, 0}; //destino do blit
	SDL_Rect dst_rectseta = {20, 150, 0, 0}; //destino do blit
	SDL_Rect dst_rectfase1 = {250, 225, 0, 0}; //destino do blit
	SDL_Rect dst_rectfase2 = {250, 225, 0, 0}; //destino do blit
	SDL_Rect dst_rectfase3 = {250, 225, 0, 0}; //destino do blit
	SDL_Rect dst_rectsetar = {420, 225, 0, 0}; //destino do blit

	SDL_Event event;

	int nivel =1;

	SDL_Init(SDL_INIT_VIDEO);

	screen = SDL_SetVideoMode(SCREEN_W, SCREEN_H, 16, SDL_SWSURFACE);

	SDL_WM_SetCaption("Bomberman!","Bomberman!");

	//carregar as imagens
	start = SDL_LoadBMP("imagens/comecar.bmp");
	exit = SDL_LoadBMP("imagens/sair.bmp");
	fbomber = SDL_LoadBMP("imagens/fbomber.bmp");
	seta = SDL_LoadBMP("imagens/seta.bmp");
	fase = SDL_LoadBMP("imagens/fase.bmp");
	fase1 = SDL_LoadBMP("imagens/fase1.bmp");
	fase2 = SDL_LoadBMP("imagens/fase2.bmp");
	fase3 = SDL_LoadBMP("imagens/fase3.bmp");
	setar = SDL_LoadBMP("imagens/setar.bmp");


	while (!quit)
	{
		while(SDL_PollEvent(&event)) // checar eventos
		{
			switch(event.type)
			{
				case SDL_QUIT: quit = 1; break;//sair do loop principal
				case SDL_KEYDOWN:
					switch(event.key.keysym.sym )
					{
						case SDLK_ESCAPE: quit = 1; break;

						case SDLK_UP:
						if((dst_rectseta.y == 300)||(dst_rectseta.y == 225)&&(dst_rectseta.x == 20)) dst_rectseta.y -= 75; break;

						case SDLK_DOWN:
						if((dst_rectseta.y == 150)||(dst_rectseta.y == 225)&&(dst_rectseta.x == 20))  dst_rectseta.y += 75; break;

						case SDLK_RETURN:
						if(dst_rectseta.y == 300) quit = 1;i = 3;
						if(dst_rectseta.y == 150) jogo(nivel);
						if(dst_rectseta.y == 225)
						{
							if(dst_rectseta.x == 20) dst_rectseta.x += 95;
							else dst_rectseta.x -= 95;
						}
						break;
						case SDLK_LEFT:
						if((dst_rectseta.y == 225)&&(dst_rectseta.x == 115)) nivel -=1;
						break;
						case SDLK_RIGHT:
						if((dst_rectseta.y == 225)&&(dst_rectseta.x == 115)) nivel += 1;
						break;

						default: break;
					}
			}
			switch(nivel){
			case 4: nivel = 1; break;
			case 0: nivel = 3; break;
			default: break;
			}
            SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
            SDL_BlitSurface(start, NULL, screen, &dst_rectstart);
			SDL_BlitSurface(exit, NULL, screen, &dst_rectexit);
			SDL_BlitSurface(fbomber, NULL, screen, &dst_rectfbomber);
			if(dst_rectseta.x == 115)	SDL_BlitSurface(setar, NULL, screen, &dst_rectsetar);
			else SDL_BlitSurface(seta, NULL, screen, &dst_rectseta);

			switch (nivel)
			{
			case 1: SDL_BlitSurface(fase1, NULL, screen, &dst_rectfase1); break;
			case 2: SDL_BlitSurface(fase2, NULL, screen, &dst_rectfase2); break;
			case 3: SDL_BlitSurface(fase3, NULL, screen, &dst_rectfase3); break;
			default: break;
			}
			SDL_BlitSurface(fase, NULL, screen, &dst_rectfase);
            SDL_Flip(screen);

        }
	}

    //SDL_Quit();
}
void CarregarMapa(int matriz[SCREEN_H/FIXO_H][SCREEN_W/FIXO_W], SDL_Surface* screen, SDL_Surface* chao, SDL_Surface* fixo, SDL_Surface* borda, SDL_Surface* quebra, SDL_Surface* saida)
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
			else if(matriz[i][j] == 9) {
				dst_movel.x = j*FIXO_W;
				dst_movel.y = i*FIXO_H;
				k.nasceX = j*FIXO_W;
				k.nasceY = i*FIXO_H;
				SDL_BlitSurface(movel, NULL, screen, &dst_movel);
				matriz[i][j] =0;

			}
			else if(matriz[i][j] == 8) {
				dst_quebra.x = j*FIXO_W;
				dst_quebra.y = i*FIXO_H;
				SDL_BlitSurface(quebra, NULL, screen, &dst_quebra);
			}
			else if(matriz[i][j] == 7) {
				dst_saida.x = j*FIXO_W;
				dst_saida.y = i*FIXO_H;
				SDL_BlitSurface(saida, NULL, screen, &dst_saida);
			}

		}
	}
}

void quitGame()
{
    SDL_BlitSurface(movel, &show_movel, screen, &dst_movel);
    SDL_Flip(screen);
    SDL_Delay(1000);
    menu();
}

void mover(char *muv, int matriz[SCREEN_H/FIXO_H][SCREEN_W/FIXO_W], SDL_Surface* car, SDL_Surface* bomba, int bomba_colocada)
{
	int posX, posY;


	posX=(dst_movel.y/FIXO_H);  //posicao do carro em relacao a linha da matriz
	posY=(dst_movel.x/FIXO_W); //posicao do carro em relacao a coluna da matriz


		if((*muv == 'u')&& ((matriz[posX-1][posY]==0)or(matriz[posX-1][posY]==7)))
		{
		    if (matriz[posX-1][posY]==7)
            {

                dst_movel.y -= 40;
                quitGame();

            }
            else
            {
                 if(bomba_colocada == 1)
                {
                        dst_movel.y -= 40;
                        if (dst_movel.x == dst_bomba.x && dst_movel.y == dst_bomba.y)
                        {
                            dst_movel.y += 40;
                        }
                        SDL_Delay(DEL);
                }
                else
                {
                    dst_movel.y -= 40;
                    SDL_Delay(DEL);
                }
            }
		}

		else if ((*muv == 'd')&&((matriz[posX+1][posY]==0)or(matriz[posX+1][posY]==7)))
		{
			if (matriz[posX+1][posY]==7)
            {
                dst_movel.y += 40;
                quitGame();
            }
            else
            {
                if(bomba_colocada == 1)
                {
                        dst_movel.y += 40;
                        if (dst_movel.x == dst_bomba.x && dst_movel.y == dst_bomba.y)
                        {
                            dst_movel.y -= 40;
                        }
                        SDL_Delay(DEL);
                }
                else
                {
                    dst_movel.y += 40;
                    SDL_Delay(DEL);
                }
            }

		}

		else if((*muv == 'l')&&((matriz[posX][posY-1]==0)or(matriz[posX][posY-1]==7)))
		{
		    if (matriz[posX][posY-1]==7)
            {

                dst_movel.x -= 40;
                quitGame();

            }
            else
            {
                if(bomba_colocada == 1)
                {
                        dst_movel.x -= 40;
                        if (dst_movel.x == dst_bomba.x && dst_movel.y == dst_bomba.y)
                        {
                            dst_movel.x += 40;
                        }
                        SDL_Delay(DEL);
                }
                else
                {
                    dst_movel.x -= 40;
                    SDL_Delay(DEL);
                }
            }
		}

		else if ((*muv == 'r')&&((matriz[posX][posY+1]==0)or(matriz[posX][posY+1]==7)))
		{
			if (matriz[posX][posY+1]==7)
            {

                dst_movel.x += 40;
                quitGame();
            }
            else
            {
                if(bomba_colocada == 1)
                {
                        dst_movel.x += 40;
                        if (dst_movel.x == dst_bomba.x && dst_movel.y == dst_bomba.y)
                        {
                            dst_movel.x -= 40;
                        }
                        SDL_Delay(DEL);
                }
                else
                {
                    dst_movel.x += 40;
                    SDL_Delay(DEL);
                }
            }
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

	if ((matriz[dst_bomba.y/40][(dst_bomba.x/40) + 1] != 1)&&(matriz[dst_bomba.y/40][(dst_bomba.x/40) + 1] != 4)&&(matriz[dst_bomba.y/40][(dst_bomba.x/40) + 1] != 7))
	{
		if (matriz[dst_bomba.y/40][dst_bomba.x/40 + 1] == 8)
		{
		    matriz[dst_bomba.y/40][dst_bomba.x/40 + 1] = 7;
		    dst_base4.x=dst_bomba.x + 40;
            dst_base4.y=dst_bomba.y;
            SDL_BlitSurface(base4, NULL, screen, &dst_base4);
		}
		else matriz[dst_bomba.y/40][dst_bomba.x/40 + 1] = 0;
		dst_base4.x=dst_bomba.x + 40;
		dst_base4.y=dst_bomba.y;
		SDL_BlitSurface(base4, NULL, screen, &dst_base4);
		if(dst_base4.x == dst_movel.x && dst_base4.y == dst_movel.y && morto == 0)
		{
		    dst_movel.x = k.nasceX;
		    dst_movel.y = k.nasceY;
		    vidas -= 1;
		    morto = 1;
		}
	}
	else if (matriz[dst_bomba.y/40][(dst_bomba.x/40) + 1] == 7)SDL_BlitSurface(base4, NULL, screen, &dst_base4);

	if ((matriz[(dst_bomba.y/40) + 1][dst_bomba.x/40] != 1)&&(matriz[(dst_bomba.y/40) + 1][dst_bomba.x/40] != 4)&&(matriz[(dst_bomba.y/40) + 1][dst_bomba.x/40] != 7))
	{
	    if (matriz[dst_bomba.y/40 + 1][dst_bomba.x/40] == 8)
	    {
	        matriz[dst_bomba.y/40 + 1][dst_bomba.x/40] = 7;
	        dst_base3.x=dst_bomba.x;
            dst_base3.y=dst_bomba.y + 40;
            SDL_BlitSurface(base3, NULL, screen, &dst_base3);
	    }
		else matriz[dst_bomba.y/40 + 1][dst_bomba.x/40] = 0;
		dst_base3.x=dst_bomba.x;
		dst_base3.y=dst_bomba.y + 40;
		SDL_BlitSurface(base3, NULL, screen, &dst_base3);
		if(dst_base3.x == dst_movel.x && dst_base3.y == dst_movel.y && morto == 0)
		{
		    dst_movel.x = k.nasceX;
		    dst_movel.y = k.nasceY;
		    vidas -= 1;
		    morto = 1;
		}
	}
	else if (matriz[dst_bomba.y/40 + 1][(dst_bomba.x/40)] == 7)SDL_BlitSurface(base3, NULL, screen, &dst_base3);

	if ((matriz[dst_bomba.y/40 - 1][dst_bomba.x/40] != 1)&&(matriz[dst_bomba.y/40 - 1][dst_bomba.x/40] != 4)&&(matriz[dst_bomba.y/40 - 1][dst_bomba.x/40] != 7))
	{
		if (matriz[dst_bomba.y/40 - 1][dst_bomba.x/40] == 8)
		{
		    matriz[dst_bomba.y/40 - 1][dst_bomba.x/40] = 7;
		    dst_base2.x=dst_bomba.x;
            dst_base2.y=dst_bomba.y - 40;
            SDL_BlitSurface(base2, NULL, screen, &dst_base2);
		}
		else matriz[dst_bomba.y/40 - 1][dst_bomba.x/40] = 0;
		dst_base2.x=dst_bomba.x;
		dst_base2.y=dst_bomba.y - 40;
        SDL_BlitSurface(base2, NULL, screen, &dst_base2);
        if(dst_base2.x == dst_movel.x && dst_base2.y == dst_movel.y && morto == 0)
		{
		    dst_movel.x = k.nasceX;
		    dst_movel.y = k.nasceY;
		    vidas -= 1;
		    morto = 1;
		}

	}
	else if (matriz[dst_bomba.y/40-1][(dst_bomba.x/40)] == 7)SDL_BlitSurface(base2, NULL, screen, &dst_base2);

	if ((matriz[dst_bomba.y/40][dst_bomba.x/40 - 1] != 1)&&(matriz[dst_bomba.y/40][dst_bomba.x/40 - 1] != 4)&&(matriz[dst_bomba.y/40][dst_bomba.x/40 - 1] != 7))
	{
		if (matriz[dst_bomba.y/40][dst_bomba.x/40 - 1] == 8)
		{
		    matriz[dst_bomba.y/40][dst_bomba.x/40 - 1] = 7;
            dst_base1.x=dst_bomba.x - 40;
            dst_base1.y=dst_bomba.y;
            SDL_BlitSurface(base1, NULL, screen, &dst_base1);
		}
		else matriz[dst_bomba.y/40][dst_bomba.x/40 - 1] = 0;
		dst_base1.x=dst_bomba.x - 40;
		dst_base1.y=dst_bomba.y;
        SDL_BlitSurface(base1, NULL, screen, &dst_base1);
        if(dst_base1.x == dst_movel.x && dst_base1.y == dst_movel.y && morto == 0)
		{
		    dst_movel.x = k.nasceX;
		    dst_movel.y = k.nasceY;
		    vidas -= 1;
		    morto = 1;
		}
	}
	else if (matriz[dst_bomba.y/40][(dst_bomba.x/40) - 1] == 7)SDL_BlitSurface(base1, NULL, screen, &dst_base1);

    dst_base.x=dst_bomba.x;
    dst_base.y=dst_bomba.y;
    if(dst_base.x == dst_movel.x && dst_base.y == dst_movel.y && morto == 0)
		{
		    dst_movel.x = k.nasceX;
		    dst_movel.y = k.nasceY;
		    vidas -= 1;
		    morto = 1;
		}
    SDL_BlitSurface(base, NULL, screen, &dst_base);

}

void gameover()
{
    SDL_Surface* over;
    over = SDL_LoadBMP("imagens/gameover.bmp");
    SDL_BlitSurface(over, NULL, screen, NULL);
    SDL_Flip(screen);
    SDL_Delay(3000);
    menu();
}

void contaVidas()
{
        if (vidas == 3)
        {
            vida3 = SDL_LoadBMP("imagens/vida3.bmp");
            dst_vida3.x = 0; dst_vida3.y = 0;
            SDL_BlitSurface(vida3, NULL, screen, &dst_vida3);
        }
        else if (vidas == 2)
        {
            vida2 = SDL_LoadBMP("imagens/vida2.bmp");
            dst_vida2.x = 0; dst_vida2.y = 0;
            SDL_BlitSurface(vida2, NULL, screen, &dst_vida2);
        }
        else if (vidas == 1)
        {
            vida1 = SDL_LoadBMP("imagens/vida1.bmp");
            dst_vida1.x = 0; dst_vida1.y = 0;
            SDL_BlitSurface(vida1, NULL, screen, &dst_vida1);
        }
}


void jogo(int nivel)
{
    vidas = 3;

	SDL_Surface* chao;
	SDL_Surface* fixo;
	SDL_Surface* borda;
	SDL_Surface* quebra;
	SDL_Surface* fundo;

	/*char *n="./fase1.txt";*/ //abre a matriz a partir do txt
	FILE *p;
	if (nivel ==1)
	{
		p=fopen("fase1.txt","r");
	}
	else if (nivel ==2)
	{
		p=fopen("fase2.txt","r");
	}
	else if (nivel ==3)
	{
		p=fopen("fase3.txt","r");
	}

	SDL_Event event;

	int timerbomb=-1;
	int bomba_colocada=0;
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
	chao = SDL_LoadBMP("imagens/chao.bmp");
	borda =	SDL_LoadBMP("imagens/borda.bmp");
	quebra = SDL_LoadBMP("imagens/quebra.bmp");
	movel = SDL_LoadBMP("imagens/movel.bmp");
	fundo = SDL_LoadBMP("imagens/fundo.bmp");
	bomba = SDL_LoadBMP("imagens/bomba.bmp");
	base = SDL_LoadBMP("imagens/explo.bmp");
	base1 = SDL_LoadBMP("imagens/explo1.bmp");
	base2 = SDL_LoadBMP("imagens/explo2.bmp");
	base3 = SDL_LoadBMP("imagens/explo3.bmp");
	base4 = SDL_LoadBMP("imagens/explo4.bmp");
	saida = SDL_LoadBMP("imagens/saida.bmp");

	SDL_Init(SDL_INIT_VIDEO);
	screen = SDL_SetVideoMode(SCREEN_W, SCREEN_H, 32, SDL_SWSURFACE);

	SDL_SetColorKey(movel, SDL_SRCCOLORKEY, SDL_MapRGB(movel->format, 255, 0, 255));
	SDL_SetColorKey(base, SDL_SRCCOLORKEY, SDL_MapRGB(movel->format, 255, 0, 255));
	SDL_SetColorKey(base1, SDL_SRCCOLORKEY, SDL_MapRGB(movel->format, 255, 0, 255));
	SDL_SetColorKey(base2, SDL_SRCCOLORKEY, SDL_MapRGB(movel->format, 255, 0, 255));
	SDL_SetColorKey(base3, SDL_SRCCOLORKEY, SDL_MapRGB(movel->format, 255, 0, 255));
	SDL_SetColorKey(base4, SDL_SRCCOLORKEY, SDL_MapRGB(movel->format, 255, 0, 255));
	SDL_SetColorKey(bomba, SDL_SRCCOLORKEY, SDL_MapRGB(movel->format, 255, 0, 255));
	SDL_WM_SetCaption("Bomberman","Bomberman");

    while (!quit)
	{
	    if (vidas == 0)gameover();//mudar pra fazer o game over
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
								menu();
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
		CarregarMapa(matriz,screen,chao,fixo,quebra,borda,saida);
		contaVidas();
        mover(&muv, matriz, movel, bomba, bomba_colocada);



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
			morto = 0;
		}

		SDL_BlitSurface(movel, &show_movel, screen, &dst_movel);
		SDL_Flip(screen);

	}

    //SDL_Quit();
}
