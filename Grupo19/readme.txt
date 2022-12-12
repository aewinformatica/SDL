Nome Do Jogo :   =^.^=  BomberKitty   =^.^=
Nome Da Empresa : Amigas 4ever LTDA.

------------------------------------------------Como Se Obter O Executável--------------------------------------
Para se obter o executaval desse incrível jogo, deve-se primeiro entar no site http://www.libsdl.org/, 
Downloads, SDL 1.2 (a versão mais recente no momento). Procure por "Development Libraries" e 
faça o download do pacote relativo ao sistema operacional e compilador que estiver usando (Linux ou MinGW).

Como no jogo tem musica e imagem é necessário que você entre nos sites http://www.libsdl.org/projects/SDL_mixer/, 
http://www.libsdl.org/projects/SDL_image/ e baixe a versão de desenvolvimento mais recente para o seu sistema.

Compilando o Jogo:

Sistema Operacional Linux:
gcc bomberkitty.c -o bomberkitty -Wall `sdl-config --cflags --libs` -lSDL_image -lSDL_mixer

./bomberkitty

Sistema Operacional Windows:
gcc bomberkitty..c -o bomberkitty..exe -Wall -lmingw32 -lSDLmain -lSDL -lSDL_image -lSDL_mixer

bomberkitty





------------------------------------------------Manual do Usuário-----------------------------------------------


Descrição e Objetivo : Hello Kitty, a famosa gatinha branca, está presa em um labirinto com inimigos ChocoCat´s .
Ela terá que percorrer o labirinto, destruindo blocos para encontrar a saída, isto é, sem esbarrar com seu inimigo #1 :
ChocoCat ! 


Elementos e Personagens Do Jogo : Hello Kitty - jogador
			          ChocoCat - inimigo, ou seja, ao encostar na Hello Kitty, esta perderá uma vida
		                  Flor - saída, estando escondida em algum dos blocos destrutíveis
                                  Blocos Indestrutíveis - blocos de cor azul, que mesmo estando perto de explosões, não irao desaparecer
		                  Blocos Destrutíveis - blocos de cor lilás, que desaparecerão se estiverem no raio da explosão da bomba
			          Bomba - elemento que explode depois de 3 segundos decorridos 

Como Jogar : Usar teclas direcionais do teclado ( setinhas ) para movimentar Hello Kitty pelo labirinto. 
	     Usar espaço para liberar bomba ( só é possível utilizar uma de cada vez )

 -->TOME CUIDADO! Pois estando no raio de explosão das bombas ou encontrando um inimigo ChocoCat, a Hello Kitty 
 perderá uma vida ! 





------------------------------------------------Manual do Programador------------------------------------------------

BomberKitty foi feito na linguagem C, com suporte da biblioteca SDL. 

O jogo foi  dividido em diversos arquivos, que são:

funcoes.h-> onde encontram-se todas as funções relacionadas ao labirinto, são elas :

*labirinto - imprime a imagem do labirinto com seus blocos destrutíveis e não destrutíveis;
*hello_andando - permite que a hello ande pelo labirinto alinhada á grade e respeitando suas respectivas restrições;
*bombamdo - imprime a figura da bomba na tela e inicializa o tempo em que a bomba irá explodir;
*explode - explode a bomba apagando o bloco destrutível e deixando seu rastro;
*morrendo - esta função mata a hello kitty caso esta esteja no alcance da bomba;
*gameover - imprime a imagem de gameover caso o jogador perca todas as vidas;
*escondendo - esta função escolhe uma bloco destrutível aleatório para esconder a saída;
*achou - imprime a imagem "você ganhou" caso o jogador encontre a saída;
*andacho - faz com que o inimigo ande por posições aleatórias, porém possíveis;
*mata_hello - se a hello kitty encostar no inimigo, esta perde uma vida;
*mata_choco - esta função mata a o inimigo caso esta esteja no alcance da bomba;


Os outros arquivos são:

main.c
jogo.h
menu.h
instintro.h

Bom Jogo!!