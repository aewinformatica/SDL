/*
V.A.D. Project - Functions

Bibliotecas SDL disponíveis em http://www.libsdl.org
Versão usada no desenvolvimento do jogo...
...SDL - 1.2.13.0
...SDL_image - 1.2.6.0
...SDL_mixer - 1.2.8.0

NFont está disponivel em http://pubpages.unh.edu/~jmb97
Versão usada no desenvolvimento do jogo é 1.611
*/

JOGADOR carregaJogador()
{
	JOGADOR jogador;

	jogador.surface = IMG_Load("Imgs/Ship.png");
   	
	jogador.comprimento = 80;
	jogador.altura = 80;

	jogador.rect.x = 320;
	jogador.rect.y = 240;
	jogador.bolasDestruidas = 0;

	jogador.tempo = 0;
	jogador.estado = 1;
	jogador.pontos = 0;
	
	return jogador;
}

//---------------------------------------------------------------------------------------------

void calculaVelocidade(float aspectX, float aspectY, float *velAspX, float *velAspY)
{
	float escala, angulo;
	
	escala = aspectX / aspectY;
	angulo = atanf(escala);
	
	*velAspX = sinf(angulo);
	*velAspY = cosf(angulo);
	if(((aspectX < 0) && (aspectY < 0)) || ((aspectY < 0) && (aspectX > 0)))
	{
		*velAspX = -*velAspX;
		*velAspY = -*velAspY;
	}
}

//---------------------------------------------------------------------------------------------

void perpendicular(float aspectX, float aspectY, float *perp1X, float *perp1Y, float *perp2X, float *perp2Y)
{
	float escala, angulo, perpAngulo1, perpAngulo2;
	
	escala = aspectX / aspectY;
	
	angulo = atanf(escala);
	
	perpAngulo1 = angulo + 1.5708;
	perpAngulo2 = angulo - 1.5708;
	
	if(perpAngulo1 > 6.27)
	{
		perpAngulo1 = (perpAngulo1 - 3.1415);
	}
	if(perpAngulo2 < -6.27)
	{
		perpAngulo2 = (perpAngulo2 + 3.1415);
	}
	
	*perp1X = sinf(perpAngulo1);
	*perp1Y = cosf(perpAngulo1);
	
	*perp2X = sinf(perpAngulo2);
	*perp2Y = cosf(perpAngulo2);
}

//---------------------------------------------------------------------------------------------

int arredonda(float num)
{
	if((num - (int)num) >= 0.5)
	{
		return (int)num + 1;
	}
	return (int)num;
}

//---------------------------------------------------------------------------------------------

void vaiParaBorda(BOLA *bolas, int mouseX, int mouseY)
{
	float posX, posY, offsetX, offsetY;
	
	posX = 1.0 * bolas->posRelX;
	posY = 1.0 * bolas->posRelY;
	
	offsetX = posX + SIZE_SMA_BALL/2 - SIZE_PLAYER/2;
	offsetY = 1.0 * SIZE_PLAYER/2 - posY - SIZE_SMA_BALL/2;
	
	while((offsetX * offsetX + offsetY * offsetY) < (SIZE_PLAYER/2 + SIZE_SMA_BALL/2) * (SIZE_PLAYER/2 + SIZE_SMA_BALL/2))
	{
		posX += bolas->velH;
		posY += bolas->velV;
		offsetX = posX + SIZE_SMA_BALL/2 - SIZE_PLAYER/2;
		offsetY = 1.0 * SIZE_PLAYER/2 - posY - SIZE_SMA_BALL/2;
	}
	
	//Arredondando.
	bolas->posRelX = arredonda(posX);
	bolas->posRelY = arredonda(posY);
}

//---------------------------------------------------------------------------------------------

void ballBlitter(BALL *bolas, SDL_Surface *screen, SDL_Surface *grande, SDL_Surface *medio, SDL_Surface *pequeno, int mouseX, int mouseY)
{
	int i;
	SDL_Rect temp;
	
	for(i = 0; i < NUM_EN; i++)
	{
		if(bolas[i].estado != 4) //Arredonda os floats para uma SDL_Rect, para ser "blitado".
		{
			temp.x = arredonda(bolas[i].posX);
			temp.y = arredonda(bolas[i].posY);
			temp.w = 0;
			temp.h = 0;
		}
		else //O caso 4 já está aqui.
		{
			//IMPORTANTE! - posX e posY aqui significam a distância entre o canto superior esquerdo da nave do jogador(poseição do mouse). Eles devem já devem vir arredondados.
			temp.x = mouseX + (int)(bolas->posX);
			temp.y = mouseY + (int)(bolas->posY);
			temp.w = 0;
			temp.h = 0;
			
			SDL_BlitSurface(pequeno, NULL, screen, &temp);
			return;
		}
		
		if(bolas[i].estado == 1)//Caso 1
		{
			SDL_BlitSurface(grande, NULL, screen, &temp);
		}
		else if(bolas[i].estado == 2)//Caso 2
		{
			SDL_BlitSurface(medio, NULL, screen, &temp);
		}
		else//Caso 3
		{
			SDL_BlitSurface(pequeno, NULL, screen, &temp);
		}
	}
}

//---------------------------------------------------------------------------------------------

void Blit(SDL_Surface *image, SDL_Surface *dst, int x, int y)
{
	SDL_Rect temp;
	
	temp.x = x;
	temp.y = y;
	temp.w = 0;
	temp.h = 0;
	SDL_BlitSurface(image, NULL, dst, &temp);
}

//---------------------------------------------------------------------------------------------

Uint32 toogleEstado(Uint32 intervalo, void *parametro)
{
	JOGADOR *jogador = (JOGADOR*) parametro;
	jogador->estado = 0;
	
	return (Uint32)NULL;
}

//---------------------------------------------------------------------------------------------

int atira(BOLA *bolas, JOGADOR *jogador, int bolasNaTela)
{
	int i;
	int conta = 0;
	int retorna=0;

	for(i = 0; i < bolasNaTela; i++)
	{
		if(bolas[i].grudada)
		{	
			bolas[i].disparada = 1;
			bolas[i].grudada = 0;
			
			jogador->estado = 2;
			conta++;
			retorna++;
		}
	}

	SDL_AddTimer(50, toogleEstado, jogador);
	
	return retorna;
}

//---------------------------------------------------------------------------------------------

void toro(BOLA *b)
{
	//A bola disparada volta ao normal apos cruzar pelos lados.
	if((b->rect.x + b->comprimento < 0) || (b->rect.x > SCREEN_W) || (b->rect.y > SCREEN_H) || (b->rect.y + b->altura < 0))
	{
		if(b->disparada)
		{
			b->disparada = 0;
			b->velH = (b->velH/VELMAX); 
			b->velV = (b->velV/VELMAX);
		}
	}
	
/*Vertical*/

	if(b->rect.y + b->altura < 0)
	{
		b->rect.y = SCREEN_H + (b->rect.y + b->altura);	
		/*A equação entre parentes é para o caso de ocorrer uma explosão nos limites da tela. 
		Caso não haja essa correção os pedaços menores da bola maior poderão aparecer juntos depois de executada essa funcao.*/
	}
	if(b->rect.y > SCREEN_H)
	{
		b->rect.y = -b->altura + (b->rect.y - SCREEN_H);
	}

/*Horizontal*/

	if(b->rect.x + b->comprimento < 0)
	{
		b->rect.x = SCREEN_W + (b->rect.x + b->comprimento);
	}

	if(b->rect.x > SCREEN_W)
	{
		b->rect.x = -b->comprimento + (b->rect.x - SCREEN_W);
	}
}

//---------------------------------------------------------------------------------------------

void movimento(BOLA *b, JOGADOR *jogador)
{
	toro(b);

	if(b->grudada)
	{
		b->rect.x = jogador->rect.x + b->posRelX;
		b->rect.y = jogador->rect.y + b->posRelY;
	}
	else
	{
		//O acumulador armazena velocidades fracionárias até que elas completem um inteiro. Quando isso acontece, o objeto eh movimentado.
		b->acumuladorX += b->velH;
		b->acumuladorY += b->velV;

		if((b->acumuladorX > 1) || (b->acumuladorX < -1))
		{
			b->rect.x += (int)floor(b->acumuladorX);
			b->acumuladorX = b->acumuladorX - (int)floor(b->acumuladorX); 	
		}
		if((b->acumuladorY > 1) || (b->acumuladorY < -1))
		{
			b->rect.y += (int)floor(b->acumuladorY);
			b->acumuladorY = b->acumuladorY - (int)floor(b->acumuladorY); 	
		}
	}

}

//---------------------------------------------------------------------------------------------

int pitagoras(SDL_Rect rect1, int comprimento1, SDL_Rect rect2, int comprimento2)
{
	float centroBola1X, centroBola1Y;
	float centroBola2X, centroBola2Y;
	float raioBola1, raioBola2;
	float dist;

	raioBola1 = 1.0 * comprimento1/2;
	raioBola2 = 1.0 * comprimento2/2;

	centroBola1X = rect1.x + raioBola1;
	centroBola1Y = rect1.y + raioBola1;

	centroBola2X = rect2.x + raioBola2;
	centroBola2Y = rect2.y + raioBola2;

	dist = pow(centroBola1X - centroBola2X,2) + pow(centroBola1Y - centroBola2Y,2);

	if(dist <= pow(raioBola1+raioBola2,2))
	{
		return 1;
	}
	
	return 0;
}

//---------------------------------------------------------------------------------------------

void subdivide(BOLA *b1)
{
	int j;

	if(b1->qtdebolas > 0)
	{
		for(j = 0; j < b1->qtdebolas; j++)
		{
			((b1->filhas)+j)->velH = -b1->velH;
			((b1->filhas)+j)->velV = b1->velV; //Modificado para as filhas/netas irem em direções opostas.

			((b1->filhas)+j)->rect.x = b1->rect.x + 20 *pow(-1,j+1);
			((b1->filhas)+j)->rect.y = b1->rect.y + 20 *pow(-1,j+1);

			((b1->filhas)+j)->visivel = 1;
		}
		b1->colidiu = 1;
		b1->visivel = 0;
	}
}

//---------------------------------------------------------------------------------------------

int alteraBolas(BOLA *bolas, BOLA pai, int indice)
{
	int i;
	bolas[indice] = pai;
	indice++;

	for(i = 0; i < pai.qtdebolas; i++)
	{
		indice = alteraBolas(bolas, *(pai.filhas+i), indice);
	}

	return indice;
}

//---------------------------------------------------------------------------------------------

void colisao(BOLA *bolas, int bolasNaTela, JOGADOR *jogador, Mix_Chunk *somexplo, Mix_Chunk *somexplo2)
{
	int h, i;
	BOLA *b2, *b1;

	for(h = 0; h < bolasNaTela; h++)
	{
		if(bolas[h].qtdebolas && bolas[h].visivel)
		{
			/*Colisão entre uma bola grande e uma pequenina*/
			b1 = &bolas[h];
			for(i = 0; i < bolasNaTela; i++)	/*Percorre todas as bolas visíveis*/
			{
				if(bolas[i].visivel && !bolas[i].qtdebolas)	/*Bolas que não se subdividem*/
				{
					b2 = &bolas[i];					
					if(b2->disparada)	/*Foi disparada*/
					{
						/*Pitagoras*/
						if(pitagoras(b1->rect, b1->comprimento, b2->rect, b2->comprimento))
						{ 
							Mix_PlayChannel(-1, somexplo2, 0);
							subdivide(b1);
							alteraBolas(bolas, *b1, h);
							jogador->bolasDestruidas++;

							b2->velH = -b2->velH;  
							b2->velV = -b2->velV;

							//Bola disparada volta ao normal
							b2->disparada = 0;
							b2->velH = (b2->velH/VELMAX); 
							b2->velV = (b2->velV/VELMAX);

							jogador->pontos += 10;

							break;
						}
					}
					else	/*Colisao entre uma bola pequenina e o jogador*/
					{
						if(pitagoras(b2->rect, b2->comprimento, jogador->rect, jogador->comprimento) && !b2->grudada && !jogador->estado)
						{
							b2->grudada = 1;

							b2->posRelX = b2->rect.x - jogador->rect.x;
							b2->posRelY = b2->rect.y - jogador->rect.y;
							
							float centroBola1X, centroBola1Y;
							float centroBola2X, centroBola2Y;
							float raioBola1, raioBola2;
							
							raioBola1 = 1.0 * jogador->comprimento/2;
							centroBola1X = jogador->rect.x + raioBola1;
							centroBola1Y = jogador->rect.y + raioBola1;
							
							raioBola2 = 1.0 * b2->comprimento/2;

							centroBola2X = b2->rect.x + raioBola2;
							centroBola2Y = b2->rect.y + raioBola2;

							calculaVelocidade(centroBola2X - centroBola1X, centroBola2Y - centroBola1Y, &(b2->velH), &(b2->velV));
							vaiParaBorda(b2, jogador->rect.x,jogador->rect.y);
							b2->velH *= 7;
							b2->velV *= 7;
						}
					}
				}
			}				
			
			/*Colisao entre uma bola grande e o jogador*/			
			if(pitagoras(b1->rect, b1->comprimento, jogador->rect, jogador->comprimento) && !jogador->estado)
			{
				Mix_PlayChannel(-1, somexplo, 0);
				subdivide(b1);
				
				jogador->estado = 1;
				jogador->bolasDestruidas++;
				
				SDL_AddTimer(2000, toogleEstado, jogador);
				alteraBolas(bolas, *b1, h);
				
				jogador->vidas -= 1;
			}
		}
	}
}

//---------------------------------------------------------------------------------------------

void atualizaTela(BOLA *bolas, int bolasNaTela, JOGADOR *jogador, SDL_Surface* tela, Mix_Chunk *somexplo, Mix_Chunk *somexplo2)
{
	int i;
	SDL_Rect aux1;

	colisao(bolas, bolasNaTela, jogador, somexplo,somexplo2);

	for(i = 0; i < bolasNaTela; i++)
	{
		if(bolas[i].visivel)
		{		
			movimento(&bolas[i], jogador);
			aux1 = bolas[i].rect;
			SDL_BlitSurface(bolas[i].surface, NULL, tela, &aux1);
		}
	}

	if(jogador->estado == 1) //pisca-pisca
	{
		if(jogador->tempo == 0)
		{
			jogador->tempo = SDL_GetTicks();
		}
		if((SDL_GetTicks() - jogador->tempo) > 100 && (SDL_GetTicks() - jogador->tempo) < 300)
		{
			SDL_BlitSurface(jogador->surface, NULL, tela, &(jogador->rect));
		}
		if((SDL_GetTicks() - jogador->tempo) > 300)
		{
			jogador->tempo = 0;
		}
	}
	else
	{
		SDL_BlitSurface(jogador->surface, NULL, tela, &(jogador->rect));
	}

	NF_Draw(570, 50, "%08d", jogador->pontos);
}

//---------------------------------------------------------------------------------------------

BOLA novaBola(int comprimento, int altura, float velH, float velV, int filhas, int visivel, SDL_Surface *surface)
{
	BOLA nova;

	nova.comprimento = comprimento;
	nova.altura = altura;

	nova.velH = velH;
	nova.velV = velV;

	nova.visivel = visivel;
	nova.colidiu = 0;

	nova.qtdebolas = filhas;

	nova.grudada = 0;
	nova.disparada = 0;
	nova.posRelX = 0;
	nova.posRelY = 0;
	nova.acumuladorX = 0;
	nova.acumuladorY = 0;

   	nova.surface = surface;

	return nova;
}

//---------------------------------------------------------------------------------------------

void adicionaFilhas(BOLA *pai, BOLA *filha)
{
	int i, qtdefilhas;

	qtdefilhas = pai->qtdebolas;

	pai->filhas = (BOLA*) malloc(qtdefilhas * sizeof(BOLA));
	if(!pai->filhas) exit(2);

	for(i = 0; i < qtdefilhas; i++)
	{
		(*(pai->filhas+i))= *filha;
	}
}

//---------------------------------------------------------------------------------------------

void organizaBolas(BOLA *bolas, JOGADOR *jogador, int bolasNaTela)
/*Esta funcão é responsável por posicionar as bolas na tela no início (somente no início) do jogo*/
{
	int x, y, i;

	for(i = 0; i < bolasNaTela; i++)
	{
		if(bolas[i].visivel)
		{
			x = rand() % SCREEN_W;
			y = rand() % SCREEN_H ;
		}
		bolas[i].rect.x = x;
		bolas[i].rect.y = y;
	}
}

//---------------------------------------------------------------------------------------------

void highOrdena(HIGHSCORE *s1)
{
	HIGHSCORE aux;
	int i, j;

	//Bubble-sort
	for(i = 0; i < NUMJOG-1; i++)
	{
		for(j = i+1; j < NUMJOG; j++)
		{
			if((s1[j].recorde) > ((s1[i]).recorde))
			{
				aux=s1[i];
				s1[i]=s1[j];
				s1[j]=aux;
			}
		}
	}
	//Fim do Bubble-sort
}

//---------------------------------------------------------------------------------------------

void trocaRecorde(HIGHSCORE *s1, HIGHSCORE s2)
{
	int i;
	HIGHSCORE aux, aux2;
	
	for(i = 0; i < NUMJOG; i++)
	{
		if ((s2.recorde) >= ((s1+i)->recorde))
		{
			aux=*(s1+i);
			*(s1+i)=s2;
			
			//Aqui vou passando para baixo os outros recordes
			for(i++; i < NUMJOG;i++)
			{
				//Passando o de baixo para aux2
				aux2=*(s1+i);
				
				//Passando aux para o de baixo
				*(s1+i)=aux;
				
				//Passando aux2 para aux, para poder recomeçar o ciclo
				aux=aux2;
			}
			break;
		}
	}
}

//---------------------------------------------------------------------------------------------

BOLA novoGrupoBolas(SDL_Surface *surfacePai, SDL_Surface *surfaceFilha, SDL_Surface *surfaceNeta)
{
	BOLA bolaNeta, bolaFilha, bolaPai;

	int vel1, vel2;

	vel1 = ((rand()%4)+1) * pow(-1,rand()%2) + 1;
	vel2 = ((rand()%4)+1) * pow(-1,rand()%2) + 1;
	bolaNeta = novaBola(20, 20, vel1, vel2, 0, 0, surfaceNeta);

	vel1 = ((rand()%4)+1) * pow(-1,rand()%2) + 1;
	vel2 = ((rand()%4)+1) * pow(-1,rand()%2) + 1;
	bolaFilha = novaBola(40, 40, vel1, vel2, 2, 0, surfaceFilha);	

	vel1 = ((rand()%4)+1) * pow(-1,rand()%2);
	vel2 = ((rand()%4)+1) * pow(-1,rand()%2);
	bolaPai = novaBola(80, 80, vel1, vel2, 2, 1, surfacePai);	

	adicionaFilhas(&bolaFilha, &bolaNeta);
	adicionaFilhas(&bolaPai, &bolaFilha);
	
	return bolaPai;
}
//tenha certeza que há uma linha em branco abaixo.
