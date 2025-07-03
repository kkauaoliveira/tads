#include <stdlib.h>
#include <stdio.h>
#include "BST.h"

int cmpInt(void *a, void *b) {
    int *n1 = a;
    int *n2 = b;

    return *n1 - *n2;
}

void printInt(void *a) {
    int *n = a;
    printf("%d ", *n);
}

void print(BST_node *n) {
	if (n) {
		printf("[%d ", *((int*)n->value));
		print(n->left);
		print(n->right);
		printf("]");
	}
	else
		printf(" . ");
}

int main() {
    int n[7] = {19,7,27,5,12,20,32};
    BST *b = BST_alloc(cmpInt);

    for (int i=0; i<7; i++)
        BST_insert(b, &n[i]);

    print(b->root);
	printf("\n");

	int x = 12;
	
	BST_remove(b, &x);
	print(b->root);
	printf("\n");



    return 0;
}