#include "meuinclude.h"



int menu (SDL_Surface *screen)
{
	SDL_Event event;
	SDL_Surface *fundo;
	SDL_Surface *save;
	SDL_Rect destino_save[5];
	TEXTO texto[6];
	Mix_Chunk *kenny_morreu;
	int quit=0, i, j, FPS,a=0;
	int opcao_menu=0;
	int salvou=0;
	int tocar=0;
	jogo.nome[0]='_';
	jogo.nome[1]='\0';

	save=IMG_Load("Imagens/save.png");

	Mix_AllocateChannels(16);

	destino_save[0]=(SDL_Rect){10,10,save->w,save->h};
	destino_save[1]=(SDL_Rect){20+save->w,10,save->w,save->h};
	destino_save[2]=(SDL_Rect){30+2*(save->w),10,save->w,save->h};
	destino_save[3]=(SDL_Rect){10,20+save->h,save->w,save->h};
	destino_save[4].x =190;
	destino_save[4].y =244;
	destino_save[4].w =170;
	destino_save[4].h =224;
	//(SDL_Rect){20+230,20+save->h,save->w,save->h};

	texto[0].imagem=IMG_Load("Imagens/Frases/novojogo.png");
	texto[0].origem=(SDL_Rect){0,40,texto[0].imagem->w,40};
	texto[0].destino=(SDL_Rect){SCREEN_W-texto[0].imagem->w-10,75,0,0};
	texto[1].imagem=IMG_Load("Imagens/Frases/carregar.png");
	texto[1].origem=(SDL_Rect){0,40,texto[1].imagem->w,40};
	texto[1].destino=(SDL_Rect){SCREEN_W-texto[1].imagem->w-10,150,0,0};
	texto[2].imagem=IMG_Load("Imagens/Frases/recordes.png");
	texto[2].origem=(SDL_Rect){0,40,texto[2].imagem->w,40};
	texto[2].destino=(SDL_Rect){SCREEN_W-texto[2].imagem->w-10,225,0,0};
	texto[3].imagem=IMG_Load("Imagens/Frases/opcoes.png");
	texto[3].origem=(SDL_Rect){0,40,texto[3].imagem->w,40};
	texto[3].destino=(SDL_Rect){SCREEN_W-texto[3].imagem->w-10,300,0,0};
	texto[4].imagem=IMG_Load("Imagens/Frases/sair.png");
	texto[4].origem=(SDL_Rect){0,40,texto[4].imagem->w,40};
	texto[4].destino=(SDL_Rect){SCREEN_W-texto[4].imagem->w-10,375,0,0};
	texto[5].imagem=IMG_Load("Imagens/Frases/voltar.png");
	texto[5].origem=(SDL_Rect){0,40,texto[5].imagem->w,40};
	texto[5].destino=(SDL_Rect){SCREEN_W-texto[5].imagem->w-10,450,0,0};


	fundo=IMG_Load("Imagens/SouthPark.JPG");

	SDL_Init(SDL_INIT_EVERYTHING);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);


	kenny_morreu=Mix_LoadWAV("../Sons/killedkenny.wav");


	screen = SDL_SetVideoMode(SCREEN_W,SCREEN_H,16,SDL_DOUBLEBUF|SDL_SWSURFACE);
	if(TTF_Init() == -1) return -1;
	quit=0;

	while(!quit)
	{
		tocar = 0;
		FPS=SDL_GetTicks();
		SDL_BlitSurface(fundo,NULL,screen,NULL);
		switch(opcao_menu)
		{
			case 0:
				SDL_BlitSurface(texto[0].imagem,&(texto[0].origem),screen,&(texto[0].destino));
				SDL_BlitSurface(texto[1].imagem,&(texto[1].origem),screen,&(texto[1].destino));
				SDL_BlitSurface(texto[2].imagem,&(texto[2].origem),screen,&(texto[2].destino));
				SDL_BlitSurface(texto[3].imagem,&(texto[3].origem),screen,&(texto[3].destino));
				SDL_BlitSurface(texto[4].imagem,&(texto[4].origem),screen,&(texto[4].destino));
				a=0;
				tocar=0;
				break;
			case 1:
				desenha_texto("Digite seu nome:", screen, 100, 50, 30, 255, 0, 0);
				desenha_texto(jogo.nome, screen, 200, 100, 40, 255, 0, 0);
				SDL_BlitSurface(texto[5].imagem,&(texto[5].origem),screen,&(texto[5].destino));
				break;
			case 2:
				for(i=0;i<5;i++)
				{
					SDL_BlitSurface(save,NULL,screen,&destino_save[i]);
				}
				le_Saves(screen);
				SDL_BlitSurface(texto[5].imagem,&(texto[5].origem),screen,&(texto[5].destino));
				break;
			case 3:
				le_recordes(screen);
				SDL_BlitSurface(texto[5].imagem,&(texto[5].origem),screen,&(texto[5].destino));
				break;
			case 17:
				desenha_texto("Escolha um arquivo",screen,30+2*save->w,20+save->h,20, 255, 255, 255);
				desenha_texto("pra salvar",screen,30+2*save->w,40+save->h, 20, 255, 255, 255);
				for(i=0;i<5;i++)
				{
					SDL_BlitSurface(save,NULL,screen,&destino_save[i]);
				}
				le_Saves(screen);
				if(!salvou)
				{
					SDL_BlitSurface(texto[5].imagem,&(texto[5].origem),screen,&(texto[5].destino));
				}
				else
				{
					SDL_Flip(screen);
					SDL_Delay(1500);
					return 278;
				}
			default:
				SDL_BlitSurface(texto[5].imagem,&(texto[5].origem),screen,&(texto[5].destino));
				tocar=1;
				break;
		}
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
						if(opcao_menu==1)
						{
							case SDLK_a:
		                        if(a < 7)
		                        {
									jogo.nome[a] = 'a';
									a++;
									jogo.nome[a] = '_';
									jogo.nome[a+1] = '\0';
		                        }
				                break;
							case SDLK_b:
		                        if(a < 7)
		                        {
									jogo.nome[a] = 'b';
									a++;
									jogo.nome[a] = '_';
									jogo.nome[a+1] = '\0';
		                        }
				                break;
		                    case SDLK_c:
		                        if(a < 7)
		                        {
									jogo.nome[a] = 'c';
									a++;
									jogo.nome[a] = '_';
									jogo.nome[a+1] = '\0';
		                        }
				                break;
						    case SDLK_d:
		                        if(a < 7)
		                        {
									jogo.nome[a] = 'd';
									a++;
									jogo.nome[a] = '_';
									jogo.nome[a+1] = '\0';
		                        }
				                break;
				            case SDLK_e:
		                        if(a < 7)
		                        {
									jogo.nome[a] = 'e';
									a++;
									jogo.nome[a] = '_';
									jogo.nome[a+1] = '\0';
		                        }
				                break;
						    case SDLK_f:
		                        if(a < 7)
		                        {
									jogo.nome[a] = 'f';
									a++;
									jogo.nome[a] = '_';
									jogo.nome[a+1] = '\0';
		                        }
				                break;
				            case SDLK_g:
		                        if(a < 7)
		                        {
									jogo.nome[a] = 'g';
									a++;
									jogo.nome[a] = '_';
									jogo.nome[a+1] = '\0';
		                        }
				                break;
		                    case SDLK_h:
		                        if(a < 7)
		                        {
									jogo.nome[a] = 'h';
									a++;
									jogo.nome[a] = '_';
									jogo.nome[a+1] = '\0';
		                        }
				                break;
		                    case SDLK_i:
		                        if(a < 7)
		                        {
									jogo.nome[a] = 'i';
									a++;
									jogo.nome[a] = '_';
									jogo.nome[a+1] = '\0';
		                        }
				                break;
		                    case SDLK_j:
		                        if(a < 7)
		                        {
									jogo.nome[a] = 'j';
									a++;
									jogo.nome[a] = '_';
									jogo.nome[a+1] = '\0';
		                        }
				                break;
		                    case SDLK_k:
		                        if(a < 7)
		                        {
									jogo.nome[a] = 'k';
									a++;
									jogo.nome[a] = '_';
									jogo.nome[a+1] = '\0';
		                        }
				                break;
		                    case SDLK_l:
		                        if(a < 7)
		                        {
									jogo.nome[a] = 'l';
									a++;
									jogo.nome[a] = '_';
									jogo.nome[a+1] = '\0';
		                        }
				                break;
		                    case SDLK_m:
		                        if(a < 7)
		                        {
									jogo.nome[a] = 'm';
									a++;
									jogo.nome[a] = '_';
									jogo.nome[a+1] = '\0';
		                        }
				                break;
		                    case SDLK_n:
		                        if(a < 7)
		                        {
									jogo.nome[a] = 'n';
									a++;
									jogo.nome[a] = '_';
									jogo.nome[a+1] = '\0';
		                        }
				                break;
		                    case SDLK_o:
		                        if(a < 7)
		                        {
									jogo.nome[a] = 'o';
									a++;
									jogo.nome[a] = '_';
									jogo.nome[a+1] = '\0';
		                        }
				                break;
		                    case SDLK_p:
		                        if(a < 7)
		                        {
									jogo.nome[a] = 'p';
									a++;
									jogo.nome[a] = '_';
									jogo.nome[a+1] = '\0';
		                        }
				                break;
		                    case SDLK_q:
		                        if(a < 7)
		                        {
									jogo.nome[a] = 'q';
									a++;
									jogo.nome[a] = '_';
									jogo.nome[a+1] = '\0';
		                        }
				                break;
		                    case SDLK_r:
		                        if(a < 7)
		                        {
									jogo.nome[a] = 'r';
									a++;
									jogo.nome[a] = '_';
									jogo.nome[a+1] = '\0';
		                        }
				                break;
		                    case SDLK_s:
		                        if(a < 7)
		                        {
									jogo.nome[a] = 's';
									a++;
									jogo.nome[a] = '_';
									jogo.nome[a+1] = '\0';
		                        }
				                break;
		                    case SDLK_t:
		                        if(a < 7)
		                        {
									jogo.nome[a] = 't';
									a++;
									jogo.nome[a] = '_';
									jogo.nome[a+1] = '\0';
		                        }
				                break;
		                    case SDLK_u:
		                        if(a < 7)
		                        {
									jogo.nome[a] = 'u';
									a++;
									jogo.nome[a] = '_';
									jogo.nome[a+1] = '\0';
		                        }
				                break;
		                    case SDLK_v:
		                        if(a < 7)
		                        {
									jogo.nome[a] = 'v';
									a++;
									jogo.nome[a] = '_';
									jogo.nome[a+1] = '\0';
		                        }
				                break;
		                    case SDLK_w:
		                        if(a < 7)
		                        {
									jogo.nome[a] = 'w';
									a++;
									jogo.nome[a] = '_';
									jogo.nome[a+1] = '\0';
		                        }
				                break;
		                    case SDLK_x:
		                        if(a < 7)
		                        {
									jogo.nome[a] = 'x';
									a++;
									jogo.nome[a] = '_';
									jogo.nome[a+1] = '\0';
		                        }
				                break;
		                    case SDLK_y:
		                        if(a < 7)
		                        {
									jogo.nome[a] = 'y';
									a++;
									jogo.nome[a] = '_';
									jogo.nome[a+1] = '\0';
		                        }
				                break;
		                    case SDLK_z:
		                        if(a < 7)
		                        {
									jogo.nome[a] = 'z';
									a++;
									jogo.nome[a] = '_';
									jogo.nome[a+1] = '\0';
		                        }
				                break;
				            case SDLK_SPACE:
				            	if(a<7)
				            	{
				            		jogo.nome[a] = ' ';
				            		a++;
				            		jogo.nome[a] = '_';
				            		jogo.nome[a+1] = '\0';
				            	}
				            	break;
                       		case SDLK_BACKSPACE:
                            	if(opcao_menu==1)
                            	{
		                        	if(a <= 7 && a > 0)
		                        	{
								   		jogo.nome[a] = '\0';
										jogo.nome[a-1] = '_';
		                        	}
		                        	if(a==0)
		                        	{
		                        		opcao_menu=0;
		                        	}
		                        	a--;
		                        }
		                    	break;
		                    case SDLK_RETURN:
		                    	if(a!=0)
		                    	{
		                    	  	jogo.nome[a]='\0';
		                    		opcao_menu=17;
		                    	}
		                    	break;
						}
						case SDLK_ESCAPE:
							switch(opcao_menu)
							{
								case 0:
									exit(0);
									break;
								default:
									opcao_menu=0;
									jogo.nome[0]='_';
									jogo.nome[1]='\0';
									break;
							}

							break;
						default: break;
					}
				case SDL_MOUSEMOTION:
					switch(event.motion.type)
					{
						case SDL_MOUSEMOTION:
							if(!salvou)
							{
								if (opcao_menu==0)
								{
									colore(&texto[0], verificaMouse(texto[0],event.motion.x,event.motion.y));
									colore(&texto[1], verificaMouse(texto[1],event.motion.x,event.motion.y));
									colore(&texto[2], verificaMouse(texto[2],event.motion.x,event.motion.y));
									colore(&texto[3], verificaMouse(texto[3],event.motion.x,event.motion.y));
									colore(&texto[4], verificaMouse(texto[4],event.motion.x,event.motion.y));
									colore(&texto[5],0);
								}
								else
								{
									colore(&texto[0], 0);
									colore(&texto[1], 0);
									colore(&texto[2], 0);
									colore(&texto[3], 0);
									colore(&texto[4], 0);
									colore(&texto[5],verificaMouse(texto[5],event.motion.x,event.motion.y));
								}
							}
							break;
							default:break;
					}
				case SDL_MOUSEBUTTONDOWN:
					switch(event.button.state)
					{
						case SDL_PRESSED:
							for (i = 0; i < 5; i += 1)
							{
								if(verificaMouse(texto[i],event.motion.x,event.motion.y)&&opcao_menu==0)
								{
									opcao_menu=cliqueMouse(texto[i],verificaMouse(texto[i],event.motion.x,event.motion.y),75);
								}
							}
							if(verificaMouse(texto[5],event.motion.x,event.motion.y))
							{
								switch(opcao_menu)
								{
									case 1:
									case 2:
									case 3:
									case 4:
										opcao_menu=0;
										break;
									case 17:
										opcao_menu=0;
										jogo.nome[0]='_';
										jogo.nome[1]='\0';
										break;
									default: break;
								}
							}

							switch(opcao_menu)
							{
								case 5:
									exit(0);
									break;
								case 17:
									salva(slot(event.motion.x,event.motion.y));
									printf("Slot: %d\n\n\n\n",slot(event.motion.x,event.motion.y));
									salvou=1;
									SDL_Delay(200);
									break;
								default:break;
							}
							printf("%d\n",opcao_menu);
							break;
						default: break;
					}
				default: break;
			}
		}

		/*SDL_BlitSurface(fundo,NULL,screen,NULL);
		switch(opcao_menu)
		{
			case 0:
				SDL_BlitSurface(texto[0].imagem,&(texto[0].origem),screen,&(texto[0].destino));
				SDL_BlitSurface(texto[1].imagem,&(texto[1].origem),screen,&(texto[1].destino));
				SDL_BlitSurface(texto[2].imagem,&(texto[2].origem),screen,&(texto[2].destino));
				SDL_BlitSurface(texto[3].imagem,&(texto[3].origem),screen,&(texto[3].destino));
				SDL_BlitSurface(texto[4].imagem,&(texto[4].origem),screen,&(texto[4].destino));
				a=0;
				break;
			case 1:
				desenha_texto("Digite seu nome:", screen, 100, 50, 30, 255, 0, 0);
				desenha_texto(nome, screen, 200, 100, 40, 255, 0, 0);
				SDL_BlitSurface(texto[5].imagem,&(texto[5].origem),screen,&(texto[5].destino));
				break;
			case 2:
				for(i=0;i<5;i++)
				{
					SDL_BlitSurface(save,NULL,screen,&destino_save[i]);
				}
				le_Saves(screen);
				SDL_BlitSurface(texto[5].imagem,&(texto[5].origem),screen,&(texto[5].destino));
				break;
			case 17:
				desenha_texto("Escolha um arquivo",screen,30+2*save->w,20+save->h,20, 255, 255, 255);
				desenha_texto("pra salvar",screen,30+2*save->w,40+save->h, 20, 255, 255, 255);
				for(i=0;i<5;i++)
				{
					SDL_BlitSurface(save,NULL,screen,&destino_save[i]);
				}
				le_Saves(screen);
				if(!salvou)
				{
					SDL_BlitSurface(texto[5].imagem,&(texto[5].origem),screen,&(texto[5].destino));
				}
				else
				{
					SDL_Flip(screen);
					SDL_Delay(1500);
					return 278;
				}
			default:
				SDL_BlitSurface(texto[5].imagem,&(texto[5].origem),screen,&(texto[5].destino));
				break;
		}*/

		/*if(tocar)
		{
			Mix_PlayChannel(-1,kenny_morreu,0);
		}*/

		FPS=SDL_GetTicks()-FPS;
		if(FPS<=20)
		{
			SDL_Delay(20-FPS);
		}
		SDL_Flip(screen);
		SDL_ShowCursor(1);
	}

	Mix_FreeChunk(kenny_morreu);
	return 0;
}
