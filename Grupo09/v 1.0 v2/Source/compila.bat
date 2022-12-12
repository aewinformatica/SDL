gcc main.c -c -Wall
gcc jogo.c -c -Wall


   gcc main.o jogo.o -o BomberKart -Wall -lmingw32 -lSDLmain -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf 