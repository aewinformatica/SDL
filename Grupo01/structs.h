#ifndef STRUCTS_H_INCLUDED
#define STRUCTS_H_INCLUDED

typedef struct _PERSONAGEM
{
    SDL_Surface *img;
    SDL_Rect destino;
    SDL_Rect origem;
    int i, j;
    int passo;
    int movendo;
    int estado, atingido;
} PERSONAGEM;

typedef struct _INIMIGO
{
    int vidas, nivel;
    SDL_Rect destino;
    SDL_Rect origem;
    int i, j;
    int estado, atingido;
    int movendo, dir;
} INIMIGO;

typedef struct _BOMBA
{
    int i, j, planted;
} BOMBA;

typedef struct _MOUSE
{
    SDL_Surface* img;
    SDL_Rect posicao;
} MOUSE;

typedef struct _JOGADOR
{
	char nome[16];
	int fim, tempo, versao;
	long int pontos;
} JOGADOR;

typedef struct _EXIT_FASE
{
    int i, j;
} EXIT_FASE;

typedef struct _SAVE
{
    int existe, fase, vidas, tempo, dificuldade, versao;
    long int pontos;
    char nome[16];
} SAVE;

#endif // STRUCTS_H_INCLUDED
