#include <stdlib.h>
#include <stdio.h>
#include "List.h"

List *List_alloc() {
  List *l = malloc(sizeof(List));

  if (l) {
    l->length = 0;
    l->first = NULL;
  }

  return l;
}

void List_free(List *l) {
  Node *n, *aux;

  if (l) {
    n = l->first;
    free(l);

    while (n) {
      aux = n->next;
      free(n);
      n = aux;    
    }
  }
}

void List_insert(List* l, int value) {
  Node *new = NULL;
  
  if (l) {
      new = malloc(sizeof(Node));
      new->value = value;
      new->next = NULL;

      if (l->length > 0)
         new->next = l->first;
      
      l->first = new;
      l->length++;
  }
}

int List_remove(List* l, int index) {
  Node *n = NULL, *ant = NULL;
  int count = 0, value = 0;
  
  if (l && index >= 0) {
    n = l->first;

    while (n) {
      if (count == index) {
        if (index == 0)
           l->first = n->next;
        else
          ant->next = n->next;
        
        value = n->value;     
        free(n);
        return value;
      }

      ant = n;
      n = n->next;
      count++;
    }
  }
}




void List_print(List *l) {
   Node *n = NULL;

   if (l) {
      n = l->first;

      while (n) {
        printf("%d->", n->value);
        n = n->next;  
      }

      printf("\n");
   }
}





