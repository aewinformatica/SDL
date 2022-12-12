#include "meuinclude.h"

unsigned long long int calcula_pontos (int max_tempo, int tempo_decorrido)
{
	int i;
	unsigned long long int calculando=0;
	if(tempo_decorrido<=1000*max_tempo)
	{
		for(i=1;i<=max_tempo-(tempo_decorrido)/1000;i++)
		{
			calculando+=10*i;
		}
	}
	return calculando;
}
