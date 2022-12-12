// Include para cuidar da ordem dos bytes
#include <iostream>
#include <fstream>
#include <cmath>
#include <SDL/SDL_endian.h>
#include "chien2Dmappy.h"
using namespace std;

static char cabecalhos[6][5] ={ "FORM", "FMAP", "MPHD", "ANDT", "BODY", "LYR?"};

// M�todo para criar um mapa em mem�ria
//
// Data: 25/01/2005
// �ltima atualiza��o: 25/01/2005

Chien2DMappy::Chien2DMappy()
{
    // N�o foi inicializado ainda
    inicializado = false;
    // Zera os ponteiros
    for(int i=0;i<MAX_CAMADAS;i++)
        camadas[MAX_CAMADAS] = 0;
    // E por hoje � s� pessoal!    
}

//    M�todo para destruir um mapa. Se inicializado, chama o m�todo 
// removeMapa
//
// Data: 25/01/2005
// �ltima atualiza��o: 25/01/2005

Chien2DMappy::~Chien2DMappy()
{
    if(inicializado)
        removeMapa();
}

// Indica se o mapa foi iniciado ou n�o
//
// Data: 28/01/2005
// �ltima atualiza��o: 28/01/2005

bool Chien2DMappy::foiIniciado()
{
    return this->inicializado;
}

// M�todo para carregar um arquivo FMP/FMA
//
// Data: 25/01/2005
// �ltima atualiza��o: 27/01/2005

bool Chien2DMappy::carregaMapa(string arquivo)
{
    // Testa se j� foi inicializado, se sim, pula fora
    if(inicializado)
        return false;

    //    L� o arquivo para mem�ria. Esse m�todo � escolhido para facilitar 
    // a convers�o futura para VFS

    // Abre a stream de entrada
    ifstream mapa;
    mapa.open (arquivo.c_str(), ios::binary );
    if(!mapa.is_open())
        return false;
    // pega o tamanho do arquivo
    mapa.seekg (0, ios::end);
    int tamanho = mapa.tellg();
    mapa.seekg (0, ios::beg);
    // Aloca mem�ria para o arquivo inteiro
    char *buffer = new char [tamanho];
    // L� os dados
    mapa.read (buffer,tamanho);
    // Fecha o arquivo
    mapa.close();
    // Pega o "suposto" cabe�alho do arquivo
    CabecalhoArquivo *cabArq = (CabecalhoArquivo*)buffer;
    // Verifica se o cabecalho � certo
    if(verificaCabecalhoArquivo(cabArq))
    {
        // Recupera o tamanho do arquivo (est� em BIG ENDIAN)
        int tamanho = cabArq->tamanho;
        if(SDL_BYTEORDER == SDL_LIL_ENDIAN)
            tamanho = SDL_Swap32(tamanho);
        // O tamanho total soma 8
        tamanho+=8;
        // �ndice dentro do buffer lido, j� pulando o header de 12 bytes
        int indice=12;        
        // Indica se o arquivo � armazenado em little endian (recupera do MPHD)
        bool arquivoLilEndian=false;
        // Indica se o sistema � lil endian (usado com a vari�vel em arquivo)
        bool sistemaLilEndian = false;
        if(SDL_BYTEORDER == SDL_LIL_ENDIAN)
            sistemaLilEndian=true;
        // Processa os chunks do arquivo enquanto o �ndice estiver dentro do arquivo
        while(indice < tamanho)
        {
            // pega o pr�ximo chunk
            CabecalhoBloco *bloco = (CabecalhoBloco *)&(buffer[indice]);
            // Faz o indice apontar para os dados do bloco (pula 8 bytes)
            indice += 8;
            // Pega o tamanho do bloco (est� no formato intel)
            int tamBloco = bloco->tamanho;
            if(SDL_BYTEORDER == SDL_LIL_ENDIAN)
                tamBloco = SDL_Swap32(tamBloco);
            //    Aqui extra�mos as informa��es dos blocos. Nos interessam apenas
            // o header do arquivo (MPHD), o cen�rio (BODY), os layers (LYR"X")
            // e as anima��es (ANDT)
            switch(tipoBloco(bloco))
            {
                case CABECALHO_MPHD:
                {
                    // Acessa o header
                    MPHD *mphd = (MPHD *)&(buffer[indice]);
                    // O arquivo � codificado em Little Endian?
                    if(mphd->lsb)
                        arquivoLilEndian=true;
                    // Extra as informa��es relevantes
                    this->altura = mphd->mapheight;
                    this->largura = mphd->mapwidth;
                    this->dimensaoAzulejo = mphd->blockwidth;
                    // Se o sistema e arquivo n�o baterem
                    if(arquivoLilEndian != sistemaLilEndian)
                    {
                        this->altura = SDL_Swap16(this->altura);
                        this->largura = SDL_Swap16(this->largura);
                        this->dimensaoAzulejo = SDL_Swap16(this->dimensaoAzulejo);
                    }
                    break;
                }
                // Bloco dos dados da camada principal (0)
                case CABECALHO_BODY:
                {
                    // Aloca a mem�ria do layer principal
                    this->camadas[0] = new short int[largura*altura];
                    // Copia os dados do buffer para a camada
                    memcpy(camadas[0], (short int*)&(buffer[indice]), 
                            largura*altura*sizeof(short int));
                    if(arquivoLilEndian != sistemaLilEndian)
                        for(int i=0;i<largura*altura;i++)
                           camadas[0][i]=SDL_Swap16(camadas[0][i]); 
                    break;
                }
                // Um dos layers associados
                case CABECALHO_LYR:
                {
                    // Determina a camada
                    int camada = bloco->tipo[3]-'0';
                    // Aloca a mem�ria do layer principal
                    this->camadas[camada] = new short int[largura*altura];
                    // Copia os dados do buffer para a camada
                    memcpy(camadas[camada], (short int*)&(buffer[indice]), 
                            largura*altura*sizeof(short int));
                    if(arquivoLilEndian != sistemaLilEndian)
                        for(int i=0;i<largura*altura;i++)
                           camadas[camada][i]=SDL_Swap16(camadas[camada][i]); 
                    break;
                }
                // Anima��es
                case CABECALHO_ANDT:
                {
                    // Procura as estruturas ANISTR (tem que ter pelo menos uma)
                    int numAniStr=0;
                    while(true)
                    {
                        // Pega a estrutura (a zero � vazia)
                        numAniStr++;
                        memcpy(&estrutAnimacao[numAniStr], 
                            (ANISTR*)&(buffer[indice+tamBloco-sizeof(ANISTR)*numAniStr]),
                            sizeof(ANISTR));
                        // Se a anima��o � do tipo AN_END, chegou ao fim
                        if(estrutAnimacao[numAniStr].antype == AN_END)
                            break;
                    }
                    // Extrai as sequ�ncias de anima��o: tamanho do bloco- ANISTR lidas
                    int numAnimSeq=(tamBloco-sizeof(ANISTR)*numAniStr)/sizeof(long int);
                    memcpy(this->seqAnimacao, (long int*)&(buffer[indice]),
                        sizeof(long int)*numAnimSeq);
                    // Ajusta os dados com mais de um byte
                    if(arquivoLilEndian != sistemaLilEndian)
                    {
                        for(int i=0;i<numAniStr;i++)
                        {
                           estrutAnimacao[i].ancuroff = SDL_Swap32(estrutAnimacao[i].ancuroff); 
                           estrutAnimacao[i].anstartoff = SDL_Swap32(estrutAnimacao[i].anstartoff); 
                           estrutAnimacao[i].anendoff = SDL_Swap32(estrutAnimacao[i].anendoff);                                                      
                        }
                        for(int i=0;i<numAnimSeq;i++)
                            seqAnimacao[i] = SDL_Swap32(seqAnimacao[i]);
                    }
                    break;                    
                }
                
                // Ignora o bloco e passa para o pr�ximo
                default:
                    break;
            }
            // Atualiza a posi��o do �ndice
            indice += tamBloco;
        }
        // Caregou o mapa, pode finalizar!
        inicializado = true;    
        // O mapa � do tipo normal a princ�pio
        this->tipo = Chien2DMappy::mapaNormal;
    }
    // Apaga o buffer
    delete buffer;
    // Retorna se inicializou certo ou n�o
    return inicializado;
}

// Remove os dados alocados do mapa e marca como n�o inicializado
//
// Data: 25/01/2005
// �ltima atualiza��o: 25/01/2005

void Chien2DMappy::removeMapa()
{
    if(!inicializado)
        return;
    // Elimina os mapas da mem�ria
    for(int i=0;i<MAX_CAMADAS;i++)
        if(camadas[MAX_CAMADAS] != 0)
            delete(camadas[MAX_CAMADAS]);
    inicializado = false;
}

// M�todo para verificar se o cabe�alho do FMP/FMA � correto
//
// Data: 26/01/2005
// �ltima atualiza��o: 26/01/2005

bool Chien2DMappy::verificaCabecalhoArquivo(CabecalhoArquivo *cabecalho)
{
    // Est� certo por defini��o
    bool ok=true;
    // Verifica se tem o FORM no come�o
    for(int i=0;i<4;i++)
        if(cabecalho->tipo[i] != cabecalhos[0][i])
        {
            ok=false;
            break;
        }
    if(!ok)
        return ok;
    // Verifica se tem o FMAP no subtipo
    for(int i=0;i<4;i++)
        if(cabecalho->subtipo[i] != cabecalhos[1][i])
        {
            ok=false;
            break;
        }
    return ok;
}

// M�todo para ver as dimens�es do mapa (retorna true se associo, false caso contr�rio)
//
// Data: 26/01/2005
// �ltima atualiza��o: 26/01/2005
bool Chien2DMappy::dimensoesMapa(int *largura, int *altura, int *dimensaoAzulejo, int *camada)
{
    // Se n�o foi inicializado, falha!
    if(!inicializado)
        return false;
    // Preenche os valores
    *largura = this->largura;
    *altura = this->altura;
    *dimensaoAzulejo = this->dimensaoAzulejo;
    // Conta quantas camadas tem no mapa
    *camada = 0;
    for(int i=0;i<MAX_CAMADAS;i++)
        if(this->camadas[i] != 0)
            *camada=*camada+1;
    // Indica que deu certo
    return true;
}

// M�todo para desenhar uma camada do mapa na tela a partir das coordenadas x,y do mapa
//
// Data: 28/01/2005
// �ltima atualiza��o: 28/01/2005

void Chien2DMappy::desenhaCamadaMapa(unsigned int idAzulejo, int camada, int x, int y)
{
    if(!this->inicializado)
        return;
    // TEsta se � um layer v�lido
    if(camada > MAX_CAMADAS)
        return;
    // Testa se o layer existe
    if(this->camadas[camada] == 0)
        return;
    // As dimens�es da tela
    int larguraTela, alturaTela;
    // Pega o renderer
    Chien2DLite *renderer = Chien2DLite::pegaInstancia();
    // Pega as dimens�es. Se der false, pula fora
    if(!renderer->dimensoesTela(&larguraTela, &alturaTela))
        return;
    // S� desenha o mapa se o ponto �ncora for dentro do mapa e o mapa couber na tela
    if(x<0 || y<0 || x>(largura*dimensaoAzulejo-larguraTela) 
            || y>(altura*dimensaoAzulejo-alturaTela))
        return;
    // VAri�vel para o azulejo que vai ser desenhado
    int azulejo;
    // Determina as dimens�es da tela em azulejos (quanto vai desenhar)
    int larguraAzulejos = larguraTela/dimensaoAzulejo;
    int alturaAzulejos = alturaTela/dimensaoAzulejo;  
    // Determina os blocos no mapa
    int blocoX = (int)floor(x)/dimensaoAzulejo;
    int blocoY = (int)floor(y)/dimensaoAzulejo;
    // Determina a posi��o inicial do mapa
    //int offsetX = (int)floor(x)%dimensaoAzulejo;
    //int offsetY = (int)floor(y)%dimensaoAzulejo;
    // DEtermina o offset em n�mero real
    int aux = (int)x/dimensaoAzulejo;
    int offsetX = x - aux*dimensaoAzulejo;
    aux = (int)y/dimensaoAzulejo;    
    int offsetY = y - aux*dimensaoAzulejo;
    // Se tem offset, precisa desenhar um bloco a mais na dire��o
    // Nota: n�o precisa verificar se vai ultrapassar o limite f�sico do mapa 
    // porque o teste da posi��o no mapa acima j� faz isso
    if(offsetX>0)
        larguraAzulejos+=1;
    if(offsetY>0)
        alturaAzulejos+=1;
    // Desenha o mapa
    for(int linha=0;linha<alturaAzulejos;linha++)
        for(int coluna=0;coluna<larguraAzulejos;coluna++)
        {
            // Recupera o azulejo a desenhar
            azulejo = camadas[camada][largura*(linha+blocoY)+coluna+blocoX];
            // Se o azulejo for negativo, recupera o azulejo na lista de anima��es
            if(azulejo < 0)
                //    Como o valor � negativo, tem que negar antes, 
                // pegando na sequ�ncia de anima��o
                azulejo = seqAnimacao[estrutAnimacao[-azulejo].ancuroff];
            // N�o desenha o azulejo 0 (transparente)
            if(azulejo!=0)
            {
                renderer->desenhaAzulejo(idAzulejo, azulejo, 
                   coluna*dimensaoAzulejo-offsetX, 
                   linha*dimensaoAzulejo-offsetY);
            }
        }
}


// Anima os azulejos animados do mapa. Atualiza os quadros, reseta e etc e tal
//
// Data: 27/01/2005
// �ltima atualiza��o: 27/01/2005

void Chien2DMappy::animaMapa()
{
    // Testa se pode fazer a opera��o
    if(!this->inicializado)
        return;    
    // Procura as anima��es (0 n�o existe, lembrando)
    int indice = 1;
    while(this->estrutAnimacao[indice].antype != AN_END)
    {
        //     Verifica se n�o � uma anima��o (s� Deus sabe porque isso existe)
        //     Se verdade, pula (acredite, isso faz tanto sentido pra mim como 
        // pra voc�, afinal, n�o � pra ser ANIMADO?!?
        if(this->estrutAnimacao[indice].antype == AN_NONE)
            continue;
        // Se a anima��o zera, tem que atualizar
        if((this->estrutAnimacao[indice].ancount-=1) == 0)
        {
            // Armazena o delay novo
            estrutAnimacao[indice].ancount = estrutAnimacao[indice].andelay;
            //    Atualiza o frame e, se estourou, volta para o in�cio de acordo
            // com o tipo da anima��o
            switch(this->estrutAnimacao[indice].antype)
            {
                // Loop pra frente
                case AN_LOOPF:            
                {
                    if((estrutAnimacao[indice].ancuroff+=1) == estrutAnimacao[indice].anendoff)
                        estrutAnimacao[indice].ancuroff = estrutAnimacao[indice].anstartoff;
                    break;
                }
                // Loop reverso
                case AN_LOOPR:
                {
                    if((estrutAnimacao[indice].ancuroff-=1) < estrutAnimacao[indice].anstartoff)
                        estrutAnimacao[indice].ancuroff = estrutAnimacao[indice].anendoff-1;
                    break;
                }
                // Anima uma �nica vez (n�o muit o�til se n�o for na primeira tela)
                case AN_ONCE:            
                {
                    if(estrutAnimacao[indice].anuser)
                        break;
                    // Testa se chegou no final
                    if((estrutAnimacao[indice].ancuroff+=1) == estrutAnimacao[indice].anendoff-1)
                        estrutAnimacao[indice].anuser = true;
                    break;        
                }
                // Anima��o ping-pong pra frente
                case AN_PPFF:
                {
                    // Se verdade, vai de marcha-r�
                    if(estrutAnimacao[indice].anuser==0)
                    {
                        if((estrutAnimacao[indice].ancuroff-=1) < estrutAnimacao[indice].anstartoff)
                        {
                            estrutAnimacao[indice].ancuroff = estrutAnimacao[indice].anstartoff+1;
                            estrutAnimacao[indice].anuser = 1;                
                        }
                    }
                    else
                    {
                        if((estrutAnimacao[indice].ancuroff+=1) == estrutAnimacao[indice].anendoff)
                        {
                            estrutAnimacao[indice].ancuroff = estrutAnimacao[indice].anendoff-2;
                            estrutAnimacao[indice].anuser = 0;
                        }
                    }   
                    break;
                }
                // Anima��o ping-pong pra tr�s
                case AN_PPRR:
                {
                    // Se verdade, vai pra frente
                    if(estrutAnimacao[indice].anuser==0)
                    {
                        if((estrutAnimacao[indice].ancuroff+=1) == estrutAnimacao[indice].anendoff)
                        {
                            estrutAnimacao[indice].ancuroff = estrutAnimacao[indice].anendoff-2;
                            estrutAnimacao[indice].anuser = 1;
                        }
                    }
                    else
                    {
                        if((estrutAnimacao[indice].ancuroff-=1) < estrutAnimacao[indice].anstartoff)
                        {
                            estrutAnimacao[indice].ancuroff = estrutAnimacao[indice].anstartoff+1;
                            estrutAnimacao[indice].anuser = 0;                
                        }
                    }
                    break;
                }
                                   
                default:
                    break;
                
            }
        }
        // Pr�xima anima��o
        indice++;
    }
}

// M�todo para copiar uma camada do mapa - �til para recuperar a camada de eventos
//
// Data: 28/01/2005
// �ltima atualiza��o: 28/01/2005
bool Chien2DMappy::copiaCamadaMapa(int camada, short int *copia)
{
    // Testa se pode fazer a opera��o
    if(!this->inicializado)
        return false;    
    
    if(this->camadas[camada] == 0)
        return false;
    if(copia == 0)
        return false;
    memcpy(copia, camadas[camada], largura*altura*sizeof(short int));
    return true;
}


// M�todo para verificar o tipo do cabe�alho. Retorna um dos tipos enumerados
//
// Data: 26/01/2005
// �ltima atualiza��o: 26/01/2005

int Chien2DMappy::tipoBloco(CabecalhoBloco *cabecalho)
{    
    // Verifica se � o bloco do MPHD no come�o
    bool ok=true;
    for(int i=0;i<4;i++)
        if(cabecalho->tipo[i] != cabecalhos[2][i])
        {
            ok=false;
            break;
        }
    if(ok)
        return CABECALHO_MPHD;
    // Verifica se � o bloco do ANDT no come�o
    ok=true;
    for(int i=0;i<4;i++)
        if(cabecalho->tipo[i] != cabecalhos[3][i])
        {
            ok=false;
            break;
        }
    if(ok)
        return CABECALHO_ANDT;
    // Verifica se � o bloco do BODY no come�o
    ok=true;
    for(int i=0;i<4;i++)
        if(cabecalho->tipo[i] != cabecalhos[4][i])
        {
            ok=false;
            break;
        }
    if(ok)
        return CABECALHO_BODY;
    // Verifica se � uma camada (o quarto caracter � o n�mero da camada)
    ok=true;
    for(int i=0;i<3;i++)
        if(cabecalho->tipo[i] != cabecalhos[5][i])
        {
            ok=false;
            break;
        }
    if(ok)
        return CABECALHO_LYR;  
    
    // Por default
    return CABECALHO_IGNORADO;
}

