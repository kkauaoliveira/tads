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

void List_insert(List* l, void *value) {
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

void *List_removeByIndex(List* l, int index) {
  Node *n = NULL, *ant = NULL;
  int count = 0;
  void *value = NULL;
  
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

void *List_removeByValue(List* l, void *key, int (*cmp)(void*, void*) ) {
  Node *n = NULL, *ant = NULL;
  void *value = NULL;
  
  if (l) {
    n = l->first;

    while (n) {
      if (cmp(n->value, key) == 0) {

        if (ant == NULL)
           l->first = n->next;
        else
          ant->next = n->next;
        
        value = n->value;     
        free(n);
        return value;
      }

      ant = n;
      n = n->next;
    }
  }
}

void *List_find(List* l, void *key, int (*cmp)(void*, void*) ) {
  Node *n = NULL;
  
  if (l) {
    n = l->first;

    while (n) {
      if (cmp(n->value, key) == 0) {
        return n->value;
      }

      n = n->next;
    }
  }

  return NULL;
}

void List_print(List *l, void (*print)(void*)) {
   Node *n = NULL;

   if (l) {
      n = l->first;

      while (n) {
        print(n->value);
        n = n->next;  
      }

      printf("\n");
   }
}





