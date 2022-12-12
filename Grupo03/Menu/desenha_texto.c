#include "meuinclude.h"


void desenha_texto(char* text, SDL_Surface* dst, int x, int y, int tam, int cor1, int cor2, int cor3)
{
	TTF_Font *fonte;
	fonte = TTF_OpenFont("Fontes/BAVEUSE.TTF", tam);

	SDL_Color cor = {cor1,cor2,cor3}; //vermelho
	SDL_Surface* src = TTF_RenderText_Blended(fonte, text, cor);
	SDL_Rect dst_rect = {x, y, 0, 0};

	SDL_BlitSurface(src, NULL, dst, &dst_rect);
	
	TTF_CloseFont(fonte);
	SDL_FreeSurface(src);
}
