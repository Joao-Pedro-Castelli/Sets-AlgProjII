#ifndef _AVL_H
#define _AVL_H


	#include <stdbool.h>
	#include <stdlib.h>

	#define ERRO -1023

	typedef struct avl AVL;

	AVL *avlCriar(void);
	bool avlPertence(AVL *arvore, int elemento);
	bool avlInserir(AVL *arvore, int elemento);
	bool avlRemover(AVL *arvore, int elemento);
	void avlApagar(AVL *arvore);
	AVL* avlArrOrdenado(int *ordenado, int n);
	int *avlElementos(AVL *arvore);
	int avlTamanho(AVL *arvore);

#endif
