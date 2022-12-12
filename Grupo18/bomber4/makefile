executa: main.exe
	@echo Compilado. Executando aplicacao...
	main.exe

main.exe: main.c labirinto.c movimento.c explode.c outras.c global.h prototipos.h
	@echo Compilando...
	gcc -o main main.c labirinto.c movimento.c explode.c outras.c -Iu:\include\ -Lu:\lib\ -Wall -lmingw32 -lSDLmain -lSDL -lSDL_image -lSDL_ttf