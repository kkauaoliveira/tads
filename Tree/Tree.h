typedef struct Tree Tree;

struct Tree {
  int value;
  Tree *left;
  Tree *right;
};

Tree *Tree_alloc(int value, Tree *l, Tree *r);
void  Tree_free(Tree *t);
void  Tree_print(Tree *t);
