#include "includes.h"

void Move_Personagem ()
{
    int n;

    if (personagem.passo % 2)
    {
        personagem.origem.x = 40;
    }
    else
    {
        personagem.origem.x = 80;
    }

    if (personagem.j > personagem.destino.x/LADO)
    {
        personagem.destino.x += INCX_DEFAULT;
        personagem.origem.y = 40;
    }
    else if (personagem.j < personagem.destino.x/LADO || (personagem.j == personagem.destino.x/LADO && personagem.destino.x%LADO))
    {
        personagem.destino.x -= INCX_DEFAULT;
        personagem.origem.y = 80;
    }
    else if (personagem.i < personagem.destino.y/LADO || (personagem.i == personagem.destino.y/LADO && personagem.destino.y%LADO))
    {
        personagem.destino.y -= INCY_DEFAULT;
        personagem.origem.y = 120;
    }
    else if (personagem.i > personagem.destino.y/LADO)
    {
        personagem.destino.y += INCY_DEFAULT;
        personagem.origem.y = 0;
    }
    else
    {
        personagem.origem.x = 0;
    }

    if (!(personagem.destino.x % LADO) && !(personagem.destino.y % LADO))
    {
        personagem.movendo = 0;
    }
    if (personagem.i == saida.i && personagem.j == saida.j && !venceu)
    {
        venceu = 1;
        tempo1 = ciclo;
        if (fase == 2)
        {
            jogador.pontos += vidas*5000;
            n = Eh_RecordeT ();
            if (n != -1)
            {
                Salva_RecordeT (n);
                fez_recorde = 1;
            }
            n = Eh_RecordeP ();
            if (n != -1)
            {
                Salva_RecordeP (n);
                fez_recorde = 1;
            }
            fase = 0;
            vidas = 3;
            jogador.pontos = 0;
            jogador.tempo = 0;
            estado = GAMEOVER;
            Mix_PlayMusic (vitoria, -1);
            Define_Botoes ();
        }
    }
}

void Reinicia_Jogo ()
{
    vidas = 3;
    existe_bomba = 0;
    inicio_fila = fim_fila;
    inicio_fila2 = fim_fila2;
    fase = 0;
    Carrega_Fase_Seguinte (0, NULL);
}

void Salva_Jogo (int slot)
{
    int i;

    saves[slot].existe = 1;
    saves[slot].fase = fase;
    saves[slot].vidas = vidas;
    saves[slot].tempo = jogador.tempo;
    saves[slot].dificuldade = dificuldade;
    saves[slot].pontos = jogador.pontos;
    saves[slot].versao = jogador.versao;
    for (i=0; i<=strlen(jogador.nome); i++)
    {
        saves[slot].nome[i] = jogador.nome[i];
    }
    estado = PAUSA;
    Define_Botoes ();
}

void Explode_Bomba ()
{
    int i, j;
    int stop1 = 0, stop2 = 0, stop3 = 0, stop4  = 0;
    i = fila[inicio_fila].i;
    j = fila[inicio_fila].j;

    if (existe_bomba && ((SDL_GetTicks() - fila[inicio_fila].planted) >= 2500 || mapa[i][j] == 8 || mapa[i][j] == 9))
    {
        Remove_Bomba_Fila ();

        for (i=1; i<=range; i++)
        {
            if (!stop1)
            {
                stop1 = Explode_Espaco (bomb[0].i-i, bomb[0].j, 'v');
            }
            if (!stop2)
            {
                stop2 = Explode_Espaco (bomb[0].i, bomb[0].j-i, 'h');
            }
            if (!stop3)
            {
                stop3 = Explode_Espaco (bomb[0].i+i, bomb[0].j, 'v');
            }
            if (!stop4)
            {
                stop4 = Explode_Espaco (bomb[0].i, bomb[0].j+i, 'h');
            }
        }

        mapa[bomb[0].i][bomb[0].j] = 7;
        SDL_AddTimer (500, Explosao_fim, NULL);
        existe_bomba--;
        Add_Bomba_Fila2 ();
    }
}

Uint32 Explosao_fim (Uint32 interval, void *param)
{
    int i;

    Remove_Bomba_Fila2 ();

    mapa[bomb[1].i][bomb[1].j] = 0;

    for (i=1; i<=range; i++)
    {
        Limpa_Espaco (bomb[1].i-i, bomb[1].j, 'h');
    }
    for (i=1; i<=range; i++)
    {
        Limpa_Espaco (bomb[1].i, bomb[1].j-i, 'v');
    }
    for (i=1; i<=range; i++)
    {
        Limpa_Espaco (bomb[1].i+i, bomb[1].j, 'h');
    }
    for (i=1; i<=range; i++)
    {
        Limpa_Espaco (bomb[1].i, bomb[1].j+i, 'v');
    }
    return 0;
}

int Explode_Espaco (int i, int j, char dir)
{
    int stop = 0;

    if (mapa[i][j] == 1 || mapa[i][j] == 2)
    {
        stop = 1;
        if (mapa[i][j] == 2)
        {
            jogador.pontos += 50;
        }
    }
    if ((mapa[i][j] == 8 && dir == 'h') || (mapa[i][j] == 9 && dir == 'v'))
    {
        mapa[i][j] = 7;
    }
    else if (mapa[i][j] != 1 && mapa[i][j] != 7 && !Bonus (i, j))
    {
        if (dir == 'v')
        {
            mapa[i][j] = 8;
        }
        else
        {
            mapa[i][j] = 9;
        }
    }
    if (stop)
    {
        return 1;
    }
    return 0;
}

void Limpa_Espaco (int i, int j, char dir)
{
    if (mapa[i][j] == 9)
    {
        mapa[i][j] = 0;
    }
    else if (mapa[i][j] == 8)
    {
        mapa[i][j] = 0;
    }
    else if (mapa[i][j] == 7 && !(bomb[1].i == i && bomb[1].j == j))
    {
        if (dir == 'v')
        {
            mapa[i][j] = 8;
        }
        else
        {
            mapa[i][j] = 9;
        }
    }
}

void Add_Bomba_Fila (int i, int j)
{
    Mix_PlayChannel (-1, planta_bomba, 0);
    fila[fim_fila].i = personagem.i;
    fila[fim_fila].j = personagem.j;
    fila[fim_fila].planted = SDL_GetTicks();
    existe_bomba++;
    fim_fila++;
    if (fim_fila > 8)
    {
        fim_fila = 0;
    }
}

void Remove_Bomba_Fila ()
{
    Mix_PlayChannel(-1, explosao, 0);
    bomb[0] = (BOMBA) fila[inicio_fila];
    inicio_fila ++;
    if (inicio_fila > 8)
    {
        inicio_fila = 0;
    }
}

void Add_Bomba_Fila2 ()
{
    fila2[fim_fila2] = (BOMBA) bomb[0];
    fim_fila2++;
    if (fim_fila2 > 8)
    {
        fim_fila2 = 0;
    }
}

void Remove_Bomba_Fila2 ()
{
    bomb[1] = (BOMBA) fila2[inicio_fila2];
    inicio_fila2 ++;
    if (inicio_fila2 > 8)
    {
        inicio_fila2 = 0;
    }
}

int Bonus (int i, int j)
{
    int a;

    a = rand() % 100 + 1;

    if (mapa[i][j] == 2)
    {
        if (a < 3 && range < 5)
        {
            mapa[i][j] = 5;
            return 1;
        }
        else if (a < 5 && max_bombas < 5)
        {
            mapa[i][j] = 6;
            return 1;
        }
    }
    return 0;
}

void Verifica_Bonus ()
{
    if (mapa[personagem.i][personagem.j] == 5)
    {
        range++;
        mapa[personagem.i][personagem.j] = 0;
    }
    else if (mapa[personagem.i][personagem.j] == 6)
    {
        max_bombas++;
        mapa[personagem.i][personagem.j] = 0;
    }
}

void Reinicia_Fase ()
{
    existe_bomba = 0;
    inicio_fila = fim_fila;
    inicio_fila2 = fim_fila2;
    if (!vidas)
    {
        fez_recorde = 0;
        estado = GAMEOVER;
        Mix_PlayMusic (derrota, -1);
        Define_Botoes ();
        fase = 0;
        vidas = 3;
        jogador.tempo = 0;
        jogador.pontos = 0;
    }
    else
    {
        fase--;
        Carrega_Fase_Seguinte (0, NULL);
        personagem.estado = VIVO;
    }
}

void Move_Inimigo (int n)
{
    switch (inimigo[n].nivel)
    {
        case 1:
            if (ciclo % 3)
                return;
            Anda_Inimigo (n);
            break;
        case 2:
            if (ciclo % 2)
                return;
            Anda_Inimigo (n);
            break;
        case 3:
            if (ciclo % 3)
                return;
            Anda_Inimigo (n);
            break;
        case 4:
            if (ciclo % 3)
                return;
            Anda_Inimigo (n);
            break;
        case 5:
            if (ciclo % 2)
                return;
            Anda_Inimigo (n);
            break;
        default:
            break;
    }
}

void Anda_Inimigo (int n)
{
    if (inimigo[n].j > inimigo[n].destino.x/LADO)
    {
        inimigo[n].destino.x += INCX_MONSTROS;
        inimigo[n].origem.y = 40;
    }
    else if (inimigo[n].j < inimigo[n].destino.x/LADO || (inimigo[n].j == inimigo[n].destino.x/LADO && inimigo[n].destino.x%LADO))
    {
        inimigo[n].destino.x -= INCX_MONSTROS;
        inimigo[n].origem.y = 80;
    }
    else if (inimigo[n].i < inimigo[n].destino.y/LADO || (inimigo[n].i == inimigo[n].destino.y/LADO && inimigo[n].destino.y%LADO))
    {
        inimigo[n].destino.y -= INCY_MONSTROS;
        inimigo[n].origem.y = 120;
    }
    else if (inimigo[n].i > inimigo[n].destino.y/LADO)
    {
        inimigo[n].destino.y += INCY_MONSTROS;
        inimigo[n].origem.y = 0;
    }
    else
    {
        inimigo[n].origem.x = 0;
    }

    if (!(inimigo[n].destino.x % LADO) && !(inimigo[n].destino.y % LADO))
    {
        inimigo[n].movendo = 0;
    }
    else
    {
        inimigo[n].movendo = 1;
    }
}


void Muda_ij_Inimigo (int n)
{
    int dir;

    if (abs(inimigo[n].i - inimigo[n].destino.y/LADO) > 0 || abs(inimigo[n].j - inimigo[n].destino.x/LADO) > 0)
        return;

    switch (dificuldade)
    {
        case FACIL:
            do
            {
                dir = rand()%5-2;
            } while (!dir || Verifica_Dir (inimigo[n].i, inimigo[n].j, n, dir) || (Verifica_Dir (inimigo[n].i, inimigo[n].j, n, -dir) && dir == -inimigo[n].dir));
            break;
        case MEDIO:
            if (rand () % 2)
            {
                dir = Diminui_Distancia (n);
            }
            else
            {
                do
                {
                    inimigo[n].dir = rand()%5-2;
                } while (!dir || Verifica_Dir (inimigo[n].i, inimigo[n].j, n, dir) || (Verifica_Dir (inimigo[n].i, inimigo[n].j, n, dir) && dir == -inimigo[n].dir));
            }
            break;
        case DIFICIL:
            dir = Diminui_Distancia (n);
            break;
        default:
            break;
    }
    switch (dir)
    {
        case -1:
            inimigo[n].i++;
            break;
        case 1:
            inimigo[n].i--;
            break;
        case -2:
            inimigo[n].j++;
            break;
        case 2:
            inimigo[n].j--;
            break;
    }

}

int Verifica_Dir (int i, int j, int n, int dir)
{
    switch (dir)
    {
        case -1:
            i++;
            break;
        case 1:
            i--;
            break;
        case -2:
            j++;
            break;
        case 2:
            j--;
            break;
    }
    if (mapa[i][j] != 1 && mapa[i][j] != 2 && mapa[i][j] != 4)
    {
        return 0;
    }
    return 1;
}

void Verifica_Mortes ()
{
    int n;
    if (personagem.estado == VIVO && (mapa[personagem.i][personagem.j] == 7 || mapa[personagem.i][personagem.j] == 8 || mapa[personagem.i][personagem.j] == 9))
    {
        personagem.estado = MORTO;
        personagem.atingido = ciclo;
        vidas--;
    }
    for (n=0; n<6; n++)
    {
        if (personagem.estado == VIVO && personagem.i == inimigo[n].i && personagem.j == inimigo[n].j && (inimigo[n].estado == VIVO || inimigo[n].estado == ATINGIDO))
        {
            personagem.estado = MORTO;
            personagem.atingido = ciclo;
            vidas--;
        }
        if (Inimigo_Morreu (n))
        {
			Mata_Inimigo (n);
		}
    }
}

void Mata_Inimigo (int n)
{
    if (inimigo[n].estado != FORA && inimigo[n].estado != MORTO && ciclo-inimigo[n].atingido > 15)
    {
        inimigo[n].vidas--;
        if (!inimigo[n].vidas)
        {
            inimigo[n].estado = MORTO;
            inimigo[n].atingido = ciclo;
            jogador.pontos += inimigo[n].nivel * 150;
            inimigo[n].origem = (SDL_Rect) {120, 0, 40, 40};
        }
        else
        {
            inimigo[n].estado = ATINGIDO;
            inimigo[n].atingido = ciclo;
        }
    }
}

void Resolve_Mortos ()
{
    int i;

    for (i=0; i<6; i++)
    {
        if (ciclo-inimigo[i].atingido == 15 && inimigo[i].vidas > 0)
        {
            inimigo[i].estado = VIVO;
        }
        else if (ciclo - inimigo[i].atingido == 15 && inimigo[i].vidas == 0)
        {
            inimigo[i].estado = FORA;
        }
    }
    if (personagem.estado == MORTO && ciclo-personagem.atingido == 20)
    {
        Reinicia_Fase ();
    }
}

void Salva_Dados ()
{
    FILE *arq;

    if (!(arq = fopen ("jogo.save", "w")))
    {
        puts ("Nao foi possivel salvar dados.");
    }
    fwrite (saves, sizeof(saves), 1, arq);
    fclose (arq);

    arq = fopen ("recordes_t.data", "w");
    fclose (arq);

    arq = fopen ("recordes_p.data", "w");
    fclose (arq);
}

int Inimigo_Morreu (int n)
{
    int x, y;

    if (inimigo[n].i != inimigo[n].destino.y/LADO)
    {
        x = inimigo[n].i - 1;
        y = inimigo[n].j;
        if (mapa[x][y] == 8 || mapa[x][y] == 7 || mapa[x+1][y] == 8 || mapa[x+1][y] == 7)
        {
            return 1;
        }
        if (mapa[x][y] == 9)
        {
            if (inimigo[n].destino.y < LADO*mapa[x+1][y] - 14 || inimigo[n].destino.y + inimigo[n].destino.h > LADO*mapa[x+1][y] + 14)
            {
                return 1;
            }
        }
    }
    else if (inimigo[n].j != inimigo[n].destino.x/LADO)
    {
        x = inimigo[n].i;
        y = inimigo[n].j - 1;
        if (mapa[x][y] == 9 || mapa[x][y] == 7 ||mapa[x][y+1] == 9 || mapa[x][y+1] == 7)
        {
            return 1;
        }
        if (mapa[x][y] == 8)
        {
            if (inimigo[n].destino.x < LADO*mapa[x][y+1] - 14 || inimigo[n].destino.x + inimigo[n].destino.w > LADO*mapa[x][y+1] + 14)
            {
                return 1;
            }
        }
    }
    else if (inimigo[n].destino.x%LADO)
    {
        x = inimigo[n].i;
        y = inimigo[n].j;
        if (mapa[x][y] == 9 || mapa[x][y] == 7 ||mapa[x][y+1] == 9 || mapa[x][y+1] == 7)
        {
            return 1;
        }
        if (mapa[x][y] == 8)
        {
            if (inimigo[n].destino.x < LADO*mapa[x][y+1] - 14 || inimigo[n].destino.x + inimigo[n].destino.w > LADO*mapa[x][y+1] + 14)
            {
                return 1;
            }
        }
    }
    else if (inimigo[n].destino.y%LADO)
    {
        x = inimigo[n].i;
        y = inimigo[n].j;
        if (mapa[x][y] == 8 || mapa[x][y] == 7 || mapa[x+1][y] == 8 || mapa[x+1][y] == 7)
        {
            return 1;
        }
        if (mapa[x][y] == 9)
        {
            if (inimigo[n].destino.y < LADO*mapa[x+1][y] - 14 || inimigo[n].destino.y + inimigo[n].destino.h > LADO*mapa[x+1][y] + 14)
            {
                return 1;
            }
        }
    }
    else
    {
        x = inimigo[n].i;
        y = inimigo[n].j;
        if (mapa[x][y] == 7 || mapa[x][y] == 8 || mapa[x][y] == 9)
        {
            return 1;
        }
    }
    return 0;
}

void Movimenta_Inimigo ()
{
    int i;

    if (!venceu)
    {
        for (i=0; i<6; i++)
        {
            if (inimigo[i].estado != MORTO && inimigo[i].estado != FORA)
            {
                if ((!(Verifica_Dir (inimigo[i].i, inimigo[i].j, i, inimigo[i].dir) || ciclo % 100) && (!inimigo[i].movendo)) || (!inimigo[i].movendo))
                {
                    Muda_ij_Inimigo (i);
                }
                Move_Inimigo (i);
            }
        }
    }
}

int Eh_RecordeT()
{
	int i;

	for (i=0; i<RECORDES; i++)
	{
		if (jogador.tempo < recordista_T[i].tempo || !recordista_T[i].tempo)
		{
			return i;
		}
	}
	return -1;
}

int Eh_RecordeP()
{
	int i;

	for (i=0; i<RECORDES; i++)
	{
		if (jogador.pontos > recordista_P[i].pontos || !recordista_P[i].pontos)
		{
			return i;
		}
	}
	return -1;
}

void Salva_RecordeP(int pos_p)
{
	JOGADOR temp1, temp2;
	int i;

	temp1 = (JOGADOR) jogador;
	for(i=pos_p; i<RECORDES; i++)
	{
		temp2 = (JOGADOR) recordista_P[i];
		recordista_P[i] = (JOGADOR) temp1;
		temp1 = (JOGADOR) temp2;
	}
}

void Salva_RecordeT(int pos_t)
{
	JOGADOR temp1, temp2;
	int i;

	temp1 = (JOGADOR) jogador;
	for(i=pos_t; i<RECORDES; i++)
	{
		temp2 = (JOGADOR) recordista_T[i];
		recordista_T[i] = (JOGADOR) temp1;
		temp1 = (JOGADOR) temp2;
	}
}

int Diminui_Distancia (int n)
{
    int dir;

    if (inimigo[n].i < personagem.i)
    {
        dir = -1;
        if (!Verifica_Dir (inimigo[n].i, inimigo[n].j, n, dir))
        {
            return dir;
        }
    }
    else if (inimigo[n].i > personagem.i)
    {
        dir = 1;
        if (!Verifica_Dir (inimigo[n].i, inimigo[n].j, n, dir))
        {
            return dir;
        }
    }
    else if (inimigo[n].j < personagem.j)
    {
        dir = -2;
        if (!Verifica_Dir (inimigo[n].i, inimigo[n].j, n, dir))
        {
            return dir;
        }
    }
    else if (inimigo[n].j > personagem.j)
    {
        dir = 2;
        if (!Verifica_Dir (inimigo[n].i, inimigo[n].j, n, dir))
        {
            return dir;
        }
    }
    do
    {
        dir = rand()%5-2;
    } while (!dir || Verifica_Dir (inimigo[n].i, inimigo[n].j, n, dir) || (Verifica_Dir (inimigo[n].i, inimigo[n].j, n, -dir) && dir == -inimigo[n].dir));
    return dir;
}


