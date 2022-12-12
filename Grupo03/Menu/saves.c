#include "meuinclude.h"

void le_Saves (SDL_Surface *screen)
{
	int i, arquivo[5];
	char *pontinho;
	SDL_Surface *vazio, *ocupado;
	SDL_Rect destino[5], origem_vazio, origem_ocupado;

	vazio=IMG_Load("Imagens/Frases/vazio.png");
	ocupado=IMG_Load("Imagens/Frases/ocupado.png");
	origem_vazio=(SDL_Rect){0,80,vazio->w,40};
	origem_ocupado=(SDL_Rect){0,80,ocupado->w,40};

	memset(arquivo,1,sizeof(arquivo));

	save[0].arquivo=fopen("../Saves/slot0.bin","r+");
	save[1].arquivo=fopen("../Saves/slot1.bin","r+");
	save[2].arquivo=fopen("../Saves/slot2.bin","r+");
	save[3].arquivo=fopen("../Saves/slot3.bin","r+");
	save[4].arquivo=fopen("../Saves/slot4.bin","r+");

	for(i=0;i<5;i++)
	{
		fseek(save[i].arquivo,0,SEEK_END);
		if(!ftell(save[i].arquivo))
		{
			arquivo[i]=0;
		}
		fseek(save[i].arquivo,0,SEEK_SET);
	}
	for(i=0;i<5;i++)
	{
		if(arquivo[i]==0)
		{
			if(i<3)
			{
				destino[i]=(SDL_Rect){20+180*i,20,0,0};

			}
			else
			{
				destino[i]=(SDL_Rect){20+(i-3)*180,30+224,0,0};
			}
			SDL_BlitSurface(vazio,&origem_vazio,screen,&destino[i]);
		}
		else
		{
			fread(save[i].nome, sizeof(char),8,save[i].arquivo);
			fseek(save[i].arquivo,-sizeof(unsigned long long int),SEEK_END);
			fread(&save[i].pontos,sizeof(unsigned long long int), 1, save[i].arquivo);
			sprintf(pontinho,"%Lu",save[i].pontos);
			if(i<3)
			{
				destino[i]=(SDL_Rect){10+180*i,20,0,0};
				desenha_texto(save[i].nome,screen,20+180*i,50,25,0,0,0);
				desenha_texto(pontinho,screen,20+180*i,80,25,0,0,0);
			}
			else
			{
				destino[i]=(SDL_Rect){10+180*(i-3),30+224,0,0};
				desenha_texto(save[i].nome,screen,20+180*(i-3),60+224,25,0,0,0);
				desenha_texto(pontinho,screen,20+180*(i-3),90+224,25,0,0,0);
			}
			SDL_BlitSurface(ocupado,&origem_ocupado,screen,&destino[i]);


		}
	}
	for (i = 0; i < 5; i += 1)
	{
		fclose(save[i].arquivo);
	}

	return;
}
