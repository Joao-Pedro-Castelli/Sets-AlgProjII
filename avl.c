#include "avl.h"

typedef struct no{
	int chave;
	struct no *filhoEsq;
	struct no *filhoDir;
	int altura;
	int FB;
} NO;

struct avl{
	NO *raiz;
	int tamanho;
}

NO *noCriar(int elemento); //cria um no com malloc e retorna um ponteiro para ele
bool nosProcurar(NO *raiz, int elemento); //funcao recursiva para procurar o no com a chave == elemento
NO *nosInserir(NO *raiz, int elemento); //recursiva: cria um no com chave = elemento, coloca no lugar certo e balanceia a AVL
NO *nosRemover(NO *raiz, int elemento); //recursiva: remove um no com chave == elemento e balanceia a AVl
NO *nosTrocaMaior(NO *raiz); //pega o no com a maior chave na subarvore esquerda do no a ser removido e retorna este no
			     //enquanto balanceia a AVL
void nosApagar(NO *raiz); //recursiva: vai colocando os ponteiros esquerdo e direito como nulo e dando free nos nos.
NO *nosArrayOrdenado(int *ordenado, int comeco, int fim); //recursiva: cria uma arvore e seus nos partindo de um array ordenado
							  //mais informacoes em: "sorted array to BST"
int nosElementos(NO *raiz, int *elementos, int i); //recursiva: coloca as chaves dos nos no array elementos em-ordem.
int max(int a, int b); //retorna o maior numero entre os dois



AVL *avlCriar(){
	AVL *arvore = (AVL *) malloc(sizeof(AVL));
	if(arvore != NULL){
		arvore->tamanho = -1;
		arvore->raiz = NULL;
	}
	return arvore;
}

NO *noCriar(int elemento){
	NO *no = (NO *) malloc(sizeof(NO));
	if(no != NULL){
		no->chave = elemento;
		no->filhoEsq = NULL;
		no->filhoDir = NULL;
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
		return nosProcurar(raiz->filhoEsq, elemento);
	}
	if(chave < elemento){
		return nosProcurar(raiz->filhoDir, elemento);
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
		raiz->filhoEsq = nosInserir(raiz->filhoEsq, elemento);
	}
	else if(raiz->chave < elemento){
		raiz->filhoDir = nosInserir(raiz->filhoDir, elemento);
	}
	else{
		return raiz; //se o elemento == chave, ele ja esta na arvore e nao precisa ser inserido.
	}


	int alturaEsq, alturaDir;
	if(raiz->filhoEsq == NULL){
		alturaEsq = -1;
	}
	else{
		alturaEsq = raiz->filhoEsq->altura;
	}
	if(raiz->filhoDir == NULL){
		alturaDir = -1;
	}
	else{
		alturaDir = raiz->filhoDir->altura;
	}
	raiz->altura = max(alturaEsq, alturaDir) + 1;
	raiz->FB = alturaEsq - alturaDir;

	if(raiz->FB == -2){
		if(raiz->filhoDir->FB <= 0){
			raiz = rotacaoEsq(raiz);
		}
		else{
			raiz = rotacaoDirEsq(raiz);
		}
	}
	else if(raiz->FB == 2){
		if(raiz->filhoEsq->FB >= 0){
			raiz = rotacaoDir(raiz);
		}
		else{
			raiz = rotacaoEsqDir(raiz);
		}
	}

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
		if(raiz->filhoEsq == NULL){
			raiz = raiz->filhoDir;
			free(noAux);
			noAux = NULL;
		}
		else if(raiz->filhoDir == NULL){
			raiz = raiz->filhoEsq;
			free(noAux);
			noAux = NULL;
		}
		else if(raiz->filhoEsq->filhoDir == NULL){
			raiz = raiz->filhoEsq;
			raiz>filhoDir = noAux->filhoDir;
			free(noAux);
			noAux = NULL;
		}
		else{
			raiz = nosTrocaMaior(raiz->filhoEsq);
			int alturaEsq, alturaDir;	
			if(raiz->filhoEsq->filhoEsq == NULL){
				alturaEsq = -1;
			}
			else{
				alturaEsq = raiz->filhoEsq->filhoEsq->altura;
			}
			if(raiz->filhoEsq->filhoDir == NULL){
				alturaDir = -1;
			}
			else{
				alturaDir = raiz->filhoEsq->filhoDir->altura;
			}
			raiz->filhoEsq->altura = max(alturaEsq, alturaDir) + 1;
			raiz->filhoEsq->FB = alturaEsq - alturaDir;
			if(raiz->filhoEsq->FB == -2){
				if(raiz->filhoEsq->filhoDir->FB <= 0){
					raiz->filhoEsq = rotacaoEsquerda(raiz->filhoEsq);
				}
				else{
					raiz->filhoEsq = rotacaoDirEsq(raiz->filhoEsq);
				}
			}
			else if(raiz->filhoEsq->FB == 2){
				if(raiz->filhoEsq->filhoEsq->FB >= 0){
					raiz->filhoEsq = rotacaoDireita(raiz->filhoEsq);
				}
				else{
					raiz->filhoEsq = rotacaoEsqDir(raiz->filhoEsq);
				}
			}
			raiz->filhoDir = noAux->filhoDir;
			raiz->filhoEsq = noAux->filhoEsq;
			free(noAux);
			noAux = NULL;
		}
	}

	else if(raiz->chave > elemento){
		raiz->filhoEsq = nosRemover(raiz->filhoEsq);
	}
	else{
		raiz->filhoDir = nosRemover(raiz->filhoDir);
	}
	
	if(raiz != NULL){
		int alturaEsq, alturaDir;
		if(raiz->filhoEsq == NULL){
			alturaEsq = -1;
		}
		else{
			alturaEsq = raiz->filhoEsq->altura;
		}
		if(raiz->filhoDir == NULL){
			alturaDir = -1;
		}
		else{
			alturaDir = raiz->filhoDir->altura;
		}
		raiz->altura = max(alturaEsq, alturaDir) + 1;
		raiz->FB = alturaEsq - alturaDir;
		if(raiz->FB == -2){
			if(raiz->filhoDir->FB <= 0){
				raiz->filhoDir = rotacaoEsquerda(raiz);
			}
			else{
				raiz = rotacaoDirEsq(raiz);
			}
		}
		else if(raiz->FB == 2){
			if(raiz->filhoEsq->FB >= 0){
				raiz = rotacaoDireita(raiz);
			}
			else{
				raiz = rotacaoEsqDir(raiz);
			}
		}
	}
	return raiz;
}

NO *nosTrocaMaior(NO *raiz){
	if(raiz->filhoDir->filhoDir != NULL){
		NO *subs = nosTrocaMaior(raiz->filhoDir);
		int alturaEsq, alturaDir;	
		if(raiz->filhoDir->filhoEsq == NULL){
			alturaEsq = -1;
		}
		else{
			alturaEsq = raiz->filhoDir->filhoEsq->altura;
		}
		if(raiz->filhoDir->filhoDir == NULL){
			alturaDir = -1;
		}
		else{
			alturaDir = raiz->filhoDir->filhoDir->altura;
		}
		raiz->filhoDir->altura = max(alturaEsq, alturaDir) + 1;
		raiz->filhoDir->FB = alturaEsq - alturaDir;
		if(raiz->filhoDir->FB == -2){
			if(raiz->filhoDir->filhoDir->FB <= 0){
				raiz->filhoDir = rotacaoEsquerda(raiz->filhoDir);
			}
			else{
				raiz->filhoDir = rotacaoDirEsq(raiz->filhoDir);
			}
		}
		else if(raiz->filhoDir->FB == 2){
			if(raiz->filhoDir->filhoEsq->FB >= 0){
				raiz->filhoDir = rotacaoDireita(raiz->filhoDir);
			}
			else{
				raiz->filhoDir = rotacaoEsqDir(raiz->filhoDir);
			}
		}
		return subs;
	}
	NO *aux = raiz->filhoDir;
	raiz->filhoDir = aux->filhoEsq;
	return aux;
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
		return NULL;
	}
	nosApagar(raiz->fiEsq);
	raiz->fiEsq = NULL;
	nosApagar(raiz->fiDir);
	raiz->fiDir = NULL;
	free(raiz);
	return;
}

void avlArrOrdenado(AVL *sintese, int *ordenado, int n){
	if(sintese = NULL){
		return;
	}
	if(sintese->raiz != NULL){
		printf("erro avlArrayOrdenado: sintese nao esta vazio\n");
		return;
	}
	sintese->raiz = nosArrayOrdenado(ordenado, 0, n - 1);
	return;
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
	return;
}

int nosElementos(NO *raiz, int *elementos, int i){
	if(raiz == NULL){
		return i;
	}
	i = nosElementos(raiz->fiEsq, elementos, i);
	elementos[i] = raiz->chave;
	i = nosElementos(raiz->fiDir, elementos, i);
	return i;
}

int avlTamanho(AVL *arvore){
	if(arvore == NULL){
		return ERRO;
	}
	return arvore->tamanho;
}


int max(int a, int b){
	if(b > a){
		return b;
	}
	return a;
}
