#include "IncludeBomber.h"

void Init_Surfaces(void)
{
	screen = SDL_SetVideoMode(SCREEN_W, SCREEN_H, BITD, SDL_SWSURFACE);
	if(!screen)
	{
		printf("Nao foi possivel carregar a tela\n");
		exit(1);
	}
    surf_chao = SDL_LoadBMP("imagens/chao.bmp");
    if(!surf_chao)
    {
        printf("Nao foi possivel carregar chao.bmp\n");
        quit = 1;
    }
    surf_parede = SDL_LoadBMP("imagens/parede.bmp");
    if(!surf_parede)
    {
        printf("Nao foi possivel carregar parede.bmp\n");
        quit = 1;
    }
    surf_caixa = SDL_LoadBMP("imagens/caixa.bmp");
    if(!surf_caixa)
    {
        printf("Nao foi possivel carregar caixa.bmp\n");
        quit = 1;
    }
    surf_bomberman = SDL_LoadBMP("imagens/bomberman_anim.bmp");
    SDL_SetColorKey(surf_bomberman, SDL_SRCCOLORKEY, SDL_MapRGB(surf_bomberman->format, 255, 0, 255));
    if(!surf_bomberman)
    {
        printf("Nao foi possivel carregar bomberman_anim.bmp\n");
        quit = 1;
    }
    surf_bomba = SDL_LoadBMP("imagens/bomba.bmp");
    if(!surf_bomba)
    {
        printf("Nao foi possivel carregar bomba.bmp\n");
        quit = 1;
    }
    surf_fogov = SDL_LoadBMP("imagens/fogov.bmp");
    if(!surf_fogov)
    {
        printf("Nao foi possivel carregar fogov.bmp\n");
        quit = 1;
    }
    surf_fogoh = SDL_LoadBMP("imagens/fogoh.bmp");
    if(!surf_fogoh)
    {
        printf("Nao foi possivel carregar fogoh.bmp\n");
        quit = 1;
    }
    surf_fogoc = SDL_LoadBMP("imagens/fogoc.bmp");
    if(!surf_fogoc)
    {
        printf("Nao foi possivel carregar fogoc.bmp\n");
        quit = 1;
    }
	surf_gameover = IMG_Load("imagens/gameover.jpg");
	if(!surf_gameover)
	{
		printf("Nao foi possivel carregar gameover.jpg\n");
		quit = 1;
	}
	surf_ibomba = IMG_Load("imagens/item_bomba.bmp");
	if(!surf_ibomba)
	{
	    printf("Nao foi possivel carregar item_bomba.bmp\n");
	    quit = 1;
	}
	surf_ipatins = SDL_LoadBMP("imagens/item_patins.bmp"); /* alterar imagem do patins */
	if(!surf_ipatins)
	{
	    printf("Nao foi possivel carregar item_patins.bmp\n");
	    quit = 1;
	}
	surf_ifogo = SDL_LoadBMP("imagens/item_fogo.bmp");/* alterar imagem do ifogo */
	if(!surf_ifogo)
	{
	    printf("Nao foi possivel carregar item_fogo.bmp\n");
	    quit = 1;
	}
	surf_ivida = SDL_LoadBMP("imagens/item_vida.bmp");/* alterar imagem da vida */
	if(!surf_ipatins)
	{
	    printf("Nao foi possivel carregar item_vida.bmp\n");
	    quit = 1;
	}
	tela_menu = IMG_Load("imagens/title_screen.png");
	if(!tela_menu)
	{
	    printf("Nao foi possivel carregar title_screen.png\n");
	    quit = 1;
	}
	surf_saida = SDL_LoadBMP("imagens/saida.bmp");
	if(!surf_saida)
	{
	    printf("Nao foi possivel carregar saida.bmp\n");
	    quit = 1;
	}
	surf_infos = SDL_LoadBMP("imagens/infos.bmp");
	if(!surf_infos)
	{
	    printf("Nao foi possivel carregar infos.bmp\n");
	    quit = 1;
	}
	surf_bomberman_morrendo = SDL_LoadBMP("imagens/bomberman_morrendo.bmp");
	SDL_SetColorKey(surf_bomberman_morrendo, SDL_SRCCOLORKEY, SDL_MapRGB(surf_bomberman_morrendo->format, 255, 0, 255));
	if(!surf_bomberman_morrendo)
	{
	    printf("Nao foi possivel carregar bomberman_morrendo.bmp");
	    quit = 1;
	}
	surf_nome = SDL_LoadBMP("imagens/nome.bmp");
	if(!surf_nome)
	{
	    printf("Nao foi possivel carregar nome.bmp");
	    quit = 1;
	}
	surf_highscore = IMG_Load("imagens/highscore.gif");
	if(!surf_highscore)
	{
	    printf("Nao foi possive carregar highscore.gif");
	    quit = 1;
	}
	surf_som_ok = IMG_Load("imagens/som_ok.bmp");
	SDL_SetColorKey(surf_som_ok, SDL_SRCCOLORKEY, SDL_MapRGB(surf_som_ok->format, 255, 0, 255));
	if(!surf_som_ok)
	{
	    printf("Nao foi possivel carregar som_ok.bmp");
	    quit = 1;
	}
	surf_som_des = IMG_Load("imagens/som_des.bmp");
	SDL_SetColorKey(surf_som_des, SDL_SRCCOLORKEY, SDL_MapRGB(surf_som_des->format, 255, 0, 255));
	if(!surf_som_des)
	{
	    printf("Nao foi possivel carregar som_des.bmp");
	    quit = 1;
	}

	surf_monstro = IMG_Load("imagens/monstros.bmp");
    SDL_SetColorKey(surf_monstro, SDL_SRCCOLORKEY, SDL_MapRGB(surf_monstro->format, 255, 0, 255));
    if(!surf_monstro)
    {
        printf("Nao foi possivel carregar monstros.bmp");
        quit = 1;
    }

    tela_abertura = SDL_LoadBMP("imagens/abertura.bmp");
    if(!tela_abertura)
    {
        printf("Nao foi possivel carregar abertura.bmp");
    }
	
	surf_ovo = IMG_Load("imagens/ovo.bmp");
	SDL_SetColorKey(surf_ovo, SDL_SRCCOLORKEY, SDL_MapRGB(surf_ovo->format, 255, 0, 255));
	if(!surf_ovo)
	{
		printf("Nao foi possivel carregar ovo.png");
		quit = 1;
	}
}

void Init_Cenario(void)
{
    int i, j, x, y;

    //Inicializando a grade
    for(i=0; i<MAPA_W/TILE_DIM; i++)
        for(j=0; j<MAPA_H/TILE_DIM; j++)
        {
            cenario[i][j].dest = (SDL_Rect) {i*TILE_DIM , j*TILE_DIM, TILE_DIM, TILE_DIM };
            cenario[i][j].superficie = surf_chao;
            cenario[i][j].tipo = CHAO;
        }

    //Botando Paredes
    for(i=0; i<MAPA_W/TILE_DIM; i++)
        for(j=0; j<MAPA_H/TILE_DIM; j++)
        {
            //borda
            if(i==0 || i==MAPA_W/TILE_DIM - 1 || j==0 || j==MAPA_H/TILE_DIM - 1)
            {
                cenario[i][j].superficie = surf_parede;
                cenario[i][j].tipo = PAREDE;
            }
            else if(i%2==0 && j%2==0) //centrais
            {
                cenario[i][j].superficie = surf_parede;
                cenario[i][j].tipo = PAREDE;
            }
        }

    //Botando Caixas aleatoriamente
    for(i=0; i<NCAIXAS; i++)
    {
        do
        {
            x = rand()%(MAPA_W/TILE_DIM);
            y = rand()%(MAPA_H/TILE_DIM);
        }while( cenario[x][y].tipo != CHAO || (x==1 && y == 1) || (x==1 && y==2) || (x==2 && y==1) );

        cenario[x][y].superficie = surf_caixa;
        cenario[x][y].tipo = CAIXA;
    }

    //Botando Saida no canto inferior esquerdo
    do
    {
        x = rand()%(MAPA_W/TILE_DIM);
        y = rand()%(MAPA_H/TILE_DIM);
    }while( cenario[x][y].tipo != CHAO || x < MAPA_W/(TILE_DIM*2) || y < MAPA_H/(TILE_DIM*2));
    cenario[x][y].superficie = surf_caixa;
    cenario[x][y].tipo = SAIDA_FECHADA;
}

void Init_Sons (void)
{
	/*CARREGANDO EFEITOS SONOROS*/

	explosao = Mix_LoadWAV( "musicas_efeitos/explosao.wav" );
    if(explosao == NULL)
        printf("Uma musica nao pode ser carregada");
	novoitem = Mix_LoadWAV( "musicas_efeitos/novoitem.wav" );
	if(novoitem == NULL)
		printf("Uma musica nao pode ser carregada");
	morte = Mix_LoadWAV( "musicas_efeitos/morte.wav" );
	if(morte == NULL)
		printf("Uma musica nao pode ser carregada");
	saida = Mix_LoadWAV( "musicas_efeitos/saida.wav" );
	if(saida == NULL)
		printf("Uma musica nao pode ser carregada");
	click = Mix_LoadWAV( "musicas_efeitos/click.wav" );
	if(click == NULL)
		printf("Uma musica nao pode ser carregada");
	seleciona = Mix_LoadWAV( "musicas_efeitos/seleciona.wav" );
	if(seleciona == NULL)
		printf("Uma musica nao pode ser carregada");

	/*CARREGANDO MUSICAS*/

	musica_highscore = Mix_LoadMUS( "musicas_efeitos/musica_highscore.mid" );
	if(musica_highscore == NULL)
		printf("Uma musica nao pode ser carregada");
	musica_abertura = Mix_LoadMUS( "musicas_efeitos/musica_abertura.mid" );
	if(musica_abertura == NULL)
		printf("Uma musica nao pode ser carregada");
	musica_jogo1 = Mix_LoadMUS( "musicas_efeitos/musica_jogo1.mid" );
	if(musica_jogo1 == NULL)
		printf("Uma musica nao pode ser carregada");
	musica_jogo2 = Mix_LoadMUS( "musicas_efeitos/musica_jogo2.mid" );
	if(musica_jogo2 == NULL)
		printf("Uma musica nao pode ser carregada");
	musica_jogo3 = Mix_LoadMUS( "musicas_efeitos/musica_jogo3.mid" );
	if(musica_jogo3 == NULL)
		printf("Uma musica nao pode ser carregada");

}

void Init_Bomberman(void)
{
    int i;

    bomberman.superficie = surf_bomberman;
	SDL_SetColorKey(bomberman.superficie, SDL_SRCCOLORKEY, SDL_MapRGB(bomberman.superficie->format, 255, 0, 255));

	for(i=0; i<13; i++)
	{
        bomberman.orig[i] = (SDL_Rect) {i*TILE_DIM, 0, TILE_DIM, TILE_DIM};
    }

	bomberman.dest = cenario[1][1].dest;

	bomberman.velX = 0;
	bomberman.velY = 0;
	bomberman.vel = 4;
	bomberman.max_bombas = 1;

	bomberman.movimento=PARADO;
	bomberman.estado = 0;
	bomberman.morrendo = 0;
	bomberman.vidas = 2;
	bomberman.em_cima = 0;
}

void Init_Bomba(OBJETO *bomb)
{
    bomb->estado = 0;
    bomb->tempo_explosao = 4000;
    bomb->alcance = 1;
	bomb->superficie = surf_bomba;
	
	bomb->quem_colocou = -2;
	
	SDL_SetColorKey(bomb->superficie, SDL_SRCCOLORKEY, SDL_MapRGB(bomb->superficie->format, 255, 0, 255));
}

void Bomberman_move(int direcao)
{
    if(bomberman.movimento==PARADO)
    {
        switch(direcao)
        {
            case CIMA:
                bomberman.estado = 1;
                bomberman.movimento = CIMA;
                bomberman.velY -= bomberman.vel;
                break;

            case BAIXO:
                bomberman.estado = 7;
                bomberman.movimento = BAIXO;
                bomberman.velY += bomberman.vel;
                break;

            case DIREITA:
                bomberman.estado = 4;
                bomberman.movimento = DIREITA;
                bomberman.velX += bomberman.vel;
                break;

            case ESQUERDA:
                bomberman.estado = 10;
                bomberman.movimento = ESQUERDA;
                bomberman.velX -= bomberman.vel;
                break;
        }
    }
}

void Update_bomberman(void)
{
    int temp, i;

    if(!bomberman.morrendo)
    {
        bomberman.dest.x += bomberman.velX;
        bomberman.dest.y += bomberman.velY;

        switch(bomberman.movimento)
        {
            case CIMA:
                bomberman.estado = (bomberman.estado + 1)%3;
                break;
            case DIREITA:
                bomberman.estado = 3 + (bomberman.estado + 1)%3;
                break;
            case BAIXO:
                bomberman.estado = 6 + (bomberman.estado + 1)%3;
                break;
            case ESQUERDA:
                bomberman.estado = 9 + (bomberman.estado + 1)%3;
                break;
            default: break;
        }

        for(i=0; i<TOTAL_MONSTROS; i++)
        {
            if(Colisao_Bomberman_Monstro(i))
            {
                bomberman.morrendo = 1;
                bomberman.superficie = surf_bomberman_morrendo;
                bomberman.estado = 0;
            }
        }
    }
    else
    {
        bomberman.estado++;
        if(bomberman.estado > 4)
        {
            temp = bomberman.vidas;
            Init_Bomberman();
            bomberman.vidas = temp - 1;
        }
    }
    /*---------*/

    if(bomberman.vidas <= 0)
    {
        estado_jogo = GAMEOVER;
    }

    switch(Detecta_colisao(&bomberman))
    {
        case COLISAO: //colisao com o cenario
            bomberman.dest.x -= bomberman.velX;
            bomberman.dest.y -= bomberman.velY;
            break;

        case MORTO:
			Mix_PlayChannel(2,morte,0);
            bomberman.morrendo = 1;
            bomberman.superficie = surf_bomberman_morrendo;
            bomberman.estado = 0;
            break;
    }

	if(Colisao_Bomberman_Bomba()==0 && bomberman.em_cima == 1)
    {
        bomberman.em_cima = 0;
    }
    if(Colisao_Bomberman_Bomba() == 1 && bomberman.em_cima == 0)
    {
        bomberman.dest.x -= bomberman.velX;
        bomberman.dest.y -= bomberman.velY;
    }

    /*---------*/
    //caso alinhe com a grade
    if( bomberman.dest.x % TILE_DIM == 0 && bomberman.dest.y % TILE_DIM == 0)
    {
        bomberman.movimento = PARADO;
        bomberman.velX = 0;
        bomberman.velY = 0;
    }
}

int Detecta_colisao(PERSONAGEM *personagem)
{
    int i, j, x, y;

    x = ( personagem->dest.x + (personagem->dest.w/2) ) / TILE_DIM;
    y = ( personagem->dest.y + (personagem->dest.h/2) ) / TILE_DIM;

    for(i= x-1 ; i<= x+1  ; i++)
        for(j= y-1; j<= y+1; j++)
        {
            if( personagem->dest.x + personagem->dest.w > cenario[i][j].dest.x &&
                personagem->dest.x < cenario[i][j].dest.x + TILE_DIM &&
                personagem->dest.y + personagem->dest.h > cenario[i][j].dest.y &&
                personagem->dest.y < cenario[i][j].dest.y + TILE_DIM &&
                cenario[i][j].tipo != CHAO )
            {
                switch(cenario[i][j].tipo)
                {
                    case FOGO:
                        return MORTO;
                    case CAIXA:
                    case PAREDE:
                    case SAIDA_FECHADA:
                        return COLISAO;
                    case ITEM:
                        //verificar se é o bomberman
                        Pegar_Item(i,j);
                        return C_ITEM;
                        break;
                    case SAIDA_ABERTA:
                        bomberman.vidas = -1;
                        return MORTO;
                    default: break;
                }
            }
        }
    return NCOLISAO;
}

void Bota_Bomba(void)
{
    int x, y, num_bomba=-1, i;
    x = ( bomberman.dest.x + bomberman.orig[0].w/2)/ TILE_DIM;
    y = ( bomberman.dest.y + bomberman.orig[0].h/2) / TILE_DIM;

    if(bomberman.morrendo)
        return;

    //procurando por bomba nao botada ainda
    for(i=0; i<bomberman.max_bombas; i++)
    {
        if(bomba[i].estado == 0)
        {
            num_bomba = i;
            break;
        }
    }

    if(num_bomba != -1 && cenario[x][y].tipo != BOMBA)
    {
        bomba[i].estado = 1;
		bomberman.em_cima = 1;
        bomba[i].dest = cenario[x][y].dest;
        bomba[i].tempo_inicial = SDL_GetTicks();
		
		bomba[i].quem_colocou = BOMBERMAN;
		
        cenario[x][y].tipo = BOMBA;
    }
}

void Explode_Bomba(OBJETO *bomb)
{
    int x, y, i, j, k;

    if(SDL_GetTicks() - bomb->tempo_inicial >= bomb->tempo_explosao && bomb->estado)
    {
        /*SOM*/
        Mix_PlayChannel(0,explosao,0);

        x = bomb->dest.x/32;
        y = bomb->dest.y/32;
        bomb->estado = 0;
        /* Explosao para DIREITA */
        for(i=1; i <= bomb->alcance; i++)
        {
            switch(cenario[x+i][y].tipo)
            {
                case CAIXA:
                    cenario[x+i][y].superficie = surf_fogoh;
                    cenario[x+i][y].tipo = FOGO;
                    cenario[x+i][y].tempo_fogo = SDL_GetTicks();
                    Gera_Item( x+i , y);
					if (bomb->quem_colocou == BOMBERMAN)
						jogador.score += SCORECAIXA;
                    i = 10000;
                    break;

                case PAREDE:
                    i = 10000;
                    break;

                case CHAO:
                case ITEM:
                    cenario[x+i][y].superficie = surf_fogoh;
                    cenario[x+i][y].tipo = FOGO;
                    cenario[x+i][y].tempo_fogo = SDL_GetTicks();
                    break;

                case BOMBA:
                    //Procurando qual bomba esta em x+i y
                    for(j=0; j<bomberman.max_bombas; j++)
                    {
                        if(x+i == bomba[j].dest.x / TILE_DIM && y == bomba[j].dest.y / TILE_DIM)
                            break;
                    }
					if(j!=bomberman.max_bombas)
                    {
						bomba[j].tempo_inicial = 0;
						Explode_Bomba(&bomba[j]);
					}
					for(k=0; k<TOTAL_MONSTROS; k++)
                    {
                        if(x+i == monstros[k].bomba[0].dest.x / TILE_DIM && y == monstros[k].bomba[0].dest.y / TILE_DIM)
                            break;
                    }
					if(k!=TOTAL_MONSTROS)
                    {
						monstros[k].bomba[0].tempo_inicial = 0;
						Explode_Bomba(&monstros[k].bomba[0]);
					}
                    i = 10000;
                    break;

                case SAIDA_FECHADA:
                    cenario[x+i][y].superficie = surf_saida;
                    cenario[x+i][y].tipo = SAIDA_ABERTA;
                    break;

                case SAIDA_ABERTA:
                    i = 10000;
                    break;

                default: break;
            }
        }
        /* Explosao para ESQUERDA */
        for(i=1; i <= bomb->alcance; i++)
        {
            switch(cenario[x-i][y].tipo)
            {
                case CAIXA:
                    cenario[x-i][y].superficie = surf_fogoh;
                    cenario[x-i][y].tipo = FOGO;
                    cenario[x-i][y].tempo_fogo = SDL_GetTicks();
                    Gera_Item( x-i , y);
					if (bomb->quem_colocou == BOMBERMAN)
						jogador.score += SCORECAIXA;
                    i = 10000;
                    break;

                case PAREDE:
                    i = 10000;
                    break;

                case CHAO:
				case ITEM:
                    cenario[x-i][y].superficie = surf_fogoh;
                    cenario[x-i][y].tipo = FOGO;
                    cenario[x-i][y].tempo_fogo = SDL_GetTicks();
                    break;

                case BOMBA:
                    //Procurando qual bomba esta em x+i y
                    for(j=0; j<bomberman.max_bombas; j++)
                    {
                        if(x-i == bomba[j].dest.x / TILE_DIM && y == bomba[j].dest.y / TILE_DIM)
                            break;
                    }
					if (j!=bomberman.max_bombas)
					{
						bomba[j].tempo_inicial = 0;
						Explode_Bomba(&bomba[j]);
					}
					for(k=0; k<TOTAL_MONSTROS; k++)
                    {
                        if(x-i == monstros[k].bomba[0].dest.x / TILE_DIM && y == monstros[k].bomba[0].dest.y / TILE_DIM)
                            break;
                    }
					if(k!=TOTAL_MONSTROS)
                    {
						monstros[k].bomba[0].tempo_inicial = 0;
						Explode_Bomba(&monstros[k].bomba[0]);
					}					
                    i = 10000;
                    break;

                case SAIDA_FECHADA:
                    cenario[x-i][y].superficie = surf_saida;
                    cenario[x-i][y].tipo = SAIDA_ABERTA;
                    break;

                case SAIDA_ABERTA:
                    i = 10000;
                    break;

                default: break;
            }
        }
        /* Explosao para CIMA */
        for(i=1; i <= bomb->alcance; i++)
        {
            switch(cenario[x][y+i].tipo)
            {
                case CAIXA:
                    cenario[x][y+i].superficie = surf_fogov;
                    cenario[x][y+i].tipo = FOGO;
                    cenario[x][y+i].tempo_fogo = SDL_GetTicks();
                    Gera_Item( x, y+i);
					if (bomb->quem_colocou == BOMBERMAN)
						jogador.score += SCORECAIXA;
                    i = 10000;
                    break;

                case PAREDE:
                    i = 10000;
                    break;

                case CHAO:
				case ITEM:
                    cenario[x][y+i].superficie = surf_fogov;
                    cenario[x][y+i].tipo = FOGO;
                    cenario[x][y+i].tempo_fogo = SDL_GetTicks();
                    break;

                case BOMBA:
                    //Procurando qual bomba esta em x+i y
                    for(j=0; j<bomberman.max_bombas; j++)
                    {
                        if(x == bomba[j].dest.x / TILE_DIM && y+i == bomba[j].dest.y / TILE_DIM)
                            break;
                    }
					if (j!=bomberman.max_bombas)
					{
						bomba[j].tempo_inicial = 0;
						Explode_Bomba(&bomba[j]);
					}
					for(k=0; k<TOTAL_MONSTROS; k++)
                    {
                        if(x == monstros[k].bomba[0].dest.x / TILE_DIM && y+i == monstros[k].bomba[0].dest.y / TILE_DIM)
                            break;
                    }
					if(k!=TOTAL_MONSTROS)
                    {
						monstros[k].bomba[0].tempo_inicial = 0;
						Explode_Bomba(&monstros[k].bomba[0]);
					}					
                    i = 10000;
                    break;

                case SAIDA_FECHADA:
                    Mix_PlayChannel(3,saida,0);
					cenario[x][y+i].superficie = surf_saida;
                    cenario[x][y+i].tipo = SAIDA_ABERTA;
                    break;

                case SAIDA_ABERTA:
                    i = 10000;
                    break;

                default: break;
            }
        }
        /* Explosao para BAIXO */
        for(i=1; i <= bomb->alcance; i++)
        {
            switch(cenario[x][y-i].tipo)
            {
                case CAIXA:
                    cenario[x][y-i].superficie = surf_fogov;
                    cenario[x][y-i].tipo = FOGO;
                    cenario[x][y-i].tempo_fogo = SDL_GetTicks();
                    Gera_Item(x ,y-i);
					if (bomb->quem_colocou == BOMBERMAN)
						jogador.score += SCORECAIXA;
                    i = 10000;
                    break;

                case PAREDE:
                    i = 10000;
                    break;

                case CHAO:
				case ITEM:
                    cenario[x][y-i].superficie = surf_fogov;
                    cenario[x][y-i].tipo = FOGO;
                    cenario[x][y-i].tempo_fogo = SDL_GetTicks();
                    break;

                case BOMBA:
                    //Procurando qual bomba esta em x+i y
                    for(j=0; j<bomberman.max_bombas; j++)
                    {
                        if(x == bomba[j].dest.x / TILE_DIM && y-i == bomba[j].dest.y / TILE_DIM)
                            break;
                    }
					if (j!=bomberman.max_bombas)
					{
						bomba[j].tempo_inicial = 0;
						Explode_Bomba(&bomba[j]);
					}
					for(k=0; k<TOTAL_MONSTROS; k++)
                    {
                        if(x == monstros[k].bomba[0].dest.x / TILE_DIM && y-i == monstros[k].bomba[0].dest.y / TILE_DIM)
                            break;
                    }
					if(k!=TOTAL_MONSTROS)
                    {
						monstros[k].bomba[0].tempo_inicial = 0;
						Explode_Bomba(&monstros[k].bomba[0]);
					}					
                    i = 10000;
                    break;

                case SAIDA_FECHADA:
                    cenario[x][y-i].superficie = surf_saida;
                    cenario[x][y-i].tipo = SAIDA_ABERTA;
                    break;

                case SAIDA_ABERTA:
                    i = 10000;
                    break;

                default: break;
            }
        }
        /* CENTRO */
        cenario[x][y].superficie = surf_fogoc;
        cenario[x][y].tipo = FOGO;
        cenario[x][y].tempo_fogo = SDL_GetTicks();
    }
}

int Colisao_Bomberman_Bomba(void)
{
    int i;

    for(i=0; i<MAXBOMBAS; i++)
    {
        if(bomba[i].estado) //bomberman.dest
        {
            if( bomberman.dest.x + bomberman.dest.w > bomba[i].dest.x &&
                bomberman.dest.x < bomba[i].dest.x + bomba[i].dest.w &&
                bomberman.dest.y + bomberman.dest.h > bomba[i].dest.y &&
                bomberman.dest.y < bomba[i].dest.y + bomba[i].dest.h )
            {
                return 1;
            }
        }
    }
    return 0;
}

void Desenha_cenario(void)
{
    int i, j;

    for(i=0; i<MAPA_W/TILE_DIM; i++)
        for(j=0; j<MAPA_H/TILE_DIM; j++)
        {
            /* Some com o fogo */
            if(cenario[i][j].tipo == FOGO && (SDL_GetTicks() - cenario[i][j].tempo_fogo >= MAX_TEMPOFOGO) )
            {
                cenario[i][j].tipo = CHAO;
                cenario[i][j].superficie = surf_chao;
            }
            SDL_BlitSurface(cenario[i][j].superficie, NULL, screen, &(cenario[i][j].dest));
        }
}

void Desenha_Pause(int x, int y, TTF_Font *font)
{
    char *texto = "Pause";
    SDL_Color cor = {0, 100, 255}; //verde
    SDL_Surface *superficie = TTF_RenderText_Solid(font, texto, cor);
    SDL_Rect dest = {x, y, 0, 0};

    SDL_BlitSurface(superficie, NULL, screen, &dest);
}

void Desenha_Gameover(int x, int y, TTF_Font *font)
{
	char *string = "Game Over";
	SDL_Color cor = {0, 0, 255};
	SDL_Surface *texto = TTF_RenderText_Solid(font, string, cor);
	SDL_Rect dest_img = {x, y, 0, 0};
	SDL_Rect dest_texto = {x + (surf_gameover->w - texto->w)/2, y + (surf_gameover->h - texto->h)/2, 0, 0};
	SDL_BlitSurface(surf_gameover, NULL, screen, &dest_img);
	SDL_BlitSurface(texto, NULL, screen, &dest_texto);
}

void Limita_fps(int tempo)
{
	int fps;
	char titulo[30];

	tempo = SDL_GetTicks() - tempo;
    fps = 1000/tempo;
    sprintf(titulo, "fps: %d", fps);
    SDL_WM_SetCaption(titulo, "jogo");
    if(tempo < MAXMSEC)
        SDL_Delay(MAXMSEC - tempo);

}

void Gera_Item(int x, int y)
{
    int chance=15, resultado, item;

    resultado = rand()%100;
    if(resultado <= chance) //chance% de chance de gerar item
    {
        item = rand()%4;
        switch(item)
        {
            case 0:
                cenario[x][y].superficie = surf_ibomba;
                break;
            case 1:
                cenario[x][y].superficie = surf_ipatins;
                break;
            case 2:
                cenario[x][y].superficie = surf_ifogo;
                break;
            case 3:
                cenario[x][y].superficie = surf_ivida;
                break;
		}
        cenario[x][y].tipo = ITEM;
    }
}

void Pegar_Item(int x, int y)
{
    int i;

    jogador.score += SCOREITEM;

	Mix_PlayChannel(1,novoitem,0);

    if(cenario[x][y].superficie == surf_ibomba)
    {
        if(bomberman.max_bombas < 10)
            bomberman.max_bombas++;
    }
    else if(cenario[x][y].superficie == surf_ipatins)
    {
        bomberman.vel = 8;
    }
    else if(cenario[x][y].superficie == surf_ifogo)
    {
        for(i=0; i<MAXBOMBAS; i++)
        {
            if(bomba[i].alcance <= 5)
                bomba[i].alcance++;
        }
    }
    else if(cenario[x][y].superficie == surf_ivida)
    {
        bomberman.vidas++;
    }

    cenario[x][y].superficie = surf_chao;
    cenario[x][y].tipo = CHAO;
}

void Desenha_Texto(char *frase,int x ,int y, SDL_Color cor)
{
    SDL_Surface *src;
    SDL_Rect destino_rect = {x, y, 0, 0};

    src = TTF_RenderText_Solid(font_times, frase, cor);

    SDL_BlitSurface(src, NULL, screen, &destino_rect);
}

void Desenha_MenuJogo(enum Opcao_menu selecao)
{
    switch(selecao)
    {
        case NOVOJOGO:
            Desenha_Texto("Novo Jogo", 300, 300, (SDL_Color){255, 255, 0});
            Desenha_Texto("Highscore", 300, 400, (SDL_Color){255, 0, 0});
            Desenha_Texto("Sair", 300, 500, (SDL_Color){255, 0, 0});
            break;

        case O_HIGHSCORE:
            Desenha_Texto("Novo Jogo", 300, 300, (SDL_Color){255, 0, 0});
            Desenha_Texto("Highscore", 300, 400, (SDL_Color){255, 255, 0});
            Desenha_Texto("Sair", 300, 500, (SDL_Color){255, 0, 0});
            break;

        case SAIR:
            Desenha_Texto("Novo Jogo", 300, 300, (SDL_Color){255, 0, 0});
            Desenha_Texto("Highscore", 300, 400, (SDL_Color){255, 0, 0});
            Desenha_Texto("Sair", 300, 500, (SDL_Color){255, 255, 0});
            break;
    }
}

void Desenha_Infos(void)
{
    SDL_Rect dest = {0, MAPA_H, surf_infos->w, surf_infos->h};
    char vidas[5], num_bombas[5], pontuacao[40];

    sprintf(vidas, "%d", bomberman.vidas);
    sprintf(num_bombas, "%d", bomberman.max_bombas);
    sprintf(pontuacao, "%d", jogador.score);

    SDL_BlitSurface(surf_infos, NULL, screen, &dest);
    Desenha_Texto(vidas, 75, MAPA_H + 20, (SDL_Color){255, 0, 0});
    Desenha_Texto(num_bombas, 160, MAPA_H + 20, (SDL_Color){255, 0, 0});
    Desenha_Texto(pontuacao, 315, MAPA_H + 22, (SDL_Color){255, 0, 0});
}

void Load_Highscore(void)
{
    char *path = "highscore.bin";
    int novo=0;
    int tam, i;

    //zera jogador_high
    for(i=0; i<MAXJ; i++)
    {
        jogador_high[i].nome[0] = '\0';
        jogador_high[i].score = 0;
    }

    if(arq_highscore == NULL)
    {
		arq_highscore = fopen(path, "r+");
		if(!arq_highscore)//arquivo ainda nao existe
		{
			arq_highscore = fopen(path, "w+");
			novo = 1;
		}
	}

    if(!novo)
    {
        fseek(arq_highscore, 0, SEEK_END);
        tam = ftell(arq_highscore);
        tam = tam / sizeof(JOGADOR);
        rewind(arq_highscore);

        for(i=0; i<tam; i++)
            fread(&jogador_high[i], 1, sizeof(JOGADOR), arq_highscore);
    }
}

void Adiciona_Highscore(char *nome, int score)
{
    int tam;

    for(tam=0; jogador_high[tam].nome[0]; tam++);

    if(tam < MAXJ)
    {
        strcpy(jogador_high[tam].nome, nome);
        jogador_high[tam].score = score;
    }
    else
    {
        if(jogador_high[MAXJ-1].score < score)
        {
            strcpy(jogador_high[MAXJ-1].nome, nome);
            jogador_high[MAXJ-1].score = score;
        }
    }

    //ordena
    qsort(jogador_high, tam+1, sizeof(jogador_high[0]), Compara);

    rewind(arq_highscore);
    fwrite(jogador_high, 1, sizeof(jogador_high), arq_highscore);
}

int Compara(const void *e1, const void *e2)
{
    JOGADOR j1, j2;
    j1 = *( (JOGADOR *)e1 );
    j2 = *( (JOGADOR *)e2 );

    if(j1.score > j2.score)
    {
        return -1;
    }
    if(j1.score < j2.score)
    {
        return 1;
    }
    return strcmp(j2.nome, j1.nome);
}

void Init_Jogador(void)
{
    int i;

    for(i=0; i<MAXNOME; i++)
    {
        jogador.nome[i] = '\0';
    }
    jogador.score = 0;
}

int Colisao_Bomberman_Monstro(int monstro)
{

    if( bomberman.dest.x + bomberman.dest.w > monstros[monstro].dst.x &&
        bomberman.dest.x < monstros[monstro].dst.x + monstros[monstro].dst.w &&
        bomberman.dest.y + bomberman.dest.h > monstros[monstro].dst.y &&
        bomberman.dest.y < monstros[monstro].dst.y + monstros[monstro].dst.h)
    {
        return MORTO;
    }
    return NCOLISAO;
}


void Update_Monstro(int monstro)
{
    if(monstros[monstro].vivo)
    {
        switch(monstros[monstro].direcao)
        {
            case CIMA:
                monstros[monstro].estado = (monstros[monstro].estado + 1)%3;
                monstros[monstro].dst.y -= monstros[monstro].velY;
                break;
            case DIREITA:
                monstros[monstro].estado = 3 + (monstros[monstro].estado + 1)%3;
                monstros[monstro].dst.x += monstros[monstro].velX;
                break;
            case BAIXO:
                monstros[monstro].estado = 6 + (monstros[monstro].estado + 1)%3;
                monstros[monstro].dst.y += monstros[monstro].velY;
                break;
            case ESQUERDA:
                monstros[monstro].estado = 9 + (monstros[monstro].estado + 1)%3;
                monstros[monstro].dst.x -= monstros[monstro].velX;
                break;
        }

        if ((monstros[monstro].dst.y % TILE_DIM == 0) && (monstros[monstro].dst.x % TILE_DIM == 0))
        {
            monstros[monstro].movendo=0;
        }

        if(Colisao_Monstro_Cenario(monstro) == MORTO)
        {
            monstros[monstro].vivo = 0;
            monstros[monstro].dst = cenario[0][0].dest;
        }
    }
    else
    {
        monstros[monstro].dst = cenario[0][0].dest;
    }

}

void Init_Monstros()
{
	int i,j;
	int coluna, linha;
	MONSTRO monstro;

	for (i=0; i<TOTAL_MONSTROS; i++)
	{
		monstro.velX=2;
		monstro.velY=2;
		monstro.direcao=0;
		monstro.movendo=0;
		monstro.estado=1;
		monstro.vivo = 1;

		for(j=0; j<13; j++)
		{
	        monstro.src[j] = (SDL_Rect) {j*TILE_DIM, i*TILE_DIM, TILE_DIM, TILE_DIM};
	    }

		do
		{
			coluna = rand()%(MAPA_W/TILE_DIM);//coluna
			linha = rand()%(MAPA_H/TILE_DIM);//linha
			monstro.dst = (SDL_Rect) {coluna*TILE_DIM, linha*TILE_DIM,TILE_DIM,TILE_DIM};
			monstros[i] = monstro;
		}
		while (Colisao_Monstro_Cenario(i) || Tem_Monstro(linha,coluna,i) ||
                (coluna == 1 && linha == 1) || (coluna == 1 && linha == 2) ||
                (coluna == 2 && linha == 1) );

		monstro.dst = (SDL_Rect) {coluna*TILE_DIM, linha*TILE_DIM,32,32};
		monstro.surf=IMG_Load("imagens/monstros.bmp");
	    if(!monstro.surf)
		{
			printf("Nao foi possivel carregar monstro.bmp\n");
			quit = 1;
		}
		monstro.movimentoAleatorio=2;
		monstro.manterDirecao = 0;
		monstro.num_bomba=0;
		monstro.alcance_bomba=3;
		SDL_SetColorKey(monstro.surf, SDL_SRCCOLORKEY, SDL_MapRGB(monstro.surf->format, 255, 0, 255));	
		
		monstros[i] = monstro;
	}

	return;
}

int Colisao_Monstro_Cenario(int monstro)
{
    int i, j,x, y;

    x = ( monstros[monstro].dst.x + (monstros[monstro].dst.w/2) ) / TILE_DIM;
    y = ( monstros[monstro].dst.y + (monstros[monstro].dst.h/2) ) / TILE_DIM;

    for(i= x-1 ; i<= x+1  ; i++)
    {
        for(j= y-1; j<= y+1; j++)
        {
            if( monstros[monstro].dst.x + monstros[monstro].dst.w > cenario[i][j].dest.x &&
                monstros[monstro].dst.x < cenario[i][j].dest.x + TILE_DIM &&
                monstros[monstro].dst.y + monstros[monstro].dst.h > cenario[i][j].dest.y &&
                monstros[monstro].dst.y < cenario[i][j].dest.y + TILE_DIM &&
                cenario[i][j].tipo != CHAO )
            {
                switch(cenario[i][j].tipo)
                {
                    case FOGO:
                        jogador.score += SCOREMONSTRO;
                        return MORTO;
                    case ITEM:
                        //verificar se é o bomberman
                        Monstro_Pegar_Item(monstro,i,j);
                        return C_ITEM;
                        break;							
                    case CAIXA:
                    case PAREDE:
                    case SAIDA_ABERTA:
                    case SAIDA_FECHADA:
                        return COLISAO;
                    default:
						break;
                }
            }
        }
    }
    if(Colisao_Monstro_Bomba(monstro))
    {
        return COLISAO;
    }

    return NCOLISAO;
}




void escolheDirecao(int monstro)
{

	int linhaBackup = monstros[monstro].dst.y;
	int colunaBackup = monstros[monstro].dst.x;
	int direcao;


	direcao = rand()%4 +1;
	switch (direcao)
	{
		case CIMA:
			monstros[monstro].estado = 1;
			monstros[monstro].dst.y -= monstros[monstro].velY;
			if (Colisao_Monstro_Cenario(monstro))
			{
				direcao=PARADO;
			}
			else
			{
				if (Colisao_Monstro_Monstro(monstro,CIMA))
				{
					direcao=PARADO;
				}
				else
				{
					if (Colisao_Monstro_MonstroEmMovimeto(monstro,CIMA))
					{
						direcao=PARADO;
					}
				}
			}
			break;
		case BAIXO:
			monstros[monstro].estado = 7;
			monstros[monstro].dst.y += monstros[monstro].velY;
			if (Colisao_Monstro_Cenario(monstro))
			{
				direcao=PARADO;
			}
			else
			{
				if (Colisao_Monstro_Monstro(monstro,BAIXO))
				{
					direcao=PARADO;
				}
				else
				{
					if (Colisao_Monstro_MonstroEmMovimeto(monstro,BAIXO))
					{
						direcao=PARADO;
					}
				}
			}

			break;
		case DIREITA:
			monstros[monstro].estado = 4;
			monstros[monstro].dst.x += monstros[monstro].velX;
			if (Colisao_Monstro_Cenario(monstro))
			{
				direcao=PARADO;
			}
			else
			{
				if (Colisao_Monstro_Monstro(monstro,DIREITA))
				{
					direcao=PARADO;
				}
				else
				{
					if (Colisao_Monstro_MonstroEmMovimeto(monstro,DIREITA))
					{
						direcao=PARADO;
					}
				}
			}
			break;
		case ESQUERDA:
			monstros[monstro].estado = 10;
			monstros[monstro].dst.x -= monstros[monstro].velX;
			if (Colisao_Monstro_Cenario(monstro))
			{
				direcao=PARADO;
			}
			else
			{

				if (Colisao_Monstro_Monstro(monstro,ESQUERDA))
				{
					direcao=PARADO;
				}
				else
				{
					if (Colisao_Monstro_MonstroEmMovimeto(monstro,ESQUERDA))
					{
						direcao=PARADO;
					}
				}
			}
			break;
		default:
			direcao=PARADO;
			break;
	}

	monstros[monstro].direcao=direcao;
	if (direcao == PARADO)
	{
		monstros[monstro].movendo=0;
		monstros[monstro].dst.x = colunaBackup;
		monstros[monstro].dst.y = linhaBackup;

	}
	else
	{
		monstros[monstro].movendo=1;
	}
	monstros[monstro].manterDirecao=0;
}


void Movimentar_Monstro(int monstro)
{
    if(monstros[monstro].vivo)
    {
        if (!monstros[monstro].movendo)
        {
            switch (monstros[monstro].movimentoAleatorio)
            {
				case 1:
					escolheDirecao(monstro);
					break;
				case 2:
					if ((rand()%100 < 3) || (monstros[monstro].manterDirecao))
					{
						escolheBomba(monstro);
					}
					else
					{
						escolheDirecao(monstro);
					}
            }
        }
        Update_Monstro(monstro);
    }
}


void Movimentar_Monstros(void)
{
	int i;
	for (i=0; i<TOTAL_MONSTROS; i++)
	{
		Movimentar_Monstro(i);
	}
}


void Desenha_Monstros(void)
{
	int i;
	for (i=0; i<TOTAL_MONSTROS; i++)
	{
	    if(monstros[i].vivo)
            SDL_BlitSurface(monstros[i].surf, &(monstros[i].src[monstros[i].estado]), screen, &(monstros[i].dst));
	}
}


int Colisao_Monstro_Monstro(int monstro, int direcao)
{
	int i;
	int posicaoX, posicaoY;
	int distX, distY;
	int distXM, distYM;

	switch (direcao)
	{
		case CIMA:
			posicaoY = monstros[monstro].dst.y - monstros[monstro].velY;
			posicaoX = monstros[monstro].dst.x;
			break;
		case BAIXO:
			posicaoY = monstros[monstro].dst.y + monstros[monstro].velY;
			posicaoX = monstros[monstro].dst.x;
			break;
		case DIREITA:
			posicaoX = monstros[monstro].dst.x + monstros[monstro].velX;
			posicaoY = monstros[monstro].dst.y;
			break;
		case ESQUERDA:
			posicaoX = monstros[monstro].dst.x - monstros[monstro].velX;
			posicaoY = monstros[monstro].dst.y;
			break;
	}

	for (i=0; i<TOTAL_MONSTROS; i++)
	{
		if (i!=monstro)
		{
			distY = posicaoY + (TILE_DIM/2);
			distYM = monstros[i].dst.y + (TILE_DIM/2);
			if (abs(distYM-distY) < TILE_DIM)
			{
				distX = posicaoX + (TILE_DIM/2);
				distXM = monstros[i].dst.x + (TILE_DIM/2);
				if (abs(distXM-distX) < TILE_DIM)
				{
					return 1;
				}
			}
		}
	}

	for (i=0; i<TOTAL_MONSTROS; i++)
	{
		if (i!=monstro)
		{
			distX = posicaoX + (TILE_DIM/2);
			distXM = monstros[i].dst.x + (TILE_DIM/2);
			if (abs(distXM-distX) < TILE_DIM)
			{
				distY = posicaoY + (TILE_DIM/2);
				distYM = monstros[i].dst.y + (TILE_DIM/2);
				if (abs(distYM-distY) < TILE_DIM)
				{
					return 1;
				}
			}
		}
	}


	return 0;
}


int Colisao_Monstro_MonstroEmMovimeto(int monstro, int direcao)
{
	int i;
	int linhaBackup, colunaBackup;


	for (i=0; i<TOTAL_MONSTROS; i++)
	{
		if (monstros[i].movendo)
		{
			linhaBackup = monstros[i].dst.y;
			colunaBackup = monstros[i].dst.x;
			switch (monstros[i].direcao)
			{
				case CIMA:
					monstros[i].dst.y = (monstros[i].dst.y/TILE_DIM)*TILE_DIM;
					break;
				case BAIXO:
					monstros[i].dst.y = (monstros[i].dst.y/TILE_DIM+1)*TILE_DIM;
					break;
				case DIREITA:
					monstros[i].dst.x = (monstros[i].dst.x/TILE_DIM+1)*TILE_DIM;
					break;
				case ESQUERDA:
					monstros[i].dst.x = (monstros[i].dst.x/TILE_DIM)*TILE_DIM;
					break;
			}
			if (Colisao_Monstro_Monstro(monstro,direcao))
			{
				monstros[i].dst.y = linhaBackup;
				monstros[i].dst.x = colunaBackup;
				return 1;
			}
			monstros[i].dst.y = linhaBackup;
			monstros[i].dst.x = colunaBackup;
		}
	}
	return 0;
}

int Tem_Monstro(int linha, int coluna, int max)
{
	int i;
	for (i=0; i<max; i++)
	{
		if (monstros[i].dst.x==coluna*TILE_DIM  &&  monstros[i].dst.y==linha*TILE_DIM)
		{
			return 1;
		}
	}
	return 0;
}

int Colisao_Monstro_Bomba(int monstro)
{
    int i;

    for(i=0; i<MAXBOMBAS; i++)
    {
        if(bomba[i].estado) //bomba[i].dest
        {
            if( monstros[monstro].dst.x + monstros[monstro].dst.w > bomba[i].dest.x &&
                monstros[monstro].dst.x < bomba[i].dest.x + bomba[i].dest.w &&
                monstros[monstro].dst.y + monstros[monstro].dst.h > bomba[i].dest.y &&
                monstros[monstro].dst.y < bomba[i].dest.y + bomba[i].dest.h )
            {
                return 1;
            }
        }
    }
    return 0;
}

void Init_Cenas(void)
{
	//tela_abertura = SDL_LoadBMP("imagens/abertura.bmp");
}


void Desenha_Abertura(int cena)
{
	char *texto1, *texto2, *texto3;
	texto1="Olá, voce está diante de um projeto final de semestre";
	texto2="do curso de Ciência da Computação da UFRJ, 2008/1.";
	texto3="Divirta-se com nosso Bomberman!";
	TTF_CloseFont(font_times);
	font_times = TTF_OpenFont("times.ttf", 33);
	SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
	SDL_BlitSurface(tela_abertura, NULL, screen, NULL);

	switch(cena)
	{
		case 1:
			Desenha_Texto(texto1,50,500,(SDL_Color){105,202,0}); break;
		case 2:
			Desenha_Texto(texto2,50,500,(SDL_Color){105,202,0}); break;
		case 3:
			Desenha_Texto(texto3,150,500,(SDL_Color){105,202,0}); break;
		default:break;
	}
	Fonte_Default();
	return;
}


void Fonte_Default(void)
{
    TTF_CloseFont(font_times);
	font_times = TTF_OpenFont("times.ttf", FONTSIZE);
}


void Desabilita_Sons(void)
{
    /*EFEITOS SONOROS*/

    Mix_FreeChunk(explosao);
	explosao = NULL;
	Mix_FreeChunk(novoitem);
	novoitem = NULL;
	Mix_FreeChunk(morte);
	morte = NULL;
	Mix_FreeChunk(saida);
	saida = NULL;
	Mix_FreeChunk(click);
	click = NULL;
	Mix_FreeChunk(seleciona);
	seleciona = NULL;

	/*MUSICAS*/

    Mix_FreeMusic(musica_highscore);
	musica_highscore = NULL;
	Mix_FreeMusic(musica_abertura);
	musica_abertura = NULL;
	Mix_FreeMusic(musica_jogo1);
	musica_jogo1 = NULL;
	Mix_FreeMusic(musica_jogo2);
	musica_jogo2 = NULL;
	Mix_FreeMusic(musica_jogo3);
	musica_jogo3 = NULL;

    if( Mix_PlayingMusic() )
    {
        Mix_HaltMusic();
    }
}




void escolheBomba(int monstro)
{
	int teste=0;
	int direcao, colisao, i;
	
	int dstY_Backup = monstros[monstro].dst.y;
	int dstX_Backup = monstros[monstro].dst.x;
	
	srand(time(NULL));
	direcao = rand()%4+1;
	while ((teste<=4) && (!monstros[monstro].manterDirecao))
	{
		switch (direcao)
		{
			case CIMA:
				direcao=CIMA;
				colisao=0;
				for (i=0; i<monstros[monstro].alcance_bomba; i++)
				{
					monstros[monstro].dst.y-=monstros[monstro].dst.h;
					if ((monstros[monstro].dst.y < 0 || 
						Colisao_Monstro_Cenario(monstro) || 
						Colisao_Monstro_MonstroEmMovimeto(monstro,direcao) || 
						Colisao_Monstro_Monstro(monstro,direcao)))
						{
							monstros[monstro].dst.y = dstY_Backup;
							monstros[monstro].dst.x = dstX_Backup;							
							teste++;
							colisao = 1;
							break;
						}
				}		
				if (!colisao)		
				{
					/*implantar bomba*/
					monstros[monstro].dst.y = dstY_Backup;
					monstros[monstro].dst.x = dstX_Backup;
					monstros[monstro].direcao=direcao;
					monstros[monstro].manterDirecao=2;
					monstros[monstro].movendo=1;
					Monstro_Bota_Bomba(monstro);					
					return;
				}
			case DIREITA:
				direcao=DIREITA;				
				colisao=0;
				for (i=0; i<monstros[monstro].alcance_bomba; i++)
				{
					monstros[monstro].dst.x+=monstros[monstro].dst.w;
					if ((monstros[monstro].dst.x >= MAPA_W-TILE_DIM || 
						Colisao_Monstro_Cenario(monstro) || 
						Colisao_Monstro_MonstroEmMovimeto(monstro,direcao) || 
						Colisao_Monstro_Monstro(monstro,direcao)))
						{
							monstros[monstro].dst.y = dstY_Backup;
							monstros[monstro].dst.x = dstX_Backup;							
							teste++;
							colisao = 1;
							break;
						}
				}		
				if (!colisao)		
				{
					/*implantar bomba*/
					monstros[monstro].dst.y = dstY_Backup;
					monstros[monstro].dst.x = dstX_Backup;
					monstros[monstro].direcao=direcao;
					monstros[monstro].manterDirecao=2;
					monstros[monstro].movendo=1;
					Monstro_Bota_Bomba(monstro);					
					return;
				}
			case BAIXO:
				direcao=BAIXO;
				colisao=0;
				for (i=0; i<monstros[monstro].alcance_bomba; i++)
				{
					monstros[monstro].dst.y+=monstros[monstro].dst.h;
					if ((monstros[monstro].dst.y >= MAPA_H-TILE_DIM || 
						Colisao_Monstro_Cenario(monstro) || 
						Colisao_Monstro_MonstroEmMovimeto(monstro,direcao) || 
						Colisao_Monstro_Monstro(monstro,direcao)))
						{
							monstros[monstro].dst.y = dstY_Backup;
							monstros[monstro].dst.x = dstX_Backup;							
							teste++;
							colisao = 1;
							break;
						}
				}		
				if (!colisao)		
				{
					/*implantar bomba*/
					monstros[monstro].dst.y = dstY_Backup;
					monstros[monstro].dst.x = dstX_Backup;
					monstros[monstro].direcao=direcao;
					monstros[monstro].manterDirecao=2;
					monstros[monstro].movendo=1;
					Monstro_Bota_Bomba(monstro);					
					return;
				}
			case ESQUERDA:
				direcao=ESQUERDA;				
				colisao=0;
				for (i=0; i<monstros[monstro].alcance_bomba; i++)
				{
					monstros[monstro].dst.x-=monstros[monstro].dst.w;
					if ((monstros[monstro].dst.x > 0 || 
						Colisao_Monstro_Cenario(monstro) || 
						Colisao_Monstro_MonstroEmMovimeto(monstro,direcao) || 
						Colisao_Monstro_Monstro(monstro,direcao)))
						{
							monstros[monstro].dst.y = dstY_Backup;
							monstros[monstro].dst.x = dstX_Backup;							
							teste++;
							colisao = 1;
							break;
						}
				}		
				if (!colisao)		
				{
					/*implantar bomba*/
					monstros[monstro].dst.y = dstY_Backup;
					monstros[monstro].dst.x = dstX_Backup;
					monstros[monstro].direcao=direcao;
					monstros[monstro].manterDirecao=2;
					monstros[monstro].movendo=1;
					Monstro_Bota_Bomba(monstro);					
					return;
				}
		}
	}
	monstros[monstro].dst.y = dstY_Backup;
	monstros[monstro].dst.x = dstX_Backup;
	if (monstros[monstro].manterDirecao && !Colisao_Monstro_MonstroEmMovimeto(monstro,monstros[monstro].direcao) && !Colisao_Monstro_Monstro(monstro,monstros[monstro].direcao) && !Colisao_Monstro_Cenario(monstro))
	{
		monstros[monstro].manterDirecao--;
		monstros[monstro].movendo=1;
		return;
	}
	monstros[monstro].manterDirecao = 0;
	escolheDirecao(monstro);	
	
}



void Monstro_Bota_Bomba(int monstro)
{
    int x, y;
    x = ( monstros[monstro].dst.x + monstros[monstro].src[0].w/2) / TILE_DIM;
    y = ( monstros[monstro].dst.y + monstros[monstro].src[0].h/2) / TILE_DIM;
	if (monstros[monstro].bomba[0].estado == 0)
	{
		printf("sou o monstro %d e coloquei bomba em posX: %d posY %d",monstro,monstros[monstro].dst.x,monstros[monstro].dst.y);
		monstros[monstro].num_bomba=1;
		monstros[monstro].bomba[0].estado = 1;
		
		monstros[monstro].bomba[0].dest.x = monstros[monstro].dst.x;
		monstros[monstro].bomba[0].dest.y = monstros[monstro].dst.y;
		
		//monstros[monstro].bomba[0].dest = cenario[x][y].dest;
		monstros[monstro].bomba[0].tempo_inicial = SDL_GetTicks();
		monstros[monstro].bomba[0].quem_colocou = INIMIGO;
		cenario[x][y].tipo = BOMBA;
	}
}

void Monstros_Explode_Bomba(void)
{
	int i, j;
	
	for (j=0; j<TOTAL_MONSTROS; j++)
	{
		for(i=0; i<monstros[j].num_bomba; i++)
		{
			Explode_Bomba(&monstros[j].bomba[i]);
			break;
		}
	}
}

void Monstros_Desenha_Bomba(void)
{
	int i, j;
	
	for (j=0; j<TOTAL_MONSTROS; j++)
		for(i=0; i<monstros[j].num_bomba; i++)
			if(monstros[j].bomba[i].estado)
				SDL_BlitSurface(monstros[j].bomba[i].superficie, NULL, screen, &(monstros[j].bomba[i].dest));
}


void Init_Bomba_Monstros(void)
{
	int i;
	
	for (i=0; i<TOTAL_MONSTROS; i++)
	{
		Init_Bomba(&monstros[i].bomba[0]);
		monstros[i].bomba[0].superficie = surf_ovo;
	}
}

void Monstro_Pegar_Item(int monstro, int x, int y)
{

	if(cenario[x][y].superficie == surf_ipatins)
    {
        monstros[monstro].velX = 4;
		monstros[monstro].velY = 4;
    }

    cenario[x][y].superficie = surf_chao;
    cenario[x][y].tipo = CHAO;
}




