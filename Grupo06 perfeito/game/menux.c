
#include"game.h"

#define BUTTON_W 243
#define BUTTON_H 53

typedef struct
{
	char nome[10];
	int pontos;
} Tcampo;

//superficie p/ fundo

SDL_Surface *menubg;

//botões em seu estado normal

SDL_Surface *b1;
SDL_Surface *b2;
SDL_Surface *b3;

//botoes no estado 1

SDL_Surface *b1u;
SDL_Surface *b2u;
SDL_Surface *b3u;

//botoes pressionados

SDL_Surface *b1p;
SDL_Surface *b2p;
SDL_Surface *b3p;

//botões
SDL_Rect button [3];

//um evento
SDL_Event sdlevent;

//estado dos botões (0=normal; 1=levantado; 2=pressionado)

int b1state = 0;
int b2state = 0;
int b3state = 0;

void Abertura(void)
{
	int a=0,dir=1,t=0;
	quit = 0;
	SDL_Surface *Minerva;
	SDL_Rect MinRet={254,120,0,0};
	
	Minerva = IMG_Load("Imagens/Minerva.bmp");
	
	SDL_Delay(500);
	
	while (!quit)
	{
		SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
		
		SDL_SetAlpha(Minerva, SDL_SRCALPHA, a);
		
		a+=dir;
		if (a>255)
		{
			dir=0;
			a=255;
		}
		if (dir==0)
		{
			t++;
		}
		if (t>250)
		{
			dir=-1;
		}
		if (a<0)
		{
			SDL_Delay(500);
			quit = 1;
		}
		
		while(SDL_PollEvent(&sdlevent))
		{
			switch(sdlevent.type)
			{
				case SDL_QUIT:
					quit = 1;
					break;
				case SDL_KEYDOWN:
					switch(sdlevent.key.keysym.sym)
					{
						case SDLK_ESCAPE:
							quit = 1;
							break;
						default: break;
					}
					break;
				default: break;
			}
		}
		
		SDL_BlitSurface(Minerva, NULL, screen, &MinRet);
		
		SDL_Flip(screen);
	}
}

void CarregarTudo(void)
{
		//LoadImg(Nome, Frames Horizontais, Frames Verticais, center.x, center.y, Frames por frame)
	
	LoadImg("Imagens/Wall/WallBorderDown",1,1,0,0,2);
	LoadImg("Imagens/Wall/WallLeft",1,1,0,0,2);
	LoadImg("Imagens/Wall/WallRight",1,1,0,0,2);
	LoadImg("Imagens/Wall/WallDown",1,1,0,0,2);
	LoadImg("Imagens/Wall/WallUp",1,1,0,0,2);
	LoadImg("Imagens/Wall/WallMiddle",1,1,0,0,2);
	LoadImg("Imagens/WoodBox",1,1,0,0,1);
	LoadImg("Imagens/Floor",1,1,0,0,1);
	LoadImg("Imagens/Barra",1,1,0,0,1);
	LoadImg("Imagens/Numeros",11,1,0,0,1);
	LoadImg("Imagens/font",12,4,0,0,2);
	
	LoadImg("Imagens/Bomber/BomberMoveLeft",8,1,0,10,2);
	LoadImg("Imagens/Bomber/BomberMoveRight",8,1,0,10,2);
	LoadImg("Imagens/Bomber/BomberMoveUp",8,1,0,14,2);
	LoadImg("Imagens/Bomber/BomberMoveDown",8,1,0,14,2);
	LoadImg("Imagens/Bomber/BomberLeft",1,1,0,10,1);
	LoadImg("Imagens/Bomber/BomberRight",1,1,0,10,1);
	LoadImg("Imagens/Bomber/BomberUp",1,1,0,14,1);
	LoadImg("Imagens/Bomber/BomberDown",1,1,0,14,1);
	LoadImg("Imagens/Bomber/BomberBurn",5,1,5,23,3);
	
	LoadImg("Imagens/Bomba/Bomba",4,1,0,0,3);
	LoadImg("Imagens/Bomba/FireM",2,1,0,0,2);
	LoadImg("Imagens/Bomba/FireLO",1,4,0,0,2);
	LoadImg("Imagens/Bomba/FireNS",4,1,0,0,2);
	LoadImg("Imagens/Bomba/FireO",1,4,0,0,2);
	LoadImg("Imagens/Bomba/FireN",4,1,0,0,2);
	LoadImg("Imagens/Bomba/FireL",1,4,0,0,2);
	LoadImg("Imagens/Bomba/FireS",4,1,0,0,2);
	
	LoadImg("Imagens/Explosion",6,1,17,56,6);
	LoadImg("Imagens/Explosion2",7,1,0,47,3);
	LoadImg("Imagens/Fogo",4,1,0,0,2);
	
	LoadImg("Imagens/Items/ItemBomba",1,1,0,0,2);
	LoadImg("Imagens/Items/ItemFire",1,1,0,0,2);
	LoadImg("Imagens/Items/ItemPatins",1,1,0,0,2);
	LoadImg("Imagens/Items/ItemLife",1,1,0,0,2);
	
	LoadImg("Imagens/Monsters/Dog/DogRight",1,1,6,12,3);
	LoadImg("Imagens/Monsters/Dog/DogLeft",1,1,6,12,3);
	LoadImg("Imagens/Monsters/Dog/DogDown",1,1,0,12,3);
	LoadImg("Imagens/Monsters/Dog/DogUp",1,1,0,16,3);
	LoadImg("Imagens/Monsters/Dog/DogMoveRight",6,1,6,12,3);
	LoadImg("Imagens/Monsters/Dog/DogMoveLeft",6,1,6,12,3);
	LoadImg("Imagens/Monsters/Dog/DogMoveDown",7,1,0,12,3);
	LoadImg("Imagens/Monsters/Dog/DogMoveUp",7,1,0,16,3);
	
	LoadImg("Imagens/Monsters/Caveira1/Caveira1Right",1,1,8,32,3);
	LoadImg("Imagens/Monsters/Caveira1/Caveira1Left",1,1,8,32,3);
	LoadImg("Imagens/Monsters/Caveira1/Caveira1Down",1,1,8,32,3);
	LoadImg("Imagens/Monsters/Caveira1/Caveira1Up",1,1,8,32,3);
	LoadImg("Imagens/Monsters/Caveira1/Caveira1MoveRight",3,1,8,32,3);
	LoadImg("Imagens/Monsters/Caveira1/Caveira1MoveLeft",3,1,8,32,3);
	LoadImg("Imagens/Monsters/Caveira1/Caveira1MoveDown",3,1,8,32,3);
	LoadImg("Imagens/Monsters/Caveira1/Caveira1MoveUp",3,1,8,32,3);
	
		//LoadSom(Nome)
	
	LoadSom("Sons/Explosion");
	LoadSom("Sons/Clock");
	LoadSom("Sons/Life");
	LoadSom("Sons/som");
}

int Menux(void)
{
	quit = 0;
 //carregando as imagens dos botões

   menubg = IMG_Load("Imagens/Menux/fundofinal.jpg");
   b1 = IMG_Load("Imagens/Menux/NOVO JOGO.png");
   b2 = IMG_Load("Imagens/Menux/Hall da Fama.png");
   b3 = IMG_Load("Imagens/Menux/sair.png");
   b1p = IMG_Load("Imagens/Menux/Novo Jogo2.png");
   b2p = IMG_Load("Imagens/Menux/Hall da Fama2.png");
   b3p = IMG_Load("Imagens/Menux/Sair2.png");
   b1u = IMG_Load("Imagens/Menux/Novo Jogo3.png");
   b2u = IMG_Load("Imagens/Menux/Hall da Fama3.png");
   b3u = IMG_Load("Imagens/Menux/Sair3.png");

//colocando transparencia nos botões

   SDL_SetColorKey(b1, SDL_SRCCOLORKEY, SDL_MapRGB(b1->format, 255, 0, 255));
   SDL_SetColorKey(b2, SDL_SRCCOLORKEY, SDL_MapRGB(b2->format, 255, 0, 255));
   SDL_SetColorKey(b3, SDL_SRCCOLORKEY, SDL_MapRGB(b3->format, 255, 0, 255));
   SDL_SetColorKey(b1u, SDL_SRCCOLORKEY, SDL_MapRGB(b1u->format, 255, 0, 255));
   SDL_SetColorKey(b2u, SDL_SRCCOLORKEY, SDL_MapRGB(b2u->format, 255, 0, 255));
   SDL_SetColorKey(b3u, SDL_SRCCOLORKEY, SDL_MapRGB(b3u->format, 255, 0, 255));
   SDL_SetColorKey(b1p, SDL_SRCCOLORKEY, SDL_MapRGB(b1p->format, 255, 0, 255));
   SDL_SetColorKey(b2p, SDL_SRCCOLORKEY, SDL_MapRGB(b2p->format, 255, 0, 255));
   SDL_SetColorKey(b3p, SDL_SRCCOLORKEY, SDL_MapRGB(b3p->format, 255, 0, 255));

//posições dos botões

   button[0].x = button[1].x = button[2].x = 347;
   button[0].y = 190;
   button[1].y = 270;
   button[2].y = 350;
   button[0].w = button[1].w = button[2].w = BUTTON_W;
   button[0].h = button[1].h = button[2].h = BUTTON_H;

//"Blitando" o menu

   SDL_BlitSurface ( menubg, 0, screen, 0 );
   SDL_BlitSurface ( b1, 0, screen, &button[0] );
   SDL_BlitSurface ( b2, 0, screen, &button[1] );
   SDL_BlitSurface ( b3, 0, screen, &button[2] );
   
//rodando a musica
   PlayMusica("Musicas/alladin.mod");

//Enquanto esc não for pressionada
   
while ( !quit )
   {
   	
      while(SDL_PollEvent(&sdlevent))
      {
	      
	    switch(sdlevent.type)
		{
			case SDL_QUIT: quit = 1; break;
			case SDL_KEYDOWN:
				if(sdlevent.key.keysym.sym==SDLK_ESCAPE)
				{
					quit = 1;
				}
				break;
			default: break;
		}
	      
//se o mouse estiver dentro do botão 0
         if ( ( sdlevent.motion.x >= button[0].x )
            && ( sdlevent.motion.x <= ( button[0].x + button[0].w ) )
            && ( sdlevent.motion.y >= ( button[0].y ) )
            && ( sdlevent.motion.y <= ( button[0].y + button[0].h ) ) )
         {
 //muda o estado para 1
		 
		 b1state = 1;

            if ( sdlevent.type == SDL_MOUSEBUTTONDOWN )
            {
//se houver clique esquerdo
		    PlaySom("ssom");

               if ( sdlevent.button.button == SDL_BUTTON_LEFT )
		        {
//muda o estado para 2	
			        b1state = 2;
			        Game();
			        PlayMusica("Musicas/alladin.mod");
			        FimDeJogo();
			        SDL_BlitSurface ( menubg, 0, screen, 0 );
			        SDL_BlitSurface ( b1, 0, screen, &button[0] );
			        SDL_BlitSurface ( b2, 0, screen, &button[1] );
			        SDL_BlitSurface ( b3, 0, screen, &button[2] );
		                quit = 0;
		      }
             }
          }


//do contrário o estado é 0

         else b1state = 0;

//se o mouse estiver dentro do botão 1

         if ( ( sdlevent.motion.x >= button[1].x )
            && ( sdlevent.motion.x <= ( button[1].x + button[1].w ) )
            && ( sdlevent.motion.y >= ( button[1].y ) )
            && ( sdlevent.motion.y <= ( button[1].y + button[1].h ) ) )
         {

 //muda o estado para 1

            b2state = 1;

            if ( sdlevent.type == SDL_MOUSEBUTTONDOWN )
            {

//se houver clique esquerdo

		    PlaySom("ssom");
               if ( sdlevent.button.button == SDL_BUTTON_LEFT )
               {
//muda o estado para 2

                  b2state = 2;
                  ShowRecords();
                  SDL_BlitSurface ( menubg, 0, screen, 0 );
		  SDL_BlitSurface ( b1, 0, screen, &button[0] );
		  SDL_BlitSurface ( b2, 0, screen, &button[1] );
		  SDL_BlitSurface ( b3, 0, screen, &button[2] );
	          quit = 0;
               }
            }
         }

//do contrário o estado é 0

         else b2state = 0;

//se o mouse estiver dentro do botão 2

	 if ( ( sdlevent.motion.x >= button[2].x )
            && ( sdlevent.motion.x <= ( button[2].x + button[2].w ) )
            && ( sdlevent.motion.y >= ( button[2].y ) )
            && ( sdlevent.motion.y <= ( button[2].y + button[2].h ) ) )
         {

//muda o estado para 1

            b3state = 1;

            if ( sdlevent.type == SDL_MOUSEBUTTONDOWN )
            {

//se houver clique esquerdo

		    PlaySom("ssom");
		    if ( sdlevent.button.button == SDL_BUTTON_LEFT )
               {

//muda o estado para 2
			quit = 1;
		       b3state = 2;
               }
            }
         }

//do contrário o estado é 

	 else b3state = 0;

//"Blitando os botões de acordo com seu estado

         if ( b1state == 0 )
            SDL_BlitSurface ( b1, 0, screen, &button[0] );

         else if ( b1state == 1 )
            SDL_BlitSurface ( b1u, 0, screen, &button[0] );

         else if ( b1state == 2 )
            SDL_BlitSurface ( b1p, 0, screen, &button[0] );

         if ( b2state == 0 )
            SDL_BlitSurface ( b2, 0, screen, &button[1] );

         else if ( b2state == 1 )
            SDL_BlitSurface ( b2u, 0, screen, &button[1] );

         else if ( b2state == 2 )
            SDL_BlitSurface ( b2p, 0, screen, &button[1] );

         if ( b3state == 0 )
            SDL_BlitSurface ( b3, 0, screen, &button[2] );

         else if ( b3state == 1 )
            SDL_BlitSurface ( b3u, 0, screen, &button[2] );

         else if ( b3state == 2 )
            SDL_BlitSurface ( b3p, 0, screen, &button[2] );

//atualizando tela

         SDL_UpdateRect ( screen, 0, 0, 0, 0 );
      }

   }

   return 0;

}

int FimDeJogo(void)
{
	FILE * f;
	Tcampo campo[10];
	int i, min=999999999;
	
	quit =0;
	
	f = fopen("Recordes", "r");
	
	if (!f)
	{
		f = fopen("Recordes", "w+");
		for (i=0;i<10;i++)
		{
			strcpy(campo[i].nome,"---");
			campo[i].pontos = 0;
		}
		fwrite(campo,sizeof(Tcampo),10,f);
		
		fseek(f,0,SEEK_SET);
	}
	
	fread(campo,sizeof(Tcampo),10,f);
	for (i=0;i<10;i++)
		if (campo[i].pontos<min)
			min = campo[i].pontos;
	fclose(f);
	
	if (min < score)
		InsiraNome();
	ShowRecords();
	
	return 0;
}

void InsiraNome(void)
{
	char nome[10];
	int x;
	
	nome[0]='\0';
	
	quit = 0;

	SDL_BlitSurface ( menubg, 0, screen, 0 );
	
	PlayMusica("Musicas/alladin.mod");
   
	while ( !quit )
	{
   	
		while(SDL_PollEvent(&sdlevent))
		{
		 
			switch(sdlevent.type)
			{
				case SDL_QUIT: quit = 1; break;
				case SDL_KEYDOWN:
					if ((sdlevent.key.keysym.sym-SDLK_a>=0 && sdlevent.key.keysym.sym-SDLK_a<=25) || (sdlevent.key.keysym.sym-SDLK_1>=0 && sdlevent.key.keysym.sym-SDLK_0<=10) || (sdlevent.key.keysym.sym==SDLK_EXCLAIM) || (sdlevent.key.keysym.sym==SDLK_ASTERISK) || (sdlevent.key.keysym.sym==SDLK_MINUS) || (sdlevent.key.keysym.sym==SDLK_SPACE))
					{
					if (strlen(nome)<10)
						sprintf(nome+strlen(nome),"%c", sdlevent.key.keysym.sym);
					}
					else
					if (sdlevent.key.keysym.sym==SDLK_BACKSPACE)
						nome[strlen(nome)-1]='\0';
					else
					if (sdlevent.key.keysym.sym==SDLK_RETURN)
						quit = 1;
					else
					if (sdlevent.key.keysym.sym==SDLK_ESCAPE)
					{
						nome[0]='\0';
						quit=1;
					}
					break;
				default: break;
			}
		}
		
		SDL_BlitSurface ( menubg, 0, screen, 0 );
		
		x = 425-((strlen(nome)*18)/2);
		Escreva("novo recorde",346,188);
		Escreva("digite seu nome:",330,210);
		Escreva(nome,x,270);
		
		SDL_UpdateRect ( screen, 0, 0, 0, 0 );

	}
	
	if (nome[0]!='\0')
	{
		FILE * f;
		Tcampo campo[11];
	
		f = fopen("Recordes", "r+");
		fread(campo,sizeof(Tcampo),10,f);
		
		strcpy(campo[10].nome,nome);
		campo[10].pontos = score;
		
		qsort(campo,11,sizeof(Tcampo),ordene);
		
		fseek(f,0,SEEK_SET);
		
		fwrite(campo,sizeof(Tcampo),10,f);
		
		fclose(f);
	}
}

void Escreva(char n[], float x, float y)
{
	int i;
	for (i=0;i<strlen(n);i++)
	{
		if (n[i]>='a' &&  n[i]<='z')
			DesenheFrame("ifont", n[i]-'a'+10, x+i*18,y);
		if (n[i]>='0' && n[i]<='9')
			DesenheFrame("ifont", n[i]-'0', x+i*18,y);
		if (n[i]=='-')
			DesenheFrame("ifont", 38, x+i*18,y);
		if (n[i]=='!')
			DesenheFrame("ifont", 36, x+i*18,y);
		if (n[i]=='*')
			DesenheFrame("ifont", 0, x+i*18,y);
		if (n[i]==' ')
			DesenheFrame("ifont", 39, x+i*18,y);
	}
}

void ShowRecords(void)
{
	FILE * f;
	Tcampo campo[11];
	char pontos[10];
	int i;

	f = fopen("Recordes", "r");
	
	if (!f)
	{
		f = fopen("Recordes", "w+");
		for (i=0;i<10;i++)
		{
			strcpy(campo[i].nome,"---");
			campo[i].pontos = 0;
		}
		fwrite(campo,sizeof(Tcampo),10,f);
		
		fseek(f,0,SEEK_SET);
	}
	
	fread(campo,sizeof(Tcampo),10,f);
	
	fclose(f);
	
	SDL_BlitSurface ( menubg, 0, screen, 0 );
	
	quit = 0;
	
	Escreva("hall da fama",283,156);
	
	for (i=0;i<10;i++)
	{
		Escreva(campo[i].nome,303,190+i*18);
		sprintf(pontos,"%d", campo[i].pontos);
		Escreva(pontos,503,190+i*18);
	}
	Escreva("pressione uma tecla",253,394);
	Escreva("para voltar",253,422);
	
	SDL_UpdateRect ( screen, 0, 0, 0, 0 );
	while ( !quit )
	{
		while(SDL_PollEvent(&sdlevent))
		{
		 
			switch(sdlevent.type)
			{
				case SDL_QUIT:
				case SDL_KEYDOWN:
					 quit = 1; break;
				default: break;
			}
		}
	}
}

int ordene(const void *e1, const void *e2)
{
	Tcampo a,b;
	
	a = *((Tcampo *) e1);
	b = *((Tcampo *) e2);
	
	if (a.pontos>b.pontos)
		return -1;
		
	if (a.pontos<b.pontos)
		return 1;
	
	return 0;
}

