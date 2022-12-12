#include "include.h"

int sorteiaFase(int inimigos,int **posInim)
{
	int matriz[14][17];
	int i, j, t;
	FILE *arq;
	char *nome;

	//nome dos arquivos a serem criados
	nome = "./matrizes/matriz0.bin";

	//zera a matriz
	memset(matriz, 0, sizeof(matriz));

	//definindo os elementos fixos
	for(i=0; i<14; i++)
	{
		for(j=0; j<17; j++)
		{
			if((!i)||(!j)||(i==1)||(i==13)||(j==16))
			{
				matriz[i][j]=1;
			}
			else if((i%2) && !(j%2))
			{
				matriz[i][j]=1;
			}
		}
	}

	


		srand(time(NULL));

		//definindo elementos que podem explodir
		for (t=0; t<80; t++)
		{
			i=rand()%14;
			j=rand()%17;

			if((!matriz[i][j]))
			{
				matriz[i][j]=2;
			}
			else
			{
				t--;
			}

			if((i==2 && j==2) || (i==3 && j==1) || (i==2 && j==1))
			{
				matriz[i][j]=0;
			}
		}

		// força o player estar cercado for destrutiveis (sem inimigo por perto)
		matriz[4][1] = 2;
		matriz[2][3] = 2;

		//definindo inimigos
		for (t=0; t<inimigos; t++)
		{
			i=rand()%14;
			j=rand()%17;

			if((!matriz[i][j]))
			{
				matriz[i][j]=3;
				posInim[t][4] = (rand()%5);
			}
			else
			{
				t--;
			}

			if((i==2 && j==2) || (i==3 && j==1) || (i==2 && j==1))
			{
				matriz[i][j]=0;
				t--;
			}
		}

		//definindo a saída
		for (t=0; t<1; t++)
		{
			i=rand()%14;
			j=rand()%17;

			if((matriz[i][j])==2)
			{
				matriz[i][j]=4;
			}
			else
			{
				t--;
			}
		}

		arq = fopen(nome, "w");

		fwrite(matriz, sizeof(matriz), 1, arq);

		fclose(arq);

		return (rand()%4);
}
