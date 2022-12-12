#include "meuinclude.h"

void salva_recordes (void)
{
	int i, j, fonte[5]={50,46,42,38,34};
	_SAVE score[6];
	
	
	score[0].arquivo=fopen("../Recordes/recordes.bin","r+");
	
	for (i = 0; i < 5; i += 1)
	{
		fread(score[i].nome,8*sizeof(char),1,score[0].arquivo);
		fread(&score[i].pontos,sizeof(unsigned long long int),1,score[0].arquivo);
	}

	for(i=0;i<12;i++)
	{
		score[5].nome[i]=jogo.nome[i];
	}
	score[5].pontos=jogo.pontos;
		
	qsort(score,6,sizeof(_SAVE),compara);
	fclose(score[0].arquivo);
	score[0].arquivo=fopen("../Recordes/recordes.bin","wb+");	
	
	for (i = 0; i < 5; i += 1)
	{
		fwrite(score[i].nome,15*sizeof(char),1,score[0].arquivo);
		fwrite(&score[i].pontos,1*sizeof(unsigned long long int),1,score[0].arquivo);
	}
	fclose(score[0].arquivo);
	return ;
}
