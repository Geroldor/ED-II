#ifndef PILHA_H
#define PILHA_H

#include <stdio.h>
#include <stdlib.h>

typedef struct no No;

typedef struct pilha Pilha;

Pilha *criaPilha();
/**
 * @brief Criar uma pilha
 * 
 * @return Pilha*
 */

void push(Pilha *p, int x, int y);
/**
 * @brief Adiciona itens a pilha
 * 
 * @param p Pilha para adicionar
 * @param x Coordenada x
 * @param y Coordenada y
 */

No* pop(Pilha *p);
/**
 * @brief remove o item no topo da pilha
 * 
 * @param p Pilha
 */

void imprimePilha(Pilha *p);
/**
 * @brief Imprime a pilha
 * 
 * @param p Pilha
 */

#endif