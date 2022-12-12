#ifndef CHIEN2DMAPPY_H
#define CHIEN2DMAPPY_H

// Includes padrão C++
#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>

// Includes da Chien2D
#include "chien2dlite.h"

// Defines específicos da Chien2DMappy

// O número máximo de camadas do mapa (0 é mais inferior, 8 é a mais em cima)
#define MAX_CAMADAS 8
// O número máximo de azulejos animados (estamos sendo conservadores)
#define MAX_ANISTR  256
// O número máximo de sequências de animação (conservador)
#define MAX_ANIMSEQ 2048
// Defines para os tipos de header
enum {CABECALHO_IGNORADO, CABECALHO_FORM, CABECALHO_FMAP, CABECALHO_MPHD, 
        CABECALHO_ANDT, CABECALHO_BODY, CABECALHO_LYR };


// These structs and defines are from the original MAPPY source files
// © Robin Burrows <rburrows@bigfoot.com>
// http://www.tilemap.co.uk

// DEfines dos tipos de animação
#define AN_END -1
#define AN_NONE 0
#define AN_LOOPF 1
#define AN_LOOPR 2
#define AN_ONCE 3
#define AN_ONCEH 4
#define AN_PPFF 5
#define AN_PPRR 6
#define AN_PPRF 7
#define AN_PPFR 8
#define AN_ONCES 9

// Header do arquivo do MAPPY
typedef struct {	/* Map header structure */
/* char M,P,H,D;	4 byte chunk identification. */
/* long int mphdsize;	size of map header. */
char mapverhigh;	/* map version number to left of . (ie X.0). */
char mapverlow;		/* map version number to right of . (ie 0.X). */
char lsb;		/* if 1, data stored LSB first, otherwise MSB first. */
char maptype;	/* 0 for 32 offset still, -16 offset anim shorts in BODY added FMP0.5*/
short int mapwidth;	/* width in blocks. */
short int mapheight;	/* height in blocks. */
short int reserved1;
short int reserved2;
short int blockwidth;	/* width of a block (tile) in pixels. */
short int blockheight;	/* height of a block (tile) in pixels. */
short int blockdepth;	/* depth of a block (tile) in planes (ie. 256 colours is 8) */
short int blockstrsize;	/* size of a block data structure */
short int numblockstr;	/* Number of block structures in BKDT */
short int numblockgfx;	/* Number of 'blocks' in graphics (BODY) */
unsigned char ckey8bit, ckeyred, ckeygreen, ckeyblue; /* colour key values added FMP0.4*/
/* info for non rectangular block maps added FMP0.5*/
short int blockgapx, blockgapy, blockstaggerx, blockstaggery;
short int clickmask, pillars;
} MPHD;

// Estrutura da animação
typedef struct { /* Animation control structure */
signed char antype;	/* Type of anim, AN_? */
signed char andelay;	/* Frames to go before next frame */
signed char ancount;	/* Counter, decs each frame, till 0, then resets to andelay */
signed char anuser;	/* User info */
long int ancuroff;	/* Points to current offset in list */
long int anstartoff;	/* Points to start of blkstr offsets list, AFTER ref. blkstr offset */
long int anendoff;	/* Points to end of blkstr offsets list */
} ANISTR;

// Estruturas e funções da biblioteca Chien2D

typedef struct
{
    char tipo[4];
    long int tamanho;
}CabecalhoBloco;

typedef struct
{
    char tipo[4];
    long int tamanho;
    char subtipo[4];
}CabecalhoArquivo;

class Chien2DMappy
{
    // Constantes:
    public:
        static int const mapaNormal = 0;
        static int const mapaSubpixel = 1;
        // Máximo de azulejos subpixel
        static int const maxAzulejosSubpixel = 3600;

    // Atributos privados
    protected:
        // Indica se o mapa foi inicializado ou não
        bool inicializado;
        // A largura e altura do mapa
        short int largura, altura;
        // O tamanho do azulejo usado (deve bater com o arquivo e ser quadrado)
        short int dimensaoAzulejo;
        // AS camadas do mapa. 0 é a camada de base e 8 é a mais em cima
        short int *camadas[MAX_CAMADAS];
        //   As estruturas de animação, são referenciadas como números negativos
        // nas camadas
        ANISTR estrutAnimacao[MAX_ANISTR];
        //   As sequências de animação, referenciadas na estrutAnimacao
        long int seqAnimacao[MAX_ANIMSEQ];
        // O tipo do mapa, normal ou subpixel
        int tipo;
       
    public:
        // Método para criar um mapa em memória
        Chien2DMappy();
        //    Método para destruir um mapa. Se inicializado, chama o método 
        // remove mapa
        ~Chien2DMappy();
        // VErifica se foi inicializado
        bool foiIniciado();
        // Método para carregar um arquivo FMP/FMA
        bool carregaMapa(string arquivo);
        // Remove os dados alocados do mapa e marca como não inicializado
        void removeMapa();
        // Método para ver as dimensões do mapa (retorna true se associo, false caso contrário)
        bool dimensoesMapa(int *largura, int *altura, int *dimensaoAzulejo, int *camadas);
        // Método para desenhar o mapa na tela a partir das coordenadas x,y da tela
        void desenhaMapa(unsigned int idAzulejo, double x, double y);
        // Método para desenhar uma camada do mapa na tela a partir das coordenadas x,y da tela
        void desenhaCamadaMapa(unsigned int idAzulejo, int camada, double x, double y);        
        // Anima os azulejos animados do mapa. Atualiza os quadros, reseta e etc e tal
        void animaMapa();
        // Método para copiar uma camada do mapa - útil para recuperar a camada de eventos
        bool copiaCamadaMapa(int camada, short int *copia);
              
    // Métodos exclusivos para os métodos da classe
    private:
        // Método para verificar se o cabeçalho do FMP/FMA é correto
        bool verificaCabecalhoArquivo(CabecalhoArquivo *cabecalho);
        // Método para verificar o tipo do cabeçalho. Retorna um dos tipos enumerados
        int tipoBloco(CabecalhoBloco *cabecalho);
};

#endif
