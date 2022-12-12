
/*
	Arquivo: ex5.c
	Autor: Bruno Bottino Ferreira

	Exemplifica CD-�udio
*/

#include <SDL.h> //usaremos funcoes da SDL
#include <SDL_image.h> //e SDL_image

#define SCREEN_W 640 //tamanho da janela que sera criada
#define SCREEN_H 480

#define PLAYERX (SCREEN_W-384)/2
#define PLAYERY (SCREEN_H-64)/2
#define ERRO -1
SDL_Surface* my_surf;
SDL_Rect dst_rect = {PLAYERX, PLAYERY, 0, 0};

int mousex = 0, mousey = 0;
int current_track = 0;
SDL_CD* cdrom;

char tmp[32];

int get_button(int x, int y)
{
	x -= PLAYERX;
	y -= PLAYERY;

	if((x > 0) && (x < 384) && (y > 0) && (y < 64))
		return x/64;
	else
		return -1;
}

void player_action(int x, int y)
{
	//if(!CD_INDRIVE(SDL_CDStatus(cdrom))) return;

	sprintf(tmp, "button pressed: %d", get_button(x, y));
	SDL_WM_SetCaption(tmp, NULL);

	switch(get_button(x, y))
	{
		case -1: return;

		case 0: //play
			if(SDL_CDStatus(cdrom) == CD_PAUSED)
			{
				if (-1 == SDL_CDResume(cdrom))
				{
					printf("Nao consegui recomecar. SDL error=%s\n", SDL_GetError());
					exit(ERRO);
				}
			}
			else
			{
				if (-1 == SDL_CDPlayTracks(cdrom, current_track, 0, 1, 0))
				{
					printf("Nao consegui tocar. SDL error=%s\n", SDL_GetError());
					exit(ERRO);
				}			}
			break;
		case 1: //pause
			if(SDL_CDStatus(cdrom) == CD_PAUSED)
			{
				if (-1 == SDL_CDResume(cdrom))
				{
					printf("Nao consegui recomecar. SDL error=%s\n", SDL_GetError());
					exit(ERRO);
				}
			}
			else
			{
				if (-1 == SDL_CDPause(cdrom))
				{
					printf("Nao consegui parar. SDL error=%s\n", SDL_GetError());
					exit(ERRO);
				}
			}
			break;
		case 2: //stop
			if (-1 == SDL_CDStop(cdrom))
			{
				printf("Nao consegui parar. SDL error=%s\n", SDL_GetError());
				exit(ERRO);
			}
			break;
		case 3: //prev
			if(current_track > 0)
			{
				current_track--;
				if (-1 == SDL_CDPlayTracks(cdrom, current_track, 0, 1, 0))
				{
					printf("Nao consegui tocar. SDL error=%s\n", SDL_GetError());
					exit(ERRO);
				}
			}
			break;
		case 4: //next
			if(current_track < (cdrom->numtracks - 1))
			{
				current_track++;
				if (-1 == SDL_CDPlayTracks(cdrom, current_track, 0, 1, 0))
				{
					printf("Nao consegui tocar. SDL error=%s\n", SDL_GetError());
					exit(ERRO);
				}
			}
			break;
		case 5: //eject
			if (-1 == SDL_CDEject(cdrom))
			{
				printf("Nao consegui ejetar. SDL error=%s\n", SDL_GetError());
				exit(ERRO);
			}
			break;
	}
}

int main(int argc, char** argv) //funcao de entrada
{
    SDL_Surface* screen; //superficie que representa a tela do computador
    SDL_Event event; //um evento enviado pela SDL
    int quit = 0; //devemos encerrar o programa?

    if (-1 == SDL_Init(SDL_INIT_VIDEO | SDL_INIT_CDROM)) //inicializar a SDL
    {
		printf("Nao consegui inicializar. SDL error=%s\n", SDL_GetError());
		exit(ERRO);
	}
	screen = SDL_SetVideoMode(SCREEN_W, SCREEN_H, 16, SDL_SWSURFACE); //criar uma janela 640x480x16bits
	if (!screen)	
	{
		printf("Nao consegui iniciar modo de video. SDL error=%s\n", SDL_GetError());
		exit(ERRO);
	}	
	
	//inicializar o CD
	if(SDL_CDNumDrives() == 0)
	{
		SDL_Quit();
		return -1;
	}

	cdrom = SDL_CDOpen(0);
	/* Did if open? Check if cdrom is NULL */
	if(!cdrom)
	{
		fprintf(stderr, "Couldn't open drive: %s\n", SDL_GetError());
		exit(-1);
	}
	SDL_WM_SetCaption(SDL_CDName(0), NULL);

	//carregar as imagens
	my_surf = IMG_Load("player.png");
	if (!my_surf)
	{		
		printf("Nao consegui carregar imagem player.png\n");
		exit(ERRO);
	}	

    while(!quit) //rodar enquanto nao for para encerrar :)
    {
		while(SDL_PollEvent(&event)) //checar eventos
		{
			switch(event.type)
			{
				case SDL_QUIT: quit = 1; break;//sair do loop principal
				case SDL_KEYDOWN: if(event.key.keysym.sym == SDLK_ESCAPE) quit = 1; break;
				case SDL_MOUSEMOTION:
					mousex = event.motion.x;
					mousey = event.motion.y;

					sprintf(tmp, "mouse x: %d mouse y: %d", mousex, mousey);
					//SDL_WM_SetCaption(tmp, NULL);

					break;
				case SDL_MOUSEBUTTONDOWN:
					player_action(mousex, mousey);
					break;
				default: break;
			}
		}

		//limpar a tela
		if (-1 == SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 5, 50, 100)))
  		{
			printf("Nao consegui encher o retangulo. SDL error=%s\n", SDL_GetError());
			exit(ERRO);
		}
		//copiar a imagem para a tela
		if (-1 == SDL_BlitSurface(my_surf, NULL, screen, &dst_rect))
		{
			printf("Sem blit. SDL error=%s\n", SDL_GetError());
			exit(ERRO);
		}		
		if (-1 == SDL_Flip(screen)) //atualizar a tela
		{
			printf("Nao consegui fazer flip. SDL error=%s\n", SDL_GetError());
			exit(ERRO);
		}
	}

	SDL_CDClose(cdrom);

    SDL_Quit(); //encerrar a SDL

    return 0;
}
