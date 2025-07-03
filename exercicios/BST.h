typedef struct BST BST;
typedef struct BST_node BST_node;

struct BST_node {
	void *value;
	BST_node *left, *right;
};

struct BST {
	int n;
	BST_node *root;
	int (*cmp)(void*, void*);
};

BST  *BST_alloc(int (*compar)(void*, void*));
void  BST_free(BST *bst);
void  BST_insert(BST *bst, void *value);
void *BST_search(BST *bst, void *key);
void *BST_remove(BST *bst, void *key);
void  BST_print(BST *bst, void (*print)(void*));
BST_node *BST_searchNode(BST *bst, void *key);
BST_node *BST_searchParent(BST *bst, void *key);

