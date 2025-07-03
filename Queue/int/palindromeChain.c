#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Queue.h"
#include "Stack.h"
#define SIZE 32

int main() {
    int i;
    char strA[SIZE], strB[SIZE], strC[SIZE];
    Queue *q = Queue_alloc(SIZE);
    Stack *s = Stack_alloc(SIZE);

    printf("Cadeia: ");
    scanf("%[^\n]", strA);
    
    for (i = 0; strA[i]; i++)
        if (strA[i] != ' ') {
            Queue_push(q, strA[i]);
            Stack_push(s, strA[i]);
        }

    memset(strB, '\0', SIZE);
    memset(strC, '\0', SIZE);

    for (i = 0; !Stack_isEmpty(s); i++) {
        strB[i] = Queue_pop(q);
        strC[i] = Stack_pop(s);
    }
    
    if (strcmp(strB, strC) == 0)
        printf("Is a palindrome chain (%s == %s)\n", strB, strC);
    else
        printf("Isn't a palindrome chain (%s != %s)\n", strB, strC);
    
    Queue_free(q);
    Stack_free(s);

    return 0;
}
