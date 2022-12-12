//new
#include "global.h"
#include "prototipos.h"

void ativar_bomba(Bomba *bomba, int mapa[MAX_H][MAX_W], Obj_Dinamico *obj)
{
	if((*bomba).estado == 0)
	{
		(*bomba).x = (*obj).j;
		(*bomba).y = (*obj).i;
		mapa[(*bomba).y][(*bomba).x] = 3;
		SDL_AddTimer(UPDATETIME,funcao_timer,NULL);
		(*bomba).estado = 1;
	}
}

Uint32 funcao_timer(Uint32 interval, void *param)
{
	explode(mapa, b1.x, b1.y, raio, -1);
	tm_explosao = SDL_GetTicks() + TM_EXP;
	return 0;
}

void explode(int mapa[MAX_H][MAX_W], int coox, int cooy, int raio, int dir)
{
	int ix, iy, i;
	if(raio < 0) return;
	if((coox < 0) || (coox > MAX_W)) return;
	if((cooy < 0) || (cooy > MAX_H)) return;
	switch(avalia_ex(coox, cooy))
	{
		case -1: break;
		case 1: 
			break;
		case 0:
			switch(dir)
			{
				case -1:
					for(i=0; i<4; i++)
					{
						direcionar(i, &ix, &iy);
						explode(mapa, coox+ix, cooy+iy, raio-1, i);
					}
					break;
				default: direcionar(dir, &ix, &iy);
					explode(mapa, coox+ix, cooy+iy, raio-1, dir); break;
			}
			mapa[cooy][coox] = -3;
			break;
	}
}

int avalia_ex(int coox, int cooy)
{
	int i;
	SDL_Rect campo={coox*TAM, cooy*TAM, TAM, TAM}; /*retangulo correspondente a area x, y, da matriz, onde a explosao esta ocorrendo - sera usado para testar se os objetos_din (na tela) estao encostando na area explodida
	Isso evita os casos em que o objeto na matriz (como codigo) escapou da explosao, mas que o objeto dinamico ainda esta se movendo para fora do alcance( caso no qual esse obj deveria morrer).
	Apesar de parecer um tanto "pesado" (afinal cehca colisao para ni + 1 objetos, sendo ni um numero variavel de inimigos), eh a melhor solucao que eu vejo. E acredite: checa_colisao nao eh uma funcao pesada (simples teste de 4 ifs)
	Com isso perde o sentido (redundancia) fazer o case codigo_dos_objs. A opcao que a gente tinha era colocar os casos de colisao no default, mas isso nao contaria os casos em que 
	bomberman foge da bomba na matriz, mas nao na tela (afinal, quando ele fugiu, o espaco avaliado eh igual a 0, e 0 eh um caso ja avaliado no switch. PS: Nao acho que checar todo mundo isso va deixar o jogo lento( milesimos de segundo e soh quando a bomba explode), mas eh bom testar. Ahh.. Eh razoavel que nao tenha ni tendendo a infinito, ne? XD ni teoricamente nao eh um numero muito grande.*/
	
	/*To checando as colisoes antes do switch, porque no switch acontece returns e a funcao encerra*/
	if (checa_colisao(campo, bomberman.rect) && !bomber_morreu) //Se a explosao na area colide com o obj_din bomberman...
	{
		bomber_morreu = 1; //morte por explosao;
	}
	for(i=0; i<ni; i++)
	{
		if(checa_colisao(campo, inimigo[i].rect))	morre_inimigo(inimigo[i].i, inimigo[i].j);
	}	
	switch(mapa[cooy][coox])
	{
		//case -2: morre_inimigo(cooy,coox); mapa[cooy][coox] = -3; return 0; 
		case -1: 
		case 6: return -1;
		case 0: return 0;
		case 1: mapa[cooy][coox] = -3; bomberman.pts += 5; return 1;
		//case 2: morre_bomber();	return 0;
		case -5: 
		case -6:
		case -7:
		case -8:
		case -9:

		/*para todos os objetos escondidos em caixas crie um "case codigo_do_objeto:" aqui. quando a bomba 
		atingir o bloco que esconde o objeto o bloco é substituido pelo objeto*/
			mapa[cooy][coox] *=-1; bomberman.pts += 5; return 1;
		default: return 0;
	}
	
	
	return 0;
}

void direcionar(int dir, int *ix, int *iy)
{
	switch(dir)
	{
		case 0: *ix=1; *iy =0; break;
		case 1: *ix = 0; *iy = 1; break;
		case 2: *ix = -1; *iy =0; break;
		case 3: *ix = 0; *iy = -1; break;
	}
}

void morre_bomber()
{
	SDL_Surface *perdeu = IMG_Load("perdeu.png");
	SDL_Rect rect_perdeu={0,0,0,0};

	if(!bomberman.invencibilidade)
	{
		if (bomberman.vida != 0)
		{
			bomberman.rect.x = pos_ini_i;
			bomberman.rect.y = pos_ini_j;

			bomberman.i = pos_ini_j/TAM;
			bomberman.j = pos_ini_i/TAM;

			bomberman.vida--;
			invencibilidade_temp(2000, &bomberman);
		}
		else
		{
			recorde();
			SDL_BlitSurface(perdeu,NULL,screen,&rect_perdeu);
			SDL_Delay(1000);
			bomber_morreu = -1;
			f_menu(); 
		}
	}
}

void morre_inimigo(int cooy, int coox)
{
	int k;

	for(k=0;k<ni;k++)
	{
		if(inimigo[k].i == cooy && inimigo[k].j == coox )
		{
			inimigo[k] = inimigo[ni-1];
		}	
	}
	ni--;
	if(inimigo[0].ai==99) explode(mapa, coox, cooy, 2, -1);
	bomberman.pts += 100;
	
}
