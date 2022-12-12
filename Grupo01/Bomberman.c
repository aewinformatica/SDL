#include "includes.h"

int main (int argc, char **argv)
{
    if (Inicializa())
    {
        puts("Nao foi possivel inicializar o jogo.");
        return 1;
    }
    Jogo ();
    Finaliza ();
    return 0;
}

int Inicializa ()
{
    srand(time(NULL));
    Inicializa_Variaveis ();
    if (Inicializa_SDL ())
    {
        return 1;
    }

    screen = SDL_SetVideoMode (SCREEN_W, SCREEN_H, 16, SDL_DOUBLEBUF|SDL_FULLSCREEN);

    if (Carrega_Menu ())
    {
        puts("Impossivel carregar menu.");
        return 2;
    }
    if (Carrega_Sons ())
    {
        exit(5);
    }

	my_font22 = (TTF_Font*) TTF_OpenFont ("fonte.ttf", 22);
	my_font16 = (TTF_Font*) TTF_OpenFont ("fonte.ttf", 16);
	my_font72 = (TTF_Font*) TTF_OpenFont ("fonte.ttf", 72);

	cursor.img = IMG_Load ("Img/cursor.gif");
	SDL_ShowCursor (SDL_DISABLE);
	if (!cursor.img)
	{
	    puts ("Impossivel carregar cursor do mouse. Alternando para cursor padrao da SDL.");
	    SDL_ShowCursor (SDL_ENABLE);
	}
	SDL_SetColorKey (cursor.img, SDL_SRCCOLORKEY, SDL_MapRGB(cursor.img->format, 255, 0, 255));

	SDL_WarpMouse(SCREEN_W/2, SCREEN_H/2);
	cursor.posicao = (SDL_Rect) {SCREEN_W/2, SCREEN_H/2, 0 ,0};
	Carrega_Dados ();

    SDL_EnableKeyRepeat (5, 10);
    return 0;
}

void Jogo ()
{
    int sair = 0;
    SDL_Event event;
    Mix_PlayMusic (menu, -1);
    while (!sair)
    {
        ciclo++;
        tempo = SDL_GetTicks ();
        switch (estado)
        {
            case MENU:
                Eventos_Menu (&event, &sair);
                Tela_Menu();
                break;
            case LE_NOME:
            	Eventos_LeNome (&event, &sair);
            	Tela_LeNome ();
            	break;
            case CARREGAR:
                Eventos_Carregar (&event, &sair);
                Tela_Carregar ();
                break;
            case RECORDES_T:
            	Eventos_Recordes_T (&event, &sair);
            	Tela_Recordes_T ();
            	break;
           	case RECORDES_P:
           		Eventos_Recordes_P (&event, &sair);
           		Tela_Recordes_P ();
           		break;
            case INSTRUCOES:
                Eventos_Creditos (&event, &sair);
                Tela_Instrucoes ();
                break;
           	case CREDITOS:
           		Eventos_Creditos (&event, &sair);
           		Tela_Creditos ();
           		break;
           	case PAUSA:
           		Eventos_Pausa (&event, &sair);
           		Tela_Pausa ();
           		break;
            case SALVA:
                Eventos_Salva (&event, &sair);
                Tela_Save ();
                break;
            case JOGO:
                Verifica_Bonus ();
                Eventos_Fase (&event, &sair);
                Movimenta_Inimigo ();
                Move_Personagem ();
                Verifica_Mortes ();
                Resolve_Mortos ();
                Explode_Bomba ();
                Tela_Jogo();
                if (venceu == 1 && ciclo - tempo1 == 20)
                {puts("here");
                    Carrega_Fase_Seguinte (0, NULL);puts("'n here");
                }

                break;
            case GAMEOVER:
                Eventos_GameOver (&event, &sair);
                Tela_GameOver();
                break;
            default:
                sair = 1;
                break;
        }
        printf ("%d\n", estado);
       if (estado == JOGO && personagem.estado == VIVO)
       {
           tempo += SDL_GetTicks () - tempo;
           jogador.tempo = tempo/1000;
       }
    }
}

void Finaliza ()
{
    Salva_Dados ();
    Mix_CloseAudio ();
    TTF_Quit ();
    SDL_Quit ();
}
