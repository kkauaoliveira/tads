#include <stdlib.h>
#include <stdio.h>
#include "BST.h"
#include "List.h"

int cmp(void *a, void *b){
    int *valor1 = a;
    int *valor2 = b;
    return *valor1 - *valor2;
}

void print(void *l){
    int *a = l;
    printf("%d ", *a);
}

void _preenche_lista_in_order(BST_node *node, List *l) {
    if (node == NULL) {
        return;
    }
    _preenche_lista_in_order(node->left, l); 
    List_insert(l, node->value);              
    _preenche_lista_in_order(node->right, l); 
}

void preenche_lista(BST_node *b, List *l) { 
    if (l == NULL) {
        return; 
    }
    _preenche_lista_in_order(b, l); 
}

int main(){
    BST *b = BST_alloc(cmp);
    int vetor[8] = {20, 33, 19, 18, 32, 66, 10, 9};

    List *l = List_alloc(); 

    for (int i = 0; i < 8; i++)
    {
        BST_insert(b, &vetor[i]);
    }

    preenche_lista(b->root, l);
    List_print(l, print);

    BST_free(b);
    List_free(l); 
    return 0;
}