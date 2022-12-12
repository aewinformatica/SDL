//new
#include "global.h"
#include "prototipos.h"

int menu2 (SDL_Surface *screen, int* voltar_pro_menu_inicial)/*!!!!!!!!!!!!Alterei a funcao menu2 pra ela poder "mexer" no quit da funcao jogo (na esperanca que isso evite as 12094271 de f_jogos e f_menus)*/
{
	int tempo0 = SDL_GetTicks();
	SDL_Rect rect_menu = {M2_X,M2_Y,0,0};
	SDL_Surface *menu2 = IMG_Load("menu2.png");
	SDL_Surface *menu2c = IMG_Load("menu2c.png");
	SDL_Surface *menu2sal = IMG_Load("menu2sal.png");
	SDL_Surface *menu2sair = IMG_Load("menu2sair.png");

	int quit=0;

	SDL_BlitSurface(menu2, NULL, screen, &rect_menu);

	while(!quit)
    {
        while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				case SDL_QUIT: quit = 1; break;
				case SDL_MOUSEMOTION:
				case SDL_MOUSEBUTTONDOWN:
					if(event.motion.x > M2_LEFT && event.motion.x < M2_RIGHT)
					{
						if(event.motion.y > M2_HORIZ && event.motion.y < M2_HORIZ + M2_DST)
						{
							SDL_BlitSurface(menu2c, NULL, screen, &rect_menu);
							if(event.button.button == SDL_BUTTON_LEFT)
							{
								
								quit = 1;
							}
						}else 
						if(event.motion.y > M2_HORIZ + M2_DST && event.motion.y < M2_HORIZ + 2*M2_DST)
						{
							SDL_BlitSurface(menu2sal, NULL, screen, &rect_menu);
							if(event.button.button == SDL_BUTTON_LEFT)
							{
								//recorde();
							}
						}else 
						if(event.motion.y > M2_HORIZ + 2*M2_DST && event.motion.y < M2_HORIZ + 3*M2_DST)
						{
							SDL_BlitSurface(menu2sair, NULL, screen, &rect_menu);
							if(event.button.button == SDL_BUTTON_LEFT)
							{
							
								recorde();
								f_menu();
								*voltar_pro_menu_inicial = 1;
								return;
							}
						}else SDL_BlitSurface(menu2, NULL, screen, &rect_menu);
					}else SDL_BlitSurface(menu2, NULL, screen, &rect_menu);
					break;
					
					case SDL_KEYDOWN:
					{
						switch(event.key.keysym.sym)
						{
							case SDLK_ESCAPE: quit=1; break; /*!!!!!!!!!!!!Alterei a funcao menu2 pra ela poder "mexer" no quit da funcao jogo (na esperanca que isso evite as 12094271 de f_jogos e f_menus)*/
							default: break;
						}
						break;
					}
			}

			SDL_Flip(screen);
		}
	}
	return SDL_GetTicks() - tempo0;


}

void desenha_texto(char* texto, SDL_Surface* dst, int x, int y)
{
	SDL_Color cor = {255, 255, 255}; //branco
	SDL_Surface* src = TTF_RenderText_Blended(my_font2, texto, cor);
	SDL_Rect dst_rect = {x, y, 0, 0};
	SDL_BlitSurface(src, NULL, dst, &dst_rect);
	SDL_FreeSurface(src);
}
void apaga_texto(SDL_Surface* dst, int x, int y)
{
	SDL_Rect dst_rect = {x, y, 0, 0};
	SDL_Surface *src ;
	src = IMG_Load("fundo_p.bmp"); // "borracha"
	SDL_BlitSurface(src, NULL, dst, &dst_rect);
	SDL_FreeSurface(src);
}
void f_introducao(void)
{
	int quit = 0;
	int k=0,i=0,j=256;

	SDL_Surface *img_ufrj;
	SDL_Surface *img_bomber;
	SDL_Rect rect;

	img_ufrj = IMG_Load("int_1.bmp");
	img_bomber = IMG_Load("int_2.bmp");

	rect.x = 0;
	rect.y = 0;

	i=i-VELOC_T;	//Velocidade do FADE
	while(!quit)
    {
        while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				case SDL_KEYDOWN: quit = 1; break;
			}
		}

		i+= VELOC_T;
		if(i<=255)  //aparece em fade a UFRJ
		{
			SDL_FillRect(screen, NULL, SDL_MapRGB (screen->format, 0, 0, 0));
			SDL_SetAlpha(img_ufrj, SDL_SRCALPHA  , i);
			SDL_BlitSurface(img_ufrj,NULL,screen,&rect);
		}

		if(i>=256 && i<=510) //desaparece em fade a UFRJ
		{
			SDL_FillRect(screen, NULL, SDL_MapRGB (screen->format, 0, 0, 0));
			j = j -VELOC_T	;
			SDL_SetAlpha(img_ufrj, SDL_SRCALPHA  , j);
			SDL_BlitSurface(img_ufrj,NULL,screen,&rect);
		}

		if(i>=511 )
		{
			if(i<=(512+256)) //aparece em fade o bomber
			{
				SDL_FillRect(screen, NULL, SDL_MapRGB (screen->format, 0, 0, 0));
				k = k + VELOC_T	;
				SDL_SetAlpha(img_bomber, SDL_SRCALPHA  , k);
			}

			SDL_BlitSurface(img_bomber,NULL,screen,&rect);
		}

		SDL_Flip(screen);
	}

}
int f_menu ()
{
	int quit = 0;
	int pos = 0;
	int start_game = 0;
	int win_aberta = 0;
	int ok_on = 0;
	int salvar = 0;
	int i;
	char lixo[80];

	//char *nome_temp = "arq_temp.txt";
	//FILE *arq_temp;
	//arq_temp = fopen(nome_temp,"w");
	//if(!arq_temp) return;

	SDL_Surface *menup = IMG_Load("menu_principal.png");		//TROCAR para png FALTA TESTAR SE VAI ABRIR !!!!!!!!!!!!!!!!!!!!!!!!!
	
	SDL_Rect rect={0,0,0,0};
	SDL_Rect rcaixa;

	SDL_Surface *menup_j = IMG_Load("menu_principal_j.png");	//FALTA TESTAR SE VAI ABRIR !!!!!!!!!!!!!!!!!!!!!!!!!
	SDL_Surface *menup_r = IMG_Load("menu_principal_r.png");				//FALTA TESTAR SE VAI ABRIR !!!!!!!!!!!!!!!!!!!!!!!!!
	SDL_Surface *menup_s = IMG_Load("menu_principal_s.png");				//FALTA TESTAR SE VAI ABRIR !!!!!!!!!!!!!!!!!!!!!!!!!
	SDL_Surface *caixa1	 = IMG_Load("caixanome1.png");			//FALTA TESTAR SE VAI ABRIR !!!!!!!!!!!!!!!!!!!!!!!!!
	SDL_Surface *caixa2	 = IMG_Load("caixanome2.png");			//FALTA TESTAR SE VAI ABRIR !!!!!!!!!!!!!!!!!!!!!!!!!

	for(i=0;i<10;i++)
	{
		player.nome[i] = '\0';
	}

	if(TTF_Init() == -1)
	{
		printf("Céus, erro ao abrir SDL_ttf: %s\n", TTF_GetError());
	}

	rcaixa.x = CAIXA_X;
	rcaixa.y = CAIXA_Y;

	//my_font = TTF_OpenFont("ARIAL.ttf", FONTSIZE);	//FALTA TESTAR SE VAI ABRIR !!!!!!!!!!!!!!!!!!!!!!!!!
	my_font2 = TTF_OpenFont("zrnic___.ttf", FONTSIZE2);


	SDL_BlitSurface(menup,NULL,screen,&rect);SDL_Flip(screen);

	while(!quit)
    {
        while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				//CONSERTAR O QUITTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT  !!!!
				case SDL_QUIT: quit = 1; break;
				case SDL_MOUSEMOTION:			//VERIFICA A POSICAO DO MOUSE
				case SDL_MOUSEBUTTONDOWN:

					//JOGAR
					if(event.motion.x > BOTAO_X)
					{
						if(event.motion.y > BOTAO_Y && event.motion.y < BOTAO_Y + T_BOTAO && win_aberta!=1)
						{
							SDL_BlitSurface(menup_j,NULL,screen,&rect);SDL_Flip(screen);

							if(event.button.button == SDL_BUTTON_LEFT)
							{
								win_aberta = 1;
							}
						}
						else
					//RECORDES
						if(event.motion.y > BOTAO_Y +T_BOTAO+20 && event.motion.y < BOTAO_Y + 2*T_BOTAO+20 && win_aberta!=1)
						{
							SDL_BlitSurface(menup_r,NULL,screen,&rect);SDL_Flip(screen);

							if(event.button.button == SDL_BUTTON_LEFT)
							{
								show_rec();
							}
						}
						else 
					//SAIR
						if(event.motion.y > BOTAO_Y+ 2*T_BOTAO+30 && event.motion.y < BOTAO_Y + 3*T_BOTAO+40 && win_aberta!=1)
							{
								SDL_BlitSurface(menup_s,NULL,screen,&rect);SDL_Flip(screen);

								if(event.button.button == SDL_BUTTON_LEFT)
								{
									quit = 1;
								}
							}
							else SDL_BlitSurface(menup,NULL,screen,&rect);
					}
					else SDL_BlitSurface(menup,NULL,screen,&rect);
					

					//CAIXA PRA DIGITAR O NOME

					if(win_aberta == 1)
					{
							if(event.motion.x > B_OK_X && event.motion.x < B_OK_X + 125)
							{
								if(event.motion.y > B_OK_Y && event.motion.y < B_OK_Y + 40)
								{
									ok_on = 1;
									if(event.button.button == SDL_BUTTON_LEFT)
									{
										salvar = 1;
										win_aberta = 0; //a janela fecha
										start_game = 1;	//e o jogo comeca
									}
								}
								else ok_on = 0;
							}
							else ok_on = 0;
					}
					break;

				case SDL_KEYUP:
					if(win_aberta == 1 && pos<=7 && pos>=0)
					{
						switch(event.key.keysym.sym)
						{
							case SDLK_a:player.nome[pos] = 'A'; desenha_texto("A", caixa1, INICIO+(pos*50), LINHA); desenha_texto("A", caixa2, INICIO+(pos*50), LINHA); pos++;	break;
							case SDLK_b:player.nome[pos] = 'B'; desenha_texto("B", caixa1, INICIO+(pos*50), LINHA); desenha_texto("B", caixa2, INICIO+(pos*50), LINHA); pos++;	break;
							case SDLK_c:player.nome[pos] = 'C'; desenha_texto("C", caixa1, INICIO+(pos*50), LINHA); desenha_texto("C", caixa2, INICIO+(pos*50), LINHA); pos++;	break;
							case SDLK_d:player.nome[pos] = 'D'; desenha_texto("D", caixa1, INICIO+(pos*50), LINHA); desenha_texto("D", caixa2, INICIO+(pos*50), LINHA); pos++;	break;
							case SDLK_e:player.nome[pos] = 'E'; desenha_texto("E", caixa1, INICIO+(pos*50), LINHA); desenha_texto("E", caixa2, INICIO+(pos*50), LINHA); pos++;	break;
							case SDLK_f:player.nome[pos] = 'F'; desenha_texto("F", caixa1, INICIO+(pos*50), LINHA); desenha_texto("F", caixa2, INICIO+(pos*50), LINHA); pos++;	break;
							case SDLK_g:player.nome[pos] = 'G'; desenha_texto("G", caixa1, INICIO+(pos*50), LINHA); desenha_texto("G", caixa2, INICIO+(pos*50), LINHA); pos++;	break;
							case SDLK_h:player.nome[pos] = 'H'; desenha_texto("H", caixa1, INICIO+(pos*50), LINHA); desenha_texto("H", caixa2, INICIO+(pos*50), LINHA); pos++;	break;
							case SDLK_i:player.nome[pos] = 'I'; desenha_texto("I", caixa1, INICIO+(pos*50), LINHA); desenha_texto("I", caixa2, INICIO+(pos*50), LINHA); pos++;	break;
							case SDLK_j:player.nome[pos] = 'J'; desenha_texto("J", caixa1, INICIO+(pos*50), LINHA); desenha_texto("J", caixa2, INICIO+(pos*50), LINHA); pos++;	break;
							case SDLK_k:player.nome[pos] = 'K'; desenha_texto("K", caixa1, INICIO+(pos*50), LINHA); desenha_texto("K", caixa2, INICIO+(pos*50), LINHA); pos++;	break;
							case SDLK_l:player.nome[pos] = 'L'; desenha_texto("L", caixa1, INICIO+(pos*50), LINHA); desenha_texto("L", caixa2, INICIO+(pos*50), LINHA); pos++;	break;
							case SDLK_m:player.nome[pos] = 'M'; desenha_texto("M", caixa1, INICIO+(pos*50), LINHA); desenha_texto("M", caixa2, INICIO+(pos*50), LINHA); pos++;	break;
							case SDLK_n:player.nome[pos] = 'N'; desenha_texto("N", caixa1, INICIO+(pos*50), LINHA); desenha_texto("N", caixa2, INICIO+(pos*50), LINHA); pos++;	break;
							case SDLK_o:player.nome[pos] = 'O'; desenha_texto("O", caixa1, INICIO+(pos*50), LINHA); desenha_texto("O", caixa2, INICIO+(pos*50), LINHA); pos++;	break;
							case SDLK_p:player.nome[pos] = 'P'; desenha_texto("P", caixa1, INICIO+(pos*50), LINHA); desenha_texto("P", caixa2, INICIO+(pos*50), LINHA); pos++;	break;
							case SDLK_q:player.nome[pos] = 'Q'; desenha_texto("Q", caixa1, INICIO+(pos*50), LINHA); desenha_texto("Q", caixa2, INICIO+(pos*50), LINHA); pos++;	break;
							case SDLK_r:player.nome[pos] = 'R'; desenha_texto("R", caixa1, INICIO+(pos*50), LINHA); desenha_texto("R", caixa2, INICIO+(pos*50), LINHA); pos++;	break;
							case SDLK_s:player.nome[pos] = 'S'; desenha_texto("S", caixa1, INICIO+(pos*50), LINHA); desenha_texto("S", caixa2, INICIO+(pos*50), LINHA); pos++;	break;
							case SDLK_t:player.nome[pos] = 'T'; desenha_texto("T", caixa1, INICIO+(pos*50), LINHA); desenha_texto("T", caixa2, INICIO+(pos*50), LINHA); pos++;	break;
							case SDLK_u:player.nome[pos] = 'U'; desenha_texto("U", caixa1, INICIO+(pos*50), LINHA); desenha_texto("U", caixa2, INICIO+(pos*50), LINHA); pos++;	break;
							case SDLK_v:player.nome[pos] = 'V'; desenha_texto("V", caixa1, INICIO+(pos*50), LINHA); desenha_texto("V", caixa2, INICIO+(pos*50), LINHA); pos++;	break;
							case SDLK_w:player.nome[pos] = 'W'; desenha_texto("W", caixa1, INICIO+(pos*50), LINHA); desenha_texto("W", caixa2, INICIO+(pos*50), LINHA); pos++;	break;
							case SDLK_x:player.nome[pos] = 'X'; desenha_texto("X", caixa1, INICIO+(pos*50), LINHA); desenha_texto("X", caixa2, INICIO+(pos*50), LINHA); pos++;	break;
							case SDLK_y:player.nome[pos] = 'Y'; desenha_texto("Y", caixa1, INICIO+(pos*50), LINHA); desenha_texto("Y", caixa2, INICIO+(pos*50), LINHA); pos++;	break;
							case SDLK_z:player.nome[pos] = 'Z'; desenha_texto("Z", caixa1, INICIO+(pos*50), LINHA); desenha_texto("Z", caixa2, INICIO+(pos*50), LINHA); pos++;	break;

							default: break;
						}
					}
					if(win_aberta == 1 && pos>=1)
					{
						switch(event.key.keysym.sym)
						{
							case SDLK_BACKSPACE:player.nome[pos-1] = '\0';apaga_texto(caixa1,INICIO+((pos-1)*50),LINHA);apaga_texto(caixa2,INICIO+((pos-1)*50),LINHA);pos--;break;
							default: break;
						}
					}
					
			}
		}//while2
		

		if(win_aberta == 1)
		{
			SDL_BlitSurface(caixa1,NULL,screen,&rcaixa);
			if(ok_on == 1)
			{
				SDL_BlitSurface(caixa2,NULL,screen,&rcaixa);
			}
		}
		else
			if(start_game == 1 && salvar == 1)
			{ 
				//fprintf(arq_temp,"%s",player.nome);
				win_aberta = 0;
				f_jogo();
				return -1;
			}

		SDL_Flip(screen);	
	}
		
	TTF_Quit();
	return 0;
}

int f_jogo ()
{
	/*DECLARANDO VARIAVEIS*/ 
	int quit = 0, loop =0, an_morte=0;
	
	int direcionais[4]={0,0,0,0}; //ESTADO DAS TECLAS DIRECIONAIS 1PR1SSIONADAS OU 0SOLTAS
	int n, m; //VARIAVEIS PARA A CRIACAO DO LABIRINTO E DESENVOLVIMENTO DO JOGO
	int i; //VARIAVEIS PARA CRIACAO E MOVIMENTO INIMIGO
	int d_tick; //CONTROLE DO TEMPO (VARIACAO DE DO SDL_GETTICKS EM UMA VOLTA NO MAIN LOOP
	SDL_Surface* tela; //serve para centralizar a screen. tela do labirinto
	SDL_Surface* s_hero = IMG_Load("chara.png"); //imagem do bomberman
	SDL_Surface* s_chipset = IMG_Load("chipset0.png"); //ambiente do labirinto
	
	int lvl =1;
	char vida[10];
	char char_ni[10];
	char tempo_m[10];
	char tempo_s[10];
	char score[10];
	int tempo0_de_jogo;
	SDL_Rect printbomber = {0, 0, TAM_IMGW, TAM_IMGH};
	pos.h = pos.w = 0;
	/*VIDEO*/
	
	s_fire = IMG_Load("fire.png");
	s_bomb = IMG_Load("bomb.png");
	r_bomb.x = r_bomb.y = 0;
	r_bomb.h = r_bomb.w = TAM;
	SDL_SetColorKey(s_fire, SDL_SRCCOLORKEY, SDL_MapRGB(s_fire->format, 0xFF, 0xFF, 0xFF));
	SDL_SetColorKey(s_bomb, SDL_SRCCOLORKEY, SDL_MapRGB(s_bomb->format, 0xFF, 0xFF, 0xFF));
	
	tela = SDL_CreateRGBSurface(SDL_HWSURFACE, SCREEN_W, SCREEN_H, 32,
																		screen->format->Rmask, 
																		screen->format->Gmask, 
																		screen->format->Bmask, 
																		screen->format->Amask);
	srand(time(NULL));
	step=1;
	novo_jogo(&n, &m, &step, direcionais, lvl, s_chipset);
		

	
	/*DEFININDO VAR GLOBAIS :( que nao sofrem alteracao com mudanca de nivel*/
	bomberman.vida = 3;
	bomberman.pts = 0;
	
	//FONT
	if(TTF_Init() == -1)
	{
		printf("Céus, erro ao abrir SDL_ttf: %s\n", TTF_GetError());
	}

	my_font = TTF_OpenFont("ARIAL.ttf", FONTSIZE);
	my_font2 = TTF_OpenFont("zrnic___.ttf", FONTSIZE2);

	//heart
	SDL_Rect rect_heart = {C_INFO_X,C_INFO_Y,0,0};
	SDL_Surface* heart = IMG_Load("heart.png");

	//alcance

	//score

	//time

	SDL_SetColorKey(s_hero, SDL_SRCCOLORKEY, SDL_MapRGB(s_hero->format, 0xFF, 0, 0xFF));
	SDL_SetColorKey(s_chipset, SDL_SRCCOLORKEY, SDL_MapRGB(s_chipset->format, 0xFF, 0, 0xFF));
	
	tempo0_de_jogo = SDL_GetTicks(); //Tempo em que o jogo comecou
	
	while(!quit) //LOOP PRINCIPAL
	{
		C_X = (SCREEN_W - (m *TAM)) /2;
		C_Y = SCREEN_H- n *TAM;
		
		loop= (loop+1)%160;
		/*ADICIONADO PARA CONTROLE DE TEMPO*/
		d_tick = SDL_GetTicks();
		/**/
		
		if(!bomber_morreu) alinhar(&bomberman); //CERTIFICA QUE O OBJ DINAMICO FIQUE ENQUADRADO AA GRADE
		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				case SDL_QUIT: quit = 1; break;
				case SDL_KEYDOWN:
				{
					switch(event.key.keysym.sym)
					{
						case SDLK_UP: if(!bomber_morreu && !fim_do_nivel) direcionais[1] =1; break;
						case SDLK_DOWN:  if(!bomber_morreu && !fim_do_nivel) direcionais[3] =1; break;
						case SDLK_LEFT: if(!bomber_morreu && !fim_do_nivel) direcionais[2] =1; break;
						case SDLK_RIGHT: if(!bomber_morreu && !fim_do_nivel) direcionais[0] =1; break;
						
						case SDLK_RETURN:
						case SDLK_SPACE: if(bomberman.mov == 0  && !fim_do_nivel) ativar_bomba(&b1, mapa, &bomberman); break;
						case SDLK_ESCAPE: tempo0_de_jogo += menu2(screen, &quit); break; /*!!!!!!!!!!!!Alterei a funcao menu2 pra ela poder "mexer" no quit da funcao jogo (na esperanca que isso evite as 12094271 de f_jogos e f_menus)*/
						default: break;
					}
					break;
				}
				case SDL_KEYUP:
				{
					switch(event.key.keysym.sym)
					{
						case SDLK_UP: direcionais[1] =0; break;
						case SDLK_DOWN: direcionais[3] =0; break;
						case SDLK_LEFT: direcionais[2] =0; break;
						case SDLK_RIGHT: direcionais[0] =0; break;
						
						default: break;
					}
					break;
				}
			}
		}
		checa_direcionais(direcionais, &bomberman, &step, mapa);
		SDL_FillRect(tela, NULL, SDL_MapRGB(screen->format, 0, 0, 0)); //LIMPA A TELA DO JOGO
		SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0)); //LIMPA A TELA DA VIDA TEMPO ETC....
		

		//blitar coracao
		SDL_BlitSurface(heart,NULL,screen,&rect_heart);

		//blitar numero de vida 
		//itoa (bomberman.vida,vida,10);		//Depois eu que gasto conhecimento ein? heauhae Me superou com certeza... nem lembrava dessa.	
		sprintf(vida, "%d", bomberman.vida);
		desenha_texto(vida, screen, C_INFO_X+28, C_INFO_Y-15);
				
		//blitar alcance da bomba 
		//SDL_BlitSurface(heart,NULL,screen,&rect_info);

		//blitar inimigos
		//itoa (ni,char_ni,10);
		sprintf(char_ni, "%d", ni);

		desenha_texto(char_ni, screen, C_INFO_X+128, C_INFO_Y-15);

		//blitar score
//		itoa (bomberman.pts,score,10);
		sprintf(score, "%d", bomberman.pts);

		desenha_texto("Score: ", screen, C_INFO_X+212, C_INFO_Y-15);
		desenha_texto(score, screen, C_INFO_X+300, C_INFO_Y-15);
		
		//blitar tempo
//		itoa (((SDL_GetTicks()-tempo0_de_jogo)/1000)/60,tempo_m,10);
		int kk = ((SDL_GetTicks()-tempo0_de_jogo)/1000)/60;
		sprintf(tempo_m, "%d", kk);

		//itoa (((SDL_GetTicks()-tempo0_de_jogo)/1000)%60,tempo_s,10);
		
		kk = ((SDL_GetTicks()-tempo0_de_jogo)/1000)%60;
		sprintf(tempo_s, "%d", kk);

		desenha_texto("Tempo: ", screen, C_INFO_X+490, C_INFO_Y-15);
		desenha_texto(tempo_m, screen, C_INFO_X+607, C_INFO_Y-15);
		desenha_texto(":", screen, C_INFO_X+630, C_INFO_Y-15);
		desenha_texto(tempo_s, screen, C_INFO_X+647, C_INFO_Y-15);

		if(loop%10==0)
		{
			r_bomb.y = TAM*(((r_bomb.y/TAM)+1)%10);
		}
		desenha_lab(tela, mapa, n, m, s_chipset); //DESENHA O LABIRINTO NA TELA
		//SDL_FillRect(screen, &(bomberman.rect), SDL_MapRGB(screen->format, 255, 255, 255)); //DESENHA O BOMBERMAN
		
		/*ADICIONADO PARA INIMIGOS: FAZ OS INIMIGOS ANDAREM NA GRADE*/
		for(i=0; i<ni; i++)
		{
				animacao_andar(&(inimigo[i].r_anima), &inimigo[i]);
				alinhar(&inimigo[i]);
				move_inimigo(&inimigo[i], 1, mapa);
				
				SDL_BlitSurface(inimigo[i].grafico, &(inimigo[i].r_anima), tela, &(inimigo[i].rect));
		}
		verifica_colisao();
		
		/* ADICIONADO PARA ANIMAR MOVIMENTO */
		if(!bomber_morreu && !fim_do_nivel) animacao_andar_hero(&r_hero, &bomberman);
		/**/
		//if(bomber_morreu) animacao_morte(tela, &bomberman, pos, s_hero);
		
		
		/** Adicionado como parte da alteração de blit, para incluir animações de morte ou vitória **/
		if(bomberman.invencibilidade && bomber_morreu)
		{
			bomber_morreu = 0;
		}
		if(bomberman.invencibilidade && SDL_GetTicks()%4 > 1)
		{
		}
		else
		{
			if(bomber_morreu)
			{
				r_hero.w = 32;
				r_hero.x = 4*TAM_IMGW;
				r_hero.y = (an_morte/10)*TAM_IMGH;
				
				printbomber.x = bomberman.rect.x;
				printbomber.y = bomberman.rect.y - (TAM_IMGH - TAM);
				SDL_BlitSurface(s_hero, &r_hero, tela, &printbomber);
				
				if(an_morte>=8*10)
				{
					bomber_morreu = 0;
					an_morte=0;
					r_hero.x =TAM_IMGW;	r_hero.y = TAM_IMGH * 2;
					r_hero.w = TAM_IMGW;
					r_hero.h = TAM_IMGH;
					morre_bomber();
				}
				an_morte++;
			}
			else if(fim_do_nivel)
			{
				r_hero.w = 32;
				r_hero.x = 4*TAM_IMGW + 32;
				r_hero.y = (an_morte/10)*TAM_IMGH;
				
				printbomber.x = bomberman.rect.x;
				printbomber.y = bomberman.rect.y - (TAM_IMGH - TAM);
				SDL_BlitSurface(s_hero, &r_hero, tela, &printbomber);
				
				if(an_morte>=8*10)
				{
					an_morte=0;
					lvl++;
					if(lvl< 3)	novo_jogo(&n, &m, &step, direcionais, lvl, s_chipset);
					else quit =1;
				}
				an_morte++;
			}
			else
			{	
				r_hero.w = TAM_IMGW;
				printbomber.x = bomberman.rect.x + (TAM - TAM_IMGW)/2;
				printbomber.y = bomberman.rect.y - (TAM_IMGH - TAM);
				SDL_BlitSurface(s_hero, &r_hero, tela, &printbomber);
			}
		}
		/**até aqui**/
		
		SDL_BlitSurface(tela,NULL,screen,&pos);
		SDL_Flip(screen); //ATUALIZA A TELA;
		
		/*ADICIONADO PARA CONTROLE DE TEMPO*/
		d_tick = SDL_GetTicks() - d_tick;
		if(d_tick < 1000/FPS) SDL_Delay(1000/FPS - d_tick);

		if(bomber_morreu==-1) quit=1;

	}

	return 3;
}

void animacao_morte(SDL_Surface* tela, Obj_Dinamico* obj, SDL_Rect pos, SDL_Surface* s_hero)
{

}

void novo_jogo(int* n, int* m, int* step, int direcionais[4], int lvl, SDL_Surface* ambiente)
{
	int caixas, i, ai;
	SDL_Surface* ready;
	
	fim_do_nivel =0;
	switch(lvl)
	{
		case 2:
			*n = 13;
			*m = 17;
			caixas = 50;
			ni = 4;
			
			ai = 1;
			ready  = IMG_Load("nivel2.png");
			break;
			
		case 1: 
			*n = 11;
			*m = 11;
			caixas = 18;
			ni = 2;
			
			ai = 0;
			ready  = IMG_Load("nivel1.png");
			break;
		
		default: 
			*n = 15;
			*m = 25;
			caixas = 80;
			ni = 7;
			ai = 2;
			ready = IMG_Load("nivel2.png");
			break;
		
	}
	
	
	define_din(&bomberman, 0, 0, 0, 0, 0, 0, 2, -1); //ZERA OBJETO DINÂMICO:BOMBERMAN
	cria_lab(mapa, *n, *m, caixas); //CRIA ALEATÓRIAMENTE UM LABIRINTO NxM COM caixas CAIXAS DESTRUTIVEIS
	posiciona_dinamico(mapa, *n, *m, &bomberman); //POSICIONA O OBJETO BOMBERMAN NO LABIRINTO CRIADO
	raio = 1;
	
	free(inimigo);
	inimigo = (Obj_Dinamico*) malloc (sizeof(Obj_Dinamico)*ni); //Gastando o conhecimento, hein ?? ehaueaheua
	if(lvl==3)
	{
		for(i=0;i<ni;i++)
		{
			define_din(&inimigo[i], 0, 0, 0, 0, 0, 0, -2, ai);
			posiciona_dinamico(mapa, *n, *m, &inimigo[i]);
			inimigo[i].direcao[(rand()*i)%4] = 1;
		}

	}
	else
		for(i=0;i<ni;i++)
		{
			define_din(&inimigo[i], 0, 0, 0, 0, 0, 0, -2, ai);
			posiciona_dinamico(mapa, *n, *m, &inimigo[i]);
			inimigo[i].direcao[(rand()*i)%4] = 1;
		}
	
	C_X = (SCREEN_W - ((*m) *TAM))/2;
	C_Y = SCREEN_H- ((*n) *TAM);
	
	esconde(mapa, *n, *m, 1, -6); //esconde item 6 (saida)
	
	for(i=0;i<4;i++) direcionais[i]=0;
	
	tm_explosao = 0;
	b1.estado = 0;
	bomber_morreu=0;
	*step = 1;
	
	r_hero.x =TAM_IMGW;	r_hero.y = TAM_IMGH * 2;
	r_hero.w = TAM_IMGW;
	r_hero.h = TAM_IMGH;
	//tela pre jogo
	SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0)); 
	
	
	pos.x = screen->w / 2 - ready->w/2;
	pos.y = screen->h / 2 - ready->h/2;
	
	SDL_SetColorKey(ready, SDL_SRCCOLORKEY, SDL_MapRGB(ready->format, 0xFF, 0, 0xFF));
	SDL_BlitSurface(ready,NULL,screen,&pos);
	SDL_Flip(screen);
	SDL_Delay(1000);
	
	pos.x = C_X;
	pos.y = C_Y;
	
	invencibilidade_temp(2000, &bomberman);
	
}

void animacao_andar_hero(SDL_Rect *r_hero, Obj_Dinamico *dinamico)//para imgs de tam diferente de 
{
	if((*dinamico).walk_control > 0)
	{
		if ((*dinamico).walk_control >=1 && (*dinamico).walk_control <=16) 
		{
			if((*dinamico).i % 2 == 0)	(*r_hero).y = (*r_hero).h  *1;
			else (*r_hero).y = (*r_hero).h *2;
		}
		else (*r_hero).y = (*r_hero).h *0;
		
		/*if (walk_control >=17 && walk_control <=25) (*r_hero).x = TAM*2;
		if (walk_control >= 25 && walk_control <32) (*r_hero).x = TAM* 1;*/
		(*dinamico).walk_control += step;
		if((*dinamico).walk_control >32) (*dinamico).walk_control = 0;
	}
	else (*r_hero).y = (*r_hero).h *0;	
	
	/*if((*dinamico).walk_control > 0)
	{
		if ((*dinamico).walk_control >=1 && (*dinamico).walk_control <=10) 
		{
			if((*dinamico).i % 2 == 0 && (*dinamico).j % 2 == 0)	(*r_hero).y = TAM_IMGH *1;
			else (*r_hero).y = TAM_IMGH *(1+3);
		}
		
		else if ((*dinamico).walk_control >=11 && (*dinamico).walk_control <=20)
		{
			if((*dinamico).i % 2 == 0 && (*dinamico).j % 2 == 0)	(*r_hero).y = TAM_IMGH *2;
			else (*r_hero).y = TAM_IMGH *(2+3);
		}
		else 
		{
			if((*dinamico).i % 2 == 0 && (*dinamico).j % 2 == 0)	(*r_hero).y = TAM_IMGH *0;
			else (*r_hero).y = TAM_IMGH *(0+3);
		}

		(*dinamico).walk_control ++;
		if((*dinamico).walk_control >32) (*dinamico).walk_control = 0;
	}
	else
	{
		if((*dinamico).i % 2 == 0 && (*dinamico).j % 2 == 0)	(*r_hero).y = TAM_IMGH *0;
		else (*r_hero).y = TAM_IMGH *(0+3);
	}*/
}

void recorde (void)
{
	char *cn_recorde = "n_rec.bin";
	char *cp_recorde = "p_rec.bin";
	FILE *arq_rec_pts;
	FILE *arq_rec_nome;
	int tmp_pts,i;
	int size;
	int comp_pts[10];
		
	arq_rec_nome = fopen(cn_recorde,"r+");	if(!arq_rec_nome) printf("Erro ao abrir o arquivo record"); //testando
	arq_rec_pts  = fopen(cp_recorde,"r+");	if(!arq_rec_pts) printf("Erro ao abrir o arquivo record"); //testando

	player.pontos = bomberman.pts;

	fseek(arq_rec_pts,0,SEEK_END);
	size = ftell(arq_rec_pts);

	fseek(arq_rec_pts,0,SEEK_SET);
	fseek(arq_rec_nome,0,SEEK_SET);

	for(i=0;i<10;i++)
	{
		fread(&tmp_pts, sizeof(int), 1,arq_rec_pts);
		fseek(arq_rec_pts,(-1)*sizeof(int),SEEK_CUR);

		if(size == 10*sizeof(int))		// Se o score tiver lotado!!!
		{
			if(tmp_pts < player.pontos) //ele verifica se tem algum menor e substitue
			{
				
				fwrite(&player.pontos, sizeof(int),1,arq_rec_pts);
				//fseek(arq_rec_pts,(-1)*sizeof(int),SEEK_CUR);
				fwrite(player.nome, sizeof(char),10,arq_rec_nome);
				//fseek(arq_rec_nome,(-10)*sizeof(char),SEEK_CUR);
				i = 10;
			}
		}
		else // Se ainda tiver espaco no score! ele coloca no ultimo mesmo.
		{
			fseek(arq_rec_pts,0,SEEK_END);
			fseek(arq_rec_nome,0,SEEK_END);

			fwrite(&player.pontos,sizeof(int),1,arq_rec_pts);
			//fseek(arq_rec_pts,(-1)*sizeof(int),SEEK_CUR);
			fwrite(player.nome,sizeof(char),10,arq_rec_nome);
			//fseek(arq_rec_nome,(-10)*sizeof(char),SEEK_CUR);
			i = 10;
		}

		if(i != 10)
		{
			fseek(arq_rec_pts,1*sizeof(int),SEEK_CUR);
			fseek(arq_rec_nome,10*sizeof(char),SEEK_CUR);
		}
	}

	fclose(arq_rec_pts);
	fclose(arq_rec_nome);
	//Odenar os arquivo de modo decrescente:

}
void show_rec (void)
{
	int quit = 0;

	char *cn_recorde = "n_rec.bin";
	char *cp_recorde = "p_rec.bin";
	FILE *arq_rec_pts;
	FILE *arq_rec_nome;

	SDL_Rect rect={0,0,0,0};
	int i,k; 
	int enter = 35;
	char nome_tmp[10];
	char pts_tmp[10];
	int pts;
	
	SDL_Surface *rec_fnd = IMG_Load("lista_rec.png");
	SDL_Surface *rec_fnd_v = IMG_Load("lista_rec_v.png");

	arq_rec_nome = fopen(cn_recorde,"r+");	if(!arq_rec_nome) printf("Erro ao abrir o arquivo record"); //testando
	arq_rec_pts  = fopen(cp_recorde,"r+");	if(!arq_rec_pts) printf("Erro ao abrir o arquivo record"); //testando

	SDL_BlitSurface(rec_fnd,NULL,screen,&rect);
	//SDL_Flip(screen);

	while(!quit) 
	{
		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				case SDL_QUIT: quit = 1; break;
				case SDL_MOUSEMOTION:
				case SDL_MOUSEBUTTONDOWN:
					if(event.motion.x > 650 )
					{
						if(event.motion.y > 530)
						{
							SDL_BlitSurface(rec_fnd_v,NULL,screen,&rect);
							if(event.button.button == SDL_BUTTON_LEFT)
							{
								quit = 1;
							}
						}else SDL_BlitSurface(rec_fnd,NULL,screen,&rect);
					}else SDL_BlitSurface(rec_fnd,NULL,screen,&rect);
						
				break;
			}
			fseek(arq_rec_pts,0,SEEK_SET);
			fseek(arq_rec_nome,0,SEEK_SET);

			for(i=1;i<11;i++)
			{
				for(k=0;k<10;k++)
					pts_tmp[i] = '\0';

				fread(nome_tmp, sizeof(char), 10, arq_rec_nome);
				desenha_texto(nome_tmp, screen, 100, 100+i*35);

				fread(&pts, sizeof(int), 1, arq_rec_pts);
				//itoa(pts,pts_tmp,10);
				sprintf(pts_tmp, "%d", pts);
				desenha_texto(pts_tmp, screen, 100+200, 100+i*35);
			}

			SDL_Flip(screen);
		}
	}

	fclose(arq_rec_pts);
	fclose(arq_rec_nome);

}

