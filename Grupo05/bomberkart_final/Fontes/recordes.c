#include "include.h"

void organizarecorde(char nome[],int j,FILE *p,int pontos);

typedef struct _RECORDE
{
	char nome[14];
	int pontos;
}RECORDE;

int salvarecorde(SDL_Surface* screen,int pontos)
{

	TTF_Init();
		TTF_Font* fonte;
		TTF_Font* fonte2;
	
		fonte = TTF_OpenFont("./fonte/baabookhmkbold.ttf",36);
		fonte2 = TTF_OpenFont("./fonte/baabookhmkbold.ttf",50);
		char lixo[12];
		char reco[11];
		int rec,i,quit=0,j;
		char nome[14]="............\n";
		SDL_Surface* caixa;
		SDL_Color cor = {0,0,0};//preto
		SDL_Color cor2 = {255,3,10};//preto
		SDL_Surface* texto;
		SDL_Surface* texto2;
		SDL_Rect dst_texto = {169,332,0,0};
		SDL_Rect dst_caixa = {137,163, 0, 0};
		SDL_Rect dst_gover = {213,242,0,0};
		SDL_Event event;

				
		FILE *p;
		char *n="./matrizes/recordes.txt";
		p=fopen(n,"r+");
		fseek(p,(10*12*sizeof(char))+20,SEEK_SET);
		
		SDL_Flip(screen);
		caixa = SDL_LoadBMP("./imgs/caixa.bmp");
		if (!caixa) return 2;
		while (!quit)
		{
			while(SDL_PollEvent(&event)) //checar eventos
			{

				switch(event.type)
				{
					case SDL_QUIT://sair do loop principal
					quit=1;
					return 1;
					break;
				}
			}
			
			for (j=0;j<10;j++)
			{
				fgets(reco,11,p);
				reco[9]='\0';
				rec=atoi(reco);
				if (pontos>rec)
				{
					SDL_BlitSurface(caixa,NULL, screen,&dst_caixa);
					SDL_Flip(screen);
			
					for (i=0;i<12;i++)
					{
						
						while(SDL_PollEvent(&event))
						{
							switch(event.type)
							{
								case SDL_QUIT://sair do loop principal
								quit=1;
								return 0;
								break;

								case SDL_KEYDOWN:
									switch(event.key.keysym.sym)
									{
										case SDLK_a:
											nome[i]='a';
											break;
										case SDLK_b:
											nome[i]='b';
											break;
										case SDLK_c:
											nome[i]='c';
											break;
										case SDLK_d:
											nome[i]='d';
											break;
										case SDLK_e:
											nome[i]='e';
											break;
										case SDLK_f:
											nome[i]='f';
											break;
										case SDLK_g:
											nome[i]='g';
											break;
										case SDLK_h:
											nome[i]='h';
											break;
										case SDLK_i:
											nome[i]='i';
											break;
										case SDLK_j:
											nome[i]='j';
											break;
										case SDLK_k:
											nome[i]='k';
											break;
										case SDLK_l:
											nome[i]='l';
											break;
										case SDLK_m:
											nome[i]='m';
											break;
										case SDLK_n:
											nome[i]='n';
											break;
										case SDLK_o:
											nome[i]='o';
											break;
										case SDLK_p:
											nome[i]='p';
											break;
										case SDLK_q:
											nome[i]='q';
											break;
										case SDLK_r:
											nome[i]='r';
											break;
										case SDLK_s:
											nome[i]='s';
											break;
										case SDLK_t:
											nome[i]='t';
											break;
										case SDLK_u:
											nome[i]='u';
											break;
										case SDLK_v:
											nome[i]='v';
											break;
										case SDLK_w:
											nome[i]='w';
											break;
										case SDLK_x:
											nome[i]='x';
											break;
										case SDLK_y:
											nome[i]='y';
											break;
										case SDLK_z:
											nome[i]='z';
											break;
										case SDLK_BACKSPACE:
											if (i==0)
											{
												break;
											}
											nome[i-1]='.';
											i-=2;
											break;
										case SDLK_RETURN:
											nome[i]=' ';
											i=11;
											organizarecorde(nome,j,p,pontos);
											fclose(p);
											return 1;
										case SDLK_SPACE:
											nome[i]=' ';
											break;
										default:
											break;
									}
									break;
								}						
							}
							texto = TTF_RenderText_Blended(fonte,nome,cor);
							SDL_BlitSurface(caixa,NULL, screen,&dst_caixa);
							SDL_BlitSurface(texto,NULL,screen,&dst_texto);
							SDL_FreeSurface(texto);
							SDL_Flip(screen);
							if (nome[i]=='.')
							{
								i--;
							}
							if (i==11)
							{
								quit=0;
								while (!quit)
								{
									while(SDL_PollEvent(&event))
									{
										switch(event.type)
										{
											case SDL_KEYDOWN:
												switch(event.key.keysym.sym)
												{
													case SDLK_RETURN:
														organizarecorde(nome,j,p,pontos);
														fclose(p);
														return 1;
													default:
														break;
												}
										}
									}
								}
								
							}
						}
						j=10;
				}
					
			}
			texto2 = TTF_RenderText_Blended(fonte2,"Game Over",cor2);
			SDL_BlitSurface(texto2,NULL,screen,&dst_gover);
			SDL_FreeSurface(texto2);
			SDL_Flip(screen);
			SDL_Delay(4000);
			return 0;
		
		}
		
		TTF_Quit();
		fclose(p);
		SDL_Flip(screen);
	
    SDL_Quit();
	

	return 0;
}

void organizarecorde(char nome[],int j,FILE *p,int pontos)
{
	int h,i;
	RECORDE recorde[10],alvo,temp;
	rewind(p);
	for (h=0;h<14;h++)
	{
		alvo.nome[h]=nome[h];
	}
	alvo.pontos=pontos;
	for (i=0;i<10;i++)
	{
			fgets(recorde[i].nome,14,p);
	}
	for (i=0;i<10;i++)
	{
			fscanf(p,"%d",&recorde[i].pontos);
	}
	for (i=0;i<10-j;i++)
	{
		for (h=0;h<14;h++)
		{
			temp.nome[h]=recorde[j+i].nome[h];
		}
		temp.pontos=recorde[j+i].pontos;
		for (h=0;h<14;h++)
		{
			recorde[j+i].nome[h]=alvo.nome[h];
		}
		recorde[j+i].pontos=alvo.pontos;
		for (h=0;h<14;h++)
		{
			alvo.nome[h]=temp.nome[h];
		}
		alvo.pontos=temp.pontos;
	}
	rewind(p);
	for (i=0;i<10;i++)
	{
			fputs(recorde[i].nome,p);
	}
	for (i=0;i<10;i++)
	{
			fprintf(p,"%09d\n",recorde[i].pontos);
	}

}
