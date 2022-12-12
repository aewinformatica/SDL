#ifndef _INCLUDE_BOMBER_H

#define _INCLUDE_BOMBER_H

#include <SDL/SDL.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>

#define SCREEN_W 800
#define SCREEN_H 600
#define MAPA_W 800
#define MAPA_H 512
#define BITD 16

#define TILE_DIM 32
#define NCAIXAS 80

#define FONTSIZE 38

#define NCHANNEL 7

#define REPEAT_DELAY 200
#define REPEAT_INTERVAL 10
#define MAX_TEMPOFOGO 200
#define MAXMSEC 50 /* FPS= 1000/MAXMSEC & MAXMSEC = 1000/FPS*/
#define MAXBOMBAS 5
#define MAXNOME 13
#define MAXJ 5

#define TOTAL_MONSTROS 9

#define SCOREMONSTRO 50
#define SCORECAIXA 5
#define SCOREITEM 25

#define TEMPOTEXTO 2300

enum Tipo_tile {PAREDE, CHAO, CAIXA, FOGO, BOMBA, ITEM, SAIDA_FECHADA, SAIDA_ABERTA};
enum Direcao_bomberman {PARADO, CIMA, DIREITA, BAIXO, ESQUERDA};
enum Tipo_colisao {NCOLISAO,COLISAO, MORTO, C_ITEM};
enum Estado_jogo {JOGANDO,INTRODUCAO,MENUABERTURA,MENUJOGO,TELAOPCOES,PAUSE,GAMEOVER,NOME,HIGHSCORE,ABERTURA};
enum Opcao_menu {NOVOJOGO, O_HIGHSCORE, SAIR};

enum Tipo_jogadores {BOMBERMAN, INIMIGO};

/*================ STRUCTS e Tipos ======================*/
typedef struct tile
{
    SDL_Surface *superficie;
    SDL_Rect dest;
    enum Tipo_tile tipo;
    int tempo_fogo;
}TILE;

typedef struct personagem
{
    SDL_Surface *superficie;
    SDL_Rect orig[12];
    SDL_Rect dest;
	enum Direcao_bomberman movimento;
    int velX, velY, vel;
    int max_bombas;
    int estado, morrendo, vidas;
	int em_cima;
}PERSONAGEM;

typedef struct objeto
{
    SDL_Surface *superficie, *sup_fogo;
    SDL_Rect orig[5];
    SDL_Rect dest;
    int estado, alcance;
    int tempo_inicial;
    int tempo_explosao;
	int velx,vely;
	
	int quem_colocou;
}OBJETO;

typedef struct _jogador
{
    char nome[MAXNOME];
    int score;
}JOGADOR;

typedef struct _MONSTRO
{
	SDL_Surface *surf;
	SDL_Rect src[12];
	SDL_Rect dst;
	int estado;
	int velX, velY;
	int direcao;
	int movendo;
	int movimentoAleatorio;
	int vivo;
	int manterDirecao;
	OBJETO bomba[1];
	int num_bomba;
	int alcance_bomba;
}MONSTRO;

/*==================Prototipos=====================*/
void Init_Surfaces(void);
void Init_Cenario(void);
void Init_Sons(void);
void Init_Bomberman(void);
void Init_Bomba(OBJETO *);
void Bomberman_move(int direcao);
void Update_bomberman(void);
int  Detecta_colisao(PERSONAGEM *);
void Bota_Bomba(void);
void Explode_Bomba(OBJETO *);
void Desenha_cenario(void);
void Desenha_Pause(int x, int y, TTF_Font *font);
void Desenha_Gameover(int x, int y, TTF_Font *font);
void Desenha_Texto(char *frase,int x ,int y, SDL_Color);
void Desenha_MenuJogo(enum Opcao_menu selecao);
void Desenha_Infos(void);
void Limita_fps(int );
void Gera_Item(int x, int y);
void Pegar_Item(int x, int y);
void Load_Highscore(void);
void Adiciona_Highscore(char *nome, int score);
int Compara(const void *e1, const void *e2);
void Init_Jogador(void);
void Desabilita_Sons(void);

int Colisao_Bomberman_Bomba(void);
int Colisao_Bomberman_Monstro(int monstro);
int Colisao_Monstro_Bomba(int monstro);

void Init_Monstros(void);
void Update_Monstro(int);
void Movimentar_Monstro(int);
void Movimentar_Monstros(void);
void Desenha_Monstros(void);
void escolheDirecao(int);
int Colisao_Monstro_Cenario(int);
int Colisao_Monstro_Monstro(int, int);
int Colisao_Monstro_MonstroEmMovimeto(int, int);
int Tem_Monstro(int, int, int);

void Init_Cenas(void);
void Desenha_Abertura(int);
void Fonte_Default(void);

void escolheBomba(int);
void Monstros_Explode_Bomba(void);
void Monstro_Bota_Bomba(int);
void Monstros_Desenha_Bomba(void);
void Init_Bomba_Monstros(void);
void Monstro_Pegar_Item(int, int, int);

/*====================Variaveis Globais=========================*/
TILE cenario[MAPA_W/TILE_DIM][MAPA_H/TILE_DIM]; /* 20 15 */
SDL_Surface *screen;
PERSONAGEM bomberman;
int quit;

OBJETO bomba[MAXBOMBAS];

FILE *arq_highscore;

SDL_Surface *surf_chao, *surf_parede, *surf_caixa, *surf_bomberman,
            *surf_bomba, *surf_fogov, *surf_fogoh, *surf_fogoc,
			*surf_gameover, *surf_ibomba, *surf_ipatins, *surf_ifogo,
			*surf_ivida, *surf_saida, *surf_infos, *surf_bomberman_morrendo,
			*surf_nome, *surf_highscore, *surf_som_ok, *surf_som_des, *surf_monstro, *surf_ovo;

SDL_Surface *tela_menu, *tela_abertura;

JOGADOR jogador, jogador_high[MAXJ];

Mix_Chunk *explosao, *novoitem, *morte, *saida, *click, *seleciona;
Mix_Music *musica_jogo1, *musica_jogo2, *musica_jogo3, *musica_abertura, *musica_highscore;
int som;

TTF_Font *font_times;

enum Estado_jogo estado_jogo;

MONSTRO monstros[TOTAL_MONSTROS];

/* ==================Funcoes=================*/

#endif
