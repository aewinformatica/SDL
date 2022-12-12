/*	Programa: Teste7.c
	Autores: Daniel Lopes Braz Dos Santos
		     Gustavo Rodrigues Lima
		     Renan da Costa Garrot
	Data: 18/06/2008
	Descrição: Teste movimentação "em grade".

*/

// INCLUDES
#include "include.h"

// GLOBAIS
SDL_Rect dst_car = {PADRAO, PADRAO * 2, 0, 0}; // posição do jogador
SDL_Rect dst_obj = {0, 0, 0, 0};	//posiçao dos fixos,inimigos,moveis e etc..
SDL_Rect show_car = {0, 0, PADRAO, PADRAO};	//coordenadas da area desejada da figura
SDL_Rect dst_bomba = {0, 0, 0, 0}; //posição da bomba
SDL_Rect dst_fogo = {0, 0, 0, 0}; //posição do fogo
SDL_Rect dst_porta = {0, 0, 0, 0};//coordenadas da saída
SDL_Rect dst_topo = {0,0,0,0};
SDL_Rect dst_vidas = {90,10,0,0};
SDL_Rect dst_pontos = {335,13,0,0};
SDL_Rect dst_pause = {250,242,0,0};

extern int vidas;
extern int inimigos;
extern int pontos;
extern int del;
extern int musicON;

// FUNCOES
char Movimenta(char *, char *, int **, SDL_Surface *, int **);
void CarregarObj(int **, SDL_Surface*,SDL_Surface*, SDL_Surface*, SDL_Surface* [], int**, SDL_Surface*);
void AtualizaImagemCarro(char);
int Explosao(int, int,  Uint32, SDL_Surface*, SDL_Surface*, SDL_Surface*, int **);
void ChecaDestruicaoNaoFixo(int **);
int ChecaDestruicaoInimigosJogador(int **, int **, Uint32);
int** AlocaEspaco(int, int);
int fase(SDL_Surface*);
int  ChoqueJogador(int **, Uint32);
int sorteiaFase(int,int **);
int ConfirmaSaida(SDL_Surface*);
int salvarecorde(SDL_Surface* ,int);

int fase(SDL_Surface* screen)
{
	TTF_Font* fonte;
	TTF_Font* pausefonte;
	SDL_Surface* fundo;
	SDL_Surface* car;
	SDL_Surface* fixo;
	SDL_Surface* movel;
	SDL_Surface* bomba;
	SDL_Surface* fogo;
	SDL_Surface* inimigo[5];
	SDL_Surface* porta;
	SDL_Surface* topo;
	SDL_Surface* vida;
	SDL_Color cor = {255,10,2};//vermelho
	SDL_Surface* texto;
	char ponto[10];

	Mix_Music* music;
	Mix_Chunk* bombaSound;

	bombaSound = Mix_LoadWAV("./sounds/efeitos/explosao.WAV");
	
	TTF_Init();
	fonte = TTF_OpenFont("./fonte/baabookhmkbold.ttf",24);
	pausefonte = TTF_OpenFont("./fonte/baabookhmkbold.ttf",48);

	int **posInim; //matriz que armazena a posição do inimigo
	posInim = AlocaEspaco(inimigos, 5);
	if(!posInim) return -3;

	dst_car.x = PADRAO;
	dst_car.y = PADRAO * 2;
	switch(sorteiaFase(inimigos,posInim)) // retorna um valor sorteade de 0 ~ 3 para escolher o fundo..
	{
		case 0:
			fundo = SDL_LoadBMP("./imgs/jogo/fundo0.bmp");
			music = Mix_LoadMUS("./sounds/trilhas/branca.mid");
			if(!fundo) return 2;
			break;
		case 1:
			fundo = SDL_LoadBMP("./imgs/jogo/fundo1.bmp");
			music = Mix_LoadMUS("./sounds/trilhas/amarela.mid");
			if(!fundo) return 2;
			break;
		case 2:
			fundo = SDL_LoadBMP("./imgs/jogo/fundo2.bmp");
			music = Mix_LoadMUS("./sounds/trilhas/azul.mid");
			if(!fundo) return 2;
			break;
		case 3:
			fundo = SDL_LoadBMP("./imgs/jogo/fundo3.bmp");
			music = Mix_LoadMUS("./sounds/trilhas/verde.mid");
			if(!fundo) return 2;
			break;
		default:
			fundo = SDL_LoadBMP("./imgs/jogo/fundo0.bmp");
			music = Mix_LoadMUS("./sounds/trilhas/branca.mid");
			if(!fundo) return 2;
			break;
	}

	if(musicON)	Mix_PlayMusic(music, -1);

	SDL_Event event;
	int quit = 0,pause = 0,mouse_x,mouse_y;
	int i, j, poeBomba = 0, poeFogo = 0, perdeuVida = 0,playExplosion = 1;
	int **matriz; //matriz que representa a tela
	char mov_atual = 'n', mov_prox = 'n', mov_car;
	char *n="./matrizes/matriz0.bin";	//abre a matriz apartir de um arquivo bin.
	FILE *p;
	Uint32 temp, invulneravel = 0;

	matriz = AlocaEspaco(SCREEN_H/PADRAO, SCREEN_W/PADRAO);
	if(!matriz) return -2;

	p=fopen(n,"r");
	if(!p) return -1;


	//manipulando os valores da matriz

	for(i=0; i<SCREEN_H/PADRAO; i++)
	{
		for(j=0; j<SCREEN_W/PADRAO; j++)
		{
			fread(&matriz[i][j],sizeof(int),1,p);
		}
	}

	fclose(p);

	car = SDL_LoadBMP("./imgs/jogo/cars.bmp");
	if(!car) return 1;
	SDL_SetColorKey(car, SDL_SRCCOLORKEY, SDL_MapRGB(car->format, 255, 156, 255));

    fixo = SDL_LoadBMP("./imgs/jogo/movel.bmp");
	if(!fixo) return 3;
	SDL_SetColorKey(fixo, SDL_SRCCOLORKEY, SDL_MapRGB(fixo->format, 255, 156, 255));

	movel = SDL_LoadBMP("./imgs/jogo/fixo2.bmp");
	if(!movel) return 4;
	SDL_SetColorKey(movel, SDL_SRCCOLORKEY, SDL_MapRGB(movel->format, 255, 156, 255));

	bomba = SDL_LoadBMP("./imgs/jogo/bomba.bmp");
	if(!bomba) return 5;
	SDL_SetColorKey(bomba, SDL_SRCCOLORKEY, SDL_MapRGB(bomba->format, 255, 0, 255));

	fogo = SDL_LoadBMP("./imgs/jogo/fogo0.bmp");
	if(!fogo) return 6;
	SDL_SetColorKey(fogo, SDL_SRCCOLORKEY, SDL_MapRGB(fogo->format, 255, 255, 255));



	inimigo[0] = SDL_LoadBMP("./imgs/jogo/enemy.bmp");
	if(!inimigo) return 7;
	SDL_SetColorKey(inimigo[0], SDL_SRCCOLORKEY, SDL_MapRGB(inimigo[0]->format, 255, 0, 255));

	inimigo[1] = SDL_LoadBMP("./imgs/jogo/enemy2.bmp");
	if(!inimigo) return 7;
	SDL_SetColorKey(inimigo[1], SDL_SRCCOLORKEY, SDL_MapRGB(inimigo[1]->format, 255, 0, 255));

	inimigo[2] = SDL_LoadBMP("./imgs/jogo/enemy3.bmp");
	if(!inimigo) return 7;
	SDL_SetColorKey(inimigo[2], SDL_SRCCOLORKEY, SDL_MapRGB(inimigo[2]->format, 255, 0, 255));

	inimigo[3] = SDL_LoadBMP("./imgs/jogo/enemy4.bmp");
	if(!inimigo) return 7;
	SDL_SetColorKey(inimigo[3], SDL_SRCCOLORKEY, SDL_MapRGB(inimigo[3]->format, 255, 0, 255));

	inimigo[4] = SDL_LoadBMP("./imgs/jogo/enemy5.bmp");
	if(!inimigo) return 7;
	SDL_SetColorKey(inimigo[4], SDL_SRCCOLORKEY, SDL_MapRGB(inimigo[4]->format, 255, 0, 255));



	porta = SDL_LoadBMP("./imgs/jogo/porta.bmp");
	if(!porta) return 8;
	SDL_SetColorKey(porta, SDL_SRCCOLORKEY, SDL_MapRGB(porta->format, 255, 0, 255));

	topo = SDL_LoadBMP("./imgs/jogo/topo.bmp");
	if(!topo) return 9;
	SDL_SetColorKey(topo, SDL_SRCCOLORKEY, SDL_MapRGB(topo->format, 255, 0, 255));

	vida = SDL_LoadBMP("./imgs/jogo/vida.bmp");
	if(!vida) return 10;
	SDL_SetColorKey(vida, SDL_SRCCOLORKEY, SDL_MapRGB(vida->format, 255, 0, 255));

	SDL_WM_SetCaption("Bomber Kart","bomberkart");

	while(!quit)
    {
		while(SDL_PollEvent(&event)) //checar eventos
		{

			switch(event.type)
			{
				case SDL_QUIT://sair do loop principal
					if((!poeBomba) && (!poeFogo)) quit = ConfirmaSaida(screen);
					break;

				case SDL_MOUSEBUTTONDOWN:
					SDL_GetMouseState(&mouse_x, &mouse_y);

					if(mouse_x > 605 && mouse_x < 663 && mouse_y > 29 && mouse_y < 46)
					{
							if ((!pause) && (!poeBomba) && (!poeFogo))
							{
								pause = 1;
							}
							else
							{
								pause = 0;
							}
							break;
					}
					if(mouse_x > 605 && mouse_x < 643 && mouse_y > 9 && mouse_y < 23)
					{
						if((!poeBomba) && (!poeFogo)) quit = ConfirmaSaida(screen);
					}

				case SDL_KEYDOWN:
					if(event.key.keysym.sym == SDLK_p)
					{
							if ((!pause) && (!poeBomba) && (!poeFogo))
							{
								pause = 1;
							}
							else
							{
								pause = 0;
							}
							break;
					}
					else if(!pause)
					{
						switch(event.key.keysym.sym)
						{

							case SDLK_UP:
								mov_prox = 'u';
								break;

							case SDLK_DOWN:
								mov_prox = 'd';
								break;

							case SDLK_LEFT:
								mov_prox = 'l';
								break;

							case SDLK_RIGHT:
								mov_prox = 'r';
								break;

							case SDLK_ESCAPE:
								if((!poeBomba) && (!poeFogo)) quit = ConfirmaSaida(screen);
							break;

							case SDLK_SPACE:
								//só põe uma bomba quando não há nenhuma outra bomba, nem nenhum outro fogo, nem sobre um objeto (fixo ou destrutível)
								if((!poeBomba) && (!poeFogo) && (!matriz[dst_car.y/PADRAO][dst_car.x/PADRAO]))
								{
									//poe bombas alinhadas com a grade
									dst_bomba.x = (dst_car.x/PADRAO)*PADRAO;
									dst_bomba.y = (dst_car.y/PADRAO)*PADRAO;
									temp = SDL_GetTicks();
									poeBomba=1;
								}
								break;

							default:
								break;
						}
					}
				break;

				case SDL_KEYUP:
					switch(event.key.keysym.sym)
					{
						case SDLK_UP:
							if(mov_prox == 'u' || (mov_prox == 'n' && mov_atual == 'u')) mov_prox = 'p';
							break;
						case SDLK_DOWN:
							if(mov_prox == 'd' || (mov_prox == 'n' && mov_atual == 'd')) mov_prox = 'p';
							break;
						case SDLK_LEFT:
							if(mov_prox == 'l' || (mov_prox == 'n' && mov_atual == 'l')) mov_prox = 'p';
							break;
						case SDLK_RIGHT:
							if(mov_prox == 'r' || (mov_prox == 'n' && mov_atual == 'r')) mov_prox = 'p';
							break;
						default:
							break;
					}
					break;

				default:
					break;
			}
		}

		if(!pause)
		{
			SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 181, 0));

			SDL_BlitSurface(fundo, NULL, screen, NULL);

			//só ativa as opções se uma bomba for colocada ou um fogo for acionado
			if(poeBomba || poeFogo)
			{
				if((SDL_GetTicks() - temp < 1300) && (poeBomba == 1))
				{
					//recebe o valor de poeFogo = 1 quando a bomba for colocada na tela
					poeFogo = Explosao(poeBomba, poeFogo, temp, screen, bomba, fogo, matriz);
				}
				else if((SDL_GetTicks() - temp < 2300) && (poeFogo == 1))
				{
					//recebe o valor de poeBomba = 0 quando o fogo é colocado na tela
					poeBomba = Explosao(poeBomba, poeFogo, temp, screen, bomba,fogo, matriz);

					perdeuVida = ChecaDestruicaoInimigosJogador(matriz, posInim, invulneravel);

					if(perdeuVida)
					{
						invulneravel = SDL_GetTicks();
						perdeuVida = 0;
					}

				}
				else
				{
					//chega se os objetos foram destruídos
					ChecaDestruicaoNaoFixo(matriz);
					//recebe o valor de poeFogo = 0 quando o fogo é retirado da tela
					poeFogo = Explosao(poeBomba, poeFogo, temp, screen, bomba, fogo, matriz);
				}
			}

			// Efeito sonoro explosao da bomba
			if((!poeBomba) && playExplosion)
			{
				if(musicON) Mix_PlayChannel(-1, bombaSound, 0);	
				playExplosion = 0;
			}
			else
			{
				if(poeBomba) playExplosion = 1;
			}

			SDL_Delay(del);

			CarregarObj(matriz, fixo, movel, screen, inimigo, posInim, porta);

			mov_car = Movimenta(&mov_atual,&mov_prox, matriz, car, posInim);

			if(mov_car == 'f') //se chegar ao final da fase
			{
				Mix_FreeMusic(music);
				Mix_FreeChunk(bombaSound);
				free(matriz); //libera o espaço alocado na memória pela matriz da tela
				free(posInim); //libera o espaço alocado na memória pela matriz posInim
				SDL_FreeSurface(car); //libera, da memória, o espaço da surface da imagem do jogador
				SDL_FreeSurface(fixo); //libera, da memória, o espaço da surface da imagem do quadrado fixo
				SDL_FreeSurface(movel); //libera, da memória, o espaço da surface da imagem do quadrado movel
				SDL_FreeSurface(bomba); //libera, da memória, o espaço da surface da imagem da bomba
				SDL_FreeSurface(fogo); //libera, da memória, o espaço da surface da imagem do fogo
				SDL_FreeSurface(inimigo[0]); //libera, da memória, o espaço da surface da imagem do inimigo[0]
				SDL_FreeSurface(inimigo[1]); //libera, da memória, o espaço da surface da imagem do inimigo[1]
				SDL_FreeSurface(inimigo[2]); //libera, da memória, o espaço da surface da imagem do inimigo[2]
				SDL_FreeSurface(inimigo[3]); //libera, da memória, o espaço da surface da imagem do inimigo[3]
				SDL_FreeSurface(inimigo[4]); //libera, da memória, o espaço da surface da imagem do inimigo[4]
				SDL_FreeSurface(porta); //libera, da memória, o espaço da surface da imagem da saída
				SDL_FreeSurface(topo); //libera, da memória, o espaço da surface da imagem do topo
				SDL_FreeSurface(vida); //libera, da memória, o espaço da surface da imagem vida
				//SDL_FreeSurface(texto);

				return 100; // VERIFICA FINAL DE FASE
			}

			AtualizaImagemCarro(mov_car);

			perdeuVida = ChoqueJogador(posInim, invulneravel);
			if(perdeuVida)
			{
				invulneravel = SDL_GetTicks();
				perdeuVida = 0;
			}

			SDL_BlitSurface(car, &show_car, screen, &dst_car);

			SDL_BlitSurface(topo, NULL, screen, &dst_topo);

			dst_vidas.x = 90;
			for(i=0;i<vidas;i++)
			{
				SDL_BlitSurface(vida, NULL, screen, &dst_vidas);
				dst_vidas.x += 40;
			}

			if(vidas < 1)
			{
				salvarecorde(screen,pontos);
				Mix_FreeMusic(music);
				Mix_FreeChunk(bombaSound);
				free(matriz); //libera o espaço alocado na memória pela matriz da tela
				free(posInim); //libera o espaço alocado na memória pela matriz posInim
				SDL_FreeSurface(car); //libera, da memória, o espaço da surface da imagem do jogador
				SDL_FreeSurface(fixo); //libera, da memória, o espaço da surface da imagem do quadrado fixo
				SDL_FreeSurface(movel); //libera, da memória, o espaço da surface da imagem do quadrado movel
				SDL_FreeSurface(bomba); //libera, da memória, o espaço da surface da imagem da bomba
				SDL_FreeSurface(fogo); //libera, da memória, o espaço da surface da imagem do fogo
				SDL_FreeSurface(inimigo[0]); //libera, da memória, o espaço da surface da imagem do inimigo[0]
				SDL_FreeSurface(inimigo[1]); //libera, da memória, o espaço da surface da imagem do inimigo[1]
				SDL_FreeSurface(inimigo[2]); //libera, da memória, o espaço da surface da imagem do inimigo[2]
				SDL_FreeSurface(inimigo[3]); //libera, da memória, o espaço da surface da imagem do inimigo[3]
				SDL_FreeSurface(inimigo[4]); //libera, da memória, o espaço da surface da imagem do inimigo[4]
				SDL_FreeSurface(porta); //libera, da memória, o espaço da surface da imagem da saída
				SDL_FreeSurface(topo); //libera, da memória, o espaço da surface da imagem do topo
				SDL_FreeSurface(vida); //libera, da memória, o espaço da surface da imagem vida
				return 0;

			}

		   //itoa(pontos,ponto,10);
		   sprintf(ponto, "%d", pontos); 
		   // BLITANDO VARIÁVEL "pontos"
		    
			texto = TTF_RenderText_Blended(fonte,ponto,cor);
			SDL_BlitSurface(texto,NULL,screen,&dst_pontos);
			SDL_Flip(screen);
			SDL_FreeSurface(texto);
		}
		else
		{

			// BLITAR TEXTO PAUSE NA TELA...
			texto = TTF_RenderText_Blended(pausefonte,"PAUSE",cor);
			SDL_BlitSurface(texto,NULL,screen,&dst_pause);
			SDL_Flip(screen);
			SDL_FreeSurface(texto);

		}
	}
	TTF_Quit();

	Mix_FreeMusic(music);
	Mix_FreeChunk(bombaSound);
	free(matriz); //libera o espaço alocado na memória pela matriz da tela
	free(posInim); //libera o espaço alocado na memória pela matriz posInim
	SDL_FreeSurface(car); //libera, da memória, o espaço da surface da imagem do jogador
	SDL_FreeSurface(fixo); //libera, da memória, o espaço da surface da imagem do quadrado fixo
	SDL_FreeSurface(movel); //libera, da memória, o espaço da surface da imagem do quadrado movel
	SDL_FreeSurface(bomba); //libera, da memória, o espaço da surface da imagem da bomba
	SDL_FreeSurface(fogo); //libera, da memória, o espaço da surface da imagem do fogo
	SDL_FreeSurface(inimigo[0]); //libera, da memória, o espaço da surface da imagem do inimigo[0]
	SDL_FreeSurface(inimigo[1]); //libera, da memória, o espaço da surface da imagem do inimigo[1]
	SDL_FreeSurface(inimigo[2]); //libera, da memória, o espaço da surface da imagem do inimigo[2]
	SDL_FreeSurface(inimigo[3]); //libera, da memória, o espaço da surface da imagem do inimigo[3]
	SDL_FreeSurface(inimigo[4]); //libera, da memória, o espaço da surface da imagem do inimigo[4]
	SDL_FreeSurface(porta); //libera, da memória, o espaço da surface da imagem da saída
	SDL_FreeSurface(topo); //libera, da memória, o espaço da surface da imagem do topo
	SDL_FreeSurface(vida); //libera, da memória, o espaço da surface da imagem vida
    return 0;
}
