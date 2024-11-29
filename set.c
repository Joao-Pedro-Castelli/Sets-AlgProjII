#include <stdio.h>
#include "set.h"

struct set{
	void *arvore;
	int tipo; //tipo: 0 == AVL, 1 == rubro-negra
};

SET *setCriar(int tipo){
	SET *set = (SET *) malloc(sizeof(SET));
	if(tipo == 0){
		set->arvore = avlCriar(); //primeira ED, arvore AVL
	}
	else if(tipo == 1){
		set->arvore = rbCriar(); //segunda ED, arvore rubro-negra
	}
	if(set->arvore == NULL){ //caso a arvore nao foi criada, o tipo indica que ocorreu um erro
		set->tipo = ERRO;
	else{
		set->tipo = tipo;
	}
	return set;
}

bool setPertence(SET *set, int elemento){
	if(set == NULL){
		return false;
	}
	if(set->tipo == 0){
		return avlPertence(set->arvore, elemento); //como estamos lidando com TADs, nao podemos acessar as arvores diretamente,
							   //precisamos usar as funcoes especificas deles.
	}
	else if(set->tipo == 1){
		return rbPertence(set->arvore, elemento);
	}
	return false; //caso o tipo nao seja 0 ou 1, nao iremos mexer no set, algo esta errado
}

bool setInserir(SET *set, int elemento){
	if(set == NULL){
		return false;
	}
	if(set->tipo == 0){
		return avlInserir(set->arvore, elemento);
	}
	else if(set->tipo == 1){
		return rbInserir(set->arvore, elemento);
	}
	return false;
}

bool setRemover(SET *set, int elemento){
	if(set == NULL){
		return false;
	}
	if(set->tipo == 0){
		return avlRemover(set->arvore, elemento);
	}
	else if(set->tipo == 1){
		return rbRemover(set->arvore, elemento);
	}
	return false;
}

void setApagar(SET **setptr){
	if(*set == NULL){
		return;
	}
	if((*set)->tipo == 0){
		avlApagar((*set)->arvore);
	}
	else if((*set)->tipo == 1){
		rbApagar((*set)->arvore);
	}
	(*set)->arvore = NULL;
	free(*set);
	*set = NULL;
}
