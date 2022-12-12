//O Cabeçalho 
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>

//Atributos da Tela
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;
 
//As superfícies
SDL_Surface *imagem = NULL;
SDL_Surface *tela = NULL;

//A estrutura que usaremos para capturarmos os eventos
SDL_Event evento;

SDL_Surface *carregaImagem( std::string imagem ) 
{ 
  //Superfície que armazena temporariamente a imagem 
  SDL_Surface* imagemCarregada = NULL;

  //Superfície que retorna a imagem otimizada 
  SDL_Surface* imagemOtimizada = NULL;
  
  //Carrega a imagem
  imagemCarregada = IMG_Load( imagem.c_str() );

  //Verifica se tudo deu certinho
  if( imagemCarregada != NULL ) 
  {
      //Cria a imagem otimizada
      imagemOtimizada = SDL_DisplayFormat( imagemCarregada); 
	
	  //Libera a imagem carregada
	  SDL_FreeSurface( imagemCarregada ); 
   }
      //Retorna a imagem otimizada
      return imagemOtimizada;
}

void aplicaSuperficie( int x, int y, SDL_Surface* fonte, SDL_Surface* destino ) 
{ 
     //Cria um retangulo para a superficie
     SDL_Rect retangulo; 
     
     //Dá as coordenadas para o retangulo
     retangulo.x = x;
     retangulo.y = y;

     //encaixa a "fonte" dentro do "destino" através do retangulo
     SDL_BlitSurface( fonte, NULL, destino, &retangulo );
}

bool inicia() 
{ 
  //Inicia os subsistemas da SDL
  if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 ) 
  { 
      return false;
  } 
  
  //Setando a tela 
  tela = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE ); 
  
  //Verifica se existe algum erro na tela 
  if( tela == NULL ) 
  { 
      return false; 
  } 
  
  //Setando o caption da janela
  SDL_WM_SetCaption( "Tutorial SDL - Eventos", NULL ); 
  
  //Se tudo deu certo
  return true; 
}

bool carrega_arquivos(std::string arquivo)
{ 
     //Carrega a imagem
     imagem = carregaImagem( arquivo.c_str() ); 
     
     //Verifica se existe algum erro no carregamento da imagem
     if( imagem == NULL ) 
     { 
         return false; 
     } 
     
     //se tudo der certo
     return true; 
}

void limpa()
{ 
     //Libera a imagem
     SDL_FreeSurface( imagem ); 
}

void sair()
{     
     //Fecha a SDL
     SDL_Quit(); 
}

int main( int argc, char* args[] )
{
    //Variável necessária para saber se o usuário fechou a janela
    bool quit = false;
    
    //Inicia 
    if( inicia() == false ) 
    { 
        return 1; 
    } 
    
    //Carrega os arquivos 
    if( carrega_arquivos("x.jpg") == false ) 
    { 
        return 1; 
    }
    
    //Aplicando as superfícies na tela
    aplicaSuperficie( 0, 0, imagem, tela ); 
    
    //Atualiza a tela
    if( SDL_Flip( tela ) == -1 ) 
    { 
        return 1; 
    }
    
    //Enquanto o usuário não fechar o programa
    while( quit == false ) 
    {
        //Quando ocorrer um evento
        while( SDL_PollEvent( &evento ) ) 
        {
           //verificando a tecla
           if( evento.type == SDL_KEYDOWN )
           {
              switch( evento.key.keysym.sym ) 
              { 
                 case SDLK_UP:
                      limpa();
                      carrega_arquivos("up.jpg");
                      break; 
                 
                 case SDLK_DOWN: 
                      limpa();
                      carrega_arquivos("down.jpg");
                      break; 
                 
                 case SDLK_LEFT: 
                      limpa();
                      carrega_arquivos("left.jpg");
                      break; 
                 
                 case SDLK_RIGHT: 
                      limpa();
                      carrega_arquivos("right.jpg");
                      break; 
                 
                 default:
                      limpa();
                      carrega_arquivos("x.jpg");
                      break;         
              }

              //Aplicando as superfícies na tela
              aplicaSuperficie( 0, 0, imagem, tela ); 
              
              //dá um refresh na tela                  
              SDL_Flip( tela );
           }
           
           //se o usuário apertou o X da janela
           if( evento.type == SDL_QUIT ) 
           { 
               //Fecha o programa
               quit = true;
           }
        }
    }
    
    //Libera a superficie e fecha a SDL
    limpa();
    sair(); 
    return 0;
}
