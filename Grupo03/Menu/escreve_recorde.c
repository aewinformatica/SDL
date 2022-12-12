#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[])
{
	FILE *arquivo;
	char *nome;
	unsigned long long int bla=2000, blah=3000;
	int i;

	nome=(char *){"Pedro"};

	arquivo=fopen("../Recordes/recordes.bin","w+");

	for (i = 0; i < 5; i += 1)
	{
		fwrite(nome,15*sizeof(char),1,arquivo);
		if(i<2)
		{
			bla*=(i+3);
			fwrite(&bla,sizeof(bla),1,arquivo);
		}
		else if (i==2)
		{
			bla=25000;
			fwrite(&bla,sizeof(bla),1,arquivo);
		}
		else
		{
			blah*=i;
			fwrite(&blah,sizeof(blah),1,arquivo);
		}
	}

	fclose(arquivo);
	return 0;
}
