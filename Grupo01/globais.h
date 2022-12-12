#ifndef GLOBAIS_H_INCLUDED
#define GLOBAIS_H_INCLUDED

BOMBA bomb[5];
BOMBA fila[10];
BOMBA fila2[10];

SAVE saves[5];

MOUSE cursor;

SDL_Rect botoes[16];

SDL_Surface* maca;
SDL_Surface* porta;
SDL_Surface* fundo;
SDL_Surface* bomba;
SDL_Surface* bonus1;
SDL_Surface* bonus2;
SDL_Surface* screen;
SDL_Surface* bomber;
SDL_Surface* janela;
SDL_Surface* pinguim;
SDL_Surface* inimigo1;
SDL_Surface* inimigo2;
SDL_Surface* inimigo3;
SDL_Surface* inimigo4;
SDL_Surface* inimigo5;
SDL_Surface* bloco_ind;
SDL_Surface* bloco_dest;
SDL_Surface* nome_do_jogo;
SDL_Surface* explosao_hor;
SDL_Surface* explosao_vert;
SDL_Surface* explosao_centro;

JOGADOR jogador;
JOGADOR recordista_T[5];
JOGADOR recordista_P[5];

INIMIGO inimigo[10];

PERSONAGEM personagem;

EXIT_FASE saida;

TTF_Font* my_font22;
TTF_Font* my_font16;
TTF_Font* my_font72;

Mix_Chunk* clica;
Mix_Chunk* explosao;
Mix_Chunk* planta_bomba;

Mix_Music* menu;
Mix_Music* jogo;
Mix_Music* le_nome;
Mix_Music* vitoria;
Mix_Music* derrota;

int ciclo;
int inicio_fase;
int fase, vidas;
int tempo, tempo1;
int cascata, botao;
int estado, dificuldade;
int venceu, fez_recorde;
int inicio_fila, fim_fila;
int mapa[GRADE_H][GRADE_W];
int inicio_fila2, fim_fila2;
int existe_bomba, range, max_bombas;

char nome_saves[5][16];

#endif // GLOBAIS_H_INCLUDED
