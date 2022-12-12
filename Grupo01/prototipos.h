#ifndef PROTOTIPOS_H_INCLUDED
#define PROTOTIPOS_H_INCLUDED

int Inicializa ();
void Inicializa_Variaveis ();
int Inicializa_SDL ();

int Carrega_Menu();
int Carrega_Versao_IMG (int);
int Carrega_Versao_Som (int);
int Carrega_Sons ();
int Carrega_Mapa ();
void Define_Transparencias ();

void Jogo ();

void Eventos_Menu (SDL_Event*, int*);
void Tela_Menu();

void Eventos_LeNome (SDL_Event*, int*);
void Tela_LeNome ();

void Eventos_Carregar (SDL_Event*, int*);
void Tela_Carregar ();

void Eventos_Recordes_T (SDL_Event*, int*);
void Tela_Recordes_T ();

void Eventos_Recordes_P (SDL_Event*, int*);
void Tela_Recordes_P ();

void Eventos_Creditos (SDL_Event*, int*);
void Tela_Instrucoes ();

void Eventos_Creditos (SDL_Event*, int*);
void Tela_Creditos ();

void Eventos_Salva (SDL_Event*, int*);
void Tela_Save ();

void Eventos_Pausa (SDL_Event*, int*);
void Tela_Pausa ();

void Eventos_Fase (SDL_Event*, int*);
void Eventos_Teclado (SDL_Event*, int*);
void Tela_Jogo();

void Eventos_GameOver (SDL_Event*, int*);
void Tela_GameOver();

int Dentro_Fora (SDL_Rect);
int Verifica_Botao (int);
void Colore_Botao (int);
void Define_Botoes ();
void Seleciona_Opcao (int, int*);
void Eventos_Menus (SDL_Event*, int*, int);

int Bonus (int i, int j);
void Verifica_Bonus ();
void Add_Bomba_Fila (int i, int j);
void Remove_Bomba_Fila ();
void Add_Bomba_Fila2 ();
void Remove_Bomba_Fila2 ();
int Explode_Espaco (int i, int j, char dir);
void Limpa_Espaco (int i, int j, char dir);
Uint32 Explosao_fim (Uint32 interval, void *param);

void Move_Personagem ();
void Explode_Bomba ();
void Reinicia_Jogo ();
void Salva_Jogo ();
void Verifica_Espaco (int, int, int*);

void Movimenta_Inimigo ();
void Move_Inimigo (int);
int Verifica_Dir (int, int, int, int);
void Muda_ij_Inimigo (int);
void Anda_Inimigo (int);
void Mata_Inimigo (int);
int Inimigo_Morreu (int);
int Diminui_Distancia (int);

void Reinicia_Fase ();
void Prepara_Inimigos ();
Uint32 Carrega_Fase_Seguinte (Uint32, void*);

void Verifica_Mortes ();
void Resolve_Mortos ();

void Desenha_Texto16 (char*, SDL_Surface*, int, int);
void Desenha_Texto22 (char*, SDL_Surface*, int, int);
void Desenha_Texto72 (char*, SDL_Surface*, int, int);

int Eh_RecordeT();
int Eh_RecordeP();
void Salva_RecordeP(int);
void Salva_RecordeT(int);

void Carrega_Dados ();
void Carrega_Jogo (int);

void Finaliza ();
void Salva_Dados ();

#endif // PROTOTIPOS_H_INCLUDED
