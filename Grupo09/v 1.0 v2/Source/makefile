CC=gcc

CFLAGS=-g -Wall -D_GNU_SOURCE=1 -D_REENTRANT
IMAGE_FLAGS=-lSDL_image
AUDIO_FLAGS=-lSDL_mixer
TEXT_FLAGS=-lSDL_ttf
LFLAGS=-L/usr/lib

IFLAGS=-I/usr/include/SDL


all: jogo

fim: jogo
	mv jogo ..

jogo: jogo.o 
	$(CC) -o jogo jogo.o $(CFLAGS) $(IMAGE_FLAGS) $(LFLAGS) $(IFLAGS) $(AUDIO_FLAGS) $(TEXT_FLAGS)
	
#funcoes.o: funcoes.c
#	$(CC) funcoes.c -c  $(CFLAGS) $(LFLAGS) $(IFLAGS)

jogo.o: jogo.c
	$(CC) jogo.c -c $(CFLAGS) $(LFLAGS) $(IFLAGS)

clean:
	rm -rf *.o jogo core



#-I/usr/include/SDL -D_GNU_SOURCE=1 -D_REENTRANT
#-L/usr/lib -lSDL
#gcc -o teste5 funcoes.o teste5.o $(CFLAGS) $(IMAGE_FLAGS) `sdl-config --cflags --libs`
