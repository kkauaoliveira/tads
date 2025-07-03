#include <stdlib.h>
#include <stdio.h>
#include "Tree23.h"

int cmp(const void *a, const void *b) {
    const int *n1 = a;
    const int *n2 = b;
    return *n1 - *n2;
}

void print(Tree23_node *n) {

    if(n) {
        if (n->link_kind == INTERNAL_LINK) {
            print(n->left.node);

            //if (n->key_item1)
                //printf("k1.%d ", *((int*)n->key_item1));

            print(n->middle.node);

            //if (n->key_item2)
                //printf("k2.%d ", *((int*)n->key_item2));

            print(n->right.node);
        }
        else if (n->link_kind == LEAF_LINK) {
            if (n->left.item)
                printf("%d ", *((int*)n->left.item));
            if (n->middle.item)
                printf("%d ", *((int*)n->middle.item));
            if (n->right.item)
                printf("%d ", *((int*)n->right.item));
        }
    }
}

int main() {
    int n[9] = {3,8,56, 15,2,9, 14,89,90};
    Tree23 *t = Tree23_alloc(cmp);

    for (int i=0; i<9; i++) {
        Tree23_insert(t, &n[i]);
    }

    /*
    int x;
    if (t->root->link_kind == INTERNAL_LINK) {
        printf("INTERNAL_LINK\n");
        if (t->root->key_item1)
            printf("k1.%d\n", *((int*)t->root->key_item1));
        if (t->root->key_item2)
            printf("k2.%d\n", *((int*)t->root->key_item2));
        
    }
    if (t->root->link_kind == LEAF_LINK) {
        printf("LEAF_LINK\n");
        if (t->root->left.item)
            printf("l.%d\n", *((int*)t->root->left.item));
        if (t->root->middle.item)
            printf("m.%d\n", *((int*)t->root->middle.item));
        if (t->root->right.item)
            printf("r.%d\n", *((int*)t->root->right.item));
    }
    */

    print(t->root);
    printf("\n");

    Tree23_free(t);

    return 0;
}