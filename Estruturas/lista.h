#ifndef LISTA_H
#define LISTA_H

typedef void *NODE;

NODE *make(int n);

void insert(int data, NODE head);

NODE search(int data, NODE head);

void print(NODE head);

void delete(int data, NODE head);

void free_list(NODE head);
#endif