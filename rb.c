#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "set.h"
#include "rb.h"


typedef struct no NO;
struct no{
    int dado;
    int cor;
    NO* esq;
    NO* dir;
};
 struct rb {
    NO* raiz;
    int tamanho;
};

int auxPertence(NO* raiz, int elemento);
NO* auxInserir(NO* raiz, int elemento);
void inverteCor(NO* raiz);
NO* rotDir(NO* raiz);
NO* rotEsq(NO* raiz);
void auxApagar(NO** raiz);
void auxElementos(NO* raiz, int* vetor, int pos);
void minDir(NO* atual, NO* anterior, NO*raiz);
NO* noCriar(int elemento);
void auxUnir(NO* adicionar, NO* sintese);
NO* auxRemover(NO** raiz, int elemento);
void auxArrOrdenado(RB* sintese, int* elementos, int ini, int fim);

NO* noCriar(int elemento){
    NO* n = malloc(sizeof(NO));
    if(n!=NULL){
        n->cor = 1;
        n->dado = elemento;
        n->dir =  NULL;
        n->esq = NULL;
    }

    return n;
}



void inverteCor(NO* raiz){

    raiz->cor = !raiz->cor;
    if(raiz->esq){
        raiz->esq->cor = !raiz->esq->cor;
    }
    if(raiz->dir){
        raiz->dir->cor = !raiz->dir->cor;
    }
}

NO* rotDir(NO* raiz){
    NO* aux = raiz->esq;

    raiz->esq = aux->dir;
    aux->dir = raiz;
    aux->cor = raiz->cor;

    raiz->cor =1;

    return raiz;
}

NO* rotEsq(NO* raiz){
    NO* aux = raiz->dir;

    raiz->dir = aux->esq;
    aux->esq = raiz;

    raiz->cor = 1;
    aux->cor = raiz->cor;

    return aux;
}




RB* rbCriar(void){
    RB * rb = malloc(sizeof(RB));
    if(rb != NULL){
        rb->raiz = NULL;
        rb->tamanho = 0;
    }
    return rb;
}

bool rbPertence(RB* rb, int elemento ){
    if(auxPertence(rb->raiz,elemento)){
        return true;
    }
    else{
        return false;
    }
}

int auxPertence(NO* raiz, int elemento){
    if(raiz == NULL){
        return 0;
    }

    if(raiz->dado == elemento){
        return 1;
    }

    if(auxPertence(raiz->dir,elemento)){
        return 1;
    }
    else{
        return auxPertence(raiz->esq,elemento);
    }
}

bool rbInserir(RB* rb, int elemento){
    if((rb->raiz = auxInserir(rb->raiz,elemento))!=NULL){
        rb->tamanho++;
        rb->raiz->cor = 0;
        return true;
    }
    else{
        return false;
    }
}

NO* auxInserir(NO* raiz, int elemento){
   if(raiz == NULL){
        return noCriar(elemento);
   }

    if(raiz->dado > elemento){
        raiz->esq = auxInserir(raiz->esq,elemento);
        }
    if(raiz->dado < elemento){
        raiz->dir = auxInserir(raiz->dir,elemento);
    }

    if(raiz->dir->cor ==1 && raiz->esq->cor != 1){
        raiz = rotEsq(raiz);
    }

    if(raiz->esq->cor ==1 && raiz->esq->esq->cor == 1){
        raiz = rotDir(raiz);
    }

    if(raiz->esq->cor ==1 && raiz->dir->cor == 1){
        inverteCor(raiz);
    }
    return raiz;


}

bool rbRemover(RB** rb, int elemento){
    if(auxRemover(&(*rb)->raiz, elemento) != NULL){
        return true;
    }
    return false;
}

NO* auxRemover(NO** raiz, int elemento){

    if(*raiz == NULL){
        return *raiz;
    }

    if((*raiz)->esq == NULL || (*raiz)->dir == NULL){
         NO* p;
         p = *raiz;
        if((*raiz)->esq == NULL){
            *raiz = (*raiz)->dir;
            free(p);
            p = NULL;
            return *raiz;   
        }
        else{
            (*raiz) = (*raiz)->esq;
            free(p);
            p = NULL;
        }
    }
    else{
        minDir(((*raiz)->dir),(*raiz),(*raiz));
    }
    
}

void minDir(NO* atual, NO* anterior, NO* raiz){

    
    if(raiz->esq == NULL){
        if(anterior == raiz){
            int aux = atual->dado;
            atual->dado = raiz->dado;
            raiz->dado = aux;
        }
    }


    minDir(raiz->esq,atual, raiz);
}

void rbApagar(RB **rb){
    auxApagar(&(*rb)->raiz);
    free(*rb);
    *rb = NULL;

    return;
}

void auxApagar(NO**raiz){
    if(*raiz == NULL){
        return;
    }

    auxApagar(&((*raiz)->esq));
    auxApagar(&((*raiz)->dir));

    free(*raiz);
    *raiz = NULL;

    return;
}

int *rbElementos(RB* rb){
   int* vetor = malloc(sizeof(int)*rb->tamanho);

    if( vetor == NULL){
        printf("oi");
        return vetor;
    }
    auxElementos(rb->raiz,vetor,0);
    return vetor;
}

void auxElementos(NO* raiz, int* vetor, int pos){
    if(raiz == NULL){
        return;
    }

    vetor[pos] = raiz->dado;

    auxElementos(raiz->esq,vetor, 2*pos+1);    
    auxElementos(raiz->dir, vetor, 2*pos +2);

}

int rbTamanho(RB *rb){
    return rb->tamanho;
}

RB* rbUnir(RB *sintese, RB *rb){
    auxUnir(rb->raiz,sintese->raiz);
    return sintese;
}

RB* rbArrOrdenado( int* elementos, int tamanho){
    RB* sintese = rbCriar();

    if(sintese != NULL){
        auxArrOrdenado(sintese, elementos, 0, tamanho-1);
    }
    return sintese;
    
}

void auxArrOrdenado(RB* sintese, int* elementos, int ini, int fim){
    if(ini == fim){
        rbInserir(sintese, elementos[ini]);
        return;
    }

    int meio = (ini + fim)/2;
    rbInserir(sintese, elementos[meio]);

    if(meio-1>=0){
        auxArrOrdenado(sintese, elementos,0, meio - 1);
    }
    
    if(meio+1<=fim){
        auxArrOrdenado(sintese, elementos, meio + 1, fim);
    }
    
}

void auxUnir(NO* adicionar, NO* sintese){
    if(adicionar == NULL){
        return;
    }

    auxUnir(adicionar->dir, sintese);
    auxUnir(adicionar->esq, sintese);

    auxInserir(sintese, adicionar->dado);
    return;
}

void printar(NO* rb){

    printf("oi");
    if(rb == NULL){
        return;
    }
    printf("%d ",rb->dado);
    printar(rb->esq);
    printar(rb->dir);
}

int main(){
    RB* rb = rbCriar();

    if(rb== NULL){
        printf("MERDA");
        exit(1);
    }
    rbInserir(rb, 1);
    rbInserir(rb,2);
    rbInserir(rb,3);
    
    
    return 0;


}