#include <stdio.h>
#include "set.h"

struct set{
	void *arvore;
	int tipo; //tipo: 0 == AVL, 1 == rubro-negra
};

SET *setCriar(int tipo){
	SET *set = (SET *) malloc(sizeof(SET));
	if(set == NULL){
		return NULL;
	}
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

void setImprimir(SET *set){
	if(set == NULL){
		printf("O set não existe!\n");
		return;
	}
	int *elementos;
	if((elementos = setElementos(set)) == NULL){
		printf("O tipo do set não existe!\n");
		return;
	}
	int n;
	if((n = setTamanho(set)) == ERRO){
		printf("Algo deu errado com o tamanho do set!\n");
		return;
	}
	for(int i = 0; i < n; i++){
		printf("%d ", elementos[i]);
	}
	free(elementos);
	elementos = NULL;
	putchar('\n');
	return;
}

SET *setUniao(SET *setA, SET *setB){
//para a uniao, irei colocar o setA no sintese, o set que sera retornado,
//e chamarei uma funcao especifica de cada arvore chamada unir.
	if(setA == NULL){
		if(setB == NULL){
			return NULL;
		}
		else{
			return setB;
		}
	}
	SET *sintese = setCopiar(setA);
	if(sintese->tipo == 0){
		avlUnir(sintese->arvore, setB->arvore);
	}
	else if(sintese->tipo == 1){
		rbUnir(sintese->arvore, setB->arvore);
	}
	return sintese;
}

SET *setInterseccao(SET *setA, SET *setB){
//para a interseccao, irei pegar todos os elementos do setA
//e irei colocando no sintese, set que sera retornado, todos os elementos que pertencerem ao setB tambem.
	if(setA == NULL || setB == NULL){
		return NULL;
	}	
	SET *sintese = set_criar(setA->tipo);
	int *elementos = setElementos(setA);
	int n = setTamanho(setA);
	for(int i = 0; i < n; i++){
		if(setPertence(setB, elementosA[i])){
			if(!setInserir(sintese, elementosA[i])){
				printf("erro na insercao durante interseccao!\n");
				return NULL;
			}
		}
	}
	free(elementos);
	elementos = NULL;
	return sintese;
}

int *setElementos(SET *set){
//todos os elementos do set em um array de inteiros.
//as funcoes avl e rb Elementos retornam array gerados por malloc. Quem chamar a funcao setElementos tem a responsabilidade
//de realizar free() apos usar o array.
	if(set->tipo == 0){
		return avlElementos(set->arvore);
	}
	else if(set->tipo == 1){
		return rbElementos(set->arvore);
	}
	return NULL;
}

int setTamanho(SET *set){
//numero de elementos no set.
	if(set->tipo == 0){
		return avlTamanho(set->arvore);
	else if(set->tipo == 1){
		return rbTamanho(set->arvore);
	}
	return ERRO;
}
