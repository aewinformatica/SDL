#include "meuinclude.h"

void salva (int slot)
{
	switch(slot)
	{
		case 0:
			jogo.arquivo=fopen("../Saves/slot0.bin","r+");
			fseek(jogo.arquivo,0,SEEK_END);
			if(!ftell(jogo.arquivo))
			{
				fclose(jogo.arquivo);
				jogo.arquivo=fopen("../Saves/slot0.bin","w+");
			}
			else
			{
				jogo.arquivo=fopen("../Saves/slot0.bin","w+");
			}
			break;
		case 1:
			jogo.arquivo=fopen("../Saves/slot1.bin","w+");
			break;
		case 2:
			jogo.arquivo=fopen("../Saves/slot2.bin","w+");
			break;
		case 3:
			jogo.arquivo=fopen("../Saves/slot3.bin","w+");
			break;
		case 4:
			jogo.arquivo=fopen("../Saves/slot4.bin","w+");
			break;
		default: break;
	}
	fwrite(jogo.nome,sizeof(jogo.nome),1,jogo.arquivo);
	fwrite(&jogo.pontos,sizeof(jogo.pontos),1,jogo.arquivo);
	fclose(jogo.arquivo);
	return;
}
