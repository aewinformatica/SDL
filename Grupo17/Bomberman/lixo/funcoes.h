void CarregarMapa(int matriz[SCREEN_H/FIXO_H][SCREEN_W/FIXO_W], SDL_Surface* screen, SDL_Surface* chao, SDL_Surface* fixo, SDL_Surface* borda, SDL_Surface* quebra, SDL_Surface* forte)
{
	int i,j;

	for(i=0;i<(SCREEN_H/FIXO_H);i++)
	{
		for(j=0;j<(SCREEN_W/FIXO_W);j++)
		{
			if(matriz[i][j] == 0)	{
				dst_chao.x = j*FIXO_W;
				dst_chao.y = i*FIXO_H;
				SDL_BlitSurface(chao, NULL, screen, &dst_chao);
			}
			else if(matriz[i][j] == 1) {
				dst_fixo.x = j*FIXO_W;
				dst_fixo.y = i*FIXO_H;
				SDL_BlitSurface(fixo, NULL, screen, &dst_fixo);
			}
			else if(matriz[i][j] == 4) {
				dst_borda.x = j*FIXO_W;
				dst_borda.y = i*FIXO_H;
				SDL_BlitSurface(borda, NULL, screen, &dst_borda);
			}
			else if(matriz[i][j] == 2) {
				dst_quebra.x = j*FIXO_W;
				dst_quebra.y = i*FIXO_H;
				SDL_BlitSurface(quebra, NULL, screen, &dst_quebra);
			}
			else if(matriz[i][j] == 3) {
				dst_forte.x = j*FIXO_W;
				dst_forte.y = i*FIXO_H;
				SDL_BlitSurface(forte, NULL, screen, &dst_forte);
			}
			else if(matriz[i][j] == 9) {
				dst_movel.x = j*FIXO_W;
				dst_movel.y = i*FIXO_H;
				SDL_BlitSurface(movel, NULL, screen, &dst_movel);
				matriz[i][j] =0;
			}
		}
	}
}

void mover(char *muv, int matriz[SCREEN_H/FIXO_H][SCREEN_W/FIXO_W], SDL_Surface* car)
{
	int posX, posY;


	posX=(dst_movel.y/FIXO_H);  //posicao do carro em relacao a linha da matriz
	posY=(dst_movel.x/FIXO_W); //posicao do carro em relacao a coluna da matriz


		if((*muv == 'u')&&(matriz[posX-1][posY]==0))
		{
			dst_movel.y -= 40;
		}
		else if ((*muv == 'd')&&(matriz[posX+1][posY]==0))
		{
			dst_movel.y += 40;
		}
		else if((*muv == 'l')&&(matriz[posX][posY-1]==0))
		{
			dst_movel.x -= 40;
		}
		else if ((*muv == 'r')&&(matriz[posX][posY+1]==0))
		{
			dst_movel.x += 40;
		}
}

int bomb_mark(void)
{
	int timerbomb;
	timerbomb=SDL_GetTicks();
	dst_bomba.x=dst_movel.x;
	dst_bomba.y=dst_movel.y;
	SDL_BlitSurface(bomba ,NULL, screen , &dst_bomba);
	return timerbomb;
}


void explode(int matriz[SCREEN_H/FIXO_H][SCREEN_W/FIXO_W])
{
	/*explode a bomba*/

	if ((matriz[dst_bomba.y/40][(dst_bomba.x/40) + 1] != 1)&&(matriz[dst_bomba.y/40][(dst_bomba.x/40) + 1] != 4))
	{
		matriz[dst_bomba.y/40][dst_bomba.x/40 + 1] =0;
		dst_base.x=dst_bomba.x + 40;
		dst_base.y=dst_bomba.y;
		SDL_BlitSurface(base, NULL, screen, &dst_base);
	}

	if ((matriz[dst_bomba.y/40 + 1][dst_bomba.x/40] != 1)&&(matriz[dst_bomba.y/40 + 1][dst_bomba.x/40] != 4))
	{
		matriz[dst_bomba.y/40 + 1][dst_bomba.x/40] = 0;
		dst_base.x=dst_bomba.x;
		dst_base.y=dst_bomba.y + 40;
		SDL_BlitSurface(base, NULL, screen, &dst_base);
	}

	if ((matriz[dst_bomba.y/40 - 1][dst_bomba.x/40] != 1)&&(matriz[dst_bomba.y/40 - 1][dst_bomba.x/40] != 4))
	{
		matriz[dst_bomba.y/40 - 1][dst_bomba.x/40] = 0;
		dst_base.x=dst_bomba.x;
		dst_base.y=dst_bomba.y - 40;
        SDL_BlitSurface(base, NULL, screen, &dst_base);

	}

	if ((matriz[dst_bomba.y/40][dst_bomba.x/40 - 1] != 1)&&(matriz[dst_bomba.y/40][dst_bomba.x/40 - 1] != 4))
	{
		matriz[dst_bomba.y/40][dst_bomba.x/40 - 1] = 0;
		dst_base.x=dst_bomba.x - 40;
		dst_base.y=dst_bomba.y;
        SDL_BlitSurface(base, NULL, screen, &dst_base);
	}

    dst_base.x=dst_bomba.x;
    dst_base.y=dst_bomba.y;
    SDL_BlitSurface(base, NULL, screen, &dst_base);

}
