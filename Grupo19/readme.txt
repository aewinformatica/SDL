Nome Do Jogo :   =^.^=  BomberKitty   =^.^=
Nome Da Empresa : Amigas 4ever LTDA.

------------------------------------------------Como Se Obter O Execut�vel--------------------------------------
Para se obter o executaval desse incr�vel jogo, deve-se primeiro entar no site http://www.libsdl.org/, 
Downloads, SDL 1.2 (a vers�o mais recente no momento). Procure por "Development Libraries" e 
fa�a o download do pacote relativo ao sistema operacional e compilador que estiver usando (Linux ou MinGW).

Como no jogo tem musica e imagem � necess�rio que voc� entre nos sites http://www.libsdl.org/projects/SDL_mixer/, 
http://www.libsdl.org/projects/SDL_image/ e baixe a vers�o de desenvolvimento mais recente para o seu sistema.

Compilando o Jogo:

Sistema Operacional Linux:
gcc bomberkitty.c -o bomberkitty -Wall `sdl-config --cflags --libs` -lSDL_image -lSDL_mixer

./bomberkitty

Sistema Operacional Windows:
gcc bomberkitty..c -o bomberkitty..exe -Wall -lmingw32 -lSDLmain -lSDL -lSDL_image -lSDL_mixer

bomberkitty





------------------------------------------------Manual do Usu�rio-----------------------------------------------


Descri��o e Objetivo : Hello Kitty, a famosa gatinha branca, est� presa em um labirinto com inimigos ChocoCat�s .
Ela ter� que percorrer o labirinto, destruindo blocos para encontrar a sa�da, isto �, sem esbarrar com seu inimigo #1 :
ChocoCat ! 


Elementos e Personagens Do Jogo : Hello Kitty - jogador
			          ChocoCat - inimigo, ou seja, ao encostar na Hello Kitty, esta perder� uma vida
		                  Flor - sa�da, estando escondida em algum dos blocos destrut�veis
                                  Blocos Indestrut�veis - blocos de cor azul, que mesmo estando perto de explos�es, n�o irao desaparecer
		                  Blocos Destrut�veis - blocos de cor lil�s, que desaparecer�o se estiverem no raio da explos�o da bomba
			          Bomba - elemento que explode depois de 3 segundos decorridos 

Como Jogar : Usar teclas direcionais do teclado ( setinhas ) para movimentar Hello Kitty pelo labirinto. 
	     Usar espa�o para liberar bomba ( s� � poss�vel utilizar uma de cada vez )

 -->TOME CUIDADO! Pois estando no raio de explos�o das bombas ou encontrando um inimigo ChocoCat, a Hello Kitty 
 perder� uma vida ! 





------------------------------------------------Manual do Programador------------------------------------------------

BomberKitty foi feito na linguagem C, com suporte da biblioteca SDL. 

O jogo foi  dividido em diversos arquivos, que s�o:

funcoes.h-> onde encontram-se todas as fun��es relacionadas ao labirinto, s�o elas :

*labirinto - imprime a imagem do labirinto com seus blocos destrut�veis e n�o destrut�veis;
*hello_andando - permite que a hello ande pelo labirinto alinhada � grade e respeitando suas respectivas restri��es;
*bombamdo - imprime a figura da bomba na tela e inicializa o tempo em que a bomba ir� explodir;
*explode - explode a bomba apagando o bloco destrut�vel e deixando seu rastro;
*morrendo - esta fun��o mata a hello kitty caso esta esteja no alcance da bomba;
*gameover - imprime a imagem de gameover caso o jogador perca todas as vidas;
*escondendo - esta fun��o escolhe uma bloco destrut�vel aleat�rio para esconder a sa�da;
*achou - imprime a imagem "voc� ganhou" caso o jogador encontre a sa�da;
*andacho - faz com que o inimigo ande por posi��es aleat�rias, por�m poss�veis;
*mata_hello - se a hello kitty encostar no inimigo, esta perde uma vida;
*mata_choco - esta fun��o mata a o inimigo caso esta esteja no alcance da bomba;


Os outros arquivos s�o:

main.c
jogo.h
menu.h
instintro.h

Bom Jogo!!