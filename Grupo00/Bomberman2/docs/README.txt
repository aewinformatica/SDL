WINDOWS
Para compilar, execute o “compila.bat”.
Ou execute no prompt:
gcc main.c funcoes.c -o bomberman -Wall -g -lm -lmingw32 -lsdlmain -lsdl -lSDL_ttf -lSDL_mixer -lSDL_image

LINUX
Execute no terminal:
gcc main.c funcoes.c -o bomberman -Wall `sdl-config --cflags --libs` -lSDL_ttf -lSDL_mixer -lSDL_image
