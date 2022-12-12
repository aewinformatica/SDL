#include "include.h"

extern int musicON;
extern int del;

int Abertura(SDL_Surface*);
int Menu(SDL_Surface*);
int ConfirmaSaida(SDL_Surface*);
int Creditos(SDL_Surface*);
int Recordes(SDL_Surface* );
int Opcoes(SDL_Surface*);

int Abertura(SDL_Surface* screen)
{
	int i,j;

	SDL_Surface* abertura;
	if(!abertura) return 1;
	SDL_Rect dst_abertura = {0, 0, 0, 0};

	for(i=0;i<3;i++) // REPETE 3 VEZES PARA AS 3 TELAS DE ABERTURA: logo ufrj, sobre o projeto, grupo 5
	{
		
		if(i==2)
		{
			abertura = IMG_Load("./imgs/abertura/img2.gif");
			if(!abertura) return 1;
		}
		else if(i==1)
		{
			abertura = IMG_Load("./imgs/abertura/img1.gif");
			if(!abertura) return 1;
		}
		else
		{
			abertura = IMG_Load("./imgs/abertura/img0.gif");
			if(!abertura) return 1;
		}

		dst_abertura.x = (SCREEN_W/2)-(abertura->w/2); // CENTRALIZA A IMAGENS
		dst_abertura.y = (SCREEN_H/2)-(abertura->h/2);

		SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0)); // APAGA "O QUADRO"

		for(j=0;j<=250;j=j+25) // EFEITO PARA A IMAGEM IR APARECENDO.. OPACIDADE DO 0 AO 250
		{
			SDL_SetAlpha(abertura, SDL_SRCALPHA, j);			
			SDL_BlitSurface(abertura,NULL, screen,&dst_abertura);
			SDL_Flip(screen);
			SDL_Delay(100);
		}
		
		SDL_Delay(2000); // DELAY PADRAO DA IMAGEM
		if(i==1) SDL_Delay(7000); // SE FOR O "SOBRE O PROJETO" DEMORA MAIS A SUMIR

		for(j=250;j>=0;j=j-25) // EFEITO PARA A IMAGEM IR SUMINDO .. OPACIDADE DO 250 AO 0
		{
			SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
			SDL_SetAlpha(abertura, SDL_SRCALPHA, j);			
			SDL_BlitSurface(abertura,NULL, screen,&dst_abertura);
			SDL_Flip(screen);
			SDL_Delay(100);
		}
		SDL_FreeSurface(abertura);
		
	}

	return 0;
}


int Menu(SDL_Surface* screen)
{

	int i,quit=0,selecionou=0;
	int mouse_x, mouse_y;
	SDL_Event event;
	SDL_Surface* menu;
	SDL_Surface* marca;

	Mix_Music* music;
	Mix_Chunk* overSound;

	music = Mix_LoadMUS("./sounds/trilhas/menu.mid");
	overSound = Mix_LoadWAV("./sounds/efeitos/click.WAV");
	
	if(musicON)	Mix_PlayMusic(music, -1);

	menu = SDL_LoadBMP("./imgs/menu/menu1.bmp");
	if(!menu) return 0;
	SDL_Rect dst_menu = {0, 0, 0, 0};
	
	marca = SDL_LoadBMP("./imgs/menu/marcador.bmp");
	if(!marca) return 0;
	SDL_SetAlpha(marca, SDL_SRCALPHA, 70);
	SDL_Rect dst_marca = {0, -100, 0, 0};
	SDL_Rect dst_marca2 = {0, 0, 0, 38};

	// EFEITO PARA DESCER O MENU ATÉ dst_menu.y = 0 
	for(i=-SCREEN_H;i<=0;i+=20)
	{
		dst_menu.y = i;
		SDL_BlitSurface(menu,NULL, screen,&dst_menu);
		SDL_Flip(screen);
		SDL_Delay(20);
	}

	while(!quit)
    {
		while(SDL_PollEvent(&event)) //checar eventos
		{

			switch(event.type)
			{
				case SDL_QUIT://sair do loop principal
						quit = ConfirmaSaida(screen);
						SDL_BlitSurface(menu,NULL, screen,&dst_menu);
						SDL_Flip(screen);
					break;
				
				case SDL_MOUSEMOTION: // CARREGA O RETANGULO BRANCO-OPACO PARA CIMA DO ITEM
					mouse_x = event.motion.x;
					mouse_y = event.motion.y;
					
					if(mouse_x > 266 && mouse_x < 416 && mouse_y > 205 && mouse_y < 237)
					{
							
							dst_marca.x = 247;
							dst_marca.y = 202;
							dst_marca2.w = 186;
							selecionou = 2;
					}
					else if(mouse_x > 265 && mouse_x < 415 && mouse_y > 250 && mouse_y < 280)
					{
							
							dst_marca.x = 254;
							dst_marca.y = 247;
							dst_marca2.w = 174;
							selecionou = 2;
					}
					else if(mouse_x > 275 && mouse_x < 400 && mouse_y > 298 && mouse_y < 330)
					{
							dst_marca.x = 265;
							dst_marca.y = 295;
							dst_marca2.w = 151;
							selecionou = 2;
					}
					else if(mouse_x > 275 && mouse_x < 400 && mouse_y > 347 && mouse_y < 378)
					{
							dst_marca.x = 261;
							dst_marca.y = 345;
							dst_marca2.w = 152;
							selecionou = 2;

					}
					else if(mouse_x > 304 && mouse_x < 375 && mouse_y > 392 && mouse_y < 424)
					{
							dst_marca.x = 293;
							dst_marca.y = 390;
							dst_marca2.w = 93;
							selecionou = 2;
					}
					else
					{
						dst_marca.y = -100;
						if(selecionou > 0) selecionou -=1;
					}
					
					if(selecionou){ // EVITA BLITAR SEM ALTERAÇÕES
						SDL_BlitSurface(menu,NULL, screen,&dst_menu);
						SDL_BlitSurface(marca,&dst_marca2, screen,&dst_marca);
						SDL_Flip(screen);							
					}

					break;

				case SDL_MOUSEBUTTONDOWN: // VERIFICA CLIQUES
					SDL_GetMouseState(&mouse_x, &mouse_y); // PEGA AS POSIÇÕES X, Y DO MOUSE
					
					// ÁREA DO BOTÃO NOVO JOGO
					if(mouse_x > 266 && mouse_x < 416 && mouse_y > 205 && mouse_y < 237)
					{
						if(musicON && dst_marca.y != -100) Mix_PlayChannel(-1, overSound, 0);	
						
						Mix_FreeMusic(music);
						SDL_FreeSurface(menu);
						SDL_FreeSurface(marca);
						return 1;
					}
					// ÁREA DO BOTÃO RECORDES
					if(mouse_x > 265 && mouse_x < 415 && mouse_y > 250 && mouse_y < 280)
					{
						if(musicON && dst_marca.y != -100) Mix_PlayChannel(-1, overSound, 0);	
						
						Mix_FreeMusic(music);
						SDL_FreeSurface(menu);
						SDL_FreeSurface(marca);
						Recordes(screen);
						return 2;
					}
					// ÁREA DO BOTÃO OPÇÕES
					if(mouse_x > 275 && mouse_x < 400 && mouse_y > 298 && mouse_y < 330)
					{
						if(musicON && dst_marca.y != -100) Mix_PlayChannel(-1, overSound, 0);	
						
						Mix_FreeMusic(music);
						SDL_FreeSurface(menu);
						SDL_FreeSurface(marca);
						Opcoes(screen);
						return 3;
					}
					// ÁREA DO BOTÃO CREDITOS
					if(mouse_x > 275 && mouse_x < 400 && mouse_y > 347 && mouse_y < 378)
					{	
						if(musicON && dst_marca.y != -100) Mix_PlayChannel(-1, overSound, 0);	
						
						Mix_FreeMusic(music);
						SDL_FreeSurface(menu);
						SDL_FreeSurface(marca);
						Creditos(screen);
						return 4;
					}
					// ÁREA DO BOTÃO SAIR
					if(mouse_x > 304 && mouse_x < 375 && mouse_y > 392 && mouse_y < 424)
					{
						if(musicON) Mix_PlayChannel(-1, overSound, 0);	
						quit = ConfirmaSaida(screen);
						SDL_BlitSurface(menu,NULL, screen,&dst_menu);
						SDL_Flip(screen);
					}
					break;

				case SDL_KEYDOWN:
					if(event.key.keysym.sym == SDLK_ESCAPE) // TECLA ESC
					{
						quit = ConfirmaSaida(screen);
						SDL_BlitSurface(menu,NULL, screen,&dst_menu);
						SDL_Flip(screen);
					}
					break;

				default:
					break;
			}
		}
	}
	SDL_FreeSurface(menu);
	return 0;
}

int ConfirmaSaida(SDL_Surface* screen)
{
	int quit = 0,mouse_x,mouse_y;

	SDL_Surface* sair;
	sair = SDL_LoadBMP("./imgs/menu/sair.bmp");
	if(!sair) return 1;

	SDL_SetColorKey(sair, SDL_SRCCOLORKEY, SDL_MapRGB(sair->format, 255, 0, 255));
	SDL_Rect dst_sair = {(SCREEN_W/2)-(sair->w/2), (SCREEN_H/2)-(sair->h/2)-(PADRAO/2), 0, 0};
	SDL_BlitSurface(sair,NULL, screen,&dst_sair);
	SDL_Flip(screen);
	SDL_Event event;

	while(!quit)
    {
		while(SDL_PollEvent(&event)) //checar eventos
		{

			switch(event.type)
			{
				case SDL_QUIT://sair do loop principal
					SDL_FreeSurface(sair);
					return 1;
					break;
				case SDL_MOUSEBUTTONDOWN:
					SDL_GetMouseState(&mouse_x, &mouse_y); // PEGA AS POSIÇÕES X, Y DO MOUSE
										
					if(mouse_x > 258 && mouse_x < 335 && mouse_y > 271 && mouse_y < 304)
					{
						return 1; // CONFIRMA SAÍDA.. RETORNA 1 PARA A VARIAVEL "quit" NO MENU
						SDL_FreeSurface(sair);
					}
					if(mouse_x > 339 && mouse_x < 416 && mouse_y > 271 && mouse_y < 304)
					{
						return 0; // CANCELA SAÍDA.. RETORNA 0 PARA A VARIAVEL "quit" NO MENU
						SDL_FreeSurface(sair);
					}
				default:
					break;
			}
		}
	}
	return 0;
}

int Creditos(SDL_Surface* screen)
{
	int mouse_x,mouse_y,i;

	SDL_Surface* creditos;
	creditos = SDL_LoadBMP("./imgs/creditos.bmp");
	if(!creditos) return 1;
	
	SDL_Rect dst_creditos = { 0, 0, 0, 0};
	
	// Desce Creditos
	for(i=-SCREEN_H;i<=0;i+=20)
	{
		dst_creditos.y = i;
		SDL_BlitSurface(creditos,NULL, screen,&dst_creditos);
		SDL_Flip(screen);
		SDL_Delay(20);
	}

	SDL_BlitSurface(creditos,NULL, screen,NULL);
	SDL_Flip(screen);
	SDL_Event event;

	while(1)
    {
		while(SDL_PollEvent(&event)) //checar eventos
		{

			switch(event.type)
			{
				case SDL_QUIT://sair do loop principal
					SDL_FreeSurface(creditos);
					return 0;
					break;
				case SDL_MOUSEBUTTONDOWN:
					SDL_GetMouseState(&mouse_x, &mouse_y); // PEGA AS POSIÇÕES X, Y DO MOUSE
										
					if(mouse_x > 241 && mouse_x < 484 && mouse_y > 446 && mouse_y < 472)
					{
						SDL_FreeSurface(creditos);
						return 0;
					}
				default:
					break;
			}
		}
	}
	return 0;
}

int Recordes(SDL_Surface* screen)
{
	int mouse_x,mouse_y,i;

	char tempo[11];
	
	char temp[14];

	TTF_Init();
	TTF_Font* fonte;
	fonte = TTF_OpenFont("./fonte/baabookhmkbold.ttf",20);
	SDL_Rect dst_nome = {141,184,0,0};
	SDL_Rect dst_pontuacao = {412,187,0,0};
	SDL_Color cor = {0,0,0};//preto
	SDL_Surface* texto;
	
	FILE *p;
	char *n="./matrizes/recordes.txt";
	p=fopen(n,"r");

	SDL_Surface* recordes;
	recordes = SDL_LoadBMP("./imgs/recordes.bmp");
	if(!recordes) return 1;
	
	SDL_Rect dst_recordes = { 0, 0, 0, 0};
	
	
	// Desce recordes
	for(i=-SCREEN_H;i<=0;i+=20)
	{
		dst_recordes.y = i;
		SDL_BlitSurface(recordes,NULL, screen,&dst_recordes);
		SDL_Flip(screen);
		SDL_Delay(20);
	}
	SDL_BlitSurface(recordes,NULL, screen,NULL);
	for (i=0;i<10;i++)
	{
		dst_nome.y+=26;
		fread(&temp,sizeof(char),13,p);
		temp[12]='\0';
		texto = TTF_RenderText_Blended(fonte,temp,cor);
		SDL_BlitSurface(texto,NULL,screen,&dst_nome);
		SDL_FreeSurface(texto);
	}
	for (i=0;i<10;i++)
	{
		dst_pontuacao.y+=26;
		fread(&tempo,sizeof(char),10,p);
		tempo[9]='\0';
		//tempo[10]='\0';
		//fread(&temp,sizeof(char),1,p);
		texto = TTF_RenderText_Blended(fonte,tempo,cor);
		SDL_BlitSurface(texto,NULL,screen,&dst_pontuacao);
		SDL_FreeSurface(texto);
	}


	SDL_Flip(screen);
	SDL_Event event;

	while(1)
    {
		while(SDL_PollEvent(&event)) //checar eventos
		{

			switch(event.type)
			{
				case SDL_QUIT://sair do loop principal
					fclose(p);
					TTF_Quit();
					SDL_FreeSurface(recordes);
					return 0;
					break;
				case SDL_MOUSEBUTTONDOWN:
					SDL_GetMouseState(&mouse_x, &mouse_y); // PEGA AS POSIÇÕES X, Y DO MOUSE
										
					if(mouse_x > 238 && mouse_x < 480 && mouse_y > 506 && mouse_y < 532)
					{
						fclose(p);
						TTF_Quit();
						SDL_FreeSurface(recordes);
						return 0;
					}
				default:
					break;
			}
		}
	}
	return 0;
}


int Opcoes(SDL_Surface* screen)
{
	int mouse_x,mouse_y,i;
	SDL_Event event;

	SDL_Surface* opcoes;
	SDL_Surface* marca;

	marca = SDL_LoadBMP("./imgs/menu/marcador.bmp");
	if(!marca) return 1;
	SDL_SetAlpha(marca, SDL_SRCALPHA, 70);
	SDL_Rect dst_marca = {320, 0, 0, 0};
	SDL_Rect dst_marca2 = {320, 0, 0, 0};
	SDL_Rect dst_marcador = {0,0,53,25};
	SDL_Rect dst_marcador2 = {0,0,110,25};

	if(musicON)
	{
		dst_marca.y = 230; // ON
	}
	else
	{
		dst_marca.y = 270; // OFF
	}
	
	if(del == 15)
	{
		dst_marca2.y = 315; // RAPIDA
	}
	else if(del == 45)
	{
		dst_marca2.y = 395;	 // LENTA
	}
	else
	{
		dst_marca2.y = 353;	 // MEDIA
	}

	opcoes = SDL_LoadBMP("./imgs/opcoes.bmp");
	if(!opcoes) return 1;
	
	SDL_Rect dst_opcoes = {0, 0, 0, 0};
	
	// Desce Opcoes
	for(i=-SCREEN_H;i<=0;i+=20)
	{
		dst_opcoes.y = i;
		SDL_BlitSurface(opcoes,NULL, screen,&dst_opcoes);
		SDL_Flip(screen);
		SDL_Delay(20);
	}

	SDL_BlitSurface(opcoes,NULL, screen,NULL);
	SDL_BlitSurface(marca,&dst_marcador, screen,&dst_marca);
	SDL_BlitSurface(marca,&dst_marcador2, screen,&dst_marca2);	
	
	SDL_Flip(screen);
	
	while(1)
    {
		while(SDL_PollEvent(&event)) //checar eventos
		{

			switch(event.type)
			{
				case SDL_QUIT://sair do loop principal
					SDL_FreeSurface(opcoes);
					SDL_FreeSurface(marca);
					return 0;
					break;
				case SDL_MOUSEBUTTONDOWN:
					SDL_GetMouseState(&mouse_x, &mouse_y); // PEGA AS POSIÇÕES X, Y DO MOUSE
										
					if(mouse_x > 241 && mouse_x < 484 && mouse_y > 508 && mouse_y < 531)
					{
						SDL_FreeSurface(opcoes);
						SDL_FreeSurface(marca);
						return 0;
					}
					if(mouse_x > 320 && mouse_x < 370)
					{
						if(mouse_y > 230 && mouse_y < 256)
						{
							musicON = 1;
							dst_marca.y = 230;
						}
						else if(mouse_y > 270 && mouse_y < 295)
						{
							musicON = 0;
							dst_marca.y = 270;						
						}
					}

					if(mouse_x > 320 && mouse_x < 435)
					{
						if(mouse_y > 315 && mouse_y < 339)
						{
							del = 15;			
							dst_marca2.y = 315;
						}
						else if(mouse_y > 353 && mouse_y < 376)
						{
							del = 30;
							dst_marca2.y = 353;				
						}
						else if(mouse_y > 395 && mouse_y < 415)
						{
							del = 45;
							dst_marca2.y = 395;	
						}
					}

				default:
					break;
			}
	
		}

	SDL_BlitSurface(opcoes,NULL, screen,NULL);
	SDL_BlitSurface(marca,&dst_marcador, screen,&dst_marca);
	SDL_BlitSurface(marca,&dst_marcador2, screen,&dst_marca2);	
	
	SDL_Flip(screen);

	}
	return 0;
}
