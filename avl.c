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
	arvore->raiz = nosInserir(arvore->raiz, elemento);
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
	arvore->raiz = nosRemover(arvore->raiz, elemento);
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


int max(int a, int b){
	if(b > a){
		return b;
	}
	return a;
}
