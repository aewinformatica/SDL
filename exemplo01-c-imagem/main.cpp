#include <cstdlib>
#include <iostream>

#include "chien2dlite.h"
#include "chien2dmappy.h"

using namespace std;

// Indica se deve terminar o programa ou não
bool sai=false;
// Polling das entradas
void entrada();

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


int main(int argc, char *argv[])
{  
    // Inicia o vídeo
    Chien2DLite *video = Chien2DLite::pegaInstancia();
    video->inicia(640, 480, Chien2DLite::janela, true, "Exemplo 01 - Imagem");
    
    // Loop principal
    while(!sai) 
    {
               // Faz o polling da entrada
               entrada();
               // Limpa a tela
               video->limpaTela();
               // desenha a tela. Você deve colocar AQUI o código do redesenho

               // Faz a troca de buffers (double buffer)
               video->sincroniza();
               
               // Aqui vai a lógica para atualizar os elementos (se tiver)               
    }
    
    // Fecha a janela
    video->encerra();
    // Finaliza a instância de vídeo
    Chien2DLite::removeInstancia();
}
