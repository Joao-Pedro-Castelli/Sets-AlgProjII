#ifndef _RB_H
#define _RB_H


#include <stdbool.h>
#include <stdlib.h>
    
typedef struct rb RB;

	RB *rbCriar(void);
	bool rbPertence(RB *rb, int elemento);
	bool rbInserir(RB *rb, int elemento);
	bool rbRemover(RB *rb, int elemento);
	void rbApagar(RB **rb);
    RB* rbUnir(RB *sintese, RB *rb);
	int *rbElementos(RB *rb);
	int rbTamanho(RB *rb);

#endif
