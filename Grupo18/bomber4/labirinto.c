#include "global.h"
#include "prototipos.h"

void cria_lab(int mapa[MAX_H][MAX_W], int n, int m, int bld)
{
	int maximo_caixas = ((n - 2)*(m - 2)) - ((m - 3)/2) - ((n - 3)/2);
	maximo_caixas =  maximo_caixas >0 ? maximo_caixas : 0;
	int q;
	
	if(bld > maximo_caixas) bld = maximo_caixas;

	posiciona_indestrutiveis(mapa, n, m);
	posiciona_caixas(mapa, n, m, bld);

	/*para todo objeto (item) a ser escondido em caixas, cabe aqui um 
		q= rand()%(quantidade_maxima_do_item- 1 - qntd minima) + quantidade minima);
		esconde(mapa, n, m, q, - (codigo_do_item));
		e importante a notacao do item, o codigo dele deve ser igual ou maior a 5 (os valores de -4 a 4 ja foram usados. 99 tambem ja foi) para que
		o bloco que o esconde seja representado por -codigo (código negativo) 
		alem de adicionar e esconder o objeto e importante adicionar o bloco negativo aa 
		funcao avalia_ex (em explode.c), avalia_passo(em movimento.c) e desenha_lab (em labirinto.c)
		A saida sera um objeto escondido de quantidade q=1!

		Ultima observacao: a soma das quantidades de objetos escondidos nao pode ultrapassar o
		numero de caixas a serem posicionadas menos 8 (Soma dos qs < bld-8). */

	q= rand()%1 +3; // quantidade do item a ser colocado (5 = incrementa raio de alcance da bomba): varia de 3 a 5
	esconde(mapa, n, m, q, -5); // esconde item 5 (incrementa raio de alcance da bomba )

	q= rand()%1 +2; // quantidade do item a ser colocado (5 = incrementa raio de alcance da bomba): varia de 3 a 5
	esconde(mapa, n, m, q, -7); //item invencibilidade temporaria 7
	
	q= rand()%1 +1; // quantidade do item a ser colocado (5 = incrementa raio de alcance da bomba): varia de 3 a 5
	esconde(mapa, n, m, q, -8); //passo 2 -8
	
	q= rand()%1 +1; // quantidade do item a ser colocado (5 = incrementa raio de alcance da bomba): varia de 3 a 5
	esconde(mapa, n, m, q, -9); //passo 2 -8
	
}

void posiciona_indestrutiveis(int mapa[MAX_H][MAX_W], int n, int m)
{
	int i, j;
	for(i =0; i <n; i++)
	{
		for(j =0; j <m; j++)
		{
			if((i == 0)||(i == (n-1))) mapa[i][j] =-1;
			else if((j == 0)||(j == m-1)) mapa[i][j] =-1;
			else if(i%2 == 0 && j%2 == 0) mapa[i][j] = -1;
			else mapa[i][j] = 0;
		}
	}
}

void posiciona_caixas(int mapa[MAX_H][MAX_W], int n, int m, int bld)
{
	int coox, cooy;
	for( ; bld >0; bld--)
	{
		do
		{
			coox = rand()%m;
			cooy = rand()%n;
		}while(mapa[cooy][coox]!=0);
		mapa[cooy][coox] = 1;
	}
}

void esconde(int mapa[MAX_H][MAX_W], int n, int m, int q, int cod)
{
	int coox, cooy;
	int i, j, soma=0;
	for(i=0; i<n; i++)
	{
		for(j=0; j<m; j++)
		{
			if(mapa[j][i]== 1) soma++;
		}
	}
	if(soma> 0)
	{
		for( ; q >0; q--)
		{
			do
			{
				coox = rand()%m;
				cooy = rand()%n;
			}while(mapa[cooy][coox]!=1);
			mapa[cooy][coox] = cod;
		}
	}
}

void posiciona_dinamico(int mapa[MAX_H][MAX_W], int n, int m, Obj_Dinamico *obj)
{
	int i, j, coox, cooy;
	do
	{
		coox = rand()%m;
		cooy = rand()%n;
	}while(mapa[cooy][coox]!=0);
	
	mapa[cooy][coox] =(*obj).cod;
	
	for(i =-1; i <=1; i++)
		for(j =-1; j <=1; j++)
		{
			if(mapa[cooy + i][coox + j] != -1 && ((i!=0)||(j!=0))) 
				if(mapa[cooy + i][coox + j]!= -6) mapa[cooy + i][coox + j] = 99; //ASSEGURA QUE PERSONAGEM NAO COMECE TRANCADO
		}

	(*obj).rect.x =coox*TAM;
	(*obj).rect.y =cooy*TAM;
	(*obj).i = cooy;
	(*obj).j = coox;

	if((*obj).cod == 2)
	{
		pos_ini_i = (*obj).rect.x;
		pos_ini_j = (*obj).rect.y;
	}
}

void desenha_lab(SDL_Surface *screen, int mapa[MAX_H][MAX_W], int n, int m, SDL_Surface* s_chipset)
{
	SDL_Rect rect= {0, 0, TAM, TAM};
	SDL_Rect corte= {0, 0, TAM, TAM};
	int i, j;
	for(i = 0; i< n; i++)
	{
		rect.y = i*TAM;
		for(j = 0; j< m; j++)
		{
			rect.x = j*TAM;
			corte.x = 0*TAM;
			//SDL_BlitSurface(s_chipset, &corte, screen, &rect);
			SDL_FillRect(screen, &rect, SDL_MapRGB(screen->format, 16, 26, 48));
			switch(mapa[i][j])
			{
				case -1: //SDL_FillRect(screen, &rect, SDL_MapRGB(screen->format, 0, 0, 255));
						corte.x = 1*TAM;
						SDL_BlitSurface(s_chipset, &corte, screen, &rect); break;
				case 1: 
				case -5:
				case -6:
				case -7:
				case -8:
				case -9:
				/*aqui entra um "case -(codigo_do_obj_escondido):" para cada objeto escondido*/
					//SDL_FillRect(screen, &rect, SDL_MapRGB(screen->format, 0, 255, 0));
					corte.x = 2*TAM;
					SDL_BlitSurface(s_chipset, &corte, screen, &rect); break;

				case 3: 
						SDL_BlitSurface(s_bomb, &r_bomb, screen, &rect); 
						break;
				case -3: 
					if(SDL_GetTicks() <= tm_explosao)
					{
						//SDL_FillRect(screen, &rect, SDL_MapRGB(screen->format, 255, 255, 0));
						SDL_SetAlpha(s_fire, SDL_SRCALPHA, (tm_explosao - SDL_GetTicks())*0.255); //efeito fade out
						SDL_BlitSurface(s_fire, &r_bomb, screen, &rect);
					}
					else
					{
						mapa[i][j] = 0;
						b1.estado = 0;
					}break;
				
				/*para cada item/ objeto a ser escondido aqui entra um "case cod_do_objeto:" e o blit correspondente*/
				case 5: //SDL_FillRect(screen, &rect, SDL_MapRGB(screen->format, 0xFF, 0x77, 0x77)); 
						corte.x = 5*TAM;
						SDL_BlitSurface(s_chipset, &corte, screen, &rect); break;
				case 6: //SDL_FillRect(screen, &rect, SDL_MapRGB(screen->format, 0x25, 0xBB, 0x88));
						if(ni<=0)
						{
							corte.x = 3*TAM;
						}
						else corte.x = 4*TAM;
						SDL_BlitSurface(s_chipset, &corte, screen, &rect); break;
				case 7:
						corte.x = 6*TAM;
						SDL_BlitSurface(s_chipset, &corte, screen, &rect); break;
				case 8:
						corte.x = 7*TAM;
						SDL_BlitSurface(s_chipset, &corte, screen, &rect); break;
				case 9:
						corte.x = 8*TAM;
						SDL_BlitSurface(s_chipset, &corte, screen, &rect); break;
			}
		}
	}
}
