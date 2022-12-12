CC=gcc

CFLAGS=-g -Wall -D_GNU_SOURCE=1 -D_REENTRANT
IMAGE_FLAGS=-lSDL_image
MIXER_FLAGS=-lSDL_mixer
LFLAGS=-L/usr/lib
IFLAGS=-I/usr/include/SDL

all: ex0 ex1 ex2v2 ex3 ex4 ex5 ex6 ex7

ex0: ex0.o 
	$(CC) -o ex0 ex0.o $(CFLAGS) $(IMAGE_FLAGS) $(LFLAGS) $(IFLAGS) 

ex0.o: ex0.c
	$(CC) ex0.c -c $(CFLAGS) $(LFLAGS) $(IFLAGS)


ex1: ex1.o 
	$(CC) -o ex1 ex1.o $(CFLAGS) $(IMAGE_FLAGS) $(LFLAGS) $(IFLAGS) 

ex1.o: ex1.c
	$(CC) ex1.c -c $(CFLAGS) $(LFLAGS) $(IFLAGS)


ex2v2: ex2v2.o 
	$(CC) -o ex2v2 ex2v2.o $(CFLAGS) $(IMAGE_FLAGS) $(LFLAGS) $(IFLAGS) 

ex2v2.o: ex2v2.c
	$(CC) ex2v2.c -c $(CFLAGS) $(LFLAGS) $(IFLAGS)


ex3: ex3.o 
	$(CC) -o ex3 ex3.o $(CFLAGS) $(IMAGE_FLAGS) $(LFLAGS) $(IFLAGS) 

ex3.o: ex3.c
	$(CC) ex3.c -c $(CFLAGS) $(LFLAGS) $(IFLAGS)


ex4: ex4.o 
	$(CC) -o ex4 ex4.o $(CFLAGS) $(IMAGE_FLAGS) $(LFLAGS) $(IFLAGS) 

ex4.o: ex4.c
	$(CC) ex4.c -c $(CFLAGS) $(LFLAGS) $(IFLAGS)


ex5: ex5.o 
	$(CC) -o ex5 ex5.o $(CFLAGS) $(IMAGE_FLAGS) $(LFLAGS) $(IFLAGS) 

ex5.o: ex5.c
	$(CC) ex5.c -c $(CFLAGS) $(LFLAGS) $(IFLAGS)


ex6: ex6.o 
	$(CC) -o ex6 ex6.o $(CFLAGS) $(IMAGE_FLAGS) $(LFLAGS) $(IFLAGS) $(MIXER_FLAGS) 


ex6.o: ex6.c
	$(CC) ex6.c -c $(CFLAGS) $(LFLAGS) $(IFLAGS)


ex7: ex7.o 
	$(CC) -o ex7 ex7.o $(CFLAGS) $(IMAGE_FLAGS) $(LFLAGS) $(IFLAGS) $(MIXER_FLAGS) 

ex7.o: ex7.c
	$(CC) ex7.c -c $(CFLAGS) $(LFLAGS) $(IFLAGS)


clean:
	rm -rf *.o ex0 ex1 ex2v2 ex3 ex4 ex5 ex6 ex7 core



#-I/usr/include/SDL -D_GNU_SOURCE=1 -D_REENTRANT
#-L/usr/lib -lSDL
#gcc -o teste5 funcoes.o teste5.o $(CFLAGS) $(IMAGE_FLAGS) `sdl-config --cflags --libs`
