typedef struct Stack Stack;

Stack *Stack_alloc(int size);
void   Stack_free(Stack *s);
int    Stack_isEmpty(Stack *s);
int    Stack_isFull(Stack *s);
void   Stack_push(Stack *s, int element);
int    Stack_pop(Stack *s);
int    Stack_top(Stack *s);

void   Stack_print(Stack *s);