/*Computação para Informática (Linguagem C) 2008/1
Professor: Adriano
Trabalho: Jogo3.c (Teste 7)
Data: 18/06/08

Alunos:	Felipe Guerreiro Barbosa Ruiz ( DRE 108056195)
		Gabriel Pires da Silva ( DRE 108056014)
		Guilherme Carneiro Antonio ( DRE 108055602 )*/



#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
//#include <windows.h>
#include <SDL_mixer.h>

#define SCREEN_W 672
#define SCREEN_H 512
#define RAIO 1
#define TOTALBOMBAS 20
#define TOTALITENS 4
#define MAXINIMIGOS 10

typedef struct _Bomba
{
	int status, tempoini, gradex, gradey;
	SDL_Surface *imagem;
	SDL_Rect posicao, origem;
	

}_BOMBA;
//STATUS =  1(LIVRE)  -  2(ATIVA) 

typedef struct _Fogo
{
	int status, tempoini, gradex, gradey;
	SDL_Surface *imagem;
	SDL_Rect posicao;
	

}_FOGO;
//STATUS =  1(LIVRE)  -  2(ATIVO) 

typedef struct _Fases
{
	int blocosD, blocosF, inimigos, itens;
	
}_FASE;

typedef struct _inimigo {
   int status, dir, sprite, movOK;
   SDL_Surface *imagem;
   SDL_Rect posicao, origem;
}_INIMIGO ;
//STATUS =  1(VIVO) -  2(MORTO)

typedef struct Passos
{
	int cima, baixo, direita, esquerda;
} PASSOS;

typedef struct _Boneco
{
	SDL_Rect origem,destino;
	SDL_Surface *imagem;
	PASSOS passo;
} _BONECO;

typedef struct _Save
{
	char nome[12];
	int vidas;
	unsigned long long int pontos;
	FILE *arquivo;
	int slot;
} _SAVE;

typedef struct Texto
{
	SDL_Surface *imagem;
	SDL_Rect origem, destino;
} TEXTO;


//VARIAVEIS GLOBAIS
int matriz_controle[SCREEN_W/32][(SCREEN_H-32)/32];
	//DEFINICOES
		// 1 == BLOCO FIXO
		// 2 == BORDA
		// 4 == SAIDA
		// 7 == DESTRUTIVEL
		// 19 == FOGO
		// 20 + == BOMBA
int matriz_itens[SCREEN_W/32][(SCREEN_H-32)/32];
	//DEFINICOES
		// 1 == +VIDA
		// 2 == +BOMBA
		// 3 == +RAIO BOMBA
		// 4 == +500
int matriz_personagens[SCREEN_W/32][(SCREEN_H-32)/32];
	//DEFINICOES
		// 1 == BOMBERMAN
		// 2 == INIMIGO

		
int a,contador, maxBombas, raio, faseAtual, vidas, tempoExpBomba, tempoPintaFogo, tempo_total;
_FASE fases[1];
_INIMIGO inimigos[MAXINIMIGOS];
_BONECO Kenny;
_SAVE jogo;
_SAVE save[5];

//PROTOTIPOS FUNCOES
int colisaoBaixo(int x, int y);
int colisaoCima(int x, int y,int vel);
int colisaoDireita(int x, int y);
int colisaoEsquerda(int x, int y, int vel);
int colisaoSaida(int x, int y);
int explodeBomba (int x, int y, int r, int *bomba, int *cont_explosao);
int verificaItem(int gradex, int gradey);

void reinicia_jogo(SDL_Rect *boneco_dst, int *cima, int *baixo, int *esquerda, int *direita, int *bomba);
int pausarJogo(int *pause, SDL_Event *evento);
void tempoBomba(_BOMBA *bomba, _FOGO *fogo, int *bombasAtivas, int *fogosAtivos, int *);
void tempoFogo(_FOGO *, int *);
void pintaFogo(_FOGO *, int *);
void despintaFogo(_FOGO *);
void montarMapa(void);
void calculaBlocosF(void);
void calculaBlocosD(void);
void valoresFases(void);
void calculaItens(void);
void colisaoItem(int x, int y);
void calculaInimigos(void);
void morrePersonagem(void);
void mover_inimigo(int velocidade, int control);
void blitaInimigo(SDL_Surface *dest);
void sprite_inimigo(void);

int verificaMouse(TEXTO, int, int);
int colore (TEXTO *, int);
void desenha_texto(char*, SDL_Surface*, int, int, int, int, int, int);
int cliqueMouse(TEXTO, int, int);
int menu(SDL_Surface *);
void le_Saves (SDL_Surface *);
int slot (int, int);
void salva (int);
int Fases(SDL_Surface *);
void andar (char, int, SDL_Surface *);
void le_recordes(SDL_Surface *);
int Jogo (SDL_Surface *);
int compara(const void *, const void *);
void salva_recordes();
