void inst(int b2state)
{
	int jogo(int estado);
	SDL_Init(SDL_INIT_VIDEO); /*Inicializando SDL video*/
	screen = SDL_SetVideoMode(SCREEN_W, SCREEN_H, 16, SDL_SWSURFACE); //criando a janela
	SDL_Event event;
	SDL_Surface* inst;
	SDL_Rect dst_inst={0,0,0,0};
	SDL_Surface* jogar;
	SDL_Rect dst_jogar={550,500,0,0};
	int stop =0, est;
	inst = IMG_Load("img/inst.gif");
	jogar = IMG_Load("img/jogar.gif");

	while (!stop)
	{
		while(SDL_PollEvent(&event)) //checar eventos
		{
				//Se o mouse esta em cima do botao
				if (  ( event.motion.x >= dst_b1.x )
						&& ( event.motion.x <= ( dst_jogar.x + dst_jogar.w ) )
						&& ( event.motion.y >= ( dst_jogar.y ) )
						&& ( event.motion.y <= ( dst_jogar.y + dst_jogar.h ) ) )
				{
					//Mudar estado
					est = 1;

					if ( event.type == SDL_MOUSEBUTTONDOWN )
					{
						//Se o botao eh pressionado
						if ( event.button.button == SDL_BUTTON_LEFT )
						{
							//Mudar estado
							est = 2;
						}
					}
				}

				//Senao nada muda
				else est = 0;

			switch(event.type)
			{
				case SDL_QUIT: stop = 1; break;//sair do loop principal
				default: break;
			}
		}
		SDL_BlitSurface(inst, NULL, screen, &dst_inst);
		SDL_BlitSurface(jogar, NULL, screen, &dst_jogar);

		if (est == 2)
		{
			jogo(est);
		}

		SDL_Flip(screen);/*Para atualizar a tela*/
	}
	SDL_Quit(); //encerrar a SDL
	exit(0);
}

void intro ()
{
	int menu(int m);
	SDL_Init(SDL_INIT_VIDEO); /*Inicializando SDL video*/
	screen = SDL_SetVideoMode(SCREEN_W, SCREEN_H, 16, SDL_SWSURFACE); //criando a janela
	SDL_Event event;
	SDL_Surface* introd;
	SDL_Rect dst_introd={0,0,0,0};
	SDL_Surface* manual;
	SDL_Rect dst_manual={0,0,0,0};
	int stop =0, tempo, i=1;
	introd = IMG_Load("img/intro.jpg");
	manual = IMG_Load("img/manual.jpg");
	while (!stop)
	{
		while(SDL_PollEvent(&event)) //checar eventos
		{
			switch(event.type)
			{
				case SDL_QUIT: stop = 1; break;//sair do loop principal
				default: break;
			}
		}
		SDL_BlitSurface(introd, NULL, screen, &dst_introd);
		while(i!=0)
		{
			tempo=SDL_GetTicks();
			i=0;
		}
		if (SDL_GetTicks() > tempo+2000)
		{
			SDL_BlitSurface(manual, NULL, screen, &dst_manual);
			while(SDL_PollEvent(&event)) //checar eventos
			{
				switch(event.type)
				{
					case SDL_KEYDOWN:        //caso aperte espaço chamar menu
						if(event.key.keysym.sym == SDLK_SPACE)
						{
							menu(1);
							exit(0);
						}
						break;
					case SDL_QUIT: stop = 1; break;//sair do loop principal
					default: break;
				}
			}
		}

		SDL_Flip(screen);/*Para atualizar a tela*/
	}
	SDL_Quit(); //encerrar a SDL
	exit(0);
}

