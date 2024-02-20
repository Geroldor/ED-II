/*
Implemente uma árvore rubro negra para administrar o sistema de alunos de uma escola. O 
ID deve ser a matrícula, que deve conter 04 dígitos. Além das funções básicas (inserção, 
remoção e etc), implemente também as funções a seguir:
 
Escreva métodos que calculem a altura (total) e a altura negra de uma árvore rubro-negra.

Acrescente um método que calcule o custo médio de uma busca (O custo da busca é o número 
de comparações de chaves).

Escreva uma função que calcule a percentagem de nós rubros e negros em uma árvore rubro-negra.

Apresente na tela as modificações ocorridas nas correções de inserção e remoção, por exemplo, 
o caso 3.1 (1°- Pai fica rubro; 2°-  Irmão fica Negro; 3° Rotacione o pai a esquerda; 4 °
Atualize o irmão;) 
*/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdbool.h>

//red = 1
//black = 0

typedef struct node
{
    int id;
    bool color;
    struct node *left;
    struct node *right;
} node, *PONT;

typedef struct redBlackTree{
    PONT root;
} redBlack, *redBlackTree;

void iniciarArvore(redBlackTree rb){
    rb->root = NULL;
}

PONT criarNo(int id){
    PONT novoNo = (PONT)malloc(sizeof(struct node));
    novoNo->id = id;
    novoNo->left = NULL;
    novoNo->right = NULL;

    return novoNo;
}

void insert(redBlackTree rb, PONT no){
    if (rb->root == NULL)
    {
    no->color = 1;
    rb->root = no;
    }else{
        
    }
    
}