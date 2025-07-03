#include <stdlib.h>
#include <stdio.h>
#include "Tree.h"

void print(Tree *t) {
  if (t) {
    printf("%d ", t->value);
    print(t->left);    
    print(t->right);
  }
}

int parentRec(Tree *t, int v, int p) {
  int pLeft = 0, pRight = 0;
  
  if (t) {
      if (t->value == v)
        return p;
      else {
        pLeft = parentRec(t->left, v, t->value);
        pRight = parentRec(t->right, v, t->value);

        if (pLeft) 
          return pLeft;

        return pRight;
      }
  }

  return 0;
}

int parent(Tree *t, int v) {
  return parentRec(t, v, 0);
}

int main() {
  Tree *t = Tree_alloc(4, 
    Tree_alloc(9, 
        Tree_alloc(13, 
            Tree_alloc(78, NULL, NULL), 
            Tree_alloc(21, NULL, NULL)
        ),
        Tree_alloc(81, 
            Tree_alloc(10, NULL, NULL),
            Tree_alloc(2, NULL, NULL)
        ) 
    ),
    Tree_alloc(7, NULL, NULL)  
  );

  print(t);
  printf("\n");

  printf("10 -> pai (%d)\n", parent(t, 10));

  Tree_free(t);

  return 0;
}
