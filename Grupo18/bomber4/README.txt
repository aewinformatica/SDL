UNIVERSIDADE FEDERAL DO RIO DE JANEIRO � UFRJ
COMPUTA��O PARA INFORM�TICA I
Projeto desenvolvido pelos alunos
Gustavo Cury E Pedro Dupim
No primeiro semestre de 2008.
Professor da disciplina: Adriano Joaquim de Oliveira

Aplica��o em linguagem C, com uso da biblioteca gr�fica SDL:

BOMBERMAN

::::::::::::::::Manual do Jogador:::::::::::::::::::

Interl�dio:
Gelecas t�xicas, dem�nios, plantas assassinas... A Terra est� � beira de um colapso!
Uma pesquisa mal-sucedida libertou essas e outras aberra��es na base 2008x1. Bomberman � o �nico sobrevivente nessa base secreta, localizada a tr�s n�veis abaixo do solo.
Para evitar o caos no mundo e salvar sua pr�pria pele, ele deve destruir todos os monstros em cada um dos n�veis e chegar � superf�cie. Para isso, conta de um arsenal ilimitado de bombas, 
al�m de recursos escondidos em caixas destrut�veis.

Sum�rio:
-Interl�dio 
-Compilando
-Comandos
-A base 2008x1
-Os labirintos
-Caixas
-Os inimigos
-Recordes
-Obs


Compilando:
Para compilar a aplica��o � necess�rio ter instalado as bibliotecas
SDL
SDL_image
SDL_ttf
SDL_mixer
E um compilador C: (O MinGW, por exemplo)

A string de compila��o deve reunir os arquivos fonte
Main.c
Labirinto.c
Movimento.c
Explode.c
Outras.c
Em um �nico aplicativo, utilizando as bibliotecas citadas.

Ex(o.s. Windows): gcc -o main main.c labirinto.c movimento.c explode.c outras.c -Iu:\include\ -Lu:\lib\ -Wall -lmingw32

Comandos pelo teclado:
- Teclas direcionais: movem Bomberman pelo labirinto. S� � poss�vel andar por espa�os livres. 
� poss�vel liberar passagem destruindo caixas com bombas.

- �Barra de espa�o� ou �Enter�: T�m a mesma fun��o no jogo. Correspondem � tecla de a��o e Server para implantar uma bomba no labirinto. 
Apesar do estoque ilimitado, s� � poss�vel implantar uma bomba de cada vez. Ap�s ativar uma,  � necess�rio esperar ela acabar de explodir para, 
s� ent�o, colocar uma nova.

- �Esc�:
Quando pressionada em jogo, esc tem fun��o de pausa, e ativa um menu de op��es. Para recome�ar, basta pression�-la novamente,
 ou selecione �Continuar� no menu de op��es.
Quando pressionada no main menu, fecha a janela do jogo.

O controle dos menus � feito pelo mouse.


A base 2008x1:
A base de testes fica localizada a tr�s n�veis abaixo do solo. Cada n�vel corresponde a um labirinto, criado para garantir o 
sigilo das opera��es. Ap�s o �ltimo teste, criaturas bizarras dominaram o local e vagam por tais labirintos. Existe uma �nica
 sa�da para cada n�vel, que leva ao n�vel superior, ou � superf�cie (no caso do �ltimo n�vel). Tamb�m por motivos de seguran�a 
a sa�da de cada labirinto est� escondida em uma das caixas (?) dispostas entre blocos fixos.

Os labirintos:
Cada andar � formado por um labirinto de blocos fixos e caixas que bloqueiam o caminho. Felizmente, essas �ltimas podem ser 
destru�das por bombas. Quando isso � feito o conte�do da caixa � revelado e pode ser usado para facilitar a tarefa. 

Caixas:
O conte�do de uma caixa pode ser:

- A sa�da: 
Leva ao pr�ximo n�vel da base, ou � superf�cie (no caso do �ltimo n�vel). Para evitar que os inimigos o sigam � superf�cie � necess�rio destru�-los, 
antes de subir. Enquanto isso n�o for feito � sa�da fica trancada.

- Fire up: Incremento ao alcance da bomba: 
Resultado de um teste anterior, Fire up incrementa 1 unidade ao alcance das bombas colocadas. Ao subir para outro n�vel, esse item perde o efeito 
e as bombas voltam a ter o alcance inicial (1).

- Invencibilidade tempor�ria:
Bomberman fica invulner�vel a explos�es e ao contato com o inimigo. Infelizmente,  isso s� tem durante 8000ms, tempo no qual Bomberman fica piscando. 
Item n�o cumulativo.

- Aumento de velocidade:
Bomberman passa a andar com o dobro da velocidade normal.

-Vida extra:
Incrementa 1 ao n�mero de vidas.

Para cada caixa destru�da h� um amento de 100 na pontua��o do jogador.

Os inimigos:
S�o resultados da pesquisa mal-sucedida. Vagam pelos labirintos e o contato com eles faz bomberman perder uma vida. A �nica forma de destru�-los 
� explodindo uma bomba que os alcance. Est�o divididos em 4 esp�cies:

- Slime:
Vaga aleatoriamente pelo labirinto.

- Bomb-Slime:
Tem o mesmo padr�o do Slime, por�m, ao ser destru�do, explode como uma bomba de alcance m�ximo.

- Planta carn�vora mutante:
Definida uma dire��o, a planta carn�vora anda linearmente at� encontrar um obst�culo.

- Dem�nio:
Possui intelig�ncia suficiente para n�o ir em dire��o �s bombas. Ele sempre sabe qual o alcance delas e tentar�o fugir da explos�o sempre que puderem.

Recordes:
Cada objeto destru�do soma um b�nus a pontua��o. Ao t�rmino de um jogo, essa pontua��o e o nome s�o salvos em uma lista e as melhores pontua��es 
podem ser vistas no menu Recordes (Main menu -> Recordes).


Considera��es:
Essa aplica��o � um projeto sem fins comerciais criado para concluir a disciplina Computa��o para Inform�tica I do curso de Ci�ncias da Computa��o 
da Universidade Federal do Rio de Janeiro �BR no primeiro semestre de 2008. Alguns dos recursos utilizados foram conseguidos na Internet sem consulta 
por autoriza��o. Se, por ventura, algu�m sentir seus direitos violados, por favor, contate-nos.



::::::::::::::::Manual do Programa:::::::::::::::::::

Global.h:
Aqui s�o definidas todas as constantes (#define) e Inicializamos as bibliotecas.

Prototipos.c:
Colocamos o prot�tipo de cada fun��o e as vari�veis globais. Isso ajuda na leitura do programa, fica mais limpo na hora de ler.

Labirino.c:
	void cria_lab(int mapa[MAX_H][MAX_W], int n, int m, int bld)
		Posiciona os blocos destrutives e indestrutives e esconde os objetos atras das caixas
	void posiciona_indestrutiveis(int mapa[MAX_H][MAX_W], int n, int m)
		O nome j� diz.

	void posiciona_caixas(int mapa[MAX_H][MAX_W], int n, int m, int bld)
		O nome j� diz.
	void esconde(int mapa[MAX_H][MAX_W], int n, int m, int q, int cod)
		?????
	void posiciona_dinamico(int mapa[MAX_H][MAX_W], int n, int m, Obj_Dinamico *obj)
		Posiciona tanto o bomberman como os inimigos
	void desenha_lab(SDL_Surface *screen, int mapa[MAX_H][MAX_W], int n, int m, SDL_Surface* s_chipset)
		Ele ir� na tela de acordo com os n�meros que est�o na matriz

Main.c:
Inicializa v�deo e chama a fun��o introducao e em seguida a menu.

Explode.c:
	void ativar_bomba(Bomba *bomba, int mapa[MAX_H][MAX_W], Obj_Dinamico *obj)
		O nome j� diz. Chama a funcao_timer depois de 2s e a ultimo chama a funcao explode.

	Uint32 funcao_timer(Uint32 interval, void *param)
		usada na funcao ativar bomba

	void explode(int mapa[MAX_H][MAX_W], int coox, int cooy, int raio, int dir)
		Se tiver bomberman ele morre, bloco destrutivel some, etc...

	int avalia_ex(int coox, int cooy)
		Ir� verificar se contiua explodindo ou nao, dependndo do que tiver no caminho

	void direcionar(int dir, int *ix, int *iy)
		????

	void morre_bomber()
		diminui uma vida dele, quando esta for menor que 0 ele tir�  salvar e retornar� ao menu.

	void morre_inimigo(int cooy, int coox)
		diminui o numero de inimigos.

Outras.c:
	int menu2 (SDL_Surface *screen, int* voltar_pro_menu_inicial)
		� o menu que aparece qdo aperta ESC durane o jogo.
	void desenha_texto(char* texto, SDL_Surface* dst, int x, int y)
		Blita uma string na tela, como as coordenadas (x,y)
	void apaga_texto(SDL_Surface* dst, int x, int y)
		simula uma borracha, por�m ela blita uma imagem com a cor do fundo por cima da letra.
	void f_introducao(void)
		Faz um efeito com duas imagens de fade in e fade out
	int f_menu ()
		Depois de passar pela introducao essa funcao da opcao de comeca um jogo, ver o recorde ou sair do jogo.
	int f_jogo ()
		Ser� explica mais adiante.
	void novo_jogo(int* n, int* m, int* step, int direcionais[4], int lvl, SDL_Surface* ambiente)
		????
	void animacao_andar_hero(SDL_Rect *r_hero, Obj_Dinamico *dinamico)
		Simula o bomberman andando. Pega varias imagens e vai trocando dando a impressao q ele esta andando.
	void recorde (void)
		grava do recorde em um arquivo binario
	void show_rec (void)
		Blita as informao dos arquivos binario para a tela do jogo

Movimento.c:

	void alinhar(Obj_Dinamico *obj)
		Ira andar com o bomberman/Inimigo at� a linha da grade (at� ficar no quadrado)
	void define_din(Obj_Dinamico *obj,int x, int y, int i, int j, int inx, int iny, int cod, int ai)
		??????
	void move_inimigo(Obj_Dinamico *obj, int step, int mapa[MAX_H][MAX_W])
		O nome j� diz.
	void mover(Obj_Dinamico *obj, int x, int y, int step, int mapa[MAX_H][MAX_W], int dir)
		move os inimigos de duas maneiras vinculadas a AI.
	void checa_direcionais(int teclado[4], Obj_Dinamico *bomberman, int *step, int mapa[MAX_H][MAX_W])
		??????
	int checa_passagem(int n)
		Verifica se tem algum bloco indestrutivel destruitel, se item,etc..
	void verifica_colisao(void)
		Colisao entre o bomber e o inimigo
	void animacao_andar(SDL_Rect *r_hero, Obj_Dinamico *dinamico)
		Simula o inimigo andando. Pega varias imagens e vai trocando dando a impressao q ele esta andando.
	void mover2(Obj_Dinamico *obj, int x, int y, int step, int mapa[MAX_H][MAX_W])
		move o bomberman
	int checa_colisao(SDL_Rect a, SDL_Rect b)
		??????
	void invencibilidade_temp(int duracao, Obj_Dinamico* obj)
		O nome j� diz.
	Uint32 timer_invencibilidade(Uint32 interval, void *param)
		O nome j� diz.

Agora que as fun��es j� est�o apresentadas, vamos falar de maneira geral do funcionamento do jogo.

Para a cria��o ficar mais f�cil, optamos por usar uma matriz como se fosse um tabuleiro de xadrez. Cada quadrado do tabuleiro representa um n�mero.

Depois lemos toda a matriz e blitamos na tela (de acordo com a propor��o escolhida pelo programador) as imagens.
Por exempo:

0 = espaco vazio
1 = bomberman

matriz[4][4]

0000
0001
0000
0000

bomberman est� na matriz[3][1]. Esse � um exemplo simples, por�m � a base do jogo.

Ao redor disso existe somente detalhes, por exemplo, fazer uma simula��o dele andando, dos inimigos andando.



:::::::::::::::::::::::::COMPILAR:::::::::::::::::::::::::


Tenha instalado um compilador que tenha o make.exe (exemplo gcc)
e as bibliotecas:

<SDL.h>
<SDL_image.h>
<conio.h>
<stdlib.h>
<string.h>
<stdio.h>
<time.h>
<SDL_ttf.h>

WINDOWS:

Abra o terminal v� at� a pasta do jogo e digite: make e aperte enter!
Ele ir� compilar e excutar autmaticamente os arquivos.


Obrigado 
E bom jogo.












































