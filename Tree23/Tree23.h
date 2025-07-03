#ifndef TREE23_H
#define TREE23_H
/*
 *   Shane Saunders
 */

/* Stack size.  Specifies the maximum tree depth supported.
 * See Tree23_alloc() in Tree23.c.
 */
#define TREE23_STACK_SIZE 1000


/* There are two kinds of child pointers for nodes in the 2-3 tree.  The first
 * kind are pointers to other nodes.  The second kind are pointers to the leaf
 * items (data items) in the tree.
 */
struct Tree23_node;

typedef union Tree23_link {
    struct Tree23_node *node;  /* link to internal node... */
    void *item;                   /* ... or a link to a data item. */
} Tree23_link;

/* A node in the 2-3 tree maintains two keys and three child pointers.
 * A node in the 2-3 tree has between two and three children, except for the
 * special case where it is the root node of a tree containing only 0 or 1
 * nodes.  When a nodes has two children its left and middle child pointers are
 * used, and its right child pointer is NULL.  For a node which has three
 * children all child pointer are used.
 *
 * Data items in a two-three tree are all stored at the lowest level of the
 * tree as leaf items.  A node whose children are leaf items has its link_kind
 * field set to LEAF_LINK.  If the node's children are other nodes, then its
 * link_kind parameter will be set to INTERNAL_LINK.
 *
 * A node in the 2-3 tree has two keys:
 *    key_item1 - points to the item with the smallest key among items in the
 *                nodes middle-child subtree.  For the special case where a
 *                root node contains only 0 or 1 nodes, key_item1 is NULL.
 *    key_item2 - points to the item with the smallest key among items in the
 *                nodes right-child subtree.  If there is no right child, then
 *                key_item2 is NULL.
 *
 * The properties of child trees of a node in a 2-3 tree are:
 *     - data items i stored under the right-child subtree have
 *       key(key_item2) <= key(i).
 *     - data items i stored under the middle-child subtree have
 *       key(key_item1) <= key(i) < key(key_item2).
 *     - data items i stored under the left-child subtree have
 *       key(i) < key(key_item2).
 */
typedef struct Tree23_node {
    void *key_item1, *key_item2;
    Tree23_link left, middle, right;
    enum { LEAF_LINK, INTERNAL_LINK } link_kind;
} Tree23_node;

/* The 2-3 tree structure type has the following fields:
 *   root - a pointer to the root node.
 *   compar - a pointer to the function to use for comparing the keys of items
 *            in the tree.
 *   n - the number of data items stored in the tree.
 *   height - the height of the tree.
 *   min_item - a pointer to the minimum item in the 2-3 tree.
 */
typedef struct Tree23 {
    Tree23_node *root;
    int (* compar)(const void *, const void *);
    int n;
    void *min_item;
    Tree23_node **stack;
    signed char *path_info;
} Tree23;



/* Tree23_alloc() - Allocates space for a 2-3 tree and returns a pointer to
 * it.  The function compar compares they keys of two items, and returns a
 * negative, zero, or positive integer depending on whether the first item is
 * less than, equal to, or greater than the second.
 */
Tree23 *Tree23_alloc(int (* compar)(const void *, const void *));

/* Tree23_free() - Frees space used by the 2-3 tree pointed to by t. */
void Tree23_free(Tree23 *t);

/* Tree23_insert() - Inserts an item into the 2-3 tree pointed to by t,
 * according the the value its key.  The key of an item in the 2-3 tree must
 * be unique among items in the tree.  If an item with the same key already
 * exists in the tree, a pointer to that item is returned.  Otherwise, NULL is
 * returned, indicating insertion was successful.
 */
void *Tree23_insert(Tree23 *t, void *item);

/* Tree23_find() - Find an item in the 2-3 tree with the same key as the
 * item pointed to by `key_item'.  Returns a pointer to the item found, or NULL
 * if no item was found.
 */
void *Tree23_find(Tree23 *t, void *key_item);

/* Tree23_find_min() - Returns a pointer to the minimum item in the 2-3 tree
 * pointed to by t.  If there are no items in the tree a NULL pointer is
 * returned.
 */
void *Tree23_find_min(Tree23 *t);

/* Tree23_delete() - Delete the item in the 2-3 tree with the same key as
 * the item pointed to by `key_item'.  Returns a pointer to the deleted item,
 * and NULL if no item was found.
 */
void *Tree23_delete(Tree23 *t, void *key_item);

/* Tree23_delete_min() - Deletes the item with the smallest key from the
 * binary search tree pointed to by t.  Returns a pointer to the deleted item.
 * Returns a NULL pointer if there are no items in the tree.
 */
void *Tree23_delete_min(Tree23 *t);

#endif
