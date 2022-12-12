#include "meuinclude.h"

int cliqueMouse(TEXTO texto,int funcao, int intervalo)
{
	if (funcao)
	{
		return texto.destino.y/intervalo;
	}
	return 0;	
} 
