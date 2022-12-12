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

// Indica se deve terminar o programa ou não
bool sai=false;
// Polling das entradas
void entrada();
// Temporiza o jogo para rodar a 50 quadros por segundo
void temporiza();

// Funções específicas da fase do jogo
int fase(Chien2DMappy *mapa, unsigned int tileset);

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
                                                                	
                                  default:                              	
                                  	break;
                        }
                        break;
                                            
              default:
                        break;
        }
     }
}

// Temporiza o jogo para rodar a 50 quadros por segundo
void temporiza()
{
	// Inicializa e pega o tempo atual (só faz isso a primeira vez)
	static Uint32 tempoAnterior=0;

	// -- Espera 20ms entre cada quadro --
	
	// Variável para o tempo atual
	int espera=20-SDL_GetTicks()+tempoAnterior;
	if(espera > 0)
		SDL_Delay(espera);
	tempoAnterior=SDL_GetTicks();
	
}


int fase(Chien2DMappy *mapa, unsigned int tileset)
{
	// Recupera o ponteiro para o sistema de vídeo
	Chien2DLite *video = Chien2DLite::pegaInstancia();
	
    // Determina as dimensões do mapa
    int largura, altura;
    int tamBloco, camadas;
    mapa->dimensoesMapa(&largura, &altura, &tamBloco, &camadas);
    int maxX=largura*tamBloco - 640;
    int maxY=altura*tamBloco - 480;
    // O eixo x para animar o mapa
	int x=0;
    // Loop principal
    while(!sai) 
    {
		
               // Faz o poling da entrada
               entrada();
               // Limpa a tela
               video->limpaTela();
               // desenha a tela. Você deve colocar AQUI o código do redesenho
               mapa->desenhaCamadaMapa(tileset, 0, x, 480);
               // Faz a troca de buffers (double buffer)
               video->sincroniza();              
				// Atualiza a posição do eixo x
               if(++x> maxX)
               	x=0;
               
				// Espera passar o tempo para desenhar o quadro
				temporiza();
               
    }
}


int main(int argc, char *argv[])
{  
    // Inicia o vídeo
    Chien2DLite *video = Chien2DLite::pegaInstancia();
    video->inicia(640, 480, Chien2DLite::janela, true, "Exemplo 10 - Lógica");

	// ---- Prepara o jogo ---- 
	
    // Carrega o tileset
    unsigned int tileset = video->carregaAzulejo( "plataforma.png", "Tileset do cenario", Chien2DLite::azulejo32);
    // Carrega o mapa da fase
    Chien2DMappy *mapa = new Chien2DMappy();
    mapa->carregaMapa("plataforma.FMP");

	// Roda a fase do jogo
	fase(mapa, tileset);
    
    // Elimina o mapa
    delete mapa;
    // Fecha a janela
    video->encerra();
    // Finaliza a instância de vídeo
    video->removeInstancia();
}
