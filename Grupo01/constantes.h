#ifndef CONSTANTES_H_INCLUDED
#define CONSTANTES_H_INCLUDED

#define LADO 40
#define RECORDES 5
#define SAVES_NUM 5
#define SCREEN_W 800
#define SCREEN_H 600
#define PAINEL_LAT 200
#define GRADE_W ((SCREEN_W-PAINEL_LAT)/LADO)
#define GRADE_H (SCREEN_H/LADO)
#define INCX_DEFAULT LADO/5
#define INCY_DEFAULT LADO/5
#define INCY_MONSTROS LADO/10
#define INCX_MONSTROS LADO/10

enum niveis{FACIL, MEDIO, DIFICIL};
enum estados_personagem{VIVO, ATINGIDO, MORTO, FORA};
enum version{LINUX, MAC, WINDOWS, BOMBER};
enum state{MENU, LE_NOME, CARREGAR, RECORDES_T, RECORDES_P, INSTRUCOES, CREDITOS, PAUSA, SALVA, JOGO, GAMEOVER};

#endif // CONSTANTES_H_INCLUDED
