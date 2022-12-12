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
	// A velocidade inicial de queda do elemento
	int vini;
	// O tempo passado (em quadros) desde o início da queda
	int tqueda;	
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
void atualiza_jogador(Elemento *jogador, InfoMapa *iMapa, short int *blocos);
// Função para desenhar o jogador na tela
void desenha_jogador(Chien2DLite *video, Elemento *jogador, InfoMapa *iMapa);

// --------------- Funções gerais para elementos -----------------------
// Função para ajustar a posição do elemento baseado na colisão do mesmo com cenário
int colide_elemento_eixo_X(Elemento *personagem, InfoMapa *iMapa, short int *blocos, int dx);
int colide_elemento_eixo_Y(Elemento *personagem, InfoMapa *iMapa, short int *blocos, int dy);

// Função para aplicar a gravidade no jogo
void aplica_gravidade_elemento(Elemento *personagem, int *dy);



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

								case SDLK_SPACE:
									pula=true;
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

								case SDLK_SPACE:
									pula=false;
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

	// monta o mapa de blocos lógicos do mapa
	short int *blocos = new short int [iMapa->altura*iMapa->largura];
	mapa->copiaCamadaMapa(0, blocos);
	// coloca true nos blocos que tem colisão (1 e 2) e false nos que não tem
	for(int linha=0;linha<iMapa->altura;linha++)
		for(int coluna=0;coluna<iMapa->largura;coluna++)
			if(blocos[linha*iMapa->largura+coluna] == 1 || blocos[linha*iMapa->largura+coluna] == 2)
				blocos[linha*iMapa->largura+coluna] = true;
			else
				blocos[linha*iMapa->largura+coluna] = false;

	// Inicia as informações do jogador e do mapa
	atualiza_jogador(jogador, iMapa, blocos);
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
               atualiza_jogador(jogador, iMapa, blocos);
				// Espera passar o tempo para desenhar o quadro
				temporiza();               
    }
    // Elimina as informações do mapa
    delete iMapa;
    // Elimina os blocos lógicos
    delete blocos;
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
void atualiza_jogador(Elemento *jogador, InfoMapa *iMapa, short int *blocos)
{
	// Atualiza a posição e a velocidade do jogador baseado no teclado
	int dx, dy;
	if(esquerda)
		dx=-3;
	else if(direita)
		dx=3;
	else
		dx = 0;
	
	// Aplica a gravidade 
	aplica_gravidade_elemento(jogador, &dy);
	
	// Verifica se colide com este deslocamento
	if(dx!=0)
		dx=colide_elemento_eixo_X(jogador, iMapa, blocos, dx);
	if(dy!=0)
		dy=colide_elemento_eixo_Y(jogador, iMapa, blocos, dy);

	// Atualiza a posição x e y.
	jogador->x += dx;
	jogador->y += dy;


	// Verifica a consistência da posição do jogador (não deixa sair fora do mapa)
	if(jogador->x<0)
		jogador->x=0;
	else if(jogador->x > iMapa->xmapa - jogador->larg)
		jogador->x = iMapa->xmapa - jogador->larg;
			
	
	// Agora, enfim, pode testar se pula ou não
	// Para pular tem que estar apoiado em algo, tqueda e vini são zero, e
	// tem que ter o botão de pula (espaço) apertado
	if(jogador->vini==0 && jogador->tqueda==0 && pula)
	{
		// Coloca uma velocidade negativa para pular
		jogador->vini = -12;
		// elimina o botão do pulo
		pula = false;
	}
	
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

// Função para ajustar a posição do elemento baseado na colisão do mesmo com cenário
int colide_elemento_eixo_X(Elemento *personagem, InfoMapa *iMapa, short int *blocos, int dx)
{
	//    Esta função corrige a posição de um elemento, baseado em quantos pontos eles estão se sobrepondo.
	//    Deve-se notar que esta função não é ideal, pois ignora a direção em que o elemento se desloca para
	// realizar o teste, nem mesmo otimiza blocos comuns de cenário que poderiam ser testados mais
	// eficientemente.	Outra coisa que a função não faz é testar elementos mais complexos que
	// retângulos, algo mandatório em jogos mais complexos.
		// Intervalo de blocos em que verificamos a colisão
		int topo, baixo, esquerda, direita;
		// O deslocamento local
		int dl=dx;
		// Qual o próximo valor de x
		int xl = personagem->x+dx;
		// Calcula o extremo esquerdo
		topo = personagem->y/iMapa->tamBloco;
		esquerda = (xl)/iMapa->tamBloco;
		// Calcula o extremo direito
		baixo = (personagem->y+personagem->alt-1)/iMapa->tamBloco;
		direita = (xl+personagem->larg-1)/iMapa->tamBloco;
		
		// A diferença entre personagem e bloco		
		int difx=0;
		// Para cada bloco no intervalo
		for(int lin=topo;lin<=baixo;lin++)
			for(int col=esquerda;col<=direita;col++)
			{
				// O bloco é válido para colisão?
				// Ele é SE:
				//			- Ele está dentro do mapa
				//		- Se ele é true (ele pode ser colidido)
				// Testa então se está dentro do mapa
				if(lin< 0 || lin >= iMapa->altura || col < 0 || col > iMapa->largura)
					continue;
				// Testa se ele é válido
				if(blocos[iMapa->largura*lin + col])
				{
					// Se for true, testa a colisão no eixo x
					difx = xl - col*iMapa->tamBloco;
					// O valor de difx tem que ser convertido para o quanto o
					// elemento entrou dentro do bloco
					
					// Se o jogador está à esquerda, tem que ajustar pelo largura
					// do elemento
					if(difx < 0)
						difx = -(personagem->larg + difx);
					// Caso contrário, está mais a esquerda e ajusta pela 
					// largura do bloco
					else
						difx = iMapa->tamBloco - difx;
					dl=dx+difx;
					
				}
			}
		
		return dl;
	
}

// Função para ajustar a posição do elemento baseado na colisão do mesmo com cenário
int colide_elemento_eixo_Y(Elemento *personagem, InfoMapa *iMapa, short int *blocos, int dy)
{
	//    Esta função corrige a posição de um elemento, baseado em quantos pontos eles estão se sobrepondo.
	//    Deve-se notar que esta função não é ideal, pois ignora a direção em que o elemento se desloca para
	// realizar o teste, nem mesmo otimiza blocos comuns de cenário que poderiam ser testados mais
	// eficientemente.	Outra coisa que a função não faz é testar elementos mais complexos que
	// retângulos, algo mandatório em jogos mais complexos.
		// Intervalo de blocos em que verificamos a colisão
		int topo, baixo, esquerda, direita;
		// O deslocamento local
		int dl=dy;
		// Qual o próximo valor de x
		int yl = personagem->y+dy;
		// Calcula o extremo esquerdo
		topo = yl/iMapa->tamBloco;
		esquerda = personagem->x/iMapa->tamBloco;
		// Calcula o extremo direito
		baixo = (yl+personagem->alt-1)/iMapa->tamBloco;
		direita = (personagem->x+personagem->larg-1)/iMapa->tamBloco;
		
		// A diferença entre personagem e bloco		
		int dify=0;
		// Para cada bloco no intervalo
		for(int lin=topo;lin<=baixo;lin++)
			for(int col=esquerda;col<=direita;col++)
			{
				// O bloco é válido para colisão?
				// Ele é SE:
				//			- Ele está dentro do mapa
				//		- Se ele é true (ele pode ser colidido)
				// Testa então se está dentro do mapa
				if(lin< 0 || lin >= iMapa->altura || col < 0 || col > iMapa->largura)
					continue;
				// Testa se ele é válido
				if(blocos[iMapa->largura*lin + col])
				{
					// Se for true, testa a colisão no eixo y
					dify = yl - lin*iMapa->tamBloco;
					// O valor de difx tem que ser convertido para o quanto o
					// elemento entrou dentro do bloco
					
					// Se o jogador está à esquerda, tem que ajustar pelo largura
					// do elemento
					if(dify < 0)
						dify = -(personagem->alt + dify);
					// Caso contrário, está mais a esquerda e ajusta pela 
					// largura do bloco
					else
						dify = iMapa->tamBloco - dify;
					dl=dy+dify;
					// Em ambos os casos, ajusta o tempo de queda
					personagem->tqueda=0;
					personagem->vini=0;
					
				}
			}
		
		return dl;
	
}


// Função para aplicar a gravidade no jogo
void aplica_gravidade_elemento(Elemento *personagem, int *dy)
{
	// Esta função calcula a próxima posição do jogador baseado na velocidade inicial e
	// no tempo passado da queda.

	// Qual o tempo passado?? (cada quadro tem 16ms)
	double tempo=personagem->tqueda*0.016;
	// O personagem cai a 32 pixeis/s². Calcula agora a velocidade atual
	double velocidade = 1+personagem->vini+48*tempo*tempo;
	// REgula a velocidade máxima
	if(velocidade > 8)
		*dy=8;
	else
		*dy = (int)velocidade;
	// Atualiza o tempo de queda
	personagem->tqueda+=1;

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
	jogador.x = 306; jogador.y = 500;
	// Preenche o tamanho do jogador
	jogador.larg = 28; jogador.alt = 40;
	jogador.xref = 2;
	jogador.yref = 24;
	// Preenche as informações da queda livre
	jogador.vini=0;
	jogador.tqueda = 0;
	
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
