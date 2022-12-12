//constantes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
//#include <SDL_mixer.h>
#include <time.h>

#define SCREEN_W 680
#define SCREEN_H 520
#define FIXO_W 40
#define FIXO_H 40
#define DEL 100
#define MAXTEMPO 60

//Mix_Chunk *explo = NULL;

SDL_Surface* num;
SDL_Rect dst_m = {520, 5, 0, 0};
SDL_Rect dst_c = {540, 5, 0, 0};
SDL_Rect dst_d = {560, 5, 0, 0};
SDL_Rect dst_u = {580, 5, 0, 0};
SDL_Rect show_n ={0, 0, 20,30};

SDL_Surface* screen;
SDL_Surface* movel;

SDL_Surface* ini;
SDL_Rect dst_ini= {0, 0, 0, 0};
SDL_Rect show_ini = {0, 0, FIXO_W, FIXO_H};
SDL_Surface* ini2;
SDL_Rect dst_ini2= {0, 0, 0, 0};
SDL_Rect show_ini2 = {0, 0, FIXO_W, FIXO_H};

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
SDL_Rect dst_vida3={10, 2, 0, 0};

SDL_Surface* vida2;
SDL_Rect dst_vida2={10, 2, 0, 0};

SDL_Surface* vida1;
SDL_Rect dst_vida1={10, 2, 0, 0};

SDL_Surface* saida;
SDL_Rect dst_saida;

SDL_Surface* mortoimg;
SDL_Rect dst_mortoimg;

SDL_Surface* pausef;
SDL_Rect dst_pausef= {0, 0, 0, 0};

SDL_Surface* pause;
SDL_Rect dst_pause= {245, 100, 0, 0};

SDL_Surface* psair;
SDL_Rect dst_psair= {270, 337, 0, 0};

SDL_Surface* pmenu;
SDL_Rect dst_pmenu= {270, 277, 0, 0};

SDL_Surface* pvoltar;
SDL_Rect dst_pvoltar= {270, 217, 0, 0};

SDL_Surface* pseta;
SDL_Rect dst_pseta= {220, 222, 0, 0};

SDL_Surface* bomba;
SDL_Rect dst_bomba;
SDL_Rect dst_movel= {0, 0, 0, 0};
SDL_Rect dst_fixo = {0, 0, 0, 0};
SDL_Rect show_movel = {0, 0, FIXO_W, FIXO_H};
SDL_Rect show_bomba = {0, 0, FIXO_W, FIXO_H};
SDL_Rect dst_chao = {300, 0, 0, 0};
SDL_Rect dst_quebra = {100, 0, 0, 0};
SDL_Rect dst_borda = {200, 0, 0, 0};
SDL_Rect dst_fundo = {0, 0, 0, 0};
SDL_Rect show_fogo = {0, 0, FIXO_W, FIXO_H};
SDL_Rect show_morto = {0, 0, FIXO_W, FIXO_H};

int ponto=0,pt=0;
int bomba_colocada =0;

void jogo(int nivel);
void instru(int nivel);

typedef struct{
    int nasceX;
    int nasceY;
} NASCE;

int morto = 0;
int vidas = 3;
int inicio = 0;
int pfase=0,cini1=1,cini2=1;
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
	SDL_Surface* fase4;

	SDL_Rect dst_rectstart = {75, 150, 0, 0}; //destino do blit
	SDL_Rect dst_rectfase = {75, 225, 0, 0}; //destino do blit
	SDL_Rect dst_rectexit = {75, 300, 0, 0}; //destino do blit
	SDL_Rect dst_rectfbomber = {440, 200, 0, 0}; //destino do blit
	SDL_Rect dst_rectseta = {20, 150, 0, 0}; //destino do blit
	SDL_Rect dst_rectfase1 = {250, 225, 0, 0}; //destino do blit
	SDL_Rect dst_rectfase2 = {250, 225, 0, 0}; //destino do blit
	SDL_Rect dst_rectfase3 = {250, 225, 0, 0}; //destino do blit
	SDL_Rect dst_rectfase4 = {250, 225, 0, 0}; //destino do blit
	SDL_Rect dst_rectsetar = {420, 225, 0, 0}; //destino do blit

	SDL_Event event;

	int nivel =1;
	vidas = 3;
	morto = 0;
	cini1=1; cini2=1;

	SDL_Init(SDL_INIT_VIDEO);

	screen = SDL_SetVideoMode(SCREEN_W, SCREEN_H, 32, SDL_SWSURFACE);

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
	fase4 = SDL_LoadBMP("imagens/fase4.bmp");
	setar = SDL_LoadBMP("imagens/setar.bmp");

	SDL_SetColorKey(fase, SDL_SRCCOLORKEY, SDL_MapRGB(fase1->format, 255, 0, 255));
	SDL_SetColorKey(start, SDL_SRCCOLORKEY, SDL_MapRGB(fase1->format, 255, 0, 255));
	SDL_SetColorKey(exit, SDL_SRCCOLORKEY, SDL_MapRGB(fase1->format, 255, 0, 255));
	SDL_SetColorKey(fase1, SDL_SRCCOLORKEY, SDL_MapRGB(fase1->format, 255, 0, 255));
	SDL_SetColorKey(fase2, SDL_SRCCOLORKEY, SDL_MapRGB(fase2->format, 255, 0, 255));
	SDL_SetColorKey(fase3, SDL_SRCCOLORKEY, SDL_MapRGB(fase3->format, 255, 0, 255));
	SDL_SetColorKey(fase4, SDL_SRCCOLORKEY, SDL_MapRGB(fase4->format, 255, 0, 255));
	SDL_SetColorKey(seta, SDL_SRCCOLORKEY, SDL_MapRGB(seta->format, 255, 0, 255));
	SDL_SetColorKey(setar, SDL_SRCCOLORKEY, SDL_MapRGB(setar->format, 255, 0, 255));

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
						if(dst_rectseta.y == 300) 
						    quit = 1;
						i = 3;
						if(dst_rectseta.y == 150) 
						    if (inicio == 0) instru(nivel); 
						    else jogo(nivel);
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
			switch(nivel)
			{
			    case 5: nivel = 1; break;
			    case 0: nivel = 4; break;
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
			    case 4: SDL_BlitSurface(fase4, NULL, screen, &dst_rectfase4); break;
			    default: break;
			}
			SDL_BlitSurface(fase, NULL, screen, &dst_rectfase);
            SDL_Flip(screen);
        }
	}

    //SDL_Quit();
}

void instru(int nivel)
{
	int z=0;
	inicio = 1;


	SDL_Surface* screen;
	SDL_Surface* intro1;
	SDL_Rect dst_intro1 ={0, 0, 0, 0};
	SDL_Surface* intro2;
	SDL_Rect dst_intro2 ={0, 0, 0, 0};
	SDL_Surface* intro3;
	SDL_Rect dst_intro3 ={0, 0, 0, 0};
	SDL_Surface* intro4;
	SDL_Rect dst_intro4 ={0, 0, 0, 0};

	SDL_Event event;

	SDL_Init(SDL_INIT_VIDEO);
	screen = SDL_SetVideoMode(SCREEN_W, SCREEN_H, 32, SDL_SWSURFACE);
	SDL_WM_SetCaption("Bomberman!","Bomberman!");

	intro1 = SDL_LoadBMP("imagens/intro1.bmp");
	intro2 = SDL_LoadBMP("imagens/intro2.bmp");
	intro3 = SDL_LoadBMP("imagens/intro3.bmp");
	intro4 = SDL_LoadBMP("imagens/intro4.bmp");


	SDL_SetColorKey(intro1, SDL_SRCCOLORKEY, SDL_MapRGB(intro1->format, 255, 0, 255));
	SDL_SetColorKey(intro2, SDL_SRCCOLORKEY, SDL_MapRGB(intro2->format, 255, 0, 255));

	while (!quit)
	{
		while(SDL_PollEvent(&event)) // checar eventos
		{
			switch(event.type)
			{
				case SDL_QUIT:
				quit=1;
				break;
				case SDL_KEYDOWN:
                       switch(event.key.keysym.sym)
							{
								case SDLK_ESCAPE:
	                            quit = 1;
	                            break;
								case SDLK_RETURN:
								if (z==3) jogo(nivel); z+=1;
								break;
								case SDLK_SPACE:
								if(z<3)	z+=1;
								break;
								default:
	                            //i = 1;
	                            break;
							}
				default: break;

			}

		}
				SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
				if(z==0) SDL_BlitSurface(intro1, NULL, screen, &dst_intro1);
				if(z==1) SDL_BlitSurface(intro2, NULL, screen, &dst_intro2);
				if(z==2) SDL_BlitSurface(intro3, NULL, screen, &dst_intro3);
				if(z==3) SDL_BlitSurface(intro4, NULL, screen, &dst_intro4);

				SDL_Flip(screen);

    }

}

void CarregarMapa(int matriz[SCREEN_H/FIXO_H][SCREEN_W/FIXO_W], SDL_Surface* screen, SDL_Surface* chao, SDL_Surface* fixo, SDL_Surface* borda, SDL_Surface* quebra, SDL_Surface* saida,SDL_Surface* ini,SDL_Surface* ini2)
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
			else if(matriz[i][j] == 5) {
				dst_ini.x = j*FIXO_W;
				dst_ini.y = i*FIXO_H;
				//SDL_BlitSurface(ini, NULL, screen, &dst_ini);
				matriz[i][j] =0;
			}
			else if(matriz[i][j] == 6) {
				dst_ini2.x = j*FIXO_W;
				dst_ini2.y = i*FIXO_H;
				//SDL_BlitSurface(ini2, NULL, screen, &dst_ini2);
				matriz[i][j] =0;
			}
		}
	}
}

void passa(int nivel)
{
    SDL_Delay(2000);
    ponto+=1000;
    jogo(nivel);
}

void quitGame()
{
    SDL_BlitSurface(movel, &show_movel, screen, &dst_movel);
    SDL_Flip(screen);
    SDL_Delay(1000);
    passa(pfase);
}

void pontuacao(int ponto)
{
	int m,c,d,u;

	if (ponto <0)
    {
        m=0;
        c=0;
        d=0;
        u=0;
    }
    else {
        m = ponto/1000;
        c = (ponto%1000)/100;
        d = (ponto%100)/10;
        u = ponto%10;
    }

	switch(m)
	{
		case 0:
		{
		show_n.x=0;
		SDL_BlitSurface(num, &show_n, screen, &dst_m);
		break;
		}
		case 1:
		{
		show_n.x=20;
		SDL_BlitSurface(num, &show_n, screen, &dst_m);
		break;
		}
		case 2:
		{
		show_n.x=40;
		SDL_BlitSurface(num, &show_n, screen, &dst_m);
		break;
		}
		case 3:
		{
		show_n.x=60;
		SDL_BlitSurface(num, &show_n, screen, &dst_m);
		break;
		}
		case 4:
		{
		show_n.x=80;
		SDL_BlitSurface(num, &show_n, screen, &dst_m);
		break;
		}
		case 5:
		{
		show_n.x=100;
		SDL_BlitSurface(num, &show_n, screen, &dst_m);
		break;
		}
		case 6:
		{
		show_n.x=120;
		SDL_BlitSurface(num, &show_n, screen, &dst_m);
		break;
		}
		case 7:
		{
		show_n.x=140;
		SDL_BlitSurface(num, &show_n, screen, &dst_m);
		break;
		}
		case 8:
		{
		show_n.x=160;
		SDL_BlitSurface(num, &show_n, screen, &dst_m);
		break;
		}
		case 9:
		{
		show_n.x=180;
		SDL_BlitSurface(num, &show_n, screen, &dst_m);
		break;
		}
	}
	switch(c)
	{
		case 0:
		{
		show_n.x=0;
		SDL_BlitSurface(num, &show_n, screen, &dst_c);
		break;
		}
		case 1:
		{
		show_n.x=20;
		SDL_BlitSurface(num, &show_n, screen, &dst_c);
		break;
		}
		case 2:
		{
		show_n.x=40;
		SDL_BlitSurface(num, &show_n, screen, &dst_c);
		break;
		}
		case 3:
		{
		show_n.x=60;
		SDL_BlitSurface(num, &show_n, screen, &dst_c);
		break;
		}
		case 4:
		{
		show_n.x=80;
		SDL_BlitSurface(num, &show_n, screen, &dst_c);
		break;
		}
		case 5:
		{
		show_n.x=100;
		SDL_BlitSurface(num, &show_n, screen, &dst_c);
		break;
		}
		case 6:
		{
		show_n.x=120;
		SDL_BlitSurface(num, &show_n, screen, &dst_c);
		break;
		}
		case 7:
		{
		show_n.x=140;
		SDL_BlitSurface(num, &show_n, screen, &dst_c);
		break;
		}
		case 8:
		{
		show_n.x=160;
		SDL_BlitSurface(num, &show_n, screen, &dst_c);
		break;
		}
		case 9:
		{
		show_n.x=180;
		SDL_BlitSurface(num, &show_n, screen, &dst_c);
		break;
		}
	}
	switch(d)
	{
		case 0:
		{
		show_n.x=0;
		SDL_BlitSurface(num, &show_n, screen, &dst_d);
		break;
		}
		case 1:
		{
		show_n.x=20;
		SDL_BlitSurface(num, &show_n, screen, &dst_d);
		break;
		}
		case 2:
		{
		show_n.x=40;
		SDL_BlitSurface(num, &show_n, screen, &dst_d);
		break;
		}
		case 3:
		{
		show_n.x=60;
		SDL_BlitSurface(num, &show_n, screen, &dst_d);
		break;
		}
		case 4:
		{
		show_n.x=80;
		SDL_BlitSurface(num, &show_n, screen, &dst_d);
		break;
		}
		case 5:
		{
		show_n.x=100;
		SDL_BlitSurface(num, &show_n, screen, &dst_d);
		break;
		}
		case 6:
		{
		show_n.x=120;
		SDL_BlitSurface(num, &show_n, screen, &dst_d);
		break;
		}
		case 7:
		{
		show_n.x=140;
		SDL_BlitSurface(num, &show_n, screen, &dst_d);
		break;
		}
		case 8:
		{
		show_n.x=160;
		SDL_BlitSurface(num, &show_n, screen, &dst_d);
		break;
		}
		case 9:
		{
		show_n.x=180;
		SDL_BlitSurface(num, &show_n, screen, &dst_d);
		break;
		}
	}
	switch(u)
	{
		case 0:
		{
		show_n.x=0;
		SDL_BlitSurface(num, &show_n, screen, &dst_u);
		break;
		}
		case 1:
		{
		show_n.x=20;
		SDL_BlitSurface(num, &show_n, screen, &dst_u);
		break;
		}
		case 2:
		{
		show_n.x=40;
		SDL_BlitSurface(num, &show_n, screen, &dst_u);
		break;
		}
		case 3:
		{
		show_n.x=60;
		SDL_BlitSurface(num, &show_n, screen, &dst_u);
		break;
		}
		case 4:
		{
		show_n.x=80;
		SDL_BlitSurface(num, &show_n, screen, &dst_u);
		break;
		}
		case 5:
		{
		show_n.x=100;
		SDL_BlitSurface(num, &show_n, screen, &dst_u);
		break;
		}
		case 6:
		{
		show_n.x=120;
		SDL_BlitSurface(num, &show_n, screen, &dst_u);
		break;
		}
		case 7:
		{
		show_n.x=140;
		SDL_BlitSurface(num, &show_n, screen, &dst_u);
		break;
		}
		case 8:
		{
		show_n.x=160;
		SDL_BlitSurface(num, &show_n, screen, &dst_u);
		break;
		}
		case 9:
		{
		show_n.x=180;
		SDL_BlitSurface(num, &show_n, screen, &dst_u);
		break;
		}
	}
}

void mover(char *muv, int matriz[SCREEN_H/FIXO_H][SCREEN_W/FIXO_W], SDL_Surface* car, SDL_Surface* bomba, int bomba_colocada)
{
	int posX, posY;


	posX=(dst_movel.y/FIXO_H);  //posicao do carro em relacao a linha da matriz
	posY=(dst_movel.x/FIXO_W); //posicao do carro em relacao a coluna da matriz


        if (dst_movel.x == dst_ini.x && dst_movel.y == dst_ini.y)	{
				morto = 1;
				vidas-=1;
				}
        if (dst_movel.x == dst_ini2.x && dst_movel.y == dst_ini2.y)	{
				morto = 1;
				vidas-=1;
				}

		if((*muv == 'u')&& ((matriz[posX-1][posY]==0)||(matriz[posX-1][posY]==7)))
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
            show_movel.y =40;
		}

		else if ((*muv == 'd')&&((matriz[posX+1][posY]==0)||(matriz[posX+1][posY]==7)))
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
            show_movel.y =0;

		}

		else if((*muv == 'l')&&((matriz[posX][posY-1]==0)||(matriz[posX][posY-1]==7)))
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
            show_movel.y =120;
		}

		else if ((*muv == 'r')&&((matriz[posX][posY+1]==0)||(matriz[posX][posY+1]==7)))
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
            show_movel.y =80;
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

    //Mix_PlayChannel( 2, explo, 2);
	if ((matriz[dst_bomba.y/40][(dst_bomba.x/40) + 1] != 1)&&(matriz[dst_bomba.y/40][(dst_bomba.x/40) + 1] != 4)&&(matriz[dst_bomba.y/40][(dst_bomba.x/40) + 1] != 7))
	{
		if (matriz[dst_bomba.y/40][dst_bomba.x/40 + 1] == 8)
		{
		    matriz[dst_bomba.y/40][dst_bomba.x/40 + 1] = 7;
		    dst_base4.x=dst_bomba.x + 40;
            dst_base4.y=dst_bomba.y;
            SDL_BlitSurface(base4, &show_fogo, screen, &dst_base4);
			ponto+=110;
		}
		else if (matriz[dst_bomba.y/40][dst_bomba.x/40 + 1] == 2)
		{
		    matriz[dst_bomba.y/40][dst_bomba.x/40 + 1] = 0;
		    dst_base4.x=dst_bomba.x + 40;
            dst_base4.y=dst_bomba.y;
            SDL_BlitSurface(base4, &show_fogo, screen, &dst_base4);
			ponto+=10;
		}
		else {
		matriz[dst_bomba.y/40][dst_bomba.x/40 + 1] = 0;
		}
		dst_base4.x=dst_bomba.x + 40;
		dst_base4.y=dst_bomba.y;
		SDL_BlitSurface(base4, &show_fogo, screen, &dst_base4);


		if(dst_base4.x == dst_movel.x && dst_base4.y == dst_movel.y && morto == 0)
		{
		    vidas -= 1;
		    morto = 1;
		}
		if(dst_base4.x == dst_ini.x && dst_base4.y == dst_ini.y && cini1 == 1)
		{
		    cini1=0;
			ponto+=200;
			dst_ini.x = 0;dst_ini.y = 0;
		}
		if(dst_base4.x == dst_ini2.x && dst_base4.y == dst_ini2.y && cini2 == 1)
		{
		    cini2=0;
			ponto+=200;
			dst_ini2.x = 0;dst_ini2.y = 0;
		}
	}
	else if (matriz[dst_bomba.y/40][(dst_bomba.x/40) + 1] == 7)	SDL_BlitSurface(base4, &show_fogo, screen, &dst_base4);

	if ((matriz[(dst_bomba.y/40) + 1][dst_bomba.x/40] != 1)&&(matriz[(dst_bomba.y/40) + 1][dst_bomba.x/40] != 4)&&(matriz[(dst_bomba.y/40) + 1][dst_bomba.x/40] != 7))
	{
	    if (matriz[dst_bomba.y/40 + 1][dst_bomba.x/40] == 8)
	    {
	        matriz[dst_bomba.y/40 + 1][dst_bomba.x/40] = 7;
			dst_base3.x=dst_bomba.x;
			dst_base3.y=dst_bomba.y + 40;
            SDL_BlitSurface(base3, &show_fogo, screen, &dst_base3);
			ponto+=110;
	    }
		else if (matriz[dst_bomba.y/40 + 1][dst_bomba.x/40] == 2)
		{
		    matriz[dst_bomba.y/40 + 1][dst_bomba.x/40]  = 0;
		    dst_base4.x=dst_bomba.x + 40;
            dst_base4.y=dst_bomba.y;
            SDL_BlitSurface(base4, &show_fogo, screen, &dst_base4);
			ponto+=10;
		}
		else {
		matriz[dst_bomba.y/40 + 1][dst_bomba.x/40] = 0;

		}
		dst_base3.x=dst_bomba.x;
		dst_base3.y=dst_bomba.y + 40;
		SDL_BlitSurface(base3, &show_fogo, screen, &dst_base3);

		if(dst_base3.x == dst_movel.x && dst_base3.y == dst_movel.y && morto == 0)
		{
		    vidas -= 1;
		    morto = 1;
		}
		if(dst_base3.x == dst_ini.x && dst_base3.y == dst_ini.y && cini1 == 1)
		{
		    cini1=0;
			ponto+=200;
			dst_ini.x = 0;dst_ini.y = 0;
		}
		if(dst_base3.x == dst_ini2.x && dst_base3.y == dst_ini2.y && cini2 == 1)
		{
		    cini2=0;
			ponto+=200;
			dst_ini2.x = 0;dst_ini2.y = 0;
		}
	}
	else if (matriz[dst_bomba.y/40 + 1][(dst_bomba.x/40)] == 7)SDL_BlitSurface(base3, &show_fogo, screen, &dst_base3);

	if ((matriz[dst_bomba.y/40 - 1][dst_bomba.x/40] != 1)&&(matriz[dst_bomba.y/40 - 1][dst_bomba.x/40] != 4)&&(matriz[dst_bomba.y/40 - 1][dst_bomba.x/40] != 7))
	{
		if (matriz[dst_bomba.y/40 - 1][dst_bomba.x/40] == 8)
		{
		    matriz[dst_bomba.y/40 - 1][dst_bomba.x/40] = 7;
		    dst_base2.x=dst_bomba.x;
            dst_base2.y=dst_bomba.y - 40;
            SDL_BlitSurface(base2, &show_fogo, screen, &dst_base2);
			ponto+=110;
		}
		else if (matriz[dst_bomba.y/40 - 1][dst_bomba.x/40] == 2)
		{
		    matriz[dst_bomba.y/40 - 1][dst_bomba.x/40] = 0;
		    dst_base2.x=dst_bomba.x;
            dst_base2.y=dst_bomba.y - 40;
            SDL_BlitSurface(base2, &show_fogo, screen, &dst_base2);
			ponto+=10;
		}
		else {
		matriz[dst_bomba.y/40 - 1][dst_bomba.x/40] = 0;
		}
		dst_base2.x=dst_bomba.x;
		dst_base2.y=dst_bomba.y - 40;
        SDL_BlitSurface(base2, &show_fogo, screen, &dst_base2);

        if(dst_base2.x == dst_movel.x && dst_base2.y == dst_movel.y && morto == 0)
		{
		    vidas -= 1;
		    morto = 1;
		}
		if(dst_base2.x == dst_ini.x && dst_base2.y == dst_ini.y && cini1 == 1)
		{
		    cini1=0;
			ponto+=200;
			dst_ini.x = 0;dst_ini.y = 0;
		}
		if(dst_base2.x == dst_ini2.x && dst_base2.y == dst_ini2.y && cini2 == 1)
		{
		    cini2=0;
			ponto+=200;
			dst_ini2.x = 0;dst_ini2.y = 0;
		}

	}
	else if (matriz[dst_bomba.y/40-1][(dst_bomba.x/40)] == 7) SDL_BlitSurface(base2, &show_fogo, screen, &dst_base2);

	if ((matriz[dst_bomba.y/40][dst_bomba.x/40 - 1] != 1)&&(matriz[dst_bomba.y/40][dst_bomba.x/40 - 1] != 4)&&(matriz[dst_bomba.y/40][dst_bomba.x/40 - 1] != 7))
	{
		if (matriz[dst_bomba.y/40][dst_bomba.x/40 - 1] == 8)
		{
		    matriz[dst_bomba.y/40][dst_bomba.x/40 - 1] = 7;
            dst_base1.x=dst_bomba.x - 40;
            dst_base1.y=dst_bomba.y;
            SDL_BlitSurface(base1, &show_fogo, screen, &dst_base1);
			ponto+=110;
		}
		else if (matriz[dst_bomba.y/40][dst_bomba.x/40 - 1] == 2)
		{
		    matriz[dst_bomba.y/40][dst_bomba.x/40 - 1] = 0;
            dst_base1.x=dst_bomba.x - 40;
            dst_base1.y=dst_bomba.y;
            SDL_BlitSurface(base1, &show_fogo, screen, &dst_base1);
			ponto+=10;
		}
		else {
		matriz[dst_bomba.y/40][dst_bomba.x/40 - 1] = 0;

		}
		dst_base1.x=dst_bomba.x - 40;
		dst_base1.y=dst_bomba.y;
        SDL_BlitSurface(base1, &show_fogo, screen, &dst_base1);

        if(dst_base1.x == dst_movel.x && dst_base1.y == dst_movel.y && morto == 0)
		{
		    vidas -= 1;
		    morto = 1;
		}
		if(dst_base1.x == dst_ini.x && dst_base1.y == dst_ini.y && cini1 == 1)
		{
		    cini1=0;
			ponto+=200;
			dst_ini.x = 0;dst_ini.y = 0;
		}
		if(dst_base1.x == dst_ini2.x && dst_base1.y == dst_ini2.y && cini2 == 1)
		{
		    cini2=0;
			ponto+=200;
			dst_ini2.x = 0;dst_ini2.y = 0;
		}
	}
	else if (matriz[dst_bomba.y/40][(dst_bomba.x/40) - 1] == 7) SDL_BlitSurface(base1, &show_fogo, screen, &dst_base1);
    dst_base.x=dst_bomba.x;
    dst_base.y=dst_bomba.y;
    if(dst_base.x == dst_movel.x && dst_base.y == dst_movel.y && morto == 0)
		{
		    vidas -= 1;
		    morto = 1;
		}
	SDL_BlitSurface(base, &show_fogo, screen, &dst_base);
	show_fogo.x+=40;
	if (show_fogo.x ==160) show_fogo.x = 0;
}

void gameover()
{
    char placar[4];

    if (ponto > 0)ponto -= 100;
    if (ponto < 0)ponto = 0;
    SDL_Surface* over;
    SDL_Surface *message;
    SDL_Rect dst_message;
    SDL_Color textColor = { 255, 255, 255 };
    TTF_Font *font = NULL;
    over = SDL_LoadBMP("imagens/gameover.bmp");
    font = TTF_OpenFont( "arialbd.ttf", 35 );
    
    
    //itoa (ponto,placar,10);
    sprintf(placar, "%d", ponto);
    
    
    dst_message.x = 390; dst_message.y = 200;
    message = TTF_RenderText_Solid( font, placar, textColor );
	SDL_Delay(3000);
    SDL_BlitSurface(over, NULL, screen, NULL);
    SDL_BlitSurface( message, NULL, screen, &dst_message );
    SDL_Flip(screen);
    ponto = 0;
    SDL_Delay(5000);
    menu();
}

void contaVidas()
{
        if (vidas == 3)
        {
            vida3 = SDL_LoadBMP("imagens/vida3.bmp");
            SDL_BlitSurface(vida3, NULL, screen, &dst_vida3);
        }
        else if (vidas == 2)
        {
            vida2 = SDL_LoadBMP("imagens/vida2.bmp");
            SDL_BlitSurface(vida2, NULL, screen, &dst_vida2);
        }
        else if (vidas == 1)
        {
            vida1 = SDL_LoadBMP("imagens/vida1.bmp");
            SDL_BlitSurface(vida1, NULL, screen, &dst_vida1);
        }
}

void inimigo(int matriz[SCREEN_H/FIXO_H][SCREEN_W/FIXO_W])
{
	int iniX, iniY,nu;

	srand(time(NULL));
	iniX=(dst_ini.y/FIXO_H);  //posicao do carro em relacao a linha da matriz
	iniY=(dst_ini.x/FIXO_W); //posicao do carro em relacao a coluna da matriz

		nu =(rand()%4);
		switch(nu)
		{
			case 0:
			if(matriz[iniX-1][iniY]==0)
			{
	            if(bomba_colocada == 1)
	            {
	                        dst_ini.y -= 40;
	                        if (dst_ini.x == dst_bomba.x && dst_ini.y == dst_bomba.y)
	                        {
	                            dst_ini.y += 40;
	                        }

	            }
	            else
	            {
	                    dst_ini.y -= 40;

	            }
	        show_ini.y =40;
			if (dst_ini.x == dst_movel.x && dst_ini.y == dst_movel.y)	{
				morto = 1;
				vidas-=1;
				}
			}
			break;
			case 1:
			if(matriz[iniX+1][iniY]==0)
			{
	            if(bomba_colocada == 1)
	            {
	                        dst_ini.y += 40;
	                        if (dst_ini.x == dst_bomba.x && dst_ini.y == dst_bomba.y)
	                        {
	                            dst_ini.y -= 40;
	                        }

	            }
	            else
	            {
	                    dst_ini.y += 40;

	            }
	        show_ini.y =0;
			if (dst_ini.x == dst_movel.x && dst_ini.y == dst_movel.y)	{
				morto = 1;
				vidas-=1;
				}
			}
			break;
			case 2:
			if(matriz[iniX][iniY-1]==0)
			{
	            if(bomba_colocada == 1)
	            {
	                        dst_ini.x -= 40;
	                        if (dst_ini.x == dst_bomba.x && dst_ini.y == dst_bomba.y)
	                        {
	                            dst_ini.x += 40;
	                        }

	            }
	            else
	            {
	                    dst_ini.x -= 40;

	            }
	        show_ini.y =120;
			if (dst_ini.x == dst_movel.x && dst_ini.y == dst_movel.y)	{
				morto = 1;
				vidas-=1;
				}
			}
			break;
			case 3:
			if(matriz[iniX][iniY+1]==0)
			{
	            if(bomba_colocada == 1)
	            {
	                        dst_ini.x += 40;
	                        if (dst_ini.x == dst_bomba.x && dst_ini.y == dst_bomba.y)
	                        {
	                            dst_ini.x -= 40;
	                        }

	            }
	            else
	            {
	                    dst_ini.x += 40;

	            }
	        show_ini.y =80;
			if (dst_ini.x == dst_movel.x && dst_ini.y == dst_movel.y)	{
				morto = 1;
				vidas-=1;
				}
			}
			break;
			default: break;
		}
}

void inimigo2(int matriz[SCREEN_H/FIXO_H][SCREEN_W/FIXO_W])
{
	int iniX, iniY,nu;

	srand(time(NULL));
	iniX=(dst_ini2.y/FIXO_H);  //posicao do carro em relacao a linha da matriz
	iniY=(dst_ini2.x/FIXO_W); //posicao do carro em relacao a coluna da matriz


		nu =(rand()%4);
		switch(nu)
		{
			case 0:
			if(matriz[iniX-1][iniY]==0)
			{
	            if(bomba_colocada == 1)
	            {
	                        dst_ini2.y -= 40;
	                        if (dst_ini2.x == dst_bomba.x && dst_ini2.y == dst_bomba.y)
	                        {
	                            dst_ini2.y += 40;
	                        }

	            }
	            else
	            {
	                    dst_ini2.y -= 40;

	            }
	        show_ini2.y =40;
			if (dst_ini2.x == dst_movel.x && dst_ini2.y == dst_movel.y) {
				morto = 1;
				vidas-=1;
				}
			}
			break;
			case 1:
			if(matriz[iniX+1][iniY]==0)
			{
	            if(bomba_colocada == 1)
	            {
	                        dst_ini2.y += 40;
	                        if (dst_ini2.x == dst_bomba.x && dst_ini2.y == dst_bomba.y)
	                        {
	                            dst_ini2.y -= 40;
	                        }

	            }
	            else
	            {
	                    dst_ini2.y += 40;

	            }
	        show_ini2.y =0;
			if (dst_ini2.x == dst_movel.x && dst_ini2.y == dst_movel.y) {
				morto = 1;
				vidas-=1;
				}
			}
			break;
			case 2:
			if(matriz[iniX][iniY-1]==0)
			{
	            if(bomba_colocada == 1)
	            {
	                        dst_ini2.x -= 40;
	                        if (dst_ini2.x == dst_bomba.x && dst_ini2.y == dst_bomba.y)
	                        {
	                            dst_ini2.x += 40;
	                        }

	            }
	            else
	            {
	                    dst_ini2.x -= 40;

	            }
	        show_ini2.y =120;
			if (dst_ini2.x == dst_movel.x && dst_ini2.y == dst_movel.y) {
				morto = 1;
				vidas-=1;
				}
			}
			break;
			case 3:
			if(matriz[iniX][iniY+1]==0)
			{
	            if(bomba_colocada == 1)
	            {
	                        dst_ini2.x += 40;
	                        if (dst_ini2.x == dst_bomba.x && dst_ini2.y == dst_bomba.y)
	                        {
	                            dst_ini2.x -= 40;
	                        }

	            }
	            else
	            {
	                    dst_ini2.x += 40;

	            }
	        show_ini2.y =80;
			if (dst_ini2.x == dst_movel.x && dst_ini2.y == dst_movel.y) {
				morto = 1;
				vidas-=1;
				}
			}
			break;
		}
}

void jogo(int nivel)
{
	SDL_Surface* chao;
	SDL_Surface* fixo;
	SDL_Surface* borda;
	SDL_Surface* quebra;
	SDL_Surface* fundo;
	FILE *p;
	if (nivel ==1)
    {
        p=fopen("fase1.txt","r");
        pfase=2;
    }
    else if (nivel ==2)
    {
        p=fopen("fase2.txt","r");
        pfase=3;
    }
    else if (nivel ==3)
    {
        p=fopen("fase3.txt","r");
        pfase=4;

    }
    else if (nivel ==4)
    {
        p=fopen("fase4.txt","r");
        pfase=1;
    }

	SDL_Event event;

	int tempo,tbomba=0,contador1=0,contador2=0;
	int timerbomb=-1;
	int i,j,pauset=0;
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
	num = SDL_LoadBMP("imagens/numeros.bmp");
	mortoimg = SDL_LoadBMP("imagens/morto.bmp");
	pause = SDL_LoadBMP("imagens/pause.bmp");
	pausef = SDL_LoadBMP("imagens/pausef.bmp");
	pmenu = SDL_LoadBMP("imagens/pmenu.bmp");
	psair = SDL_LoadBMP("imagens/psair.bmp");
	pseta = SDL_LoadBMP("imagens/pseta.bmp");
	pvoltar = SDL_LoadBMP("imagens/pvoltar.bmp");
	ini = SDL_LoadBMP("imagens/ini.bmp");
	ini2 = SDL_LoadBMP("imagens/ini2.bmp");

	//explo = Mix_LoadWAV("explosion.wav");


	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	TTF_Init();
	//Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 );
	screen = SDL_SetVideoMode(SCREEN_W, SCREEN_H, 32, SDL_SWSURFACE);

	SDL_SetColorKey(movel, SDL_SRCCOLORKEY, SDL_MapRGB(movel->format, 255, 0, 255));
	SDL_SetColorKey(base, SDL_SRCCOLORKEY, SDL_MapRGB(base->format, 255, 0, 255));
	SDL_SetColorKey(base1, SDL_SRCCOLORKEY, SDL_MapRGB(base1->format, 255, 0, 255));
	SDL_SetColorKey(base2, SDL_SRCCOLORKEY, SDL_MapRGB(base2->format, 255, 0, 255));
	SDL_SetColorKey(base3, SDL_SRCCOLORKEY, SDL_MapRGB(base3->format, 255, 0, 255));
	SDL_SetColorKey(base4, SDL_SRCCOLORKEY, SDL_MapRGB(base4->format, 255, 0, 255));
	SDL_SetColorKey(bomba, SDL_SRCCOLORKEY, SDL_MapRGB(bomba->format, 255, 0, 255));
	SDL_SetColorKey(num, SDL_SRCCOLORKEY, SDL_MapRGB(num->format, 255, 0, 255));
	SDL_SetColorKey(mortoimg, SDL_SRCCOLORKEY, SDL_MapRGB(mortoimg->format, 255, 0, 255));
	SDL_SetColorKey(pause, SDL_SRCCOLORKEY, SDL_MapRGB(pause->format, 255, 0, 255));
	SDL_SetColorKey(pvoltar, SDL_SRCCOLORKEY, SDL_MapRGB(pause->format, 255, 0, 255));
	SDL_SetColorKey(pmenu, SDL_SRCCOLORKEY, SDL_MapRGB(pause->format, 255, 0, 255));
	SDL_SetColorKey(psair, SDL_SRCCOLORKEY, SDL_MapRGB(pause->format, 255, 0, 255));
	SDL_SetColorKey(pseta, SDL_SRCCOLORKEY, SDL_MapRGB(pause->format, 255, 0, 255));
	SDL_SetColorKey(ini, SDL_SRCCOLORKEY, SDL_MapRGB(ini->format, 255, 0, 255));
	SDL_SetColorKey(ini2, SDL_SRCCOLORKEY, SDL_MapRGB(ini->format, 255, 0, 255));

	SDL_SetAlpha(pausef, SDL_SRCALPHA,200);



	SDL_WM_SetCaption("Bomberman","Bomberman");

    while (!quit)
	{
		tempo = SDL_GetTicks();
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
								if (pauset==1) {
									if (dst_pseta.y!=222) dst_pseta.y-=60;
									}
								break;
							case SDLK_DOWN:
								muv = 'd';
								if (pauset==1) {
									if (dst_pseta.y!=342) dst_pseta.y+=60;
									}
								break;
							case SDLK_LEFT:
								muv = 'l';
								break;
							case SDLK_RIGHT:
								muv = 'r';
								break;

							case SDLK_ESCAPE:
								pauset+=1;

								if (pauset!=1) {
								pauset=0;
								}
								break;
							case SDLK_SPACE:
							if(bomba_colocada==0)
							{
							 	timerbomb = bomb_mark();
							 	bomba_colocada=1;
							}
							break;
							case SDLK_RETURN:
							if (pauset==1) {
									if (dst_pseta.y==222) pauset+=1;
									else if (dst_pseta.y==282) menu();
									else if (dst_pseta.y==342) exit(0);
									pauset = 0;
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
		CarregarMapa(matriz,screen,chao,fixo,quebra,borda,saida, ini, ini2);
		if(pauset==1) {
		SDL_BlitSurface(pausef, NULL, screen,&dst_pausef);
		SDL_BlitSurface(pause, NULL, screen, &dst_pause);
		SDL_BlitSurface(pseta, NULL, screen, &dst_pseta);
		SDL_BlitSurface(pvoltar, NULL, screen, &dst_pvoltar);
		SDL_BlitSurface(pmenu, NULL, screen, &dst_pmenu);
		SDL_BlitSurface(psair, NULL, screen, &dst_psair);
		}

		else {

		contaVidas();pontuacao(ponto);
        mover(&muv, matriz, movel, bomba, bomba_colocada);
        if (morto==1)
			{
                ponto-=100;
                dst_movel.x = k.nasceX;
                dst_movel.y = k.nasceY;
                SDL_Delay(100);
                morto = 0;
			}


		if(bomba_colocada==1&&tbomba==0)
		{
			SDL_BlitSurface(bomba, &show_bomba, screen, &dst_bomba);
			show_bomba.x+=40;
            if(show_bomba.x == 120) show_bomba.x=0;
			//SDL_Delay(50);
		}
		if (cini1==1) {
				contador1+=1;
				if (contador1==10) {
					inimigo(matriz);
					if (morto==1)
                    {
                        ponto-=100;
                        dst_movel.x = k.nasceX;
                        dst_movel.y = k.nasceY;
                        SDL_Delay(100);
                        morto = 0;
                    }
                    tbomba = 0;
					contador1=0;
				}
			SDL_BlitSurface(ini, &show_ini, screen, &dst_ini);
			}
        if (cini2==1) {
				contador2+=1;
				if (contador2==13) {
					inimigo2(matriz);
					if (morto==1)
                    {
                        ponto-=100;
                        dst_movel.x = k.nasceX;
                        dst_movel.y = k.nasceY;
                        SDL_Delay(100);
                        morto = 0;
                    }
                    tbomba = 0;
					contador2=0;
				}
			SDL_BlitSurface(ini2, &show_ini2, screen, &dst_ini2);
			}

		if ((SDL_GetTicks() >= timerbomb+2500)&& (bomba_colocada==1))
		{

			explode(matriz);
			tbomba=1;
		}
		if ((SDL_GetTicks() >= timerbomb+3000)&& (bomba_colocada==1))
		{
			show_fogo.x=0;
			show_morto.x=0;
			bomba_colocada=0;
			if (morto==1)
			{
                ponto-=100;
                dst_movel.x = k.nasceX;
                dst_movel.y = k.nasceY;
			}
			morto = 0;
			tbomba = 0;
		}



		if (morto !=1) {
		SDL_BlitSurface(movel, &show_movel, screen, &dst_movel);
		}

		show_movel.x+=40;
		show_ini.x+=40;
        show_ini2.x+=40;
		if(show_movel.x == 160) show_movel.x=0;
		if(show_ini.x == 160) show_ini.x=0;
        if(show_ini2.x == 160) show_ini2.x=0;

		tempo = SDL_GetTicks() - tempo;
		if( tempo < MAXTEMPO )	SDL_Delay( MAXTEMPO - tempo );


		}

		SDL_Flip(screen);
	}

    //SDL_Quit();
}
