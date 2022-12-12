/*
+----------------------------------------------------------+
| Data: 28/03/2006 - 27/04/2006                            |
|                                                          |
| Diogo_RBG - diogorigo@yahoo.com.br - diogorbg.bigbig.com |
|                                                          |
| * Classe TSurface que organiza a estrutura SDL_Surface;  |
+----------------------------------------------------------+
*/
#ifndef TSurface_H
#define TSurface_H

#include <SDL/SDL.h>
//- manipulacao de arquivo
#include <sys/stat.h>
#include <fcntl.h>

struct fileRGB{
    Uint8  tipo[3];
    Uint8 bpp;
    Uint16 nExtra;
};

union RGB{
    Uint32 cor;
    Uint8 rgb[4];
};

class TSurface{
private:
    SDL_Surface *Surface;
    Uint8 *Mask;
public:
    TSurface(){Surface=0;Mask=0;}
    ~TSurface(){free();}

    operator SDL_Surface*(){return Surface;}
    bool loadBMP(const char *file);
    bool loadRGB(const char *file,Uint32 flags=SDL_SWSURFACE);
    bool setVideoMode(int w,int h,Uint8 prof,int flags);
    bool setVideoMode();
    int fullScreen();
    Uint32 rgb(Uint8 r,Uint8 g,Uint8 b);
    void fillRect(SDL_Rect *rect,Uint32 cor);
    void flip();
    int w(){return Surface->w;}
    int h(){return Surface->h;}
    Uint32 getpixel(int x,int y);
    Uint32 getpix24(int x,int y);
    void setpixel(int x,int y,Uint32 cor);
    void free();
    int draw(SDL_Rect *rect,SDL_Surface *dst,SDL_Rect *dstrect);
    bool criarSurface(int w,int h,int depth,Uint32 flags);
    bool criarSurface24(int w,int h,Uint32 flags);
    bool criarSurface32(int w,int h,Uint32 flags);
    bool transp(Uint32 cor);
};

bool TSurface::transp(Uint32 cor){
    return SDL_SetColorKey(Surface,SDL_SRCCOLORKEY,cor);
}

bool TSurface::loadBMP(const char *file){
    Surface = SDL_LoadBMP(file);
    return Surface;
}

bool TSurface::loadRGB(const char *file,Uint32 flags){
    struct fileRGB cab;
    Uint16 wh[2];

    int hd = open(file,O_BINARY|O_RDONLY,S_IREAD|S_IWRITE);
    if(hd<0)
        return 0;
    read(hd,&cab,sizeof(struct fileRGB));
    lseek(hd,cab.nExtra,SEEK_CUR); //- pular extras
    read(hd,wh,4); //- bas e alt
    if(!criarSurface(wh[0],wh[1],cab.bpp*8,flags)){//
        close(hd);
        return 0;
    }
    int cont=read(hd,Surface->pixels,wh[0]*wh[1]*cab.bpp);
    close(hd);
    //MessageBox (0,"ok","Error",MB_ICONHAND);
    return 1;
}

bool TSurface::criarSurface(int w,int h,int depth,Uint32 flags){
    if(depth==24)
        return criarSurface24(w,h,flags);
    else if(depth==32)
        return criarSurface32(w,h,flags);
    return 0;
}

bool TSurface::criarSurface32(int w,int h,Uint32 flags){
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    // 0xRGBA
    return Surface = SDL_CreateRGBSurface(flags,w,h,32,0xFF000000,0xFF0000,0x00FF00,0x0000FF);
#else
    // 0xABGR - MAIS COMUM
    return Surface = SDL_CreateRGBSurface(flags,w,h,32,0x0000FF,0x00FF00,0xFF0000,0xFF000000);
#endif
}

bool TSurface::criarSurface24(int w,int h,Uint32 flags){
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    // 0xRGB
    return Surface = SDL_CreateRGBSurface(flags,w,h,24,0xFF000000,0xFF0000,0x00FF00,0);
#else
    // 0xBGR - MAIS COMUM
    return Surface = SDL_CreateRGBSurface(flags,w,h,24,0x0000FF,0x00FF00,0xFF0000,0);
#endif
}

int TSurface::draw(SDL_Rect *rect,SDL_Surface *dst,SDL_Rect *dstrect){
    return SDL_BlitSurface(Surface,rect,dst,dstrect);
}

void TSurface::free(){
    SDL_FreeSurface(Surface);
    Surface = 0;
    if(Mask)
        delete[] Mask;
    Mask=0;
}

bool TSurface::setVideoMode(int w,int h,Uint8 prof,int flags){
    if(Surface)
        return 0;
    Surface = SDL_SetVideoMode(w,h,prof,flags);
    return Surface;
}

bool TSurface::setVideoMode(){
    if(Surface)
        return 0;
    Surface = SDL_SetVideoMode (640,480,32,SDL_SWSURFACE|SDL_DOUBLEBUF);
    return Surface;
}

int TSurface::fullScreen(){
    return SDL_WM_ToggleFullScreen(Surface);
}

Uint32 TSurface::rgb(Uint8 r,Uint8 g,Uint8 b){
    return SDL_MapRGB (Surface->format,r,g,b);
}

void TSurface::fillRect(SDL_Rect *rect,Uint32 cor){
    SDL_FillRect(Surface,rect,cor);
}

void TSurface::flip(){
    SDL_Flip(Surface);
}

Uint32 TSurface::getpix24(int x,int y){
    RGB rgb;
    SDL_GetRGB(getpixel(x,y),Surface->format,&rgb.rgb[0],&rgb.rgb[1],&rgb.rgb[2]);
    return rgb.cor;
}

Uint32 TSurface::getpixel(int x,int y){
    if(x<0||x>=Surface->w||y<0||y>=Surface->h)
        return 0;
    int bpp = Surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to retrieve */
    Uint8 *p = (Uint8 *)Surface->pixels + y * Surface->pitch + x * bpp;

    switch(bpp){
    case 1:
        return *p;
    case 2:
        return *(Uint16 *)p;
    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;
    case 4:
        return *(Uint32 *)p;
    default:
        return 0; //- shouldn't happen, but avoids warnings
    }
}

void TSurface::setpixel(int x,int y,Uint32 cor){
    if(x<0||x>=Surface->w||y<0||y>=Surface->h)
        return;
    int bpp = Surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to set */
    Uint8 *p = (Uint8 *)Surface->pixels + y*Surface->pitch + x*bpp;

    switch(bpp) {
    case 1:
        *p = cor;
        break;
    case 2:
        *(Uint16 *)p = cor;
        break;
    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
            p[0] = (cor >> 16) & 0xff;
            p[1] = (cor >> 8) & 0xff;
            p[2] = cor & 0xff;
        } else {
            p[0] = cor & 0xff;
            p[1] = (cor >> 8) & 0xff;
            p[2] = (cor >> 16) & 0xff;
        }
        break;
    case 4:
        *(Uint32 *)p = cor;
        break;
    }
}

#endif
