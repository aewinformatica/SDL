gcc main.c -c -Wall
   gcc abertura.c -c -Wall
   gcc fases.c -c -Wall
   gcc funcoesFases.c -c -Wall
   gcc sorteiaFase.c -c -Wall
   gcc recordes.c -c -Wall

   gcc main.o Abertura.o fases.o funcoesFases.o sorteiaFase.o recordes.o -o BomberKart -Wall -lmingw32 -lSDLmain -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf 