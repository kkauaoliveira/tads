#include <stdlib.h>
#include <stdio.h>
#include "Tree.h"

void print(Tree *t) {
  if (t) {
    print(t->left);
    printf("%c ", t->value);
    print(t->right);
  }
}

int evaluate(Tree *t) {   
  if (t) {
      switch (t->value) {
          case '+': return evaluate(t->left) + evaluate(t->right);
          case '-': return evaluate(t->left) - evaluate(t->right);
          case '*': return evaluate(t->left) * evaluate(t->right);
          case '/': return evaluate(t->left) / evaluate(t->right);
          default:  return t->value - '0';
      }
  }

  return 0;
}

int main() {
  Tree *t = Tree_alloc('+', 
    Tree_alloc('*', 
        Tree_alloc('+', 
            Tree_alloc('3', NULL, NULL), 
            Tree_alloc('6', NULL, NULL)
        ),
        Tree_alloc('-', 
            Tree_alloc('4', NULL, NULL),
            Tree_alloc('1', NULL, NULL)
        ) 
    ),
    Tree_alloc('5', NULL, NULL)  
  );

  print(t);
  printf(" = %d\n", evaluate(t));

  Tree_free(t);

  return 0;
}
