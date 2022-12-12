#include <cmath>
#include "chien2dlite.h"
//#include "geometria2D.h"

// Classe que implementa o renderer 2D "Chien2D", em implementação
// combinada SDL + SDL_Image. Para maiores detalhes
// das funcionalidades, consulte a documentação.
// 
// Este programa é propriedade de Paulo Vinícius Wolski Radke, seu
// uso por terceiros é proibidi, salvo autorização por escrito indicando
// o contrário.
// 
// Data de início de desenvolvimento: 21/12/2004
// Data da última versão:


using namespace std;

// Instância singleton da classe Chien2D
Chien2DLite* Chien2DLite::instancia=0;

// Construtor da classe
// construtor vazio. Inicializa o atributo iniciado com false e as listas de azulejos e fontes.
//
// Data: 21/12/2004
// Última atualização: 26/11/2004

Chien2DLite::Chien2DLite()
{
    // Garante que não foi iniciado
    iniciado = false;
    // Limpa os dados dos azulejos (nulo)
    for(int i=0;i<Chien2DLite::maximoAzulejos;i++)
    {
        azulejos[i].usuarios=0;
        azulejos[i].imagem=0;
        azulejos[i].colisao32=0;
        azulejos[i].apelido="";
    }
    // Reinicia os azulejos das fontes
    for(int i=0;i<Chien2DLite::maximoFontes;i++)
    {
        fontes[i].usuarios=0;        
        fontes[i].idAzulejo = 0;
        fontes[i].apelido = "";
    }    
    // Opens the output file
    log.open("video.log");
    #ifdef CHIEN2DLITE_DEBUG
        if(!log.is_open())
            std::cout << "Nao conseguiu abrir o arquivo de log!" << endl;
    #endif
    
    if(log.is_open())
    {
        log << "CHIEN 2D - v" << VERSAO << " - c 2004,2005 Paulo V. W. Radtke" << endl << endl;
        log << "Criação da classe ok - Aguardando início do sistema de vídeo" << endl;
    }
}

// destrutor da classe
Chien2DLite::~Chien2DLite()
{
    if(iniciado)
        encerra();
	// insert your code here
    if(log.is_open())
        log << "Fechando o arquivo de log para encerrar a instância." << endl;
	log.close();
}

//    Retorna o ponteiro para a instância única do renderer. Caso o atributo 
//  instancia possua um valor diferente de NULL, retorna o valor armazenado no 
//  atributo. Caso contrário, aloca uma nova instância, armazena no atributo 
//  e a retorna.
//
// Data: 21/12/2004
// Última atualização: 21/12/2004

Chien2DLite* Chien2DLite::pegaInstancia()
{
    if(instancia==0)
    {
        instancia = new Chien2DLite();
        if(instancia->log.is_open())
            instancia->log << "Alocou a instância da Chien2DLite - pegaInstancia()" << endl;
    }
    return instancia;
}

//    deleta a instância do singleton. Deve ser utilizado com cuidado, apenas 
//  no encerramento do sistema. Apaga os elementos da memória se preciso, 
//  utilizando o método encerra.
//
// Data: 21/12/2004
// Última atualização: 21/12/2004

void Chien2DLite::removeInstancia()
{
    // Testa se existe a instância
    if(instancia!=0)
    {
        // Se existe a instância, ela foi iniciada?
        if(instancia->foiIniciado())
        {
            // Se foi iniciada, deve fechar e apagar tudo antes.
            if(instancia->log.is_open())
                instancia->log << "Encerrando a instância - removeInstancia()" << endl;
            instancia->encerra();    
            if(instancia->log.is_open())
                instancia->log << "Terminou de encerrar a instancia  - removeInstancia()" << endl;       
        }
        if(instancia->log.is_open())
            instancia->log << "Vai apagar a instância da memória  - removeInstancia()" 
            << endl;
        delete instancia;
        instancia = 0;
    }

}

//     Recebe as dimensões da tela, as dimensões da janela, o modo do vídeo 
// (tela cheia ou janela), tipo de monitor e o valor para o retraço. Verifica a
// consistência do modo, prepara o vídeo e inicia atributos da configuração. 
// Retorna true se teve sucesso, false caso contrário. Verifica antes de tudo 
// o atributo iniciado para evitar o início duplo da instância. 
//
// Data: 21/12/2004
// Última atualização: 25/12/2004

bool Chien2DLite::inicia(unsigned int largura, unsigned int altura, 
     int modoVideo, bool retraco, string tituloJanela)
{
    if(iniciado)
        return false;     

    // Não está encerrando agora ...
    shutdownNow = false;

    // Testa se já foi inicializado o vídeo (se foi, cai fora!)
    if(SDL_WasInit(SDL_INIT_VIDEO))
        return false;
    // Inicia o vídeo
    if ( SDL_InitSubSystem(SDL_INIT_VIDEO) < 0 ) 
    {
        if(log.is_open())
            log << "A Chien2DLite não conseguiu iniciar a SDL. Mensagem do sistema: " 
                <<  SDL_GetError() << endl;
        return false;
    }

    // Imprime informação do modo de vídeo requisitado
    if(log.is_open())
        log << "Iniciando o modo de vídeo: " << largura << "x" << altura <<
            "32bpp" << endl;
    
    // Flags do modo de vídeo (se ficar assim, roda em janela)
    Uint32 flags = SDL_HWSURFACE ;
    // Espera pelo retraço vertical?
    if(retraco)
    {
        flags |= SDL_DOUBLEBUF ;
    }
    // Se for rodar em tela cheia, tem que colocar um flag a mair
    if(modoVideo==Chien2DLite::telaCheia)
    {
        flags |= SDL_FULLSCREEN;
        if(log.is_open())
            log << "A aplicação requisitou um modo em tela cheia." << endl;
    }
    else
        if(log.is_open())
            log << "A aplicação requisitou um modo em janela." << endl;
    
    // Inicia o modo de vídeo
    if(log.is_open())
        log << "A Chien2DLite vai verificar se o modo requisitado é válido." << endl; 
    
    if(SDL_VideoModeOK(largura, altura, 24, flags) ) 
    {
        if(log.is_open())
            log << "O sistema indica que o modo é suportado. Tenta iniciar." << endl; 
        
        // Inicia o modo de vídeo e recupera a surface (diferente de 0 se tudo ok)
        screen = SDL_SetVideoMode(largura, altura, 32,  flags);
        if ( screen == 0 ) 
        {
            if(log.is_open())
                log << "Não foi possível iniciar o modo de vídeo requisitado. Encerrando." << endl;
            SDL_QuitSubSystem(SDL_INIT_VIDEO);
            return false;
        }
    }
    else
    {
        if(log.is_open())
            log << "O modo de vídeo não é suportado pelo hardware. Encerrando." << endl; 
		SDL_QuitSubSystem(SDL_INIT_VIDEO);
        return false;
    }
    if(log.is_open())
        log << "Modo de vídeo iniciado com sucesso!" << endl;

    // Coloca o nome na janela
    SDL_WM_SetCaption(tituloJanela.c_str(), 0);
    

    // Desabilita o cursor do mouse
    SDL_ShowCursor(SDL_DISABLE);

    // Armazena as váriáveis do sistema
    this->largura = largura;
    this->altura = altura;
    if(modoVideo == Chien2DLite::janela)
        modoTelaCheia = false;
    else
        modoTelaCheia = true;
    this->retraco = retraco;
    
    // Indica que foi iniciado e pula fora
    iniciado=true;
    return true;
}

//     Encerra o modo de vídeo, eliminando todos os elementos da memória e 
// colocando o valor false no atributo iniciado.
//
// Data: 21/12/2004
// Última atualização: 25/12/2004

void Chien2DLite::encerra()
{
    // Testa por via das dúvidas para não ter problemas
    if(!iniciado)
        return;
        
    // Indica que está encerrando
    shutdownNow = true;
        
    if(log.is_open())
        log << "Apagando os azulejos e fontes do sistema." << endl;
    //
    //

    // Apaga as fontes
    for(int i=0;i<Chien2DLite::maximoFontes;i++)
        this->removeFonte(i+1);

    // Apaga os azulejos
    for(int i=0;i<Chien2DLite::maximoAzulejos;i++)
        this->removeAzulejo(i+1);

    if(log.is_open())
        log << "Encerrando a SDL" << endl;
    // Encerra o vídeo
    SDL_Surface *screen= SDL_GetVideoSurface();
    if(screen != 0)
        SDL_FreeSurface(screen);        
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
    if(log.is_open())
        log << "Encerrou a SDL" << endl;
    
    iniciado=false;
}

//     Retorna o estado da inicialização do vídeo
//
// Data: 21/12/2004
// Última atualização: 21/12/2004

bool Chien2DLite::foiIniciado()
{
    return iniciado;
}

// Retorna as dimensões da tela
//
// Data: 26/01/2005
// Última atualização: 26/01/2005

bool Chien2DLite::dimensoesTela(int *largura, int *altura)
{
    // Se não estiver inicializado, pula fora
    if(!iniciado)
        return false;
    // Associa os valores
    *largura = this->largura;
    *altura = this->altura;
    // Indica que deu certo
    return true;
}

//     Elimina um azulejo da memória. Versão que recebe o identificador. Se o 
// azulejo não existir, ignora e não faz nada. Ao remover o azulejo, além de 
// remover a imagem da memória, prepara a posição na lista para uso futuro .
//
// Data: 25/12/2004
// Última atualização: 28/04/2006
//

//     CarregaAzulejo (inteiro não sinalizado, public) - recebe o nome do arquivo em disco para carregar a imagem, o apelido do azulejo e a dimensão - obrigatoriamente quadrado e potência de 2. Cria uma instância de Azulejo baseada no arquivo, associa o apelido, determina o identificado único, insere na lista de azulejos e retorna o identificador. Caso falhe a leitura do arquivo ou então as dimensões do azulejo sejam inválidas, retorna NULL e não realiza as operações. Se já existir na lista um azulejo com o mesmo nome, não carrega e retorna o identificador do azulejo em memória. Caso não seja possível incluir novos azulejos, retorna 0. Testa se a imagem lida é quadrada.

unsigned int Chien2DLite::carregaAzulejo(string arquivo, string apelido, int tipoAzulejo)
{
    // Verifica se o azulejo não existe já
    unsigned int idx = pegaAzulejo(apelido);
    // Se já existe um azulejo com o apelido, retorna o índice associado
    if(idx != 0)
    {
        azulejos[idx-1].usuarios=azulejos[idx-1].usuarios+1;
        return idx;
    }
        
    // Se não existe, procura o primeiro índice vago (idx ainda é igual a 0)
    for(int i=0;i<Chien2DLite::maximoAzulejos;i++)
        // O azulejo é vago (não tem imagem associada?
        if(this->azulejos[i].imagem == 0)
        {
            idx=i+1;
            break;
        }
    
    // Testa se ainda tem espaço na lista
    //
    // ATENÇÃO: não ter espaço na memória não é relacionado a este teste. Apenas
    // testa-se aqui se existe um índice vago na lista. Se não existe, idx==0
    if(idx==0)
        // Retorna um índice inválido para indicar que o método falhou
        return 0;
    
    // Se chegou até aqui, idx contém o identificador correto 
    // posição no array (sem incrementar 1)
    idx=idx-1;    
    // Indica o apelido
    this->azulejos[idx].apelido = apelido;

    // Carrega a imagem no azulejo
    this->azulejos[idx].imagem = IMG_Load(arquivo.c_str());

    // Testa: conseguiu abrir a imagem? Se deu erro, retorna azulejo inválido
    if ( this->azulejos[idx].imagem == 0) 
    {
        if(log.is_open())
            log << "Método carregaAzulejo falhou ao carregar o arquivo " << 
                arquivo << " (apelido: " << apelido << ") Erro: " << 
                SDL_GetError() << endl;
        this->azulejos[idx].apelido = "";
        return 0;
    }

    // Preenche a dimensão total do azulejo
    this->azulejos[idx].dimensao = this->azulejos[idx].imagem->w;
    // A imagem carregada é quadrada? Compara a dimensão pega da largura com a 
    // altura da imagem
    if(this->azulejos[idx].dimensao != this->azulejos[idx].imagem->h)
    {
        // Se não for, apaga a imagem e retorna
        if(log.is_open())
            log << "Método carregaAzulejo não pode utilizar o arquivo " << 
                arquivo << " (apelido: " << apelido << 
                ") Erro: a imagem não é quadrada." << endl;
        SDL_FreeSurface(this->azulejos[idx].imagem);
        return 0;
        
    }
    //    A imagem tem dimensões em potência de 2? Suportamos: 32, 64, 128, 256,
    // 512, 1024
    bool potencia=false;
    // Testamos de potência de 5 (32) até potência de 10 (1024);
    for(int i=5;i<=10;i++)
        if(pow(2.0,i)==this->azulejos[idx].dimensao)
        {
            potencia=true;
            break;
        }
    if(!potencia)
    {
        // Se não for, apaga a imagem e retorna
        if(log.is_open())
            log << "Método carregaAzulejo não pode utilizar o arquivo " << 
                arquivo << " (apelido: " << apelido << 
                ") Erro: as dimensões da imagem não são potência de 2." << endl;
        SDL_FreeSurface(this->azulejos[idx].imagem);
        return 0;
        
    }
    // Associa outras informações
    // Escolhe as dimensões do azulejo
    switch(tipoAzulejo)
    {
        case Chien2DLite::azulejo8:
            this->azulejos[idx].dimensaoAzulejo=8;
            break;
        case Chien2DLite::azulejo16:
            this->azulejos[idx].dimensaoAzulejo=16;
            break;
        case Chien2DLite::azulejo32:
            this->azulejos[idx].dimensaoAzulejo=32;
            break;
        case Chien2DLite::azulejo64:
            this->azulejos[idx].dimensaoAzulejo=64;
            break;
        // Esse caso existe apenas em erro
        default:
            if(log.is_open())
                log << "Método carregaAzulejo não pode utilizar o arquivo " << 
                    arquivo << " (apelido: " << apelido << 
                    ") Erro: tipo de azulejo inválido - contacte o produtor." 
                    << endl;
            SDL_FreeSurface(this->azulejos[idx].imagem);
            return 0;
    }
    // O tipo de azulejo é compatível com o tamanho da imagem carregada?
    if(this->azulejos[idx].dimensaoAzulejo > this->azulejos[idx].dimensao)
    {
        if(log.is_open())
            log << "Método carregaAzulejo não pode utilizar o arquivo " << 
                arquivo << " (apelido: " << apelido << 
                ") Erro: tipo de azulejo incompatível com o tamanho da imagem"
                << " - contacte o produtor." << endl;
        SDL_FreeSurface(this->azulejos[idx].imagem);
        return 0;
    }
    
    // Preenche o tamanho da matriz de azulejos
    this->azulejos[idx].dimensaoMatrizAzulejo = 
        this->azulejos[idx].dimensao/this->azulejos[idx].dimensaoAzulejo;
        
    // Define o magenta (R=255, B=255, G=0) para cor transparente
    SDL_SetColorKey(this->azulejos[idx].imagem, SDL_SRCCOLORKEY | SDL_RLEACCEL,
              SDL_MapRGB(this->azulejos[idx].imagem->format, 255, 0, 255));
    // Converte a imagem para o formato do vídeo do sistema
    SDL_Surface *temp=SDL_DisplayFormat(this->azulejos[idx].imagem);
    if(temp == NULL) 
    {
        if(log.is_open())
          log << "Não conseguiu criar a imagem temporária no método " <<
              "carregaAzulejo. Arquivo: " << arquivo <<" (apelido: " <<
              apelido << ") - Erro: " << SDL_GetError() << endl;
          // Tem que apagar a imagem carregada antes de encerrar 
          SDL_FreeSurface(this->azulejos[idx].imagem);               
          // Retorna um identificador de azulejo inválido
          return 0;
    }   
    // Apaga a surface antiga
    SDL_FreeSurface(this->azulejos[idx].imagem);
    // Associa a nova
    this->azulejos[idx].imagem = temp;

    // Cria a máscara de colisão 32x32
    if(this->azulejos[idx].dimensaoAzulejo==32)
    {
        // Quantos azulejos estão armazenados 
        int numAzulejos = (azulejos[idx].dimensaoMatrizAzulejo)*(azulejos[idx].dimensaoMatrizAzulejo);
        this->azulejos[idx].colisao32 = new Uint32*[numAzulejos];
        // Para cada azulejo, cria a máscara
        for(int azulejo=0;azulejo<numAzulejos;azulejo++)
        {
            // São 32 linhas no azulejo
            this->azulejos[idx].colisao32[azulejo]= new Uint32[32];
            // Pega os pontos transparentes na imagem
            SDL_LockSurface(this->azulejos[idx].imagem);
            for(int linha=0;linha<32;linha++)
            {
                Uint32 bit=0x80000000, valor=0;
                for(int coluna=0;coluna<32;coluna++)
                {
                    // determina os pontos na imagem
                    int x = coluna+(azulejo%this->azulejos[idx].dimensaoMatrizAzulejo)*32;
                    int y = linha+(azulejo/this->azulejos[idx].dimensaoMatrizAzulejo)*32;
                    if(!pontoTransparente(this->azulejos[idx].imagem, x, y))
                        valor |= bit;
                    bit=bit>>1;
                    
                }
                this->azulejos[idx].colisao32[azulejo][linha]=valor;
            }
            SDL_UnlockSurface(this->azulejos[idx].imagem);
        }
    }        
    // Imprime os dados dos azulejos se estiver no modo debug
    #ifdef CHIEN2DLITE_DEBUG
    if(azulejos[idx].colisao32 != 0)
    {
        int numAzulejos = (azulejos[idx].dimensaoMatrizAzulejo)*(azulejos[idx].dimensaoMatrizAzulejo);
        log << "Azulejo: " << this->azulejos[idx].apelido << " - " << numAzulejos << " azulejos." << endl << endl;
        for(int i=0;i<numAzulejos;i++)
        {
            log << "Azulejo: " << i << endl;
            for(int linha=0;linha<32;linha++)
            {
                Uint32 mascara = this->azulejos[idx].colisao32[i][linha];
                Uint32 val = 0x80000000;
                for(int bit=0;bit<32;bit++)
                {
                    if(mascara & val)
                        log << "1";
                    else
                        log << "0";
                    val = val >> 1;
                }   
                log << endl;
            }
        }
    }
    #endif
    // Indica que tem um usuário
    azulejos[idx].usuarios = 1;
    // idx+1 indica o identificador. Retorna e encerra (ufa!)
    return idx+1;
}


//     Recebe o apelido de um azulejo e retorna identificador do azulejo na 
//lista. Caso ele não esteja na lista, retorna 0. 
//
// Data: 26/12/2004
// Última atualização: 26/12/2004
//

unsigned int Chien2DLite::pegaAzulejo(string apelido)
{
    // Índice de azulejo inválido, caso não encontre
    unsigned int idx=0;
    for(int i=0;i<Chien2DLite::maximoAzulejos;i++)
        if(this->azulejos[i].apelido == apelido)
        {
            // O índice é a posição atual + 1
            idx=i+1;
            // Encerra a busca
            break;
        }
    return idx;
}

void Chien2DLite::removeAzulejo(unsigned int id)
{
    // O identificador é válido?
    if(id > Chien2DLite::maximoAzulejos || id == 0)
        return;
    // Só apaga se o número de usuários for um ou se estiver em shutdown
    if(azulejos[id-1].usuarios > 1 && !shutdownNow)
    {
        azulejos[id-1].usuarios = azulejos[id-1].usuarios - 1;
        return;
    }
    // Não tem mais usuários
    azulejos[id-1].usuarios = 0;
    // Tem uma surface SDL associada?
    if(this->azulejos[id-1].imagem != 0)
    {
        // Apaga a surface
        SDL_FreeSurface(this->azulejos[id-1].imagem);
        // Associa um valor nulo para reutilizar depois
        this->azulejos[id-1].imagem = 0;
        // Só pra garantir
        this->azulejos[id-1].apelido = "";
    }
    // Se tem máscara de colisão, apaga
    if(this->azulejos[id-1].colisao32 != 0)
    {
        // Apaga as máscaras de cada azulejo
        int numAzulejos = this->azulejos[id-1].dimensaoMatrizAzulejo*this->azulejos[id-1].dimensaoMatrizAzulejo;
        for(int i=0;i<numAzulejos;i++)
            delete this->azulejos[id-1].colisao32[i];
        // apaga a máscara completa
        delete this->azulejos[id-1].colisao32;
        // Prepara para o próximo uso
        this->azulejos[id-1].colisao32=0;
    }
}

//     Elimina um azulejo da memória. Versão que recebe o apelido. Se o 
// azulejo não existir, ignora e não faz nada. Ao remover o azulejo, além de 
// remover a imagem da memória, prepara a posição na lista para uso futuro.
//
// Data: 25/12/2004
// Última atualização: 25/12/2004
//

void Chien2DLite::removeAzulejo(string apelido)
{
    // Procura o azulejo que seja indicado pelo apelido
    unsigned int idx = pegaAzulejo(apelido);
    // Verifica se é válido o identificador e apaga
    if(idx != 0)
        removeAzulejo(idx);
}


//     Recebe o identificador do azulejo, o índice do azulejo e as coordenadas 
// x,y para desenhar na tela. Retorna false se o azulejo não existe e true se 
// desenhou. Numa segunda versão, recebe ainda as cores no formato RGBA para 
// desenhar o mesmo com efeito.
//
// Data: 26/12/2004
// Última atualização: 26/12/2004*/

bool Chien2DLite::desenhaAzulejo(unsigned int identificador, unsigned int indice,
                int x, int y)
{
    // Tem que existir a imagem
    if(!this->azulejos[identificador-1].imagem)
        return false;
    
    // Seleciona o azulejo que vai desenhar
    Azulejo *azulejo = &(azulejos[identificador-1]);
    
    // Tamanho em pixels do azulejo
    int tamPixels = azulejo->dimensaoAzulejo;
    // Posiçao na textura do canto esquerdo superior
//    double posx= (indice%(azulejo->dimensaoMatrizAzulejo))*tamAzulejo ;
//    double posy= (indice/(azulejo->dimensaoMatrizAzulejo))*tamAzulejo ;
    // Define os rects para o blit
	SDL_Rect orig, dest;
 	dest.x = (Sint16)x;
	dest.y = (Sint16)y;
	dest.w = tamPixels;
	dest.h = tamPixels;
	orig.x = (indice%azulejo->dimensaoMatrizAzulejo)*tamPixels;
	orig.y = (indice/azulejo->dimensaoMatrizAzulejo)*tamPixels;
	orig.w = tamPixels;
	orig.h = tamPixels;
	SDL_BlitSurface(azulejo->imagem, &orig, screen, &dest);


    return true;
}

// Verifica se dois azulejos colidiram nas coordenadas indicadas
//    Identificador indica o azulejo no sistema, indice a porção do
// azulejo e (x,y) as coordenadas INTEIRAS na tela (não existe colisão
// subpixel).
//
// Data: 29/01/2005
// Última atualização: 29/01/2005
bool Chien2DLite::colidiuAzulejos(int identificador1, int indice1, int x1, int y1, 
            int identificador2, int indice2, int x2, int y2)
{
    // Tem que estar na memória os azulejos
    if(this->azulejos[identificador1-1].imagem==0 || this->azulejos[identificador2-1].imagem==0)
        return false;
    // Os índices são válidos?
    if(indice1 > this->azulejos[identificador1-1].dimensaoMatrizAzulejo*this->azulejos[identificador1-1].dimensaoMatrizAzulejo
        || indice2 > this->azulejos[identificador2-1].dimensaoMatrizAzulejo*this->azulejos[identificador2-1].dimensaoMatrizAzulejo)
        return false;
    // Recupera as diferenças em pontos e verifica se os quadrados se interceptam
    int dx=abs(x1-x2);
    int dy=abs(y1-y2);
    // Recupera as máscaras de colisão dos azulejos
    Uint32 *colisao1 = this->azulejos[identificador1-1].colisao32[indice1];
    Uint32 *colisao2 = this->azulejos[identificador2-1].colisao32[indice2];            
    
    if(dx<32 && dy<32)
    {
		// Verifica a colisão em si
		for(int y=0;y<32-dy;y++)
		{
   			Uint32 cima,baixo;
   			// Se o primeiro azulejo está acima do segundo
			if(y1<y2)
			{
				// O sprite mais acima deve ser pego a partir da linha y+dy
				cima=colisao1[y+dy];
				// O sprite abaixo é pego a partir da linha y
				baixo=colisao2[y];
				// O mais a esquerda deve ser rotacionado dx bits à esquerda
				if(x1<x2)
					cima = cima << dx;
				else
					baixo = baixo << dx;
			}
			else
			{
				// O sprite mais acima deve ser pego a partir da linha y+dy
				cima=colisao2[y+dy];
				// O sprite abaixo é pego a partir da linha y
				baixo=colisao1[y];
				// O mais à esquerda deve ser rotacionado dx bits a esquerda
				if(x1>x2)
					baixo = baixo << dx;
				else
					cima = cima << dx;
			}
            // Se for verdade é porque colidiu
			if(cima & baixo)
				return true;
		}
    }    
    return false;
}


// Métodos para desenhar pontos

//     Desenha os pontos indicados na lista de coordenadas passadas, com a cor
// especificada. A variável numPoints indica o número de pontos a desenhar.
//
// Data: 09/01/2005
// Última atualização: 09/01/2005

void Chien2DLite::desenhaPontos(int *x, int *y, int size, int r, int g, int b, 
                int numPoints)
{
 // To do ...
}


// Métodos para manipular fontes do sistema

//     Carrega uma fonte, utilizando para isto um Azulejo de dimensão 16x16 
// (azulejos, não pontos) com as letras. Recebe o nome do arquivo e o apelido 
// da Fonte. Pode utilizar uma das quatro resoluções válidas do sistema, 8x8, 
// 16x16, 32x32 e 64x64. Ao carregar a fonte, o método preenche para todas as 
// letras as informações relativas ao offset do primeiro pixel não transparente 
// da imagem na vertical e a largura da letra (do primeiro até o último pixel 
// não transparente). Retorna o identificador da fonte ou 0 se não conseguiu 
// carregar/alocar.
//
// Este método determina automaticamente o tipo da fonte!!
//
// Data: 30/12/2004
// Última atualização: 26/11/2005

unsigned int Chien2DLite::carregaFonte(string arquivo, string apelido, int tipoFonte)
{
    // Verifica se a fonte existe
    unsigned int idx = pegaFonte(apelido);
    // Se já existe uma fonte com o apelido, retorna o índice associado
    if(idx != 0)
    {
        fontes[idx-1].usuarios = fontes[idx-1].usuarios+1;
        return idx;
    }
        
    // Se não existe, procura o primeiro índice vago (idx ainda é igual a 0)
    for(int i=0;i<Chien2DLite::maximoFontes;i++)
        // A fonte é vaga (não tem imagem associada?
        if(this->fontes[i].idAzulejo == 0)
        {
            idx=i+1;
            break;
        }
    
    // ATENÇÃO: não ter espaço na memória não é relacionado a este teste. Apenas
    // testa-se aqui se existe um índice vago na lista. Se não existe, idx==0
    if(idx==0)
        // Retorna um índice inválido para indicar que o método falhou
        return 0;
    
    // Se chegou até aqui, idx contém o identificador correto 
    // posição no array (sem incrementar 1)
    idx=idx-1;    

    // Indica o apelido
    this->fontes[idx].apelido = apelido;
    
    // Carrega o azulejo, de acordo com o tipo de fonte recebida
    // No mesmo passo, indica o tamanho em pontos da fonte
    switch(tipoFonte)
    {
        // FOnte tamanho 8
        case Chien2DLite::fonte8:
            this->fontes[idx].tamanhoFonte=8;
            this->fontes[idx].idAzulejo = this->carregaAzulejo(arquivo, apelido, Chien2DLite::azulejo8);
            break;
        // Fonte tamanho 16
        case Chien2DLite::fonte16:
            this->fontes[idx].tamanhoFonte=16;
            this->fontes[idx].idAzulejo = this->carregaAzulejo(arquivo, apelido, Chien2DLite::azulejo16);
            break;
        // Fonte tamanho 32
        case Chien2DLite::fonte32:
            this->fontes[idx].tamanhoFonte=32;
            this->fontes[idx].idAzulejo = this->carregaAzulejo(arquivo, apelido, Chien2DLite::azulejo32);
            break;
        // Fonte tamanho 64
        case Chien2DLite::fonte64:
            this->fontes[idx].tamanhoFonte=64;
            this->fontes[idx].idAzulejo = this->carregaAzulejo(arquivo, apelido, Chien2DLite::azulejo64);
            break;
        // Se não for nenhuma das outras alternativas, é pau! 
        default:
            this->fontes[idx].apelido = "";
            return 0;
    }
    // Conseguiu carregar o azulejo? Se for inválido, retorna 0
    if(this->fontes[idx].idAzulejo == 0)
    {
        this->fontes[idx].apelido = "";        
        return 0;
    }
    
    // Preenche os deslocamentos
    for(int linha=0;linha<16;linha++)
        for(int coluna=0;coluna<16;coluna++)
        {           
            // Procura a primeira coluna com pixels não transparentes
            
            // A primeira coluna com pixel não transparente
            int primeira=-1;
            // Para todas as colunas e linhas da fonte...
            SDL_LockSurface(this->azulejos[this->fontes[idx].idAzulejo-1].imagem);
            for(int x=0;x<this->fontes[idx].tamanhoFonte;x++)
            {
                for(int y=0;y<this->fontes[idx].tamanhoFonte;y++)
                if(!pontoTransparente(this->azulejos[this->fontes[idx].idAzulejo-1].imagem, 
                    x+coluna*this->fontes[idx].tamanhoFonte, 
                    y+linha*this->fontes[idx].tamanhoFonte))
                {
                    primeira = x;
                    break;
                }
                // Deve parar o laço do x?
                if(primeira != -1)
                    break;
            }
            SDL_UnlockSurface(this->azulejos[this->fontes[idx].idAzulejo-1].imagem);
            // Achou uma coluna não transparente?
            if(primeira >= 0)
                    this->fontes[idx].deslocamentos[linha*16+coluna] = primeira;
            else
            {
                // A letra é toda transparente, pega o máximo de largura e deslocamento 0
                this->fontes[idx].larguras[linha*16+coluna] = this->fontes[idx].tamanhoFonte;
                this->fontes[idx].deslocamentos[linha*16+coluna] = 0;
                // Pula para a próxima letra
                continue;
            }
            
            // Agora procura a primeira coluna com todos os pontos transparntes
            // (executa só se há uma coluna transparente, vide else anterior)

            // Para todas as colunas e linhas da fonte...
            int ultima=-1;
            // Indica que todos os pontos na coluna são transparentes
            bool todosBrancos;
            SDL_LockSurface(this->azulejos[this->fontes[idx].idAzulejo-1].imagem);
            for(int x=primeira+1;x<this->fontes[idx].tamanhoFonte;x++)
            {
                // Todos os pontos são transparentes até prova contrária
                todosBrancos = true;
                for(int y=0;y<this->fontes[idx].tamanhoFonte;y++)
                if(!pontoTransparente(this->azulejos[this->fontes[idx].idAzulejo-1].imagem, 
                    x+coluna*this->fontes[idx].tamanhoFonte, 
                    y+linha*this->fontes[idx].tamanhoFonte))
                {
                    todosBrancos = false;
                    break;
                }
                // Deve parar o laço do x?
                if(todosBrancos)
                {
                    ultima=x;
                    break;
                }
            }
            SDL_UnlockSurface(this->azulejos[this->fontes[idx].idAzulejo-1].imagem);
            // Achou uma coluna transparente?
            if(ultima >= 0)
            {
                // Adiciona um pouco à largura, de acordo com o tamanho da fonte
                switch(this->fontes[idx].tamanhoFonte)
                {
                    case 8:
                        ultima+=1;
                        break;
                    case 16:
                        ultima+=1;
                        break;
                    case 32:
                        ultima+=2;
                        break;
                    case 64:
                        ultima+=3;
                        break;
                }
                // Testa se não saiu fora da fonte
                if(ultima <= this->fontes[idx].tamanhoFonte)
                    this->fontes[idx].larguras[linha*16+coluna] = ultima - primeira;
                else
                    // Se saiu fora da fonte, volta pra dentro. Pode ser que não sobre espaço
                    this->fontes[idx].larguras[linha*16+coluna] = this->fontes[idx].tamanhoFonte - primeira;
            }
            else
                this->fontes[idx].larguras[linha*16+coluna] = this->fontes[idx].tamanhoFonte - primeira;          
        }
    // Deixa o espaço como metade do tamanho da fonte
    this->fontes[idx].larguras[' '] = this->fontes[idx].tamanhoFonte / 2;
    this->fontes[idx].deslocamentos[' '] = 0;    
    // Indica que tem um usuário
    fontes[idx].usuarios = 1;
    return idx+1;
    
}


//     Remove uma fonte do sistema através do identificador.
//
// Data: 30/12/2004
// Última atualização: 26/11/2005

void Chien2DLite::removeFonte(unsigned int id)
{
    // Está na faixa esperada para remover?
    if(id > Chien2DLite::maximoFontes || id==0)
        return;
    // Só remove se existe apenas um usuário da fonte ou se estiver em shutdown
    if(fontes[id-1].usuarios > 1 && !shutdownNow)
    {
        fontes[id-1].usuarios = fontes[id-1].usuarios-1;
        return;
    }
        
    if(this->fontes[id-1].idAzulejo != 0)
    {
        this->removeAzulejo(this->fontes[id-1].idAzulejo);
        this->fontes[id-1].idAzulejo = 0;
        this->fontes[id-1].apelido = "";
    }
    fontes[id-1].usuarios = 0;
}

//     Remove uma fonte do sistema através do apelido.
//
// Data: 30/12/2004
// Última atualização: 30/12/2004

void Chien2DLite::removeFonte(string apelido)
{
    // Procura o azulejo que seja indicado pelo apelido
    unsigned int idx = pegaFonte(apelido);
    // Verifica se é válido o identificador e apaga
    if(idx != 0)
        removeFonte(idx);
    
}

//     Recebe uma string com o nome da fonte e retorna o identificador da fonte.
// Retorna 0 se a fonte não existe, caso contrário, retorna o identificador.
//
// Data: 30/12/2004
// Última atualização: 30/12/2004

unsigned int Chien2DLite::pegaFonte(string apelido)
{
    for(int i=0;i<Chien2DLite::maximoFontes;i++)
        if(this->fontes[i].apelido == apelido && this->fontes[i].idAzulejo!=0)
        {
            // O índice é a posição atual + 1
            return i+1;
        }
    return 0;
}

//     Recebe uma string, um identificador de fonte, uma coordenada x,y inicial,
// uma largura máxima para o texto e o alinhamento. Se a fonte existe e o texto
// cabe na largura indicada, faz o desenho e retorna true. Caso contrário,
// retorna false.
//
// Data: 03/01/2005
// Última atualização: 05/01/2005
//

bool Chien2DLite::desenhaTexto(string texto, unsigned int idFonte, int x, 
    int y, int largura, int alinhamento)
{
    // A fonte existe?
    if(idFonte > Chien2DLite::maximoFontes || idFonte ==0)
        return false;
    // A largura real do texto
    int larguraReal, alturaReal;

    if(!dimensoesTexto(texto, idFonte, &larguraReal, &alturaReal))
    {
        cout << "Falhou ao procurar as dimensões." << endl;
        return false;
    }
    if(larguraReal > largura)
    {
        cout << "Falhou porque é mais largo que a tela." << endl;
        return false;
    }

    // Pega a fonte para acesso local
    Fonte *fonte = &(this->fontes[idFonte-1]);
    
    // Desenha de acordo com o alinhamento
    switch(alinhamento)
    {
        case Chien2DLite::textoJustificado:
        {
            // Começa a desenhar a partir da coordenada x-deslocamento da primeira imagem
            int posicao = x;
            // Quantos pontos compensa ao desenhar a fonte
            int compensa = 0;
            if(texto.size() > 1)
                compensa = largura - larguraReal;
            for(int i=0;i<texto.length();i++)
            {   
                this->desenhaAzulejo(fonte->idAzulejo, (unsigned char)(texto[i]), posicao - fonte->deslocamentos[(unsigned char)(texto[i])], y);
                // Atualiza para a próxima letra
                posicao+=fonte->larguras[(unsigned char)(texto[i])] + compensa/(texto.length()-i);
                compensa-=compensa/(texto.length()-i);
            }
            break;
        }

        case Chien2DLite::textoCentralizado:
        {
            // Começa a desenhar a partir da coordenada x-deslocamento da primeira imagem
            int posicao = x + (largura - larguraReal)/2;
            for(int i=0;i<texto.length();i++)
            {   
                this->desenhaAzulejo(fonte->idAzulejo, (unsigned char)(texto[i]), posicao - fonte->deslocamentos[(unsigned char)(texto[i])], y);
                // Atualiza para a próxima letra
                posicao+=fonte->larguras[(unsigned char)(texto[i])];
            }
            break;
        }

        case Chien2DLite::textoDireita:
        {
            // Começa a desenhar a partir da coordenada x-deslocamento da primeira imagem
            int posicao = x + largura - larguraReal;
            for(int i=0;i<texto.length();i++)
            {   
                this->desenhaAzulejo(fonte->idAzulejo, (unsigned char)(texto[i]), posicao - fonte->deslocamentos[(unsigned char)(texto[i])], y);
                // Atualiza para a próxima letra
                posicao+=fonte->larguras[(unsigned char)(texto[i])];
            }
            break;
        }

        case Chien2DLite::textoEsquerda:
        default:
        {
            // Começa a desenhar a partir da coordenada x-deslocamento da primeira imagem
            int posicao = x;
            for(int i=0;i<texto.length();i++)
            {   
                this->desenhaAzulejo(fonte->idAzulejo, (unsigned char)(texto[i]), posicao - fonte->deslocamentos[(unsigned char)(texto[i])], y);
                // Atualiza para a próxima letra
                posicao+=fonte->larguras[(unsigned char)(texto[i])];
            }
            break;
        }
    }    
    return true;
}

//     Recebe uma string, um identificador de fonte, e ponteiros para dimensões 
// x e y do bounding box do texto. Retorna true se calculou as dimensões, ou
// false se a fonte não existe.

bool Chien2DLite::dimensoesTexto(string texto, unsigned int idFonte, int *largura, int *altura)
{
    // A fonte existe?
    if(idFonte > Chien2DLite::maximoFontes || idFonte == 0)
        return false;
    Fonte *fonte = &(this->fontes[idFonte-1]);
    if(fonte->idAzulejo != 0)
    {
        //  Pega a altura
        *altura=fonte->tamanhoFonte;
        // Largura local
        int larg=0;
        // Calcula o tamanho
        for(int i =0;i<texto.length();i++)
            larg+=fonte->larguras[(unsigned char)(texto[i])];
        // PAssa o valor
        *largura=larg;
        return true;
    }
    return false;
}

// Métodos auxiliares para a OpenGL


//   Método para limpar a tela. Limpa a tela com a cor de fundo atual e retorna.
//
// Data: 26/12/2004
// Última atualização: 26/12/2004
//

void Chien2DLite::limpaTela()
{
 // Faz um blit com tela preta
 SDL_FillRect(screen, NULL, 0);
}

//    Método para trocar os buffers e mostrar a imagem desenhada
//
// Data: 26/12/2004
// Última atualização: 26/12/2004
//

void Chien2DLite::sincroniza()
{
    // Troca os buffers
    SDL_Flip(screen);
}

//
// Métodos específicos da versão SDL
//
//

bool Chien2DLite::pontoTransparente(SDL_Surface *surface, int x, int y)
{
    // Quantos bytes tem por pixel a imagem
    int bpp = surface->format->BytesPerPixel;
    // Endereço do ponto a recuperar
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
    // Só funciona em imagens com 32 bits e canal de alfa
    Uint32 cor = *(Uint32 *)p;
    if(cor != SDL_MapRGB(surface->format, 255, 0, 255))
        return false;
    else
        return true;
    
    return false;
}
