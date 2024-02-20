#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

typedef struct no {
    int x;
    int y;
    struct no *prox;
} No;

typedef struct pilha {
    No *topo;
} Pilha;

Pilha *criaPilha() {
    Pilha *p = (Pilha *) malloc(sizeof(Pilha));
    p->topo = NULL;
    return p;
}

void push(Pilha *p, int x, int y) {
    No *novo = (No *) malloc(sizeof(No));
    novo->x = x;
    novo->y = y;
    novo->prox = p->topo;
    p->topo = novo;
}

No* pop(Pilha *p) {
    if (p->topo == NULL) {
        printf("Pilha vazia!");
    }
    No *aux = p->topo;
    No *aux2 = aux;
    p->topo = aux->prox;
    free(aux);
    return aux2;
}

void imprimePilha(Pilha *p) {
    No *aux = p->topo;
    if (aux != NULL)
    {
        while (aux->prox != NULL) {
        printf("(%d, %d)\n", aux->x, aux->y);
        aux = aux->prox;
        }
    }
    
    
}