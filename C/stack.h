#pragma once

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

/**
 * data: Data stored in the node.
 * p_next: Pointer to the next node in the stack.
*/
typedef struct Node {
	void* data;
	size_t size;
	struct Node* p_next;
} Node;

/**
 * Polymorphic data structure following LIFO restriction.
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
int push(Stack*, void*, size_t);
void test(Stack*);

void* peek(Stack*);
void* pop(Stack*);
