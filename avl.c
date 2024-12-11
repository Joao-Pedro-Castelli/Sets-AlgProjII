#include <stdio.h>
#include "avl.h"

typedef struct no{
	int chave;
	struct no *fiEsq;
	struct no *fiDir;
	int altura;
	int FB;
} NO;

struct avl{
	NO *raiz;
	int tamanho;
};

NO *noCriar(int elemento);
	//cria um no com malloc e retorna um ponteiro para ele.
bool nosProcurar(NO *raiz, int elemento);
	//funcao recursiva para procurar o no com a chave == elemento.
NO *nosInserir(NO *raiz, int elemento);
	//recursiva: cria um no com chave = elemento, coloca no lugar certo e balanceia a AVL.
NO *nosRemover(NO *raiz, int elemento);
	//recursiva: remove um no com chave == elemento e balanceia a AVl.
NO *nosTrocaMaior(NO *raiz);
	//pega o no com a maior chave na subarvore esquerda do no a ser removido e retorna este no
	//enquanto balanceia a AVL.
NO *rotacaoEsquerda(NO *raiz);
	//aumenta a altura do fiDir e do fiDir, diminui a altura da raiz.
NO *rotacaoDireita(NO *raiz);
	//aumenta a altura do fiEsq, diminui a altura da raiz.
NO *rotacaoEsqDir(NO *raiz);
	//diminui a altura da raiz e do fiEsq, aumenta a altura do raiz->fiEsq->fiDir.
NO *rotacaoDirEsq(NO *raiz);
	//diminui a altura da raiz e do fiDir, aumenta a altura do raiz->fiDir->fiEsq.
void nosApagar(NO *raiz);
	//recursiva: vai colocando os ponteiros esquerdo e direito como nulo e dando free nos nos.
NO *nosArrayOrdenado(int *ordenado, int comeco, int fim);
	//recursiva: cria uma arvore e seus nos partindo de um array ordenado
	//mais informacoes em: "sorted array to BST"
int nosElementos(NO *raiz, int *elementos, int i);
	//recursiva: coloca as chaves dos nos no array elementos em-ordem.
void alturaFbAtualizar(NO *no);
	//procedimentos para colocar os valores corretos em no->altura e no->FB.
int calcAltura(NO *no);
	//se no eh nulo, altura eh -1, senao altura == no->altura.
NO *noBalancear(NO *raiz);
	//verifica se o FB eh -2 ou 2 e realiza as rotacoes necessarias.
int max(int a, int b);
	//retorna o maior numero entre os dois



AVL *avlCriar(){
	AVL *arvore = (AVL *) malloc(sizeof(AVL));
	if(arvore != NULL){
		arvore->tamanho = 0;
		arvore->raiz = NULL;
	}
	return arvore;
}

NO *noCriar(int elemento){
	NO *no = (NO *) malloc(sizeof(NO));
	if(no != NULL){
		no->chave = elemento;
		no->fiEsq = NULL;
		no->fiDir = NULL;
		no->altura = 0;
		no->FB = 0;
	}
	return no;
}

bool avlPertence(AVL *arvore, int elemento){
	if(arvore == NULL){
		return false;
	}
	return nosProcurar(arvore->raiz, elemento);
}

bool nosProcurar(NO *raiz, int elemento){
	if(raiz == NULL){
		return false;
	}
	int chave = raiz->chave;
	if(chave == elemento){
		return true;
	}
	if(chave > elemento){
		return nosProcurar(raiz->fiEsq, elemento);
	}
	if(chave < elemento){
		return nosProcurar(raiz->fiDir, elemento);
	}
	return false;
}

bool avlInserir(AVL *arvore, int elemento){
	if(arvore == NULL){
		return false;
	}
	if(avlPertence(arvore, elemento)){
		return true;
	}
	arvore->raiz = nosInserir(arvore->raiz, elemento);
	arvore->tamanho++;
	return true;
}

NO *nosInserir(NO *raiz, int elemento){
	if(raiz == NULL){
		return noCriar(elemento);
	}
	if(raiz->chave > elemento){
		raiz->fiEsq = nosInserir(raiz->fiEsq, elemento);
	}
	else if(raiz->chave < elemento){
		raiz->fiDir = nosInserir(raiz->fiDir, elemento);
	}
	else{
		return raiz; //se o elemento == chave, ele ja esta na arvore e nao precisa ser inserido.
	}


	alturaFbAtualizar(raiz);
	raiz =  noBalancear(raiz);

	return raiz;
}

bool avlRemover(AVL *arvore, int elemento){
	if(arvore == NULL){
		return false;
	}
	if(avlPertence(arvore, elemento)){
		arvore->raiz = nosRemover(arvore->raiz, elemento);
		arvore->tamanho--;
	}
	return true;
}

NO *nosRemover(NO *raiz, int elemento){
	if(raiz == NULL){
		return NULL;
	}
	NO *noAux;
	if(raiz->chave == elemento){
		noAux = raiz;
		if(raiz->fiEsq == NULL){
			raiz = raiz->fiDir;
			free(noAux);
			noAux = NULL;
		}
		else if(raiz->fiDir == NULL){
			raiz = raiz->fiEsq;
			free(noAux);
			noAux = NULL;
		}
		else if(raiz->fiEsq->fiDir == NULL){
			raiz = raiz->fiEsq;
			raiz->fiDir = noAux->fiDir;
			free(noAux);
			noAux = NULL;
		}
		else{
			raiz = nosTrocaMaior(raiz->fiEsq);
			raiz->fiDir = noAux->fiDir;
			raiz->fiEsq = noAux->fiEsq;
			free(noAux);
			noAux = NULL;
			alturaFbAtualizar(raiz->fiEsq);
			raiz->fiEsq =  noBalancear(raiz->fiEsq);
		}
	}

	else if(raiz->chave > elemento){
		raiz->fiEsq = nosRemover(raiz->fiEsq, elemento);
	}
	else{
		raiz->fiDir = nosRemover(raiz->fiDir, elemento);
	}
	
	if(raiz != NULL){
		alturaFbAtualizar(raiz);
		raiz = noBalancear(raiz);
	}
	return raiz;
}

NO *nosTrocaMaior(NO *raiz){
	if(raiz->fiDir->fiDir != NULL){
		NO *subs = nosTrocaMaior(raiz->fiDir);
		alturaFbAtualizar(raiz->fiDir);
		raiz->fiDir = noBalancear(raiz->fiDir);
		return subs;
	}
	NO *aux = raiz->fiDir;
	raiz->fiDir = aux->fiEsq;
	return aux;
}

NO *rotacaoEsquerda(NO *raiz){
	NO *fi = raiz->fiDir;
	raiz->fiDir = fi->fiEsq;
	fi->fiEsq = raiz;
	alturaFbAtualizar(raiz);
	alturaFbAtualizar(fi);

	return fi;
}

NO *rotacaoDireita(NO *raiz){
	NO *fi = raiz->fiEsq;
	raiz->fiEsq = fi->fiDir;
	fi->fiDir = raiz;
	alturaFbAtualizar(raiz);
	alturaFbAtualizar(fi);

	return fi;
}

NO *rotacaoEsqDir(NO *raiz){
	NO *novaRaiz = raiz->fiEsq->fiDir;
	NO *fi = raiz->fiEsq;
	fi->fiDir = novaRaiz->fiEsq;
	raiz->fiEsq = novaRaiz->fiDir;
	novaRaiz->fiEsq = fi;
	novaRaiz->fiDir = raiz;

	alturaFbAtualizar(raiz);
	alturaFbAtualizar(fi);
	alturaFbAtualizar(novaRaiz);
	return novaRaiz;
}

NO *rotacaoDirEsq(NO *raiz){
	NO *novaRaiz = raiz->fiDir->fiEsq;
	NO *fi = raiz->fiDir;
	fi->fiEsq = novaRaiz->fiDir;
	raiz->fiDir = novaRaiz->fiEsq;
	novaRaiz->fiEsq = raiz;
	novaRaiz->fiDir = fi;

	alturaFbAtualizar(raiz);
	alturaFbAtualizar(fi);
	alturaFbAtualizar(novaRaiz);
	return novaRaiz;
}

void avlApagar(AVL *arvore){
	if(arvore == NULL){
		return;
	}
	nosApagar(arvore->raiz);
	arvore->raiz = NULL;
	free(arvore);
	arvore = NULL; //isso nao fara que o ponteiro original se torne nulo, mas eh apenas para esta propria funcao.
	return;
}

void nosApagar(NO *raiz){
	if(raiz == NULL){
		return;
	}
	nosApagar(raiz->fiEsq);
	raiz->fiEsq = NULL;
	nosApagar(raiz->fiDir);
	raiz->fiDir = NULL;
	free(raiz);
	return;
}

AVL *avlArrOrdenado(int *ordenado, int n){
	AVL *sintese = avlCriar();
	if(sintese == NULL){
		printf("erro avlArrayOrdenado: sintese nao pode ser criada\n");
		return NULL;
	}
	sintese->raiz = nosArrayOrdenado(ordenado, 0, n - 1);
	return sintese;
}

NO *nosArrayOrdenado(int *ordenado, int comeco, int fim){
	if(comeco > fim){
		return NULL;
	}

	int meio = (comeco + fim) / 2;
	NO *raiz = noCriar(ordenado[meio]);
	raiz->fiEsq = nosArrayOrdenado(ordenado, comeco, meio - 1);
	raiz->fiDir = nosArrayOrdenado(ordenado, meio + 1, fim);

	int altura1, altura2;
	if(raiz->fiEsq == NULL){
		altura1 = -1;
	}
	else{
		altura1 = raiz->fiEsq->altura;
	}
	if(raiz->fiDir == NULL){
		altura2 = -1;
	}
	else{
		altura2 = raiz->fiDir->altura;
	}
	raiz->FB = altura1 - altura2;
	return raiz;
}

int *avlElementos(AVL *arvore){
	int *elementos = (int *) malloc(sizeof(int) * arvore->tamanho);
	int i = 0;
	nosElementos(arvore->raiz, elementos, i);
	return elementos;
}

int nosElementos(NO *raiz, int *elementos, int i){
	if(raiz == NULL){
		return i;
	}
	elementos[i] = raiz->chave;
	i++;
	i = nosElementos(raiz->fiEsq, elementos, i);
	i = nosElementos(raiz->fiDir, elementos, i);
	return i;
}

int avlTamanho(AVL *arvore){
	if(arvore == NULL){
		return ERRO;
	}
	return arvore->tamanho;
}

void alturaFbAtualizar(NO *no){
	no->altura = max(calcAltura(no->fiEsq), calcAltura(no->fiDir)) + 1;
	no->FB = calcAltura(no->fiEsq) - calcAltura(no->fiDir);
}

int calcAltura(NO *no){
	if(no == NULL){
		return -1;
	}
	else{
		return no->altura;
	}
}

NO *noBalancear(NO *raiz){
	if(raiz->FB == -2){
		if(raiz->fiDir->FB <= 0){
			raiz = rotacaoEsquerda(raiz);
		}
		else{
			raiz = rotacaoDirEsq(raiz);
		}
	}
	else if(raiz->FB == 2){
		if(raiz->fiEsq->FB >= 0){
			raiz = rotacaoDireita(raiz);
		}
		else{
			raiz = rotacaoEsqDir(raiz);
		}
	}
	return raiz;
}

int max(int a, int b){
	if(b > a){
		return b;
	}
	return a;
}
