#pragma once

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

/**
 * data: Data stored in the node.
 * size: Size in byets of the data stored.
 * p_next: Pointer to the next node in the stack.
*/
typedef struct NodeStack {
	void* data;
	size_t size;
	struct NodeStack* p_next;
} NodeStack;

/**
 * Polymorphic data structure following LIFO restriction.
 *
 * size: Number of elements in the stack
 * p_top: Pointer to the top (most recent) element in the stack.
*/
typedef struct Stack {
	int size;
	NodeStack* p_top;

} Stack;

bool isStackEmpty(Stack*);

void deleteStack(Stack*);
void initStack(Stack*);
int pushStack(Stack*, void*, size_t);
void testStack(Stack*);

void* peekStack(Stack*);
void* popStack(Stack*);
