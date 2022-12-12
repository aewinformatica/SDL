/*
	Projeto Final de Computação para Informática 1

	~*~*~*~*~*~*~  =^^= BomberKitty =^^=  ~*~*~*~*~*~*~

	Alunas: Camila Campos, Carina Dias e Paula Loureiro

*/

#include <string.h>
#include<SDL.h>
#include<SDL_image.h>
#include <SDL_mixer.h>
#include <time.h>

#define SCREEN_W 850
#define SCREEN_H 650
#define MAX 17
#define DIM 13
#define DEL 100

SDL_Surface* screen;

SDL_Rect chao = {0, 0, 50,50};

SDL_Surface* hello;
SDL_Rect dst_hello = {50,50, 0, 0}; /*Posicao inicial da Hello*/

SDL_Surface* choco;
SDL_Rect dst_choco={550,300,0,0};
SDL_Rect dst_choco1={600,550,0,0};
SDL_Rect dst_choco2={400,550,0,0};


SDL_Surface* vidas3;
SDL_Rect dst_vidas3;

SDL_Surface* vidas2;
SDL_Rect dst_vidas2;

SDL_Surface* vidas1;
SDL_Rect dst_vidas1;

SDL_Surface* vidas0;
SDL_Rect dst_vidas0;

SDL_Surface* me;
SDL_Rect dst_me;

SDL_Surface* nu;
SDL_Rect dst_nu;

SDL_Surface* door;
SDL_Rect dst_door;

SDL_Surface* quad;
SDL_Rect dst_quad = {0, 0, 0, 0};

SDL_Surface* quad2;
SDL_Rect dst_quad2;

SDL_Surface* tile;
SDL_Rect dst_tile = {100,100, 0, 0};

SDL_Surface* bomba;
SDL_Rect dst_bomba;

SDL_Rect ve_hello = {0, 0, 50,50};

//Background do Menu
SDL_Surface* menubg;
SDL_Rect dst_menubg = {0, 0, 0, 0};

//Botoes
SDL_Surface *b1;
SDL_Rect dst_b1 = {300, 250, 0, 0};
SDL_Surface *b2;
SDL_Rect dst_b2 = {300, 350, 0, 0};
SDL_Surface *b3;
SDL_Rect dst_b3 = {300, 450, 0, 0};

//Botoes selecionados
SDL_Surface *b1u;
SDL_Rect dst_b1u = {300, 250, 0, 0};
SDL_Surface *b2u;
SDL_Rect dst_b2u = {300, 350, 0, 0};
SDL_Surface *b3u;
SDL_Rect dst_b3u = {300, 450, 0, 0};


//Botoes pressionados
SDL_Surface *b1p;
SDL_Rect dst_b1p = {300, 250, 0, 0};
SDL_Surface *b2p;
SDL_Rect dst_b2p = {300, 350, 0, 0};
SDL_Surface *b3p;
SDL_Rect dst_b3p = {300, 450, 0, 0};

//Estado inicial dos botoes(0 para botao, 1 para selecionado, 2 para pressionado)
int b1state = 0;
int b2state = 0;
int b3state = 0;

//sons
Mix_Music* music;
Mix_Chunk* bombsnd;

int a, b;

#include "menu.h"
int menu(int m);

#include "funcoes.h"
void Labirinto(int grade[DIM][MAX] , SDL_Surface* quad, SDL_Surface* screen, int vidas);
void hello_andando(char *passo1, int grade[DIM][MAX],SDL_Surface* hello);
void explode(int grade[DIM][MAX]);
int bombando(void);
void escreve_matriz(int grade[DIM][MAX]);
int morrendo(int vidas);
void escondendo (int grade[DIM][MAX]);
void gameover(int life);
void achou(int grade[DIM][MAX]);
void andachoco(SDL_Rect *dst_choco, int grade[DIM][MAX]);
int mata_hello(SDL_Rect *dst_choco,int vidas);
void mata_choco(SDL_Rect *dst_choco,int grade[DIM][MAX]);

#include "instintro.h"
void inst(int b2state);
void intro ();

#include "jogo.h"
int jogo(int estado);


int main(int argc, char **argv)
{
	intro();
	return 0;
}
