#pragma once

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/**
 * data: data stored in the Node.
 * p_next: Pointer to the next Node in the Stack.
*/
typedef struct Node {
	void* data;
	struct Node* p_next;
} Node;

/**
 * Data structure following LIFO restriction.
 *
 * size: Number of elements in the stack
 * p_top: Pointer to the top (most recent) element in the stack.
*/
typedef struct Stack {
	int size;
	Node* p_top;

} Stack;

bool isEmpty(Stack*);

void delete(Stack*);
void init(Stack*);
void push(Stack*, void*);
void test(Stack*);

void* peek(Stack*);
void* pop(Stack*);
