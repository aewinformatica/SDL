//////////////////////////////////////////////////////
//
//   Exemplo de jogo plataforma simples.
//
//   Autor: Paulo V. W. Radtke - pvwradtke@gmail.com
//
//   Direitos reservados - 2006 - Exclusivo para uso educacional.
//
//////////////////////////////////////////////////////

#include <cstdlib>
#include <iostream>

#include "chien2dlite.h"
#include "chien2dmappy.h"

using namespace std;

// Estrutura para representar um elemento, como o jogador
typedef struct
{
	// Qual conjunto de sprites est? usando??
	unsigned int azulejo;
	// As coordenadas na tela ocupadas pelo elemento
	int x,y;
	// A largura e altura do elemento
	int larg, alt;
	// As coordenadas de refer?ncia dentro do sprite
	int xref, yref;
	
}Elemento;

// Estrutura para armazenar as informa??es l?gicas sobre o mapa
typedef struct
{
	// A largura e altura do mapa
	int largura, altura;
	// O tamanho do bloco
	int tamBloco;
	// O n?mero de camadas
	int numCamadas;
	// As dimens?es m?ximas do mapa
	int xmapa, ymapa;
	// O x e y da origem baseados no jogador
	int xOrig, yOrig;
} InfoMapa;
	

// --------------- Vari?veis Globais --------------------

// Indica se deve terminar o programa ou n?o
bool sai=false;
bool esquerda=false, direita=false, cima=false, baixo=false, pula=false;


// Polling das entradas
void entrada();
// Temporiza o jogo para rodar a 50 quadros por segundo
void temporiza();

// Fun??es espec?ficas da fase do jogo
int fase(Chien2DMappy *mapa, unsigned int tileset, Elemento *jogador);
// Cria uma estrutura de informa??es do mapa a partir de um mapa
InfoMapa* criaInfoMapa(Chien2DMappy *mapa);

// ------------ Fun??es do jogador -----------------

// Fun??o para atualizar o jogador na tela
void atualiza_jogador(Elemento *jogador, InfoMapa *iMapa, short int *blocos);
// Fun??o para desenhar o jogador na tela
void desenha_jogador(Chien2DLite *video, Elemento *jogador, InfoMapa *iMapa);

// --------------- Fun??es gerais para elementos -----------------------
// Fun??o para ajustar a posi??o do elemento baseado na colis?o do mesmo com cen?rio
int colide_elemento_eixo_X(Elemento *personagem, InfoMapa *iMapa, short int *blocos, int dx);
int colide_elemento_eixo_Y(Elemento *personagem, InfoMapa *iMapa, short int *blocos, int dy);



// Poling das entradas. TRata todos os eventos relacionados a dispositivos de
// entrada do sistema
void entrada()
{
    // A estrutura que recebe os eventos
     SDL_Event event;
     // Enquanto houverem eventos a processar ...
     while(SDL_PollEvent( &event ))
     {
         // TRata de acordo com o tipo de evento
         switch( event.type )
         {
         	  case SDL_QUIT:
            		sai=true;
              		break;
                  
              case SDL_KEYDOWN:
                        switch(event.key.keysym.sym)
                        {
                                  // Pressionou ESC?
                                  case SDLK_ESCAPE:
                                  	sai=true;
                                  	break;
                                case SDLK_UP:
									cima=true;
									break;
									
								case SDLK_DOWN:
									baixo=true;
									break;
								
								case SDLK_LEFT:
									esquerda=true;
									break;
									
								case SDLK_RIGHT:
									direita=true;
									break;
                                                                	
                                  default:                              	
                                  	break;
                        }
                        break;

              case SDL_KEYUP:
                        switch(event.key.keysym.sym)
                        {
                                case SDLK_UP:
									cima=false;
									break;
									
								case SDLK_DOWN:
									baixo=false;
									break;
								
								case SDLK_LEFT:
									esquerda=false;
									break;
									
								case SDLK_RIGHT:
									direita=false;
									break;
                                                                	
                                  default:                              	
                                  	break;
                        }
                        break;

                                            
              default:
                        break;
        }
     }
}

// Temporiza o jogo para rodar a 60 quadros por segundo
void temporiza()
{
	// Inicializa e pega o tempo atual (s? faz isso a primeira vez)
	static Uint32 tempoAnterior=0;

	// -- Espera 16ms entre cada quadro --
	
	// Vari?vel para o tempo atual
	int espera=16-SDL_GetTicks()+tempoAnterior;
	if(espera > 0)
		SDL_Delay(espera);
	tempoAnterior=SDL_GetTicks();
	
}


int fase(Chien2DMappy *mapa, unsigned int tileset, Elemento *jogador)
{
	// Recupera o ponteiro para o sistema de v?deo
	Chien2DLite *video = Chien2DLite::pegaInstancia();
	// Cria as informa??es do mapa
	InfoMapa *iMapa = criaInfoMapa(mapa);

	// monta o mapa de blocos l?gicos do mapa
	short int *blocos = new short int [iMapa->altura*iMapa->largura];
	mapa->copiaCamadaMapa(0, blocos);
	// coloca true nos blocos que tem colis?o (1 e 2) e false nos que n?o tem
	for(int linha=0;linha<iMapa->altura;linha++)
		for(int coluna=0;coluna<iMapa->largura;coluna++)
			if(blocos[linha*iMapa->largura+coluna] == 1 || blocos[linha*iMapa->largura+coluna] == 2)
				blocos[linha*iMapa->largura+coluna] = true;
			else
				blocos[linha*iMapa->largura+coluna] = false;

	// Inicia as informa??es do jogador e do mapa
	atualiza_jogador(jogador, iMapa, blocos);
    // Loop principal
    while(!sai) 
    {
		
               // Faz o poling da entrada
               entrada();
               // Limpa a tela
               video->limpaTela();
               // desenha a tela. Voc? deve colocar AQUI o c?digo do redesenho
               mapa->desenhaCamadaMapa(tileset, 0, iMapa->xOrig, iMapa->yOrig);
               // DEsenha o jogador
               desenha_jogador(video, jogador, iMapa);
               // Faz a troca de buffers (double buffer)
               video->sincroniza();              
               // Atualiza a l?gica
               atualiza_jogador(jogador, iMapa, blocos);
				// Espera passar o tempo para desenhar o quadro
				temporiza();               
    }
    // Elimina as informa??es do mapa
    delete iMapa;
    // Elimina os blocos l?gicos
    delete blocos;
}

// Cria uma estrutura de informa??es do mapa a partir de um mapa
InfoMapa* criaInfoMapa(Chien2DMappy *mapa)
{
	// Cria a estrutura com as informa??es do mapa
 	InfoMapa *info = new InfoMapa;
 	// Testa se alocou corretamente
 	if(info == 0)
 		return 0;
    // Determina as dimens?es do mapa
    int largura, altura;
    int tamBloco, camadas;
    mapa->dimensoesMapa(&largura, &altura, &tamBloco, &camadas);
    // Preenche os dados da estrutura
	info->altura = altura;
	info->largura = largura;
	info->numCamadas = camadas;
	info->tamBloco = tamBloco;
    info->xmapa=largura*tamBloco;
    info->ymapa=altura*tamBloco;
    return info;
}	

// ------------ Fun??es do jogador -----------------

// Fun??o para atualizar o jogador na tela
void atualiza_jogador(Elemento *jogador, InfoMapa *iMapa, short int *blocos)
{
	// Calcula o movimento do jogados
	int dx, dy;
	if(esquerda)
		dx=-4;
	else if(direita)
		dx=4;
	else
		dx=0;
	if(cima)
		dy=-4;
	else if(baixo)
		dy=4;
	else
		dy=0;

	// Verifica se colide com este deslocamento
	if(dx!=0)
		dx=colide_elemento_eixo_X(jogador, iMapa, blocos, dx);
	if(dy!=0)
		dy=colide_elemento_eixo_Y(jogador, iMapa, blocos, dy);

	// Atualiza a posi??o x e y.
	jogador->x += dx;
	jogador->y += dy;

	// Verifica a consist?ncia da posi??o do jogador (n?o deixa sair fora do mapa)
	if(jogador->x<0)
		jogador->x=0;
	else if(jogador->x > iMapa->xmapa - jogador->larg)
		jogador->x = iMapa->xmapa - jogador->larg;
		
	if(jogador->y<0)
		jogador->y=0;
	else if(jogador->y > iMapa->ymapa - jogador->alt)
		jogador->y = iMapa->ymapa - jogador->alt;
		

	// Atualiza a origem do mapa em rela??o ao jogador
	iMapa->xOrig = jogador->x - (jogador->larg)/2 - 320;
	iMapa->yOrig = jogador->y - (jogador->alt)/2 - 240;	
	
	// Verifica consist?ncia do mapa
	if(iMapa->xOrig < 0)
		iMapa->xOrig = 0;
	else if(iMapa->xOrig > iMapa->xmapa-640)
		iMapa->xOrig = iMapa->xmapa-640;
	if(iMapa->yOrig < 0)
		iMapa->yOrig = 0;
	else if(iMapa->yOrig > iMapa->ymapa-480)
		iMapa->yOrig = iMapa->ymapa-480;
		
}

// Fun??o para desenhar o jogador na tela
void desenha_jogador(Chien2DLite *video, Elemento *jogador, InfoMapa *iMapa)
{
	// Desenha, por enquanto, os sprite 0 e 8 (primeiro quadro)

	// Determina a coordenada x,y real a desenhar
	int x=jogador->x - jogador->xref - iMapa->xOrig;
	int y=jogador->y - jogador->yref - iMapa->yOrig;	
	// Desenha o sprite
	video->desenhaAzulejo(jogador->azulejo, 0, x, y);
	video->desenhaAzulejo(jogador->azulejo, 8, x, y+32);
}

// Fun??o para ajustar a posi??o do elemento baseado na colis?o do mesmo com cen?rio
int colide_elemento_eixo_X(Elemento *personagem, InfoMapa *iMapa, short int *blocos, int dx)
{
	//    Esta fun??o corrige a posi??o de um elemento, baseado em quantos pontos eles est?o se sobrepondo.
	//    Deve-se notar que esta fun??o n?o ? ideal, pois ignora a dire??o em que o elemento se desloca para
	// realizar o teste, nem mesmo otimiza blocos comuns de cen?rio que poderiam ser testados mais
	// eficientemente.	Outra coisa que a fun??o n?o faz ? testar elementos mais complexos que
	// ret?ngulos, algo mandat?rio em jogos mais complexos.
		// Intervalo de blocos em que verificamos a colis?o
		int topo, baixo, esquerda, direita;
		// O deslocamento local
		int dl=dx;
		// Qual o pr?ximo valor de x
		int xl = personagem->x+dx;
		// Calcula o extremo esquerdo
		topo = personagem->y/iMapa->tamBloco;
		esquerda = (xl)/iMapa->tamBloco;
		// Calcula o extremo direito
		baixo = (personagem->y+personagem->alt-1)/iMapa->tamBloco;
		direita = (xl+personagem->larg-1)/iMapa->tamBloco;
		
		// A diferen?a entre personagem e bloco		
		int difx=0;
		// Para cada bloco no intervalo
		for(int lin=topo;lin<=baixo;lin++)
			for(int col=esquerda;col<=direita;col++)
			{
				// O bloco ? v?lido para colis?o?
				// Ele ? SE:
				//			- Ele est? dentro do mapa
				//		- Se ele ? true (ele pode ser colidido)
				// Testa ent?o se est? dentro do mapa
				if(lin< 0 || lin >= iMapa->altura || col < 0 || col > iMapa->largura)
					continue;
				// Testa se ele ? v?lido
				if(blocos[iMapa->largura*lin + col])
				{
					// Se for true, testa a colis?o no eixo x
					difx = xl - col*iMapa->tamBloco;
					// O valor de difx tem que ser convertido para o quanto o
					// elemento entrou dentro do bloco
					
					// Se o jogador est? ? esquerda, tem que ajustar pelo largura
					// do elemento
					if(difx < 0)
						difx = -(personagem->larg + difx);
					// Caso contr?rio, est? mais a esquerda e ajusta pela 
					// largura do bloco
					else
						difx = iMapa->tamBloco - difx;
					dl=dx+difx;
					
				}
			}
		
		return dl;
	
}

// Fun??o para ajustar a posi??o do elemento baseado na colis?o do mesmo com cen?rio
int colide_elemento_eixo_Y(Elemento *personagem, InfoMapa *iMapa, short int *blocos, int dy)
{
	//    Esta fun??o corrige a posi??o de um elemento, baseado em quantos pontos eles est?o se sobrepondo.
	//    Deve-se notar que esta fun??o n?o ? ideal, pois ignora a dire??o em que o elemento se desloca para
	// realizar o teste, nem mesmo otimiza blocos comuns de cen?rio que poderiam ser testados mais
	// eficientemente.	Outra coisa que a fun??o n?o faz ? testar elementos mais complexos que
	// ret?ngulos, algo mandat?rio em jogos mais complexos.
		// Intervalo de blocos em que verificamos a colis?o
		int topo, baixo, esquerda, direita;
		// O deslocamento local
		int dl=dy;
		// Qual o pr?ximo valor de x
		int yl = personagem->y+dy;
		// Calcula o extremo esquerdo
		topo = yl/iMapa->tamBloco;
		esquerda = personagem->x/iMapa->tamBloco;
		// Calcula o extremo direito
		baixo = (yl+personagem->alt-1)/iMapa->tamBloco;
		direita = (personagem->x+personagem->larg-1)/iMapa->tamBloco;
		
		// A diferen?a entre personagem e bloco		
		int dify=0;
		// Para cada bloco no intervalo
		for(int lin=topo;lin<=baixo;lin++)
			for(int col=esquerda;col<=direita;col++)
			{
				// O bloco ? v?lido para colis?o?
				// Ele ? SE:
				//			- Ele est? dentro do mapa
				//		- Se ele ? true (ele pode ser colidido)
				// Testa ent?o se est? dentro do mapa
				if(lin< 0 || lin >= iMapa->altura || col < 0 || col > iMapa->largura)
					continue;
				// Testa se ele ? v?lido
				if(blocos[iMapa->largura*lin + col])
				{
					// Se for true, testa a colis?o no eixo x
					dify = yl - lin*iMapa->tamBloco;
					// O valor de difx tem que ser convertido para o quanto o
					// elemento entrou dentro do bloco
					
					// Se o jogador est? ? esquerda, tem que ajustar pelo largura
					// do elemento
					if(dify < 0)
						dify = -(personagem->alt + dify);
					// Caso contr?rio, est? mais a esquerda e ajusta pela 
					// largura do bloco
					else
						dify = iMapa->tamBloco - dify;
					dl=dy+dify;
					
				}
			}
		
		return dl;
	
}


int main(int argc, char *argv[])
{  
    // Inicia o v?deo
    Chien2DLite *video = Chien2DLite::pegaInstancia();
    //video->inicia(640, 480, Chien2DLite::telaCheia, true, "Exemplo 10 - L?gica");
    video->inicia(640, 480, Chien2DLite::janela, true, "Exemplo 10 - L?gica");

	// ---- Prepara o jogo ---- 

	// ---------- Cria o jogador -------------
	// Cria a estrutura
	Elemento jogador;
	// Carrega o azulejo
	jogador.azulejo = video->carregaAzulejo("personagem_darkphoenix.png","personagem_darkphoenix.png", Chien2DLite::azulejo32);
	// Prenche a posi??o
	jogador.x = 306; jogador.y = 700;
	// Preenche o tamanho do jogador
	jogador.larg = 28; jogador.alt = 40;
	jogador.xref = 2;
	jogador.yref = 24;
	
    // Carrega o tileset
    unsigned int tileset = video->carregaAzulejo( "plataforma.png", "Tileset do cenario", Chien2DLite::azulejo32);
    // Carrega o mapa da fase
    Chien2DMappy *mapa = new Chien2DMappy();
    mapa->carregaMapa("plataforma.FMP");


	// Roda a fase do jogo
	fase(mapa, tileset, &jogador);
    
    // Elimina o mapa
    delete mapa;
    // Elimina o tileset
    video->removeAzulejo(tileset);
    // Fecha a janela
    video->encerra();
    // Finaliza a inst?ncia de v?deo
    video->removeInstancia();
}
