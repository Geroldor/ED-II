#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#define true 1
#define false 0

typedef int bool;
typedef int TIPOCHAVE;
typedef struct aux {
TIPOCHAVE chave;
struct aux *esq;
struct aux *dir;
int bal;
} NO, *PONT;

/* cria um novo (aloca memoria e preenche valores) no com chave=ch e retorna seu endereço */
PONT criarNovoNo(TIPOCHAVE ch){
    PONT novoNo = (PONT)malloc(sizeof(NO));
    novoNo->chave = ch;
    novoNo->esq = NULL;
    novoNo->dir = NULL;
    novoNo->bal = 0;
    return novoNo;
}

// Retorna o maior valor entre dois inteiros
int max(int a, int b){
    if (a>b)
    {
        return a;
    }
    else
    {
        return b;
    }
    
}

// Retorna a altura de uma (sub-)arvore
int altura(PONT p){
    if (!p){ 
        return -1;
    }
    return 1 + max(altura(p->esq), altura(p->dir));
}

/* Exibe arvore Em Ordem */
void exibirArvoreEmOrdem(PONT raiz){
    if (raiz != NULL){
        exibirArvoreEmOrdem(raiz->esq);
        printf("%d ", raiz->chave);
        exibirArvoreEmOrdem(raiz->dir);
    }
}

/* Exibe arvore Pre Ordem */
void exibirArvorePreOrdem(PONT raiz){
    if (raiz != NULL){
        printf("%d ", raiz->chave);
        exibirArvorePreOrdem(raiz->esq);
        exibirArvorePreOrdem(raiz->dir);
    }
}

/* Exibe arvore Pos Ordem */
void exibirArvorePosOrdem(PONT raiz){
    if (raiz != NULL){
        exibirArvorePosOrdem(raiz->esq);
        exibirArvorePosOrdem(raiz->dir);
        printf("%d ", raiz->chave);
    }
}

/* Exibe arvore Em Ordem (com parenteses para os filhos) */
void exibirArvore(PONT raiz){
    if (raiz != NULL){
        printf("%d", raiz->chave);
        printf("(");
        exibirArvore(raiz->esq);
        exibirArvore(raiz->dir);
        printf(")");
    }
}

/* Exibe arvore Pre-Ordem indicando pai de cada no */
void exibirArvore2(PONT raiz, TIPOCHAVE chavePai){
    if (raiz != NULL){
        printf("%d", raiz->chave);
        if (raiz->esq != NULL || raiz->dir !=
        NULL){
            printf("(");
            exibirArvore2(raiz->esq, raiz->chave);
            printf(",");
            exibirArvore2(raiz->dir, raiz->chave);
            printf(")");
        }
    }
}

// Verifica se árvore é AVL
bool ehAVL(PONT p){
    if (!p){
        return true;
    }
    if (abs(altura(p->esq) - altura(p->dir)) > 1){
        return false;
    }
    return ehAVL(p->esq) && ehAVL(p->dir);
}

// Atualiza o balancemento total
int atualizarBalanceamentoTotal(PONT raiz){
    if (!raiz){
        return 0;
    }
    raiz->bal = altura(raiz->dir) -
    altura(raiz->esq);
    return raiz->bal;
}

/* Rotações à direita (LL e LR)
Retornará o endereço do nó que será a
nova raiz da subárvore originalmente
iniciada por p */
PONT rotacaoL(PONT p){

    //pega os filhos do nó p para rotacionar
    PONT x = p->dir;
    PONT y = p->esq;

    //rotaciona para a esquerda, nó x assume a raiz
    x->esq = p;
    x->dir = y;

    p->bal = atualizarBalanceamentoTotal(p);
    x->bal = atualizarBalanceamentoTotal(x);

    return x;
}

/* Rotações à esquerda (RR e RL)
Retornará o endereço do nó que será a
nova raiz da subárvore originalmente iniciada por p */
PONT rotacaoR(PONT p){
    PONT x = p->esq;
    PONT y = p->dir;

    x->dir = p;
    x->esq = y;

    p->bal = atualizarBalanceamentoTotal(p);
    x->bal = atualizarBalanceamentoTotal(x);

    return x;
}

/* Inserção AVL: p é inicializado com o
endereco do nó raiz e alterou com false
*/
void inserirAVL(PONT* pp, TIPOCHAVE ch, bool* alterou){
    PONT p = *pp;
    if (!p){
        *pp = criarNovoNo(ch);
        *alterou = true;
        return;
    }
    if (ch == p->chave){
        *alterou = false;
        return;
    }
    if (ch < p->chave){
        inserirAVL(&(p->esq), ch, alterou);
        if (*alterou){
            atualizarBalanceamentoTotal(p);
            if (p->bal == 2){
                if (p->dir->bal == -1){
                    p = rotacaoR(p->dir);
                }
                p = rotacaoL(p);
                *pp = p;
            }
        }
    }
    else{
        inserirAVL(&(p->dir), ch, alterou);
        if (*alterou){
            atualizarBalanceamentoTotal(p);
            if (p->bal == -2){
                if (p->esq->bal == 1){
                    p = rotacaoL(p->esq);
                }
                p = rotacaoR(p);
                *pp = p;
            }
        }
    }
}

/* retorna o endereco do NO que contem
chave=ch ou NULL caso a chave nao seja
encontrada. Utiliza busca binaria
recursiva
*/
PONT buscaBinaria(TIPOCHAVE ch, PONT raiz){
    if (!raiz){
        return NULL;
    }
    if (raiz->chave == ch){
        return raiz;
    }
    if (ch < raiz->chave){
        return buscaBinaria(ch, raiz->esq);
    }
    return buscaBinaria(ch, raiz->dir);
}

// Busca binária não recursiva devolvendo o nó pai
PONT buscaNo(PONT raiz, TIPOCHAVE ch, PONT *pai){
    PONT atual = raiz;
    *pai = NULL;
    while (atual){
        if (atual->chave == ch){
            return atual;
        }
        *pai = atual;
        if (ch < atual->chave){
            atual = atual->esq;
        }
        else{
            atual = atual->dir;
        }
    }
    return NULL;
}

/* Auxilir da funcao excluirChave,
procura a maior chave menor que a chave
que será excluida */
PONT maiorAEsquerda(PONT p, PONT *ant){
    *ant = p;
    p = p->esq;
    while (p->dir){
        *ant = p;
        p = p->dir;
    }
    return p;
}


/* exclui a chave com valor igual a ch*/
bool excluirAVL(PONT* raiz, TIPOCHAVE ch, bool* alterou){
    PONT p = *raiz;
    if (!p){ // Se p é NULL
        *alterou = false;
        return false;
    }
    if (ch < p->chave){
        if (excluirAVL(&(p->esq), ch, alterou)){
            if (*alterou){
                atualizarBalanceamentoTotal(p);
                if (p->bal == -2){
                    if (p->esq->bal == 1){
                        p = rotacaoL(p->esq);
                    }
                    p = rotacaoR(p);
                    *raiz = p;
                }
                else{
                    *alterou = false;
                }
            }
        }
    }
    else if (ch > p->chave){ //Se a chave inserida for menor que a do nó selecionado
        if (excluirAVL(&(p->dir), ch, alterou)){
            if (*alterou){
                atualizarBalanceamentoTotal(p);
                if (p->bal == 2){
                    if (p->dir->bal == -1){
                        p = rotacaoR(p->dir);
                    }
                    p = rotacaoL(p);
                    *raiz = p;
                }
                else{
                    *alterou = false;
                }
            }
        }
    }
    else{ //se a chave é maior ou igual ao nó
        if (!p->esq || !p->dir){
            PONT aux = p;
            if (p->esq){
                p = p->esq;
            }
            else{
                p = p->dir;
            }
            free(aux);
            *raiz = p;
            *alterou = true;
        }
        else{
            PONT ant;
            PONT maior = maiorAEsquerda(p, &ant);
            p->chave = maior->chave;
            if (excluirAVL(&(p->esq), p->chave,
            alterou)){
                if (*alterou){
                    atualizarBalanceamentoTotal(p);
                    if (p->bal == -2){
                        if (p->esq->bal == 1){
                            p = rotacaoL(p->esq);
                        }
                        p = rotacaoR(p);
                        *raiz = p;
                    }
                    else{
                        *alterou = false;
                    }
                }
            }
        }
    }
    return *alterou;
}


/* funcao auxiliar na destruicao
(liberacao da memoria) de uma arvore */
void destruirAux(PONT subRaiz){
    if (subRaiz){
        destruirAux(subRaiz->esq);
        destruirAux(subRaiz->dir);
        free(subRaiz);
    }
}


/* libera toda memoria de uma arvore e
coloca NULL no valor da raiz */
void destruirArvore(PONT *raiz){
    destruirAux(*raiz);
    *raiz = NULL;
}


//inicializa arvore
void inicializar(PONT *raiz){
    *raiz = NULL;
}


int main(){
    PONT raiz;
    inicializar(&raiz);
    bool alterou;
    int n;
    do{
        printf("Digite um numero (ou -1 para sair): ");
        scanf("%d", &n);
        if (n != -1){
            inserirAVL(&raiz, n, &alterou);
            printf("Arvore AVL: ");
            exibirArvore(raiz);
            printf("\n");
        }
    } while (n != -1);
    printf("Arvore AVL: ");
    exibirArvore(raiz);
}