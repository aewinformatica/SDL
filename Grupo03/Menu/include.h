#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#define SCREEN_W 672
#define SCREEN_H 512

typedef struct Texto
{
	SDL_Surface *imagem;
	SDL_Rect origem, destino;
} TEXTO;

typedef struct Save
{
	char nome[12];
	int vidas;
	unsigned long long int pontos;
	FILE *arquivo;
} SAVE;

typedef struct Passos
{
	int cima, baixo, direita, esquerda;
} PASSOS;

typedef struct Boneco
{
	SDL_Rect origem,destino;
	SDL_Surface *imagem;
	PASSOS passo;
} BONECO;

SAVE jogo;
SAVE save[5];

BONECO Kenny;

char nome[12];
int vidas;
unsigned long long int pontos;
int tempo_total;


int verificaMouse(TEXTO, int, int);
int colore (TEXTO *, int);
void desenha_texto(char*, SDL_Surface*, int, int, int, int, int, int);
int cliqueMouse(TEXTO, int, int);
int menu(SDL_Surface *);
void le_Saves (SDL_Surface *);
int slot (int, int);
void salva (int,SDL_Surface *);
int Fases(SDL_Surface *);
void andar (char, int, SDL_Surface *);
void le_recordes(SDL_Surface *);
int pausarJogo(int *,SDL_Event *);
unsigned long long int calcula_pontos (int, int)

