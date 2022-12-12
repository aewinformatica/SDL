#include "includes.h"

void Eventos_Menu (SDL_Event *event, int *sair)
{
    Eventos_Menus (event, sair, 12);
}

void Eventos_LeNome (SDL_Event *event, int *sair)
{
	while (SDL_PollEvent (event))
	{
		switch (event->type)
		{
            case SDL_KEYDOWN:
            	if (event->key.keysym.sym >= 32 && event->key.keysym.sym <=255 && jogador.fim < 13)
            	{
					if (event->key.keysym.sym != '´' && event->key.keysym.sym != SDLK_BACKQUOTE && event->key.keysym.sym != '~' && event->key.keysym.sym != SDLK_CARET && event->key.keysym.sym != '¨')
					{
						jogador.nome[jogador.fim] = event->key.keysym.unicode;
						jogador.fim++;
						jogador.nome[jogador.fim] = '\0';
					}
				}
				switch (event->key.keysym.sym)
				{
					case SDLK_BACKSPACE:
						if (jogador.fim > 1)
						{
							jogador.fim--;
							jogador.nome[jogador.fim] = '\0';
						}
						else if (jogador.fim == 1)
						{
						    jogador.fim--;
						    jogador.nome[jogador.fim] = ' ';
						}
						break;
					default:
						break;
				}
				break;
			case SDL_MOUSEMOTION:
				cursor.posicao.x += event->motion.xrel;
				cursor.posicao.y += event->motion.yrel;
				botao = Verifica_Botao (5);
				break;
			case SDL_MOUSEBUTTONUP:
                printf ("%d\n", jogador.fim);
                if (jogador.nome[0] == ' ')
                {
                    jogador.nome[1] = '\0';
                }
                puts(jogador.nome);
				botao = Verifica_Botao (5);
				if (botao)
				{
				    Mix_PlayChannel(-1, clica, 0);
					Seleciona_Opcao (botao, sair);
				}
				break;
            case SDL_QUIT:
                *sair = 1;
			default:
				break;
		}
	}
}

void Eventos_Carregar (SDL_Event* event, int* sair)
{
    Eventos_Menus (event, sair, 6);
}

void Eventos_Recordes_T (SDL_Event* event, int* sair)
{
    Eventos_Menus (event, sair, 2);
}

void Eventos_Recordes_P (SDL_Event* event, int* sair)
{
    Eventos_Menus (event, sair, 2);
}

void Eventos_Instrucoes (SDL_Event* event, int* sair)
{
    Eventos_Menus (event, sair, 1);
}

void Eventos_Creditos (SDL_Event* event, int* sair)
{
    Eventos_Menus (event, sair, 1);
}

void Eventos_Pausa (SDL_Event* event, int* sair)
{
    Eventos_Menus (event, sair, 5);
}

void Eventos_Salva (SDL_Event* event, int* sair)
{
    Eventos_Menus (event, sair, 6);
}


void Eventos_Fase (SDL_Event* event, int* sair)
{
    int moveu = 0;

    while (SDL_PollEvent (event))
    {
        switch (event->type)
        {
            case SDL_KEYDOWN:
                if (personagem.estado == VIVO && venceu == 0)
                {
                    Eventos_Teclado (event, &moveu);
                }
                break;
            case SDL_QUIT:
                *sair = 1;
                break;
            default:
                break;
        }
    }
}

void Eventos_GameOver (SDL_Event* event, int* sair)
{
	while (SDL_PollEvent (event))
    {
        switch (event->type)
        {
            case SDL_MOUSEMOTION:
                cursor.posicao.x += event->motion.xrel;
                cursor.posicao.y += event->motion.yrel;
                botao = Verifica_Botao (2);
                if (botao)
                {
                    Colore_Botao (botao);
                }
                break;
            case SDL_MOUSEBUTTONUP:
            	botao = Verifica_Botao (2);
                if (botao)
                {
                    Mix_PlayChannel(-1, clica, 0);
                    Seleciona_Opcao (botao, sair);
                }
                break;
            case SDL_QUIT:
                *sair = 1;
                break;
            default:
                break;
        }
    }
}

void Eventos_Teclado (SDL_Event *event, int *moveu)
{
    switch (event->key.keysym.sym)
    {
        case SDLK_SPACE:
            if (existe_bomba < max_bombas && !mapa[personagem.i][personagem.j])
            {
                mapa[personagem.i][personagem.j] = 4;
                Add_Bomba_Fila (personagem.i, personagem.j);
            }
            break;
        case SDLK_UP:
            Verifica_Espaco(personagem.i-1, personagem.j, moveu);
            break;
        case SDLK_DOWN:
            Verifica_Espaco(personagem.i+1, personagem.j, moveu);
            break;
        case SDLK_RIGHT:
            Verifica_Espaco(personagem.i, personagem.j+1, moveu);
            break;
        case SDLK_LEFT:
            Verifica_Espaco(personagem.i, personagem.j-1, moveu);
            break;
        case SDLK_ESCAPE:
        	estado = PAUSA;
        	Mix_PauseMusic ();
        	SDL_WarpMouse (SCREEN_W/2, SCREEN_H/2);
        	cursor.posicao = (SDL_Rect) {SCREEN_W/2, SCREEN_H/2, 0 ,0};
        	SDL_EnableKeyRepeat (500, 100);
        	Define_Botoes ();
        	break;
        default:
            break;
    }
}

void Verifica_Espaco (int i, int j, int *moveu)
{
    if (mapa[i][j] != 1 && mapa[i][j] != 2 && mapa[i][j] != 4 && !(*moveu) && !(personagem.movendo))
    {
        personagem.i = i;
        personagem.j = j;
        *moveu = 1;
        personagem.movendo = 1;
        personagem.passo++;
        personagem.passo %= 2;
    }
}

int Verifica_Botao (int n)
{
	int i, j;
	int dentro;

	for (i=0; i<n; i++)
	{
		dentro = Dentro_Fora (botoes[i]);
		if (dentro)
		{
			if (estado == MENU)
			{
				if (i == 0)
				{
					cascata = 1;
				}
				else if (i == 3)
				{
					cascata = 2;
				}
				else if (i >= 6)
				{
					if (!cascata)
					{
						break;
					}
				}
				if (i == 9 && cascata == 2)
				{
				    continue;
				}
			}
			return i+1;
		}
		if (cascata)
        {
            for (j=1; j<=n; j++)
            {
                if (j == 1 || j == 2 || j == 4 || j == 5)
                {
                    continue;
                }
                if (!(Dentro_Fora (botoes[j])))
                {
                    dentro = 0;
                }
                else
                {
                    if ((cascata == 1 && j < 10) || (cascata == 2 && j > 8))
                    {
                        dentro = 1;
                    }
                    break;
                }
            }
            if (!dentro)
            {
                cascata = 0;
            }
        }
	}
    return 0;
}

void Seleciona_Opcao (int botao, int *sair)
{
    int i;
    switch (estado)
	{
		case MENU:
			switch (botao)
			{
				case 2:
                    estado = CARREGAR;
                    Define_Botoes ();
					break;
                case 3:
                    estado = INSTRUCOES;
                    if (!(fundo = IMG_Load ("Img/instrucoes.gif")))
					{
					    puts ("Nao carregou os creditos");
					    exit (9);
					}
                    Define_Botoes ();
                    break;
				case 5:
					estado = CREDITOS;
					if (!(fundo = IMG_Load ("Img/creditos.gif")))
					{
					    puts ("Nao carregou os creditos");
					    exit (9);
					}
					Define_Botoes ();
					break;
				case 6:
					*sair = 1;
					break;
				case 7:
					if (Carrega_Versao_IMG (LINUX))
					{
					    puts ("Impossivel carregar versao.");
					    exit(2);
					}
					if (Carrega_Versao_Som (LINUX))
					{
					    puts ("Impossivel carregar versao.");
					    exit(2);
					}
					estado = LE_NOME;
					Mix_PlayMusic (le_nome, -1);
					SDL_EnableKeyRepeat (500, 100);
					Define_Botoes ();
					SDL_EnableUNICODE (1);
					break;
				case 8:
					if (Carrega_Versao_IMG (MAC))
					{
					    puts ("Impossivel carregar versao.");
					    exit(2);
					}
					if (Carrega_Versao_Som (MAC))
					{
					    puts ("Impossivel carregar versao.");
					    exit(2);
					}
					estado = LE_NOME;
					Mix_PlayMusic (le_nome, -1);
					SDL_EnableKeyRepeat (500, 100);
					Define_Botoes ();
					SDL_EnableUNICODE (1);
					break;
				case 9:
					if (Carrega_Versao_IMG (WINDOWS))
					{
					    puts ("Impossivel carregar versao.");
					    exit(2);
					}
					if (Carrega_Versao_Som (WINDOWS))
					{
					    puts ("Impossivel carregar versao.");
					    exit(2);
					}
					estado = LE_NOME;
					Mix_PlayMusic (le_nome, -1);
					SDL_EnableKeyRepeat (500, 100);
					Define_Botoes ();
					SDL_EnableUNICODE (1);
					break;
				case 10:
					if (Carrega_Versao_IMG (BOMBER))
					{
					    puts ("Impossivel carregar versao.");
					    exit(2);
					}
					if (Carrega_Versao_Som (BOMBER))
					{
					    puts ("Impossivel carregar versao.");
					    exit(2);
					}
					estado = LE_NOME;
					Mix_PlayMusic (le_nome, -1);
					SDL_EnableKeyRepeat (500, 100);
					Define_Botoes ();
					SDL_EnableUNICODE (1);
					break;
				case 11:
					estado = RECORDES_T;
					Define_Botoes ();
					break;
				case 12:
					estado = RECORDES_P;
					Define_Botoes ();
					break;
				default:
					break;
			}
			break;
		case LE_NOME:
			switch (botao)
			{
				case 1:
					/*dificuldade = FACIL;
					Carrega_Fase_Seguinte (0, NULL);*/
					break;
				case 2:
                    dificuldade = FACIL;
					Carrega_Fase_Seguinte (0, NULL);
					break;
				case 3:
					dificuldade = DIFICIL;
					Carrega_Fase_Seguinte (0, NULL);
					break;
				case 4:
					/*do
					{
					    dificuldade = rand()%3;
					}while (dificuldade != MEDIO);
					Carrega_Fase_Seguinte (0, NULL);*/
					break;
				case 5:
					estado = MENU;
					Mix_PlayMusic (menu, -1);
					Define_Botoes ();
					break;
				default:
					break;
			}
			SDL_EnableUNICODE (0);
            if (botao != 5)
            {
				estado = JOGO;
				Mix_PlayMusic (jogo, -1);
				SDL_EnableKeyRepeat (5, 10);
			}
			break;
        case CARREGAR:
            switch (botao)
            {
                case 1:
                    Carrega_Jogo (1);
                    break;
                case 2:
                    Carrega_Jogo (2);
                    break;
                case 3:
                    Carrega_Jogo (3);
                    break;
                case 4:
                    Carrega_Jogo (4);
                    break;
                case 5:
                    Carrega_Jogo (5);
                    break;
                case 6:
                    estado = MENU;
                    Define_Botoes ();
                    break;
            }
            break;
        case INSTRUCOES:
			estado = MENU;
			Define_Botoes ();
			break;
		case GAMEOVER:
			switch (botao)
			{
				case 1:
					Inicializa_Variaveis ();
					personagem.estado = VIVO;
					venceu = 0;
					jogador.pontos = 0;
					jogador.tempo = 0;
					Mix_PlayMusic (menu, -1);
					break;
				case 2:
					*sair = 1;
					break;
				default:
					break;
			}
			break;
		case PAUSA:
			switch (botao)
			{
				case 1:
					estado = JOGO;
					Mix_ResumeMusic ();
					SDL_EnableKeyRepeat (5, 10);
					break;
				case 2:
					Reinicia_Jogo ();
					Mix_RewindMusic ();
					Mix_ResumeMusic ();
					SDL_EnableKeyRepeat (5, 10);
					break;
				case 3:
                    for (i=0; i<SAVES_NUM; i++)
                    {
                        sprintf (nome_saves[i], "%s", saves[i].nome);
                    }
					estado = SALVA;
					Define_Botoes ();
					break;
				case 4:
					estado = MENU;
					Mix_PlayMusic (menu, -1);
					fase = 0;
					SDL_WarpMouse (SCREEN_W/2, SCREEN_H/2);
					cursor.posicao = (SDL_Rect) {SCREEN_W/2, SCREEN_H/2, 0 ,0};
					Define_Botoes ();
					break;
				case 5:
					*sair = 1;
					break;
				default:
					break;
			}
			break;
		case RECORDES_T:
			switch (botao)
			{
				case 1:
					estado = RECORDES_P;
					Define_Botoes ();
					break;
				case 2:
					estado = MENU;
					Define_Botoes ();
					break;
				default:
					break;
			}
			break;
		case RECORDES_P:
			switch (botao)
			{
				case 1:
					estado = RECORDES_T;
					Define_Botoes ();
					break;
				case 2:
					estado = MENU;
					Define_Botoes ();
					break;
				default:
					break;
			}
			break;
		case CREDITOS:
            switch (botao)
			{
				case 1:
					estado = MENU;
					Define_Botoes ();
					break;
				default:
					break;
			}
			break;
        case SALVA:
            switch (botao)
            {
                case 1:
                    Salva_Jogo (0);
                    break;
                case 2:
                    Salva_Jogo (1);
                    break;
                case 3:
                    Salva_Jogo (2);
                    break;
                case 4:
                    Salva_Jogo (3);
                    break;
                case 5:
                    Salva_Jogo (4);
                    break;
                case 6:
                    estado = PAUSA;
                    Define_Botoes ();
                    break;
                default:
                    break;
            }
            break;
		default:
			break;
	}
}

int Dentro_Fora (SDL_Rect botao)
{
	if (cursor.posicao.x>=botao.x && cursor.posicao.x<=botao.x+botao.w)
	{
		if (cursor.posicao.y>=botao.y && cursor.posicao.y<=botao.y+botao.h)
		{
			return 1;
		}
	}
	return 0;
}

void Eventos_Menus (SDL_Event* event, int* sair, int n_botoes)
{
    int botao;

    while (SDL_PollEvent (event))
    {
        switch (event->type)
        {
            case SDL_MOUSEMOTION:
                cursor.posicao.x = event->motion.x;
                cursor.posicao.y = event->motion.y;
                botao = Verifica_Botao (n_botoes);
                break;
            case SDL_MOUSEBUTTONUP:
            	botao = Verifica_Botao (n_botoes);
                if (botao)
                {
                    Mix_PlayChannel(-1, clica, 0);
                    Seleciona_Opcao (botao, sair);
                }
                break;
            case SDL_KEYDOWN:
            	if (estado == PAUSA && event->key.keysym.sym == SDLK_ESCAPE)
				{
					estado = JOGO;
					Mix_ResumeMusic ();
					SDL_EnableKeyRepeat (5, 10);
				}
				break;
            case SDL_QUIT:
                *sair = 1;
                break;
            default:
                break;
        }
    }
}
