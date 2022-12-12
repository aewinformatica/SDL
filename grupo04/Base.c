/*
V.A.D. Project - Base

Bibliotecas SDL disponíveis em http://www.libsdl.org
Versão usada no desenvolvimento do jogo...
...SDL - 1.2.13.0
...SDL_image - 1.2.6.0
...SDL_mixer - 1.2.8.0

NFont está disponivel em http://pubpages.unh.edu/~jmb97
Versão usada no desenvolvimento do jogo é 1.611
*/

#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include<stdlib.h>
#include<time.h>
#include<values.h>
#include<math.h>

#define SCREEN_W 800 //Largura da tela.
#define SCREEN_H 600 //Altura da tela.
#define SCREEN_DEPTH 24 // Bit-depth da screen.

//Tamanhos/definições dos objetos.
#define SIZE_PLAYER 80
#define SIZE_BIG_BALL 80
#define SIZE_MED_BALL 40
#define SIZE_SMA_BALL 20
#define NUM_EN 100 //Define o número máximo de bolas inimigas.
#define FPS_MAX 25 //O valor deve ser de 1000/fps, sendo "fps" o máximo de fps desejado.
#define VELMAX 5 //Velocidade máxima de quando uma bola é atirada.

#define NUMJOG 10 //Número máximo de jogadores no highscores.
#define TAMNOME 10 //Tamanho máximo do nome de cada jogador no highscores.

//Este typedef é para as bolas inimigas no jogo. Vai armazenar tudo relacionado a elas.
typedef struct _BALL
{
	int estado; //0 é invisível/desativada; 1 é grande; 2 é média; 3 é pequena; 4 ou qualquer outra coisa é pequena capturada.
	float posX, posY; //armazena a posição. perceba que NÃO está inicializada. a decisão de usar float aqui é que vai ser mais fácil pra gerenciar as velocidades
					//. vai ser arredondada/convertida em SDL_Rect (integers) quando for desenhada.
	float velaspX, velaspY; //armazena a velocidade dos inimigos.
	int atirada; //vai indicar se a bola pequena foi atirada. 0 é não; 1 é acelerando; 2 é desacelerando.
} BALL;

typedef struct _DIFICULDADE //Armazena a quantidade de bolas inimigas em cada fase.
{
	int easy[10];
	int medium[10];
	int hard[10];
} DIFICULDADE;

struct _BOLA
{
	int comprimento, altura;  //Comprimento, Altura, Velocidade Horizontal, Velocidade Vertical
	float velH, velV;
	SDL_Rect rect;
	SDL_Surface *surface;

	int qtdebolas;	//Numero de bolas filhas//
	int colidiu, visivel;

	//Variaveis usadas quando a bola é pequenina//
	int grudada, disparada;
	int posRelX, posRelY;
	float acumuladorX, acumuladorY;

	struct _BOLA *filhas;
};

typedef struct _JOGADOR
{
	int comprimento, altura;
	int vidas;
	int estado; //0 é normal; 1 é pisca-pisca; 2 é bolas pequenas nao encostam.		
	int bolasDestruidas;
	int pontos;
	Uint32 tempo;

	SDL_Rect rect;
	SDL_Surface *surface;
} JOGADOR;

typedef struct _BOLA BOLA;

typedef struct _HIGHSCORE
{
	int recorde;
	char nome[TAMNOME];
} HIGHSCORE;

//---------------------------------------------------------------------------------------------

int arredonda(float num);
int pitagoras(SDL_Rect rect1, int comprimento1, SDL_Rect rect2, int comprimento2);
int alteraBolas(BOLA *bolas, BOLA pai, int indice);
void calculaVelocidade(float aspectX, float aspectY, float *velAspX, float *velAspY);
void perpendicular(float aspectX, float aspectY, float *perp1X, float *perp1Y, float *perp2X, float *perp2Y);
void vaiParaBorda(BOLA *bolas, int mouseX, int mouseY);
void ballBlitter(BALL *bolas, SDL_Surface *screen, SDL_Surface *grande, SDL_Surface *medio, SDL_Surface *pequeno, int mouseX, int mouseY);
void Blit(SDL_Surface *image, SDL_Surface *dst, int x, int y);
int atira(BOLA *bolas, JOGADOR *jogador, int bolasNaTela);
void toro(BOLA *b);
void movimento(BOLA *b, JOGADOR *jogador);
void subdivide(BOLA *b1);
void colisao(BOLA *bolas, int bolasNaTela, JOGADOR *jogador, Mix_Chunk *somexplo, Mix_Chunk *somexplo2);
void atualizaTela(BOLA *bolas, int bolasNaTela, JOGADOR *jogador, SDL_Surface* tela, Mix_Chunk *somexplo, Mix_Chunk *somexplo2);
void adicionaFilhas(BOLA *pai, BOLA *filha);
void organizaBolas(BOLA *bolas, JOGADOR *jogador, int bolasNaTela);
void highOrdena(HIGHSCORE *s1);
void trocaRecorde(HIGHSCORE *s1, HIGHSCORE s2);
Uint32 toogleEstado(Uint32 intervalo, void *parametro);
BOLA novaBola(int comprimento, int altura, float velH, float velV, int filhas, int visivel, SDL_Surface *surface);
BOLA novoGrupoBolas(SDL_Surface *surfacePai, SDL_Surface *surfaceFilha, SDL_Surface *surfaceNeta);
JOGADOR carregaJogador();
//tenha certeza que há uma linha em branco abaixo.
