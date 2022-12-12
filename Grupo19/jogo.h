int jogo(int estado)
{
	int menu(int m);
	int timerbomb=-1;
	screen = SDL_SetVideoMode(SCREEN_W, SCREEN_H, 16, SDL_SWSURFACE); //criando a janela
	SDL_Event event;
	FILE *pgrade ;
	int i,j,stop = 0, m=0;
	char passo;
	int grade[DIM][MAX];
	int botei_bomba=0, vidas=3,devagar=50000;
	srand(time(NULL));


	hello = IMG_Load("img/hello1.gif");
	bomba = IMG_Load("img/bomba.gif");
	tile = IMG_Load("img/tile.gif");
	quad =	IMG_Load("img/quadrado.gif");
	quad2 =	IMG_Load("img/quadrado2.gif");
	vidas3 = IMG_Load("img/vidas3.gif");
	vidas2 = IMG_Load("img/vidas2.gif");
	vidas1 = IMG_Load("img/vidas1.gif");
	vidas0 = IMG_Load("img/vidas0.gif");
	me = IMG_Load("img/me.gif");
	nu = IMG_Load("img/nu.gif");
	door = IMG_Load("img/flor.gif");
	choco= IMG_Load("img/choco.bmp");



	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO); /*Inicializando SDL video e audio*/

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096); //inicializar SDL_mixer
	Mix_AllocateChannels(16);
	bombsnd = Mix_LoadWAV("explode.wav");
	Mix_VolumeChunk(bombsnd, 10);
	music = Mix_LoadMUS("nightmare.mid");

	pgrade=fopen("./grade.txt","r");

	if (!pgrade)return 1;

	for (i=0;i<DIM ;i++ )
	{
		for (j=0;j<MAX ;j++ )
		{
			fscanf(pgrade,"%d", &grade[i][j]);
		}
	}

	fclose(pgrade);

	escondendo(grade);


	//tocar a musica
	Mix_PlayMusic(music, -1);


	while (!stop)
	{
		while(SDL_PollEvent(&event)) //checar eventos
		{
         	if (  ( event.motion.x >= dst_me.x ) //Se o mouse esta em cima menu
            	&& ( event.motion.x <= ( dst_me.x + dst_me.w ) )
            	&& ( event.motion.y >= ( dst_me.y ) )
           		&& ( event.motion.y <= ( dst_me.y + dst_me.h ) ) )
         	{

            	if ( event.type == SDL_MOUSEBUTTONDOWN )
            	{
               		if ( event.button.button == SDL_BUTTON_LEFT )//Se o botao eh pressionado
               		{
               		   m=1;
               		}
        			else m = 0;
           		 }
         	}

         	if (  ( event.motion.x >= dst_nu.x)	//Se o mouse esta em cima menu
            	&& ( event.motion.x <= ( dst_nu.x + dst_nu.w ) )
            	&& ( event.motion.y >= ( dst_nu.y ) )
           		&& ( event.motion.y <= ( dst_nu.y + dst_nu.h ) ) )
         	{

            	if ( event.type == SDL_MOUSEBUTTONDOWN )
            	{
               		if ( event.button.button == SDL_BUTTON_LEFT )//Se o botao eh pressionado
               		{
               		   m=1;
               		}
        			else m = 0;
           		 }
         	}


			switch(event.type)
			{
				case SDL_QUIT: stop = 1; break;//sair do loop principal

				case SDL_KEYDOWN:
					switch(event.key.keysym.sym)
					{
						case SDLK_UP:
							 passo='h';
							 break;
						case SDLK_DOWN:
							 passo='e';
						     break;
						case SDLK_LEFT:
							 passo='l';
						     break;
						case SDLK_RIGHT:
							 passo='o';
							break;
						case SDLK_SPACE:
							if(botei_bomba==0)
							{
							 	timerbomb = bombando();
							 	botei_bomba=1;
							}

							break;

						case SDLK_ESCAPE: stop = 1; break;

						default: break;
					}
					break;
				case SDL_KEYUP:
					switch(event.key.keysym.sym)
					{
							case SDLK_UP:
								passo = 'k';
								break;
							case SDLK_DOWN:
								 passo = 'k';
								break;
							case SDLK_LEFT:
								 passo = 'k';
								break;
							case SDLK_RIGHT:
								 passo = 'k';
								break;
							default:
								break;
					}
					break;
				default: break;
			}
		}




		SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 238, 221, 130));
		dst_door.x=b*50;
		dst_door.y=a*50;
		SDL_BlitSurface(door ,NULL, screen , &dst_door);
		Labirinto(grade , quad, screen, vidas);
		hello_andando(&passo,grade, hello);
		if(devagar%50==0)
        {

            andachoco(&dst_choco,grade);
            andachoco(&dst_choco1,grade);
            andachoco(&dst_choco2,grade);
            devagar++;
        }
        else
        {
            devagar++;
        }

		
		vidas=mata_hello(&dst_choco,vidas);
		vidas=mata_hello(&dst_choco1,vidas);
		vidas=mata_hello(&dst_choco2,vidas);
		if (vidas<0)
		{
			gameover(vidas);
			exit(0);
		}

		

		
 

		if(botei_bomba==1)
		{
			SDL_BlitSurface(bomba, NULL, screen, &dst_bomba);
		}

		SDL_BlitSurface(quad, NULL, screen, &dst_quad);
		SDL_BlitSurface(quad2, NULL, screen, &dst_quad2);
		SDL_BlitSurface(tile, NULL, screen, &dst_tile);
		SDL_BlitSurface(hello, NULL, screen, &dst_hello);
		SDL_BlitSurface(choco ,NULL, screen , &dst_choco);
		SDL_BlitSurface(choco ,NULL, screen , &dst_choco1);
		SDL_BlitSurface(choco ,NULL, screen , &dst_choco2);


		if ((SDL_GetTicks() >= timerbomb+3000)&& (botei_bomba==1))
		{
			explode(grade);
			Mix_PlayChannel(-1, bombsnd, 0);
			mata_choco(&dst_choco,grade);
			mata_choco(&dst_choco1,grade);
			mata_choco(&dst_choco2,grade);
			vidas = morrendo(vidas);

			if (vidas<0)
			{
				Mix_FreeMusic(music);
				Mix_CloseAudio();
				gameover(vidas);
				exit(0);
			}
		}
		if ((SDL_GetTicks() >= timerbomb+4000)&& (botei_bomba==1))
		{
			botei_bomba=0;
		}
		if (m==1)
		{
			Mix_FreeMusic(music);
			Mix_CloseAudio();
			menu(m);
			exit(0);
		}

		if (dst_hello.x==b*50 && dst_hello.y==a*50)
		{
				Mix_FreeMusic(music);
				Mix_CloseAudio();
				achou(grade);
				exit(0);
		}

		SDL_Flip(screen);/*Para atualizar a tela*/

	}

	Mix_FreeMusic(music);
	Mix_FreeChunk(bombsnd);

	Mix_CloseAudio();

	SDL_Quit(); //encerrar a SDL
	exit(0);
}
