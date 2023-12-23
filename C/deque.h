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
 * p_previous: Pointer to the previous node in the stack.
*/
typedef struct NodeDeque {
	void* data;
	size_t size;
	struct NodeDeque* p_next;
	struct NodeDeque* p_previous;
} NodeDeque;

/**
 * Polymorphic data structure accessible from both the head and the tail.
 *
 * size: Number of elements in the stack
 * p_head: Pointer to the head element in the stack.
 * p_tail: Pointer to the tail element in the stack.
*/
typedef struct Deque {
	int size;
	NodeDeque* p_head;
	NodeDeque* p_tail;
} Deque;

bool isDequeEmpty(Deque*);
void deleteDeque(Deque*);
void initDeque(Deque*);
int insertHeadOfDeque(Deque*, void*, size_t);
int insertTailOfDeque(Deque*, void*, size_t);
void* removeHeadOfDeque(Deque*);
void* removeTailOfDeque(Deque*);
void* peekTailOfDeque(Deque*);
void* peekHeadOfDeque(Deque*);
void testDeque(Deque*);
