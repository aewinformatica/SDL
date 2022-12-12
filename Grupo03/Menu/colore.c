#include "meuinclude.h"

int colore (TEXTO *texto, int funcao)
{
	if(funcao)
	{
		texto->origem.y=0;
		return 1;
	}
	texto->origem.y=40;
	
	return 0;
}
