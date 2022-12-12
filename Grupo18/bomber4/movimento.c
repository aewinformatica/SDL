#include "global.h"
#include "prototipos.h"

void alinhar(Obj_Dinamico *obj)
{
	int i;
	
	if((*obj).rect.x%TAM == 0)
	{
		(*obj).incx = 0;
		(*obj).mov = 0;
	}
	else 
	{
		(*obj).rect.x += (*obj).incx;
	}
	
	if((*obj).rect.y%TAM == 0)
	{
		(*obj).incy = 0;
		(*obj).mov = 0;
	}
	else (*obj).rect.y +=(*obj).incy;
	
	/*verifica se o bomberman esta encostado em algum inimigo*/
	for(i=0; i<ni; i++)
	{
		if(checa_colisao(bomberman.rect, inimigo[i].rect) && !bomber_morreu)	bomber_morreu = 1;;
	}	
	
}

void define_din(Obj_Dinamico *obj,int x, int y, int i, int j, int inx, int iny, int cod, int ai)
{
	int indice;
	(*obj).rect.x = x;
	(*obj).rect.y = y;
	(*obj).rect.w = TAM;
	(*obj).rect.h = TAM;
	(*obj).i = i;
	(*obj).j = j;
	(*obj).incx = inx;
	(*obj).incy = iny;
	(*obj).mov = 0;
	(*obj).cod = cod;
	(*obj).ai = ai;
	for(indice=0; indice < 4; indice++)
	{
		(*obj).direcao[indice] = 0;
	}
	(*obj).walk_control = 0;
	
	(*obj).r_anima.w = (*obj).r_anima.h = TAM;
	(*obj).r_anima.x = TAM; (*obj).r_anima.y = TAM*2;
	
	switch(ai) 
	{
		case 0: (*obj).grafico = IMG_Load("inimigo0.png");break;
		case 1:
			(*obj).grafico = IMG_Load("inimigo1.png");break;
		case 2:
			(*obj).grafico = IMG_Load("inimigo2.png");break;
		case 99:
			(*obj).grafico = IMG_Load("inimigo4.png");break;
		default: (*obj).grafico = IMG_Load("inimigo0.png");break;
			
	}
	SDL_SetColorKey((*obj).grafico, SDL_SRCCOLORKEY, SDL_MapRGB((*obj).grafico->format, 0xFF, 0, 0xFF));
}


void move_inimigo(Obj_Dinamico *obj, int step, int mapa[MAX_H][MAX_W])
{
	int dir, s, i;
	switch((*obj).ai)
	{
		case 1:
		case 2:
			for(i=0, s=0; i<4; i++)
			{
				if((*obj).direcao[i]!=0)
				{
					s+= (*obj).direcao[i];
					break;
				}
			}
			dir = i;
			break;

		default:
			dir = rand()%4;
			break;
	}
	switch(dir)
	{
		case 0: mover(obj, 1, 0, step, mapa, dir);break;
		case 1: mover(obj, 0, -1, step, mapa, dir);break;
		case 2: mover(obj, -1, 0, step, mapa, dir);break;
		case 3: mover(obj, 0, 1, step, mapa, dir); break;
	}
}

void mover(Obj_Dinamico *obj, int x, int y, int step, int mapa[MAX_H][MAX_W], int dir)//Só está sendo usada pra inimigos, certo?! Então podemos "personalizar" isso aqui...
{
	int i, new_d = dir, safe=0;
	int coox = (*obj).rect.x/TAM , cooy = (*obj).rect.y/TAM;
	if((*obj).mov == 0 && (*obj).incx == 0 && (*obj).incy == 0 && checa_passagem(mapa[cooy+y][coox+x]))
	{
		if(mapa[cooy][coox]==(*obj).cod) 
			mapa[cooy][coox] = 0;
		if(cooy+y >= 0 && cooy+y <= MAX_H && coox+x >= 0 && coox+x <= MAX_W)
		{
			mapa[cooy+y][coox+x] = (*obj).cod;
			(*obj).i += y;
			(*obj).j += x;
		}
		(*obj).walk_control = 1;
		(*obj).incx = x*step;
		(*obj).incy = y*step;

		if(((*obj).rect.x + (*obj).incx) >= 0 && ((*obj).rect.x + (*obj).incx ) <= (MTRZ_M*50 - (*obj).rect.w) )
			(*obj).rect.x += (*obj).incx;
		if(((*obj).rect.y + (*obj).incy) >= 0 && ((*obj).rect.y + (*obj).incy ) <= (MTRZ_N*50 - (*obj).rect.h) )
			(*obj).rect.y += (*obj).incy;
	}
	
	if(x==0 && y==-1) (*obj).r_anima.y = 0* TAM;
	if(x==0 && y==1) (*obj).r_anima.y = 2* TAM;
	if(x==-1 && y==0) (*obj).r_anima.y = 3* TAM;
	if(x==1 && y==0) (*obj).r_anima.y = 1* TAM;
	
	if(((*obj).ai == 1)||((*obj).ai == 2)) //anda linearmente.
	{
		if(!checa_passagem(mapa[cooy+y][coox+x]))
		{
			new_d = ((*obj).i+(*obj).j+rand())%4;
			do
			{
				new_d =(new_d+1)%4;
				switch(new_d)
				{
					case 0: x = 1; y = 0;break;
					case 1: x = 0; y = -1;break;
					case 2: x= -1; y = 0;break;
					case 3: x= 0; y = 1;break;
				}
				
			}while(!checa_passagem(mapa[cooy+y][coox+x]));

			for(i=0; i<4; i++)
			{
				(*obj).direcao[i]=0;
			}
			(*obj).direcao[new_d]=1;
		}
	}
	if((*obj).ai == 2) //se estiver andando na direcao da bomba ele muda de direcao
	{
		for(i=0; i<=raio+1; i++)
		{
			if(coox+i*x >= 0 && coox+i*x < MAX_W && cooy+i*y >=0 && cooy+i*y < MAX_H)
			{
				
				if(!safe)
				{
					if(checa_passagem(mapa[cooy+i*y][coox+i*x])==0 && mapa[cooy+i*y][coox+i*x]!=3 )
					{
						safe=1;
					}
				
					if(mapa[cooy+i*y][coox+i*x]==3)
					{
						new_d= (new_d+2)%4;
						for(i=0; i<4; i++)	
						{
							(*obj).direcao[i]=0;
						}
						
						(*obj).direcao[new_d]=1;
					}
				}
			}
		}
	}
	
	if((*obj).ai == 3)
	{
		
	}
}


void checa_direcionais(int teclado[4], Obj_Dinamico *bomberman, int *step, int mapa[MAX_H][MAX_W])
{
		/*note que os 'else' após cada caso de teste, permite um único movimento na seguinte prioridade*/
		if(teclado[1] == 1) mover2(bomberman, 0, -1, *step, mapa); //CIMA
		else if(teclado[3] == 1) mover2(bomberman, 0, 1, *step, mapa); //BAIXO
		else if(teclado[2] == 1) mover2(bomberman, -1, 0, *step, mapa); //ESQUERDA
		else if(teclado[0] == 1) mover2(bomberman, 1, 0, *step, mapa); //DIREITA
}

int checa_passagem(int n)
{
	switch(n)
	{
		case -1:
		case 1:
		case 3:
		case -5:
		case -6:
		case -7:
		case -8:
		case -9:
		/*um case -(codigo do objeto escondido) pra cada objeto escondido (corresponde ao bloco que o esconde portanto nao da passagem);*/
			return 0;
		
		case 5:
			raio++;
			return 1;
		/*aqui cabe um "case codigo_do_objeto_escondido:" seguido pelo o que acontece quando o 
		bomber encosta no objeto e terminando com return 1 (permite passagem) ou 0(nao permite passagem);*/
		case 6:
			if(ni>0) return 0; /*encontrou a saida mas ela esta bloqueada*/
			else fim_do_nivel = 1; return 1;
			
		case 7:
			invencibilidade_temp(8000, &bomberman);
			return 1;
			
		case 8:
			step = 2;
			return 1;
		
		case 9:
			bomberman.vida++;
			return 1;
		default:
			
			return 1;
	}
}

void verifica_colisao(void)
{
	int i;

	if(!bomber_morreu)
	{
		for(i=0;i<ni;i++)
		{
			if(inimigo[i].rect.x == bomberman.rect.x)
				if(inimigo[i].rect.y == bomberman.rect.y)
				{
					bomber_morreu=1;
					//morre_bomber();
				}
		}
	}
}


void animacao_andar(SDL_Rect *r_hero, Obj_Dinamico *dinamico)//para imgs de três quadros (inimigos)
{
	if((*dinamico).walk_control > 0)
	{
		if ((*dinamico).walk_control >=1 && (*dinamico).walk_control <=16) 
		{
			if((*dinamico).i % 2 == 0)	(*r_hero).x = (*r_hero).w  *0;
			else (*r_hero).x = (*r_hero).w *2;
		}
		else (*r_hero).x = (*r_hero).w *1;
		
		/*if (walk_control >=17 && walk_control <=25) (*r_hero).x = TAM*2;
		if (walk_control >= 25 && walk_control <32) (*r_hero).x = TAM* 1;*/
		(*dinamico).walk_control ++;
		if((*dinamico).walk_control >32) (*dinamico).walk_control = 0;
	}
	else (*r_hero).x = (*r_hero).w *1;		
}
void mover2(Obj_Dinamico *obj, int x, int y, int step, int mapa[MAX_H][MAX_W])
{
	int coox = (*obj).rect.x/TAM , cooy = (*obj).rect.y/TAM;
	if((*obj).mov == 0 && (*obj).incx == 0 && (*obj).incy == 0 && checa_passagem(mapa[cooy+y][coox+x]))
	{
		if(cooy+y >= 0 && cooy+y <= MAX_H && coox+x >= 0 && coox+x <= MAX_W)
		{
			if(mapa[cooy][coox]==2)	mapa[cooy][coox] = 0;
			mapa[cooy+y][coox+x] = 2;
			(*obj).i += y;
			(*obj).j += x;
			(*obj).walk_control = 1;
		}
		(*obj).incx = x*step;
		(*obj).incy = y*step;
		if(((*obj).rect.x + (*obj).incx) >= 0 && ((*obj).rect.x + (*obj).incx ) <= (MTRZ_M*50 - (*obj).rect.w) )
			(*obj).rect.x += (*obj).incx;
		if(((*obj).rect.y + (*obj).incy) >= 0 && ((*obj).rect.y + (*obj).incy ) <= (MTRZ_N*50 - (*obj).rect.h) )
			(*obj).rect.y += (*obj).incy;
			
		if(x==0 && y==-1) r_hero.x = 0* TAM_IMGW;
		if(x==0 && y==1) r_hero.x = 1* TAM_IMGW;
		if(x==-1 && y==0) r_hero.x = 2* TAM_IMGW;
		if(x==1 && y==0) r_hero.x = 3* TAM_IMGW;
	}
}


int checa_colisao(SDL_Rect a, SDL_Rect b) //funcao checa colisao: dados dois retangulos, verifica se um encosta(ou transpassa) o outro
{
    int aesq, adir, acim, abai, besq, bdir, bcim, bbai;
    aesq = a.x;
    adir = a.x + a.w;
    acim = a.y;
    abai = a.y + a.h;

    besq = b.x;
    bdir = b.x + b.w;
    bcim = b.y;
    bbai = b.y + b.h;
    if(abai <= bcim)
    {
        return 0;
    }
    if(acim >= bbai)
    {
        return 0;
    }
    if(adir <= besq)
    {
        return 0;
    }
    if(aesq >= bdir)
    {
        return 0;
    }

    return 1;
}

void invencibilidade_temp(int duracao, Obj_Dinamico* obj)
{
	(*obj).invencibilidade = 1;
	SDL_AddTimer(duracao,timer_invencibilidade,NULL);
}
Uint32 timer_invencibilidade(Uint32 interval, void *param)
{
	bomberman.invencibilidade = 0;
	return 0;
}
