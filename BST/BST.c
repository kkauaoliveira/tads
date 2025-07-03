#include <stdlib.h>
#include <stdio.h>
#include "BST.h"

BST *BST_alloc(int (*compar)(void*, void*)) {
    BST *bst = NULL;

    if (compar) {
        bst = malloc(sizeof(BST));

        bst->n = 0;
        bst->root = NULL;
        bst->cmp = compar;
    }

    return bst;
}

void BST_insert(BST *bst, void *value) {
    BST_node *new = NULL;
    BST_node *n = NULL;

    if (bst && value) {
        new = malloc(sizeof(BST_node));
        new->value = value;
        new->left = NULL;
        new->right = NULL;

        if (bst->n == 0) {
            bst->root = new;
            bst->n++;
        }
        else {
            n = bst->root;

            while (n) {
                if (bst->cmp(n->value, new->value) > 0){
                    if (n->left == NULL) {
                        n->left = new;
                        bst->n++;
                        break;
                    }
                    n = n->left;
                }
                else if (bst->cmp(n->value, new->value) < 0){
                    if (n->right == NULL) {
                        n->right = new;
                        bst->n++;
                        break;
                    }
                    n = n->right;
                }
                else
                    break;
            }
        }
    }
}

void printBST(BST_node *n, void (*print)(void*)) {
    if (n) {
        printBST(n->left, print);
        print(n->value);
        printBST(n->right, print);
    }
}

void BST_print(BST *bst, void (*print)(void*)) {
    if (bst && print) {
        printBST(bst->root, print);
        printf("\n");
    }
}

void freeBST(BST_node *n) {
    if (n) {
        freeBST(n->left);
        freeBST(n->right);
        free(n);
    }
}

void BST_free(BST *bst) {
    if (bst) {
        freeBST(bst->root);
        free(bst);
    }
}

void *BST_search(BST *bst, void *key) {
    BST_node *n = NULL;

    if (bst && key) {
        n = bst->root;

        while (n) {
           if (bst->cmp(n->value, key) == 0) {
                return n->value;
           }
           else if (bst->cmp(n->value, key) > 0) {
                n = n->left;
           }
           else {
                n = n->right;
           }
        }
    }

    return NULL;
}

BST_node *BST_searchNode(BST *bst, void *key) {
    BST_node *n = NULL;

    if (bst && key) {
        n = bst->root;

        while (n) {
           if (bst->cmp(n->value, key) == 0) {
                return n;
           }
           else if (bst->cmp(n->value, key) > 0) {
                n = n->left;
           }
           else {
                n = n->right;
           }
        }
    }

    return NULL;
}

BST_node *BST_searchParent(BST *bst, void *key) {
    BST_node *n = NULL, *p = NULL;

    if (bst && key) {
        n = bst->root;

        while (n) {
           if (bst->cmp(n->value, key) == 0) {
                return p;
           }
           else if (bst->cmp(n->value, key) > 0) {
                p = n;
                n = n->left;
           }
           else {
                p = n;
                n = n->right;
           }
        }
    }

    return NULL;
}

void *BST_remove(BST *bst, void *key) {
    BST_node *q, *p, *pr, *r;
    void *value = NULL;

    if (bst && key) {
        r = BST_searchNode(bst, key);
        if (r) {
            pr = BST_searchParent(bst, r->value);
            q = r->left;

            if (q) {
                p = r;
                while (q->right) {
                    p = q;
                    q = q->right;
                }

                if (q != r->left) {
                    p->right = q->left;
                }

                if (q != r->left)
                    q->left = r->left;
                
                q->right = r->right;
            }
            
            if (pr) {
                if (r == pr->left)
                    pr->left = q;
                else
                    pr->right = q;
            }
            else {
                bst->root = q;
            }

            bst->n--;

            value = r->value;
            free(r);
        }
    }

    return value;
}















