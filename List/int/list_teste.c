#include <stdlib.h>
#include <stdio.h>
#include "List.h"

void print(Node *n) {
  if (n) {
    printf("%d->", n->value);
    print(n->next);  
  }
  else {
    printf("\n");  
  }
}

int main() {
  List *l = List_alloc();
  printf("l = %p\n", l);

  List_insert(l, 8);
  List_insert(l, 6);
  List_insert(l, 4);
  List_insert(l, 2);

  printf("%d->", l->first->value);
  printf("%d->", l->first->next->value);
  printf("%d->", l->first->next->next->value);
  printf("%d->\n", l->first->next->next->next->value);

  print(l->first);

  List_print(l);

  List_remove(l, 2);

  List_print(l);

  List_remove(l, 0);

  List_print(l);

  List_remove(l, 1);

  List_print(l);

  List_free(l);
  return 0;
}





