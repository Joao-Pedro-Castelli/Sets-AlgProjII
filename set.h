#ifndef _SET_H
#define _SET_H

	#include "ED1.h" //São as interfaces dos TADs que serão 
	#include "ED2.h" //utilizados para armazenar os Dados do Set.
			 //i.e, Set é um TAD que usa outros TADs. 

	#define ERRO -1023
	typedef struct set SET;

	SET *setCriar(int tipo);
	bool setPertence(SET *set, int elemento);
	bool setInserir (SET *set, int elemento);
	bool setRemover(SET *set, int elemento);
	void setApagar(SET **setptr);
	void setImprimir(SET *set);
	SET *setUniao(SET *setA, SET *setB);
	SET *setInterseccao(SET *setA, SET *setB);
  
#endif