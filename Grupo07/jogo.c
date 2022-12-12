#include <SDL.h>
#include<time.h>
#include<stdlib.h>
#include <SDL_mixer.h> 
#include <SDL_image.h>
#define SCREEN_W 640 
#define SCREEN_H 480

//Superfícies e posiões da funão Introdução
SDL_Surface* bob;
SDL_Rect posbob = {260, 210, 0, 0};
SDL_Surface* fundo;
SDL_Rect posfundo = {0, 0, 0, 0};
SDL_Surface* enter;
SDL_Rect posenter = {220, 280, 0, 0};
int incx = 5;
Mix_Chunk* som;
Mix_Music* musica;
int i=0, j;
void menu (SDL_Surface*, int);

void animacao(int max_w, int max_h)
{
	posbob.x += incx;
	if (incx > 0)
	{
		if (posbob.x % 20 == 0) bob = SDL_LoadBMP("bomb4.bmp");
		if (posbob.x % 20 == 5) bob = SDL_LoadBMP("bomb5.bmp");
		if (posbob.x % 20 == 10) bob = SDL_LoadBMP("bomb4.bmp");
		if (posbob.x % 20 == 15) bob = SDL_LoadBMP("bomb6.bmp");
		if (posbob.x % 320 == 0)
		{
			bob = SDL_LoadBMP("bomb6.bmp");
			incx = -5;
		}
	}
	if (incx < 0)
	{
		if (posbob.x % 20 == 0) bob = SDL_LoadBMP("bomb1.bmp");
		if (posbob.x % 20 == 15) bob = SDL_LoadBMP("bomb2.bmp");
		if (posbob.x % 20 == 10) bob = SDL_LoadBMP("bomb1.bmp");
		if (posbob.x % 20 == 5) bob = SDL_LoadBMP("bomb3.bmp");
		if (posbob.x % 260 == 0)
		{
			bob = SDL_LoadBMP("bomb3.bmp");
			incx = 5;
		}
	}	
}

void fade (SDL_Surface* superficie, SDL_Surface* superficie2)
{
	j=255;
	void SDL_Delay(Uint32 ms);
	while (j!=0)
	{
		SDL_SetAlpha(superficie, SDL_SRCALPHA, j);
		j = j-1;
		void SDL_Delay(Uint32 ms);
		SDL_Delay(5);
		SDL_FillRect(superficie2, NULL, SDL_MapRGB(superficie2->format, (255-j), (255-j), (255-j)));
		SDL_BlitSurface(superficie, NULL, superficie2, &posbob);
        SDL_Flip(superficie2);
	}
	i=50;
}

void audio (SDL_Surface* tela, int saida)
{
	Mix_PlayChannel(1, som, 0);
	Mix_VolumeChunk(som, 16);
	Mix_VolumeMusic(MIX_MAX_VOLUME);
	Mix_PlayMusic(musica, 0);
	while (j!=255)
	{
		SDL_SetAlpha(fundo, SDL_SRCALPHA, j);
		j++;
		void SDL_Delay(Uint32 ms);
		SDL_Delay(5);
		SDL_BlitSurface(fundo, NULL, tela, &posfundo);
		SDL_Flip(tela);
	}
	menu (tela, saida);
	return;
}

void intro(SDL_Surface* screen, int quit)
{
    SDL_Event event;
	int j=255, k=51;
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
	Mix_AllocateChannels(4);
	som = Mix_LoadWAV("explosion.wav");
	musica = Mix_LoadMUS("musica.ogg");
	fundo = IMG_Load("fundoexplosao1.JPG");
	enter = IMG_Load("enter.GIF");
	
    while(!quit)
    {
        while(SDL_PollEvent(&event))
        {
			switch(event.type)
			{
				case SDL_KEYDOWN:
				switch(event.key.keysym.sym)
				{
					case SDLK_RETURN:
					i++;
					default:
					break;
				}
			}
			if(event.type == SDL_QUIT)
			{
				quit = 1;
			}
		}
		if (i==0)
		{
			animacao(SCREEN_W, SCREEN_H);
		}
		if ((i>0) && (i<50))
		{
			fade(bob, screen);
		}
		if (i>=50)
		{
			audio (screen, quit);
			return;
		}
		//Limpa a tela
		SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
		//Copia as imagens
		SDL_SetColorKey(bob, SDL_SRCCOLORKEY, SDL_MapRGB(bob->format, 249, 85, 215));
		SDL_BlitSurface(bob, NULL, screen, &posbob);
		SDL_SetColorKey(enter, SDL_SRCCOLORKEY, SDL_MapRGB(enter->format, 255, 0, 255));
		SDL_BlitSurface(enter, NULL, screen, &posenter);
		SDL_SetAlpha(enter, SDL_SRCALPHA, j);
		j = j - k;
		if(j<=0)
		{
			j++;
			k=-k;
		}
		if (j>=255)
		{
			j--;
			k=-k;
		}
        SDL_Flip(screen); //Atualiza a tela
		void SDL_Delay(Uint32 ms);
		SDL_Delay(150);
    }
	Mix_FreeChunk(som);
	Mix_FreeMusic(musica);
	Mix_CloseAudio();
    SDL_Quit(); //Encerra a SDL
}

/****************************************
Início da Função Menu
*****************************************/
//botoes normais
SDL_Surface* b1;
SDL_Surface* b2;
SDL_Surface* b3;

//botoes qdo estao selecionados, com o mouse sobre eles
SDL_Surface* b1u;
SDL_Surface* b2u;
SDL_Surface* b3u;

//botoes qdo estao apertados
SDL_Surface* b1p;
SDL_Surface* b2p;
SDL_Surface* b3p;

//aqui controlaremos a posiçao dos botoes
SDL_Rect button [3];

//um evento qlq
SDL_Event sdlevent;

//stado dos botoes (0 pra normal, 1 pra "marcado", 2 pra apertado)
int b1state = 0;
int b2state = 0;
int b3state = 0;

void menu (SDL_Surface* screen, int quit)
{

   //carregando as imagens....dã, o problema é q nao achei, entao fiz como se só tivessem 3 botoes...
    b1 = IMG_Load("b1.GIF");
    b2 = IMG_Load("b2.GIF");
    b3 = IMG_Load("b3.GIF");
    b1u = IMG_Load("b1up.GIF");
    b2u = IMG_Load("b2up.GIF");
    b3u = IMG_Load("b3up.GIF");
    b1p = IMG_Load("b1press.GIF");
    b2p = IMG_Load("b2press.GIF");
    b3p = IMG_Load("b3press.GIF");
	
	SDL_SetColorKey(b1, SDL_SRCCOLORKEY, SDL_MapRGB(b1->format, 255, 0, 255));
	SDL_SetColorKey(b1u, SDL_SRCCOLORKEY, SDL_MapRGB(b1u->format, 255, 0, 255));
	SDL_SetColorKey(b1p, SDL_SRCCOLORKEY, SDL_MapRGB(b1p->format, 255, 0, 255));
	SDL_SetColorKey(b2, SDL_SRCCOLORKEY, SDL_MapRGB(b2->format, 255, 0, 255));
	SDL_SetColorKey(b2u, SDL_SRCCOLORKEY, SDL_MapRGB(b2u->format, 255, 0, 255));
	SDL_SetColorKey(b2p, SDL_SRCCOLORKEY, SDL_MapRGB(b2p->format, 255, 0, 255));
	SDL_SetColorKey(b3, SDL_SRCCOLORKEY, SDL_MapRGB(b3->format, 255, 0, 255));
	SDL_SetColorKey(b3u, SDL_SRCCOLORKEY, SDL_MapRGB(b3u->format, 255, 0, 255));
	SDL_SetColorKey(b3p, SDL_SRCCOLORKEY, SDL_MapRGB(b3p->format, 255, 0, 255));
      
   //posicionando os ditos cujos
    button[0].x = 265;
	button[1].x = 225;
	button[2].x = 275;
    button[0].y = 100;
    button[1].y = 180;
    button[2].y = 260;

   //e agora blitando
    SDL_BlitSurface ( b1, 0, screen, &button[0] );
    SDL_BlitSurface ( b2, 0, screen, &button[1] );
    SDL_BlitSurface ( b3, 0, screen, &button[2] );


   //nosso famoso while
    while (!quit)
	{
		while (SDL_PollEvent(&sdlevent))
		{
          
			if(sdlevent.type == SDL_QUIT) 
			{
		 		quit = 1; 
			}
			 
		 
		 
		 
		 //se o mouse ta DENTRO do botao[0]
			if ( ( sdlevent.motion.x >= button[0].x )
				 && ( sdlevent.motion.x <= ( button[0].x + button[0].w ) )
				&& ( sdlevent.motion.y >= ( button[0].y ) )
				&& ( sdlevent.motion.y <= ( button[0].y + button[0].h ) ) )
			{
             //troca o estado pra "marcado"
				 b1state = 1;

             if ( sdlevent.type == SDL_MOUSEBUTTONDOWN )
             { 
                //se o cidadao clicar com o mouse
				if ( sdlevent.button.button == SDL_BUTTON_LEFT )
                {
                   //troca o estado pra apertado
                   b1state = 2;
				   return;
                }
             }
          }

          //senao fica como tava
          else b1state = 0;
            
          //msma ideia mas pro botao[1] e por ai vai
          if ( ( sdlevent.motion.x >= button[1].x )
             && ( sdlevent.motion.x <= ( button[1].x + button[1].w ) )
             && ( sdlevent.motion.y >= ( button[1].y ) )
             && ( sdlevent.motion.y <= ( button[1].y + button[1].h ) ) )
          {
             
             b2state = 1;
            
             if ( sdlevent.type == SDL_MOUSEBUTTONDOWN )
             {
               
                if ( sdlevent.button.button == SDL_BUTTON_LEFT )
                {
                   
                   b2state = 2;
				   //quit=1;
                }
             }
          }

         
          else b2state = 0;
         
         
          if ( ( sdlevent.motion.x >= button[2].x )
             && ( sdlevent.motion.x <= ( button[2].x + button[2].w ) )
             && ( sdlevent.motion.y >= ( button[2].y ) )
             && ( sdlevent.motion.y <= ( button[2].y + button[2].h ) ) )
          {
            
             b3state = 1;
               
             if ( sdlevent.type == SDL_MOUSEBUTTONDOWN )
             {
              
                if ( sdlevent.button.button == SDL_BUTTON_LEFT )
                {
                  
                   b3state = 2;
				   quit=1;
                }
             }
          }

        
          else b3state = 0;

          
		  
		  //blita os bagulhos de acordo com o estado


          if (b1state==0)
		  {
			  SDL_BlitSurface ( b1, 0, screen, &button[0] );
			  
		  }
          else if (b1state==1)
				{	
					SDL_BlitSurface ( b1u, 0, screen, &button[0] );
				}
				else if (b1state==2)
						{
							SDL_BlitSurface ( b1p, 0, screen, &button[0] );
						}
          if (b2state==0)
		  {
			  SDL_BlitSurface ( b2, 0, screen, &button[1] );
		  }
          else if (b2state==1)
		        {
					SDL_BlitSurface ( b2u, 0, screen, &button[1] );
				}
				else if (b2state==2)
					  {
							SDL_BlitSurface ( b2p, 0, screen, &button[1] );
					  }
          if ( b3state == 0 )
		  {
			  SDL_BlitSurface ( b3, 0, screen, &button[2] );
		  }
		  else if ( b3state == 1 )
				{
					SDL_BlitSurface ( b3u, 0, screen, &button[2] );
				}
				else if ( b3state == 2 )
					  {
							SDL_BlitSurface ( b3p, 0, screen, &button[2] );
					  }

			SDL_Flip(screen);
       }
    }
	void SDL_Delay(Uint32 ms);
	SDL_Delay(150);
	SDL_Quit(); 
	//return 0;
} 

/*************************
Aqui começa a parte principal do código
*************************/

SDL_Surface* my_surfbmp; // Carregando a parede
SDL_Rect dst_rectbmp = {0, 0, 0, 0};
SDL_Surface* caixa;
SDL_Rect poscaixa = {0, 0, 0, 0}; 
SDL_Surface* bomber; // Carregando o personagem
SDL_Rect posbmp = {32, 32, 0, 0};
SDL_Surface* bomba;
SDL_Rect posbomba = {0, 0, 0, 0};
SDL_Surface* saida;
SDL_Rect possaida = {0, 0, 0, 0};
SDL_Surface* fogo;
SDL_Rect posfogo = {0, 0, 0, 0};
SDL_Surface* fim;
SDL_Rect posfim = {0, 0, 0, 0};

int matriz[100][100];
int xVel=0;
int yVel=0;
int incr=4;
int deslocamento =32, pontos, vidas=3;
float tempo;

void Recorde ()
{
	FILE *arq;
	char *arq2 = "recorde.txt";
	int pontuacao;
	pontuacao = pontos + vidas*150;
	arq = fopen(arq2,"a");
	fprintf(arq,"\nJOGADOR:ZE SA  PONTOS:%d",pontuacao);
	fclose(arq);
}


void displayer (SDL_Surface* screen)
{
	SDL_Surface* display[2];
	SDL_Rect posdisp1 = {5,5,0,0};
	SDL_Rect posdisp2 = {80,5,0,0};
	SDL_Surface* num[9];
	char linha[40];
	int i, valor;
	
	num[0] = SDL_LoadBMP("0.bmp");
    num[1] = SDL_LoadBMP("1.bmp");
    num[2] = SDL_LoadBMP("2.bmp");
    num[3] = SDL_LoadBMP("3.bmp");
    num[4] = SDL_LoadBMP("4.bmp");
    num[5] = SDL_LoadBMP("5.bmp");
    num[6] = SDL_LoadBMP("6.bmp");
    num[7] = SDL_LoadBMP("7.bmp");
    num[8] = SDL_LoadBMP("8.bmp");
	num[9] = SDL_LoadBMP("9.bmp");
	display[0] = SDL_LoadBMP("vidas.bmp");
	display[1] = SDL_LoadBMP("pontos.bmp");
	SDL_BlitSurface (display[0], 0, screen, &posdisp1);
	posdisp1.x += display[0]->w;
	SDL_BlitSurface (num[vidas], 0, screen, &posdisp1);
	SDL_BlitSurface (display[1], 0, screen, &posdisp2);
	posdisp2.x += display[1]->w;
	
	//itoa(pontos,linha,10);
	
	sprintf(linha, "%d", pontos);
	
	for(i=0;i<strlen(linha);i++)
	{
		valor = (linha[i] - '0');
		SDL_BlitSurface (num[valor], 0, screen, &posdisp2);
		posdisp2.x+=num[valor]->w;
	}
	
	return;
}

void mapeando (SDL_Surface* screen)//matriz que define o labirinto
{
	int i, j;
	srand(time(NULL));
	for (i=0; i<(SCREEN_W/my_surfbmp->w); i++)//zerando a matriz
	{
		for (j=0; j<(SCREEN_H/my_surfbmp->h); j++)
		{
			matriz[i][j] = 0;
		}
	}
	
	for (i=0; i<(SCREEN_W/my_surfbmp->w); i++)
	{
		for (j=0; j<(SCREEN_H/my_surfbmp->h); j++)
		{
			if (i==0||j==0||i==(SCREEN_W/my_surfbmp->w)-1||j==(SCREEN_H/my_surfbmp->h)-1)//pq a matriz começa no 00 e sua ultima coluna e linha eh n-1
			{
				matriz[i][j] = 1; //bordas marcadas com 1
			}
		}
	}
	
	for (i=0;i<(SCREEN_W/my_surfbmp->w);i+=2)// outras partes da matriz marcadas com 1
	{
		for (j=0;j<(SCREEN_H/my_surfbmp->h) ;j+=2)
		{
			matriz[i][j]=1;
		}		
	}
	
	for (i=3;i<(SCREEN_W/my_surfbmp->w)-2;i+=2)
	{
		for (j=1;j<(SCREEN_H/my_surfbmp->h) ;j+=2)
		{
			if (matriz[i][j]==0) matriz[i][j]=2;
		}		
	}
	
	for (j=1;j<(SCREEN_H/my_surfbmp->h) ;j+=2)
	{
		matriz[(SCREEN_W/my_surfbmp->w)-2][j]=2;
	}
	
	
	j = rand()%(SCREEN_H/my_surfbmp->h);
	while (j%2==0)
	{
		j = rand()%(SCREEN_H/my_surfbmp->h);
	}
	matriz[(SCREEN_W/my_surfbmp->w)-2][j]=10;
	
	for (i=0;i<(SCREEN_W/my_surfbmp->w);i+=2)// outras partes da matriz marcadas com 1
	{
		for (j=0;j<(SCREEN_H/my_surfbmp->h) ;j+=2)
		{
			matriz[i][j]=1;
		}		
	}


}

void termino (SDL_Surface* screen)
{

    SDL_Surface* creditos;
	SDL_Rect posimg = {0, 0, 0, 0};
	int i=0;
	
	creditos = IMG_Load("creditos.GIF");
	while (i<255)
	{
		SDL_SetAlpha(creditos, SDL_SRCALPHA, i);
		SDL_BlitSurface(creditos, NULL, screen, &posimg);
		SDL_Flip(screen); //atualiza a tela
		i++;
	}

}

int mapa (SDL_Surface* screen, int timer, int plantada, int quit)
{
	int i, j, alcance;
	for (i=0; i<(SCREEN_W/my_surfbmp->w); i++)
	{
		for (j=0; j<(SCREEN_H/my_surfbmp->h); j++)
		{
			if (matriz[i][j]==1)
			{
				SDL_Rect dst_rectbmp = {(i*my_surfbmp->w), (j*my_surfbmp->h), 0, 0};//colocando a imagem da parede onde a matriz tem valor 1			
				SDL_BlitSurface(my_surfbmp, NULL, screen, &dst_rectbmp);
			}
			if (matriz[i][j]==2)
			{
				SDL_Rect poscaixa = {(i*my_surfbmp->w), (j*my_surfbmp->h), 0, 0};			
				SDL_BlitSurface(caixa, NULL, screen, &poscaixa);
			}
			
			if (matriz[i][j]==-1)
			{
				SDL_Rect posbomba = {(i*my_surfbmp->w), (j*my_surfbmp->h), 0, 0};			
				SDL_BlitSurface(bomba, NULL, screen, &posbomba);
				if (SDL_GetTicks()>=timer+2000)
				{
					SDL_BlitSurface(fogo, NULL, screen, &posbomba);
					alcance =0;
					while (alcance<3)
					{
						if (matriz[(posbomba.x/my_surfbmp->w)+alcance][posbomba.y/my_surfbmp->h]!=1)
						{
							if ((matriz[(posbomba.x/my_surfbmp->w)+alcance][posbomba.y/my_surfbmp->h]==2)||(matriz[(posbomba.x/my_surfbmp->w)+alcance][posbomba.y/my_surfbmp->h]==0))
							{
								if (matriz[(posbomba.x/my_surfbmp->w)+alcance][posbomba.y/my_surfbmp->h]==2) pontos +=10;
								matriz[(posbomba.x/my_surfbmp->w)+alcance][posbomba.y/my_surfbmp->h] = -3;
							}
							if (matriz[(posbomba.x/my_surfbmp->w)+alcance][posbomba.y/my_surfbmp->h]==10)
							{
								matriz[(posbomba.x/my_surfbmp->w)+alcance][posbomba.y/my_surfbmp->h] = -100;
								pontos +=10;
							}
						}
						else break;
						alcance++;
					}
					alcance =0;
					while (alcance<3)
					{
						if (matriz[(posbomba.x/my_surfbmp->w)-alcance][posbomba.y/my_surfbmp->h]!=1)
						{
							if ((matriz[(posbomba.x/my_surfbmp->w)-alcance][posbomba.y/my_surfbmp->h]==2)||(matriz[(posbomba.x/my_surfbmp->w)-alcance][posbomba.y/my_surfbmp->h]==0))
							{
								if (matriz[(posbomba.x/my_surfbmp->w)-alcance][posbomba.y/my_surfbmp->h]==2)pontos +=10;
								matriz[(posbomba.x/my_surfbmp->w)-alcance][posbomba.y/my_surfbmp->h] = -3;
							}
							if (matriz[(posbomba.x/my_surfbmp->w)-alcance][posbomba.y/my_surfbmp->h]==10)
							{
								matriz[(posbomba.x/my_surfbmp->w)-alcance][posbomba.y/my_surfbmp->h] = -100;
								pontos +=10;
							}
						}
						else break;
						alcance++;
					}
					alcance =0;
					while (alcance<3)
					{
						if (matriz[(posbomba.x/my_surfbmp->w)][(posbomba.y/my_surfbmp->h)+alcance]!=1)
						{
							if ((matriz[(posbomba.x/my_surfbmp->w)][(posbomba.y/my_surfbmp->h)+alcance]==2)||(matriz[(posbomba.x/my_surfbmp->w)][(posbomba.y/my_surfbmp->h)+alcance]==0))
							{
								if (matriz[(posbomba.x/my_surfbmp->w)][(posbomba.y/my_surfbmp->h)+alcance]==2)pontos +=10;
								matriz[(posbomba.x/my_surfbmp->w)][(posbomba.y/my_surfbmp->h)+alcance] = -3;
							}
							if (matriz[(posbomba.x/my_surfbmp->w)][(posbomba.y/my_surfbmp->h)+alcance]==10)
							{
								matriz[(posbomba.x/my_surfbmp->w)][(posbomba.y/my_surfbmp->h)+alcance] = -100;
								pontos +=10;
							}
						}
						else break;
						alcance++;
					}
					alcance =0;
					while (alcance<3)
					{
						if (matriz[(posbomba.x/my_surfbmp->w)][(posbomba.y/my_surfbmp->h)-alcance]!=1)
						{
							if ((matriz[(posbomba.x/my_surfbmp->w)][(posbomba.y/my_surfbmp->h)-alcance]==2)||(matriz[(posbomba.x/my_surfbmp->w)][(posbomba.y/my_surfbmp->h)-alcance]==0))
							{
								if (matriz[(posbomba.x/my_surfbmp->w)][(posbomba.y/my_surfbmp->h)-alcance]==2)pontos +=10;
								matriz[(posbomba.x/my_surfbmp->w)][(posbomba.y/my_surfbmp->h)-alcance] = -3;
							}
							if (matriz[(posbomba.x/my_surfbmp->w)][(posbomba.y/my_surfbmp->h)-alcance]==10)
							{
								matriz[(posbomba.x/my_surfbmp->w)][(posbomba.y/my_surfbmp->h)-alcance]=-100;
								pontos +=10;
							}
						}
						else break;
						alcance++;
					}
					matriz[i][j]=-3;
				}
			}
			
			if (matriz[i][j]==-3)
			{
				SDL_Rect posfogo = {(i*my_surfbmp->w), (j*my_surfbmp->h), 0, 0};			
				SDL_BlitSurface(fogo, NULL, screen, &posfogo);
			}
			
			if (matriz[i][j]==10)
			{
				SDL_Rect possaida = {(i*my_surfbmp->w), (j*my_surfbmp->h), 0, 0};			
				SDL_BlitSurface(saida, NULL, screen, &possaida);
				SDL_BlitSurface(caixa, NULL, screen, &possaida);
			}
			if (matriz[i][j]==-100)
			{
				SDL_Rect possaida = {(i*my_surfbmp->w), (j*my_surfbmp->h), 0, 0};			
				SDL_BlitSurface(saida, NULL, screen, &possaida);
			}
		}
	}
	
	if(SDL_GetTicks()>=timer+2500)
	{
		for (i=0;i<(SCREEN_W/my_surfbmp->w);i++)
		{
			for (j=0;j<(SCREEN_H/my_surfbmp->h);j++)
			{
				if (matriz[i][j]==-3) 
				{
					matriz[i][j]=0;
				}
			}		
		}
		timer = 0;
		plantada = 0;
	}
	if (matriz[posbmp.x/my_surfbmp->w][posbmp.y/my_surfbmp->h]==-3 || matriz[(posbmp.x+bomber->w)/my_surfbmp->w][posbmp.y/my_surfbmp->h]==-3 || matriz[posbmp.x/my_surfbmp->w][(posbmp.y+bomber->h)/my_surfbmp->h]==-3)
	{
		posbmp.x=32;
		posbmp.y=32;
		xVel=0;
		yVel=0;
		vidas --;
	}
	
	if (matriz[posbmp.x/my_surfbmp->w][posbmp.y/my_surfbmp->h]==-100)
	{
		pontos+=300;
		Recorde (pontos);
		termino(screen);
		menu (screen, quit);
		posbmp.x = posbmp.y = 32;
		mapeando (screen);
		pontos=0;
		vidas = 3;
		
	}
	return plantada;
	
}

void move ()
{
	if ((matriz[(posbmp.x+xVel)/my_surfbmp->w][(posbmp.y+yVel)/my_surfbmp->h]>0) || (matriz[(posbmp.x+bomber->w+xVel)/my_surfbmp->w][(posbmp.y+bomber->h+yVel)/my_surfbmp->h]>0) || (matriz[(posbmp.x+bomber->w+xVel)/my_surfbmp->w][(posbmp.y+yVel)/my_surfbmp->h]>0) || (matriz[(posbmp.x+xVel)/my_surfbmp->w][(posbmp.y+bomber->h+yVel)/my_surfbmp->h]>0))
	{
		if(xVel!=0)xVel=0;
		if(yVel!=0) yVel=0;
	}
	else
	{
		posbmp.x += xVel;
		posbmp.y += yVel;
	}

}

int main(int argc, char** argv)
{
    SDL_Surface* screen;
    SDL_Event event; 
    int quit = 0;
	bomber = SDL_LoadBMP("ramzabaixo.bmp");//Carregar personagem
	int plantada=0, timer, j;
	
    SDL_Init(SDL_INIT_EVERYTHING);
    screen = SDL_SetVideoMode(SCREEN_W, SCREEN_H, 16, SDL_SWSURFACE);
	intro (screen, quit);
	caixa = SDL_LoadBMP("bloco.bmp"); // Carregar o quadradinho
	SDL_BlitSurface(my_surfbmp, NULL, screen, &dst_rectbmp);
	my_surfbmp = SDL_LoadBMP("azuc2.bmp"); // Carregar o quadradinho
	SDL_BlitSurface(my_surfbmp, NULL, screen, &dst_rectbmp);
	bomba = SDL_LoadBMP("bomba.bmp");
	saida = SDL_LoadBMP("pizza.bmp");
	fogo = SDL_LoadBMP("fogo.bmp");
	fim = IMG_Load("gameover.GIF");
	SDL_SetColorKey(saida, SDL_SRCCOLORKEY, SDL_MapRGB(saida->format, 255, 0, 255));
	SDL_SetColorKey(bomba, SDL_SRCCOLORKEY, SDL_MapRGB(saida->format, 255, 0, 255));
	SDL_SetColorKey(fogo, SDL_SRCCOLORKEY, SDL_MapRGB(saida->format, 255, 0, 255));
	SDL_SetColorKey(my_surfbmp, SDL_SRCCOLORKEY, SDL_MapRGB(my_surfbmp->format, 255, 0, 255));
	SDL_SetColorKey(caixa, SDL_SRCCOLORKEY, SDL_MapRGB(caixa->format, 255, 0, 255));
	posbmp.x = posbmp.y = 32;
	mapeando (screen);
	pontos=0;
	
	
    while(!quit)
    {
        while(SDL_PollEvent(&event)) //checar eventos
		{
			switch(event.type)
			{
				case SDL_KEYDOWN:
					switch(event.key.keysym.sym)
					{
						case SDLK_UP:
							bomber = SDL_LoadBMP("ramzacima.bmp");
							if (matriz[(posbmp.x/my_surfbmp->w)][(posbmp.y-deslocamento)/my_surfbmp->h]<=0)//prevê a posição futura do personagem para saber se é possível haver o deslocamento
							{
								yVel -= incr;	
							}
							break;
						case SDLK_DOWN:
							bomber = SDL_LoadBMP("ramzabaixo.bmp");
							if (matriz[(posbmp.x/my_surfbmp->w)][(posbmp.y+deslocamento)/my_surfbmp->h]<=0)
							{
								yVel += incr;
							}
							break;
						case SDLK_LEFT: 
							bomber = SDL_LoadBMP("ramzaesq.bmp");
							if (matriz[(posbmp.x-deslocamento)/my_surfbmp->w][(posbmp.y/my_surfbmp->h)]<=0)
							{
								xVel -= incr;
							}
							break;
						case SDLK_RIGHT: 
							bomber = SDL_LoadBMP("ramzadir.bmp");
							if (matriz[(posbmp.x+deslocamento)/my_surfbmp->w][(posbmp.y/my_surfbmp->h)]<=0)
							{
								xVel += incr;
							}	
							break;
						case SDLK_SPACE:
							if (plantada==0)
							{
								matriz[posbmp.x/my_surfbmp->w][posbmp.y/my_surfbmp->h]=-1;
								plantada =1;
								timer = SDL_GetTicks();
							}
							break;
							case SDLK_RETURN:
							menu (screen, quit);
							break;
						case SDLK_ESCAPE: quit = 1; 
							break;
						default: break;
					}
					break;
				case SDL_KEYUP:
					switch(event.key.keysym.sym)
					{
						case SDLK_UP: 
							if (yVel<0)
							{
								yVel = 0;
							}
							break;
						case SDLK_DOWN: 
							if (yVel>0)
							{
								yVel = 0;
							}
							break;
						case SDLK_LEFT: 
							if (xVel<0)
							{
								xVel = 0;
							}
							break;
						case SDLK_RIGHT: 
							if (xVel>0)
							{
								xVel = 0;
							}
							break;

						default: break;
					}
					break;
				default: break;
			}
            if(event.type == SDL_QUIT)
            {
				quit = 1;
			}
        }
		deslocamento = 32;
		SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 128, 64));
		SDL_BlitSurface(bomber, NULL, screen, &posbmp);
		SDL_SetColorKey(bomber, SDL_SRCCOLORKEY, SDL_MapRGB(bomber->format, 0, 255, 0));
		plantada = mapa(screen, timer, plantada, quit);
		displayer(screen);
		
		if (xVel!=0||yVel!=0)
		{
			while (deslocamento!=0)//coordena o alinhamento do personagem com a grade
			{
				SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 128, 64));
				plantada = mapa(screen, timer, plantada, quit);
				move();
				displayer(screen);
				SDL_BlitSurface(bomber, NULL, screen, &posbmp);
				deslocamento -= incr;
				void SDL_Delay(Uint32 ms);
				SDL_Delay(40);
				SDL_Flip(screen); //atualiza a tela
			}
		}
		if (vidas <= 0)
		{
			j=0;
			while (j<255)
			{
				SDL_SetAlpha(fim, SDL_SRCALPHA, j);
				SDL_BlitSurface(fim, NULL, screen, &posfim);
				SDL_Flip(screen); //atualiza a tela
				j++;
			}
			menu (screen, quit);
			posbmp.x = posbmp.y = 32;
			mapeando (screen);
			pontos=0;
			vidas = 3;
		}
        SDL_Flip(screen); //atualiza a tela
	}
    SDL_Quit();
	return 0;
}
