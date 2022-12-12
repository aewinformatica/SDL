void Labirinto(int grade[DIM][MAX] , SDL_Surface* quad, SDL_Surface* screen, int vidas)
{
	int i,j;

	for (i=0; i<DIM;i++ )
	{
		for (j=0;j<MAX ;j++ )
		{
			if(grade[i][j] == 1)
			{
				dst_quad.x=j*50;//50 é o tamanho do quadrado
				dst_quad.y=i*50;
				SDL_BlitSurface(quad ,NULL, screen , &dst_quad);
			}
			else if (grade[i][j]==2)
			{
				dst_tile.x=j*50;
				dst_tile.y=i*50;
				SDL_BlitSurface(tile ,NULL, screen , &dst_tile);
			}
			else if (grade[i][j]==3)
			{
				dst_quad2.x=j*50;
				dst_quad2.y=i*50;
				SDL_BlitSurface(quad2 ,NULL, screen , &dst_quad2);
			}
			else if (grade[i][j]==5)
			{

				if (vidas == 3)
				{
					dst_vidas3.x=j*50;
					dst_vidas3.y=i*50;
					SDL_BlitSurface(vidas3 ,NULL, screen , &dst_vidas3);
				}
				else if (vidas == 2)
				{
					dst_vidas2.x=j*50;
					dst_vidas2.y=i*50;
					SDL_BlitSurface(vidas2 ,NULL, screen , &dst_vidas2);
				}
				else if (vidas == 1)
				{
					dst_vidas1.x=j*50;
					dst_vidas1.y=i*50;
					SDL_BlitSurface(vidas1 ,NULL, screen , &dst_vidas1);
				}
				else if (vidas == 0)
				{
					dst_vidas0.x=j*50;
					dst_vidas0.y=i*50;
					SDL_BlitSurface(vidas0 ,NULL, screen , &dst_vidas0);
				}

			}
			else if (grade[i][j]==6)
			{
				dst_me.x=j*50;
				dst_me.y=i*50;
				SDL_BlitSurface(me ,NULL, screen , &dst_me);
			}
			else if (grade[i][j]==7)
			{
				dst_nu.x=j*50;
				dst_nu.y=i*50;
				SDL_BlitSurface(nu ,NULL, screen , &dst_nu);
			}
		}
	}
}

void hello_andando(char *passo1, int grade[DIM][MAX],SDL_Surface* hello)
{
	int incx,incy;

	incx=(dst_hello.y/50);
	incy=(dst_hello.x/50);

	if((*passo1 == 'h')&&(grade[incx-1][incy]==0))
		{
			dst_hello.y -= 50;
			SDL_Delay(DEL);

		}
		else if ((*passo1 == 'e')&&(grade[incx+1][incy]==0))
		{
			dst_hello.y += 50;
			SDL_Delay(DEL);

		}
		else if((*passo1 == 'l')&&(grade[incx][incy-1]==0))
		{
			dst_hello.x -= 50;
			SDL_Delay(DEL);

		}
		else if ((*passo1 == 'o')&&(grade[incx][incy+1]==0))
		{
			dst_hello.x += 50;
			SDL_Delay(DEL);
		}

}

int bombando(void)
{
	int timerbomb;
	timerbomb=SDL_GetTicks();
	dst_bomba.x=dst_hello.x;
	dst_bomba.y=dst_hello.y;
	SDL_BlitSurface(bomba ,NULL, screen , &dst_bomba);
	return timerbomb;
}


void explode(int grade[DIM][MAX])
{
	/*explode a bomba*/

	if (grade[dst_bomba.y/50][(dst_bomba.x/50) + 1] != 1 &&
		grade[dst_bomba.y/50][(dst_bomba.x/50) + 1] != 3 &&
		grade[dst_bomba.y/50][(dst_bomba.x/50) + 1] != 5 &&
		grade[dst_bomba.y/50][(dst_bomba.x/50) + 1] != 6 &&
		grade[dst_bomba.y/50][(dst_bomba.x/50) + 1] != 7)
	{
		grade[dst_bomba.y/50][dst_bomba.x/50 + 1] =0;
		chao.x=dst_bomba.x + 50;
		chao.y=dst_bomba.y;
		SDL_FillRect(screen, &chao, SDL_MapRGB(screen->format, 244, 152, 191));
	}

	if (grade[dst_bomba.y/50 + 1][dst_bomba.x/50] !=1 &&
		grade[dst_bomba.y/50 + 1][dst_bomba.x/50] !=3 &&
		grade[dst_bomba.y/50 + 1][dst_bomba.x/50] !=5 &&
		grade[dst_bomba.y/50 + 1][dst_bomba.x/50] !=6 &&
		grade[dst_bomba.y/50 + 1][dst_bomba.x/50] !=7)
	{
		grade[dst_bomba.y/50 + 1][dst_bomba.x/50] = 0;
		chao.x=dst_bomba.x;
		chao.y=dst_bomba.y + 50;
		SDL_FillRect(screen, &chao, SDL_MapRGB(screen->format, 244, 152, 191));
	}

	if (grade[dst_bomba.y/50 - 1][dst_bomba.x/50] !=1 &&
		grade[dst_bomba.y/50 - 1][dst_bomba.x/50] !=3 &&
		grade[dst_bomba.y/50 - 1][dst_bomba.x/50] !=5 &&
		grade[dst_bomba.y/50 - 1][dst_bomba.x/50] !=6 &&
		grade[dst_bomba.y/50 - 1][dst_bomba.x/50] !=7 )
	{
		grade[dst_bomba.y/50 - 1][dst_bomba.x/50] = 0;
		chao.x=dst_bomba.x;
		chao.y=dst_bomba.y - 50;
		SDL_FillRect(screen, &chao, SDL_MapRGB(screen->format, 244, 152, 191));

	}

	if (grade[dst_bomba.y/50][dst_bomba.x/50 - 1] !=1 &&
		grade[dst_bomba.y/50][dst_bomba.x/50 - 1] !=3 &&
		grade[dst_bomba.y/50][dst_bomba.x/50 - 1] !=5 &&
		grade[dst_bomba.y/50][dst_bomba.x/50 - 1] !=6 &&
		grade[dst_bomba.y/50][dst_bomba.x/50 - 1] !=7 )
	{
		grade[dst_bomba.y/50][dst_bomba.x/50 - 1] = 0;
		chao.x=dst_bomba.x - 50;
		chao.y=dst_bomba.y;
		SDL_FillRect(screen, &chao, SDL_MapRGB(screen->format, 244, 152, 191));
	}


	SDL_FillRect(screen, &dst_bomba, SDL_MapRGB(screen->format, 244, 152, 191));

}

int morrendo(int vidas)
{
	/*mata a hello kitty*/

	if (dst_bomba.y/50 == dst_hello.y/50 && (dst_bomba.x/50) + 1 == dst_hello.x/50)
	{
		vidas--;
		SDL_Delay(30);
		dst_hello.x=50;
		dst_hello.y=50;
	}

	if (dst_bomba.y/50 + 1 == dst_hello.y/50 && dst_bomba.x/50 == dst_hello.x/50)
	{
		vidas--;
		SDL_Delay(30);
		dst_hello.x=50;
		dst_hello.y=50;
	}

	if (dst_bomba.y/50 - 1 == dst_hello.y/50 && dst_bomba.x/50 == dst_hello.x/50)
	{
		vidas--;
		SDL_Delay(30);
		dst_hello.x=50;
		dst_hello.y=50;
	}

	if (dst_bomba.y/50 == dst_hello.y/50 && dst_bomba.x/50 - 1 == dst_hello.x/50)
	{
		vidas--;
		SDL_Delay(30);
		dst_hello.x=50;
		dst_hello.y=50;
	}
	if (dst_bomba.y/50 == dst_hello.y/50 && dst_bomba.x/50 == dst_hello.x/50)
	{
		vidas--;
		SDL_Delay(30);
		dst_hello.x=50;
		dst_hello.y=50;
	}



	return vidas;

}


void gameover(int life)
{
	if (life<0)
	{
		SDL_Surface* gover;
		SDL_Rect dst_gover = {0, 0, 0, 0};
		gover = IMG_Load("img/gameover.gif");
		SDL_BlitSurface(gover, NULL, screen, &dst_gover);
		SDL_Flip(screen);
		SDL_Delay(3000);
		menu(1);
		exit(0);
	}

}

void escondendo (int grade[DIM][MAX])
{
	srand(time(NULL));

	a=rand() % 13;
	b=rand() % 17;

	while (grade[a][b]!=2)
	{
		a=rand() % 13;
		b=rand() % 17;
	}
}

void achou(int grade[DIM][MAX])
{
	SDL_Surface* win;
	SDL_Rect dst_win = {0, 0, 0, 0};
	win = IMG_Load("img/youwin.gif");
	SDL_BlitSurface(win, NULL, screen, &dst_win);
	SDL_Flip(screen);
	SDL_Delay(3000);
	menu(1);
	exit(0);
}




void andachoco(SDL_Rect *dst_choco, int grade[DIM][MAX])
{
		int x;

	x=rand()%4;

	switch(x)
	{
		case 0:
			if (grade[(dst_choco->y/50)-1][dst_choco->x/50]==0)
			{
				dst_choco->y -=50;
			}
			break;

		case 1:
			if (grade[(dst_choco->y/50) + 1][dst_choco->x/50]==0)
			{
				dst_choco->y +=50;
				break;
			}
		case 2:
			if (grade[dst_choco->y/50][(dst_choco->x/50)-1]==0)
			{
				dst_choco->x -=50 ;
			}
			break;
		case 3:
			if (grade[dst_choco->y/50][(dst_choco->x/50)+1]==0)
			{
				dst_choco->x +=50 ;
			}
			break;
	}

}



int mata_hello(SDL_Rect *dst_choco,int vidas)
{
	/* choco matou a hello*/

	if ((dst_choco->y/50 == dst_hello.y/50) && (dst_choco->x/50  == dst_hello.x/50))
	{
			vidas--;
			SDL_Delay(30);
			dst_hello.x=50;
			dst_hello.y=50;

	}
	return vidas;
}


void mata_choco(SDL_Rect *dst_choco,int grade[DIM][MAX])
{
       //bomba mata o choco
       if ((dst_bomba.y/50 == dst_choco->y/50) && ((dst_bomba.x/50) + 1 == dst_choco->x/50))
       {

            dst_choco->y=900;
			dst_choco->x=900;

       }

       if (((dst_bomba.y/50) + 1 == dst_choco->y/50) && (dst_bomba.x/50 == dst_choco->x/50))
       {

            dst_choco->y=900;
			dst_choco->x=900;


       }

       if (((dst_bomba.y/50) - 1 == dst_choco->y/50) && (dst_bomba.x/50 == dst_choco->x/50))
       {
            dst_choco->y=900;
			dst_choco->x=900;

       }

       if ((dst_bomba.y/50 == dst_choco->y/50 ) && ((dst_bomba.x/50) - 1 == dst_choco->x/50))
       {
            dst_choco->y=900;
			dst_choco->x=900;
       }
       if ((dst_bomba.y/50 == dst_choco->y/50) && (dst_bomba.x/50 == dst_choco->x/50))
       {
            dst_choco->y=900;
			dst_choco->x=900;
       }

}


