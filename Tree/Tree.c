#include <stdlib.h>
#include <stdio.h>
#include "Tree.h"

Tree *Tree_alloc(int value, Tree *l, Tree *r) {
  Tree *t = malloc(sizeof(Tree));

  if (t) {
    t->value = value;
    t->left = l;
    t->right = r;
  }

  return t;
}


void Tree_print(Tree *t) {
  if (t) {
    printf("%c ", t->value);
    Tree_print(t->left);
    Tree_print(t->right);
  }
}

void Tree_printNotation(Tree *t) {
  if (t) {
    printf("< %c ", t->value);
    Tree_print(t->left);
    Tree_print(t->right);  
    printf(" >");
  }
  else
    printf("<> ");
}

void Tree_free(Tree *t) {
  if (t) {
    Tree_free(t->left);
    Tree_free(t->right);
    free(t);
  }
}

