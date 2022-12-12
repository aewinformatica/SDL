int menu(int m)
{
	int jogo(int estado);
	void inst(int b2state);
	//menu
	menubg = IMG_Load("img/menubg.gif");

	//botoes
	b1 = IMG_Load("img/b1.gif");
	b2 = IMG_Load("img/b2.gif");
	b3 = IMG_Load("img/b3.gif");

	//botoes selecionados
	b1u = IMG_Load("img/b1u.gif");
	b2u = IMG_Load("img/b2u.gif");
	b3u = IMG_Load("img/b3u.gif");

	//botoes pressionados
	b1p = IMG_Load("img/b1p.gif");
	b2p = IMG_Load("img/b2p.gif");
	b3p = IMG_Load("img/b3p.gif");



	SDL_Init(SDL_INIT_VIDEO); /*Inicializando SDL video*/
	screen = SDL_SetVideoMode(SCREEN_W, SCREEN_H, 16, SDL_SWSURFACE); //criando a janela
	SDL_WM_SetCaption("BomberKitty * Amigas 4ever LTDA", "BomberKitty");

	SDL_Event event;

	int stop = 0;

	while (!stop)
	{
		while(SDL_PollEvent(&event)) //checar eventos
		{

		 //Se o mouse esta em cima do botao 1
         if (  ( event.motion.x >= dst_b1.x )
            && ( event.motion.x <= ( dst_b1.x + dst_b1.w ) )
            && ( event.motion.y >= ( dst_b1.y ) )
            && ( event.motion.y <= ( dst_b1.y + dst_b1.h ) ) )
         {
            //Mudar estado
            b1state = 1;

            if ( event.type == SDL_MOUSEBUTTONDOWN )
            {
               //Se o botao eh pressionado
               if ( event.button.button == SDL_BUTTON_LEFT )
               {
                  //Mudar estado
                  b1state = 2;
               }
            }
         }

         //Senao nada muda
         else b1state = 0;

		 //Se o mouse esta em cima do botao 2
         if (  ( event.motion.x >= dst_b2.x )
            && ( event.motion.x <= ( dst_b2.x + dst_b2.w ) )
            && ( event.motion.y >= ( dst_b2.y ) )
            && ( event.motion.y <= ( dst_b2.y + dst_b2.h ) ) )
         {
            //Mudar estado
            b2state = 1;

            if ( event.type == SDL_MOUSEBUTTONDOWN )
            {
               //Se o botao eh pressionado
               if ( event.button.button == SDL_BUTTON_LEFT )
               {
                  //Mudar estado
                  b2state = 2;
               }
            }
         }

         //Senao nada muda
         else b2state = 0;

		 //Se o mouse esta em cima do botao 3
         if (  ( event.motion.x >= dst_b3.x )
            && ( event.motion.x <= ( dst_b3.x + dst_b3.w ) )
            && ( event.motion.y >= ( dst_b3.y ) )
            && ( event.motion.y <= ( dst_b3.y + dst_b3.h ) ) )
         {
            //Mudar estado
            b3state = 1;

            if ( event.type == SDL_MOUSEBUTTONDOWN )
            {
               //Se o botao eh pressionado
               if ( event.button.button == SDL_BUTTON_LEFT )
               {
                  //Mudar estado
                  b3state = 2;
               }
            }
         }

         //Senao nada muda
         else b3state = 0;


			switch(event.type)
			{
				case SDL_QUIT: stop = 1; break;//sair do loop principal
				default: break;
			}

		}

		SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 238, 221, 130));


		SDL_BlitSurface(menubg, NULL, screen, &dst_menubg);

         //Blitando os botoes baseado em seu estado
         if (b1state == 0)
            SDL_BlitSurface (b1, 0, screen, &dst_b1);
         else if (b1state == 1)
            SDL_BlitSurface (b1u, 0, screen, &dst_b1);
         else if (b1state == 2)
         {
            SDL_BlitSurface (b1p, 0, screen, &dst_b1);
            jogo(b1state);
		 }

         if (b2state == 0)
            SDL_BlitSurface (b2, 0, screen, &dst_b2);
         else if (b2state == 1)
            SDL_BlitSurface (b2u, 0, screen, &dst_b2);
         else if (b2state == 2)
         {
            SDL_BlitSurface (b2p, 0, screen, &dst_b2);
			inst(b2state);
		 }

         if (b3state == 0)
            SDL_BlitSurface (b3, 0, screen, &dst_b3);
         else if (b3state == 1)
            SDL_BlitSurface (b3u, 0, screen, &dst_b3);
         else if (b3state == 2)
         {
            SDL_BlitSurface (b3p, 0, screen, &dst_b3);
            stop = 1;
		 }



		SDL_Flip(screen);/*Para atualizar a tela*/
	}

	SDL_Quit(); //encerrar a SDL
	return 0;
}
