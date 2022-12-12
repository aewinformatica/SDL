/*
V.A.D. Project - Main
v1.0

Bibliotecas SDL disponíveis em http://www.libsdl.org
Versão usada no desenvolvimento do jogo...
...SDL - 1.2.13.0
...SDL_image - 1.2.6.0
...SDL_mixer - 1.2.8.0

NFont está disponivel em http://pubpages.unh.edu/~jmb97
Versão usada no desenvolvimento do jogo é 1.611
*/

#include "nfontc.c"
#include "Base.c"
#include "Functions.c"

//---------------------------------------------------------------------------------------------

//função principal.
int main(int argc, char** argv)
{
	srand(time(NULL));
	
	int bolasNaTela;
	BOLA *bolas; /*Matriz com todas as bolas do jogo*/
	JOGADOR jogador;
	
	int acabou = 0;
	
	SDL_Event event; //SDL event variable.
	
	int i, j; //Contadores genéricos;
	int carrega = 1; //Carrega as bolas só uma vez.
	int quit = 0; //Variável SDL de saída.
	int mouseX = 0, mouseY = 0; //Armazena a posição atual do mouse.
	int ingame = 0; //Armazena o estado atual de jogo. 0 é menu, 1 é options, 2 é highscores, 3 é credits, e 5 é ingame.
	int difMenu = 1; //Armazena a dificuldade atual. 0 é easy, 1 é medium, e 2 é hard.
	int fase = 0; //Nível atual.
	DIFICULDADE dificuldades = {{3,4,5,7,8,9,10,11,12,13},{4,6,8,10,12,14,16,18,20,22},{6,9,12,15,18,21,24,27,30,33}};
	//Vai armazenar a quantidade de bolas ao iniciar todo nível até o 10. Acima do nível 10 mantém-se o número de bolas.
	int vidasMenu = 3; //Armazena a quantidade de vidas "setadas" no menu. ESTA NÃO É ALTERADA DURANTE O JOGO!
	int tocaMusica = 0; //Armazena o estado atual da música. 0 é não está tocando, 1 é tocando música do menu, e 2 é tocando música do jogo.
	int nivelVolume = 6; //Armazena o nível atual de volume.
	char nome[TAMNOME]="\0"; //Nome do jogador.
	int menorHS; //Armazena o menor highscore gravado

	/*Variáveis carregaBolas*/
	int indice, bolasPaiQtde;
	int cor;
	/*Fim variáveis carregaBolas*/

	Uint32 lasttick = SDL_GetTicks(); //Variáveis para o timer de limite de FPS.
	Uint32 thistick; //Variável para o timer de limite de FPS.
	
	FILE *logfile; //Arquivo log do jogo. Vai armazenar tudo que ocorre durante o jogo, e erros. Vai ser apagado a cada uso do programa.
	FILE *highscores; //Lista de highscores do jogo.
	HIGHSCORE highvetor[NUMJOG]; //Vetor que temporariamente armazena os highscores.
	
	//Declaração de surfaces
		
		SDL_Surface *screen; //Tela geral do jogo.
		SDL_Surface *game; //Tela do in-game.
		SDL_Surface *creditsscr; //Tela de créditos;
		
		SDL_Surface *title; //Imagem do título.
		
		SDL_Surface *start; //Botão "START".
		SDL_Surface *starthov; //Botão "START" flutuada.
		SDL_Surface *options; //Botão "OPTIONS".
		SDL_Surface *optionshov; //Botão "OPTIONS" flutuada.
		SDL_Surface *exitb; //Botão "EXIT".
		SDL_Surface *exitbhov; //Botão "EXIT" flutuada.
		SDL_Surface *butback; //Botão "BACK".
		SDL_Surface *butbackhov; //Botão "BACK" flutuada.
		SDL_Surface *highsurf; //Botão "HIGHSCORE".
		SDL_Surface *highsurfhov; //Botão "HIGHSCORE" flutuada.
		SDL_Surface *credsurf; //Botão "CREDITS".
		SDL_Surface *credsurfhov; //Botão "CREDITS" flutuada.
		
		SDL_Surface *diff; //Imagem "DIFFICULTY".
		SDL_Surface *diffhov; //Imagem flutuada"DIFFICULTY".
		SDL_Surface *livessurf; //Imagem "LIVES".
		SDL_Surface *livessurfhov; //Imagem flutuada "LIVES".
		SDL_Surface *livessurfsma;
		SDL_Surface *easy; //Imagem "EASY".
		SDL_Surface *medium; //Imagem "MEDIUM".
		SDL_Surface *hard; //Imagem "HARD".
		SDL_Surface *volsurf; //Imagem "VOLUME".
		SDL_Surface *volsurfhov; //Imagem flutuada "VOLUME".
		
		SDL_Surface *player; //Nave do jogador.
		SDL_Surface *life; //Ícone de vidas restantes do jogador.
		SDL_Surface *lifesma;
		SDL_Surface *soundbox; //Caixa de som usada para as opções de volume.
		
		/*Bolas surfaces*/
		SDL_Surface *vermelhaPai = IMG_Load("Imgs/RBB.png");
		SDL_Surface *vermelhaFilha = IMG_Load("Imgs/RBM.png");
		SDL_Surface *vermelhaNeta = IMG_Load("Imgs/RBS.png");

		SDL_Surface *azulPai = IMG_Load("Imgs/BBB.png");
		SDL_Surface *azulFilha = IMG_Load("Imgs/BBM.png");
		SDL_Surface *azulNeta = IMG_Load("Imgs/BBS.png");

		SDL_Surface *amarelaPai = IMG_Load("Imgs/YBB.png");
		SDL_Surface *amarelaFilha = IMG_Load("Imgs/YBM.png");
		SDL_Surface *amarelaNeta = IMG_Load("Imgs/YBS.png");

		SDL_Surface *roxaPai = IMG_Load("Imgs/PBB.png");
		SDL_Surface *roxaFilha = IMG_Load("Imgs/PBM.png");
		SDL_Surface *roxaNeta = IMG_Load("Imgs/PBS.png");

		SDL_Surface *verdePai = IMG_Load("Imgs/GBB.png");
		SDL_Surface *verdeFilha = IMG_Load("Imgs/GBM.png");
		SDL_Surface *verdeNeta = IMG_Load("Imgs/GBS.png");

	//Fim surfaces de bolas.
	
	//Fim das declarações de variáveis.
	
	if ((logfile = fopen("log.txt","w")) == NULL) //Abre o arquivo de log.
	{
		fprintf(stderr, "Erro ao inicializar arquivo.");
		exit(1);
	}
	time_t timer = time(NULL);
	fprintf(logfile,"V.A.D. - Arquivo Log iniciado.\n%s\n\n",asctime(localtime(&timer)));
	
	//Área de inicialização SDL.
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER);
	fprintf(logfile,"SDL inicializado com sucesso.\n");
	
	//Ícone da janela.
	SDL_Surface *icone;
	if((icone = IMG_Load("Imgs/Icon.png")) == NULL)
	{
		fprintf(logfile,"!!! - Falha ao carregar arquivo ícone (Icon.png).\n");
	}
	SDL_WM_SetIcon(icone, NULL);
	
	screen = SDL_SetVideoMode(SCREEN_W, SCREEN_H, SCREEN_DEPTH, SDL_SWSURFACE|SDL_DOUBLEBUF);
	fprintf(logfile,"Vídeo inicializado com sucesso.\n");
	
	Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 4096);
	fprintf(logfile,"Áudio inicializado com sucesso.\n");
	
	//Carregando som.
	Mix_Music *menumusic = Mix_LoadMUS("Sounds/Theme1.it");
	if(menumusic == NULL)
	{
		fprintf(logfile,"!!! - Falha ao carregar arquivo de música do menu (Theme1.it).\n");
	}
	Mix_Chunk *somtiro= Mix_LoadWAV("Sounds/Shot.wav");
	if(menumusic == NULL)
	{
		fprintf(logfile,"!!! - Falha ao carregar arquivo de som (Shot.wav).\n");
	}
	Mix_Chunk *somexplo= Mix_LoadWAV("Sounds/Explo.wav");
	if(menumusic == NULL)
	{
		fprintf(logfile,"!!! - Falha ao carregar arquivo de som (Explo.wav).\n");
	}
	Mix_Chunk *somexplo2= Mix_LoadWAV("Sounds/Explo2.wav");
	if(menumusic == NULL)
	{
		fprintf(logfile,"!!! - Falha ao carregar arquivo de som (Explo2.wav).\n");
	}
	//Fim de carregando som.

	//Alocando canais de som
	Mix_AllocateChannels(8);
	
	fprintf(logfile,"Sons carregados.\n");
	
	//Título da janela.
	SDL_WM_SetCaption("VAD Project", NULL);
	
	//Disabilita o cursor para usar outro.
	SDL_ShowCursor(0);
	SDL_Surface *cursor;
	if((cursor=IMG_Load("Imgs/Cursor.png")) == NULL)
		{
			fprintf(logfile,"!!! - Falha ao carregar Cursor.png.\n");
		}
	
	//Carregamento das imagens.
		
		//Esta imagem será convertida por razões de performance.
		if((game = SDL_ConvertSurface(IMG_Load("Imgs/Back.png"),screen->format,SDL_SWSURFACE)) == NULL)
		{
			fprintf(logfile,"!!! - Falha ao carregar Back.png\n");
		}
		
		if((title = IMG_Load("Imgs/Title.png")) == NULL)
		{
			fprintf(logfile,"!!! - Falha ao carregar Title.png\n");
		}
		
		if((creditsscr = IMG_Load("Imgs/CreditsScr.png")) == NULL)
		{
			fprintf(logfile,"!!! - Falha ao carregar CreditsScr.png\n");
		}
		
		if((butback = IMG_Load("Imgs/ButBack.png")) == NULL)
		{
			fprintf(logfile,"!!! - Falha ao carregar ButBack.png\n");
		}
		
		if((butbackhov = IMG_Load("Imgs/ButBackHov.png")) == NULL)
		{
			fprintf(logfile,"!!! - Falha ao carregar ButBackHov.png\n");
		}
		
		if((start = IMG_Load("Imgs/ButStart.png")) == NULL)
		{
			fprintf(logfile,"!!! - Falha ao carregar ButStart.png\n");
		}
		
		if((starthov = IMG_Load("Imgs/ButStartHov.png")) == NULL)
		{
			fprintf(logfile,"!!! - Falha ao carregar ButStartHov.png\n");
		}
		
		if((optionshov = IMG_Load("Imgs/ButOptionsHov.png")) == NULL)
		{
			fprintf(logfile,"!!! - Falha ao carregar ButOptionsHov.png\n");
		}
		
		if((exitbhov = IMG_Load("Imgs/ButExitHov.png")) == NULL)
		{
			fprintf(logfile,"!!! - Falha ao carregar ButExitHov.png\n");
		}
		
		if((options = IMG_Load("Imgs/ButOptions.png")) == NULL)
		{
			fprintf(logfile,"!!! - Falha ao carregar ButOptions.png\n");
		}
		
		if((exitb = IMG_Load("Imgs/ButExit.png")) == NULL)
		{
			fprintf(logfile,"!!! - Falha ao carregar ButExit.png\n");
		}
		
		if((diff = IMG_Load("Imgs/Difficulty.png")) == NULL)
		{
			fprintf(logfile,"!!! - Falha ao carregar Difficulty.png\n");
		}
		
		if((diffhov = IMG_Load("Imgs/DifficultyHov.png")) == NULL)
		{
			fprintf(logfile,"!!! - Falha ao carregar DifficultyHov.png\n");
		}
		
		if((livessurf = IMG_Load("Imgs/Lives.png")) == NULL)
		{
			fprintf(logfile,"!!! - Falha ao carregar Lives.png\n");
		}
		
		if((livessurfhov = IMG_Load("Imgs/LivesHov.png")) == NULL)
		{
			fprintf(logfile,"!!! - Falha ao carregar LivesHov.png failed to load\n");
		}
		
		if((easy = IMG_Load("Imgs/Easy.png")) == NULL)
		{
			fprintf(logfile,"!!! - Falha ao carregar Easy.png\n");
		}
		
		if((medium = IMG_Load("Imgs/Medium.png")) == NULL)
		{
			fprintf(logfile,"!!! - Falha ao carregar Medium.png\n");
		}
		
		if((hard = IMG_Load("Imgs/Hard.png")) == NULL)
		{
			fprintf(logfile,"!!! - Falha ao carregar Hard.png\n");
		}
		
		if((volsurf = IMG_Load("Imgs/Volume.png")) == NULL)
		{
			fprintf(logfile,"!!! - Falha ao carregar Volume.png\n");
		}
		
		if((volsurfhov = IMG_Load("Imgs/VolumeHov.png")) == NULL)
		{
			fprintf(logfile,"!!! - Falha ao carregar VolumeHov.png\n");
		}
		
		if((player = IMG_Load("Imgs/Ship.png")) == NULL)
		{
			fprintf(logfile,"!!! - Falha ao carregar Ship.png\n");
		}
		
		if((life = IMG_Load("Imgs/Life.png")) == NULL)
		{
			fprintf(logfile,"!!! - Falha ao carregar Life.png\n");
		}
		
		if((highsurf = IMG_Load("Imgs/Highscores.png")) == NULL)
		{
			fprintf(logfile,"!!! - Falha ao carregar Highscores.png\n");
		}
		
		if((highsurfhov = IMG_Load("Imgs/HighscoresHov.png")) == NULL)
		{
			fprintf(logfile,"!!! - Falha ao carregar HighscoresHov.png\n");
		}
		
		if((credsurf = IMG_Load("Imgs/Credits.png")) == NULL)
		{
			fprintf(logfile,"!!! - Falha ao carregar Credits.png\n");
		}
		
		if((credsurfhov = IMG_Load("Imgs/CreditsHov.png")) == NULL)
		{
			fprintf(logfile,"!!! - Falha ao carregar CreditsHov.png\n");
		}
		
		if((soundbox = IMG_Load("Imgs/SoundBox.png")) == NULL)
		{
			fprintf(logfile,"!!! - Falha ao carregar SoundBox.png\n");
		}
		
		if((livessurfsma = IMG_Load("Imgs/LivesSma.png")) == NULL)
		{
			fprintf(logfile,"!!! - Falha ao carregar LivesSma.png\n");
		}
		
		if((lifesma = IMG_Load("Imgs/LifeSma.png")) == NULL)
		{
			fprintf(logfile,"!!! - Falha ao carregar LifeSma.png\n");
		}
		
	fprintf(logfile,"Imagens carregadas.\n");
	//Fim do carregamento das imagens.
	
	//Inicialização do NFont.
	NFont *myfont = NF_New(); //NFont, usada para fonte bitmap.
	if(myfont == NULL)
	{
		fprintf(logfile,"!!! - Falha ao inicializar NFont.\n");
	}
	else
	{
		fprintf(logfile,"NFont inicializado com sucesso.\n");
	}
	NF_Push(myfont);
	if((NF_ResetFont(screen, IMG_Load("Imgs/GreenVenus26.png"), 1)) == 0)
	{
		fprintf(logfile,"!!! - Falha ao carregar o arquivo de fonte (GreenVenus26.png).\n");
	}
	
	fprintf(logfile,"Entrando no loop principal do SDL.\n");	
	
	//Loop principal do SDL.
	jogador = carregaJogador();


	//Isto vai carregar o arquivo "highscores.dat", ou criar um novo se ele nao existir.
	if((highscores = fopen("highscores.dat","rb")) == NULL)
	{
		highscores = fopen("highscores.dat","wb");
		for(i = 0; i < NUMJOG; i++)
		{
			sprintf(highvetor[i].nome,"Creator");
			highvetor[i].recorde = 42;
		}
		fwrite(highvetor, sizeof(HIGHSCORE), NUMJOG, highscores);
		
		fprintf(logfile,"Criado arquivo vazio highscores.dat.\n");
		fclose(highscores);
		highscores = fopen("highscores.dat","rb");
	}

	fread(highvetor,sizeof(HIGHSCORE),NUMJOG,highscores);
	fclose(highscores);

	menorHS = highvetor[NUMJOG-1].recorde;

	while(!quit)
	{
		SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format,0,0,0));
		while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT)
			{
				quit = 1; //Isto faz terminar o loop principal do SDL.
				fprintf(logfile,"Comando \"sair\" recebido.\n");
			}
			else if(event.type == SDL_MOUSEMOTION) //Lê o movimento do mouse e o armazena nas variáveis de posição atual do mouse.
			{
				jogador.rect.x = event.motion.x;
				jogador.rect.y = event.motion.y;
				mouseX = event.motion.x;
				mouseY = event.motion.y;
			}
			else if(event.type == SDL_MOUSEBUTTONDOWN)
			{
				if(ingame == 0)
				{
					if((mouseX >= 200) && (mouseX <= 600) && (mouseY >= 250) && (mouseY <= 296)) //Botão start.
					{
						ingame = 5;

						carrega=1;
						fase=0;
						jogador = carregaJogador();
					}
					else if((mouseX >= 200) && (mouseX <= 600) && (mouseY >= 352) && (mouseY <= 398))//Botão exit.
					{
						quit = 1; //Isto faz terminar o loop principal do SDL.
						fprintf(logfile,"Comando \"sair\" recebido.\n");
					}
					else if((mouseX >= 200) && (mouseX <= 600) && (mouseY >= 302) && (mouseY <= 346))//Botão options.
					{
						ingame = 1;
					}
					else if((mouseX >= 100) && (mouseX <= 353) && (mouseY >= 566) && (mouseY <= 600))//Botão highscores.
					{					
						ingame = 2;
					}
					else if((mouseX >= 514) && (mouseX <= 700) && (mouseY >= 566) && (mouseY <= 600)) //Botão credits.
					{
						ingame = 3;
					}
				}
				else if(ingame == 1)
				{
					if((mouseX >= 50) && (mouseX <= 450) && (mouseY >= 200) && (mouseY <= 234)) //Botão difficulty.
					{
						difMenu++;
						if(difMenu == 3)
						{
							difMenu = 0;
						}
					}
					else if((mouseX >= 50) && (mouseX <= 240) && (mouseY >= 280) && (mouseY <= 314)) //Botão lives.
					{
						vidasMenu++;
						if(vidasMenu == 7)
						{
							vidasMenu = 1;
						}
					}
					else if((mouseX >= 50) && (mouseX <= 340) && (mouseY >= 360) && (mouseY <= 384)) //Botão volume.
					{
						nivelVolume++;
						if(nivelVolume > 6)
						{
							nivelVolume = 0;
						}
						Mix_VolumeMusic(arredonda((1.0 * nivelVolume / 6) * MIX_MAX_VOLUME));
						Mix_Volume(-1, arredonda((1.0 * nivelVolume / 6) * MIX_MAX_VOLUME));
					}
					else if((mouseX >= 297) && (mouseX <= 502) && (mouseY >= 450) && (mouseY <= 550)) //Botão back.
					{
						ingame = 0;
					}
				}
				else if(ingame == 2)
				{
					if((mouseX >= 297) && (mouseX <= 502) && (mouseY >= 500) && (mouseY <= 600)) //Botão back.
					{
						fclose(highscores);
						ingame = 0;
					}
				}
				else if(ingame == 3)
				{
					if((mouseX >= 550) && (mouseX <= 755) && (mouseY >= 500) && (mouseY <= 600))//Botão back.
					{
						ingame = 0;
					}
				}
				else if(ingame == 5)
				{
					if (atira(bolas, &jogador, bolasNaTela))
					{
						Mix_PlayChannel(-1, somtiro, 0);
					}
				}
			}
			else if(event.type == SDL_KEYDOWN)
			{
				if(ingame==6)
				{
					i=0;
					while(nome[i]!='\0') i++;
					if(i>=TAMNOME-1) 
					{
						i = TAMNOME-2;
					}
					switch(event.key.keysym.sym)
					{
						case SDLK_a: nome[i]='a'; break;
						case SDLK_b: nome[i]='b'; break;
						case SDLK_c: nome[i]='c'; break;
						case SDLK_d: nome[i]='d'; break;
						case SDLK_e: nome[i]='e'; break;
						case SDLK_f: nome[i]='f'; break;
						case SDLK_g: nome[i]='g'; break;
						case SDLK_h: nome[i]='h'; break;
						case SDLK_i: nome[i]='i'; break;
						case SDLK_j: nome[i]='j'; break;
						case SDLK_k: nome[i]='k'; break;
						case SDLK_l: nome[i]='l'; break;
						case SDLK_m: nome[i]='m'; break;
						case SDLK_n: nome[i]='n'; break;
						case SDLK_o: nome[i]='o'; break;
						case SDLK_p: nome[i]='p'; break;
						case SDLK_q: nome[i]='q'; break;
						case SDLK_r: nome[i]='r'; break;
						case SDLK_s: nome[i]='s'; break;
						case SDLK_t: nome[i]='t'; break;
						case SDLK_u: nome[i]='u'; break;
						case SDLK_v: nome[i]='v'; break;
						case SDLK_w: nome[i]='w'; break;
						case SDLK_x: nome[i]='x'; break;
						case SDLK_y: nome[i]='y'; break;
						case SDLK_z: nome[i]='z'; break;
						case SDLK_BACKSPACE:
							{
								if(i>=TAMNOME-2 && nome[i]!='\0')
								{
									nome[i]='\0'; break;
								}
								else
								{
									nome[i-1]='\0'; break;
								}
							}
						case SDLK_RETURN: 
						{
							ingame=2; 
								
							sprintf(highvetor[9].nome,nome);
							highvetor[9].recorde = jogador.pontos;

							highOrdena(highvetor);

							fopen("highscores.dat","wb");	
							fwrite(highvetor,sizeof(HIGHSCORE),NUMJOG,highscores);
							fclose(highscores);

					
							break;
						}
							nome[i+1]='\0';
					}
				}
				else if (ingame == 5)
				{
					if(event.key.keysym.sym == SDLK_ESCAPE)
					{
						jogador.vidas=0; //Sai do jogo.
					}
				}
			}
		}
		
		//Isto irá reduzir o uso de CPU se o jogo ficar fora de foco.
		if(((SDL_GetAppState() == SDL_APPACTIVE) || (!SDL_GetAppState())))
		{
			SDL_Delay(250);
		}
		
		//Música
		if(!tocaMusica)
		{
			Mix_PlayMusic(menumusic, -1);
			tocaMusica = 1;
		}
		
		//---------------------------------------------------------------------------------------------
		//A verdadeira ação começa aqui.
		//---------------------------------------------------------------------------------------------
		
		//MENU PRINCIPAL.
		if(ingame == 0)
		{
			Blit(game,screen,0,0); //background
			Blit(title,screen,80,0); //Título do menu, na borda superior esquerda da tela.
			Blit(start,screen,200,250); //Botão start.
			Blit(options,screen,200,302); //Botão options.
			Blit(exitb,screen,200,352); //Botão exit.
			Blit(highsurf,screen,100,566); //Botão highscore.
			Blit(credsurf,screen,514,566); //Botão credits.
			
			//Parte flutuada.
			if((mouseX >= 200) && (mouseX <= 600) && (mouseY >= 250) && (mouseY <= 296)) //Botão start flutuado.
			{
				Blit(starthov,screen,200,250);
			}
			else if((mouseX >= 200) && (mouseX <= 600) && (mouseY >= 302) && (mouseY <= 346)) //Botão options flutuado.
			{
				Blit(optionshov,screen,200,302);
			}
			else if((mouseX >= 200) && (mouseX <= 600) && (mouseY >= 352) && (mouseY <= 398)) //Botão exit flutuado.
			{
				Blit(exitbhov,screen,200,352);
			}
			else if((mouseX >= 100) && (mouseX <= 353) && (mouseY >= 566) && (mouseY <= 600)) //Botão highscore flutuado.
			{
			Blit(highsurfhov,screen,100,566);
			}
				else if((mouseX >= 514) && (mouseX <= 700) && (mouseY >= 566) && (mouseY <= 600)) //Botão credits flutuado.
			{
			Blit(credsurfhov,screen,514,566);
			}
		}
		
		//---------------------------------------------------------------------------------------------
		
		//MENU OPÇÕES.
		else if(ingame == 1)
		{
			Blit(game, screen, 0, 0); //background.
			Blit(title, screen, 80, 0); //Título do menu, na borda superior esquerda da tela.
			Blit(diff, screen, 50, 200); //Imagem "DIFFICULTY".
			
			if(difMenu == 0) //easy
			{
				Blit(easy, screen, 480, 200); //Imagem "EASY".
			}
			else if(difMenu == 1) //medium
			{
				Blit(medium, screen, 480, 200); //Imagem "MEDIUM".
			}
			else //hard
			{
				Blit(hard, screen, 480, 200); //Imagem "HARD".
			}
			
			Blit(livessurf, screen, 50, 280); //Imagem "LIVES".
			
			//Esta parte é para desenhar as vidas usando o ícone "life".
			j = 270;
			for(i = 0; i < vidasMenu; i++)
			{
				Blit(life, screen, j, 280); //Imagem "LIFE".
				j += 45;
			}
			
			Blit(volsurf, screen, 50, 360); //Imagem "VOLUME".
			
			//Esta parte é para desenhar o volume usando o ícone "soundbox".
			j = 370;
			for(i = 0; i < nivelVolume; i++)
			{
				Blit(soundbox, screen, j, 360); //Imagem "SOUNDBOX".
				j += 30;
			}
			
			Blit(butback, screen, 297, 450); //Botão back.
			
			//Parte flutuada.
			if((mouseX >= 50) && (mouseX <= 450) && (mouseY >= 200) && (mouseY <= 234)) //Botão DIFFICULTY flutuado.
			{
				Blit(diffhov, screen, 50, 200);
			}
			else if((mouseX >= 50) && (mouseX <= 240) && (mouseY >= 280) && (mouseY <= 314)) //Botão LIVES flutuado.
			{
				Blit(livessurfhov, screen, 50, 280);
			}
			else if((mouseX >= 50) && (mouseX <= 340) && (mouseY >= 360) && (mouseY <= 384)) //Botão VOLUME flutuado.
			{
				Blit(volsurfhov, screen, 50, 360);
			}
			else if((mouseX >= 297) && (mouseX <= 502) && (mouseY >= 450) && (mouseY <= 550)) //Botão BACK flutuado
			{
				Blit(butbackhov, screen, 297, 450);
			}
		}
		
		//---------------------------------------------------------------------------------------------
		
		//HIGHSCORES.
		else if(ingame == 2)
		{		
			Blit(game, screen, 0, 0); //background.
			j = 20;
			for(i = 0; i < NUMJOG; i++)
			{
				NF_Draw(50, j, "%s", highvetor[i].nome);
				j += 50;
			}
			j = 20;
			for(i = 0; i < NUMJOG; i++)
			{
				NF_Draw(600, j, "%d", highvetor[i].recorde);
				j += 50;
			}
			Blit(butback, screen, 297, 500); //Botão back.
			if((mouseX >= 297) && (mouseX <= 502) && (mouseY >= 500) && (mouseY <= 600)) //Botão back flutuado.
			{
				Blit(butbackhov, screen, 297, 500);
			}
		}
		
		//---------------------------------------------------------------------------------------------
		
		//CREDITS.
		else if(ingame == 3)
		{
			Blit(game, screen, 0, 0); //background
			Blit(creditsscr, screen, 0, 0); //Credits
			Blit(butback, screen, 550, 500); //Botão back.
			if((mouseX >= 550) && (mouseX <= 755) && (mouseY >= 500) && (mouseY <= 600)) //Botão back flutuado.
			{
				Blit(butbackhov, screen, 550, 500);
			}
		}
		
		//---------------------------------------------------------------------------------------------
		
		//IN-GAME.
		else if(ingame == 5)
		{
			if(carrega)
			{
				if(fase==0) jogador.vidas = vidasMenu;
				/*CarregaBolas*/
				if(difMenu == 0)
				{
					bolasNaTela = 7 * dificuldades.easy[fase] + 1;
				}
				else if(difMenu == 1)
				{
					bolasNaTela = 7 * dificuldades.medium[fase] + 1;
				}
				else
				{
					bolasNaTela = 7 * dificuldades.hard[fase] + 1;	
				}
				
				//Cria as bolas grandes.
				bolas = (BOLA*) malloc(bolasNaTela * sizeof(BOLA));

				bolasPaiQtde = (bolasNaTela - 1) / 7;
				indice = 0;
				
				for(i = 0; i < bolasPaiQtde; i++)
				{
					cor = rand() % 5;
					switch(cor)
					{
						case 0:
						{
							indice = alteraBolas(bolas, novoGrupoBolas(roxaPai,roxaFilha,roxaNeta), indice);	
							break;
						}
						case 1:
						{
							indice = alteraBolas(bolas, novoGrupoBolas(azulPai,azulFilha,azulNeta), indice);		
							break;
						}
						case 2:
						{
							indice = alteraBolas(bolas, novoGrupoBolas(verdePai,verdeFilha,verdeNeta), indice);		
							break;
						}
						case 3:
						{
							indice = alteraBolas(bolas, novoGrupoBolas(amarelaPai,amarelaFilha,amarelaNeta), indice);		
							break;
						}
						case 4:
						{
							indice = alteraBolas(bolas, novoGrupoBolas(vermelhaPai,vermelhaFilha,vermelhaNeta), indice);		
							break;
						}
					}
				}
				indice = alteraBolas(bolas, novaBola(20, 20, 1, 3, 0, 1, roxaNeta),indice);
				organizaBolas(bolas, &jogador, bolasNaTela);
				/*Fim CarregaBolas*/
				
				SDL_AddTimer(2000, toogleEstado, &jogador);
				carrega = 0;
			}
			
			if(jogador.vidas == 0)
			{
				ingame = 6;
			}
			
			Blit(game, screen, 0, 0); //background
			atualizaTela(bolas, bolasNaTela, &jogador, screen, somexplo,somexplo2);

			NF_Draw(640, 20,"%s", "SCORE:");

			Blit(livessurfsma, screen, 20, 20); //"LIVES" image.
			
			//Esta parte é para desenhar as vidas usando o ícone "life".
			j = 140;
			for(i = 0; i < jogador.vidas; i++)
			{
				Blit(lifesma, screen, j, 20); //Imagem Life.
				j += 25;
			}
			
			if(fase<9)
			{
				NF_Draw(20, 560,"Level %d", fase+1);
			}
			else
			{
				NF_Draw(20, 560,"Level 10++");
			}
			
			if(jogador.bolasDestruidas == (bolasNaTela-1) - 4 * ((bolasNaTela-1) / 7))
			{
					if(fase == 9)
					{
						fase = 8;
					}
					
					jogador.estado = 1;
					
					jogador.bolasDestruidas = 0;
					carrega = 1;
					fase++;
			}
		}
		//ENTRAR NOME
		else if (ingame==6)
		{
			if(jogador.pontos>menorHS)
			{
				Blit(game, screen, 0, 0); //background
				NF_Draw(20,20,"Game Over\nEnter your name...");
				NF_Draw(20,100,"%s",nome);
			}
			else
			{
				ingame = 0;
			}
		}
		
		//---------------------------------------------------------------------------------------------
		
		//Desenhando o cursor.
		if(ingame != 5)
		{
			Blit(cursor, screen, mouseX, mouseY);
		}
		
		//Limitador de FPS. Os movimentos do jogo ficarão mais devagar se o CPU não conseguir acompanhar.
		thistick = SDL_GetTicks();
		if((thistick - lasttick) < FPS_MAX)
		{
			SDL_Delay(FPS_MAX - (thistick - lasttick));
		}
		
		//Atualiza tela.
		SDL_Flip(screen);
		lasttick = SDL_GetTicks();
		//---------------------------------------------------------------------------------------------
		//Ação acaba aqui.
		//---------------------------------------------------------------------------------------------
	}
	//Fim do loop principal do SDL.
	
	NF_Free(myfont);
	Mix_CloseAudio(); //Fechando áudio.
	SDL_Quit(); //Termina SDL.
	
	timer = time(NULL);
	fprintf(logfile, "SDL finalizado.\n\nLog fechado.\n%s", asctime(localtime(&timer)));
	fclose(logfile); //Arquivo log fechado.
	
	return 0;
}
//Fim da função principal. Tenha certeza que há uma linha em branco abaixo.

//---------------------------------------------------------------------------------------------

//tenha certeza que há uma linha em branco abaixo.
