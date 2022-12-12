/*
	
	Arquivo: 	game.c
	
	Alunos:	Nadeem Ahmad Tahir
			Leonardo Polly Assumpcao
			Diego Fonseca Pereira de Souza
	
	Descrição:	Movimentação do Bomberman no labirinto gerado aleatoriamente ao iniciar o jogo, é possivel 				colocar bombas pressionando espaço.
	
*/

#define screen_w 608
#define screen_h 480
#define true 1
#define false 0
#define TempoFogo 20
#define TempoCrescimento 2
#define pausa 17
#define tempo 3
#define InitBombs 1
#define InitChama 2
#define InitVidas 3

int quit=0;
int kleft, kright, kup, kdown, kspace, vidas = InitVidas, score, score2;
int FirePower=InitChama, Bombs=0, MaxBombs=InitBombs;

#include<SDL.h>
#include<SDL_mixer.h>
#include<string.h>
#include<stdlib.h>
#include <SDL_image.h>
#include<time.h>
#include"Funcoes.h"
#include"Genericas.h"
#include"Bomber.h"
#include"Bomba.h"
#include"Wall.h"
#include"WoodBox.h"
#include"Explosion.h"
#include"Explosion2.h"
#include"Fire.h"
#include"Dog.h"
#include"Caveira1.h"
#include"BomberBurn.h"
#include"Fogo.h"

int Clock0;
SDL_Event sdlevent;

void Loop(void)
{
	int i;
	ChecarEventos();
	SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
	DesenheBackground("iFloor");
	
	for (i=0;i < nobj; i++)
	{
		if (obj[i].vivo)
		{
			Desenhe(&obj[i]);
			
			Movimentar(&obj[i]);
			
			Colisoes(&obj[i]);
			
			AtualizeRelogio(&obj[i]);
		}
	}
	
	DrawBarra();
	
	UpdateObjs();
	
	SDL_Flip(screen);
}

void pare(void)
{
	//Funçao para ajudar na depuração
}

void aoCriar(Tobj *o)
{
	if (!strcmp(o->nome,"Explosion"))
		aoCriar_Explosion(o);
	
	if (!strcmp(o->nome,"Fogo"))
		aoCriar_Fogo(o);
	
	if (!strcmp(o->nome,"Explosion2"))
		aoCriar_Explosion2(o);
	
	if (!strcmp(o->nome,"BomberBurn"))
		aoCriar_BomberBurn(o);
	
	if (!strcmp(o->nome,"Bomba"))
		aoCriar_Bomba(o);
	
	if (!strcmp(o->nome, "Bomber"))
		aoCriar_Bomber(o);
	
	if (!strcmp(o->nome, "WoodBox"))
		aoCriar_WoodBox(o);
	
	if (!strcmp(o->nome, "Wall"))
		aoCriar_Wall(o);
	
	if (!strcmp(o->nome, "FireN") || !strcmp(o->nome, "FireS") || !strcmp(o->nome, "FireL") || !strcmp(o->nome, "FireO"))
		aoCriar_Fire(o);
	
	if (!strcmp(o->nome, "FireNS") || !strcmp(o->nome, "FireLO") || !strcmp(o->nome, "FireM"))
		aoCriar_Fire2(o);
	
	if (!strcmp(o->nome, "Dog"))
		aoCriar_Dog(o);
		
	if (!strcmp(o->nome, "Caveira1"))
		aoCriar_Caveira1(o);
}

void aoDestruir(Tobj *o)
{
	if (!strcmp(o->nome, "WoodBox"))
		aoDestruir_WoodBox(o);

	if (!strcmp(o->nome, "Dog"))
		aoDestruir_Dog(o);
	
	if (!strcmp(o->nome, "Caveira1"))
		aoDestruir_Caveira1(o);
	
	if (!strcmp(o->nome,"Bomba"))
		aoDestruir_Bomba(o);
	
	if (!strcmp(o->nome,"Bomber"))
		aoDestruir_Bomber(o);
}

void aoDesenhar(Tobj *o)
{
	
}

void aoTerminarAnim(Tobj *o)
{
	if (!strcmp(o->nome, "Explosion"))
		aoTerminarAnim_Explosion(o);
	
	if (!strcmp(o->nome, "Explosion2"))
		aoTerminarAnim_Explosion2(o);
	
	if (!strcmp(o->nome, "BomberBurn"))
		aoTerminarAnim_BomberBurn(o);
	
	if (!strcmp(o->nome, "Bomba"))
		aoTerminarAnim_Bomba(o);
}

void Movimentar(Tobj *o)
{
	if (!strcmp(o->nome,"Bomber"))
		Movimentar_Bomber(o);
	
	if (!strcmp(o->nome,"Bomba"))
		Movimentar_Bomba(o);
}

void aoClock0(Tobj *o)
{
	if (!strcmp(o->nome, "Dog"))
		aoClock0_Dog(o);
	
	if (!strcmp(o->nome, "Fogo"))
		aoClock0_Fogo(o);
	
	if (!strcmp(o->nome, "BomberBurn"))
		aoClock0_BomberBurn(o);
	
	if (!strcmp(o->nome, "Caveira1"))
		aoClock0_Caveira1(o);
	
	if (!strcmp(o->nome,"Bomba"))
		aoClock0_Bomba(o);
	
	if (!strcmp(o->nome, "FireN") || !strcmp(o->nome, "FireS") || !strcmp(o->nome, "FireL") || !strcmp(o->nome, "FireO"))
		aoClock0_Fire(o);
	
	if (!strcmp(o->nome, "FireNS") || !strcmp(o->nome, "FireLO") || !strcmp(o->nome, "FireM"))
		aoClock0_Fire2(o);
}

void aoClock1(Tobj *o)
{
	if (!strcmp(o->nome, "FireN") || !strcmp(o->nome, "FireS") || !strcmp(o->nome, "FireL") || !strcmp(o->nome, "FireO"))
		aoClock1_Fire(o);
}

void Colisoes(Tobj *o)
{
	if (!strcmp(o->nome, "Bomber"))
		Colisoes_Bomber(o);
	
	if (!strcmp(o->nome, "Caveira1"))
		Colisoes_Caveira1(o);

	if (!strcmp(o->nome, "Dog"))
		Colisoes_Dog(o);
	
	if (!strcmp(o->nome, "Bomba"))
		Colisoes_Bomba(o);
}

void Game(void)
{
	int i, j, start_time = -1000000;
	score = score2 = 0;
	vidas = InitVidas;
	Clock0 = SDL_GetTicks();
	
		//Crie(Nome, x, y)
	
	Crie("Bomber",32,96);
	
	for(i=0;i<screen_w/32;i++)
		Crie("Wall",i*32,64);
	for(i=0;i<screen_w/32;i++)
		Crie("Wall",i*32,screen_h-32);
	for(i=3;i<screen_h/32-1;i++)
		Crie("Wall",0,i*32);
	for(i=3;i<screen_h/32-1;i++)
		Crie("Wall",screen_w-32,i*32);
	
	for (i=1;i<9;i++)
		for (j=1;j<7;j++)
			Crie("Wall", 64*i,64*j);
	
	for (i=0;i<60;i++)
		Crie("WoodBox",64,64);
	
	i = rand()%3+1;
	for (j=0;j<i;j++)
		Crie("Caveira1",64,32);
	
	i = rand()%3+1;
	for (j=0;j<i;j++)
		Crie("Dog",64,32);
	
	UpdateZ();
	
	PlayMusica("Musicas/Classical - I Like Chopin (Techno Remix).ogg");
	
	while (!quit)
	{
		if (SDL_GetTicks() - start_time > pausa)
		{
			start_time = SDL_GetTicks();
			Loop();
		}
		else
		{
			SDL_Delay(1);
		}
	}
	
	KillAll();
}

int main(int argc, char **argv)
{
	Iniciar();
		
	CarregarTudo();
	
	//Abertura();
	
	Menux();
	
	Finalizar();
	
	return 0;
}

void DrawBarra(void)
{
	int n = BuscaImg("iBarra"), i, m, s;
	char sc[10];
	SDL_Rect a={0,0,0,0};
	if (n != -1)
	{
		SDL_BlitSurface(pic[n].img, NULL, screen, &a);
		
		DesenheFrame("iNumeros", vidas, 247,16);
		
		DesenheFrame("iNumeros", MaxBombs, 324,17);
		
		DesenheFrame("iNumeros", FirePower, 400,17);
		
		if (score > score2)
			score2++;
		
		sprintf(sc,"%d", score2);
		
		for (i=strlen(sc)-1;i>=0;i--)
			DesenheFrame("iNumeros", sc[i]-'0', 192-(strlen(sc)-i)*11,16);
		i = tempo*60-(SDL_GetTicks()-Clock0)/1000;
		
		m = i/60;
		s = i%60;
		
		if (i<0)
		{
			vidas = 0;
			DestruaObj("Bomber");
			m=0;
			s=0;
		}
		
		sprintf(sc,"%2d:%2d", m, s);
		
		for (i=strlen(sc)-1;i>=0;i--)
		{
			switch(sc[i])
			{
				case ':':
					DesenheFrame("iNumeros", 10, 565-(strlen(sc)-i)*11,15);
					break;
				case ' ':
					DesenheFrame("iNumeros", 0, 565-(strlen(sc)-i)*11,15);
					break;
				default:
					DesenheFrame("iNumeros", sc[i]-'0', 565-(strlen(sc)-i)*11,15);
			}	
		}
	}
}

void ChecarEventos(void)
{
	while(SDL_PollEvent(&sdlevent))
	{
		switch(sdlevent.type)
		{
			case SDL_QUIT: quit = 1; break;
			case SDL_KEYDOWN:
				switch(sdlevent.key.keysym.sym)
				{
					case SDLK_ESCAPE:
						quit = 1;
						break;
					
					case SDLK_LEFT:
						kleft=true;
						break;
					case SDLK_RIGHT:
						kright=true;
						break;
					case SDLK_UP:
						kup=true;
						break;
					case SDLK_DOWN:
						kdown=true;
						break;
					case SDLK_SPACE:
						kspace=2;
						break;
					default: break;
				}
				break;
			case SDL_KEYUP:
				switch(sdlevent.key.keysym.sym)
				{
					case SDLK_LEFT:
						kleft=false;
						break;
					case SDLK_RIGHT:
						kright=false;
						break;
					case SDLK_UP:
						kup=false;
						break;
					case SDLK_DOWN:
						kdown=false;
						break;
					case SDLK_SPACE:
						kspace=false;
					default: break;
				}
				break;
			default: break;
		}
	}
}

