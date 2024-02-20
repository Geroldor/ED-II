#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
typedef struct node {
    int data;
    struct node *next;
} node;

node *make(int n){
    node *head = NULL;
    head = (node *) malloc(sizeof(node));
    head->data = n;
    return head;
}

void insert(int data, NODE head) {
    node *new_node = (node *) malloc(sizeof(node));
    node *n = head;
    new_node->data = data;
    new_node->next = n->next;
    n->next = new_node;
    head = n;
}

NODE search(int data, NODE head) {
    node *current = head;
    while (current != NULL) {
        if (current->data == data) {
            head = current;
            return head;
        }else{
            current = current->next;
        }
    }
}           

void print(NODE head) {
    node *current = head;
    while (current != NULL) {
        if (current == NULL)
        {
            break;
        }
        
        printf("%d ", current->data);
        current = current->next;
    }
}

void delete(int data, NODE head) {
    node *current = head;
    node *previous = NULL;
    while (current != NULL) {
        if (current->data == data) {
            if (previous == NULL) {
                head = current->next;
            } else {
                previous->next = current->next;
            }
            free(current);
            return;
        }
        previous = current;
        current = current->next;
    }
}

void free_list(NODE head) {
    node *current = head;
    node *next = NULL;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}