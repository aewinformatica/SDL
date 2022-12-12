/*Computação para Informática (Linguagem C) 2008/1
Professor: Adriano
Trabalho: Jogo3.c (Teste 7)
Data: 18/06/08

Alunos:	Felipe Guerreiro Barbosa Ruiz ( DRE 108056195)
		Gabriel Pires da Silva ( DRE 108056014)
		Guilherme Carneiro Antonio ( DRE 108055602 )*/

#include "meuinclude.h"

	//   1 == BLOCO
	//  2 == BORDA
	//  4 == SAIDA
	//  7 ==  DESTRUTÍVEL
	// 19 == FOGO
	// 20 + B == BOMBA    | 0 <= B <=20 |
	// 37 == SAIDA + BLOCO



void montarMapa(void)
{
	memset(matriz_controle,0,sizeof(matriz_controle));
	memset(matriz_itens,0,sizeof(matriz_itens));
	memset(matriz_personagens,0,sizeof(matriz_itens));

	matriz_personagens[1][1]=1;

	calculaBlocosF();
	calculaBlocosD();
	calculaItens();
	calculaInimigos();
}

void calculaBlocosF(void)
{
	//GERANDO BORDAS, BLOCOS FIXOS E SAIDA

	//CONTROLADORES
	int i, j;

	//DEFININDO TAMANHOS
	int largura, altura;
	largura = (SCREEN_W/32);
	altura = ((SCREEN_H-32)/32);

	//BORDA
	{
	for(i=0;i<largura;i++)
	{
		matriz_controle[i][0]=2;
		matriz_controle[i][altura-1]=2;
	}
	for(i=0;i<altura;i++)
	{
		matriz_controle[0][i]=2;
		matriz_controle[largura-1][i]=2;
	}
	}


	//GERANDO BLOCOS FIXOS
	for(i=0;i<21;i++)
	{
		for(j=0;j<15;j++)
		{
              if(j!=0 && i!= 0)
              {
                      if (j%2 == 0 && i%2 == 0)
                      {
                              matriz_controle[i][j]=1;
                      }
              }
        }
	}



}

void calculaBlocosD(void)
{
	//GERA BLOCOS DESTRUTIVEIS

	//CONTROLADORES
	int i, a, b;

	//DEFININDO TAMANHOS
	int largura, altura;
	largura = (SCREEN_W/32);
	altura = ((SCREEN_H-32)/32);

	for(i=0; i < fases[faseAtual].blocosD ; i++)
	{
		srand(time(NULL));
		a = (rand()%(largura-1))+1;
		b = (rand()%(altura-1))+1;
		while(matriz_controle[a][b]!=0 || matriz_personagens[a][b]!=0)
		{
			a = (rand()%(largura-1))+1;
			b = (rand()%(altura-1))+1;
		}
		matriz_controle[a][b]=7;
	}

    //GERANDO SAIDA
	a = (rand()%(largura-1))+1;
	b = (rand()%(altura-1))+1;
	while(matriz_controle[a][b]!=7 || matriz_personagens[a][b]!=0)
	{
		a=(rand()%(largura-1))+1;
		b=(rand()%(altura-1))+1;
	}
	matriz_itens[a][b]=37;
}

void valoresFases(void)
{
	fases[0].blocosD = 20;
	fases[0].blocosF = 50;
	fases[0].inimigos = 3;
	fases[0].itens = 6;

}

void calculaItens(void)
{
	int i, a, b;

	//DEFININDO TAMANHOS
	int largura, altura;
	largura = (SCREEN_W/32);
	altura = ((SCREEN_H-32)/32);

	for(i=0; i < fases[faseAtual].itens ; i++)
	{
		srand(time(NULL));
		a = (rand()%(largura-1))+1;
		b = (rand()%(altura-1))+1;
		while(matriz_controle[a][b]!=7 || matriz_itens[a][b]!=0)
		{
			a = (rand()%(largura-1))+1;
			b = (rand()%(altura-1))+1;
		}
		matriz_itens[a][b]=(i%TOTALITENS)+1;
	}

}

void morrePersonagem(void)
{
	int gradex, gradey;
	Mix_Chunk *efeito;

	efeito=Mix_LoadWAV("../Sons/killedkenny.wav");

	//VALORES DA GRADE
	gradex = (Kenny.destino.x/32);
	gradey = ((Kenny.destino.y+32)/32);

	//ZERANDO ITENS E VALOR DO PERSONAGEM
	matriz_personagens[gradex][gradey] = 0;
	Kenny.origem.x=32;
	Kenny.origem.y=128;
	Kenny.passo.cima=0;
	Kenny.passo.baixo=2;
	Kenny.passo.direita=0;
	Kenny.passo.esquerda=0;
	jogo.vidas-=1;
	Mix_PlayChannel(-1,efeito,0);
//	raio=1;
//	maxBombas=1;
	Kenny.destino.x=32;
	Kenny.destino.y=0;
	matriz_personagens[1][1] = 1;
}



int colisaoBaixo(int x, int y)
{
	int linha, coluna;
	y+=32;

	coluna=x/32;
	linha=y/32;

	if(matriz_controle[coluna][linha+1]==1 || matriz_controle[coluna][linha+1]==7 || matriz_controle[coluna][linha+1]==2)//PRIMEIRA COLISAO
	{
		return 1;
	}
	else if(matriz_personagens[coluna][linha+1]>=2 && matriz_personagens[coluna][linha+1]<2+MAXINIMIGOS)
	{
		morrePersonagem();
		return 1;
	}
	return 0;
}

int colisaoCima(int x, int y, int vel)
{
	int linha, coluna;
	y+=32-vel;

	coluna=x/32;
	linha=y/32;

	if(matriz_controle[coluna][linha]==1 || matriz_controle[coluna][linha]==7 || matriz_controle[coluna][linha]==2)//PRIMEIRA COLISAO
	{
		return 1;
	}
	else if(matriz_personagens[coluna][linha]>=2 && matriz_personagens[coluna][linha]<2+MAXINIMIGOS)
	{
		morrePersonagem();
		return 1;
	}

	return 0;
}

int colisaoDireita(int x, int y)
{
	int coluna, linha;
	y+=32;
	x+=32;

	coluna = x/32;
	linha = y/32;

	if(matriz_controle[coluna][linha]==1 || matriz_controle[coluna][linha]==7 || matriz_controle[coluna][linha]==2)
	{
		return 1;
	}
	else if(matriz_personagens[coluna][linha]>=2 && matriz_personagens[coluna][linha]<2+MAXINIMIGOS)
	{
		morrePersonagem();
		return 1;
	}
	return 0;
}

int colisaoEsquerda(int x, int y, int vel)
{
	int coluna, linha;

	x-=(32-(3*vel));
	y+=32;

	coluna=x/32;
	linha=y/32;

	if(matriz_controle[coluna][linha]==1 || matriz_controle[coluna][linha]==7 || matriz_controle[coluna][linha]==2)
	{
		return 1;
	}
	else if(matriz_personagens[coluna][linha]>=2 && matriz_personagens[coluna][linha]<2+MAXINIMIGOS)
	{
		morrePersonagem();
		return 1;
	}
	return 0;
}

int colisaoSaida(int x, int y)
{
	int coluna, linha;

	y+=32;

	coluna=x/32;
	linha=y/32;

	if(matriz_controle[coluna][linha]==4 && !(x%32) && !(y%32))
	{
		return 1;
		tempo_total=SDL_GetTicks();
	}
	return 0;
	salva_recordes();
	salva(jogo.slot);
}

void colisaoItem(int x, int y)
{
	y+=32;
	x/=32;
	y/=32;

	if(matriz_controle[x][y] == 10)
	{
		jogo.vidas+=1;
		matriz_controle[x][y] = 0;
		matriz_itens[x][y] = 0;
	}
	else if(matriz_controle[x][y] == 11)
	{
		maxBombas+=1;
		matriz_controle[x][y] = 0;
		matriz_itens[x][y] = 0;
	}
	else if(matriz_controle[x][y] == 12)
	{
		raio+=1;
		matriz_controle[x][y] = 0;
		matriz_itens[x][y] = 0;
	}
	else if(matriz_controle[x][y] == 13)
	{
		jogo.pontos+=500;
		matriz_controle[x][y] = 0;
		matriz_itens[x][y] = 0;
	}
	else if(matriz_controle[x][y] == 18)
	{
		matriz_controle[x][y] = 4;
		matriz_itens[x][y] = 0;
	}
}





int explodeBomba (int x, int y, int r, int *bomba, int *cont_explosao)
{
	if(*bomba==1)//Se bomba for colocada
	{
		int b;//VARIAVEL CONTADORA DE TEMPO
		x /= 32;
		y /= 32;
		if(contador==0)//SE TEMPO DA BOMBA ATUAL FOR SER INICIADO
		{
			a=SDL_GetTicks();//PEGA TEMPO INICIAL
			contador++; //NAO PEGAR O TEMPO INICIAL MAIS DE UMA VEZ
		}
		b = SDL_GetTicks();
		if(b-a >= 5000)//TEMPO DECORRIDO DESDE A BOMBA TER SIDO COLOCADA
		{
			matriz_controle[x][y] = 6;
			contador=0;
			*bomba=0;
			*cont_explosao=1;
			return b;
		}
	}
	return 0;
}

void reinicia_jogo(SDL_Rect *boneco_dst,int *cima, int *baixo, int *esquerda, int *direita, int *bomba)
{
	int gradex, gradey;

	//VALORES DA GRADE
	gradex = (Kenny.destino.x/32);
	gradey = ((Kenny.destino.y+32)/32);

	//ZERANDO ITENS E VALOR DO PERSONAGEM
	matriz_personagens[gradex][gradey] = 0;
	matriz_personagens[1][1] = 1;
	montarMapa();
	*cima=0;
	*baixo=0;
	*direita=0;
	*esquerda=0;
	*bomba=0;
	a=0;
	boneco_dst->x=32;
	boneco_dst->y=0;
}

void desenha_texto(char* text, SDL_Surface* dst, int x, int y, int tam, int cor1, int cor2, int cor3)
{
	TTF_Font *fonte;
	fonte = TTF_OpenFont("Fontes/south_park2.TTF", tam);

	SDL_Color cor = {cor1,cor2,cor3}; //vermelho
	SDL_Surface* src = TTF_RenderText_Blended(fonte, text, cor);
	SDL_Rect dst_rect = {x, y, 0, 0};

	SDL_BlitSurface(src, NULL, dst, &dst_rect);

	TTF_CloseFont(fonte);
	SDL_FreeSurface(src);
}

int pausarJogo(int *pause, SDL_Event *evento)
{
	int quit=0;
	while(!quit && *pause==1)
	{
		while(SDL_PollEvent(evento))
		{
			switch((*evento).type)
			{
				case SDL_QUIT:
					exit(0);
					break;

				case SDL_KEYDOWN:
					switch((*evento).key.keysym.sym)
					{
						case SDLK_ESCAPE:
							exit(0);
							break;

						case SDLK_p:
							*pause=0;
							return 0;
							break;

						case SDLK_m:
							return 666;
						default:
							break;
					}
					break;
			}
		}
	}
	return 0;
}






void tempoBomba(_BOMBA *bomba, _FOGO *fogo, int *bombasAtivas, int *fogosAtivos, int *bseq)
{
	int tempoAtual;
	tempoAtual = SDL_GetTicks();
	if(tempoAtual - ((*bomba).tempoini) > tempoExpBomba)
	{
		matriz_controle[(*bomba).gradex][(*bomba).gradey] = 0;
		(*bomba).status =1;
		*bombasAtivas-=1;
		//FOGO
		(*fogo).status = 2;
		(*fogo).tempoini = SDL_GetTicks();
		(*fogo).gradex = (*bomba).gradex;
		(*fogo).gradey = (*bomba).gradey;
		(*fogo).posicao.x = ((*fogo).gradex) * 32;
		(*fogo).posicao.y = ((*fogo).gradey) * 32;
		*fogosAtivos+=1;

		//CHAMA A FUNCAO PINTA FOGO COM ESSE FOGO
		pintaFogo(fogo, bseq);

	}

}

void tempoFogo(_FOGO *fogo, int *fogosAtivos)
{
	int tempoAtual = SDL_GetTicks();
	if(tempoAtual - ((*fogo).tempoini) > tempoPintaFogo)
	{
		despintaFogo(fogo);
		*fogosAtivos -= 1;
		(*fogo).status = 1;
	}
}

int verificaItem(int gradex, int gradey)
{
	int b;

	for(b=0; b<TOTALITENS ; b++)
	{
		if(matriz_itens[gradex][gradey] == b+1)
		{
			return 10+b;
		}
	}
	//ALTERADO DE MADRUGADA PELO GABRIEL! ACRESCENTANDO O CASO DA SA�DA EMBUTIDA!
	if(matriz_itens[gradex][gradey] == 37)
	{
        return 4;
    }
	return 19;

}

void pintaFogo(_FOGO *fogo, int *bseq)
{
	int gradex, gradey, I_gradex, I_gradey, c, k;
	int pcima=0, pbaixo=0, pdir=0, pesq=0;
	I_gradex = (*fogo).gradex;
	I_gradey = (*fogo).gradey;

	matriz_controle[I_gradex][I_gradey] = 19;

	if(matriz_personagens[I_gradex][I_gradey] == 1)
	{
		jogo.vidas -= 1;
	}


	//PINTAR PARA CIMA
	for(c=1;c<=raio; c++)
	{
		gradex = I_gradex;
		gradey = I_gradey - c;

		//CAMPO LIMPO
		if(matriz_controle[gradex][gradey] == 0 && !pcima)
		{
			matriz_controle[gradex][gradey] = 19;
		}
		//CAMPOS NAO DESTRUTIVEIS
		else if((matriz_controle[gradex][gradey] == 1 || matriz_controle[gradex][gradey] == 2 || matriz_controle[gradex][gradey] == 4) && !pcima)
		{
			pcima=1;
		}
		// ITENS
		else if( (matriz_controle[gradex][gradey] >= 10 && matriz_controle[gradex][gradey]<=TOTALITENS+10) && !pcima)
		{
			matriz_controle[gradex][gradey] = 19;
		}
		//OBJETOS DESTRUTIVEIS
		else if(matriz_controle[gradex][gradey] == 7 && !pcima)
		{
			matriz_controle[gradex][gradey] = verificaItem(gradex,gradey);
			pcima=1;
			jogo.pontos+=10;
		}
		//OUTRA BOMBA
		else if((matriz_controle[gradex][gradey] >= 20 && matriz_controle[gradex][gradey] < 20 + maxBombas) && !pcima)
		{
			for(k=0; k<maxBombas;k++)
			{
				if(matriz_controle[gradex][gradey] == 20+k)
				{
					*bseq=k;
					pcima=1;
				}
			}
		}

		//ATINGE PERSONAGEM
		if(matriz_personagens[gradex][gradey] == 1 && !pcima)
		{
			morrePersonagem();
		}
		//ATINGE INIMIGO
		else if(matriz_personagens[gradex][gradey] >= 2 && matriz_personagens[gradex][gradey] <2+MAXINIMIGOS && !pcima)
		{
			for(k=0;k<fases[faseAtual].inimigos;k++)
			{
				if(matriz_personagens[gradex][gradey] == (2+k) && inimigos[k].status==1)
				{
					inimigos[k].status=2;
					matriz_personagens[gradex][gradey] = 0;
					jogo.pontos+=100;
				}
			}
		}
	}

	//FOGO PARA BAIXO
	for(c=1;c<=raio; c++)
	{
		gradex = I_gradex;
		gradey = I_gradey + c;

		//CAMPO LIMPO
		if(matriz_controle[gradex][gradey] == 0 && !pbaixo)
		{
			matriz_controle[gradex][gradey] = 19;
		}
		//CAMPOS NAO DESTRUTIVEIS
		else if((matriz_controle[gradex][gradey] == 1 || matriz_controle[gradex][gradey] == 2 || matriz_controle[gradex][gradey] == 4) && !pbaixo)
		{
			pbaixo=1;
		}
		// ITENS
		else if( (matriz_controle[gradex][gradey] >= 10 && matriz_controle[gradex][gradey]<=TOTALITENS+10) && !pbaixo)
		{
			matriz_controle[gradex][gradey] = 19;
		}
		//OBJETOS DESTRUTIVEIS
		else if(matriz_controle[gradex][gradey] == 7 && !pbaixo)
		{
			matriz_controle[gradex][gradey] = verificaItem(gradex,gradey);
			pbaixo=1;
			jogo.pontos+=10;
		}
		//OUTRA BOMBA
		else if((matriz_controle[gradex][gradey] >= 20 && matriz_controle[gradex][gradey] < 20 + maxBombas) && !pbaixo)
		{
			for(k=0; k<maxBombas;k++)
			{
				if(matriz_controle[gradex][gradey] == 20+k)
				{
					*(bseq+1)=k;
					pbaixo=1;
				}
			}
		}
		//ATINGE PERSONAGEM
		if(matriz_personagens[gradex][gradey] == 1 && !pbaixo)
		{
			morrePersonagem();
		}
		//ATINGE INIMIGO
		else if(matriz_personagens[gradex][gradey] >= 2 && matriz_personagens[gradex][gradey] <2+MAXINIMIGOS && !pbaixo)
		{
			for(k=0;k<fases[faseAtual].inimigos;k++)
			{
				if(matriz_personagens[gradex][gradey] == (2+k) && inimigos[k].status==1)
				{
					inimigos[k].status=2;
					matriz_personagens[gradex][gradey] = 0;
					jogo.pontos+=100;
				}
			}
		}
	}

	//FOGO PARA DIREITA
	for(c=1;c<=raio; c++)
	{
		gradex = I_gradex + c;
		gradey = I_gradey;

		//CAMPO LIMPO
		if(matriz_controle[gradex][gradey] == 0 && !pdir)
		{
			matriz_controle[gradex][gradey] = 19;
		}
		//CAMPOS NAO DESTRUTIVEIS
		else if((matriz_controle[gradex][gradey] == 1 || matriz_controle[gradex][gradey] == 2 || matriz_controle[gradex][gradey] == 4) && !pdir)
		{
			pdir=1;
		}
		// ITENS
		else if( (matriz_controle[gradex][gradey] >= 10 && matriz_controle[gradex][gradey]<=TOTALITENS+10) && !pdir)
		{
			matriz_controle[gradex][gradey] = 19;
		}
		//OBJETOS DESTRUTIVEIS
		else if(matriz_controle[gradex][gradey] == 7 && !pdir)
		{
			matriz_controle[gradex][gradey] = verificaItem(gradex,gradey);
			pdir=1;
			jogo.pontos+=10;
		}
		//OUTRA BOMBA
		else if((matriz_controle[gradex][gradey] >= 20 && matriz_controle[gradex][gradey] < 20 + maxBombas) && !pdir)
		{
			for(k=0; k<maxBombas;k++)
			{
				if(matriz_controle[gradex][gradey] == 20+k)
				{
					*(bseq+2)=k;
					pdir=1;
				}
			}
		}
		//ATINGE PERSONAGEM
		if(matriz_personagens[gradex][gradey] == 1 && !pdir)
		{
			morrePersonagem();
		}
		else if(matriz_personagens[gradex][gradey] >= 2 && matriz_personagens[gradex][gradey] <2+MAXINIMIGOS && !pdir)
		{
			for(k=0;k<fases[faseAtual].inimigos;k++)
			{
				if(matriz_personagens[gradex][gradey] == (2+k) && inimigos[k].status==1)
				{
					inimigos[k].status=2;
					matriz_personagens[gradex][gradey] = 0;
					jogo.pontos+=100;
				}
			}
		}
	}

	//FOGO PARA ESQUERDA
	for(c=1;c<=raio; c++)
	{
		gradex = I_gradex - c;
		gradey = I_gradey;

		//CAMPO LIMPO
		if(matriz_controle[gradex][gradey] == 0 && !pesq)
		{
			matriz_controle[gradex][gradey] = 19;
		}
		//CAMPOS NAO DESTRUTIVEIS
		else if((matriz_controle[gradex][gradey] == 1 || matriz_controle[gradex][gradey] == 2 || matriz_controle[gradex][gradey] == 4) && !pesq)
		{
			pesq=1;
		}
		// ITENS
		else if( (matriz_controle[gradex][gradey] >= 10 && matriz_controle[gradex][gradey]<=TOTALITENS+10) && !pesq)
		{
			matriz_controle[gradex][gradey] = 19;
		}
		//OBJETOS DESTRUTIVEIS
		else if(matriz_controle[gradex][gradey] == 7 && !pesq)
		{
			matriz_controle[gradex][gradey] = verificaItem(gradex,gradey);
			pesq=1;
			jogo.pontos+=10;
		}
		//OUTRA BOMBA
		else if((matriz_controle[gradex][gradey] >= 20 && matriz_controle[gradex][gradey] < 20 + maxBombas) && !pesq)
		{
			for(k=0; k<maxBombas;k++)
			{
				if(matriz_controle[gradex][gradey] == 20+k)
				{
					*(bseq+3)=k;
					pesq=1;
				}
			}
		}
		//ATINGE PERSONAGEM
		if(matriz_personagens[gradex][gradey] == 1 && !pesq)
		{
			morrePersonagem();
		}
		else if(matriz_personagens[gradex][gradey] >= 2 && matriz_personagens[gradex][gradey] <2+MAXINIMIGOS && !pesq)
		{
			for(k=0;k<fases[faseAtual].inimigos;k++)
			{
				if(matriz_personagens[gradex][gradey] == (2+k) && inimigos[k].status==1)
				{
					inimigos[k].status=2;
					matriz_personagens[gradex][gradey] = 0;
					jogo.pontos+=100;
				}
			}
		}
	}

}

void despintaFogo(_FOGO *fogo)
{
	int gradex, gradey, I_gradex, I_gradey, c;
	int pcima=0, pbaixo=0, pdir=0, pesq=0;
	I_gradex = (*fogo).gradex;
	I_gradey = (*fogo).gradey;
	matriz_controle[I_gradex][I_gradey] = 0;


	//DESPINTAR PARA CIMA
	for(c=1;c<=raio; c++)
	{
		gradex = I_gradex;
		gradey = I_gradey - c;

		//CAMPO LIMPO
		if(matriz_controle[gradex][gradey] == 19 && !pcima)
		{
			matriz_controle[gradex][gradey] = 0;
		}
		//CAMPOS NAO DESTRUTIVEIS
		else if((matriz_controle[gradex][gradey] == 1 || matriz_controle[gradex][gradey] == 2 || matriz_controle[gradex][gradey] == 4) && !pcima)
		{
			pcima=1;
		}
	}

	//DESPINTAR PARA BAIXO
	for(c=1;c<=raio; c++)
	{
		gradex = I_gradex;
		gradey = I_gradey + c;

		//CAMPO LIMPO
		if(matriz_controle[gradex][gradey] == 19 && !pbaixo)
		{
			matriz_controle[gradex][gradey] = 0;
		}
		//CAMPOS NAO DESTRUTIVEIS
		else if((matriz_controle[gradex][gradey] == 1 || matriz_controle[gradex][gradey] == 2 || matriz_controle[gradex][gradey] == 4) && !pbaixo)
		{
			pbaixo=1;
		}
	}

	//DESPINTAR PARA DIREITA
	for(c=1;c<=raio; c++)
	{
		gradex = I_gradex + c;
		gradey = I_gradey;

		//CAMPO LIMPO
		if(matriz_controle[gradex][gradey] == 19 && !pdir)
		{
			matriz_controle[gradex][gradey] = 0;
		}
		//CAMPOS NAO DESTRUTIVEIS
		else if((matriz_controle[gradex][gradey] == 1 || matriz_controle[gradex][gradey] == 2 || matriz_controle[gradex][gradey] == 4) && !pdir)
		{
			pdir=1;
		}
	}

		//DESPINTAR PARA ESQUERDA
	for(c=1;c<=raio; c++)
	{
		gradex = I_gradex - c;
		gradey = I_gradey;

		//CAMPO LIMPO
		if(matriz_controle[gradex][gradey] == 19 && !pesq)
		{
			matriz_controle[gradex][gradey] = 0;
		}
		//CAMPOS NAO DESTRUTIVEIS
		else if((matriz_controle[gradex][gradey] == 1 || matriz_controle[gradex][gradey] == 2 || matriz_controle[gradex][gradey] == 4) && !pesq)
		{
			pesq=1;
		}
	}
}

void calculaInimigos(void)
{

	int k, a, b;

	int largura, altura;
	largura = (SCREEN_W/32);
	altura = ((SCREEN_H-32)/32);

	//INIMIGOS DIED
	for(k=0; k<MAXINIMIGOS; k++)
	{
		inimigos[k].status = 2;
		inimigos[k].imagem = IMG_Load("Imagens/Sprites/sprite.png");
		inimigos[k].origem = (SDL_Rect){32,128,32,64};
		inimigos[k].dir = rand()%4;
		inimigos[k].movOK = 0;
	}
	//REVIVE INIMIGOS
	srand(time(NULL));
	for(k=0; k<fases[faseAtual].inimigos; k++)
	{
		a = (rand()%(largura-1))+1;
		b = (rand()%(altura-1))+1;
		while(matriz_controle[a][b]!=0 || matriz_personagens[a][b] != 0 )
		{
			a = (rand()%(largura-1))+1;
			b = (rand()%(altura-1))+1;
		}
		inimigos[k].status = 1;
		inimigos[k].posicao.x=a*32;
		inimigos[k].posicao.y=(b-1)*32;
	}
}

void mover_inimigo(int velocidade, int control)
{
	int gradex, gradey;

	gradex = (inimigos[control].posicao.x/32);
	gradey = ((inimigos[control].posicao.y+32)/32);


	//MOVER PARA ESQUERDA
	if(inimigos[control].dir==0 && inimigos[control].movOK==0)
	{
		//VERIFICA SE ALINHOU GRADE
		if(inimigos[control].posicao.x % 32 == 0)
		{
			//VERIFICA COLISOES
			if( matriz_controle[gradex-1][gradey] == 0)
			{
				inimigos[control].posicao.x -= velocidade;
			}
			else if(matriz_personagens[gradex-1][gradey] == 1)
			{
				morrePersonagem();
				inimigos[control].dir = rand()%4;
			}
			else
			{
				inimigos[control].dir = rand()%4;
			}
		}

		//SE AINDA NAO ESTA ALINHADO A GRADE
		else if(inimigos[control].posicao.x % 32 != 0)
		{
			inimigos[control].posicao.x -= velocidade;

			//ALINHOU GRADE
			if(inimigos[control].posicao.x % 32 == 0)
			{
				gradex = (inimigos[control].posicao.x/32);
				gradey = ((inimigos[control].posicao.y+32)/32);
				matriz_personagens[gradex+1][gradey] = 0;
				if(matriz_personagens[gradex][gradey] == 1)
				{
					morrePersonagem();
				}
				else
				{
					matriz_personagens[gradex][gradey] = (2+control);
				}
			}

		}
	}//FIM IF ESQUERDA

	//MOVER PARA DIREITA
	else if(inimigos[control].dir==1 && inimigos[control].movOK==0)
	{
		//VERIFICA SE ALINHOU GRADE
		if(inimigos[control].posicao.x % 32 == 0)
		{
			//VERIFICA COLISOES
			if( matriz_controle[gradex+1][gradey] == 0)
			{
				inimigos[control].posicao.x += velocidade;
			}
			else if(matriz_personagens[gradex+1][gradey] == 1)
			{
				morrePersonagem();
				inimigos[control].dir = rand()%4;
			}
			else
			{
				inimigos[control].dir = rand()%4;
			}
		}
		//SE AINDA NAO ESTA ALINHADO A GRADE
		else if(inimigos[control].posicao.x % 32 != 0)
		{
			inimigos[control].posicao.x += velocidade;

			if(inimigos[control].posicao.x % 32 == 0)
			{
				gradex = (inimigos[control].posicao.x/32);
				gradey = ((inimigos[control].posicao.y+32)/32);
				matriz_personagens[gradex-1][gradey] = 0;
				if(matriz_personagens[gradex][gradey] == 1)
				{
					morrePersonagem();
				}
				else
				{
					matriz_personagens[gradex][gradey] = (2+control);
				}
			}
		}
	}//FIM IF DIREITA

	//MOVER PARA CIMA
	else if(inimigos[control].dir==2 && inimigos[control].movOK==0)
	{
		//VERIFICA SE ALINHOU GRADE
		if(inimigos[control].posicao.y % 32 == 0)
		{
			//VERIFICA COLISOES
			if( matriz_controle[gradex][gradey-1] == 0)
			{
				inimigos[control].posicao.y -= velocidade;
			}
			else if(matriz_personagens[gradex][gradey-1] == 1)
			{
				morrePersonagem();
				inimigos[control].dir = rand()%4;
			}
			else
			{
				inimigos[control].dir = rand()%4;
			}
		}

		//SE AINDA NAO ESTA ALINHADO A GRADE
		else if(inimigos[control].posicao.y % 32 != 0)
		{
			inimigos[control].posicao.y -= velocidade;

			if(inimigos[control].posicao.y % 32 == 0)
			{
				gradex = (inimigos[control].posicao.x/32);
				gradey = ((inimigos[control].posicao.y+32)/32);
				matriz_personagens[gradex][gradey+1] = 0;
				if(matriz_personagens[gradex][gradey] == 1)
				{
					morrePersonagem();
				}
				else
				{
					matriz_personagens[gradex][gradey] = (2+control);
				}
			}
		}
	}//FIM IF CIMA

	//MOVER PARA BAIXO
	else if(inimigos[control].dir==3 && inimigos[control].movOK==0)
	{
		//VERIFICA SE ALINHOU GRADE
		if(inimigos[control].posicao.y % 32 == 0)
		{
			//VERIFICA COLISOES
			if( matriz_controle[gradex][gradey+1] == 0)
			{
				inimigos[control].posicao.y += velocidade;
			}
			else if(matriz_personagens[gradex][gradey+1] == 1)
			{
				morrePersonagem();
				inimigos[control].dir = rand()%4;
			}
			else
			{
				inimigos[control].dir = rand()%4;
			}
		}

		//SE AINDA NAO ESTA ALINHADO A GRADE
		else if(inimigos[control].posicao.y % 32 != 0)
		{
			inimigos[control].posicao.y += velocidade;

			if(inimigos[control].posicao.y % 32 == 0)
			{
				gradex = (inimigos[control].posicao.x/32);
				gradey = ((inimigos[control].posicao.y+32)/32);
				matriz_personagens[gradex][gradey-1] = 0;
				if(matriz_personagens[gradex][gradey] == 1)
				{
					morrePersonagem();
				}
				else
				{
					matriz_personagens[gradex][gradey] = (2+control);
				}
			}
		}
	}//FIM IF BAIXO

}

void sprite_inimigo(void)
{
     int i;
     for(i=0 ; i<fases[faseAtual].inimigos ; i++)
     {
          switch(inimigos[i].dir)
          {
                case 0:
                     if(inimigos[i].posicao.x % 32 == 8)
                     {
                            inimigos[i].sprite=9;
                     }
                     else if(inimigos[i].posicao.x % 32 == 0 || inimigos[i].posicao.x % 32 == 16)
                     {
                            inimigos[i].sprite=10;
                     }
                     else if(inimigos[i].posicao.x % 32 == 24)
                     {
                            inimigos[i].sprite=11;
                     }
                     break;

                case 1:
                     if(inimigos[i].posicao.x % 32 == 8)
                     {
                            inimigos[i].sprite=3;
                     }
                     else if(inimigos[i].posicao.x % 32 == 0 || inimigos[i].posicao.x % 32 == 16)
                     {
                            inimigos[i].sprite=4;
                     }
                     else if(inimigos[i].posicao.x % 32 == 24)
                     {
                            inimigos[i].sprite=5;
                     }
                     break;

                case 2:
                     if(inimigos[i].posicao.y % 32 == 8)
                     {
                            inimigos[i].sprite=2;
                     }
                     else if(inimigos[i].posicao.y % 32 == 0 || inimigos[i].posicao.y % 32 == 16)
                     {
                            inimigos[i].sprite=1;
                     }
                     else if(inimigos[i].posicao.y % 32 == 24)
                     {
                            inimigos[i].sprite=0;
                     }
                     break;

                case 3:
                     if(inimigos[i].posicao.y % 32 == 8)
                     {
                            inimigos[i].sprite=8;
                     }
                     else if(inimigos[i].posicao.y % 32 == 0 || inimigos[i].posicao.y % 32 == 16)
                     {
                            inimigos[i].sprite=7;
                     }
                     else if(inimigos[i].posicao.y % 32 == 24)
                     {
                            inimigos[i].sprite=6;
                     }
                     break;
                default:
                        break;
          }
     }
}

void blitaInimigo(SDL_Surface *dest)
{
	int i;
	SDL_Rect crop = {0, 0, 32, 64};
	SDL_Surface *img =IMG_Load("Imagens/Sprites/sprite.png");
	for (i=0 ; i<fases[faseAtual].inimigos ; i++)
	{
		if(inimigos[i].status ==1)
		{
			switch(inimigos[i].sprite)
			{
				case 0:
					crop.x = 0;
					crop.y = 0;
					break;
				case 1:
					crop.x = 32;
					crop.y = 0;
					break;
				case 2:
					crop.x = 64;
					crop.y = 0;
					break;
				case 3:
					crop.x = 0;
					crop.y = 64;
					break;
				case 4:
					crop.x = 32;
					crop.y = 64;
					break;
				case 5:
					crop.x = 64;
					crop.y = 64;
					break;
				case 6:
					crop.x = 0;
					crop.y = 128;
					break;
				case 7:
					crop.x = 32;
					crop.y = 128;
					break;
				case 8:
					crop.x = 64;
					crop.y = 128;
					break;
				case 9:
					crop.x = 0;
					crop.y = 192;
					break;
				case 10:
					crop.x = 32;
					crop.y = 192;
					break;
				case 11:
					crop.x = 64;
					crop.y = 192;
					break;
				default:
					break;
			}

			SDL_BlitSurface(img, &crop, dest, &(inimigos[i].posicao));
		}
	}

	SDL_FreeSurface(img);
}


















