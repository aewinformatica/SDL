/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL/SDL.h>*/

#include <windows.h>

#include "trecorte.h"

TSurface screen;
TSurface fase,faseMask,back,marios;
TRecorte mario;

bool right,left,up,n;

void erro(const char *s,int i=0,int j=0,int k=0,int l=0){
    char msg[100];
    sprintf(msg,s,i,j,k,l);
    MessageBox(0,msg,"Error",MB_ICONHAND);
    free(msg);
}

void draw();

int main (int argc, char *argv[]){
    int done;

    /* Initialize SDL */
    if (SDL_Init (SDL_INIT_VIDEO) < 0){
        /*sprintf (msg, "Couldn't initialize SDL: %s\n", SDL_GetError ());
        MessageBox (0, msg, "Error", MB_ICONHAND); 
        free (msg);*/
        exit (1);
    }
    atexit (SDL_Quit);

    screen.setVideoMode();
    back.loadBMP("bmp/back.bmp");
    fase.loadBMP("bmp/fase.bmp");
    fase.transp(fase.rgb(255,224,176));
    faseMask.loadBMP("bmp/fase_mask.bmp");
    marios.loadBMP("bmp/mario_passos.bmp");
    marios.transp(marios.rgb(248,224,176));
    mario.definir(&marios,50,0);

    SDL_WM_SetCaption ("dr Mário Clone - Diogo_RBG - 25/04/2006", NULL);

    done = 0;
    //--- teclas mapeadas ---//
    bool alt=0,f4=0;
    
    while (!done){
        SDL_Event event;

        /* Check for events */
        while (SDL_PollEvent (&event)){
            switch (event.type){
            case SDL_KEYDOWN:
                if(event.key.keysym.sym == SDLK_RALT || event.key.keysym.sym == SDLK_LALT)
                    alt=1;
                else if(event.key.keysym.sym == SDLK_F4)
                    f4=1;
                else if(event.key.keysym.sym == SDLK_UP)
                    up=1;
                else if(event.key.keysym.sym == SDLK_LEFT)
                    left=1;
                else if(event.key.keysym.sym == SDLK_RIGHT)
                    right=1;
                else if(event.key.keysym.sym == 'n')
                    n=1;
                //- como as variaveis são boleanas faremos isto
                if(alt && f4)
                    done = 1;
                break;
            case SDL_KEYUP:
                if(event.key.keysym.sym == SDLK_RALT || event.key.keysym.sym == SDLK_LALT)
                    alt=0;
                else if(event.key.keysym.sym == SDLK_F4)
                    f4=0;
                else if(event.key.keysym.sym == SDLK_UP)
                    up=0;
                else if(event.key.keysym.sym == SDLK_LEFT)
                    left=0;
                else if(event.key.keysym.sym == SDLK_RIGHT)
                    right=0;
                break;
            case SDL_QUIT:
                done = 1;
                break;
            default:
                break;
            }
        }
        draw ();
    }
    return 0;
}

void draw(){
    static Uint8 pos=0,dir=0;
    static Sint16 X = 300,Y = 300;
    static Sint8 desly = 0;
    static int piso,i;

    if(n || Y > 700){ //- novo jogo
        n = 0;
        pos=dir=0;
        X = Y = 300;
        desly = 0;
    }

    if(right){
        X+=4;
        dir=0;
    }else if(left){
        X-=4;
        dir=25;
    }

    back.draw(0,screen,0);

    SDL_Rect ret;
    ret.x=300-X;
    ret.y=256;
    fase.draw(0,screen,&ret);

    /* colisão leteral ainda possue falhas, muitas falhas !!!
    for(i=0;i<4;i++){
        for(int j=0;j<29;j++){
            piso = faseMask.getpix24(X+i,Y+j-ret.y);
            if(piso==0xffffff||piso==0x808080){
                if(right)
                    X-=j;
                else if(left)
                    X+=j;
                goto pula01;
            }
        }
    }
    pula01:*/

    if(desly==0){
        if(up)
            desly = -12;
    }else
        up=0;

    for(i=0;i<10&&desly>=0;i++){
        for(int j=8;j<18;j++){
            piso = faseMask.getpix24(X+j,Y+29+i-ret.y);
            if(piso==0xffffff||piso==0x808080){
                desly = 0;
                Y+=i;
                goto pula;
            }
        }
    }
    pula:
    if(i==10)
        desly++;
    if(desly<0)
        desly++;

    if(desly > 10)
        desly = 10;
    else if(desly < -12)
        desly = -12;
    Y+=desly;

    mario.draw(pos+dir,&screen,300,Y+desly);

    if(pos==0||pos==6||pos==12||pos==18||pos==24){
        if(right||left)
            pos++;
        else{
            switch(pos){
            case 6:
                pos=23;
                break;
            case 12:
                pos=5;
                break;
            case 18:
                pos=11;
                break;
            case 24:
                pos=0;
            };
        }
    }else{
        pos++;
    }
    if(pos==25)
        pos=1;

    screen.flip();
    SDL_Delay(20);
}
