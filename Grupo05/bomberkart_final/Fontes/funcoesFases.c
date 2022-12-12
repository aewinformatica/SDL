/*	Programa: Bomber Kart
	Autores: Daniel Lopes Braz Dos Santos
		     Gustavo Rodrigues Lima
		     Renan da Costa Garrot
	Data: XX/XX/XXXX
	Descrição: Projeto final do curso de computação 1

*/
#include "include.h"

extern SDL_Rect dst_car;
extern SDL_Rect dst_obj;
extern SDL_Rect show_car;
extern SDL_Rect dst_bomba;
extern SDL_Rect dst_fogo;
extern SDL_Rect dst_porta;

extern int vidas;
extern int inimigos;
extern int pontos;

int ifinal = -1;
int jfinal = -1;

char Movimenta(char *atual, char *prox, int **matriz, SDL_Surface *car, int **posInim)
{
	int posX, posY, i;
	char mov_car;

	posX=(dst_car.y/PADRAO);//calcula a posição da imagem em relação à linha da matriz
	posY=(dst_car.x/PADRAO);//calcula a posição da imagem em relação à coluna da matriz

	// VERIFICA FINAL DE FASE
	if((!(dst_car.x % 40)) && (!(dst_car.y % 40)))
	{
		if(posX==ifinal && posY==jfinal)
		{
			if(inimigos < 15) inimigos++; // adiciona um inimigo na proxima fase
			pontos += 200;
			return 'f'; // retorna (f)inal de fase
		}
	}


	// verifica se o carro está alinhado HORIZONTALMENTE para liberar movimentos VERTICAIS.
	if(!(dst_car.x % PADRAO))
	{
		if((*prox == 'u'))
		{
				*atual = 'u';//u=cima/d=baixo/l=esquerda/r=direita
				*prox = 'n';//n=nulo
				mov_car='u'; //usado na atualixaçao da imagem
		}
		else if((*prox == 'd'))
		{
				*atual = 'd';
				*prox = 'n';
				mov_car='d';
		}
	}

	// verifica se o carro está alinhado VERTICALMENTE para liberar movimentos HORIZONTAIS.
	if(!(dst_car.y % PADRAO))
	{
		if((*prox == 'l'))
		{
				*atual = 'l';
				*prox = 'n';
				mov_car='l';
		}
		else if((*prox == 'r'))
		{
				*atual = 'r';
				*prox = 'n';
				mov_car='r';
		}
	}

	// verifica se o carro está alinhado TOTALMENTE para parar.
	if(*prox == 'p')
	{
		if(!(dst_car.x % PADRAO) && !(dst_car.y % PADRAO))
		{
			*atual = 'n';
		}
	}

	//MOVIMENTANDO OS INIMIGOS
	for(i=0; i<inimigos; i++)
	{
		//só movimenta se os inimigos estiverem vivos
		if(posInim[i][0] && posInim[i][1])
		{
			// Efetua movimento
			dst_obj.x = posInim[i][0];
			dst_obj.y = posInim[i][1];

			//caso não tenha instruções para andar, verifique para onde é possível se movimentar
			if(!posInim[i][3])
			{
				//movimento para cima
				if(!matriz[(dst_obj.y/PADRAO) - 1][dst_obj.x/PADRAO])
				{
					posInim[i][3] = 1;
				}
				//movimento para direita
				else if(!matriz[dst_obj.y/PADRAO][(dst_obj.x/PADRAO) + 1])
				{
					posInim[i][3] = 2;
				}
				//movimento para baixo
				else if(!matriz[(dst_obj.y/PADRAO) + 1][dst_obj.x/PADRAO])
				{
					posInim[i][3] = 3;
				}
				//movimento para esquerda
				else if(!matriz[dst_obj.y/PADRAO][(dst_obj.x/PADRAO) - 1])
				{
					posInim[i][3] = 4;
				}
			}
			//caso o movimento já esteja definido
			else if((posInim[i][3] == 1) && (posInim[i][2]))
			{
				//movimentando 1 pixel para cima
				posInim[i][1] -= 1;
				//movimenta-se até que esteja alinhado com a grade
				posInim[i][2] --;
				//verifica se é possível continuar o movimento, quando o inimigo já executou PADRAO pixels
				if(!posInim[i][2])
				{
					posInim[i][2] = PADRAO;
					if(matriz[(dst_obj.y/PADRAO) - 1][dst_obj.x/PADRAO])
					{
						posInim[i][3] = 0;
					}
				}
			}
			else if((posInim[i][3] == 2) && (posInim[i][2]))
			{
				//movimentando 1 pixel para direita
				posInim[i][0] += 1;
				//movimenta-se até que esteja alinhado com a grade
				posInim[i][2] --;
				//verifica se é possível continuar o movimento, quando o inimigo já executou PADRAO pixels
				if(!posInim[i][2])
				{
					posInim[i][2] = PADRAO;
					if(matriz[dst_obj.y/PADRAO][(dst_obj.x/PADRAO) + 2])
					{
					posInim[i][3] = 0;
					}
				}
			}
			else if((posInim[i][3] == 3) && (posInim[i][2]))
			{
				//movimentando 1 pixel para baixo
				posInim[i][1] += 1;
				//movimenta-se até que esteja alinhado com a grade
				posInim[i][2] --;
				//verifica se é possível continuar o movimento, quando o inimigo já executou PADRAO pixels
					if(!posInim[i][2])
				{
					posInim[i][2] = PADRAO;
					if(matriz[(dst_obj.y/PADRAO) + 2][dst_obj.x/PADRAO])
					{
							posInim[i][3] = 0;
					}
				}
			}
			else if((posInim[i][3] == 4) && (posInim[i][2]))
				{
				//movimentando 1 pixel para esquerda
				posInim[i][0] -= 1;
				//movimenta-se até que esteja alinhado com a grade
				posInim[i][2] --;
				//verifica se é possível continuar o movimento, quando o inimigo já executou PADRAO pixels
				if(!posInim[i][2])
				{
					posInim[i][2] = PADRAO;
					if(matriz[dst_obj.y/PADRAO][(dst_obj.x/PADRAO) - 1])
					{
						posInim[i][3] = 0;
					}
				}
			}
		}

	}


	// efetua o movimento de STEP em STEP pixels
	switch(*atual)
	{
		case 'u':
			//verifica se o proximo espaço está vazio(igual a zero)
				if((!matriz[posX][posY]) || (matriz[posX][posY] == 10))
				{
					dst_car.y = dst_car.y - STEP;
					//impede que o carro fique quicando no lado superior da tela
					if(dst_car.y <= 2*PADRAO)
					{
						dst_car.y = 2*PADRAO;
					}
				}
				//impede que o carro fique quicando no lado inferior de cado quadrado
				if((dst_car.y % PADRAO && matriz[dst_car.y/PADRAO][dst_car.x/PADRAO]==1)||(dst_car.y % PADRAO && matriz[dst_car.y/PADRAO][dst_car.x/PADRAO]==2))
				{
					dst_car.y=((dst_car.y/PADRAO)+1)*PADRAO;
				}
				break;
		case 'd':
				//verifica se o proximo espaço está vazio(igual a zero)
				if((!matriz[posX+1][posY]) || (matriz[posX+1][posY] == 10))
				{
					dst_car.y = dst_car.y + STEP;
				}
				break;
		case 'l':
			//verifica se o proximo espaço está vazio(igual a zero)
				if((!matriz[posX][posY]) || (matriz[posX][posY] == 10))
				{
					dst_car.x = dst_car.x - STEP;
					//impede que o carro fique quicando no lado esquerdo da tela
					if(dst_car.x <= PADRAO)
					{
						dst_car.x = PADRAO;
					}
				}
				//impede que o carro fique quicando no lado direito de cada quadrado
				if((dst_car.x % PADRAO && matriz[dst_car.y/PADRAO][dst_car.x/PADRAO]==1)||(dst_car.x % PADRAO && matriz[dst_car.y/PADRAO][dst_car.x/PADRAO]==2))
				{
					dst_car.x=((dst_car.x/PADRAO)+1)*PADRAO;
				}
				break;
		case 'r':
				//verifica se o proximo espaço está vazio(igual a zero)
				if((!matriz[posX][posY+1]) || (matriz[posX][posY+1] == 10))
				{
					dst_car.x = dst_car.x + STEP;
				}

			break;
	}

	return mov_car;
}

//carrega os objetos fixos de acordo com os elementos da matriz
void CarregarObj(int **matriz, SDL_Surface* fixo, SDL_Surface* movel, SDL_Surface* screen, SDL_Surface* inimigo[], int** posInim, SDL_Surface* porta)
{
	int i, j, t = 0;

	for(i=0; i<SCREEN_H/PADRAO; i++)
	{
		for(j=0; j<SCREEN_W/PADRAO; j++)
		{
			//carrega objetos fixos e indestrutíveis
			if(matriz[i][j] == 1)
			{
				dst_obj.x = j*PADRAO;
				dst_obj.y = i*PADRAO;
				SDL_BlitSurface(fixo, NULL, screen, &dst_obj);
			}
			//carrega objetos fixos e destrutíveis
			else if((matriz[i][j] == 2) || (matriz[i][j] == 4))
			{
				dst_obj.x = j*PADRAO;
				dst_obj.y = i*PADRAO;
				SDL_BlitSurface(movel, NULL, screen, &dst_obj);
				if(matriz[i][j] == 4)
				{
					dst_porta.x = j*PADRAO;
					dst_porta.y = i*PADRAO;
					matriz[i][j] = 2;
					ifinal = i;
					jfinal = j;
				}
			}
			//carrega inimigos
			else if(matriz[i][j] == 3)
			{
				posInim[t][0] = j*PADRAO;
				posInim[t][1] = i*PADRAO;
				posInim[t][2] = PADRAO;
				posInim[t][3] = 0;
				matriz[i][j] = 0;
				t++;
			}
			//permite que a saída seja colocada na tela
			if(!matriz[dst_porta.y/PADRAO][dst_porta.x/PADRAO])
			{
				SDL_BlitSurface(porta, NULL, screen, &dst_porta);
			}
		}
	}

	for(i=0; i<inimigos; i++)
	{
		for(j=0; j<2; j++)
		{
			if(!j)
			{
				dst_obj.x = posInim[i][j];
			}
			else
			{
				dst_obj.y = posInim[i][j];
				SDL_BlitSurface(inimigo[posInim[i][4]], NULL, screen, &dst_obj);
			}
		}
	}
}


//atualiza a imagem do carro de acordo com o movimento do mesmo
void AtualizaImagemCarro(char mov_car)
{
	if(mov_car == 'l')
	{
		show_car.x = 2 * PADRAO;
	}
	else if(mov_car == 'r')
	{
		show_car.x = 3 * PADRAO;
	}
	else if(mov_car == 'u')
	{
		show_car.x = 1 * PADRAO;
	}
	else if(mov_car == 'd')
	{
		show_car.x = 0 * PADRAO;
	}
}

int Explosao(int poeBomba, int poeFogo,  Uint32 temp, SDL_Surface* screen, SDL_Surface* bomba, SDL_Surface* fogo, int** matriz)
{
	//põe apenas 1 bomba por vez que explode a um tempo de 1,3 segundos
	if((SDL_GetTicks() - temp < 1300) && (poeBomba == 1))
	{
		SDL_BlitSurface(bomba, NULL, screen, &dst_bomba);

		//permite que a imagem do fogo seja colocada na tela
		poeFogo = 1;

		matriz[dst_bomba.y/PADRAO][dst_bomba.x/PADRAO] = 10;

		return poeFogo;
	}
	else if((SDL_GetTicks() - temp < 2300) && (poeFogo == 1)) //permite que o fogo seja colocado num tempo de 1 segundo
	{
		//impede que a bomba seja recolocada
		poeBomba = 0;

		//determina onde deve ser colocado o fogo
		dst_fogo.x = dst_bomba.x - PADRAO;
		dst_fogo.y = dst_bomba.y - PADRAO;
		SDL_BlitSurface(fogo, NULL, screen, &dst_fogo);

		matriz[dst_bomba.y/PADRAO][dst_bomba.x/PADRAO] = 0;

		return poeBomba;
	}
	else
	{
		//impede que o fogo seja colocado na tela
		poeFogo = 0;
		return poeFogo;
	}
}

//Checa se os blocos foram destruídos
void ChecaDestruicaoNaoFixo(int** matriz)
{
		//destruição do quadrado da esquerda
		if(matriz[(dst_fogo.y + PADRAO)/PADRAO][dst_fogo.x/PADRAO] == 2)
		{
			matriz[(dst_fogo.y + PADRAO)/PADRAO][dst_fogo.x/PADRAO] = 0;
			pontos += 5;
		}
		//destruição do quadrado da direita
		if(matriz[(dst_fogo.y + PADRAO)/PADRAO][(dst_fogo.x + 2*PADRAO)/PADRAO] == 2)
		{
			matriz[(dst_fogo.y + PADRAO)/PADRAO][(dst_fogo.x + 2*PADRAO)/PADRAO] = 0;
			pontos += 5;
		}
		//destruição do quadrado de cima
		if(matriz[dst_fogo.y/PADRAO][(dst_fogo.x + PADRAO)/PADRAO] == 2)
		{
			matriz[dst_fogo.y/PADRAO][(dst_fogo.x + PADRAO)/PADRAO] = 0;
			pontos += 5;
		}
		//destruição do quadrado de baixo
		if(matriz[(dst_fogo.y + 2*PADRAO)/PADRAO][(dst_fogo.x + PADRAO)/PADRAO] == 2)
		{
			matriz[(dst_fogo.y + 2*PADRAO)/PADRAO][(dst_fogo.x + PADRAO)/PADRAO] = 0;
			pontos += 5;
		}
}

int ChecaDestruicaoInimigosJogador(int **matriz, int **posInim, Uint32 invulneravel)
{
	int i, larg, alt;

	//destruição dos inimigos
	for(i=0; i<inimigos; i++)
	{
		larg = posInim[i][0] + PADRAO; //ponto x+40 da imagem
		alt = posInim[i][1] + PADRAO; //ponto y+40 da imagem

		if((posInim[i][0] > dst_fogo.x + PADRAO) && (posInim[i][0] < dst_fogo.x + 2*PADRAO) && (posInim[i][1] >= dst_fogo.y) && (posInim[i][1] < dst_fogo.y + PADRAO))
		{
			posInim[i][0] = 0;
			posInim[i][1] = 0;
			pontos += (posInim[i][4] + 1) * 10;
		}
		//fogo do quadrado de cima em relação ao ponto x+40,y+40 da imagem
		else if((larg > dst_fogo.x + PADRAO) && (larg <= dst_fogo.x + 2*PADRAO) && (alt > dst_fogo.y) && (alt <= dst_fogo.y + PADRAO))
		{
			posInim[i][0] = 0;
			posInim[i][1] = 0;
			pontos += (posInim[i][4] + 1) * 10;
		}
		//fogo dos quadrados do centro em relação ao ponto x,y da imagem
		else if((posInim[i][0] >= dst_fogo.x) && (posInim[i][0] < dst_fogo.x + 3*PADRAO) && (posInim[i][1] >= dst_fogo.y + PADRAO) && (posInim[i][1] < dst_fogo.y + 2*PADRAO))
		{
			posInim[i][0] = 0;
			posInim[i][1] = 0;
			pontos += (posInim[i][4] + 1) * 10;
		}
		//fogo dos quadrados do centro em relação ao ponto x+40,y+40 da imagem
		else if((larg > dst_fogo.x) && (larg <= dst_fogo.x + 3*PADRAO) && (alt > dst_fogo.y + PADRAO) && (alt <= dst_fogo.y + 2*PADRAO))
		{
			posInim[i][0] = 0;
			posInim[i][1] = 0;
			pontos += (posInim[i][4] + 1) * 10;
		}
		//fogo do quadrado de baixo em relação ao ponto x,y da imagem
		else if((posInim[i][0] >= dst_fogo.x + PADRAO) && (posInim[i][0] < dst_fogo.x + 2*PADRAO) && (posInim[i][1] >= dst_fogo.y + 2*PADRAO) && (posInim[i][1] < dst_fogo.y + 3*PADRAO))
		{
			posInim[i][0] = 0;
			posInim[i][1] = 0;
			pontos += (posInim[i][4] + 1) * 10;
		}
		//fogo do quadrado de baixo em relação ao ponto x+40,y+40 da imagem
		else if((larg > dst_fogo.x + PADRAO) && (larg < dst_fogo.x + 2*PADRAO) && (alt > dst_fogo.y + 2*PADRAO) && (alt <= dst_fogo.y + 3*PADRAO))
		{
			posInim[i][0] = 0;
			posInim[i][1] = 0;
			pontos += (posInim[i][4] + 1) * 10;
		}
	}

	//se morrer, possui 5 segundos de invulnerabilidade
	if(SDL_GetTicks() - invulneravel > 5000)
	{
		larg = dst_car.x + PADRAO; //ponto x+40 da imagem
		alt = dst_car.y + PADRAO; //ponto y+40 da imagem

		//fogo do quadrado de cima em relação ao ponto x,y da imagem
		if((dst_car.x > dst_fogo.x + PADRAO) && (dst_car.x < dst_fogo.x + 2*PADRAO) && (dst_car.y >= dst_fogo.y) && (dst_car.y < dst_fogo.y + PADRAO))
		{
			vidas --;
			dst_car.x = PADRAO;
			dst_car.y = 2*PADRAO;
			return 1;
		}
		//fogo do quadrado de cima em relação ao ponto x+40,y+40 da imagem
		else if((larg > dst_fogo.x + PADRAO) && (larg <= dst_fogo.x + 2*PADRAO) && (alt > dst_fogo.y) && (alt <= dst_fogo.y + PADRAO))
		{
			vidas --;
			dst_car.x = PADRAO;
			dst_car.y = 2*PADRAO;
			return 1;
		}
		//fogo dos quadrados do centro em relação ao ponto x,y da imagem
		else if((dst_car.x >= dst_fogo.x) && (dst_car.x < dst_fogo.x + 3*PADRAO) && (dst_car.y >= dst_fogo.y + PADRAO) && (dst_car.y < dst_fogo.y + 2*PADRAO))
		{
			vidas --;
			dst_car.x = PADRAO;
			dst_car.y = 2*PADRAO;
			return 1;
		}
		//fogo dos quadrados do centro em relação ao ponto x+40,y+40 da imagem
		else if((larg > dst_fogo.x) && (larg <= dst_fogo.x + 3*PADRAO) && (alt > dst_fogo.y + PADRAO) && (alt <= dst_fogo.y + 2*PADRAO))
		{
			vidas --;
			dst_car.x = PADRAO;
			dst_car.y = 2*PADRAO;
			return 1;
		}
		//fogo do quadrado de baixo em relação ao ponto x,y da imagem
		else if((dst_car.x >= dst_fogo.x + PADRAO) && (dst_car.x < dst_fogo.x + 2*PADRAO) && (dst_car.y >= dst_fogo.y + 2*PADRAO) && (dst_car.y < dst_fogo.y + 3*PADRAO))
		{
			vidas --;
			dst_car.x = PADRAO;
			dst_car.y = 2*PADRAO;
			return 1;
		}
		//fogo do quadrado de baixo em relação ao ponto x+40,y+40 da imagem
		else if((larg > dst_fogo.x + PADRAO) && (larg < dst_fogo.x + 2*PADRAO) && (alt > dst_fogo.y + 2*PADRAO) && (alt <= dst_fogo.y + 3*PADRAO))
		{
			vidas --;
			dst_car.x = PADRAO;
			dst_car.y = 2*PADRAO;
			return 1;
		}
	}

	return 0;
}

//aloca espaço para a matriz
int** AlocaEspaco(int lin, int col)
{
	int **matriz;
	int i;

	//"aloca espaço para as linhas"
	matriz = (int **) malloc(lin*sizeof(int *));
	if(!matriz)	return (int **) 0;

	for (i=0; i<lin; i++)
	{
		//"aloca espaço para as colunas"
		matriz[i] = (int *) malloc(col*sizeof(int));
		if(!matriz[i]) return (int**) 0;
	}

	return matriz;
}

//checa se algum inimigo encostou no jogador
int ChoqueJogador(int** posInim, Uint32 invulneravel)
{
	int i, larg, alt;

	//se morrer, possui 5 segundos de invulnerabilidade
	if(SDL_GetTicks() - invulneravel > 5000)
	{
		larg = dst_car.x + PADRAO;
		alt = dst_car.y + PADRAO;

		for(i=0; i<inimigos; i++)
		{
			if((dst_car.x >= posInim[i][0]) && (dst_car.x < posInim[i][0] + PADRAO) && (dst_car.y >= posInim[i][1]) && (dst_car.y < posInim[i][1] + PADRAO))
			{
				vidas --;
				dst_car.x = PADRAO;
				dst_car.y = 2*PADRAO;
				return 1;
			}
			else if((larg > posInim[i][0]) && (larg <= posInim[i][0] + PADRAO) && (alt > posInim[i][1]) && (alt <= posInim[i][1] + PADRAO))
			{
				vidas --;
				dst_car.x = PADRAO;
				dst_car.y = 2*PADRAO;
				return 1;
			}
		}
	}
	return 0;
}
