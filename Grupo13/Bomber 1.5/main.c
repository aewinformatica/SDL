/*
    Programadores: Wander Mendonça Soares,Thiago Sangiacomo Masello e Carolina Szkruc de Carvalho.
    DRE:                  107414706              107391398                     107413394
    Programa: jogo Principal.
    Descrição: projeto final.
    Data:Desde o primeiro dia da liberação até 08/07/08.
*/


/* Estados retornados
  -1 - Erro ao inicializar a biblioteca SDL_ttf.
   1 - Erro ao carregar a superficie do bloco indestrutível.
   2 - Erro ao carregar a superficie do inimigo.
   3 - Erro ao carregar a superficie do heroi.
   4 - Erro ao carregar a superficie do bloco destrutivel.
   5 - Erro ao carregar a tela.
   6 - Erro ao carregar a superficie da bomba.

*/


/* Estados da matriz pos_proib

    0 - Espaço em branco.
    1 - Espaço com blocos indestrutíveis
    2 - Espaço com o herói.
    3 - Espaço em branco reservados para garantir que haja movimentação.
    4 - inimigos.
    5 - Blocos destrutíveis.
*/

/* Estados da variável mov -> variável para saber a ultima direção do heroi

    0 - Nenhum.
    1 - Esquerda.
    2 - Direita.
    3 - Cima.
    4 - Baixo.

*/

/* Estados da variavel sort -> Sorteio da direção do inimigo

    0 - direita.
    1 - esquerda.
    2 - baixo.
    3 - cima.
*/

/* Estado da variavel dir[]//guarda a direção atual do inimigo.
    1 - direita.
    2 - esquerda.
    3 - baixo.
    4 - cima.

*/



#pragma comment(lib,"SDL.lib")
#pragma comment(lib,"SDLmain.lib")
#pragma comment(lib,"SDL_ttf.lib")

#include <SDL.h>
#include <SDL_ttf.h>
#include <time.h>
#include <math.h>


#define LARGURA_TELA 800
#define ALTURA_TELA 600
#define TAM_RECT 25 /*cada elemento da grade terá esse tamanho, neste caso (25x25) -> que toda imagem carregada deve ter essa dimensão*/
#define NUM_INIMIGOS1 5/*Número máximo de inimigos1*/
#define PONTOS_CAIXA 100
#define PONTOS_INI 400
#define TAMANHO_FONTE 18


SDL_Surface* superfBlocoInd;
SDL_Surface* superfInimigo1;
SDL_Surface* superfheroi;

SDL_Surface* superfBlocoDest;
SDL_Surface* superfBomba;
SDL_Surface* screen;


SDL_Rect pos_heroi;
SDL_Rect pos_inimigo1[NUM_INIMIGOS1];
SDL_Rect pos_bomba;
SDL_Rect spriteheroi = {0,0 , 25, 25};

TTF_Font* fonte;


int w=0,e=0,z;//variáveis de controle
int mov_inim[NUM_INIMIGOS1];//Diz se um inimigo está em movimento ou não 1/0.
int dir[NUM_INIMIGOS1];//variavel para saber que direção o inimigo tomou.
int vida_ini[NUM_INIMIGOS1];
int vida_heroi=1;

int pos_proib[LARGURA_TELA][ALTURA_TELA];

//Variáveis de controle das teclas.
int teclaEsq=0;
int teclaDir=0;
int teclaCima=0;
int teclaBaixo=0;
int teclaEsp=0;

//variáveis auxiliares
int incx=1,incy=1,num_bombas=0,pontos;
unsigned int tempo_bomba = 0;

//funções
void desenha_texto(char* texto, SDL_Surface* dst, int x, int y);//Função do Bruno(monitor)
void zere_vet(int vet[],int tam);
void zere_mat(int max_w,int max_h,int mat[LARGURA_TELA][ALTURA_TELA]);
void um_vet(int vet[],int tam);
void desenhe_borda (int max_w,int max_h,int tam,SDL_Surface *tela,SDL_Surface *dist_rectbmp);
void desenhe_fase1(int max_w,int max_h,int tam,SDL_Surface *tela,SDL_Surface *superfrect);
void carregue_personagens (int max_w,int max_h,int tam,SDL_Surface *tela,SDL_Surface *superfrect,SDL_Surface *superfrect2,int num_inim);
void carregue_blockDest (int max_w,int max_h,int tam,SDL_Surface *tela,SDL_Surface *superfrect);
int teste_colisao(SDL_Rect personagem,int tam,int mov);
int teste_colisao_inim(int dir,int j,SDL_Rect pos_inimigo, int tam);
void mova_personagens(int tam,int mov);
void solte_bomba(int explodiu);
void exploda_bomba(int explodiu,int tam);



int main(int argc, char** argv)
{

    SDL_Event evento;
    Uint32 cor_fundo;
    int quit = 0;
    int mov=0,explodiu=1;
    unsigned int tempo_jogo;

    srand(time(NULL));
    tempo_jogo=SDL_GetTicks();
    SDL_Init(SDL_INIT_VIDEO);
    if(TTF_Init() == -1) return -1;

    superfBlocoInd = SDL_LoadBMP("./imagens/blocoInd.bmp");
    if(!(superfBlocoInd)) return 1;
    superfInimigo1 = SDL_LoadBMP("./imagens/inimigo.bmp");
    if(!(superfInimigo1)) return 2;
    superfheroi = SDL_LoadBMP("./imagens/spriteheroi2.bmp");
    if(!(superfheroi)) return 3;
    superfBlocoDest = SDL_LoadBMP("./imagens/blocoDest.bmp");
    if(!(superfBlocoDest)) return 4;
    superfBomba = SDL_LoadBMP("./imagens/bomba.bmp");
    if(!(superfBomba)) return 6;
    screen = SDL_SetVideoMode(LARGURA_TELA, ALTURA_TELA, 16, SDL_SWSURFACE);
    if(!(screen)) return 5;

    fonte = TTF_OpenFont("./fontes/Caligula.ttf", TAMANHO_FONTE);
    if(!(fonte)) return 10;

    SDL_SetColorKey(superfBlocoInd, SDL_SRCCOLORKEY, SDL_MapRGB(superfBlocoInd->format,0, 0,0));
    SDL_SetColorKey(superfInimigo1, SDL_SRCCOLORKEY, SDL_MapRGB(superfInimigo1->format, 0, 0,0));
    SDL_SetColorKey(superfheroi, SDL_SRCCOLORKEY, SDL_MapRGB(superfheroi->format, 16, 16, 16));
    SDL_SetColorKey(superfBlocoDest, SDL_SRCCOLORKEY, SDL_MapRGB(superfBlocoDest->format, 0, 0, 0));
    SDL_SetColorKey(superfBomba, SDL_SRCCOLORKEY, SDL_MapRGB(superfBomba->format, 255, 255, 255));

    cor_fundo = SDL_MapRGB(screen->format,22,103,0);

    zere_mat(LARGURA_TELA,ALTURA_TELA,pos_proib);
    zere_vet(mov_inim,NUM_INIMIGOS1);
    zere_vet(dir,NUM_INIMIGOS1);
    um_vet(vida_ini,NUM_INIMIGOS1);
    while(!quit)
    {
        while(SDL_PollEvent(&evento))
        {
               switch(evento.type)

                {
                    case SDL_QUIT:

                    quit = 1;
                    break;

                    //verificação do estado das teclas.
                    case SDL_KEYDOWN:

                    if (evento.key.keysym.sym ==  SDLK_LEFT)
                    {
                        teclaEsq=1;
                        mov=1;
                    }
                    else if (evento.key.keysym.sym ==  SDLK_RIGHT)
                    {
                        teclaDir=1;
                        mov=2;
                    }

                    else if (evento.key.keysym.sym ==  SDLK_UP)
                    {
                        teclaCima=1;
                        mov=3;
                    }

                    else if (evento.key.keysym.sym ==  SDLK_DOWN)
                    {
                        teclaBaixo=1;
                        mov=4;
                    }
                    else if (evento.key.keysym.sym == SDLK_SPACE)
                    {
                        teclaEsp=1;
                    }
                    else
                    {
                        mov=0;
                    }
                    break;

                    case SDL_KEYUP:
                    if (evento.key.keysym.sym ==  SDLK_LEFT)  teclaEsq=0;
                    if (evento.key.keysym.sym ==  SDLK_RIGHT) teclaDir=0;
                    if (evento.key.keysym.sym ==  SDLK_UP)    teclaCima=0;
                    if (evento.key.keysym.sym ==  SDLK_DOWN)  teclaBaixo=0;
                    if (evento.key.keysym.sym ==  SDLK_SPACE) teclaEsp=0;
                    break;
                }

            }
            desenhe_borda(LARGURA_TELA,ALTURA_TELA,TAM_RECT,screen,superfBlocoInd);
            desenhe_fase1(LARGURA_TELA,ALTURA_TELA,TAM_RECT,screen,superfBlocoInd);
            if (w < 1)
            {

                 carregue_personagens(LARGURA_TELA,ALTURA_TELA,TAM_RECT,screen,superfheroi,superfInimigo1,NUM_INIMIGOS1);
                 w++;
            }
            else
            {
                mova_personagens(TAM_RECT,mov);
                solte_bomba(explodiu);

                if(vida_heroi>0)
                {
                    SDL_BlitSurface(superfheroi, &spriteheroi, screen, &pos_heroi);
                }

                if (SDL_GetTicks()<tempo_bomba+3000)//Se não se passaram 3 segundos...
                {
                    SDL_BlitSurface(superfBomba, NULL, screen,&pos_bomba);
                }
                else
                {

                    exploda_bomba(explodiu,TAM_RECT);
                }


                for(z=0;z<NUM_INIMIGOS1;z++)
                {
                    if(vida_ini[z]>0)
                    {
                        SDL_BlitSurface(superfInimigo1, NULL, screen,&pos_inimigo1[z]);
                    }
                }



            }

            carregue_blockDest (LARGURA_TELA,ALTURA_TELA,TAM_RECT,screen,superfBlocoDest);
            desenha_texto("Tempo: ",screen, 3, 3);
            SDL_Flip(screen);
            SDL_FillRect(screen, NULL,cor_fundo);
            SDL_Delay(10);
        }

        SDL_FreeSurface(superfBlocoDest);
        SDL_FreeSurface(superfBlocoInd);
        SDL_FreeSurface(superfBomba);
        SDL_FreeSurface(superfheroi);
        SDL_FreeSurface(superfInimigo1);
        TTF_CloseFont(fonte);

        TTF_Quit();
        SDL_Quit();

        return 0;
}

void zere_mat(int max_w,int max_h,int mat[LARGURA_TELA][ALTURA_TELA])
{
    int i,j;

    for(i=0;i<max_w;i++)
    {
        for(j=0;j<max_h;j++)
        {
            mat[i][j]=0;

        }
    }
}

void zere_vet(int vet[],int tam)
{
    int i;
    for(i=0;i<tam;i++)
    {
        vet[i]=0;
    }
}
void um_vet(int vet[],int tam)
{
    int i;

    for(i=0;i<NUM_INIMIGOS1;i++)
    {
        vet[i]=1;
    }
}
void desenhe_borda(int max_w,int max_h,int tam,SDL_Surface *tela,SDL_Surface *superfrect)
{

        int i;
        for(i=0;i<max_w;i++)//parede esquerda e parede direita
        {
            SDL_Rect dist_rectbmp={i,0,0,0}; //define onde ficará a "moldura" do retangulo.
            SDL_BlitSurface(superfrect, NULL, tela, &dist_rectbmp); //carrega o retangulo na tela.

            pos_proib[i][0]=1;

            dist_rectbmp.x= i;
            dist_rectbmp.y= max_h-tam;
            SDL_BlitSurface(superfrect, NULL, tela, &dist_rectbmp);

            pos_proib[i][max_h-tam]=1;

            i=i+tam-1;
        }

        for(i=0;i<max_h;i++)//parede de cima e parede de baixo
        {
            SDL_Rect dist_rectbmp={0,i,0,0};
            SDL_BlitSurface(superfrect, NULL, tela, &dist_rectbmp);

            pos_proib[0][i]=1;

            dist_rectbmp.x= max_w-tam;
            dist_rectbmp.y= i;
            SDL_BlitSurface(superfrect, NULL, tela, &dist_rectbmp);

            pos_proib[max_w-tam][i]=1;

            i=i+tam-1;
        }

}

void desenhe_fase1(int max_w,int max_h,int tam,SDL_Surface *tela,SDL_Surface *superfrect)
{

        int i,j;

        for (i=tam*2;i<max_h-2*tam;i=i+tam*2)//carrega o bloco, célula sim célula não
        {
            for(j=tam*2;j<max_w-2*tam;j=j+tam*2)
            {
                SDL_Rect dist_rectbmp={j,i,0,0};
                SDL_BlitSurface(superfrect, NULL, tela, &dist_rectbmp);
                pos_proib[j][i]=1;
            }

        }

}
void carregue_blockDest (int max_w,int max_h,int tam,SDL_Surface *tela,SDL_Surface *superfrect)
{
    int i,j;

    for (i=0;i<max_w;i=i+tam)
    {
        for(j=0;j<max_h;j=j+tam)
        {
            if(!(pos_proib[i][j]))
            {
                SDL_Rect dist_rectbmp={i,j,0,0};
                SDL_BlitSurface(superfrect, NULL, tela, &dist_rectbmp);
                pos_proib[i][j]=0;
            }

        }
    }

}
void carregue_personagens(int max_w,int max_h,int tam,SDL_Surface *tela,SDL_Surface *superfrect,SDL_Surface *superfrect2,int num_inim)
{

    int n=0,teste;
    int x,y,xp,yp;

    while(n<=num_inim)
    {

        teste=0;

        x=rand()%max_w;
        y=rand()%max_h;

        while(x%tam!=0)//garante que o número randomizado seja múltiplo do tamanho da célula,neste caso 25
        {
            x = rand()%max_w;
        }

        while((y%tam)!=0)//idem
        {
            y= rand()%max_h;
        }

        if (n==0)//se n=0 estamos tratando o carregamento do herói
        {
            if(!(pos_proib[x][y]))
            {
                        teste=1;

                        xp=x;
                        yp=y;
                        pos_proib[x][y]=2;

                        pos_proib[x+tam][y]=3;
                        pos_proib[x-tam][y]=3;
                        pos_proib[x][y+tam]=3;
                        pos_proib[x][y-tam]=3;

                        pos_proib[x+2*tam][y]=3;
                        pos_proib[x-2*tam][y]=3;
                        pos_proib[x][y+2*tam]=3;
                        pos_proib[x][y-2*tam]=3;
                        pos_heroi.x=x;
                        pos_heroi.y=y;

                        SDL_BlitSurface(superfrect, NULL, tela, &pos_heroi);

            }

        }
        else// se n!= 0 estamos tratando os inimigos
        {

            if((!(pos_proib[x][y]))&&((sqrt(pow((x-xp),2)+pow((y-yp),2)))>3*tam))
            {

                        teste=1;

                        pos_proib[x][y]=4;

                        pos_proib[x+tam][y]=3;
                        pos_proib[x-tam][y]=3;
                        pos_proib[x][y+tam]=3;
                        pos_proib[x][y-tam]=3;

                        pos_inimigo1[n-1].x=x;
                        pos_inimigo1[n-1].y=y;

                        SDL_BlitSurface(superfrect2, NULL, tela, &pos_inimigo1[n-1]);


            }

        }

        if(teste==1)
        {
            n++;
        }

    }


}

void mova_personagens(int tam,int mov)

{

        int sort,j;

        sort=rand()%4;

        //movimentação dos inimigos
        for(j=0;j<NUM_INIMIGOS1;j++)
        {
            if((sort==0)&&(!(mov_inim[j])))
            {
                dir[j]=1;
                if(teste_colisao_inim(dir[j],j,pos_inimigo1[j],TAM_RECT)!=1)
                {
                    pos_proib[pos_inimigo1[j].x][pos_inimigo1[j].y]=3;
                    pos_inimigo1[j].x+=incx;
                    pos_proib[pos_inimigo1[j].x][pos_inimigo1[j].y]=4;
                    mov_inim[j]=1;
                }
            }
            else if((sort==1)&&(!(mov_inim[j])))
            {
                dir[j]=2;
                if(teste_colisao_inim(dir[j],j,pos_inimigo1[j],TAM_RECT)!=2)
                {

                    pos_proib[pos_inimigo1[j].x][pos_inimigo1[j].y]=3;
                    pos_inimigo1[j].x-=incx;
                    pos_proib[pos_inimigo1[j].x][pos_inimigo1[j].y]=4;
                    mov_inim[j]=1;
                }
            }
            else if((sort==2)&&(!(mov_inim[j])))
            {
                dir[j]=3;
                if(teste_colisao_inim(dir[j],j,pos_inimigo1[j],TAM_RECT)!=3)
                {
                    pos_proib[pos_inimigo1[j].x][pos_inimigo1[j].y]=3;
                    pos_inimigo1[j].y+=incy;
                    pos_proib[pos_inimigo1[j].x][pos_inimigo1[j].y]=4;
                    mov_inim[j]=1;
                }
            }
            else if((sort==3)&&(!(mov_inim[j])))
            {
                dir[j]=4;
                if(teste_colisao_inim(dir[j],j,pos_inimigo1[j],NUM_INIMIGOS1)!=4)
                {
                    pos_proib[pos_inimigo1[j].x][pos_inimigo1[j].y]=3;
                    pos_inimigo1[j].y-=incy;
                    pos_proib[pos_inimigo1[j].x][pos_inimigo1[j].y]=4;
                    mov_inim[j]=1;
                }
            }

            //mov para grade
            else if(((pos_inimigo1[j].y%tam!=0))&&(dir[j]==3)&&(mov_inim[j]))
            {
                pos_proib[pos_inimigo1[j].x][pos_inimigo1[j].y]=3;
                pos_inimigo1[j].y+=incy;
                pos_proib[pos_inimigo1[j].x][pos_inimigo1[j].y]=4;
                if((pos_inimigo1[j].y%tam==0))
                {
                    mov_inim[j]=0;
                }

            }
            else if (((pos_inimigo1[j].y%tam!=0))&&(dir[j]==4)&&(mov_inim[j]))
            {
                pos_proib[pos_inimigo1[j].x][pos_inimigo1[j].y]=3;
                pos_inimigo1[j].y-=incy;
                pos_proib[pos_inimigo1[j].x][pos_inimigo1[j].y]=4;
                if((pos_inimigo1[j].y%tam==0))
                {
                    mov_inim[j]=0;
                }
            }
            else if(((pos_inimigo1[j].x%tam!=0))&&(dir[j]==1)&&(mov_inim[j]))
            {
                pos_proib[pos_inimigo1[j].x][pos_inimigo1[j].y]=3;
                pos_inimigo1[j].x+=incx;
                pos_proib[pos_inimigo1[j].x][pos_inimigo1[j].y]=4;
                if((pos_inimigo1[j].x%tam==0))
                {
                    mov_inim[j]=0;
                }

            }
            else if (((pos_inimigo1[j].x%tam!=0))&&(dir[j]==2)&&(mov_inim[j]))
            {
                pos_proib[pos_inimigo1[j].x][pos_inimigo1[j].y]=3;
                pos_inimigo1[j].x-=incx;
                pos_proib[pos_inimigo1[j].x][pos_inimigo1[j].y]=4;
                if((pos_inimigo1[j].x%tam==0))
                {
                    mov_inim[j]=0;
                }
            }

        }


        //mov do heroi
        if(teclaCima)
        {
            if((teste_colisao(pos_heroi,TAM_RECT,mov)==1))
            {
                pos_proib[pos_heroi.x][pos_heroi.y]=3;
                pos_heroi.y-=incy;
                pos_proib[pos_heroi.x][pos_heroi.y]=2;
            }


        }
        else if(teclaBaixo)
        {
            if((teste_colisao(pos_heroi,TAM_RECT,mov)==2))
            {
                pos_proib[pos_heroi.x][pos_heroi.y]=3;
                pos_heroi.y+=incy;
                pos_proib[pos_heroi.x][pos_heroi.y]=2;
            }

        }
		else if(teclaEsq)
        {
           if((teste_colisao(pos_heroi,TAM_RECT,mov)==3))
           {
                pos_proib[pos_heroi.x][pos_heroi.y]=3;
                pos_heroi.x-=incx;
                pos_proib[pos_heroi.x][pos_heroi.y]=2;

           }

        }
		else if(teclaDir)
        {
           if((teste_colisao(pos_heroi,TAM_RECT,mov)==4))
           {
                pos_proib[pos_heroi.x][pos_heroi.y]=3;
                pos_heroi.x+=incx;
                pos_proib[pos_heroi.x][pos_heroi.y]=2;
           }

        }

        //mov para grade
        else if(((pos_heroi.y%tam!=0))&&(mov==3))
        {
            pos_proib[pos_heroi.x][pos_heroi.y]=3;
            pos_heroi.y-=incy;
            pos_proib[pos_heroi.x][pos_heroi.y]=2;
        }
        else if((pos_heroi.y%tam!=0)&&(mov==4))
        {
            pos_proib[pos_heroi.x][pos_heroi.y]=3;
            pos_heroi.y+=incy;
            pos_proib[pos_heroi.x][pos_heroi.y]=2;
        }
        else if(((pos_heroi.x%tam!=0))&&(mov==1))
        {
           pos_proib[pos_heroi.x][pos_heroi.y]=3;
           pos_heroi.x-=incx;
           pos_proib[pos_heroi.x][pos_heroi.y]=2;

        }
        else if((pos_heroi.x%tam!=0)&&(mov==2))
        {
           pos_proib[pos_heroi.x][pos_heroi.y]=3;
           pos_heroi.x+=incx;
           pos_proib[pos_heroi.x][pos_heroi.y]=2;
        }

}

int teste_colisao(SDL_Rect personagem,int tam,int mov)
{

    if (teclaEsq)
    {
        if((pos_proib[(personagem.x-tam)][personagem.y]==3))
        {
            return 3;
        }

    }

    else if (teclaDir)
    {
        if((pos_proib[(personagem.x+tam)][personagem.y]==3))
        {
            return 4;
        }

    }
    else if (teclaCima)
    {
        if((pos_proib[(personagem.x)][personagem.y-tam])==3)
        {
            return 1;
        }

    }
    else if (teclaBaixo)
    {
        if((pos_proib[(personagem.x)][personagem.y+tam]==3))
        {
            return 2;
        }

    }
    return 0;
}

int teste_colisao_inim(int dir,int i,SDL_Rect pos_inimigo, int tam)
{
        int a=0;

        if ((dir==1)&&((pos_proib[pos_inimigo1[i].x+tam][pos_inimigo1[i].y])!=3))      a=1;

        else if ((dir==2)&&((pos_proib[pos_inimigo1[i].x-tam][pos_inimigo1[i].y])!=3)) a=2;

        else if ((dir==3)&&((pos_proib[pos_inimigo1[i].x][pos_inimigo1[i].y+tam]!=3))) a=3;

        else if ((dir==4)&&((pos_proib[pos_inimigo1[i].x][pos_inimigo1[i].y-tam]!=3))) a=4;

        else a=41;

        return (a);


}

void solte_bomba(int explodiu)
{

    if ((teclaEsp)&&(num_bombas<1))
    {

        num_bombas+=1;
        if(e<1)
        {
            pos_bomba=pos_heroi;
            tempo_bomba=SDL_GetTicks();
            e++;
        }
        explodiu=0;

    }


}

void exploda_bomba(int explodiu,int tam)
{
    if(!(teclaEsp))
    {
        if(pos_proib[pos_bomba.x][pos_bomba.y]!=1)
        {
            if((pos_proib[pos_bomba.x][pos_bomba.y]==2)&&(explodiu==0))
            {
                vida_heroi-=1;
                explodiu=1;
            }
            /*else if(pos_proib[pos_bomba.x][pos_bomba.y]==4)
            {
                //pos_proib[pos_bomba.x][pos_bomba.y]=3;
            }*/

            pos_proib[pos_bomba.x][pos_bomba.y]=3;
        }
        if(pos_proib[pos_bomba.x+tam][pos_bomba.y]!=1)
        {
            pontos+=PONTOS_CAIXA;
            pos_proib[pos_bomba.x+tam][pos_bomba.y]=3;
        }
        if(pos_proib[pos_bomba.x-tam][pos_bomba.y]!=1)
        {
            pontos+=PONTOS_CAIXA;
            pos_proib[pos_bomba.x-tam][pos_bomba.y]=3;
        }
        if(pos_proib[pos_bomba.x][pos_bomba.y+tam]!=1)
        {
            pontos+=PONTOS_CAIXA;
            pos_proib[pos_bomba.x][pos_bomba.y+tam]=3;
        }
        if(pos_proib[pos_bomba.x][pos_bomba.y-tam]!=1)
        {
            pontos+=PONTOS_CAIXA;
            pos_proib[pos_bomba.x][pos_bomba.y-tam]=3;
        }

    }
    else
    {
        e--;
        num_bombas-=1;
    }
}

void desenha_texto(char* texto, SDL_Surface* dst, int x, int y)
{
  SDL_Color cor = {255, 0, 0}; //vermelho
  SDL_Color cor_fundo = {255, 255, 255};
  SDL_Surface* src = TTF_RenderText_Shaded(fonte, texto, cor,cor_fundo);
  SDL_Rect dst_rect = {x, y, 0, 0};

  SDL_BlitSurface(src, NULL, dst, &dst_rect);

  SDL_FreeSurface(src);
}


