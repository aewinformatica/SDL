#ifndef CHIEN2DLITE_H
#define CHIEN2DLITE_H

#define CHIEN2DLITE_DEBUG 1
#define VERSAO  0.1

// Includes padr�o C++
#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>

// Includes SDL
#include <SDL/SDL.h>
#include <SDL/SDL_Image.h>

using namespace std;

// Classe que implementa o renderer 2D "Chien2DLite", em implementa��o
// combinada SDL + SDL_Image. Para maiores detalhes
// das funcionalidades, consulte a documenta��o.
// 
// Este programa � propriedade de Paulo Vin�cius Wolski Radke, seu
// uso por terceiros � proibido, salvo autoriza��o por escrito indicando
// o contr�rio.
// 
// Data de in�cio de desenvolvimento: 21/12/2004
// Data da �ltima vers�o: 28/04/2006
    
// Estruturas de dados utilizadas

//     A estrutura azulejo possui campos relacionados � imagem no sistema, 
// sendo dividida em duas partes. Uma padr�o para todas as implementa��es e 
// outra vari�vel, de acordo com a implementa��o utilizada. 
//
// Data: 21/12/2004
// �ltima atualiza��o: 26/11/2005
    
typedef struct Azulejo
{
    // Quantos elementos usam esse azulejo. Elimina quando chega a zero
    int usuarios;
    // O apelido do azulejo. �nico no sistema
    std::string apelido;
    // O tamanho total da imagem do azulejo (quadrada)
    int dimensao;
    // As dimens�es do azulejo (em pixels)
    int dimensaoAzulejo;
    // As dimens�es da matriz de azulejos
    int dimensaoMatrizAzulejo;
    // M�scara de clos�o dos azulejos - apenas 32x32
    Uint32 **colisao32;
    
    // PARTE ESPEC�FICA DA IMPLEMENTA��O EM SDL+OPENGL
    
    // Os dados da imagem lida do disco
    SDL_Surface *imagem;
   
} Azulejo;    

// A estrutura Fonte possui campos padr�o, relacionados �s fonte no sistema.
//
// Data: 21/12/2004
// �ltima atualiza��o: 31/12/2004

typedef struct Fonte
{
    // Quantos elementos usam esse azulejo. Elimina quando chega a zero
    int usuarios;
    // O apelido da fonte. �nico no sistema
    std::string apelido;
    // Qual o tamanho (em pixels) da fonte
    int tamanhoFonte;
    // Identificador do azulejo da fonte
    unsigned int idAzulejo;
    // Os deslocamentos em pontos das letras
    int deslocamentos[256];
    // As larguras das fontes
    int larguras[256];
    
} Fonte;
      
//
// Classe Chien2DLite
//
//     Esta classe � respons�vel pelas funcionalidades do sistema de v�deo, 
// de acordo com o descrito anteriormente. Implementada como um singleton, 
// a classe � acessada de qualquer ponto do programa e deve ser iniciada e 
// encerrada de maneira apropriada. Tal processo � responsabilidade do motor, 
// baseado em configura��es padr�o ou lidas de um arquivo. O usu�rio n�o deve 
// em hip�tese alguma acessar os m�todos de in�cio e encerramento, sob pena de 
// instabilidade do sistema.
//
// Data: 21/12/2004
// �ltima atualiza��o: 21/12/2004

class Chien2DLite
{
    // Constantes da classe
    public:
        // indica que a aplica��o deve rodar em tela cheia. Valor para atributo do renderer.
        static const int telaCheia = 0;
        // indica que a aplica��o deve rodar em janela. Valor para atributo do renderer.        
        static const int janela = 1;
        
        // indica um azulejo de tamanho 8x8. Valor para campo da estrutura Azulejo.
        static const int azulejo8  = 0;
        // indica um azulejo de tamanho 16x16. Valor para campo da estrutura Azulejo.
        static const int azulejo16 = 1;
        // indica um azulejo de tamanho 32x32. Valor para campo da estrutura Azulejo.
        static const int azulejo32 = 2;
        // indica um azulejo de tamanho 64x64. Valor para campo da estrutura Azulejo.
        static const int azulejo64 = 3;

        // indica uma fonte de tamanho 8. Valor para campo da estrutura Fonte.
        static const int fonte8  = 0;
        // indica uma fonte de tamanho 16. Valor para campo da estrutura Fonte.
        static const int fonte16 = 1;
        // indica uma fonte de tamanho 32. Valor para campo da estrutura Fonte.
        static const int fonte32 = 2;
        // indica uma fonte de tamanho 64. Valor para campo da estrutura Fonte.
        static const int fonte64 = 3;

        // indica que o texto deve ser desenhado centralizado no bounding box indicado.
        static const int textoCentralizado = 0;
        // indica que o texto deve ser desenhado � esquerda no bounding box indicado.
        static const int textoEsquerda = 1;
        // indica que o texto deve ser desenhado � direita no bounding box indicado.
        static const int textoDireita = 2;
        // indica que o texto deve ser desenhado justificado no bounding box indicado.
        static const int textoJustificado = 3;
        
        // Tamanho m�ximo das listas
        static const int maximoAzulejos = 1024;
        static const int maximoFontes = 64;       
        

    // Atributos da classe
    protected:
        // Inst�ncia singleton da classe Chien2D
        static Chien2DLite *instancia;
        // A tela da SDL
        SDL_Surface *screen;
        // indica a largura em pixels do v�deo.
        unsigned int largura;
        // indica a altura em pixels do v�deo.
        unsigned int altura;
        // indica se o renderer est� rodando em modo tela cheia (true) ou modo janela (false).
        bool modoTelaCheia;
        // indica o tipo do monitor
        int tipoMonitor;
        // indica se o renderer j� foi inicializado. Utilizado para evitar in�cio redundante
        bool iniciado;
        // indica se deve aguardar o retra�o ou n�o.
        bool retraco;

        // Listas de azulejos e fontes
        Azulejo azulejos[maximoAzulejos];
        Fonte fontes[maximoFontes];
              
        // Stream de sa�da de mensagens
        std::ofstream log;
        
        // Indica se est� encerrando ou n�o
        bool shutdownNow;
        
    // UTILIZADO PARA SER UM SINGLETON!!
	protected:
        // Construtor da classe
        // construtor vazio. Inicializa o atributo iniciado com false e as listas de azulejos e fontes.
		Chien2DLite();

		// destrutor da classe
		~Chien2DLite();
	
	// M�todos p�blicos
	public:
        // Pega a inst�ncia singleton
        static Chien2DLite* pegaInstancia();

        // Remove a inst�ncia singleton
        static void removeInstancia();

        // Inicia o engine de v�deo
        bool inicia(unsigned int largura, unsigned int altura, 
            int modoVideo, bool retraco, string tituloJanela);

        // Encerra o engine de v�deo
        void encerra();
        
        // Retorna o estado da inicializa��o do v�deo
        bool foiIniciado();
        // REtorna as dimens�es da tela
        bool dimensoesTela(int *largura, int *altura);
        
        //
        // M�todos relacionados a azulejos
        //
        
        // Carrega um azulejo
        unsigned int carregaAzulejo(string arquivo, string apelido, int tipoAzulejo);
        // Procura um azulejo pelo apelido
        unsigned int pegaAzulejo(string apelido);
        // Remove um azulejo da mem�ria
        void removeAzulejo(unsigned int id);
        void removeAzulejo(string apelido);
        // M�todos para conectar e desconectar um azulejo (individual)
        void conectaAzulejo(Azulejo *azulejo);
        void desconectaAzulejo(Azulejo *azulejo);
       
        // M�todos para desenhar pontos
        void desenhaPontos(int *x, int *y, int size, int r, 
                int g, int b, int numPoints);
        
        // M�todos para desenhar um azulejo
        bool desenhaAzulejo(unsigned int identificador, unsigned int indice,
                int x, int y);
        // Verifica se dois azulejos colidiram nas coordenadas indicadas
        //    Identificador indica o azulejo no sistema, indice a por��o do
        // azulejo e (x,y) as coordenadas INTEIRAS na tela (n�o existe colis�o
        // subpixel).
        bool colidiuAzulejos(int identificador1, int indice1, int x1, int y1, 
            int identificador2, int indice2, int x2, int y2);        
        // M�todos para as fontes
        
        // Carrega uma fonte no sistema
        unsigned int carregaFonte(string arquivo, string apelido, int tipoFonte);
        // Remove uma fonte pelo identificador
        void removeFonte(unsigned int id);
        // remove uma fonte pelo apelido
        void removeFonte(string apelido);
        // Procura uma fonte na lista pelo apelido
        unsigned int pegaFonte(string apelido);
        // Escreve um texto na tela
        bool desenhaTexto(string texto, unsigned int idFonte, int x, int y, 
            int largura, int alinhamento);
        bool dimensoesTexto(string texto, unsigned int idFonte, 
             int *largura, int *altura);

        // M�todo para limpar a tela
        void limpaTela();
        // M�todo para trocar os buffers da OpenGL e mostrar a imagem desenhada
        void sincroniza();
    
    // M�todos privados da vers�o SDL
    private:
        bool pontoTransparente(SDL_Surface *surface, int x, int y);
    
};

#endif // CHIEN2DLITE_H
