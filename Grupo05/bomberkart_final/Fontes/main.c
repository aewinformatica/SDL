/*	Programa: Bomber Kart
	Autores: Daniel Lopes Braz Dos Santos
		     Gustavo Rodrigues Lima
		     Renan da Costa Garrot
	Data: XX/XX/XXXX
	Descrição: Projeto final do curso de computação 1

*/

#include "include.h"

int Abertura(SDL_Surface*);
int Menu(SDL_Surface*);
int fase(SDL_Surface*);

int musicON = 1;
int vidas;
int inimigos;
int pontos;
int del = 30;

int main(int argc, char** argv)
{
	int op;

	SDL_WM_SetCaption("Bomber Kart","bomberkart");

	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER);

	SDL_Surface* screen;
	screen = SDL_SetVideoMode(SCREEN_W, SCREEN_H, 16, SDL_SWSURFACE);

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096)) 
	{
	    puts("Erro");
	    exit(1);
	}// INICIA O AUDIO 
	Mix_AllocateChannels(1);
		
	if(Abertura(screen)) return 1;
	
	while((op = Menu(screen))) // OP = 0 -> SAIR
	{
		switch (op)
		{
		case 1: // OP = 1 -> NOVO JOGO
			vidas = 3;
			inimigos = 5;
			pontos = 0;
			while(fase(screen) == 100);
			break;
		
		default:
			break;
		}
	
	}

	SDL_Quit();
	return 0;
}

