/*Trabalho de Algoritmo e estrutura de dados.
Docente: Rudinei Gularte
Discentes: Matheus Muzza Pires Ferreira - 15479468, João Pedro Monteiro Castelli

    O arquivo em questão fornece um dos TAD`S que serão utilizados no programa principal. A implementação proposta nesse arquivo 
    é deu uma árvore binária que segue a estrutura de uma left-Leaning Red-Black Tree. Foram criadas certas funções auxiliares a
    medida que foram surgindo necessidades para uma adequada implementação do TAD.

    Referências: Material disponibilizado das aulas de AVL e das árvores LLRB.
 */

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


NO* propagaDir(NO* raiz);//Faz a propagação da aresta vermelha para o lado direito
NO* removeMin(NO* raiz);// Quando achamos o valor mínimo da árvore direita que já substituiu o número que queremos retirar, nós o removemos;
NO* propagaEsq(NO* raiz);//Faz a propagação da aresta vermelha para o lado esquerdo para a remoção adequada de nós.
int auxPertence(NO* raiz, int elemento);//verifica se o inteiro elemento pertence a árvore binária red-black
NO* auxInserir(NO* raiz, int elemento);//Função que auxilia na inserção de um elemento na árvore binária red-black
void inverteCor(NO* raiz);//inverte a cor de um nó e de seus respectivos filhos quando eles não forem nulos
NO* rotDir(NO* raiz);// Rotaciona o nó para direita quando a árvore precisa ser balanceada
NO* rotEsq(NO* raiz);// Rotaciona o nó para a esquerda quando a árvore precisa ser balanceada
void auxApagar(NO** raiz);//Auxilia no momento de apagar a árvore binária red-black
int auxElementos(NO* raiz, int* vetor, int pos);//Função que auxilia na criação de um vetor com os elementos da árvore binária red-black.
NO* minDir(NO* raiz);//Encontra o menor valor que está a direita de um nó que queremos remover
NO* noCriar(int elemento);//Cria um nó que será inserido na árvore binária
void auxUnir(NO* adicionar, NO* sintese);//Função que une duas árvores binárias
NO* auxRemover(NO* raiz, int elemento);//Função que auxilia na remoção de um dado elemento que está presente na árvore binária red-black
void auxArrOrdenado(RB* sintese, int* elementos, int ini, int fim);//Função que transforma um array ordenado na árvore binária red-black

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

    return aux;
}

NO* rotEsq(NO* raiz){
    NO* aux = raiz->dir;

    raiz->dir = aux->esq;
    aux->esq = raiz;

   
    aux->cor = raiz->cor;
     raiz->cor = 1;

    return aux;
}



/*Cria a struct que auxiliará na manipulação da árvore.*/
RB* rbCriar(void){
    RB * rb = malloc(sizeof(RB));
    if(rb != NULL){
        rb->raiz = NULL;
        rb->tamanho = 0;
    }
    return rb;
}
/*Função responsável por ver se o elemento pertence a uma árvore fornecida.
    Saída: 
        true-> se pertence a árvore
        False->Se não pertence a árvore
 */
bool rbPertence(RB* rb, int elemento ){
    if(auxPertence(rb->raiz,elemento)){
        return true;
    }
    else{
        return false;
    }
}
/*Retorna 0 se o elemento não está contido na árvore, ou retorna 1 caso contrário */
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
/*Insere o elemento na árvore binária */
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
/*Analisa se um dado nó da árvore está ou não recebendo uma aresta vermelha */
int Vermelho(NO* raiz){
    if(raiz == NULL){
        return 0;
    }

    return (raiz->cor == 1);
}
/*Auxilia na inserção criando o nó e o colocando na posição correta, além de fazer os ajustes necessários, caso a árvore fique 
desbalanceada após a inserção */
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
/*Remove um elemento desejado da árvore que for passada por argumento. Faz os deslocamentos necessários das arestas vermelhas 
para esse processo. Além de fazer as correções necessárias quando ficarem desbalanceadas. Retorna true se o elemento foi retirado, 
e retorna false se o elemento pedido não estiver presente na árvore ou se não foi possível retirá-lo*/
bool rbRemover(RB* rb, int elemento){
    if(!rbPertence(rb, elemento)){
        return false;
    }
    if((rb->raiz = auxRemover(rb->raiz, elemento) )!= NULL){
        rb->tamanho--;
        return true;
        
    }
    return false;
}

NO* auxRemover(NO* raiz, int elemento){

    if(raiz == NULL){
        return raiz;
    }

    if(raiz->dado == elemento){
        /*Se o nó a ser retirado tem algum dos filhos como nulo, basta deslocar o filho não nulo para o local do nó pai,
         e apagar o nó pai, caso os dois sejam nulos um deles substituirá o pai e podemos apagá-lo em seguida  */
        if(raiz->esq == NULL || raiz->dir == NULL){
            NO* aux = raiz;
            if(raiz->esq == NULL){
                raiz = raiz->dir;
            }
            else{
                raiz = raiz->esq;
            }
            free(aux);
            aux = NULL;
        }
        /*Se o nó a ser retirado tem os dois filhos presentes, encontraremos o menor elemento da árvore direita e substituir 
        com o nó a ser retirado,precisamos propagar a aresta vermelha até o local de remoção,ou seja onde estava o menor elemento 
        da árvore direita, depois, removemos o menor elemento que estava duplicado por ter substituido o elemento a ser retirado*/  
        else{
            raiz = propagaDir(raiz);
            NO* aux = minDir(raiz->dir);//encontra o minimo elemento da direita
            raiz->dado = aux->dado;
            raiz->dir = removeMin(raiz->dir);// percorre até o local do minimo e o retira
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
    /*Parte de ajuste no retorno da recursão para corrigir algum desalinho com a estrutura da árvore LLRB*/
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
//apafa a árvore toda
void rbApagar(RB **rb){
    auxApagar(&(*rb)->raiz);
    free(*rb);
    *rb = NULL;

    return;
}
//Auxilia no processo recursivo para apagar os elementos
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
/*Função responsável por criar e retornar um array de inteiros que estão presentes na árvore que será passada como argumento.*/
int *rbElementos(RB* rb){
   int* vetor = malloc(sizeof(int)*rb->tamanho);

    if( vetor == NULL){
        return vetor;
    }
    auxElementos(rb->raiz,vetor,0);
    return vetor;
}
/*Auxilia na parte recursiva para inserir os elementos de forma ordenada no vetor que será retornado, para isso usamos um caminho 
que a interação com o nó é feita entre as chamadas recursivas */
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
//Retorna a quantidade de elementos da árvore
int rbTamanho(RB *rb){
    return rb->tamanho;
}
//retorna a árvore síntese que irá agora ter seus elementos e os elementos da árvore rb, que serão passados para a função.
RB* rbUnir(RB *sintese, RB *rb){
    auxUnir(rb->raiz,sintese->raiz);
    return sintese;
}
//Função que cria uma árvore LLRB tomando como base os elementos de um vetor que será passado para a função
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
//Une duas árvores em uma só, que será o retorno da função principal. A árvore síntese será a árvore que conterá os elementos de ambas.
void auxUnir(NO* adicionar, NO* sintese){
    if(adicionar == NULL){
        return;
    }

    auxUnir(adicionar->dir, sintese);
    auxUnir(adicionar->esq, sintese);

    auxInserir(sintese, adicionar->dado);
    return;
}
//função para percorrer a árvore e mostrar na tela todos os elementos
void printar(NO* rb){

    if(rb == NULL){
        return;
    }
    printf("%d ",rb->dado);
    printar(rb->esq);
    printar(rb->dir);
}
