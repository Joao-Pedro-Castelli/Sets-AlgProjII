#include "set.h"
#include <stdio.h>
#include <stdlib.h>

int main(void){

    int tad;
    //Leitura do tipo de dado desejado
    scanf("%d", &tad);
    //Criação dos conjuntos passando o     
    SET* A = setCriar(tad);
    SET* B = setCriar(tad); 
    //Leitura dos tamanhos e dos elementos de cada conjunto
    int tamA, tamB;

    scanf("%d %d", &tamA,&tamB);

    int item;
    for(int i=0; i<tamA; i++){
        scanf("%d", &item);
        setInserir(A,item);
    }

    for(int i=0; i<tamB; i++){
        scanf("%d", &item);
        setInserir(B,item);
    }

    //Leitura da operação desejada
        int op;
        scanf("%d", &op);
        int elemento;

        //Chamada da operação desejada
    switch (op){
        case 1: scanf("%d", &elemento); 
		if(setPertence(A,elemento)){
			printf("Pertence.\n");
		}else{
			printf("Nao pertence.\n");
		}
		; break;
        case 2: SET* uni = setUniao(A,B); setImprimir(uni); break;
        case 3: SET* inter = setInterseccao(A,B); setImprimir(inter); break;
        case 4: scanf("%d",&item); setRemover(A,item); setImprimir(A); break;
    }
    




    return 0;
}
