typedef struct
{
	int x,y;
} Tponto;

typedef struct
{
	char nome[256];
	Mix_Music* arquivo;
} Tmusica;

Tmusica musica;

typedef struct
{
	char nome[100];
	char pic[100];
	float x, y, z, speed, direction;
	int w, h, frame, solido, clock0, clock1, extra1, extra2, vivo, opac;
} Tobj;

typedef struct
{
	char nome[100];
	SDL_Surface* img;
	int fh, fv, AltFrame, LargFrame, fpf;
	Tponto center;
} Tpic;

typedef struct
{
	char nome[100];
	Mix_Chunk* som;
} Tsom;

SDL_Surface* screen;
Tobj *obj;
Tpic *pic;
Tsom *som;
int nobj=0, npic=0, nsom=0, RefreshList=1;
SDL_Rect rect,frame;

//menux.c
void CarregarTudo(void);
int Menux(void);
int FimDeJogo(void);
void InsiraNome(void);
void Escreva(char n[], float x, float y);
void ShowRecords(void);
int ordene(const void *e1, const void *e2);
void Abertura(void);

//game.h
void Movimentar(Tobj *o);
void ChecarEventos(void);
void aoCriar(Tobj *o);
void aoDestruir(Tobj *o);
void aoClock0(Tobj *o);
void aoClock1(Tobj *o);
void aoTerminarAnim(Tobj *o);
void aoDesenhar(Tobj *o);
void pare(void);
void Colisoes(Tobj *o);
void Game(void);
void DrawBarra(void);
void Loop(void);

//Funcoes.h
void Iniciar(void);
void Finalizar(void);
int ColisaoS(Tobj *o, Tobj *p);
int Colidindo(Tobj *o, int x, int y);
void Crie(char n[],float x, float y);
void Destrua(Tobj *o);
void LoadImg(char c[], int fh, int fv, int cx, int cy, int fpf);
void Desenhe(Tobj *o);
void PlaySom(char c[]);
int cmp(const void *e1, const void *e2);
int cmpsom(const void *e1, const void *e2);
int cmppic(const void *e1, const void *e2);
void DefinaPic(Tobj *o, char c[]);
void SomeImg(SDL_Surface* s, const SDL_Rect *sr,SDL_Surface* d,const SDL_Rect *dr, int p);
void AtualizeRelogio(Tobj *o);
void UpdateZ(void);
void UpdateObjs(void);
void PuleAleatorio(Tobj *o);
int BuscaImg(char nm[]);
int BuscaSom(char nm[]);
void Vanish(Tobj *o);
int ColisaoS2(Tobj *o, Tobj *p, int d);
int NaGrade(Tobj *o, int g);
void DesenheBackground(char c[]);
int ColObjPos(Tobj *o, char c[], float x, float y);
void DesenheFrame(char c[], int f, float x, float y);
void DestruaObj(char c[]);
void PlayMusica(char c[]);
void KillAll(void);

//Genericas
void redirect(Tobj *o);
void Mova(Tobj *o);

//Bomba.h
void aoCriar_Bomba(Tobj *o);
void aoDestruir_Bomba(Tobj *o);
void aoClock0_Bomba(Tobj *o);
void Movimentar_Bomba(Tobj *o);
void aoTerminarAnim_Bomba(Tobj *o);

//Bomber.h
void Bomber_Movimentar(Tobj *o);
void aoCriar_Bomber(Tobj *o);
void Colisoes_Bomber(Tobj *o);
void aoDestruir_Bomber(Tobj *o);

//BomberBurn.h
void aoTerminarAnim_BomberBurn(Tobj *o);
void aoCriar_BomberBurn(Tobj *o);
void aoClock0_BomberBurn(Tobj *o);

//Explosion.h
void aoTerminarAnim_Explosion(Tobj *o);
void aoCriar_Explosion(Tobj *o);

//WoodBox.h
void aoCriar_WoodBox(Tobj *o);
void aoDestruir_WoodBox(Tobj *o);
void SortItem(Tobj *o);

//Wall.h
void aoCriar_Wall(Tobj *o);

//Fire.h
void CrieChama(Tobj *o);
void TrateColisao(Tobj *o);
void aoCriar_Fire(Tobj *o);
void aoClock0_Fire(Tobj *o);
void aoClock1_Fire(Tobj *o);
void aoCriar_Fire2(Tobj *o);
void aoClock0_Fire2(Tobj *o);

//Dog
void aoCriar_Dog(Tobj *o);
void aoClock0_Dog(Tobj *o);
void aoDestruir_Dog(Tobj *o);
void Colisoes_Dog(Tobj *o);

//Caveira1
void aoCriar_Caveira1(Tobj *o);
void aoClock0_Caveira1(Tobj *o);
void Colisoes_Caveira1(Tobj *o);

//Explosion2
void aoCriar_Explosion2(Tobj *o);
void aoTerminarAnim_Explosion2(Tobj *o);

//Fogo
void aoCriar_Fogo(Tobj *o);
void aoClock0_Fogo(Tobj *o);

void PlayMusica(char c[])
{
	if ( strcmp(musica.nome, c))
	{
		Mix_FreeMusic(musica.arquivo);
		musica.arquivo = Mix_LoadMUS(c);
		Mix_PlayMusic(musica.arquivo, -1);
	}
}

int ColObjPos(Tobj *o, char c[], float x, float y)
{
	int i, oldx=o->x, oldy=o->y;
	
	o->x=x;
	o->y=y;
	
	for(i=0;i<nobj;i++)
	{
		if (!strcmp(obj[i].nome,c) && ColisaoS(o, &obj[i]) && o != &obj[i] && obj[i].vivo)
		{
			o->x=oldx;
			o->y=oldy;
			return i+1;
		}
	}
	
	o->x=oldx;
	o->y=oldy;
	
	return 0;
}

void DesenheBackground(char c[])
{
	int n,i,j;
	
	n = BuscaImg(c);
	
	if (n != -1)
	{
		for (i=0; i < screen_w; i += pic[n].img->w)
			for (j=0; j < screen_h; j += pic[n].img->h)
			{
				rect = (SDL_Rect) {i,j,pic[n].img->w,pic[n].img->h};
				SDL_BlitSurface(pic[n].img, NULL, screen, &rect);
			}
	}
}

int NaGrade(Tobj *o, int g)
{
	if (((int)o->x)%g==0 && ((int)o->y)%g==0)
		return 1;
	return 0;
}

void PuleAleatorio(Tobj *o)
{
	int x=screen_w/32,y=screen_h/32;
	do
	{
		o->x = rand()%x*32;
		o->y = rand()%y*32;
	}
	while(Colidindo(o,o->x,o->y) || (o->x==32 && o->y==96) || (o->x==32 && o->y==128) || (o->x==64 && o->y==96) || (o->y<64));
}

void UpdateZ(void)
{
	qsort(obj,nobj,sizeof(Tobj),cmp);
}

void AtualizeRelogio(Tobj *o)
{
	if (o->clock0 >=0)
	{
		if (o->clock0==0)
			aoClock0(o);
		o->clock0--;
	}
	
	if (o->clock1 >=0)
	{
		if (o->clock1==0)
			aoClock1(o);
		o->clock1--;
	}
}

void SomeImg(SDL_Surface* s, const SDL_Rect *sr,SDL_Surface* d,const SDL_Rect *dr, int p)
{
	int i, j, offset, max = d->w*d->h;
	Uint8 r, g, b, r2, g2, b2, tr, tg, tb;
	
	for (j=0; j < sr->h; j++)
		for (i=0; i < sr->w; i++)
		{
			if (dr->x+i<0 || dr->x+i >= d->w)
				continue;
			
			offset = sr->x+i + s->w*(j+sr->y);
			SDL_GetRGB(*((Uint16*)s->pixels + offset), s->format, &r2, &g2, &b2);
			
			offset = dr->x+i + d->w*(dr->y+j);
			if (offset>0 && offset<max)
				SDL_GetRGB(*((Uint16*)d->pixels + offset), d->format, &r, &g, &b);
			else
				continue;
			
			tr = (r2*p)/100;
			tg = (g2*p)/100;
			tb = (b2*p)/100;
			
			if ((int)r + (int)tr>255)
				r=255;
			else
				r+=tr;
				
			if ((int)g + (int)tg>255)
				g=255;
			else
				g+=tg;
				
			if ((int)b + (int)tb>255)
				b=255;
			else
				b+=tb;
			
			if (offset>0 && offset<max)
				*((Uint16*)d->pixels + offset) = (Uint16) SDL_MapRGB(d->format, r, g, b);
		}
}

void DefPic(Tobj *o, char c[])
{
	if(strcmp(o->pic, c))
	{
		strcpy(o->pic,c);
		o->frame=0;
	}
}

int cmp(const void *e1, const void *e2)
{
	Tobj a,b;
	
	a = *((Tobj *) e1);
	b = *((Tobj *) e2);
	
	if (a.z>b.z)
		return 1;
		
	if (a.z<b.z)
		return -1;
	
	if (a.y>b.y)
		return 1;
		
	if (a.y<b.y)
		return -1;
	
	return 0;
}

int cmppic(const void *e1, const void *e2)
{
	Tpic a,b;
	
	a = *((Tpic *) e1);
	b = *((Tpic *) e2);
	
	return strcmp(a.nome, b.nome);
}

int cmpsom(const void *e1, const void *e2)
{
	Tsom a,b;
	
	a = *((Tsom *) e1);
	b = *((Tsom *) e2);
	
	return strcmp(a.nome, b.nome);
}

void Iniciar(void)
{
	srand(time(NULL));
	
	SDL_WM_SetCaption("A DLN GAME PROJECT", "xD"); // dei um titulo para o programa
	
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	
	screen = SDL_SetVideoMode(screen_w, screen_h, 16, SDL_SWSURFACE);
	
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
	Mix_AllocateChannels(16);
	
	obj = (Tobj *) malloc(nobj*sizeof(Tobj));
	if (!obj)
	{
		printf("Falha ao alocar memoria para criar o vetor obj\n");
		exit(1);
	}
	pic = (Tpic *) malloc(npic*sizeof(Tpic));
	if (!pic)
	{
		printf("Falha ao alocar memoria para criar o vetor pic\n");
		exit(1);
	}
	som = (Tsom *) malloc(nsom*sizeof(Tsom));
	if (!pic)
	{
		printf("Falha ao alocar memoria para criar o vetor som\n");
		exit(1);
	}
}

void Finalizar(void)
{
	Mix_CloseAudio();
	free(obj);
	free(pic);
	free(som);
	SDL_Quit();
}

int ColisaoS(Tobj *o, Tobj *p)
{
	if(o->x+o->w > p->x && o->x < p->x+p->w)
		if(o->y+o->h > p->y && o->y < p->y+p->h)
			return 1;
	return 0;
}

int ColisaoS2(Tobj *o, Tobj *p, int d)
{
	if(o->x+o->w-d > p->x+d && o->x+d < p->x+p->w-d)
		if(o->y+o->h-d > p->y+d && o->y+d < p->y+p->h-d)
			return 1;
	return 0;
}

int Colidindo(Tobj *o, int x, int y)
{
	int i, oldx=o->x, oldy=o->y;
	
	o->x=x;
	o->y=y;
	
	for(i=0;i<nobj;i++)
	{
		if (ColisaoS(o, &obj[i]) && obj[i].solido && o != &obj[i] && obj[i].vivo)
		{
			o->x=oldx;
			o->y=oldy;
			return i+1;
		}
	}
	
	o->x=oldx;
	o->y=oldy;
	return 0;
}

int NotPlaceFree(Tobj *o, int x, int y)
{
	int i, oldx=o->x, oldy=o->y;
	
	o->x=x;
	o->y=y;
	
	for(i=0;i<nobj;i++)
	{
		if (ColisaoS(o, &obj[i]) && o!=&obj[i] && obj[i].vivo)
		{
			o->x=oldx;
			o->y=oldy;
			return i+1;
		}
	}
	
	o->x=oldx;
	o->y=oldy;
	return 0;
}


void Crie(char n[],float x, float y)
{
	nobj++;
	
	obj = (Tobj *) realloc(obj, nobj*sizeof(Tobj));
	
	if(!obj)
	{
		printf("Falha ao realocar memoria para criar: %s\n", n);
		exit(1);
	}
	
	obj[nobj-1].vivo = 1;
	
	strcpy(obj[nobj-1].nome, n);
	strcpy(obj[nobj-1].pic, "i");
	strcpy(obj[nobj-1].pic+1, n);
	
	obj[nobj-1].x = x;
	obj[nobj-1].y = y;
	obj[nobj-1].z = 0;
	obj[nobj-1].solido = 0;
	obj[nobj-1].frame = 0;
	
	obj[nobj-1].w = 32;
	obj[nobj-1].h = 32;
	
	obj[nobj-1].clock0 = -1;
	obj[nobj-1].clock1 = -1;
	
	obj[nobj-1].extra1 = 0;
	obj[nobj-1].extra2 = 0;
	
	obj[nobj-1].opac = -1;
	
	aoCriar(&obj[nobj-1]);
	
	RefreshList=1;
}

void Destrua(Tobj *p)
{
	p->vivo = 0;
	aoDestruir(p);	
}

void DestruaObj(char c[])
{
	int i;
	
	for (i=0;i<nobj;i++)
		if (!strcmp(obj[i].nome, c))
			Destrua(&obj[i]);
}

void KillAll(void)
{
	nobj=0;
	
	obj = (Tobj *) realloc(obj, nobj*sizeof(Tobj));
}

void Vanish(Tobj *o)
{
	o->vivo = 0;
}

void UpdateObjs(void)
{
	int i;
	for (i=0; i<nobj; i++)
	{
		if (!obj[i].vivo)
		{
			RefreshList=1;
			Tobj temp;
			
			temp = obj[i];
			obj[i] = obj[nobj-1];
			obj[nobj-1] = temp;
	
			nobj--;
	
			obj = (Tobj *) realloc(obj, nobj*sizeof(Tobj));
	
			if(!obj)
			{
				printf("Falha ao realocar memoria durante a destruição de um objeto");
				exit(1);
			}
		}
	}
	
	if (RefreshList)
	{
		UpdateZ();
		RefreshList=0;
	}
}

int BuscaSom(char nm[])
{
	int ini=0;
	int fim=nsom;
	int c;
	c=strcmp(nm, som[(ini+fim)/2].nome);
	while(c)
	{
		if(ini==fim-1) break;
		if(c>0)
			ini=(ini+fim)/2;
		else if(c<0)
			fim=(ini+fim)/2;
		c=strcmp(nm, som[(ini+fim)/2].nome);
	}
	if(c)
		return -1;
	return ((ini+fim)/2);
}

void PlaySom(char c[])
{
	int i = BuscaSom(c);
	
	if (i != -1)
	{
		Mix_PlayChannel(-1, som[i].som, 0);
	}
}

void LoadSom(char c[])
{
	nsom++;
	
	char f[150];
	int i;
	
	som = (Tsom *) realloc(som, npic*sizeof(Tsom));
	
	if (!som)
	{
		printf("Falha ao realocar memoria para o vetor som\n");
		exit(1);
	}
	
	strcpy(f,c);
	strcpy(f+strlen(c),".wav");
	som[nsom-1].som =  Mix_LoadWAV(f);
	
	if (!som[nsom-1].som)
	{
		printf("Nao foi possivel carregar: \"%s\"\n", c);
		exit(1);
	}
	
	for (i=strlen(c); c[i]!='/' && i>=0;i--);
	strcpy(som[nsom-1].nome, "s");
	strcpy(som[nsom-1].nome+1, &c[i+1]);
	
	qsort(som,nsom,sizeof(Tsom),cmpsom);
}

void LoadImg(char c[], int fh, int fv, int cx, int cy, int fpf)
{
	npic++;
	
	char f[150];
	int i;
	
	pic = (Tpic *) realloc(pic, npic*sizeof(Tpic));
	
	if (!pic)
	{
		printf("Falha ao realocar memoria para o vetor pic\n");
		exit(1);
	}
	
	strcpy(f,c);
	strcpy(f+strlen(c),".bmp");
	pic[npic-1].img = SDL_LoadBMP(f);
	
	if (!pic[npic-1].img)
	{
		printf("Nao foi possivel carregar: \"%s\"\n", c);
		exit(1);
	}
	
	for (i=strlen(c); c[i]!='/' && i>=0;i--);
	strcpy(pic[npic-1].nome, "i");
	strcpy(pic[npic-1].nome+1, &c[i+1]);
	
	pic[npic-1].fh = fh;
	pic[npic-1].fv = fv;
	
	pic[npic-1].center.x = cx;
	pic[npic-1].center.y = cy;
	
	pic[npic-1].fpf = fpf;
	
	pic[npic-1].LargFrame = pic[npic-1].img->w/pic[npic-1].fh;
	pic[npic-1].AltFrame = pic[npic-1].img->h/pic[npic-1].fv;
	
	SDL_SetColorKey(pic[npic-1].img, SDL_SRCCOLORKEY, SDL_MapRGB(pic[npic-1].img->format, 255, 0, 255));
	
	qsort(pic,npic,sizeof(Tpic),cmppic);
}

int BuscaImg(char nm[])
{
	int ini=0;
	int fim=npic;
	int c;
	c=strcmp(nm, pic[(ini+fim)/2].nome);
	while(c)
	{
		if(ini==fim-1) break;
		if(c>0)
			ini=(ini+fim)/2;
		else if(c<0)
			fim=(ini+fim)/2;
		c=strcmp(nm, pic[(ini+fim)/2].nome);
	}
	if(c)
		return -1;
	return ((ini+fim)/2);
}

void DesenheFrame(char c[], int f, float x, float y)
{
	int i = BuscaImg(c);
	
	if (i != -1 && f < pic[i].fh*pic[i].fv)
	{	
		rect = (SDL_Rect) 
		{
		x,
		y,
		pic[i].LargFrame,
		pic[i].AltFrame
		};
		
		frame = (SDL_Rect) 
		{
		f%pic[i].fh*pic[i].LargFrame,
		f/pic[i].fh*pic[i].AltFrame,
		pic[i].LargFrame,
		pic[i].AltFrame
		};
		
		SDL_BlitSurface(pic[i].img, &frame, screen, &rect);
	}
}

void Desenhe(Tobj *o)
{
	int i,a;
	
	i = BuscaImg(o->pic);
	
	if (i != -1)
	{
		a = pic[i].fh*pic[i].fv;
		rect = (SDL_Rect) 
		{
		o->x-pic[i].center.x,
		o->y-pic[i].center.y,
		pic[i].LargFrame,
		pic[i].AltFrame
		};
		
		frame = (SDL_Rect) 
		{
		o->frame/pic[i].fpf%pic[i].fh*pic[i].LargFrame,
		o->frame/pic[i].fpf/pic[i].fh*pic[i].AltFrame,
		pic[i].LargFrame,
		pic[i].AltFrame
		};
		
		if (o->opac < 0)
			SDL_BlitSurface(pic[i].img, &frame, screen, &rect);
		else
			SomeImg(pic[i].img, &frame, screen, &rect, o->opac);
		
		//SomeImg(SDL_Surface* s, SDL_Rect *sr,SDL_Surface* d, SDL_Rect dr, int p)
		o->frame++;
		
		if (o->frame >= pic[i].fpf*a)
		{
			o->frame = o->frame % a;
			aoTerminarAnim(o);
		}
		
		aoDesenhar(o);
	}
}

