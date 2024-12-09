#include "set.h"
#include <stdio.h>
#include <stdlib.h>

int main(void){

    int tad;
    printf("Indique qual tipo de dado Abstrato deseja usar:\n  Digite 0 para : Árvore flamenguista:\n Digite 1 para : Árvore AVL:\n");
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
    int op = 0;
    while(op !=EOF){
        printf("Escolha uma das operações abaixo:\n");
        printf("Digite 1 para: set-imprimir de A e B\n ");
        printf("Digite 2 para: set-união de A e B\n ");
        printf("Digite 3 para: set-interseccao de A e B\n ");
        printf("Digite 4 para: set-pertence de A e B\n ");
        scanf("%d", &op);
        //Chamada da operação desejada
        switch (op)
        {
        case 1: setImprimir(A); printf("\n"); setImprimir(B); break;
        case 2: setUniao(A,B); break;
        case 3: setInterseccao(A,B); break;
        case 4: scanf("%d",&item); setPertence(A,item); scanf("%d",&item); setPertence(B,intem); break;
        }

    }
    




    return 0;
}