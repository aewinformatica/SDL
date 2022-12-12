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
	// Qual conjunto de sprites está usando??
	unsigned int azulejo;
	// As coordenadas na tela ocupadas pelo elemento
	int x,y;
	// A largura e altura do elemento
	int larg, alt;
	// As coordenadas de referência dentro do sprite
	int xref, yref;
	
}Elemento;

// Estrutura para armazenar as informações lógicas sobre o mapa
typedef struct
{
	// A largura e altura do mapa
	int largura, altura;
	// O tamanho do bloco
	int tamBloco;
	// O número de camadas
	int numCamadas;
	// As dimensões máximas do mapa
	int xmapa, ymapa;
	// O x e y da origem baseados no jogador
	int xOrig, yOrig;
} InfoMapa;
	

// --------------- Variáveis Globais --------------------

// Indica se deve terminar o programa ou não
bool sai=false;
bool esquerda=false, direita=false, cima=false, baixo=false, pula=false;


// Polling das entradas
void entrada();
// Temporiza o jogo para rodar a 50 quadros por segundo
void temporiza();

// Funções específicas da fase do jogo
int fase(Chien2DMappy *mapa, unsigned int tileset, Elemento *jogador);
// Cria uma estrutura de informações do mapa a partir de um mapa
InfoMapa* criaInfoMapa(Chien2DMappy *mapa);

// ------------ Funções do jogador -----------------

// Função para atualizar o jogador na tela
void atualiza_jogador(Elemento *jogador, InfoMapa *iMapa);
// Função para desenhar o jogador na tela
void desenha_jogador(Chien2DLite *video, Elemento *jogador, InfoMapa *iMapa);


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
	// Inicializa e pega o tempo atual (só faz isso a primeira vez)
	static Uint32 tempoAnterior=0;

	// -- Espera 16ms entre cada quadro --
	
	// Variável para o tempo atual
	int espera=16-SDL_GetTicks()+tempoAnterior;
	if(espera > 0)
		SDL_Delay(espera);
	tempoAnterior=SDL_GetTicks();
	
}


int fase(Chien2DMappy *mapa, unsigned int tileset, Elemento *jogador)
{
	// Recupera o ponteiro para o sistema de vídeo
	Chien2DLite *video = Chien2DLite::pegaInstancia();
	// Cria as informações do mapa
	InfoMapa *iMapa = criaInfoMapa(mapa);

	// Inicia as informações do jogador e do mapa
	atualiza_jogador(jogador, iMapa);
    // Loop principal
    while(!sai) 
    {
		
               // Faz o poling da entrada
               entrada();
               // Limpa a tela
               video->limpaTela();
               // desenha a tela. Você deve colocar AQUI o código do redesenho
               mapa->desenhaCamadaMapa(tileset, 0, iMapa->xOrig, iMapa->yOrig);
               // DEsenha o jogador
               desenha_jogador(video, jogador, iMapa);
               // Faz a troca de buffers (double buffer)
               video->sincroniza();              
               // Atualiza a lógica
               atualiza_jogador(jogador, iMapa);
				// Espera passar o tempo para desenhar o quadro
				temporiza();
               
    }
    // Elimina as informações do mapa
    delete iMapa;
}

// Cria uma estrutura de informações do mapa a partir de um mapa
InfoMapa* criaInfoMapa(Chien2DMappy *mapa)
{
	// Cria a estrutura com as informações do mapa
 	InfoMapa *info = new InfoMapa;
 	// Testa se alocou corretamente
 	if(info == 0)
 		return 0;
    // Determina as dimensões do mapa
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

// ------------ Funções do jogador -----------------

// Função para atualizar o jogador na tela
void atualiza_jogador(Elemento *jogador, InfoMapa *iMapa)
{
	// Atualiza a posição do jogador baseado no teclado
	if(esquerda)
		jogador->x-=3;
	if(direita)
		jogador->x+=3;
	if(cima)
		jogador->y-=3;
	if(baixo)
		jogador->y+=3;
	// Verifica a consistência da posição do jogador (não deixa sair fora do mapa)
	if(jogador->x<0)
		jogador->x=0;
	else if(jogador->x > iMapa->xmapa - jogador->larg)
		jogador->x = iMapa->xmapa - jogador->larg;
		
	if(jogador->y<0)
		jogador->y=0;
	else if(jogador->y > iMapa->ymapa - jogador->alt)
		jogador->y = iMapa->ymapa - jogador->alt;
		
	// Atualiza a origem do mapa em relação ao jogador
	iMapa->xOrig = jogador->x - (jogador->larg)/2 - 320;
	iMapa->yOrig = jogador->y - (jogador->alt)/2 - 240;	
	
	// Verifica consistência do mapa
	if(iMapa->xOrig < 0)
		iMapa->xOrig = 0;
	else if(iMapa->xOrig > iMapa->xmapa-640)
		iMapa->xOrig = iMapa->xmapa-640;
	if(iMapa->yOrig < 0)
		iMapa->yOrig = 0;
	else if(iMapa->yOrig > iMapa->ymapa-480)
		iMapa->yOrig = iMapa->ymapa-480;
		
}

// Função para desenhar o jogador na tela
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



int main(int argc, char *argv[])
{  
    // Inicia o vídeo
    Chien2DLite *video = Chien2DLite::pegaInstancia();
    //video->inicia(640, 480, Chien2DLite::telaCheia, true, "Exemplo 10 - Lógica");
    video->inicia(640, 480, Chien2DLite::janela, true, "Exemplo 10 - Lógica");

	// ---- Prepara o jogo ---- 

	// ---------- Cria o jogador -------------
	// Cria a estrutura
	Elemento jogador;
	// Carrega o azulejo
	jogador.azulejo = video->carregaAzulejo("personagem_darkphoenix.png","personagem_darkphoenix.png", Chien2DLite::azulejo32);
	// Prenche a posição
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
    // Finaliza a instância de vídeo
    video->removeInstancia();
}
