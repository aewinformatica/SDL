#include "meuinclude.h"

void le_recordes (SDL_Surface *screen)
{
	int i, j, tamanho_da_letra[5]={60,56,52,48,44};
	FILE *arquivo;
	_SAVE recordes[5];
	char num[100];
	
	arquivo=fopen("../Recordes/recordes.bin","r");
	
	for (i = 0; i < 5; i += 1)
	{
		fread(recordes[i].nome,15*sizeof(char),1,arquivo);
		fread(&recordes[i].pontos,sizeof(unsigned long long int),1,arquivo);
	}
	
	qsort(recordes,5,sizeof(_SAVE),compara);
	
	for(i=0;i<5;i++)
	{
		for (j = i; j < 5; j += 1)
		{
			if(recordes[i].pontos==recordes[j].pontos)
			{
				tamanho_da_letra[i]=tamanho_da_letra[j];
			}
		}
	}	
	for (i = 0; i < 5; i += 1)
	{
		sprintf(num,"%Lu",recordes[i].pontos);
		desenha_texto(recordes[i].nome,screen,10,75*(i+1),tamanho_da_letra[i],0,0,0);
		desenha_texto(num,screen,400,75*(i+1),tamanho_da_letra[i],0,0,0);
	}
	
	fclose(arquivo);
	return;
}
