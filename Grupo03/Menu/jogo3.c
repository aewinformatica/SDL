/*Computação para Informática (Linguagem C) 2008/1
Professor: Adriano
Trabalho: Jogo3.c (Teste 7)
Data: 18/06/08

Alunos:	Felipe Guerreiro Barbosa Ruiz ( DRE 108056195)
		Gabriel Pires da Silva ( DRE 108056014)
		Guilherme Carneiro Antonio ( DRE 108055602 )*/

#include "meuinclude.h"

int Jogo (SDL_Surface *screen)
{
	faseAtual = 0;
	jogo.vidas = 3;
	//DECLARANDO SURFACES
	SDL_Surface *fundo=IMG_Load("Imagens/fundo.png");
	Kenny.imagem=IMG_Load("Imagens/Sprites/kenny_.png");
	SDL_Surface *bloco=IMG_Load("Imagens/bloco.png");
	SDL_Surface *saida=IMG_Load("Imagens/saida.png");
	SDL_Surface *destrutivel=IMG_Load("Imagens/bloco_d.png");
	SDL_Surface *game_over=IMG_Load("Imagens/game_over.jpg");
	SDL_Surface *vidinha=IMG_Load("Imagens/vidas.png");
	SDL_Surface *pause_imagem=IMG_Load("Imagens/pause.bmp");
	SDL_Surface *item[TOTALITENS];

	item[0]=IMG_Load("Imagens/i_v.png");
	item[1]=IMG_Load("Imagens/i_b.png");
	item[2]=IMG_Load("Imagens/i_f.png");
	item[3]=IMG_Load("Imagens/i_500.png");
	//PERSONAGEM
	Kenny.destino= (SDL_Rect) {32,0,0,0};
	Kenny.origem= (SDL_Rect) {32,128,32,64};

	//DECLARANDO RETANGULOS
	SDL_Rect bloco_dst, saida_dst, bombaPosicao;//ESTATICOS
	SDL_Rect vida_destino={500,480,0,0};
	SDL_Event evento;

	bloco_dst.w=bloco->w;
	bloco_dst.h=bloco->h;

	saida_dst.w=saida->w;
	saida_dst.h=saida->h;

	int quit=0, cima=0, esquerda=0, direita=0, baixo=0, vel=8;//VARIAVEIS DA MOVIMENTACAO
	int i, j, k, b;//CONTADORES
	int minutos, segundos, tempo_que_comecou_o_pause, tempo_que_acabou_o_pause, intervalo_do_pause=0, tempo_da_fase;//VARIÁVEIS DE TEMPO
	int menu=0; //VARIÁVEL PARA O CASO DE QUERER VOLTAR PARA O MENU
	char minuto[5],segundo[5],pontinhos[10],vidinhas[5];
	//int bomba=0, cont_bomba=0, cont_explosao=0, nBomba=1, bombaOk=1;//VARIAVEIS DA BOMBA
	maxBombas=1;
	raio=1;
	tempoExpBomba=2500;
	tempoPintaFogo=200;


	int fogosAtivos=0, bombasAtivas=0, bombaOk=1, bombaA=0, bseq[4];
	_BOMBA bomba[TOTALBOMBAS];
	_FOGO fogo[TOTALBOMBAS];

	for(b=0; b < TOTALBOMBAS ; b++)
	{
		bomba[b].imagem = IMG_Load("Imagens/bomba0.png");
		bomba[b].status = 1;
		fogo[b].imagem = IMG_Load("Imagens/explosao.png");
		fogo[b].status = 1;
	}
	for(b=0; b<4; b++)
	{
		bseq[b]=5000;
	}


	int pause=0;
	int controleMovimento=0, contMovx, contMovy, movInimigo=0;//VARIAVEIS DE CONTROLE
	int tempo;//VARIAVEIS DE TEMPO

	contador=0;

	valoresFases();
	montarMapa();

	SDL_EnableKeyRepeat(10,SDL_DEFAULT_REPEAT_INTERVAL);



	while(!quit)
	{
		tempo_da_fase=SDL_GetTicks()-tempo_total-intervalo_do_pause;
		tempo=SDL_GetTicks();
		SDL_PumpEvents();
		while(SDL_PollEvent(&evento))
		{
			switch(evento.type)
			{
				case SDL_QUIT:
					quit=1;
					break;

				case SDL_KEYDOWN:
					switch(evento.key.keysym.sym)
					{
						case SDLK_r:
							reinicia_jogo(&Kenny.destino,&cima,&baixo,&esquerda,&direita, &bombaA);
							Kenny.origem.x=32;
							Kenny.origem.y=128;
							break;
						case SDLK_ESCAPE:
							quit=1;
							break;
						//ANDANDO
						case SDLK_UP:
							if(controleMovimento == 0)
							{
								controleMovimento = 1;
								cima++;
							}
							break;
						case SDLK_DOWN:
							if(controleMovimento == 0)
							{
								controleMovimento = 1;
								baixo++;
							}
							break;
						case SDLK_RIGHT:
							if(controleMovimento == 0)
							{
								controleMovimento = 1;
								direita++;
							}
							break;
						case SDLK_LEFT:
							if(controleMovimento == 0)
							{
								controleMovimento = 1;
								esquerda++;
							}
							break;
						case SDLK_SPACE:
							if(bombasAtivas<maxBombas)
							{

								bombasAtivas+=1;

								for(b=0; b<bombasAtivas; b++)
								{
									if(bomba[b].status == 1)
									{
										//STATUS E TEMPO
										bomba[b].status = 2;
										bomba[b].tempoini = SDL_GetTicks();
										//GRADE
										bomba[b].gradex = (Kenny.destino.x/32);
										bomba[b].gradey = ((Kenny.destino.y+32)/32);
										//POSICAO
										bomba[b].posicao.x = (bomba[b].gradex)*32;
										bomba[b].posicao.y = (bomba[b].gradey)*32;
										//MARCANDO MATRIZ
										matriz_controle[bomba[b].gradex][bomba[b].gradey]=20+b;
									}
								}

							}
							break;
						case SDLK_p:
                            if(pause == 0)
                            {
							    pause = 1;
							    tempo_que_comecou_o_pause = SDL_GetTicks();
                            }
							break;
						default: break;
					}

				default: break;
			}
		}


		//CONTROLE DE MOVIMENTO
		if(controleMovimento == 1)
		{
			//MOVIMENTACAO PARA CIMA
			if(cima > 0)
			{
				if(cima >= 3)
				{
					if(colisaoCima(Kenny.destino.x,Kenny.destino.y, vel)==1)
					{
						cima = 2;
						bombaOk=1;
						controleMovimento =0;
					}
					else if(cima == 3)
					{
						contMovx = (Kenny.destino.x/32);
						contMovy = ((Kenny.destino.y+32)/32);
						Kenny.origem.x=0;//LOAD IMAGEM 2
						cima++;
						bombaOk=0;
						Kenny.destino.y-=(vel);
					}
					else if(cima ==4)
					{
						Kenny.origem.x=32;//load imagem 1
						cima++;
						Kenny.destino.y-=(vel);
					}
					else if(cima == 5)
					{
						Kenny.origem.x=64;//load imagem 3
						cima++;
						Kenny.destino.y-=(vel);
					}
					else if(cima == 6)
					{
						Kenny.origem.x=32;//load imagem 1
						cima = 2;
						bombaOk=1;
						controleMovimento =0;
						Kenny.destino.y-=(vel);
						matriz_personagens[(Kenny.destino.x/32)][((Kenny.destino.y+32)/32)] = 1;
						matriz_personagens[contMovx][contMovy] = 0;
					}
					if(colisaoSaida(Kenny.destino.x,Kenny.destino.y))
					{
						reinicia_jogo(&Kenny.destino,&cima,&baixo,&esquerda,&direita, &bombaA);						Kenny.origem.x=32;
						Kenny.origem.y=128;
					}
				}
				else if(cima == 1)
				{
					Kenny.origem.y=0;
					Kenny.origem.x=32;//load boneco posicao 1
					cima++;
					baixo=0;
					direita=0;
					esquerda=0;
					controleMovimento = 0;
				}
			}
			//MOVIMENTACAO PARA BAIXO
			if(baixo > 0)
			{
				if(baixo >= 3)
				{
					if( colisaoBaixo(Kenny.destino.x,Kenny.destino.y)==1 )
					{
						baixo = 2;
						bombaOk=1;
						controleMovimento =0;
					}
					else if(baixo == 3)
					{
						contMovx = (Kenny.destino.x/32);
						contMovy = ((Kenny.destino.y+32)/32);
						Kenny.origem.x=0;//LOAD IMAGEM 2
						baixo++;
						bombaOk=0;
						Kenny.destino.y+=(vel);
					}
					else if(baixo ==4)
					{
						Kenny.origem.x=32;//load imagem 1
						baixo++;
						Kenny.destino.y+=(vel);
					}
					else if(baixo == 5)
					{
						Kenny.origem.x=64;//load imagem 3
						baixo++;
						Kenny.destino.y+=(vel);
					}
					else if(baixo == 6)
					{
						Kenny.origem.x=32;//load imagem 1
						baixo = 2;
						bombaOk=1;
						controleMovimento =0;
						Kenny.destino.y+=(vel);
						matriz_personagens[(Kenny.destino.x/32)][((Kenny.destino.y+32)/32)] = 1;
						matriz_personagens[contMovx][contMovy] = 0;
					}
					if(colisaoSaida(Kenny.destino.x,Kenny.destino.y))
					{
						reinicia_jogo(&Kenny.destino,&cima,&baixo,&esquerda,&direita, &bombaA);						Kenny.origem.x=32;
						Kenny.origem.y=128;
					}
				}
				else if(baixo == 1)
				{
					Kenny.origem.y=128;
					Kenny.origem.x=32;//load boneco posicao 1
					baixo++;
					cima=0;
					direita=0;
					esquerda=0;
					controleMovimento = 0;
				}
			}
			//MOVIMENTACAO PARA DIREITA
			if(direita > 0)
			{
				if(direita >= 3)
				{
					if(colisaoDireita(Kenny.destino.x,Kenny.destino.y)==1 )
					{
						direita = 2;
						bombaOk=1;
						controleMovimento =0;
					}
					else if(direita == 3)
					{
						contMovx = (Kenny.destino.x/32);
						contMovy = ((Kenny.destino.y+32)/32);
						Kenny.origem.x=0;//LOAD IMAGEM 2
						direita++;
						bombaOk=0;
						Kenny.destino.x+=(vel);
					}
					else if(direita ==4)
					{
						Kenny.origem.x=32;//load imagem 1
						direita++;
						Kenny.destino.x+=(vel);
					}
					else if(direita == 5)
					{
						Kenny.origem.x=64;//load imagem 3
						direita++;
						Kenny.destino.x+=(vel);
					}
					else if(direita == 6)
					{
						Kenny.origem.x=32;//load imagem 1
						direita = 2;
						bombaOk=1;
						controleMovimento =0;
						Kenny.destino.x+=(vel);
						matriz_personagens[(Kenny.destino.x/32)][((Kenny.destino.y+32)/32)] = 1;
						matriz_personagens[contMovx][contMovy] = 0;
					}
					if(colisaoSaida(Kenny.destino.x,Kenny.destino.y))
					{
						reinicia_jogo(&Kenny.destino,&cima,&baixo,&esquerda,&direita, &bombaA);						Kenny.origem.x=32;
						Kenny.origem.y=128;
					}
				}
				else if(direita == 1)
				{
					Kenny.origem.y=64;
					Kenny.origem.x=32;//load boneco posicao 1
					direita++;
					cima=0;
					baixo=0;
					esquerda=0;
					controleMovimento = 0;
				}
			}
			//MOVIMENTACAO PARA ESQUERDA
			if(esquerda > 0)
			{
				if(esquerda >= 3)
				{
					if( colisaoEsquerda(Kenny.destino.x,Kenny.destino.y,vel)==1 )
					{
						esquerda = 2;
						bombaOk=1;
						controleMovimento =0;
					}
					else if(esquerda == 3)
					{
						contMovx = (Kenny.destino.x/32);
						contMovy = ((Kenny.destino.y+32)/32);
						Kenny.origem.x=0;//LOAD IMAGEM 2
						esquerda++;
						bombaOk=0;
						Kenny.destino.x-=(vel);
					}
					else if(esquerda ==4)
					{
						Kenny.origem.x=32;//load imagem 1
						esquerda++;
						Kenny.destino.x-=(vel);
					}
					else if(esquerda == 5)
					{
						Kenny.origem.x=64;//load imagem 3
						esquerda++;
						Kenny.destino.x-=(vel);
					}
					else if(esquerda == 6)
					{
						Kenny.origem.x=32;//load imagem 1
						esquerda = 2;
						bombaOk=1;
						controleMovimento =0;
						Kenny.destino.x-=(vel);
						matriz_personagens[(Kenny.destino.x/32)][((Kenny.destino.y+32)/32)] = 1;
						matriz_personagens[contMovx][contMovy] = 0;
					}
					if(colisaoSaida(Kenny.destino.x,Kenny.destino.y))
					{
						reinicia_jogo(&Kenny.destino,&cima,&baixo,&esquerda,&direita, &bombaA);						Kenny.origem.x=32;
						Kenny.origem.y=128;
					}
				}
				else if(esquerda == 1)
				{
					Kenny.origem.y=192;
					Kenny.origem.x=32;//load boneco posicao 1
					esquerda++;
					cima=0;
					baixo=0;
					direita=0;
					controleMovimento = 0;
				}
			}
		}

		//MOVENDO INIMIGOS
		//if(movInimigo%16>=0 && movInimigo%16<4)
		//{
			for(b=0 ; b<fases[faseAtual].inimigos ; b++)
			{
				if(inimigos[b].status == 1)
				{
					mover_inimigo(4, b);
				}
			}
		//}
		sprite_inimigo();
		movInimigo++;

		//Calculando explosao da bomba E BLIT DO FOGO
		if(bombasAtivas>0)
		{
			for(b=0; b<maxBombas; b++)
			{
				if(bomba[b].status == 2)
				{
					tempoBomba(&(bomba[b]), &(fogo[b]), &bombasAtivas, &fogosAtivos, bseq);
				}
			}
		}

		//ZERANDO FOGO
		if(fogosAtivos>0)
		{
			for(b=0; b<maxBombas; b++)
			{
				if(fogo[b].status == 2)
				{
					tempoFogo(&(fogo[b]), &fogosAtivos);
				}
			}
		}

		//CALCULANDO DESTRUICAO EM SEQUENCIA
		for(k=0;k<4;k++)
		{
			while(bseq[k]>=0 && bseq[k]<maxBombas)
			{
				b = bseq[k];
				bseq[k] = 1000;
				if(bomba[b].status == 2)
				{
					bomba[b].tempoini = (bomba[b].tempoini)- (2*tempoExpBomba);
					tempoBomba(&(bomba[b]), &(fogo[b]), &bombasAtivas, &fogosAtivos, bseq);
				}
			}
		}

		//COLISAO COM ITEM
		colisaoItem(Kenny.destino.x,Kenny.destino.y);

		//PAUSANDO JOGO
		if(pause==1)
		{
			SDL_BlitSurface(pause_imagem,NULL,screen,NULL);
			desenha_texto("Jogo em pausa",screen,180,100,40,0,0,0);
			desenha_texto("Pressione m para voltar",screen,0,200,40,0,0,0);
			desenha_texto("para o menu",screen,180,300,40,0,0,0);
			SDL_Flip(screen);
			menu=pausarJogo(&pause,&evento);
			tempo_que_acabou_o_pause=SDL_GetTicks();
			intervalo_do_pause+=(tempo_que_acabou_o_pause-tempo_que_comecou_o_pause);
		}
		if(menu==666)
		{
			return menu;
		}

		//CAPTURANDO TEMPO
		tempo=SDL_GetTicks()-tempo;

		//RESETANDO TELA
		SDL_BlitSurface(fundo,NULL,screen,NULL);


		//IMPRIME BLOCOS DE BATIDA / FOGO / BOMBA
		for(i=1;i<20;i++)
		{
			for(j=1;j<14;j++)
			{
				//BLITA BLOCOS
				if(matriz_controle[i][j]==1)
				{
					bloco_dst.x=i*32;
					bloco_dst.y=j*32;
					SDL_BlitSurface(bloco,NULL,screen,&bloco_dst);
				}
				//bLITA SAIDA
				else if(matriz_controle[i][j]==4)
				{
					saida_dst.x=i*32;
					saida_dst.y=j*32;
					SDL_BlitSurface(saida,NULL,screen,&saida_dst);
				}
				//BLITA BOMBA
				else if(matriz_controle[i][j]>=20 && matriz_controle[i][j]<=20+maxBombas)
				{
					for(b=0; b<maxBombas; b++)
					{
						if(matriz_controle[i][j]==20+b)
						{
							SDL_BlitSurface(bomba[b].imagem, NULL, screen, &(bomba[b].posicao));
						}
					}
				}
				//BLITA FOGO
				else if(matriz_controle[i][j]==19)
				{
					bombaPosicao.x = i*32;
					bombaPosicao.y = j*32;
					SDL_BlitSurface(fogo[0].imagem, NULL, screen, &bombaPosicao);
				}
				//BLITTA DESTRUTIVEL
				else if(matriz_controle[i][j]==7)
				{
					saida_dst.x=i*32;
					saida_dst.y=j*32;
					SDL_BlitSurface(destrutivel,NULL,screen,&saida_dst);
				}
				//BLITA ITEM
				else if(matriz_controle[i][j]>=10 && matriz_controle[i][j]<(10+TOTALITENS))
				{
					for(b=0; b<TOTALITENS; b++)
					{
						if(matriz_controle[i][j]==10+b)
						{
							saida_dst.x=i*32;
							saida_dst.y=j*32;
							SDL_BlitSurface(item[b], NULL, screen, &saida_dst);
						}
					}
				}
			}
		}

		SDL_BlitSurface(Kenny.imagem,&Kenny.origem,screen,&Kenny.destino);
		blitaInimigo(screen);

		/*//BLITANDO  INIMIGO POR CIMA DO PERSONAGEM SE NECESSARIO
		if(b1!=100)
		{
			saida_dst.x=(i1*32);
			saida_dst.y=((j1-1)*32);
			SDL_BlitSurface((inimigos[b1].imagem), &(inimigos[b1].origem), screen, &saida_dst);
			i1=100;
			j1=100;
			b1=100;
		}*/

		tempo_da_fase/=1000; //CALCULANDO OS MINUTOS E SEGUNDOS PARA MOSTRAR NA TELA

		minutos=tempo_da_fase/60;
		segundos=(tempo_da_fase-minutos*60)%60;

		switch(segundos)
		{
			case 0: segundo[0]='0'; segundo[1]='0';  segundo[2]='\0'; break;
			case 1: segundo[0]='0'; segundo[1]='1';  segundo[2]='\0'; break;
			case 2: segundo[0]='0'; segundo[1]='2';  segundo[2]='\0'; break;
			case 3: segundo[0]='0'; segundo[1]='3';  segundo[2]='\0'; break;
			case 4: segundo[0]='0'; segundo[1]='4';  segundo[2]='\0'; break;
			case 5: segundo[0]='0'; segundo[1]='5';  segundo[2]='\0'; break;
			case 6: segundo[0]='0'; segundo[1]='6';  segundo[2]='\0'; break;
			case 7: segundo[0]='0'; segundo[1]='7';  segundo[2]='\0'; break;
			case 8: segundo[0]='0'; segundo[1]='8';  segundo[2]='\0'; break;
			case 9: segundo[0]='0'; segundo[1]='9';  segundo[2]='\0'; break;
			default:	sprintf(segundo,"%d",segundos); break;
		}
		sprintf(minuto,"%d",minutos);

		desenha_texto(minuto,screen, 50, 480, 30, 255,255,255);
		desenha_texto(":",screen,70, 480,30,255,255,255);
		desenha_texto(segundo,screen,90,480,30,255,255,255);

		sprintf(pontinhos,"%Lu",jogo.pontos);

		desenha_texto(pontinhos,screen,350, 480, 30,255,255,255);

		SDL_BlitSurface(vidinha,NULL,screen,&vida_destino);
		desenha_texto("x",screen,540,480,30,255,255,255);

		sprintf(vidinhas,"%d",jogo.vidas);
		desenha_texto(vidinhas,screen,570,480,30,255,255,255);

		if(jogo.vidas<=0)
		{
			SDL_BlitSurface(game_over,NULL,screen,NULL);
			desenha_texto("Game Over",screen,180,450,50,255,255,255);
			SDL_Flip(screen);
			SDL_Delay(5000);
			menu=666;
		}
		if(tempo<20)
		{
			SDL_Delay(20-tempo);
		}
		SDL_Flip(screen);
	}
	SDL_FreeSurface(screen);
	SDL_FreeSurface(Kenny.imagem);
	TTF_Quit();
	SDL_Quit();
	return 0;
}




