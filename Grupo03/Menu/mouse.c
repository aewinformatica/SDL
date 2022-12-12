#include "meuinclude.h"


int verificaMouse (TEXTO texto, int x, int y)
{
	if ( ( x>=texto.destino.x && x<=texto.destino.x+texto.destino.w) && (y>=texto.destino.y && y<=texto.destino.y+texto.destino.h) )
	{
		return 1;
	}
	return 0;
}
