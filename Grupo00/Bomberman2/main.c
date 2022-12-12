/*
    Grupo: Bruna de Barros, Pedro Philippe, George Lucas
    gcc main.c funcoes.c -o bomberman -Wall -g -lm -lmingw32 -lsdlmain -lsdl -lSDL_ttf -lSDL_mixer -lSDL_image
	gcc main10.c funcoes10.c -o bomberman10l -Wall `sdl-config --cflags --libs` -lSDL_ttf -lSDL_mixer -lSDL_image
*/

#include "IncludeBomber.h"

int main (int argc, char **argv)
{
    /*====================Declaracoes=======================*/
	SDL_Event evento;
	int tempo_frame, tempo_pausado, tempo_gameover=0, tempo_texto;
	int i, tam, musica_jogo, cena_abertura=1;
	int cont1=0, cont2=0, cont3=0; //variaveis que controlam a escolha das musicas em midi
	enum Opcao_menu opcao_selecionada;
	char string_score[MAXNOME];

    /*====================Inicializacoes====================*/

    //Inicializa SDL
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_EnableKeyRepeat(REPEAT_DELAY, REPEAT_INTERVAL);
	SDL_EnableUNICODE(1);

	srand(time(NULL));
	quit = 0;
	som = 1;
	estado_jogo = ABERTURA;
	opcao_selecionada = NOVOJOGO;

	if(TTF_Init() == -1)  return -1;
    if(Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )  return -1;
	Init_Surfaces();
	Init_Cenario();
	Init_Sons();
	Init_Bomberman();
	for(i=0; i<MAXBOMBAS; i++)
        Init_Bomba(&bomba[i]);
	Mix_AllocateChannels(NCHANNEL);
	Load_Highscore();

	Init_Monstros();
	Init_Bomba_Monstros();
	
	font_times = TTF_OpenFont("times.ttf", FONTSIZE);
	if(font_times==NULL)
        return 1;

	Init_Jogador();

	Init_Cenas();
	tempo_texto = SDL_GetTicks();

    /*==================Loop Principal====================*/
    while(!quit)
    {
        tempo_frame = SDL_GetTicks();
		/*=============== Trata Eventos==================*/
		while(SDL_PollEvent(&evento))
		{
            switch(evento.type)
            {
                case SDL_QUIT:
                    quit = 1;
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    if( evento.button.button == SDL_BUTTON_LEFT )
                    {
                        if( evento.button.x < surf_som_ok->w &&  evento.button.y < surf_som_ok->h )
                        {
                            if(estado_jogo == MENUJOGO && som == 1)
                            {
                                Desabilita_Sons();
                                som = 0;
                            }
                            else if(estado_jogo == MENUJOGO && som == 0)
                            {
                                Init_Sons();
                                Mix_PlayMusic(musica_abertura,-1);
                                som = 1;
                            }
                        }
                    }
                    break;

                case SDL_KEYDOWN:
                    switch(evento.key.keysym.sym)
                    {
                        case SDLK_ESCAPE:
                            quit = 1;
                            break;

                        case SDLK_p:
                            if(estado_jogo == JOGANDO)
                            {
                                estado_jogo = PAUSE;
                                SDL_EnableKeyRepeat(0, 0);
                                tempo_pausado = SDL_GetTicks();
                            }
                            else if(estado_jogo == PAUSE)
                            {
                                tempo_pausado = SDL_GetTicks() - tempo_pausado;

                                for(i=0; i<bomberman.max_bombas; i++)
                                    bomba[i].tempo_inicial += tempo_pausado;
                                estado_jogo = JOGANDO;
                                SDL_EnableKeyRepeat(REPEAT_DELAY, REPEAT_INTERVAL);
                            }
                            else if(estado_jogo == NOME)
                            {
                                tam = strlen(jogador.nome);
                                if(tam < MAXNOME - 1)
                                    jogador.nome[tam] = evento.key.keysym.unicode & 0x7F;
                            }
                            break;

                        case SDLK_a...SDLK_o:
                        case SDLK_q...SDLK_z:
                        case SDLK_0...SDLK_9:
                        case SDLK_PERIOD:
						case SDLK_MINUS:
						case SDLK_QUOTE:
                            if(estado_jogo == NOME)
                            {
                                tam = strlen(jogador.nome);
                                if(tam < MAXNOME - 1)
                                    jogador.nome[tam] = evento.key.keysym.unicode & 0x7F;
                            }
                            break;

                        case SDLK_BACKSPACE:
                            if(estado_jogo == NOME)
                            {
                                tam = strlen(jogador.nome);
                                if(tam > 0)
                                {
                                    jogador.nome[tam - 1] = '\0';
                                }
                            }
                            break;

						case SDLK_UP:
                            if(estado_jogo == JOGANDO)
                            {
                                Bomberman_move(CIMA);
                            }
                            else if(estado_jogo == MENUJOGO)
                            {
                                opcao_selecionada = (opcao_selecionada + 2)%3;
								Mix_PlayChannel(4,click,0);
                            }
							break;

						case SDLK_RIGHT:
                            if(estado_jogo == JOGANDO)
                            {
                                Bomberman_move(DIREITA);
                            }
							break;

						case SDLK_DOWN:
                            if(estado_jogo == JOGANDO)
                            {
                                Bomberman_move(BAIXO);
                            }
                            else if(estado_jogo == MENUJOGO)
                            {
                                opcao_selecionada = (opcao_selecionada + 1)%3;
								Mix_PlayChannel(4,click,0);
                            }
							break;

						case SDLK_LEFT:
                            if(estado_jogo == JOGANDO)
                            {
                                Bomberman_move(ESQUERDA);
                            }
							break;

                        case SDLK_SPACE:
                            if(estado_jogo == JOGANDO)
                            {
                                Bota_Bomba();
                            }
                            else if(estado_jogo == NOME)
                            {
                                tam = strlen(jogador.nome);
                                if(tam < MAXNOME - 1)
                                    jogador.nome[tam] = evento.key.keysym.unicode & 0x7F;
                            }
                            else if(estado_jogo == ABERTURA)
							{
								estado_jogo = MENUJOGO;
							}
                            break;

                        case SDLK_RETURN:
                            if(estado_jogo == MENUJOGO)
                            {
                                switch(opcao_selecionada)
                                {
                                    case NOVOJOGO:
                                        estado_jogo = JOGANDO;
										Mix_PlayChannel(5,seleciona,0);
                                        break;
                                    case O_HIGHSCORE:
                                        estado_jogo = HIGHSCORE;
										Mix_PlayChannel(5,seleciona,0);
                                        break;
                                    case SAIR:
                                        quit =1;
										Mix_PlayChannel(5,seleciona,0);
                                        break;
                                    default: break;
                                }
                            }
                            else if(estado_jogo == NOME)
                            {
                                estado_jogo = HIGHSCORE;
                                Adiciona_Highscore(jogador.nome,jogador.score);
                            }
                            else if(estado_jogo == HIGHSCORE)
                            {
                                estado_jogo = MENUJOGO;
                                Init_Cenario();
                                Init_Bomberman();
                                Load_Highscore();
                                Init_Monstros();
                                Init_Jogador();
                            }
                            else if(estado_jogo == ABERTURA)
							{
								estado_jogo = MENUJOGO;
							}
                            break;

                        case SDLK_F5:
                            Init_Cenario();
                            break;

                        default: break;
                    }
                    break;

				case SDL_KEYUP:
					break;
            }
        }//fim trata eventos

        /*===================Processamento=============*/
        switch(estado_jogo)
        {
            case JOGANDO:
                for(i=0; i<bomberman.max_bombas; i++)
                    Explode_Bomba(&bomba[i]);
				Monstros_Explode_Bomba();
                Update_bomberman();
				Movimentar_Monstros();
                break;

            case GAMEOVER:
                if(tempo_gameover == 0) //caso tenha acabado de entrar em gameover
                {
                    tempo_gameover = SDL_GetTicks();
                }
                else
                {
                    if(SDL_GetTicks() - tempo_gameover > 3000) //tempo em G.O. > 3s ir pro menu
                    {
                        estado_jogo = NOME;
                        tempo_gameover = 0;
                    }
                }
                break;

			case ABERTURA:
				if(SDL_GetTicks() - tempo_texto >= TEMPOTEXTO)
				{
					cena_abertura++;
					tempo_texto=SDL_GetTicks();
				}
				if(cena_abertura==4)
					estado_jogo = MENUJOGO;
					break;
            default:
                break;
        }


		/*===========================RENDER==============================*/

        switch(estado_jogo)
        {
            case JOGANDO:
                if(!cont3)
				{
					musica_jogo=rand()%3;
					switch(musica_jogo)
					{
						case 0:
							Mix_PlayMusic(musica_jogo1,-1); break;
						case 1:
							Mix_PlayMusic(musica_jogo2,-1); break;
						case 2:
							Mix_PlayMusic(musica_jogo3,-1); break;
						default: break;
					}
					cont3++;
				}

				SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
                //Renderiza Cenario
                Desenha_cenario();

                //Renderiza Infos
                Desenha_Infos();

                //Renderiza Bombas
                for(i=0; i<bomberman.max_bombas; i++)
					if(bomba[i].estado)
                        SDL_BlitSurface(bomba[i].superficie, NULL, screen, &bomba[i].dest);
						
				//Renderiza Bombas dos Monstros
				Monstros_Desenha_Bomba();
				
				//Renderiza Monstro
				Desenha_Monstros();				

                //Renderiza Bobmerman
                SDL_BlitSurface(bomberman.superficie, &bomberman.orig[bomberman.estado], screen, &bomberman.dest);

                break;

            case PAUSE:
                Desenha_Pause(MAPA_W/2, MAPA_H/2, font_times);
                break;

			case GAMEOVER:
				Desenha_Gameover( MAPA_W/2-surf_gameover->w/2 , MAPA_H/2-surf_gameover->h/2 , font_times);
				break;

            case MENUJOGO:
                if(!cont1)
				{
					Mix_PlayMusic(musica_abertura,-1);
					cont1++;
				}

				cont2=cont3=0;
				SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
                SDL_BlitSurface(tela_menu, NULL, screen, NULL);
                Desenha_MenuJogo(opcao_selecionada);
                if(som)
                {
                    SDL_BlitSurface( surf_som_ok, NULL, screen, NULL);
                }
                else
                {
                    SDL_BlitSurface( surf_som_des, NULL, screen, NULL);
                }
                break;

            case NOME:
                SDL_BlitSurface(surf_nome, NULL, screen, NULL);
                Desenha_Texto(jogador.nome, 90, 350, (SDL_Color){255, 0, 0});
                break;

            case HIGHSCORE:
                if(!cont2)
				{
					Mix_PlayMusic(musica_highscore,-1);
					cont2++;
				}

				cont1=0;
				SDL_BlitSurface(surf_highscore, NULL, screen, NULL);
                for(i=0; jogador_high[i].nome[0]; i++)
                {
                    Desenha_Texto(jogador_high[i].nome, 380, 50 + i*50, (SDL_Color){255, 0, 0});
                    sprintf(string_score, "%d", jogador_high[i].score);
                    Desenha_Texto(string_score, 650, 50 + i*50, (SDL_Color){255, 0, 0});
                }
                break;

			case ABERTURA:
				Desenha_Abertura(cena_abertura);
				break;

            default:
                break;
        }

		//Atualiza Tela
		SDL_Flip(screen);

		/*=========================FPS=======================*/
		Limita_fps( tempo_frame );



	}//loop principal

    Mix_CloseAudio();
    TTF_Quit();
    SDL_Quit();
    return 0;
}
