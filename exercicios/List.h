typedef struct List List;
typedef struct Node Node;

struct List {
  int length;
  Node *first;
};

struct Node {
  void *value;
  Node *next;
};

List *List_alloc();
void  List_free(List *l);
void  List_insert(List* l, void *value);

void *List_removeByIndex(List* l, int index);

void *List_removeByValue(List* l, void *value, int (*cmp)(void*, void*) );
void *List_find(List* l, void *key, int (*cmp)(void*, void*) );

void  List_print(List *l, void (*print)(void*));









