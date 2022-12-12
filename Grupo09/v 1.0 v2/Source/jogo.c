/*
	Programa : Donut´s Invasion
	Nome : Matheus Ribeiro Motta de Almeida , Luis M. Novaes, Victor Landeira
	E-mail : Mirhous.mm@gmail.com
	Data  : 2008/11/27
*/

/*------ LIBRARIES ------*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>


/*------ CONSTANTS ------*/

#define TRANS_COLOR_R 255
#define TRANS_COLOR_G 0
#define TRANS_COLOR_B 255

#define S_WIDTH 800
#define S_HEIGHT 600
#define S_DEPTH 32

#define NUM_BALLS_MAX 200
#define NUM_BALLS_SIZES 3
#define SPEED_MAX 3

#define NEXT_LOOP 34 //30 fps

#define NUM_BACK_IMG 10

#define IMG_BACKGROUND_GAME "Images/background.png"
#define IMG_BACKGROUND_GAME_2 "Images/background_2.png"
#define IMG_BACKGROUND_GAME_3 "Images/background_3.png"
#define IMG_BACKGROUND_GAME_4 "Images/background_4.png"
#define IMG_BACKGROUND_GAME_5 "Images/background_5.png"
#define IMG_BACKGROUND_OVER "Images/gameOver.png"
#define IMG_BACKGROUND_TUTO "Images/tutorial.png"
#define IMG_BACKGROUND_INTRO "Images/ufrjLogo.png"
#define IMG_BACKGROUND_INTRO2 "Images/gameLogo.png"
#define IMG_BACKGROUND_RECORDS "Images/gameRecords.png"

#define INDEX_BACK_GAME 0
#define INDEX_BACK_GAME_2 1
#define INDEX_BACK_GAME_3 2
#define INDEX_BACK_GAME_4 3
#define INDEX_BACK_GAME_5 4
#define INDEX_BACK_OVER 5
#define INDEX_BACK_TUTO 6
#define INDEX_BACK_INTRO 7
#define INDEX_BACK_INTRO2 8
#define INDEX_BACK_RECORDS 9

#define NUM_MENU_IMG 6

#define IMG_MENU_BACK "Images/menuBackground.png"
#define IMG_MENU_RECORDS "Images/menuRecords.png"
#define IMG_MENU_TUTORIAL "Images/menuTutorial.png"
#define IMG_MENU_BEGIN "Images/menuBegin.png"
#define IMG_MENU_QUIT "Images/menuQuit.png"
#define IMG_MENU_SELECTOR "Images/menuSelector.png"

#define INDEX_MENU_BACK 0
#define INDEX_MENU_RECORDS 1
#define INDEX_MENU_TUTORIAL 2
#define INDEX_MENU_BEGIN 3
#define INDEX_MENU_QUIT 4
#define INDEX_MENU_SELECTOR 5

#define NUM_BALLS_IMG 4

#define IMG_SHIP "Images/ship.png"

#define IMG_SMALL_FREE_BALL "Images/sBallFree.png"
#define IMG_SMALL_FIRED_BALL "Images/sBallFired.png"
#define IMG_MEDIUM_BALL "Images/mBall.png"
#define IMG_BIG_BALL "Images/bBall.png"

#define INDEX_SMALL 0
#define INDEX_SMALL_FIRED 1
#define INDEX_MEDIUM 2
#define INDEX_BIG 3

#define FONT_PATH "Fonts/simpsonsFont.ttf"
#define FONT_SIZE 18
#define FONT_REC_SIZE 36

#define NUM_GAME_MUSIC 3

#define MUSIC_MENU "Music/Theme.ogg"
#define MUSIC_RECORDS "Music/Krusty.ogg"
#define MUSIC_TUTO "Music/ItchyScra.ogg"

#define INDEX_MUSIC_MENU 0
#define INDEX_MUSIC_RECORDS 1
#define INDEX_MUSIC_TUTO 2

#define NUM_GAME_SOUNDS 2

#define SOUND_BEHIT "Sounds/Doh.wav"
#define SOUND_DIED "Sounds/Crap.wav"

#define INDEX_SOUND_BEHIT 0
#define INDEX_SOUND_DIED 1

#define GAME_STATE_INTRO 0
#define GAME_STATE_MENU 1
#define GAME_STATE_PLAY 2
#define GAME_STATE_RECORDS 3
#define GAME_STATE_TUTORIAL 4
#define GAME_STATE_OVER 5
#define GAME_STATE_END 6
#define GAME_STATE_CHARSELECT 7

#define SMALL 0
#define MEDIUM 1
#define BIG 2

#define STATE_FREE 0
#define STATE_STUCKED 1
#define STATE_FIRED 2

#define INVENCIBLE_TIME 100
#define INVENCIBLE_START_TIME 60

#define NUM_RECORDS 5

#define PATH_FILE_REC "Rec/Rec.bin"

/*------ STRUCTS ------*/
struct record
{
	int points;
};typedef struct record RECORD;


struct vetor
{
	int x,y;
	float norma;
	float cos, sen;
};typedef struct vetor VETOR;

struct bola
{
    SDL_Rect pos;
	int raio;
    VETOR vel;
	int size;
	int state;
};typedef struct bola BOLA;

struct nave
{
	SDL_Rect pos;
	SDL_Surface* surfShip;
	int raio;
	int lifes;
	int invencible;
	RECORD rec;
};typedef struct nave NAVE;

struct menu
{
	SDL_Surface** surfMenu;
	int choice;
	SDL_Rect pos[NUM_MENU_IMG];
};typedef struct menu MENU;

/*------ PROTOTYPES ------*/

void InitSDL(); // Inicia a SDL.
void InitIMG(SDL_Surface**, SDL_Surface**, SDL_Surface**, SDL_Surface**); //Carrega todas as Imagens .
void InitSound(Mix_Chunk**); // Carrega os Sons
void InitMusic(Mix_Music**); // Carrega as Musicas
SDL_Surface* LoadIMG(char*);//Carrega uma imagem.
void InitBalls(BOLA*, SDL_Surface**, short int);//Inicializa posição, raio  e velocidade das bolas.
void InitShip(NAVE*); // Inicia a nave no centro da tela.
int InitLevel(BOLA*, SDL_Surface**, NAVE*, short int); // Inicia um level.
void UpdateGameScreen(BOLA*, SDL_Surface**, NAVE*, SDL_Surface*, SDL_Surface**, SDL_Surface*, short int, short int, TTF_Font*);// Desenha as imagens e Flipa a tela.
void BlitLifeText(NAVE,TTF_Font*, SDL_Surface*);// Blita o texto das vidas
void BlitLevelText(short int, TTF_Font* , SDL_Surface*);// Blita o texto dos leveis
void BlitShip(NAVE*, SDL_Surface*, SDL_Surface*); // Blita a nave.
void BlitBalls(BOLA*, SDL_Surface**, SDL_Surface*, short int); // Blita as bolas.
void MoveBalls(BOLA*, SDL_Surface*, short int); // Movimenta a Bola.
int ShockTest(NAVE, BOLA); // Testa Colisao entre a nave e uma bola.
int ShockTestBalls(BOLA, BOLA); // Testa colisao entre 2 bolas.
void StuckBalls(NAVE, BOLA*, short int); // Gruda a bola e calcula seu vetor velocidade de saida.
void SplitBallTest(BOLA*,SDL_Surface**, short int*); // Testa se alguma bola deve ser dividida.
void SplitBalls(BOLA*, SDL_Surface**, short int, short int);
void LoseLife(NAVE*, BOLA*, short int, Mix_Chunk**); //Testa se a nave bateu contra uma bola grande, ou seja perdeu uma vida.
void MoveShip(NAVE*, BOLA*, int, int, short int); // Movimenta a Nave.
void MoveStuckedBalls(BOLA*, int, int, short int); // Movimenta as bolas grudadas a nave.
void ReleaseBalls(BOLA*, short int); // Libera as Bolas grudadas.
int EndLevel(BOLA*, short int); // Testa se o level ja terminou.
int EventGameLoop(BOLA*, NAVE*, short int); // Realiza o loop de eventos do jogo
int GameLoop(BOLA*, NAVE*, SDL_Surface**, SDL_Surface*, SDL_Surface**, TTF_Font*, Mix_Chunk**); // Realiza o loop geral do jogo
void InitMenu(MENU*); //Inicializa o menu
int MenuLoop(MENU*, SDL_Surface*, Mix_Music**); // Faz o loop do menu
void BlitMenu(MENU*, SDL_Surface*); // Blita as imagens do menu
int EventMenuLoop(MENU*); // Realiza o loop de eventos do menu
void Intro(SDL_Surface**, SDL_Surface*);// Faz a animacao de Intro
void GameOver(SDL_Surface**, SDL_Surface*); // Realiza a animacao de fim de jogo
void Tutorial(SDL_Surface**, SDL_Surface*); // Faz a parte de Tutorial
void Records(NAVE*, SDL_Surface**, SDL_Surface*, TTF_Font*); // Mostra a tela de Records
void EndGame(SDL_Surface** background, SDL_Surface* screen); // Pruduz a animacao de fim de jogo
int* ReadRecords(const char* arqName);
void ShowRecords(NAVE*, TTF_Font*, SDL_Surface*, int*);
void InitRecFile(const char*);
int* GambleRecords(int* records);
void PrintRecords(NAVE*, int*);


int main (int argc, char** argv)
{

/*------ VARIABLES ------*/

    SDL_Surface* screen;
	SDL_Surface** background;
	SDL_Surface** surfBalls;

	TTF_Font* textFont;
	TTF_Font* recFont;
	
	Mix_Chunk** gameSounds;
	Mix_Music** gameMusic;
	
    BOLA* balls;

	NAVE ship;
	
	MENU menu;
	
    short int quit = 0;

	short int i;
	
	short int gameState = GAME_STATE_INTRO;

/*------ BEGIN ------*/

    srand(time(NULL));

    InitSDL();
	
	SDL_WM_SetCaption("Donut's Invasion", " ");
	
    atexit(SDL_Quit);
	atexit(TTF_Quit);
	atexit(Mix_CloseAudio);
	
/*	screen = SDL_SetVideoMode(S_WIDTH , S_HEIGHT , S_DEPTH ,SDL_SWSURFACE|SDL_DOUBLEBUF|SDL_FULLSCREEN);*/
	screen = SDL_SetVideoMode(S_WIDTH , S_HEIGHT , S_DEPTH ,SDL_DOUBLEBUF);
    if (!screen)
    {
        printf("Unable to set 800x600 video: %s\n", SDL_GetError());
        exit(1);
    }
		
	background = (SDL_Surface**) malloc (NUM_BACK_IMG * sizeof(SDL_Surface*));
	if (!background)
	{
		printf("Unable to memory alloc %s\n", SDL_GetError());
		exit(1);
	}
	
	balls = (BOLA*) malloc (NUM_BALLS_MAX * sizeof(BOLA));
	if (!balls)
	{
		printf("Unable to memory alloc %s\n", SDL_GetError());
		exit(1);
	}
	
	surfBalls = (SDL_Surface**) malloc (NUM_BALLS_IMG * sizeof(SDL_Surface*));
	if (!surfBalls)
	{
		printf("Unable to memory alloc %s\n", SDL_GetError());
		exit(1);
	}
	
	gameSounds = (Mix_Chunk**) malloc (NUM_GAME_SOUNDS * sizeof(Mix_Chunk*));
	if (!gameSounds)
	{
		printf("Unable to memory alloc %s\n", SDL_GetError());
		exit(1);
	}
	
	gameMusic = (Mix_Music**) malloc (NUM_GAME_MUSIC * sizeof(Mix_Music*));
	if (!gameMusic)
	{
		printf("Unable to memory alloc %s\n", SDL_GetError());
		exit(1);
	}
	
	menu.surfMenu = (SDL_Surface**) malloc (NUM_MENU_IMG * sizeof(SDL_Surface*));
	if (!menu.surfMenu)
	{
		printf("Unable to memory alloc %s\n", SDL_GetError());
		exit(1);
	}
	
	textFont = TTF_OpenFont(FONT_PATH, FONT_SIZE);
	
	recFont = TTF_OpenFont(FONT_PATH, FONT_REC_SIZE);
	
	InitMusic(gameMusic);
	
	InitSound(gameSounds);
	
	InitIMG(surfBalls, menu.surfMenu, &ship.surfShip, background);
	
	InitRecFile(PATH_FILE_REC);
	
    while (!quit)
    {		
		switch (gameState)
		{		
			case GAME_STATE_PLAY: 
			{
				gameState = GameLoop(balls, &ship, surfBalls, screen, background, textFont, gameSounds);
				break;
			}
			
			case GAME_STATE_MENU:
			{
				InitMenu(&menu);
				gameState = MenuLoop(&menu, screen, gameMusic);
				break;
			}
			
			case GAME_STATE_END:
			{
				Mix_HaltMusic();
				GameOver(background, screen);
				gameState = GAME_STATE_MENU;
				Mix_HaltMusic();
				Mix_PlayMusic(gameMusic[INDEX_MUSIC_MENU],-1);
				break;
			}
			
			case GAME_STATE_OVER:
			{
				EndGame(background, screen);
				quit = 1;
				break;
			}
			
			case GAME_STATE_CHARSELECT:
			{
				//SelectChar();
				gameState = GAME_STATE_PLAY;
				break;
			}
			
			case GAME_STATE_TUTORIAL:
			{
				Mix_HaltMusic();
				Mix_PlayMusic(gameMusic[INDEX_MUSIC_TUTO],-1);
				Tutorial(background, screen);
				gameState = GAME_STATE_MENU;
				Mix_HaltMusic();
				Mix_PlayMusic(gameMusic[INDEX_MUSIC_MENU],-1);
				break;
			}
			
			case GAME_STATE_RECORDS:
			{
				Mix_HaltMusic();
				Mix_PlayMusic(gameMusic[INDEX_MUSIC_RECORDS],-1);
				Records(&ship, background, screen, recFont);
				gameState = GAME_STATE_MENU;
				Mix_HaltMusic();
				Mix_PlayMusic(gameMusic[INDEX_MUSIC_MENU],-1);
				break;
			}
			
			case GAME_STATE_INTRO:
			{ 
				Mix_FadeInMusic(gameMusic[INDEX_MUSIC_MENU], -1, 10000);
				Intro(background, screen);
				gameState = GAME_STATE_MENU;
				break;
			}
			
			default:
			{
				puts("Undefined game phase");
				break;
			}
		}
    }

    for (i=0 ; i < NUM_BACK_IMG ; i++)
			SDL_FreeSurface(background[i]);
	SDL_FreeSurface(ship.surfShip);
	for (i=0 ; i < NUM_BALLS_IMG ; i++)
		SDL_FreeSurface(surfBalls[i]);
	SDL_FreeSurface(screen);
	for (i=0 ; i < NUM_GAME_SOUNDS; i++)
		Mix_FreeChunk(gameSounds[i]); 
	for (i=0 ; i < NUM_GAME_MUSIC; i++)
		Mix_FreeMusic(gameMusic[i]); 
		
		
    return 0;
}

void InitSDL()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        exit(1);
    }
	
	if(TTF_Init() == -1)
	{
		printf("Unabble to open TTF: %s\n", TTF_GetError());
		exit(1);
	} 

	Mix_OpenAudio(44100,AUDIO_S16SYS, MIX_DEFAULT_CHANNELS, 4096);	
}

void InitIMG(SDL_Surface** surfBalls, SDL_Surface** surfMenu, SDL_Surface** surfShip, SDL_Surface** background)
{
	short int i;
	
	*surfShip = LoadIMG(IMG_SHIP);
	
	SDL_SetColorKey(*surfShip, SDL_SRCCOLORKEY, SDL_MapRGB((*surfShip)->format, TRANS_COLOR_R, TRANS_COLOR_G, TRANS_COLOR_B));	
	
	background[INDEX_BACK_GAME] = LoadIMG(IMG_BACKGROUND_GAME);
	background[INDEX_BACK_GAME_2] = LoadIMG(IMG_BACKGROUND_GAME_2);
	background[INDEX_BACK_GAME_3] = LoadIMG(IMG_BACKGROUND_GAME_3);
	background[INDEX_BACK_GAME_4] = LoadIMG(IMG_BACKGROUND_GAME_4);
	background[INDEX_BACK_GAME_5] = LoadIMG(IMG_BACKGROUND_GAME_5);
	background[INDEX_BACK_OVER] = LoadIMG(IMG_BACKGROUND_OVER);
	background[INDEX_BACK_TUTO] = LoadIMG(IMG_BACKGROUND_TUTO);
	background[INDEX_BACK_INTRO] = LoadIMG(IMG_BACKGROUND_INTRO);
	background[INDEX_BACK_INTRO2] = LoadIMG(IMG_BACKGROUND_INTRO2);
	background[INDEX_BACK_RECORDS] = LoadIMG(IMG_BACKGROUND_RECORDS);
	
	surfBalls[INDEX_SMALL] = LoadIMG(IMG_SMALL_FREE_BALL);
	surfBalls[INDEX_SMALL_FIRED] = LoadIMG(IMG_SMALL_FIRED_BALL);
	surfBalls[INDEX_MEDIUM] = LoadIMG(IMG_MEDIUM_BALL);
	surfBalls[INDEX_BIG] = LoadIMG(IMG_BIG_BALL);
	
	surfMenu[INDEX_MENU_BACK] = LoadIMG(IMG_MENU_BACK);
	surfMenu[INDEX_MENU_RECORDS] = LoadIMG(IMG_MENU_RECORDS);
	surfMenu[INDEX_MENU_TUTORIAL] = LoadIMG(IMG_MENU_TUTORIAL);
	surfMenu[INDEX_MENU_BEGIN] = LoadIMG(IMG_MENU_BEGIN);
	surfMenu[INDEX_MENU_QUIT] = LoadIMG(IMG_MENU_QUIT);
	surfMenu[INDEX_MENU_SELECTOR] = LoadIMG(IMG_MENU_SELECTOR);
	
	for (i = 0; i < NUM_BALLS_IMG ; i++)
	{
		SDL_SetColorKey(surfBalls[i], SDL_SRCCOLORKEY, SDL_MapRGB(surfBalls[i]->format, TRANS_COLOR_R, TRANS_COLOR_G, TRANS_COLOR_B));
	}	
}	

void InitSound(Mix_Chunk** gameSounds)
{
	Mix_AllocateChannels(16);
	
	gameSounds[INDEX_SOUND_BEHIT] = Mix_LoadWAV(SOUND_BEHIT);
	if (!(gameSounds[INDEX_SOUND_BEHIT])) 
	{
		printf("Unable to open Sound");
		exit(1);
	}
	Mix_VolumeChunk(gameSounds[INDEX_SOUND_BEHIT], 50);
	
	gameSounds[INDEX_SOUND_DIED] = Mix_LoadWAV(SOUND_DIED);
	if (!(gameSounds[INDEX_SOUND_DIED])) 
	{
		printf("Unable to open Sound");
		exit(1);
	}
	Mix_VolumeChunk(gameSounds[INDEX_SOUND_DIED], 32);
	
}

void InitMusic(Mix_Music** gameMusic)
{

	Mix_VolumeMusic(100);	
		
	gameMusic[INDEX_MUSIC_MENU] = Mix_LoadMUS(MUSIC_MENU);
	if (!(gameMusic[INDEX_MUSIC_MENU])) 
	{
		printf("Unable to open Music");
		exit(1);
	}
	
	gameMusic[INDEX_MUSIC_RECORDS] = Mix_LoadMUS(MUSIC_RECORDS);
	if (!(gameMusic[INDEX_MUSIC_MENU])) 
	{
		printf("Unable to open Music");
		exit(1);
	}
	
	gameMusic[INDEX_MUSIC_TUTO] = Mix_LoadMUS(MUSIC_TUTO);
	if (!(gameMusic[INDEX_MUSIC_MENU])) 
	{
		printf("Unable to open Music");
		exit(1);
	}
}

SDL_Surface* LoadIMG(char* nomeArq)
{
	SDL_Surface* img;

	img = (SDL_Surface*) malloc (sizeof(SDL_Surface));
	if (!img)
	{
		printf("Unable to memory alloc %s\n", SDL_GetError());
		exit(1);
	}
	
	img = IMG_Load(nomeArq);

    if (img == NULL)
    {
        printf("Unable to load bitmap: %s\n", SDL_GetError());
        exit(1);
    }
	
	return img;
}

void InitShip (NAVE* ship)
{
	ship->raio = (ship->surfShip->w/2);

	ship->invencible = INVENCIBLE_START_TIME;	
	
	ship->rec.points = 0;
		
	ship->pos.x = S_WIDTH/2 - ship->raio;
	ship->pos.y = S_HEIGHT/2 - ship->raio;
}

void InitBalls(BOLA* balls, SDL_Surface** surfBalls, short int lvlBalls)
{
	int i, sig;
	
	balls[0].size = SMALL;
	
	for (i = 1 ; i < lvlBalls ; i++)
	{
		balls[i].size = ((rand() % (NUM_BALLS_SIZES - 1)) + 1);
	}	
	
	for (i=0 ; i < lvlBalls ; i++)
	{
		switch (balls[i].size)
		{
			case SMALL:
				balls[i].raio = (surfBalls[INDEX_SMALL]->w/2);
				break;
			case MEDIUM:
				balls[i].raio = (surfBalls[INDEX_MEDIUM]->w/2);
				break;
			case BIG:
				balls[i].raio = (surfBalls[INDEX_BIG]->w/2);
				break;				
		}
		
		balls[i].state = STATE_FREE;
	}
		
	for(i=0; i < lvlBalls; i++)
	{
		sig = (rand() % 2);
		if (sig)
			balls[i].vel.x = (rand() % SPEED_MAX + 1);
		else
			balls[i].vel.x = -(rand() % SPEED_MAX + 1);
		if (sig)
			balls[i].vel.y = (rand() % SPEED_MAX + 1);
		else
			balls[i].vel.y = -(rand() % SPEED_MAX + 1);
	}

    //Decide a posiçao inicial das bolas
	
	for (i = 0; i < lvlBalls; i++)
	{
		balls[i].pos.x = rand() % (S_WIDTH - 2 * (int) balls[0].raio);
		while (balls[i].pos.x > S_WIDTH/2 - 100 && balls[i].pos.x < S_WIDTH/2 + 100)
			balls[i].pos.x = rand() % (S_WIDTH - 2 * (int) balls[0].raio);
			
		balls[i].pos.y = rand() % (S_HEIGHT - 2 * (int) balls[0].raio);
		while (balls[i].pos.y > S_HEIGHT/2 - 100 && balls[i].pos.y < S_HEIGHT/2 + 100)
			balls[i].pos.y = rand() % (S_HEIGHT - 2 * (int) balls[0].raio);
	}
	
}

int InitLevel(BOLA* balls, SDL_Surface** surfBalls, NAVE* ship, short int lvl)
{
	int lvlBalls = lvl*2 + 1;
	
	if (lvl == 1) ship->lifes = 3;
	
	InitShip(ship);
	InitBalls(balls, surfBalls, lvlBalls);
	
	SDL_EventState(SDL_MOUSEMOTION,SDL_DISABLE);
	SDL_WarpMouse(S_WIDTH/2, S_HEIGHT/2);
	SDL_EventState(SDL_MOUSEMOTION,SDL_ENABLE);

	SDL_ShowCursor(SDL_DISABLE);
	SDL_WM_GrabInput(SDL_GRAB_ON);
	
	return lvlBalls;
}

void UpdateGameScreen (BOLA* balls, SDL_Surface** surfBalls,  NAVE* ship, SDL_Surface* surfShip, SDL_Surface** background, SDL_Surface* screen, short int lvlBalls, short int lvl, TTF_Font* textFont)
{		
		if (lvl % 5 == 1)
			SDL_BlitSurface(background[INDEX_BACK_GAME], 0, screen, 0);
		else if (lvl % 5 == 2)
			SDL_BlitSurface(background[INDEX_BACK_GAME_2], 0, screen, 0);
		else if (lvl % 5 == 3)
			SDL_BlitSurface(background[INDEX_BACK_GAME_3], 0, screen, 0);
		else if (lvl % 5 == 4)
			SDL_BlitSurface(background[INDEX_BACK_GAME_4], 0, screen, 0);
		else if (lvl % 5 == 0)
			SDL_BlitSurface(background[INDEX_BACK_GAME_5], 0, screen, 0);
	
		BlitLevelText(lvl, textFont ,screen);
			
		BlitLifeText(*ship,textFont,screen);
		
		BlitShip(ship, surfShip, screen);

		BlitBalls(balls, surfBalls, screen, lvlBalls);
		
        SDL_Flip(screen);
}

void BlitLifeText(NAVE ship, TTF_Font* textFont , SDL_Surface* screen)
{
	char *lifeText; 
	SDL_Color color = {255,255,255};
	SDL_Surface* aux;
	SDL_Rect temp;
	
	lifeText = (char*) malloc (sizeof(char));
	
	sprintf (lifeText,"%d",ship.lifes);

	aux = TTF_RenderText_Blended(textFont, lifeText, color);
	
	temp.x = 43;
	temp.y = 32;

	SDL_BlitSurface(aux,NULL,screen,&temp);
	
	SDL_FreeSurface(aux);
}

void BlitLevelText(short int lvl, TTF_Font* textFont , SDL_Surface* screen)
{
	char *levelText; 
	SDL_Color color = {255,255,255};
	SDL_Surface* aux;
	SDL_Rect temp;
	
	if (!(lvl%5) || !(lvl%4))
	{
		color.r = color.g = color.b = 0;
	}
	
	levelText = (char*) malloc (sizeof(char));
	
	sprintf(levelText,"%d",lvl);
	
	aux = TTF_RenderText_Blended(textFont, levelText, color);
	
	temp.x = 757;
	temp.y = 41;

	SDL_BlitSurface(aux,NULL,screen,&temp);
	
	SDL_FreeSurface(aux);
}

void BlitShip(NAVE* ship, SDL_Surface* surfShip, SDL_Surface* screen)
{
	SDL_Rect temp;
		
	if (!ship->invencible)
	{
		temp = ship->pos;
		SDL_BlitSurface(surfShip,0,screen,&temp);
	}
	else
	{
		if (ship->invencible % 3)
		{
			temp = ship->pos;
			SDL_BlitSurface(surfShip,0,screen,&temp);
		}
	}
}

void BlitBalls(BOLA* balls, SDL_Surface** surfBalls,  SDL_Surface* screen, short int lvlBalls)
{
	SDL_Rect temp;
	short int i;
	
	for (i = 0; i < lvlBalls ; i++)
	{
		temp = balls[i].pos;
		switch (balls[i].size)
		{
			case SMALL:
				if (balls[i].state == STATE_FIRED)
					SDL_BlitSurface(surfBalls[INDEX_SMALL_FIRED],0,screen,&temp);
				else
					SDL_BlitSurface(surfBalls[INDEX_SMALL],0,screen,&temp);
				break;
			case MEDIUM:
				SDL_BlitSurface(surfBalls[INDEX_MEDIUM],0,screen,&temp);
				break;
			case BIG:
				SDL_BlitSurface(surfBalls[INDEX_BIG],0,screen,&temp);
				break;
		}
	}
}

void MoveBalls(BOLA* balls, SDL_Surface* screen, short int lvlBalls)
{
	short int i;
	short int ctrl;
	
	for (i = 0; i < lvlBalls; i++)
	{
		ctrl = 0;
		
		if (balls[i].state != STATE_STUCKED)
		{	
			if (balls[i].state == STATE_FIRED)
			{
				balls[i].pos.x += 4*balls[i].vel.x;
				balls[i].pos.y += 4*balls[i].vel.y;
			}
			else
			{
				balls[i].pos.x += balls[i].vel.x;
				balls[i].pos.y += balls[i].vel.y;
			}

		    if (balls[i].pos.x >= screen->w)
		    {
		        balls[i].pos.x = (-2*balls[i].raio);
				ctrl = 1;
		    }
		    else if (balls[i].pos.x + 2*balls[i].raio <= 0)
		    {
		        balls[i].pos.x = screen->w;
				ctrl = 1;
		    }

			if (balls[i].pos.y >= screen->h)
            {
		        balls[i].pos.y = (-2*balls[i].raio);
				ctrl = 1;
		    }
		    else if (balls[i].pos.y + 2*balls[i].raio <= 0)
		    {
		        balls[i].pos.y = screen->h;
				ctrl = 1;
		    }
			
			if (ctrl == 1 && balls[i].state == STATE_FIRED)
				balls[i].state = STATE_FREE;
		}		
	}
	 
	 
}

int ShockTest(NAVE ship, BOLA ballB)
{
		if (ship.raio + ballB.raio >= sqrt(pow(((ship.pos.x + ship.raio) - (ballB.pos.x + ballB.raio)),2) + pow(((ship.pos.y + ship.raio) - (ballB.pos.y + ballB.raio)),2)))
		{	
			return 1;
		}
		return 0;
}

int ShockTestBalls(BOLA bolaA, BOLA ballB)
{
		if (bolaA.raio + ballB.raio >= sqrt(pow(((bolaA.pos.x + bolaA.raio) - (ballB.pos.x + ballB.raio)),2) + pow(((bolaA.pos.y + bolaA.raio) - (ballB.pos.y + ballB.raio)),2)))
		{	
			return 1;
		}
		return 0;
}

void StuckBalls(NAVE ship, BOLA* balls, short int lvlBalls)
{
	VETOR aux;
	short int i;
	
	for (i = 0 ; i < lvlBalls ; i++)
	{
		if (balls[i].size == SMALL && balls[i].state == STATE_FREE)
		{
			if (ShockTest(ship, balls[i]))
			{
				aux.x = (ship.pos.x + ship.raio) - (balls[i].pos.x + balls[i].raio);
				aux.y = (ship.pos.y + ship.raio) - (balls[i].pos.y + balls[i].raio);
	
				aux.norma = sqrt(aux.x * aux.x + aux.y * aux.y);
		
				aux.cos = aux.x/aux.norma;
				aux.sen = aux.y/aux.norma;
	
				balls[i].vel.x = -3 * aux.cos;
				balls[i].vel.y = -3 * aux.sen;

				while (ship.raio + balls[i].raio > sqrt(pow(((ship.pos.x + ship.raio) - (balls[i].pos.x + balls[i].raio)),2) + pow(((ship.pos.y + ship.raio) - (balls[i].pos.y + balls[i].raio)),2)))
				{
					balls[i].pos.x += balls[i].vel.x;
					balls[i].pos.y += balls[i].vel.y;
				}
	
				balls[i].state = STATE_STUCKED;
			}
		}
	}	
}

void SplitBallTest(BOLA* balls, SDL_Surface** surfBalls, short int* lvlBalls)
{
	short int i, j;
	
	for (i = 0 ; i < *lvlBalls ; i++)
	{
		if(balls[i].state == STATE_FIRED)
		{
			for (j = 0; j < *lvlBalls ; j++)
			{
				if (balls[j].size == SMALL) continue;
				
				if(balls[i].state != STATE_FIRED) break;
				
				if(ShockTestBalls(balls[i],balls[j]))
				{
					SplitBalls(balls, surfBalls, j, *lvlBalls);
					balls[i].state = STATE_FREE;
					*lvlBalls += 1;
				}
			}
		}
	}
}

void SplitBalls(BOLA* balls, SDL_Surface** surfBalls, short int index, short int lvlBalls)
{
	balls[index].size--;
	
	if (balls[index].size == MEDIUM)
	{
		balls[index].raio = (surfBalls[INDEX_MEDIUM]->w/2);
	}
	else
	{
		balls[index].raio = (surfBalls[INDEX_SMALL]->w/2);
	}
	
	balls[lvlBalls] = balls[index];
	
	balls[lvlBalls].vel.x *= -1;
	balls[lvlBalls].vel.y *= -1;
}

void LoseLife(NAVE* ship, BOLA* balls, short int lvlBalls, Mix_Chunk** gameSounds)
{
	short int i;
	
	if (ship->invencible > 0)
	{
		ship->invencible--;
	}
	else
	{
		for (i = 0 ; i < lvlBalls ; i++)
		{	
			if (balls[i].state == STATE_FREE)
			{
				if (ShockTest(*ship, balls[i]))
				{
					Mix_PlayChannel(-1,gameSounds[INDEX_SOUND_BEHIT], 0);
					ship->lifes--;
					ship->invencible = INVENCIBLE_TIME;
				}
			}
		}
	}
}

void MoveShip(NAVE* ship, BOLA* balls, int xrel, int yrel, short int lvlBalls)
{	
	if (ship->pos.x + xrel < 0) 
	{
		xrel = -ship->pos.x; 
	}
	if (ship->pos.x + xrel + 2 * ship->raio > S_WIDTH )
	{
		xrel = -(ship->pos.x + (ship->raio * 2) - S_WIDTH);
	}	
	if (ship->pos.y + yrel < 0)
	{
		yrel = -ship->pos.y;
	}
	if (ship->pos.y + yrel + 2 * ship->raio > S_HEIGHT)
	{
		yrel = -(ship->pos.y + (2 * ship->raio) - S_HEIGHT);
	}

	ship->pos.x += xrel;
	ship->pos.y += yrel;
	
	MoveStuckedBalls(balls,xrel,yrel,lvlBalls);

}

void MoveStuckedBalls(BOLA* balls, int xrel, int yrel, short int lvlBalls)
{
	short int i;
	
	for (i = 0 ; i < lvlBalls ; i++)
	{
		if (balls[i].state == STATE_STUCKED)
		{
			balls[i].pos.x += xrel;
			balls[i].pos.y += yrel;
		}
	}
}

void ReleaseBalls(BOLA* balls, short int lvlBalls)
{
	short int i;
	
	for (i=0; i < lvlBalls; i++)
	{
		if (balls[i].state == STATE_STUCKED)
			balls[i].state = STATE_FIRED;
	}
}

int EndLevel(BOLA* balls, short int lvlBalls)
{
	int i = 0;
	
	while (i < lvlBalls)
	{
		if (balls[i].size != SMALL) return 1;
		i++;
	}
	
	return 0;
}

int EventGameLoop(BOLA* balls, NAVE* ship, short int lvlBalls)
{
	static SDL_Event event;	
	int pause;
		
	while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
			case SDL_KEYDOWN:
	        {
	            if (event.key.keysym.sym == SDLK_ESCAPE)
	                return GAME_STATE_MENU;
				
				if (event.key.keysym.sym ==  SDLK_p)
				{
					pause = 1;
					while (pause)
					{
						while (SDL_PollEvent(&event))
						{
							switch (event.type)
							{
								case SDL_KEYDOWN:
								{
									if (event.key.keysym.sym ==  SDLK_p)
									pause = 0;
								}
							}
						}
					}
				}
				break;
				
	        }

			case SDL_MOUSEMOTION:
			{
				MoveShip(ship, balls, event.motion.xrel, event.motion.yrel, lvlBalls);
				return GAME_STATE_PLAY;
				break;
			}
				
			case SDL_MOUSEBUTTONDOWN:
			{
				if (event.button.button == SDL_BUTTON_LEFT)
					ReleaseBalls(balls, lvlBalls);
				return GAME_STATE_PLAY;
				break;
			}	
		}
    }
	return GAME_STATE_PLAY;
}

int GameLoop(BOLA* balls, NAVE* ship, SDL_Surface** surfBalls, SDL_Surface* screen, SDL_Surface** background, TTF_Font* textFont, Mix_Chunk** gameSounds)
{
	static short int lvlBalls;
	static short int lvl = 0;
	static short int endLvl = 0;
	
	short int aux = GAME_STATE_PLAY;
	int frameClock = SDL_GetTicks();
	
	if (!endLvl)
	{
		lvl++;
		lvlBalls = InitLevel(balls, surfBalls, ship, lvl);
		if (!(lvl % 3) && lvl != 1) ship->lifes++;
		endLvl = 1;
	}
		
	aux = EventGameLoop(balls, ship, lvlBalls);
		
	MoveBalls(balls, screen, lvlBalls);
	StuckBalls(*ship, balls, lvlBalls);		
	SplitBallTest(balls, surfBalls, &lvlBalls);
			
	LoseLife(ship, balls, lvlBalls, gameSounds);
	
	UpdateGameScreen(balls, surfBalls, ship, ship->surfShip, background, screen, lvlBalls, lvl, textFont);
			
	endLvl = EndLevel(balls, lvlBalls);
	
	if (!ship->lifes)
	{
		aux = GAME_STATE_END;
		ship->rec.points = lvl;
	}	
	
	if (aux != GAME_STATE_PLAY) 
	{
		if (aux == GAME_STATE_END) Mix_PlayChannel(-1,gameSounds[INDEX_SOUND_DIED],0);
		lvl = 0;
		endLvl = 0;
	}
	
	while (frameClock + NEXT_LOOP > SDL_GetTicks()) ; // Controla o loop do jogo de acordo com o tempo
	
	return aux;
}

void InitMenu(MENU* menu)
{
	menu->choice = GAME_STATE_PLAY;
	
	menu->pos[INDEX_MENU_BACK].x = 0;
	menu->pos[INDEX_MENU_BACK].y = 0;
	
	menu->pos[INDEX_MENU_BEGIN].x = 245;
	menu->pos[INDEX_MENU_BEGIN].y = 150;
	
	menu->pos[INDEX_MENU_RECORDS].x = 245;
	menu->pos[INDEX_MENU_RECORDS].y = 250;
	
	menu->pos[INDEX_MENU_TUTORIAL].x = 245;
	menu->pos[INDEX_MENU_TUTORIAL].y = 350;

	menu->pos[INDEX_MENU_QUIT].x = 245;
	menu->pos[INDEX_MENU_QUIT].y = 450;
	
	menu->pos[INDEX_MENU_SELECTOR].x = 245 - 80;
	menu->pos[INDEX_MENU_SELECTOR].y = 0;
}

int MenuLoop(MENU* menu, SDL_Surface* screen, Mix_Music** gameMusic)
{
	int aux = 0;
	
	int frameClock;
	
	while(1)
	{
		frameClock = SDL_GetTicks();

		BlitMenu(menu, screen);
		aux = EventMenuLoop(menu);
		if (aux == 0) break;
		
		while (frameClock + NEXT_LOOP > SDL_GetTicks()) ; // Controla o loop do jogo de acordo com o tempo
	}
	
	return menu->choice;
}

void BlitMenu(MENU* menu, SDL_Surface* screen)
{
	SDL_BlitSurface(menu->surfMenu[INDEX_MENU_BACK],0,screen,&menu->pos[INDEX_MENU_BACK]);
	SDL_BlitSurface(menu->surfMenu[INDEX_MENU_RECORDS],0,screen,&menu->pos[INDEX_MENU_RECORDS]);
	SDL_BlitSurface(menu->surfMenu[INDEX_MENU_TUTORIAL],0,screen,&menu->pos[INDEX_MENU_TUTORIAL]);
	SDL_BlitSurface(menu->surfMenu[INDEX_MENU_BEGIN],0,screen,&menu->pos[INDEX_MENU_BEGIN]);
	SDL_BlitSurface(menu->surfMenu[INDEX_MENU_QUIT],0,screen,&menu->pos[INDEX_MENU_QUIT]);
	
	menu->pos[5].y = 150 + (menu->choice-2)*100;
	SDL_BlitSurface(menu->surfMenu[INDEX_MENU_SELECTOR],0,screen,&menu->pos[INDEX_MENU_SELECTOR]);
	
	SDL_Flip(screen);
}

int EventMenuLoop(MENU* menu)
{
	static SDL_Event event;	
		
	while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
			case SDL_KEYDOWN:
	        {
	            if (event.key.keysym.sym == SDLK_RETURN)
				{
					return 0;
				}	
				
				if (event.key.keysym.sym == SDLK_DOWN)
				{
					menu->choice++;
					if (menu->choice > GAME_STATE_OVER) menu->choice = GAME_STATE_PLAY;
					return menu->choice;
				}				
				
				if (event.key.keysym.sym == SDLK_UP)
				{
					menu->choice--;
					if (menu->choice < GAME_STATE_PLAY) menu->choice = GAME_STATE_OVER;
					return menu->choice;
				}	
				
	        }
		}
    }
	return -10;
}

void Intro(SDL_Surface** background, SDL_Surface* screen)
{
	SDL_Event event;
	int i;	

	for (i = 0;i < 255; i += 2)
	{
		SDL_SetAlpha(background[INDEX_BACK_INTRO], SDL_SRCALPHA, i);
		SDL_BlitSurface(background[INDEX_BACK_INTRO],0,screen,0);
		SDL_Flip(screen);
	}

	for (i = 0; i < 255 ; i += 2)
	{
		SDL_SetAlpha(background[INDEX_BACK_INTRO2], SDL_SRCALPHA, i);
		SDL_BlitSurface(background[INDEX_BACK_INTRO2],0,screen,0);
		SDL_Flip(screen);
	}

	while (SDL_PollEvent(&event));
}

void GameOver(SDL_Surface** background, SDL_Surface* screen)
{
	int i;
	SDL_Event event;
	int out;
	
	for (i = 0;i < 255; i += 5)
	{
		SDL_SetAlpha(background[INDEX_BACK_OVER], SDL_SRCALPHA, i);
		SDL_BlitSurface(background[INDEX_BACK_OVER],0,screen,0);
		SDL_Flip(screen);
	}
	
	out = 0;
	
	while(!out)
	{
		while (SDL_PollEvent(&event))
	    {
	        switch (event.type)
	        {
				case SDL_KEYDOWN:
		        {
		            if (event.key.keysym.sym == SDLK_RETURN)
					{
						out = 1;
					}	
										
					if (event.key.keysym.sym == SDLK_ESCAPE)
					{
						out = 1;
					}	
					
		        }
			}
	    }

		SDL_BlitSurface(background[INDEX_BACK_OVER],0,screen,0);
		SDL_Flip(screen);
	}
}

void Tutorial(SDL_Surface** background, SDL_Surface* screen)
{
	SDL_Event event;
	int out = 0;
	
	while(!out)
	{
		while (SDL_PollEvent(&event))
	    {
	        switch (event.type)
	        {
				case SDL_KEYDOWN:
		        {
		            if (event.key.keysym.sym == SDLK_RETURN)
					{
						out = 1;
					}	
										
					if (event.key.keysym.sym == SDLK_ESCAPE)
					{
						out = 1;
					}	
					
		        }
			}
	    }

		SDL_BlitSurface(background[INDEX_BACK_TUTO],0,screen,0);
		SDL_Flip(screen);
	}
}

void EndGame(SDL_Surface** background, SDL_Surface* screen)
{
	//BLA
}

void Records(NAVE* ship, SDL_Surface** background, SDL_Surface* screen, TTF_Font* recFont)
{
	SDL_Event event;
	int out = 0;
	
	SDL_BlitSurface(background[INDEX_BACK_RECORDS],0,screen,0);
	SDL_Flip(screen);
	
	PrintRecords(ship, ReadRecords(PATH_FILE_REC));
	
	ShowRecords(ship, recFont, screen, GambleRecords(ReadRecords(PATH_FILE_REC)));
	
	while(!out)
	{
		while (SDL_PollEvent(&event))
	    {
	        switch (event.type)
	        {
				case SDL_KEYDOWN:
		        {
		            if (event.key.keysym.sym == SDLK_RETURN)
					{
						out = 1;
					}	
					
					if (event.key.keysym.sym == SDLK_ESCAPE)
					{
						out = 1;
					}	
		        }
			}
	    }
	}
}

int* ReadRecords(const char * arqName)
{
	FILE* recArq;
	int* aux;
	int i;
	
	aux = (int*) malloc (sizeof(int)* NUM_RECORDS);
	
	if(!(recArq = fopen(arqName,"rb")))
	{
		printf("Unable to open file");
		exit(1);
	}
	
	for (i = 0; i < NUM_RECORDS; i++)
		fread(&aux[i],sizeof(int),1,recArq);
	
	fclose(recArq);
	
	return aux;
}

void ShowRecords(NAVE* ship, TTF_Font* recFont, SDL_Surface* screen, int* records)
{
	SDL_Color color = {255,255,0};
	SDL_Surface* aux;
	SDL_Rect temp;
	int i;
	char* tempStr;
	
	tempStr = (char*) malloc (sizeof(char));
	
	for (i=0; i< NUM_RECORDS; i++)
	{				
		sprintf(tempStr,"%d",records[i]);
		
		aux = TTF_RenderText_Blended(recFont, tempStr, color);
		
		temp.x = 200;
		temp.y = 150 + (80 * i);

		SDL_BlitSurface(aux,NULL,screen,&temp);
		SDL_Flip(screen);
	}
		
	SDL_FreeSurface(aux);
}

void InitRecFile(const char* arqName)
{
	int aux;
	FILE* recArq;
	int i;
	
	if(!(recArq = fopen(arqName,"rb")))
	{
		
		fclose(recArq);
		
		recArq = fopen(arqName,"wb");
			
		aux = 14;
		
		for (i = 0; i < NUM_RECORDS ; i++)
		{
			fwrite(&aux,sizeof(int),1,recArq);
			aux += i;
		}
	
		fclose(recArq);
	}
}

int* GambleRecords(int* records)
{
	int i, j , troca;
	int temp;
	
	for (i = NUM_RECORDS; i > 0; i--)
    {
        troca = 0;
        for (j = 0; j < i; j++)
        {
            if (records[j] < records[j+1])
            {
                temp = records[j]; 
                records[j] = records[j+1];
                records[j+1] = temp;
                troca = 1;
            }
        }
        if (troca == 0)
            break;
    }
	
	return records;
}

void PrintRecords(NAVE* ship, int* records)
{
	FILE* arqName;
	
	if(!(arqName = fopen(PATH_FILE_REC,"rb+")))
	{
		printf("Unable to open file");
		exit(1);
	}
	
	if (ship->rec.points > records[4])
	{
		fseek(arqName,sizeof(int),SEEK_END);
		fwrite(&ship->rec.points,sizeof(int),1,arqName);
	}
	
	fclose(arqName);
}
