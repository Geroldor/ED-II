#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RED 0
#define BLACK 1

typedef struct Node {
    int id;
    int color;
    struct Node *left, *right, *parent;
} Node;

Node *root = NULL;

Node *createNode(int id) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->id = id;
    newNode->color = RED;
    newNode->left = newNode->right = newNode->parent = NULL;
    return newNode;
}

void rotateLeft(Node *x) {
    Node *y = x->right;
    x->right = y->left;
    if (y->left != NULL) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NULL) {
        root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

void rotateRight(Node *x) {
    Node *y = x->left;
    x->left = y->right;
    if (y->right != NULL) {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NULL) {
        root = y;
    } else if (x == x->parent->right) {
        x->parent->right = y;
    } else {
        x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
}

void fixViolation(Node *newNode) {
    Node *parent = NULL;
    Node *grandParent = NULL;
    while ((newNode != root) && (newNode->color != BLACK) && (newNode->parent->color == RED)) {
        parent = newNode->parent;
        grandParent = newNode->parent->parent;
        if (parent == grandParent->left) {
            Node *uncle = grandParent->right;
            if (uncle != NULL && uncle->color == RED) {
                grandParent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                newNode = grandParent;
            } else {
                if (newNode == parent->right) {
                    rotateLeft(parent);
                    newNode = parent;
                    parent = newNode->parent;
                }
                rotateRight(grandParent);
                int temp = parent->color;
                parent->color = grandParent->color;
                grandParent->color = temp;
                newNode = parent;
            }
        } else {
            Node *uncle = grandParent->left;
            if (uncle != NULL && uncle->color == RED) {
                grandParent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                newNode = grandParent;
            } else {
                if (newNode == parent->left) {
                    rotateRight(parent);
                    newNode = parent;
                    parent = newNode->parent;
                }
                rotateLeft(grandParent);
                int temp = parent->color;
                parent->color = grandParent->color;
                grandParent->color = temp;
                newNode = parent;
            }
        }
    }
    root->color = BLACK;
}

void insert(int id) {
    Node *newNode = createNode(id);
    Node *parent = NULL;
    Node *current = root;
    while (current != NULL) {
        parent = current;
        if (newNode->id < current->id) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    newNode->parent = parent;
    if (parent == NULL) {
        root = newNode;
    } else if (newNode->id < parent->id) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }
    fixViolation(newNode);
}

void print(Node *root, int space) {
    if (root == NULL) {
        return;
    }
    space += 5;
    print(root->right, space);
    printf("\n");
    for (int i = 5; i < space; i++) {
        printf(" ");
    }
    if (root->color == RED) {
        printf("%d(R)\n", root->id);
    } else {
        printf("%d(B)\n", root->id);
    }
    print(root->left, space);
}

int calculateHeight(Node *root) {
    if (root == NULL) {
        return 0;
    }
    int leftHeight = calculateHeight(root->left);
    int rightHeight = calculateHeight(root->right);
    return leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1;
}

int calculateBlackNodes(Node *root) {
    if (root == NULL) {
        return 1;
    }
    int leftBlackNodes = calculateBlackNodes(root->left);
    int rightBlackNodes = calculateBlackNodes(root->right);
    if (leftBlackNodes != rightBlackNodes) {
        return -1;
    }
    return root->color == BLACK ? leftBlackNodes + 1 : leftBlackNodes;
}

int calculateRedNodes(Node *root) {
    if (root == NULL) {
        return 0;
    }
    int leftRedNodes = calculateRedNodes(root->left);
    int rightRedNodes = calculateRedNodes(root->right);
    return root->color == RED ? leftRedNodes + rightRedNodes + 1 : leftRedNodes + rightRedNodes;
}

int main() {
    insert(7);
    insert(3);
    insert(18);
    insert(10);
    insert(22);
    insert(8);
    insert(11);
    insert(26);
    insert(2);
    insert(6);
    insert(13);
    print(root, 0);
    printf("Height: %d\n", calculateHeight(root));
    printf("Black Nodes: %d\n", calculateBlackNodes(root));
    printf("Red Nodes: %d\n", calculateRedNodes(root));
    return 0;
}