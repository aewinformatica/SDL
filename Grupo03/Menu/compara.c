#include "meuinclude.h"

int compara(const void *e1, const void *e2)
{
	_SAVE *a = (_SAVE *)e1;
	_SAVE *b = (_SAVE *)e2;
	
	if(a->pontos > b->pontos) return -1;
	if(a->pontos < b->pontos) return 1;
	
	return strcmp(a->nome,b->nome);
}
