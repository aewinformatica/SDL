#include "includes.h"

void Inicializa_Variaveis ()
{
    int i;

    estado = MENU;
    Define_Botoes ();
    cascata = 0;
    vidas = 3;
    fase = 0;
    venceu = 0;

    jogador.fim = 0;
    jogador.nome[0] = ' ';
    personagem.passo = 0;
    personagem.atingido = 0;

    bomb[0] = (BOMBA) {0, 0, 0};
    existe_bomba = 0;
    max_bombas = 1;
    range = 2;

    fez_recorde = 0;

    for (i=0; i<9; i++)
    {
        inimigo[i].movendo = 0;
    }
}

int Inicializa_SDL ()
{
    if ((SDL_Init (SDL_INIT_EVERYTHING)) == -1)
    {
        puts ("Nao foi possivel iniciar a SDL.");
        return 1;
    }
    if ((Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) == -1))
    {
        puts ("Nao foi possivel inicializar o audio.");
    }
    if(TTF_Init() == -1)
	{
		puts ("Nao foi possivel carregar a SDL_TTF.");
		return 3;
	}
    return 0;
}

int Carrega_Menu ()
{
	nome_do_jogo = IMG_Load ("nome_do_jogo.png");
	if (!nome_do_jogo)
	{
		puts ("Nao foi possivel carregar imagem.");
		return 1;
	}
	pinguim = IMG_Load ("killbill.png");
	if (!pinguim)
	{
		puts ("Nao foi possivel carregar imagem.");
		return 1;
	}
	janela = IMG_Load ("janela.png");
	if (!janela)
	{
		puts ("Nao foi possivel carregar imagem.");
		return 1;
	}
	maca = IMG_Load ("maca.png");
	if (!maca)
	{
		puts ("Nao foi possivel carregar imagem.");
		return 1;
	}
	bomber = IMG_Load ("bomber.png");
	if (!bomber)
	{
		puts ("Nao foi possivel carregar imagem.");
		return 1;
	}

    if (!(clica = Mix_LoadWAV ("Sons/clique.wav")))
    {
        puts ("Impossivel carregar audio.");
        return 5;
    }
	return 0;
}

int Carrega_Versao_IMG (int versao)
{
    char *player, *bg, *bomba_img, *bonus1_img, *bonus2_img, *bloco_dest_img, *bloco_ind_img, *in2, *in3, *in4;

    jogador.versao = versao;

    switch (versao)
    {
        case LINUX:
            player = (char*) {"Img/pinguim.gif"};
            bg = (char*) {"Img/fundo.png"};
            bomba_img = (char*) {"Img/bomba.png"};
            bonus1_img = (char*) {"Img/bonus1.png"};
            bonus2_img = (char*) {"Img/bonus2.png"};
            bloco_dest_img = (char*) {"Img/destrutivel.png"};
            bloco_ind_img = (char*) {"Img/indestrutivel.gif"};
            in2 = (char*) {"Img/bomberman.gif"};
            in3 = (char*) {"Img/maca.gif"};
            in4 = (char*) {"Img/billy.gif"};
            break;
        case MAC:
            player = (char*) {"Img/maca.gif"};
            bg = (char*) {"Img/fundo.png"};
            bomba_img = (char*) {"Img/bomba.png"};
            bonus1_img = (char*) {"Img/bonus1.png"};
            bonus2_img = (char*) {"Img/bonus2.png"};
            bloco_dest_img = (char*) {"Img/destrutivel.png"};
            bloco_ind_img = (char*) {"Img/arvore.gif"};
            in2 = (char*) {"Img/pinguim_mau.gif"};
            in3 = (char*) {"Img/pinguim.gif"};
            in4 = (char*) {"Img/billy.gif"};
            break;
        case WINDOWS:
            player = (char*) {"Img/billy.gif"};
            bg = (char*) {"Img/fundo.png"};
            bomba_img = (char*) {"Img/bomba.png"};
            bonus1_img = (char*) {"Img/bonus1.png"};
            bonus2_img = (char*) {"Img/bonus2.png"};
            bloco_dest_img = (char*) {"Img/destrutivel.png"};
            bloco_ind_img = (char*) {"Img/window.gif"};
            in2 = (char*) {"Img/pinguim_mau.gif"};
            in3 = (char*) {"Img/maca.gif"};
            in4 = (char*) {"Img/pinguim.gif"};
            break;
        case BOMBER:
            player = (char*) {"Img/bomberman.gif"};
            bg = (char*) {"Img/fundo.png"};
            bomba_img = (char*) {"Img/bomba.png"};
            bonus1_img = (char*) {"Img/bonus1.png"};
            bonus2_img = (char*) {"Img/bonus2.png"};
            bloco_dest_img = (char*) {"Img/destrutivel.png"};
            bloco_ind_img = (char*) {"Img/indestrutivel.gif"};
            in2 = (char*) {"Img/billy.gif"};
            in3 = (char*) {"Img/pinguim.gif"};
            in4 = (char*) {"Img/pinguim_mau.gif"};
            break;
        default:
            break;
    }

    if (!(personagem.img = IMG_Load (player)))
    {
        puts ("Impossivel carregar imagens da versao.");
        return 1;
    }
    SDL_SetColorKey (personagem.img, SDL_SRCCOLORKEY, SDL_MapRGB (personagem.img->format, 255, 0, 255));
    if (!(fundo = IMG_Load (bg)))
    {
        puts ("Impossivel carregar imagens da versao.");
        return 1;
    }
    if (!(bomba = IMG_Load (bomba_img)))
    {
        puts ("Impossivel carregar imagens da versao.");
        return 1;
    }
    if (!(bonus1 = IMG_Load (bonus1_img)))
    {
        puts ("Impossivel carregar imagens da versao.");
        return 1;
    }
    if (!(bonus2 = IMG_Load (bonus2_img)))
    {
        puts ("Impossivel carregar imagens da versao.");
        return 1;
    }
    if (!(bloco_dest = IMG_Load (bloco_dest_img)))
    {
        puts ("Impossivel carregar imagens da versao.");
        return 1;
    }
    if (!(bloco_ind = IMG_Load (bloco_ind_img)))
    {
        puts ("Impossivel carregar imagens da versao.");
        return 1;
    }
    if (!(explosao_hor = IMG_Load ("Img/explosao_hor.png")))
    {
        puts ("Impossivel carregar imagens da versao.");
        return 1;
    }
    if (!(explosao_vert = IMG_Load ("Img/explosao_vert.png")))
    {
        puts ("Impossivel carregar imagens da versao.");
        return 1;
    }
    if (!(explosao_centro = IMG_Load ("Img/explosao_centro.png")))
    {
        puts ("Impossivel carregar imagens da versao.");
        return 1;
    }
    if (!(inimigo1 = IMG_Load ("Img/troia.gif")))
    {
        puts ("Impossivel carregar imagens da versao.");
        return 1;
    }
    if (!(inimigo2 = IMG_Load (in2)))
    {
        puts ("Impossivel carregar imagens da versao.");
        return 1;
    }
    if (!(inimigo3 = IMG_Load (in3)))
    {
        puts ("Impossivel carregar imagens da versao.");
        return 1;
    }
    if (!(inimigo4 = IMG_Load (in4)))
    {
        puts ("Impossivel carregar imagens da versao.");
        return 1;
    }
    if (!(porta = IMG_Load ("Img/saida.gif")))
    {
        puts ("Impossivel carregar imagens da versao.");
        return 1;
    }

    Define_Transparencias ();

	return 0;
}

int Carrega_Versao_Som (int versao)
{
    char *som_bomba;

    switch (versao)
    {
        case LINUX:
        case MAC:
        case WINDOWS:
            som_bomba = (char*) {"Sons/bomba.wav"};
            break;
        case BOMBER:
            som_bomba = (char*) {"Sons/BUM.wav"};
            if (!(planta_bomba = Mix_LoadWAV ("Sons/BOMBA_.wav")))
            {
                puts ("Impossivel carregar audio.");
                exit(5);
            }
            break;
        default:
            break;
    }
    if (!(explosao = Mix_LoadWAV (som_bomba)))
    {
        puts ("Impossivel carregar audio.");
        exit(5);
    }

    return 0;
}

int Carrega_Mapa ()
{
    FILE* arquivo;
    char nome[32];

    sprintf (nome, "fase%d.map", fase);

    if (!(arquivo = fopen (nome, "r")))
    {
        printf ("%d\n", fase);
        puts ("Nao foi possivel carregar mapa.");
        return 1;
    }
    fread (mapa, sizeof(mapa), 1, arquivo);

    fclose (arquivo);
    return 0;
}

Uint32 Carrega_Fase_Seguinte (Uint32 interval, void *param)
{
    existe_bomba = 0;
    inicio_fila = fim_fila;
    inicio_fila2 = fim_fila2;
    fase++;
    if (Carrega_Mapa ())
    {
        exit(4);
    }
    personagem.i = 1;
    personagem.j = 1;
    personagem.origem = (SDL_Rect) {0, 0, 40, 40};
    personagem.destino = (SDL_Rect) {40, 40, 0, 0};
    do
    {
        saida.i = rand()%14;
        saida.j = rand()%14;
    } while (mapa[saida.i][saida.j] != 2 || saida.i < 11 || saida.j < 11);
    venceu = 0;
    Prepara_Inimigos ();
    inicio_fase = SDL_GetTicks ();

    estado = JOGO;
    Mix_PlayMusic (jogo, -1);

    return 0;
}

void Prepara_Inimigos ()
{
    int i;

    for (i=0; i<9; i++)
    {
        inimigo[i].origem = (SDL_Rect) {0, 0, 40, 40};
    }

    switch (fase)
    {
        case 1:
            inimigo[0].i = 13;
			inimigo[0].j = 12;
			inimigo[0].nivel = 1;
			inimigo[1].i = 1;
			inimigo[1].j = 11;
			inimigo[1].nivel = 1;
			inimigo[2].i = 13;
			inimigo[2].j = 1;
			inimigo[2].nivel = 1;
			inimigo[3].i = 10;
			inimigo[3].j = 3;
			inimigo[3].nivel = 1;
			inimigo[4].i = 8;
			inimigo[4].j = 9;
			inimigo[4].nivel = 1;
			inimigo[5].i = 4;
			inimigo[5].j = 4;
			inimigo[5].nivel = 1;
            for (i=0; i<6; i++)
            {
                inimigo[i].destino = (SDL_Rect) {inimigo[i].j*LADO, inimigo[i].i*LADO, 0, 0};
                inimigo[i].estado = VIVO;
            }
            break;
        case 2:
            inimigo[0].i = 13;
            inimigo[0].j = 12;
            inimigo[0].nivel = 2;
            inimigo[1].i = 1;
            inimigo[1].j = 12;
            inimigo[1].nivel = 2;
            inimigo[2].i = 13;
            inimigo[2].j = 1;
            inimigo[2].nivel = 2;
            inimigo[3].i = 10;
            inimigo[3].j = 3;
            inimigo[3].nivel = 2;
            inimigo[4].i = 8;
            inimigo[4].j = 4;
            inimigo[4].nivel = 2;
            inimigo[5].i = 4;
            inimigo[5].j = 4;
            inimigo[5].nivel = 2;
            for (i=0; i<6; i++)
            {
                inimigo[i].destino = (SDL_Rect) {inimigo[i].j*LADO, inimigo[i].i*LADO, 0, 0};
                inimigo[i].estado = VIVO;
            }
            break;
        case 3:
        	inimigo[0].i = 13;
			inimigo[0].j = 8;
			inimigo[0].nivel = 3;
			inimigo[1].i = 1;
			inimigo[1].j = 8;
			inimigo[1].nivel = 3;
			inimigo[2].i = 12;
			inimigo[2].j = 1;
			inimigo[2].nivel = 3;
			inimigo[3].i = 10;
			inimigo[3].j = 3;
			inimigo[3].nivel = 3;
			inimigo[4].i = 8;
			inimigo[4].j = 9;
			inimigo[4].nivel = 3;
			inimigo[5].i = 4;
			inimigo[5].j = 10;
			inimigo[5].nivel = 3;
			for (i=0; i<6; i++)
			{
				inimigo[i].destino = (SDL_Rect) {inimigo[i].j*LADO, inimigo[i].i*LADO, 0, 0};
				inimigo[i].estado = VIVO;
            }
            break;
        case 4:
        	inimigo[0].i = 13;
			inimigo[0].j = 12;
			inimigo[0].nivel = 2;
			inimigo[1].i = 1;
			inimigo[1].j = 11;
			inimigo[1].nivel = 3;
			inimigo[2].i = 13;
			inimigo[2].j = 1;
			inimigo[2].nivel = 2;
			inimigo[3].i = 10;
			inimigo[3].j = 3;
			inimigo[3].nivel = 3;
			inimigo[4].i = 8;
			inimigo[4].j = 9;
			inimigo[4].nivel = 2;
			inimigo[5].i = 4;
			inimigo[5].j = 4;
			inimigo[5].nivel = 3;
			for (i=0; i<6; i++)
			{
				inimigo[i].destino = (SDL_Rect) {inimigo[i].j*LADO, inimigo[i].i*LADO, 0, 0};
				inimigo[i].estado = VIVO;
            }
            break;
        case 5:
        	inimigo[0].i = 13;
			inimigo[0].j = 12;
			inimigo[0].nivel = 4;
			inimigo[1].i = 1;
			inimigo[1].j = 11;
			inimigo[1].nivel = 4;
			inimigo[2].i = 13;
			inimigo[2].j = 1;
			inimigo[2].nivel = 4;
			inimigo[3].i = 10;
			inimigo[3].j = 3;
			inimigo[3].nivel = 4;
			inimigo[4].i = 8;
			inimigo[4].j = 9;
			inimigo[4].nivel = 3;
			inimigo[5].i = 4;
			inimigo[5].j = 4;
			inimigo[5].nivel = 3;
			for (i=0; i<6; i++)
			{
				inimigo[i].destino = (SDL_Rect) {inimigo[i].j*LADO, inimigo[i].i*LADO, 0, 0};
				inimigo[i].estado = VIVO;
            }
            break;
        default:
            break;
    }
    for (i=0; i<6; i++)
    {
        inimigo[i].atingido = 0;
        switch (inimigo[i].nivel)
        {
            case 1:
                inimigo[i].vidas = 1;
                break;
            case 2:
                inimigo[i].vidas = 1;
                break;
            case 3:
                inimigo[i].vidas = 1;
                break;
            case 4:
                inimigo[i].vidas = 2;
                break;
        }
    }
}

void Define_Botoes ()
{
    int i;

    switch (estado)
    {
        case MENU:
            botoes[0] = (SDL_Rect) {SCREEN_W/2-100, 200, 200, 60};
            for (i=1; i<6; i++)
            {
                botoes[i] = (SDL_Rect) {SCREEN_W/2-100, botoes[i-1].y + botoes[i-1].h, 200, 60};
            }
            for (i=6; i<10; i++)
            {
                botoes[i] = (SDL_Rect) {SCREEN_W/2+100, botoes[i-6].y, 200, 60};
            }
            for (i=10; i<15; i++)
            {
                botoes[i] = (SDL_Rect) {SCREEN_W/2+100, botoes[i-7].y, 200, 60};
            }
            break;
        case LE_NOME:
            botoes[0] = (SDL_Rect) {80, 420, 160, 60};
            botoes[1] = (SDL_Rect) {240, 420, 160, 60};
            botoes[2] = (SDL_Rect) {400, 420, 160, 60};
            botoes[3] = (SDL_Rect) {560, 420, 160, 60};
            botoes[4] = (SDL_Rect) {SCREEN_W/2-80, 520, 160, 60};
            break;
        case CARREGAR:
            botoes[0] = (SDL_Rect) {SCREEN_W/2-300, 190, 600, 60};
            botoes[1] = (SDL_Rect) {SCREEN_W/2-300, 250, 600, 60};
            botoes[2] = (SDL_Rect) {SCREEN_W/2-300, 310, 600, 60};
            botoes[3] = (SDL_Rect) {SCREEN_W/2-300, 370, 600, 60};
            botoes[4] = (SDL_Rect) {SCREEN_W/2-300, 430, 600, 60};
            botoes[5] = (SDL_Rect) {SCREEN_W/2-80, 550, 160, 40};
            break;
        case RECORDES_T:
            botoes[0] = (SDL_Rect) {200, 550, 100, 30};
            botoes[1] = (SDL_Rect) {500, 550, 100, 30};
            break;
        case RECORDES_P:
            botoes[0] = (SDL_Rect) {200, 550, 100, 30};
            botoes[1] = (SDL_Rect) {500, 550, 100, 30};
            break;
        case INSTRUCOES:
            botoes[0] = (SDL_Rect) {SCREEN_W/2-50, 550, 100, 30};
            break;
        case CREDITOS:
            botoes[0] = (SDL_Rect) {10, 560, 100, 30};
            break;
        case PAUSA:
            botoes[0] = (SDL_Rect) {SCREEN_W/2-100, 190, 200, 60};
            botoes[1] = (SDL_Rect) {SCREEN_W/2-100, 250, 200, 60};
            botoes[2] = (SDL_Rect) {SCREEN_W/2-100, 310, 200, 60};
            botoes[3] = (SDL_Rect) {SCREEN_W/2-100, 370, 200, 60};
            botoes[4] = (SDL_Rect) {SCREEN_W/2-100, 430, 200, 60};
            break;
        case SALVA:
            botoes[0] = (SDL_Rect) {SCREEN_W/2-100, 190, 200, 60};
            botoes[1] = (SDL_Rect) {SCREEN_W/2-100, 250, 200, 60};
            botoes[2] = (SDL_Rect) {SCREEN_W/2-100, 310, 200, 60};
            botoes[3] = (SDL_Rect) {SCREEN_W/2-100, 370, 200, 60};
            botoes[4] = (SDL_Rect) {SCREEN_W/2-100, 430, 200, 60};
            botoes[5] = (SDL_Rect) {120, 470, 80, 25};
            break;
        case GAMEOVER :
            botoes[0] = (SDL_Rect) {200, 450, 150, 60};
            botoes[1] = (SDL_Rect) {450, 450, 150, 60};
            break;
    }
}

void Carrega_Dados ()
{
    int i;
    FILE* arq;

    if (!(arq = fopen ("recordes_t.data", "r")))
    {
        puts ("Impossivel carregar melhores tempos.");
    }
    fread (recordista_T, sizeof(recordista_T), 1, arq);
    fclose (arq);

    if (!(arq = fopen ("recordes_p.data", "r")))
    {
        puts ("Impossivel carregar melhores pontuacoes.");
    }
    fread (recordista_P, sizeof(recordista_P), 1, arq);
    fclose (arq);

    if (!(arq = fopen ("jogo.save", "r")))
    {
        puts ("Impossivel carregar jogos salvos.");
    }
    fread (saves, sizeof(saves), 1, arq);
    fclose (arq);

    for (i=0; i<SAVES_NUM; i++)
    {
        if (!saves[i].existe)
        {
            sprintf (saves[i].nome, "Vazio");
        }
    }
}

void Carrega_Jogo (int slot)
{
    fase = saves[slot].fase;
    Carrega_Versao_IMG (saves[slot].versao);
    Carrega_Versao_Som (saves[slot].versao);
    Carrega_Fase_Seguinte (0, NULL);
    vidas = saves[slot].vidas;
    jogador.pontos = saves[slot].pontos;
    jogador.tempo = saves[slot].tempo;
    dificuldade = saves[slot].dificuldade;
    estado = JOGO;
    Mix_PlayMusic (jogo, -1);
    SDL_EnableKeyRepeat (5, 10);
}

void Define_Transparencias ()
{
    SDL_SetColorKey (porta, SDL_SRCCOLORKEY, SDL_MapRGB (porta->format, 255, 0, 255));

    SDL_SetColorKey (inimigo1, SDL_SRCCOLORKEY, SDL_MapRGB (inimigo1->format, 255, 0, 255));
    SDL_SetColorKey (inimigo2, SDL_SRCCOLORKEY, SDL_MapRGB (inimigo2->format, 255, 0, 255));
    SDL_SetColorKey (inimigo3, SDL_SRCCOLORKEY, SDL_MapRGB (inimigo3->format, 255, 0, 255));
    SDL_SetColorKey (inimigo4, SDL_SRCCOLORKEY, SDL_MapRGB (inimigo4->format, 255, 0, 255));
    SDL_SetColorKey (bloco_ind, SDL_SRCCOLORKEY, SDL_MapRGB (bloco_ind->format, 255, 0, 255));

}

int Carrega_Sons ()
{
    Mix_AllocateChannels(10);

    if (!(menu = Mix_LoadMUS("Sons/menu.wav")))
    {
        puts ("Impossivel carregar musica.");
    }
    if (!(jogo = Mix_LoadMUS("Sons/jogo.ogg")))
    {
        puts ("Impossivel carregar musica.");
    }
    if (!(vitoria = Mix_LoadMUS("Sons/vitoria.ogg")))
    {
        puts ("Impossivel carregar musica.");
    }
    if (!(derrota = Mix_LoadMUS("Sons/gameover.ogg")))
    {
        puts ("Impossivel carregar musica.");
    }
    if (!(le_nome = Mix_LoadMUS("Sons/le_nome.ogg")))
    {
        puts ("Impossivel carregar musica.");
    }
    return 0;
}

