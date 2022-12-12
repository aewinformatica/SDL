#include "includes.h"

void Tela_Menu ()
{
    int botao;

    SDL_Rect destino;

	SDL_FillRect (screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));

    destino  = (SDL_Rect) {175, 50, 0, 0};
	SDL_BlitSurface (nome_do_jogo, NULL, screen, &destino);

	destino = (SDL_Rect) {100, 200, 0, 0};
	SDL_BlitSurface (pinguim, NULL, screen, &destino);

	destino = (SDL_Rect) {600, 200, 0, 0};
	SDL_BlitSurface (janela, NULL, screen, &destino);

	destino = (SDL_Rect) {100, 450, 0, 0};
	SDL_BlitSurface (maca, NULL, screen, &destino);

	destino = (SDL_Rect) {600, 450, 0, 0};
	SDL_BlitSurface (bomber, NULL, screen, &destino);

    botao = Verifica_Botao(12);
	if (botao)
	{
		Colore_Botao (botao);
	}

	Desenha_Texto22 ("NOVO JOGO", screen, SCREEN_W/2, 230);
	Desenha_Texto22 ("CARREGAR JOGO", screen, SCREEN_W/2, 290);
	Desenha_Texto22 ("INSTRUÇÕES", screen, SCREEN_W/2, 350);
	Desenha_Texto22 ("RECORDES", screen, SCREEN_W/2, 410);
	Desenha_Texto22 ("CRÉDITOS", screen, SCREEN_W/2, 470);
	Desenha_Texto22 ("SAIR", screen, SCREEN_W/2, 530);

	if (cascata == 1)
	{
		Desenha_Texto22 ("LINUX LOVER", screen, SCREEN_W/2+200, 230);
		Desenha_Texto22 ("MAC LOVER", screen, SCREEN_W/2+200, 290);
		Desenha_Texto22 ("WINDOWS LOVER", screen, SCREEN_W/2+200, 350);
		Desenha_Texto22 ("BONUS", screen, SCREEN_W/2+200, 410);
	}
	else if (cascata == 2)
	{
		Desenha_Texto22 ("TEMPO", screen, SCREEN_W/2+200, 410);
		Desenha_Texto22 ("PONTOS", screen, SCREEN_W/2+200, 470);
	}

	SDL_BlitSurface (cursor.img, NULL, screen, &(cursor.posicao));

	SDL_Flip (screen);
}

void Tela_LeNome ()
{
	SDL_Rect caixa = {SCREEN_W/2-100, 360, 200, 40};
    int botao;

    SDL_FillRect (screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));

    SDL_FillRect (screen, &caixa, SDL_MapRGB(screen->format, 255, 255, 0));

    caixa = (SDL_Rect) {SCREEN_W/2-98, 362, 196, 36};
    SDL_FillRect (screen, &caixa, SDL_MapRGB(screen->format, 100, 0, 255));


    botao = Verifica_Botao (5);
    if (botao)
    {
        if (botao != 1 && botao != 4)
            Colore_Botao (botao);
    }
    Desenha_Texto16 ("Digite seu nome:", screen, SCREEN_W/2, 325);
    Desenha_Texto22 (jogador.nome, screen, SCREEN_W/2, 380);
    //Desenha_Texto22 ("FÁCIL", screen, 160, 450);
    Desenha_Texto22 ("FACIL", screen, 320, 450);
    Desenha_Texto22 ("DIFÍCIL", screen, 480, 450);
    //Desenha_Texto22 ("QUALQUER", screen, 640, 450);
    Desenha_Texto22 ("MENU", screen, SCREEN_W/2, 550);
    SDL_BlitSurface (cursor.img, NULL, screen, &(cursor.posicao));

    SDL_Flip (screen);
}

void Tela_Carregar ()
{
    int botao, i, y;
    char string[50], v[15];

    SDL_FillRect (screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
    botao = Verifica_Botao (6);
    if (botao)
    {
        Colore_Botao (botao);
    }
    Desenha_Texto22 ("Escolha o jogo a ser carregado.", screen, SCREEN_W/2, 100);
    y = 220;
    for (i=0; i<SAVES_NUM; i++)
    {
        switch (saves[i].versao)
        {
            case LINUX:
                sprintf (v, "\"Linux Lover\"");
                break;
            case WINDOWS:
                sprintf (v, "\"Windows Lover\"");
                break;
            case MAC:
                sprintf (v, "\"Mac Lover\"");
                break;
            case BOMBER:
                sprintf (v, "\"Bonus\"");
                break;
            default:
                break;
        }
        if (saves[i].existe)
        {
            sprintf(string, "%s - Fase: %d, Versao: %s", saves[i].nome, saves[i].fase, v);
        }
        else
        {
            sprintf(string, "Vazio");
        }
        Desenha_Texto22 (string, screen, SCREEN_W/2, y);
        y += 60;
    }
    Desenha_Texto16 ("MENU", screen, SCREEN_W/2, 570);
    SDL_BlitSurface (cursor.img, NULL, screen, &(cursor.posicao));

    SDL_Flip (screen);
}

void Tela_Recordes_T ()
{
    int botao, y, i;
    char string[50];

    SDL_FillRect (screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
    botao = Verifica_Botao (2);
    if (botao)
    {
        Colore_Botao (botao);
    }
    Desenha_Texto22 ("Melhores Tempos", screen, SCREEN_W/2, 60);
	y = 160;
    for (i=0; i<RECORDES; i++)
    {
        sprintf (string, "%d - %s - %d:%2d:%2d", i+1, recordista_T[i].nome, recordista_T[i].tempo/360, (recordista_T[i].tempo/60)%60, recordista_T[i].tempo%60);
		Desenha_Texto22 (string, screen, SCREEN_W/2, y);
		y += 80;
	}
	Desenha_Texto16 ("Pontos", screen, 250, 565);
	Desenha_Texto16 ("Menu", screen, 550, 565);
    SDL_BlitSurface (cursor.img, NULL, screen, &(cursor.posicao));
    SDL_Flip (screen);
}

void Tela_Recordes_P ()
{
    int botao, y, i;
	char string[50];

	SDL_FillRect (screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
	botao = Verifica_Botao (2);
	if (botao)
	{
		Colore_Botao (botao);
	}
	Desenha_Texto22 ("Melhores Pontuações", screen, SCREEN_W/2, 60);
	y = 160;
	for (i=0; i<RECORDES; i++)
	{
		sprintf (string, "%d - %s - %li pts", i+1, recordista_T[i].nome, recordista_P[i].pontos);
		Desenha_Texto22 (string, screen, SCREEN_W/2, y);
		y += 80;
	}
	Desenha_Texto16 ("Tempos", screen, 250, 565);
	Desenha_Texto16 ("Menu", screen, 550, 565);
	SDL_BlitSurface (cursor.img, NULL, screen, &(cursor.posicao));
    SDL_Flip (screen);
}

void Tela_Instrucoes ()
{
    int botao;
    SDL_FillRect (screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
    SDL_BlitSurface (fundo, NULL, screen, NULL);
    botao = Verifica_Botao (1);
    if (botao)
    {
        Colore_Botao (botao);
    }
    Desenha_Texto16 ("Menu", screen, SCREEN_W/2, 565);

    SDL_BlitSurface (cursor.img, NULL, screen, &(cursor.posicao));
    SDL_Flip (screen);
}

void Tela_Creditos ()
{
    int botao;
    SDL_FillRect (screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));

    SDL_BlitSurface (fundo, NULL, screen, NULL);

    botao = Verifica_Botao (1);
    if (botao)
    {
        Colore_Botao (botao);
    }
	Desenha_Texto16 ("Menu", screen, 60, 575);

    SDL_BlitSurface (cursor.img, NULL, screen, &(cursor.posicao));
    SDL_Flip (screen);
}

void Tela_Pausa ()
{
    int botao;
    SDL_Rect fundo = {98, 48, 604, 504};
    Tela_Jogo ();
    SDL_FillRect (screen, &fundo, SDL_MapRGB(screen->format, 255, 255, 255));
    fundo = (SDL_Rect) {100, 50, 600, 500};
    SDL_FillRect (screen, &fundo, SDL_MapRGB(screen->format, 0, 0, 0));
    botao = Verifica_Botao (5);
    if (botao)
    {
        Colore_Botao (botao);
    }
    Desenha_Texto72 ("PAUSA", screen, SCREEN_W/2, 110);
    Desenha_Texto22 ("CONTINUAR", screen, SCREEN_W/2, 220);
    Desenha_Texto22 ("REINICIAR O JOGO", screen, SCREEN_W/2, 280);
    Desenha_Texto22 ("SALVAR", screen, SCREEN_W/2, 340);
    Desenha_Texto22 ("MENU", screen, SCREEN_W/2, 400);
    Desenha_Texto22 ("SAIR", screen, SCREEN_W/2, 460);
    SDL_BlitSurface (cursor.img, NULL, screen, &(cursor.posicao));
    SDL_Flip (screen);
}

void Tela_Save ()
{
    int botao, i, y;
    SDL_Rect fundo = {100, 50, 600, 500};

    Tela_Jogo ();
    SDL_FillRect (screen, &fundo, SDL_MapRGB(screen->format, 255, 0, 0));
    botao = Verifica_Botao (6);
    if (botao)
    {
        Colore_Botao (botao);
    }
    Desenha_Texto72 ("PAUSA", screen, SCREEN_W/2, 110);
    y = 220;
    for (i=0; i<SAVES_NUM; i++)
    {puts ("foi 1");
        Desenha_Texto22 (nome_saves[i], screen, SCREEN_W/2, y);puts ("foi 2");
        y += 60;
    }
    Desenha_Texto16 ("VOLTA", screen, 160, 482);

    SDL_BlitSurface (cursor.img, NULL, screen, &(cursor.posicao));
    SDL_Flip (screen);
}

void Tela_Jogo ()
{
	char texto[80];
    SDL_Rect destino;
    SDL_Rect painel = {SCREEN_W-PAINEL_LAT, 0, PAINEL_LAT, SCREEN_H};
    int i, j, k;

    SDL_BlitSurface (fundo, NULL, screen, NULL);
    SDL_FillRect (screen, &painel, SDL_MapRGB(screen->format, 0, 0, 0));
    destino = (SDL_Rect) {saida.j*LADO, saida.i*LADO, 0, 0};
    SDL_BlitSurface (porta, NULL, screen, &destino);

    for (k=0; k<6; k++)
    {
        if (inimigo[k].estado != FORA)
        {
            switch (inimigo[k].nivel)
            {
                case 1:
                    if (inimigo[k].estado == ATINGIDO)
                    {
                        SDL_SetAlpha(inimigo1, SDL_SRCALPHA|SDL_RLEACCEL, 128);
                    }
                    SDL_BlitSurface (inimigo1, &(inimigo[k].origem), screen, &(inimigo[k].destino));
                    if (inimigo[k].estado == ATINGIDO)
                    {
                        SDL_SetAlpha(inimigo1, SDL_SRCALPHA|SDL_RLEACCEL, 255);
                    }
                    break;
                case 2:
                    if (inimigo[k].estado == ATINGIDO)
                    {
                        SDL_SetAlpha(inimigo2, SDL_SRCALPHA|SDL_RLEACCEL, 128);
                    }
                    SDL_BlitSurface (inimigo2, &(inimigo[k].origem), screen, &(inimigo[k].destino));
                    if (inimigo[k].estado == ATINGIDO)
                    {
                        SDL_SetAlpha(inimigo2, SDL_SRCALPHA|SDL_RLEACCEL, 255);
                    }
                    break;
                case 3:
                    if (inimigo[k].estado == ATINGIDO)
                    {
                        SDL_SetAlpha(inimigo3, SDL_SRCALPHA|SDL_RLEACCEL, 128);
                    }
                    SDL_BlitSurface (inimigo3, &(inimigo[k].origem), screen, &(inimigo[k].destino));
                    if (inimigo[k].estado == ATINGIDO)
                    {
                        SDL_SetAlpha(inimigo3, SDL_SRCALPHA|SDL_RLEACCEL, 255);
                    }
                    break;
                case 4:
                    if (inimigo[k].estado == ATINGIDO)
                    {
                        SDL_SetAlpha(inimigo4, SDL_SRCALPHA|SDL_RLEACCEL, 128);
                    }
                    SDL_BlitSurface (inimigo4, &(inimigo[k].origem), screen, &(inimigo[k].destino));
                    if (inimigo[k].estado == ATINGIDO)
                    {
                        SDL_SetAlpha(inimigo4, SDL_SRCALPHA|SDL_RLEACCEL, 255);
                    }
                    break;
                case 5:
                    if (inimigo[k].estado == ATINGIDO)
                    {
                        SDL_SetAlpha(inimigo5, SDL_SRCALPHA|SDL_RLEACCEL, 128);
                    }
                    SDL_BlitSurface (inimigo5, &(inimigo[k].origem), screen, &(inimigo[k].destino));
                    if (inimigo[k].estado == ATINGIDO)
                    {
                        SDL_SetAlpha(inimigo5, SDL_SRCALPHA|SDL_RLEACCEL, 255);
                    }
                    break;
                case 6:
                    if (inimigo[k].estado == ATINGIDO)
                    {
                        SDL_SetAlpha(inimigo5, SDL_SRCALPHA|SDL_RLEACCEL, 128);
                    }
                    SDL_BlitSurface (inimigo5, &(inimigo[k].origem), screen, &(inimigo[k].destino));
                    if (inimigo[k].estado == ATINGIDO)
                    {
                        SDL_SetAlpha(inimigo5, SDL_SRCALPHA|SDL_RLEACCEL, 255);
                    }
                    break;
                default:
                    break;
            }
        }
    }

    for (i=0; i<GRADE_H; i++)
    {
        for (j=0; j<GRADE_W; j++)
        {
            destino = (SDL_Rect) {j*LADO, i*LADO, LADO, LADO};

            switch (mapa[i][j])
            {
                case 0:
                    break;
                case 1:
                    SDL_BlitSurface (bloco_ind, NULL, screen, &destino);
                    break;
                case 2:
                    SDL_BlitSurface (bloco_dest, NULL, screen, &destino);
                    break;
                case 4:
                    SDL_BlitSurface (bomba, NULL, screen, &destino);
                    break;
                case 5:
                    SDL_BlitSurface (bonus1, NULL, screen, &destino);
                    break;
                case 6:
                    SDL_BlitSurface (bonus2, NULL, screen, &destino);
                    break;
                case 7:
                    SDL_BlitSurface (explosao_centro, NULL, screen, &destino);
                    break;
                case 8:
                    SDL_BlitSurface (explosao_vert, NULL, screen, &destino);
                    break;
                case 9:
                    SDL_BlitSurface (explosao_hor, NULL, screen, &destino);
                    break;
                default:
                    break;
            }
        }
    }
    sprintf (texto, "Fase: %d - %s", fase, jogador.nome);
    Desenha_Texto16 (texto, screen, 700, 10);
    Desenha_Texto16 ("Pontos:", screen, 700, 80);
    sprintf (texto, "%li pts", jogador.pontos);
    Desenha_Texto16 (texto, screen, 700, 100);
    sprintf (texto, "Tempo: %d:%2d:%2d", jogador.tempo/360, (jogador.tempo/60)%60, jogador.tempo%60);
    Desenha_Texto16 (texto, screen, 700, 150);
    sprintf (texto, "Vidas: %d", vidas);
    Desenha_Texto16 (texto, screen, 700, 250);
    sprintf (texto, "Bombas: %d", max_bombas);
    Desenha_Texto16 (texto, screen, 700, 350);
    sprintf (texto, "Alcance: %d", range);
    Desenha_Texto16 (texto, screen, 700, 380);
    SDL_BlitSurface (personagem.img, &(personagem.origem), screen, &(personagem.destino));

    if (estado == JOGO) SDL_Flip(screen);
}

void Tela_GameOver ()
{
    SDL_FillRect (screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
    botao = Verifica_Botao (2);
	if (botao)
	{
		Colore_Botao (botao);
	}
	Desenha_Texto22 ("MENU", screen, 275, 480);
	Desenha_Texto22 ("SAIR", screen, 525, 480);
	if (venceu) Desenha_Texto72 ("VOCÊ VENCEU!!!", screen, SCREEN_W/2, 200);
	else Desenha_Texto72 ("VOCÊ PERDEU!!!", screen, SCREEN_W/2, 200);
	if (fez_recorde)
	{
	    Desenha_Texto22 ("PARABÉNS! VOCÊ FEZ UM NOVO RECORDE!", screen, 400, SCREEN_H/2);
	}
	SDL_BlitSurface (cursor.img, NULL, screen, &(cursor.posicao));
	SDL_Flip (screen);
}

void Colore_Botao (int botao)
{
    botao--;

	if (cascata == 1 && estado == MENU)
	{
		SDL_FillRect (screen, &botoes[0], SDL_MapRGB(screen->format, 0, 128, 0));
		if (botao < 10)
		{
		    SDL_FillRect (screen, &botoes[botao], SDL_MapRGB(screen->format, 0, 128, 0));
		}
	}
	else if (cascata == 2 && estado == MENU)
	{
		SDL_FillRect (screen, &botoes[3], SDL_MapRGB(screen->format, 0, 128, 0));
		if (botao > 9)
		{
		    SDL_FillRect (screen, &botoes[botao], SDL_MapRGB(screen->format, 0, 128, 0));
		}
	}
	else
	{
	    SDL_FillRect (screen, &botoes[botao], SDL_MapRGB(screen->format, 0, 128, 0));
	}
}

void Desenha_Texto22 (char* texto, SDL_Surface* dst, int x, int y)
{
    int x1, y1;
    SDL_Rect dst_rect;
	SDL_Color cor = {255, 255, 255};

	SDL_Surface* src = TTF_RenderText_Blended (my_font22, texto, cor);

	x1 = x-(src->w)/2;
	y1 = y-(src->h)/2;
	dst_rect = (SDL_Rect) {x1, y1, 0, 0};

	SDL_BlitSurface (src, NULL, dst, &dst_rect);

    SDL_FreeSurface (src);
}

void Desenha_Texto16 (char* texto, SDL_Surface* dst, int x, int y)
{
    int x1, y1;
	SDL_Color cor = {255, 255, 255};

	SDL_Surface* src = TTF_RenderText_Blended (my_font16, texto, cor);
    x1 = x-src->w/2;
	y1 = y-src->h/2;
	SDL_Rect dst_rect = {x1, y1, 0, 0};

	SDL_BlitSurface (src, NULL, dst, &dst_rect);

    SDL_FreeSurface (src);
}

void Desenha_Texto72 (char* texto, SDL_Surface* dst, int x, int y)
{
    int x1, y1;
	SDL_Color cor = {255, 255, 255};

	SDL_Surface* src = TTF_RenderText_Blended (my_font72, texto, cor);
	x1 = x-src->w/2;
	y1 = y-src->h/2;
	SDL_Rect dst_rect = {x1, y1, 0, 0};

	SDL_BlitSurface (src, NULL, dst, &dst_rect);

    SDL_FreeSurface (src);
}
