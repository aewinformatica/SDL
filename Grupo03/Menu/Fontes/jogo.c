#include "include.h"

int Fases (SDL_Surface *screen)
{
	jogo.vidas=3;
	Kenny.passo.cima=0;
	Kenny.passo.direita=0;
	Kenny.passo.esquerda=0;
	Kenny.passo.baixo=1;
	SDL_Event event;
	SDL_Surface *fundo;
	int quit=0;
	int velocidade=8;	
	int FPS;
	int i;
	char direcao;
	int tempo_da_fase, minutos, segundos, tempo_que_comecou_o_pause, tempo_que_acabou_o_pause, intervalo_pause=0;
	char minuto[5], segundo[5], pontos[10], vidinhas[5];
	int pause=0;
	int menu=0;
	SDL_Surface *pause_imagem=IMG_Load("Imagens/pause.bmp");
	SDL_Surface *vidas=IMG_Load("Imagens/vidas.png");
	SDL_Rect vida_destino={500,480,0,0};
	
	SDL_Rect gambiarra_origem={0,0,672,480};
	
	fundo=IMG_Load("Imagens/fundo.png");
	Kenny.origem=(SDL_Rect){32,128,32,64};
	Kenny.destino=(SDL_Rect){32,0,0,0};
	Kenny.imagem=IMG_Load("Imagens/kenny.png");
	
	SDL_BlitSurface(fundo,NULL,screen,NULL);
	SDL_BlitSurface(Kenny.imagem,&(Kenny.origem),screen,&(Kenny.destino));
	
	while(!quit)
	{
		tempo_da_fase=SDL_GetTicks()-tempo_total-intervalo_pause;
		FPS=SDL_GetTicks();
		SDL_PumpEvents();
		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				case SDL_QUIT:
					exit(0);
					break;
				case SDL_KEYDOWN:
					switch(event.key.keysym.sym)
					{
						case SDLK_ESCAPE:
							exit(0);
						case SDLK_LEFT:
							direcao='e';
							break;
						case SDLK_RIGHT:
							direcao='d';
							break;
						case SDLK_UP:
							direcao='c';
							break;
						case SDLK_DOWN:
							direcao='b';
							break;
						case SDLK_p:
							if(pause == 0)
                            { 
							    tempo_que_comecou_o_pause=SDL_GetTicks();
							    pause = 1;
                            }
						default:break;
					}
				default: break;
			}
		}
		
		if(pause==1)
		{
			SDL_BlitSurface(pause_imagem,NULL,screen,NULL);
			desenha_texto("Jogo em pausa",screen,180,100,40,0,0,0);
			desenha_texto("Pressione m para voltar",screen,0,200,40,0,0,0);
			desenha_texto("para o menu",screen,180,300,40,0,0,0);
			SDL_Flip(screen);
			menu=pausarJogo(&pause,&event);
			tempo_que_acabou_o_pause=SDL_GetTicks();
			intervalo_pause+=(tempo_que_acabou_o_pause-tempo_que_comecou_o_pause);
		}
		
		if(menu==666)
		{
			return menu;
		}
		
		for(i=0;i<32/velocidade;i++)
		{
			andar(direcao,velocidade,screen);
			SDL_BlitSurface(fundo,&gambiarra_origem,screen,NULL);
			SDL_BlitSurface(Kenny.imagem,&(Kenny.origem),screen,&(Kenny.destino));
			switch(direcao)
			{
				case 'b':
					SDL_UpdateRect(screen,Kenny.destino.x,Kenny.destino.y-velocidade,32,64+velocidade);
					break;
				case 'c':
					SDL_UpdateRect(screen,Kenny.destino.x,Kenny.destino.y+velocidade,32,64+velocidade);
					break;
				case 'e':
					SDL_UpdateRect(screen,Kenny.destino.x+velocidade,Kenny.destino.y,32+velocidade,64);
					break;
				case 'd':
					SDL_UpdateRect(screen,Kenny.destino.x-velocidade,Kenny.destino.y,32+velocidade,64);
					break;
				default: break;
			}
			SDL_PumpEvents();
		}
		direcao='\0';
		
		if(direcao=='\0')
		{
			SDL_BlitSurface(fundo,NULL,screen,NULL);
		}
		SDL_BlitSurface(Kenny.imagem,&(Kenny.origem),screen,&(Kenny.destino));
		tempo_da_fase/=1000;
		
		minutos=tempo_da_fase/60;
		segundos=(tempo_da_fase-minutos*60)%60;

		switch(segundos)
		{
			case 0: segundo[0]='0'; segundo[1]='0';  segundo[2]='\0'; break;
			case 1: segundo[0]='0'; segundo[1]='1';  segundo[2]='\0'; break;
			case 2: segundo[0]='0'; segundo[1]='2';  segundo[2]='\0'; break;
			case 3: segundo[0]='0'; segundo[1]='3';  segundo[2]='\0'; break;
			case 4: segundo[0]='0'; segundo[1]='4';  segundo[2]='\0'; break;
			case 5: segundo[0]='0'; segundo[1]='5';  segundo[2]='\0'; break;
			case 6: segundo[0]='0'; segundo[1]='6';  segundo[2]='\0'; break;
			case 7: segundo[0]='0'; segundo[1]='7';  segundo[2]='\0'; break;
			case 8: segundo[0]='0'; segundo[1]='8';  segundo[2]='\0'; break;
			case 9: segundo[0]='0'; segundo[1]='9';  segundo[2]='\0'; break;
			default:	sprintf(segundo,"%d",segundos); break;
		}	
		sprintf(minuto,"%d",minutos);
		
		desenha_texto(minuto,screen, 50, 480, 30, 255,255,255);
		desenha_texto(":",screen,70, 480,30,255,255,255);
		desenha_texto(segundo,screen,90,480,30,255,255,255);
		
		sprintf(pontos,"%Lu",jogo.pontos);
		
		desenha_texto(pontos,screen,350, 480, 30,255,255,255);
		
		SDL_BlitSurface(vidas,NULL,screen,&vida_destino);
		desenha_texto("x",screen,540,480,30,255,255,255);
		
		sprintf(vidinhas,"%d",jogo.vidas);
		desenha_texto(vidinhas,screen,570,480,30,255,255,255);
		
		if(direcao=='\0')
		{
			SDL_UpdateRect(screen,0,480,screen->w,32);
		}
		
		
		FPS=SDL_GetTicks()-FPS;
		if(FPS<=25)
		{
			SDL_Delay(25-FPS);
		}
		
		SDL_Flip(screen);
	}
	
	return 0;
}
