//new
#include "global.h"

typedef struct
{
	SDL_Rect rect;
	int i;
	int j;
	int incx;
	int incy;
	int mov;
	int cod; //codigo bomber=2
	int vida;
	int pts; //pontos
	int ai;
	int direcao[4];
	int invencibilidade;
	int walk_control;
	SDL_Rect r_anima;
	SDL_Surface* grafico;
}Obj_Dinamico;

typedef struct
{
	int x;
	int y;
	int estado;
}Bomba;

typedef struct
{
	char nome[10];
	int pontos;
}InfPlayer;

int tm_explosao;
int raio, mapa[MAX_H][MAX_W]; //MATRIZ DO LABIRINTO
Bomba b1; //BOMBA 1
Obj_Dinamico bomberman; //OBJETO DINAMICO CONTROLADO PELO JOGADOR
Obj_Dinamico *inimigo; //OBJETO DINAMICO INIMIGO
int pos_ini_i;
int pos_ini_j;
SDL_Rect r_hero;
int ni;
int step;
int bomber_morreu;
SDL_Event event;
SDL_Surface* screen;
int C_X, C_Y;
SDL_Surface* s_bomb;
SDL_Rect r_bomb;
SDL_Surface* s_fire;
SDL_Rect pos;
TTF_Font* my_font;
TTF_Font* my_font2;
int controlador;
int fim_do_nivel;
int move_lab;
InfPlayer player;


/* labirinto.c*/
void cria_lab(int mapa[MAX_H][MAX_W], int n, int m, int bld);

void posiciona_indestrutiveis(int mapa[MAX_H][MAX_W], int n, int m);

void posiciona_dinamico(int mapa[MAX_H][MAX_W], int n, int m, Obj_Dinamico *obj);

void posiciona_caixas(int mapa[MAX_H][MAX_W], int n, int m, int bld);

void desenha_lab(SDL_Surface *screen, int mapa[MAX_H][MAX_W], int n, int m, SDL_Surface* s_chipset);

void esconde(int mapa[MAX_H][MAX_W], int n, int m, int q, int cod);
/*movimento*/
void alinhar(Obj_Dinamico *obj);

void define_din(Obj_Dinamico *obj,int x, int y, int i, int j, int inx, int iny, int cod, int ai);

void mover(Obj_Dinamico *obj, int x, int y, int step, int mapa[MAX_H][MAX_W], int dir);

void checa_direcionais(int teclado[4], Obj_Dinamico *bomberman, int *step, int mapa[MAX_H][MAX_W]);

int checa_passagem(int n);

void move_inimigo(Obj_Dinamico *obj, int step, int mapa[MAX_H][MAX_W]);

int checa_colisao(SDL_Rect a, SDL_Rect b);

void mover2(Obj_Dinamico *obj, int x, int y, int step, int mapa[MAX_H][MAX_W]);

void verifica_colisao(void);

void invencibilidade_temp(int duracao, Obj_Dinamico* obj);

Uint32 timer_invencibilidade(Uint32 interval, void *param);

void animacao_andar(SDL_Rect *r_hero, Obj_Dinamico *dinamico); //para spites de 3 quadros 32x32

void animacao_andar_hero(SDL_Rect *r_hero, Obj_Dinamico *dinamico); //para sprites de 6 quadros 40x24

/*explode*/

void ativar_bomba(Bomba *bomba, int mapa[MAX_H][MAX_W], Obj_Dinamico *obj);

Uint32 funcao_timer(Uint32 interval, void *param);

void explode(int mapa[][MAX_W], int coox, int cooy, int raio, int dir);

int avalia_ex(int coox, int cooy);

void direcionar(int dir, int *ix, int *iy);

void morre_bomber();

void morre_inimigo(int cooy, int coox);

/*outras funcoes*/
int menu2 (SDL_Surface *screen, int* voltar_pro_menu_inicial); 

void apaga_texto(SDL_Surface* dst, int x, int y);

void desenha_texto(char* texto, SDL_Surface* dst, int x, int y);

int f_menu (void);

void f_introducao(void);

int f_jogo (void);

void novo_jogo(int* n, int* m, int* step, int direcionais[4], int lvl, SDL_Surface* ambiente);

void animacao_morte(SDL_Surface* tela, Obj_Dinamico* obj, SDL_Rect pos, SDL_Surface* s_hero);

void recorde (void);

void show_rec (void);
