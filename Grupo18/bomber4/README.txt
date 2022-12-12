UNIVERSIDADE FEDERAL DO RIO DE JANEIRO – UFRJ
COMPUTAÇÃO PARA INFORMÁTICA I
Projeto desenvolvido pelos alunos
Gustavo Cury E Pedro Dupim
No primeiro semestre de 2008.
Professor da disciplina: Adriano Joaquim de Oliveira

Aplicação em linguagem C, com uso da biblioteca gráfica SDL:

BOMBERMAN

::::::::::::::::Manual do Jogador:::::::::::::::::::

Interlúdio:
Gelecas tóxicas, demônios, plantas assassinas... A Terra está à beira de um colapso!
Uma pesquisa mal-sucedida libertou essas e outras aberrações na base 2008x1. Bomberman é o único sobrevivente nessa base secreta, localizada a três níveis abaixo do solo.
Para evitar o caos no mundo e salvar sua própria pele, ele deve destruir todos os monstros em cada um dos níveis e chegar à superfície. Para isso, conta de um arsenal ilimitado de bombas, 
além de recursos escondidos em caixas destrutíveis.

Sumário:
-Interlúdio 
-Compilando
-Comandos
-A base 2008x1
-Os labirintos
-Caixas
-Os inimigos
-Recordes
-Obs


Compilando:
Para compilar a aplicação é necessário ter instalado as bibliotecas
SDL
SDL_image
SDL_ttf
SDL_mixer
E um compilador C: (O MinGW, por exemplo)

A string de compilação deve reunir os arquivos fonte
Main.c
Labirinto.c
Movimento.c
Explode.c
Outras.c
Em um único aplicativo, utilizando as bibliotecas citadas.

Ex(o.s. Windows): gcc -o main main.c labirinto.c movimento.c explode.c outras.c -Iu:\include\ -Lu:\lib\ -Wall -lmingw32

Comandos pelo teclado:
- Teclas direcionais: movem Bomberman pelo labirinto. Só é possível andar por espaços livres. 
É possível liberar passagem destruindo caixas com bombas.

- ‘Barra de espaço’ ou ‘Enter’: Têm a mesma função no jogo. Correspondem à tecla de ação e Server para implantar uma bomba no labirinto. 
Apesar do estoque ilimitado, só é possível implantar uma bomba de cada vez. Após ativar uma,  é necessário esperar ela acabar de explodir para, 
só então, colocar uma nova.

- ‘Esc’:
Quando pressionada em jogo, esc tem função de pausa, e ativa um menu de opções. Para recomeçar, basta pressioná-la novamente,
 ou selecione “Continuar” no menu de opções.
Quando pressionada no main menu, fecha a janela do jogo.

O controle dos menus é feito pelo mouse.


A base 2008x1:
A base de testes fica localizada a três níveis abaixo do solo. Cada nível corresponde a um labirinto, criado para garantir o 
sigilo das operações. Após o último teste, criaturas bizarras dominaram o local e vagam por tais labirintos. Existe uma única
 saída para cada nível, que leva ao nível superior, ou à superfície (no caso do último nível). Também por motivos de segurança 
a saída de cada labirinto está escondida em uma das caixas (?) dispostas entre blocos fixos.

Os labirintos:
Cada andar é formado por um labirinto de blocos fixos e caixas que bloqueiam o caminho. Felizmente, essas últimas podem ser 
destruídas por bombas. Quando isso é feito o conteúdo da caixa é revelado e pode ser usado para facilitar a tarefa. 

Caixas:
O conteúdo de uma caixa pode ser:

- A saída: 
Leva ao próximo nível da base, ou à superfície (no caso do último nível). Para evitar que os inimigos o sigam à superfície é necessário destruí-los, 
antes de subir. Enquanto isso não for feito à saída fica trancada.

- Fire up: Incremento ao alcance da bomba: 
Resultado de um teste anterior, Fire up incrementa 1 unidade ao alcance das bombas colocadas. Ao subir para outro nível, esse item perde o efeito 
e as bombas voltam a ter o alcance inicial (1).

- Invencibilidade temporária:
Bomberman fica invulnerável a explosões e ao contato com o inimigo. Infelizmente,  isso só tem durante 8000ms, tempo no qual Bomberman fica piscando. 
Item não cumulativo.

- Aumento de velocidade:
Bomberman passa a andar com o dobro da velocidade normal.

-Vida extra:
Incrementa 1 ao número de vidas.

Para cada caixa destruída há um amento de 100 na pontuação do jogador.

Os inimigos:
São resultados da pesquisa mal-sucedida. Vagam pelos labirintos e o contato com eles faz bomberman perder uma vida. A única forma de destruí-los 
é explodindo uma bomba que os alcance. Estão divididos em 4 espécies:

- Slime:
Vaga aleatoriamente pelo labirinto.

- Bomb-Slime:
Tem o mesmo padrão do Slime, porém, ao ser destruído, explode como uma bomba de alcance máximo.

- Planta carnívora mutante:
Definida uma direção, a planta carnívora anda linearmente até encontrar um obstáculo.

- Demônio:
Possui inteligência suficiente para não ir em direção às bombas. Ele sempre sabe qual o alcance delas e tentarão fugir da explosão sempre que puderem.

Recordes:
Cada objeto destruído soma um bônus a pontuação. Ao término de um jogo, essa pontuação e o nome são salvos em uma lista e as melhores pontuações 
podem ser vistas no menu Recordes (Main menu -> Recordes).


Considerações:
Essa aplicação é um projeto sem fins comerciais criado para concluir a disciplina Computação para Informática I do curso de Ciências da Computação 
da Universidade Federal do Rio de Janeiro –BR no primeiro semestre de 2008. Alguns dos recursos utilizados foram conseguidos na Internet sem consulta 
por autorização. Se, por ventura, alguém sentir seus direitos violados, por favor, contate-nos.



::::::::::::::::Manual do Programa:::::::::::::::::::

Global.h:
Aqui são definidas todas as constantes (#define) e Inicializamos as bibliotecas.

Prototipos.c:
Colocamos o protótipo de cada função e as variáveis globais. Isso ajuda na leitura do programa, fica mais limpo na hora de ler.

Labirino.c:
	void cria_lab(int mapa[MAX_H][MAX_W], int n, int m, int bld)
		Posiciona os blocos destrutives e indestrutives e esconde os objetos atras das caixas
	void posiciona_indestrutiveis(int mapa[MAX_H][MAX_W], int n, int m)
		O nome já diz.

	void posiciona_caixas(int mapa[MAX_H][MAX_W], int n, int m, int bld)
		O nome já diz.
	void esconde(int mapa[MAX_H][MAX_W], int n, int m, int q, int cod)
		?????
	void posiciona_dinamico(int mapa[MAX_H][MAX_W], int n, int m, Obj_Dinamico *obj)
		Posiciona tanto o bomberman como os inimigos
	void desenha_lab(SDL_Surface *screen, int mapa[MAX_H][MAX_W], int n, int m, SDL_Surface* s_chipset)
		Ele irá na tela de acordo com os números que estão na matriz

Main.c:
Inicializa vídeo e chama a função introducao e em seguida a menu.

Explode.c:
	void ativar_bomba(Bomba *bomba, int mapa[MAX_H][MAX_W], Obj_Dinamico *obj)
		O nome já diz. Chama a funcao_timer depois de 2s e a ultimo chama a funcao explode.

	Uint32 funcao_timer(Uint32 interval, void *param)
		usada na funcao ativar bomba

	void explode(int mapa[MAX_H][MAX_W], int coox, int cooy, int raio, int dir)
		Se tiver bomberman ele morre, bloco destrutivel some, etc...

	int avalia_ex(int coox, int cooy)
		Irá verificar se contiua explodindo ou nao, dependndo do que tiver no caminho

	void direcionar(int dir, int *ix, int *iy)
		????

	void morre_bomber()
		diminui uma vida dele, quando esta for menor que 0 ele tirá  salvar e retornará ao menu.

	void morre_inimigo(int cooy, int coox)
		diminui o numero de inimigos.

Outras.c:
	int menu2 (SDL_Surface *screen, int* voltar_pro_menu_inicial)
		é o menu que aparece qdo aperta ESC durane o jogo.
	void desenha_texto(char* texto, SDL_Surface* dst, int x, int y)
		Blita uma string na tela, como as coordenadas (x,y)
	void apaga_texto(SDL_Surface* dst, int x, int y)
		simula uma borracha, porém ela blita uma imagem com a cor do fundo por cima da letra.
	void f_introducao(void)
		Faz um efeito com duas imagens de fade in e fade out
	int f_menu ()
		Depois de passar pela introducao essa funcao da opcao de comeca um jogo, ver o recorde ou sair do jogo.
	int f_jogo ()
		Será explica mais adiante.
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
		Ira andar com o bomberman/Inimigo até a linha da grade (até ficar no quadrado)
	void define_din(Obj_Dinamico *obj,int x, int y, int i, int j, int inx, int iny, int cod, int ai)
		??????
	void move_inimigo(Obj_Dinamico *obj, int step, int mapa[MAX_H][MAX_W])
		O nome já diz.
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
		O nome já diz.
	Uint32 timer_invencibilidade(Uint32 interval, void *param)
		O nome já diz.

Agora que as funções já estão apresentadas, vamos falar de maneira geral do funcionamento do jogo.

Para a criação ficar mais fácil, optamos por usar uma matriz como se fosse um tabuleiro de xadrez. Cada quadrado do tabuleiro representa um número.

Depois lemos toda a matriz e blitamos na tela (de acordo com a proporção escolhida pelo programador) as imagens.
Por exempo:

0 = espaco vazio
1 = bomberman

matriz[4][4]

0000
0001
0000
0000

bomberman está na matriz[3][1]. Esse é um exemplo simples, porém é a base do jogo.

Ao redor disso existe somente detalhes, por exemplo, fazer uma simulação dele andando, dos inimigos andando.



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

Abra o terminal vá até a pasta do jogo e digite: make e aperte enter!
Ele irá compilar e excutar autmaticamente os arquivos.


Obrigado 
E bom jogo.












































