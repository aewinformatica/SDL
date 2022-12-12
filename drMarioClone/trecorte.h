/*
+----------------------------------------------------------+
| Data: 09/04/2006 - 09/04/2006                            |
|                                                          |
| Diogo_RBG - diogorigo@yahoo.com.br - diogorbg.bigbig.com |
|                                                          |
| * Classe TRecorte;                                       |
+----------------------------------------------------------+
*/
#ifndef TRecorte_H
#define TRecorte_H

#include "tsurface.h"

class TRecorte{
public:
    TSurface *Quadros;
    int Bas;
    bool Div;
    TRecorte();
    ~TRecorte(){}

    bool definir(TSurface *quadros,int contx,bool div=0);
    bool draw(int pos,TSurface *screen,int x,int y);
};

TRecorte::TRecorte(){
    Quadros=0;
    Bas=0;
    bool Div;
}

bool TRecorte::definir(TSurface *quadros,int contx,bool div){
    if(!quadros)
        return 0;
    Quadros = quadros;
    Div = div;
    Bas = Quadros->w()/contx-Div;
}

bool TRecorte::draw(int pos,TSurface *screen,int x,int y){
    SDL_Rect ret1,ret2;
    ret1.x = Div + pos*(Bas+Div);
    ret1.y = 0;
    ret2.x = x;
    ret2.y = y;
    ret1.w = ret2.w = Bas;
    ret1.h = ret2.h = Quadros->h();
    return Quadros->draw(&ret1,*screen,&ret2);
}

#endif
