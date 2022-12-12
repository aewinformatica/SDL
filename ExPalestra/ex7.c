
/*
	Arquivo: ex6.c
	Autor: Bruno Bottino Ferreira

	Exemplifica sons e música
*/

#include <SDL.h> //usaremos funcoes da SDL
#include <SDL_image.h> //e SDL_image
#include <SDL_mixer.h> //e SDL_mixer

#define SCREEN_W 640 //tamanho da janela que sera criada
#define SCREEN_H 480

#define BOMBX (SCREEN_W-300)/2
#define BOMBY (SCREEN_H-231)/2

#define BOMBBORDER 32

#define UPDATETIME 2 * 1000 //2 segundos

SDL_Surface* my_surf;
SDL_Rect dst_rect = {BOMBX, BOMBY, 0, 0};

int mousex = 0, mousey = 0;

Mix_Chunk* sound;
Mix_Music* music;

int start_time = -1000000;
int bomb_moving = 0;

int incx = 5, incy = 5;

void update_bomb(void)
{
	if(!bomb_moving) return;
	if((SDL_GetTicks() - start_time) > UPDATETIME) bomb_moving = 0;

	dst_rect.x += incx;
	dst_rect.y += incy;

	if((dst_rect.x < 0) || (dst_rect.x > SCREEN_W-300)) incx = -incx;
	if((dst_rect.y < 0) || (dst_rect.y > SCREEN_H-231)) incy = -incy;
}

Uint32 timer_func(Uint32 interval, void *param)
{
	Mix_PlayChannel(-1, sound, 0);

	return 0; //suprimir warning
}

int main(int argc, char** argv) //funcao de entrada
{
    SDL_Surface* screen; //superficie que representa a tela do computador
    SDL_Event event; //um evento enviado pela SDL
    int quit = 0; //devemos encerrar o programa?

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER); //inicializar a SDL
    screen = SDL_SetVideoMode(SCREEN_W, SCREEN_H, 16, SDL_SWSURFACE); //criar uma janela 640x480x16bits

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096); //inicializar SDL_mixer
	Mix_AllocateChannels(1);
	sound = Mix_LoadWAV("kaboom.wav");
	music = Mix_LoadMUS("music.mod");

	//carregar as imagens
	my_surf = IMG_Load("kaboom.png");

	//tocar a musica
	Mix_PlayMusic(music, -1);

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
					break;
				case SDL_MOUSEBUTTONDOWN:
					if(!bomb_moving) //somente uma explosao por vez...
					{
						start_time = SDL_GetTicks(); //ponha a bomba em movimento
						SDL_AddTimer(UPDATETIME, timer_func, NULL); //ligue o timer da explosao
						bomb_moving = 1;
					}

					break;
				default: break;
			}
		}

		//atualizar a posicao
		update_bomb();

		//limpar a tela
		SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 5, 50, 100));

		//copiar a imagem para a tela
		SDL_BlitSurface(my_surf, NULL, screen, &dst_rect);

		SDL_Flip(screen); //atualizar a tela
	}

	Mix_FreeChunk(sound);
	Mix_FreeMusic(music);

	Mix_CloseAudio();

    SDL_Quit(); //encerrar a SDL

    return 0;
}
