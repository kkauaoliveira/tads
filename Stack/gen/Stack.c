#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Stack.h"

struct Stack {
	int size;
	int top;
	void **elements;
};

Stack *Stack_alloc(int size) { 
	Stack *s = malloc(sizeof(Stack));
	
	assert(s != NULL);
	
	if (s) {
		s->size = size;
		s->top = -1;
		s->elements = calloc(size, sizeof(void*));
		
		assert(s->elements != NULL);
		
		if (s->elements == NULL) {
			free(s);
			s = NULL;
		}
	}
	
	return s;
}

void   Stack_free(Stack *s) { 
	
	assert(s != NULL);
	
	if (s) {
		free(s->elements);
		free(s);
	}
}

int    Stack_isEmpty(Stack *s) { 
	
	assert(s != NULL);
	
	if (s)
		return s->top == -1;
	
	return 1;
}

int    Stack_isFull(Stack *s) { 
	
	assert(s != NULL);
	
	if (s)
		return s->top == s->size-1;
	
	return 0;
}

void   Stack_push(Stack *s, void *element) { 
	assert(s != NULL);
	
	if (s) {
		if (!Stack_isFull(s)) {
			s->top++;
			s->elements[s->top] = element;
		}
	}
}

void *Stack_pop(Stack *s) { 
	void *topElement = NULL;
	
	if (s) {
		if (!Stack_isEmpty(s)) {
			topElement = s->elements[s->top];
			s->top--;
		}
	}
	
	return topElement;
}

void *Stack_top(Stack *s) { 
	if (s) {
		if (!Stack_isEmpty(s))
			return s->elements[s->top];
	}
	
	return NULL;
}

void Stack_print(Stack *s, void (*print)(void *) ) { 
	if (s) {
		printf("Stack (%d)\n", s->top+1);
		
		for (int i = s->top; i >= 0; i--)
			print(s->elements[i]);
	}
}









