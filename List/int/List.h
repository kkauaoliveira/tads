typedef struct List List;
typedef struct Node Node;

struct List {
  int length;
  Node *first;
};

struct Node {
  int value;
  Node *next;
};

List *List_alloc();
void  List_free(List *l);
void  List_insert(List* l, int value);
int   List_remove(List* l, int index);

void  List_print(List *l);





