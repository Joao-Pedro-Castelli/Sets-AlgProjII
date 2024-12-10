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
NO* propagaDir(NO* raiz);
NO* removeMin(NO* raiz);
NO* propagaEsq(NO* raiz);
int auxPertence(NO* raiz, int elemento);
NO* auxInserir(NO* raiz, int elemento);
void inverteCor(NO* raiz);
NO* rotDir(NO* raiz);
NO* rotEsq(NO* raiz);
void auxApagar(NO** raiz);
int auxElementos(NO* raiz, int* vetor, int pos);
NO* minDir(NO* raiz);
NO* noCriar(int elemento);
void auxUnir(NO* adicionar, NO* sintese);
NO* auxRemover(NO* raiz, int elemento);
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

    if(raiz->dado > elemento){
        return auxPertence(raiz->esq,elemento);
    }
    
    return auxPertence(raiz->dir,elemento);
}

bool rbInserir(RB* rb, int elemento){
    if(rbPertence(rb,elemento)){
        return false;
    }
    if((rb->raiz = auxInserir(rb->raiz,elemento))!=NULL){
        rb->tamanho++;
        rb->raiz->cor = 0;
        return true;
    }
    else{
        return false;
    }
}

int Vermelho(NO* raiz){
    if(raiz == NULL){
        return 0;
    }

    return (raiz->cor == 1);
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

    if(Vermelho(raiz->dir) ==1 && !Vermelho(raiz->esq) ){
        raiz = rotEsq(raiz);
    }

    if(Vermelho(raiz->esq) && Vermelho(raiz->esq->esq)){
        raiz = rotDir(raiz);
    }

    if(Vermelho(raiz->esq) && Vermelho( raiz->dir)){
        inverteCor(raiz);
    }
    return raiz;


}

bool rbRemover(RB* rb, int elemento){
    if(!rbPertence(rb, elemento)){
        return false;
    }
    if((rb->raiz = auxRemover(rb->raiz, elemento) )!= NULL){
        return true;
    }
    return false;
}

NO* auxRemover(NO* raiz, int elemento){

    if(raiz == NULL){
        return raiz;
    }

    if(raiz->dado == elemento){
        if(raiz->esq == NULL || raiz->dir == NULL){
            NO* p = raiz;
            if(raiz->esq == NULL){
                raiz = raiz->dir;
            }
            else{
                raiz = raiz->esq;
            }
            free(p);
            p = NULL;
        }
        else{
            raiz = propagaDir(raiz);
            NO* aux = minDir(raiz->dir);
            raiz->dado = aux->dado;
            raiz->dir = removeMin(raiz->dir);
        }
    }
    else{
        if(elemento<raiz->dado){
            raiz = propagaEsq(raiz);
            raiz->esq = auxRemover(raiz->esq,elemento);

        }
        else{
            raiz = propagaDir(raiz);
            raiz->dir = auxRemover(raiz->dir,elemento);
        }
    }

    if(raiz!= NULL){
        if(Vermelho(raiz->dir) ==1 && !Vermelho(raiz->esq) ){
        raiz = rotEsq(raiz);
        }

        if(Vermelho(raiz->esq) && Vermelho(raiz->esq->esq)){
        raiz = rotDir(raiz);
        }

        if(Vermelho(raiz->esq) && Vermelho( raiz->dir)){
        inverteCor(raiz);
        }
        

    }
    return raiz;
    
}

NO* removeMin(NO* raiz){
    if(raiz->esq ==  NULL){
        NO* p = raiz;
        raiz = raiz->dir;

        free(p);
        p= NULL;

        return raiz;
    }
    raiz = propagaEsq(raiz);
    raiz->esq = removeMin(raiz->esq);
    return raiz;
}

NO* propagaEsq(NO* raiz){
    if(!Vermelho(raiz->esq)&& !Vermelho(raiz->esq->esq)){
        inverteCor(raiz);
        if(Vermelho(raiz->dir->esq)){
            raiz->dir = rotDir(raiz->dir);
            raiz = rotEsq(raiz);
            inverteCor(raiz);
        }
    }
    return raiz;
}

NO* propagaDir(NO* raiz){
    if(Vermelho(raiz->esq)){
        raiz = rotDir(raiz);
    }
    if(Vermelho(raiz->dir)&& !Vermelho(raiz->dir->esq)){
        inverteCor(raiz);
        if(Vermelho(raiz->esq->esq)){
            raiz = rotDir(raiz);
            inverteCor(raiz);
        }
    }
    return raiz;
}

NO* minDir(NO* raiz){
    if(raiz->esq == NULL){
        return raiz;
    }
    return minDir(raiz->esq);
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

    for(int i=0;i<rb->tamanho;i++){
        vetor[i] = -1;
    }
    if( vetor == NULL){
        return vetor;
    }
    auxElementos(rb->raiz,vetor,0);
    return vetor;
}

int auxElementos(NO* raiz, int* vetor, int pos){
    if(raiz == NULL){
        return pos;
    }

    
    
    pos = auxElementos(raiz->esq,vetor, pos);
    vetor[pos] = raiz->dado;
    pos++;
    pos = auxElementos(raiz->dir, vetor, pos);
    return pos;
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

    if(rb == NULL){
        return;
    }
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
    rbInserir(rb,4);
    rbInserir(rb,12);
    rbInserir(rb,5);
    rbInserir(rb,17);
    rbInserir(rb,13);
    rbInserir(rb,6);

    
    printar(rb->raiz);

    
   
    
    return 0;
}