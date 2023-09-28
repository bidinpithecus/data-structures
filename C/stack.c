#include "stack.h"

/**
 * Initializes a stack by setting its size to 0 and the top pointer to NULL.
 *
 * @param stack A pointer to the stack to be initialized.
 */
void init(Stack* stack) {
	stack->size = 0;
	stack->p_top = NULL;
}

/**
 * Deletes a stack and frees all allocated memory, including nodes and the stack itself.
 *
 * @param stack A pointer to the stack to be deleted.
 */
void delete(Stack* stack) {
	while (stack->p_top != NULL) {
		Node* temp = stack->p_top;
		stack->p_top = stack->p_top->p_next;
		temp->data = NULL;
		temp->p_next = NULL;
		free(temp);
		stack->size--;
	}

	stack->size = 0;
	free(stack);
}

/**
 * Pushes an element onto the top of the stack.
 *
 * @param self A pointer to the stack.
 * @param data The data to be added to the stack.
 */
void push(Stack* self, void* data) {
	Node* node = (Node*) malloc(sizeof(Node));
	if (node == NULL) {
		printf("Error allocating new node to the stack. Exiting...\n");
		delete(self);
		exit(1);
	}

	node->data = data;
	node->p_next = self->p_top;

	self->p_top = node;
	self->size++;
}

/**
 * Checks if a stack is empty.
 *
 * @param self A pointer to the stack.
 * @return true if the stack is empty, false otherwise.
 */
bool isEmpty(Stack* self) {
	return self->size == 0;
}

/**
 * Removes and returns the element at the top of the stack.
 *
 * @param self A pointer to the stack.
 * @return The data of the element removed from the stack.
 */
void* pop(Stack* self) {
	if (isEmpty(self)) {
		printf("Can't pop an empty Stack. Exiting...\n");
		delete(self);
		exit(1);
	}

	void* data = self->p_top->data;
	Node* temp = self->p_top;
	self->p_top = self->p_top->p_next;

	free(temp);
	self->size--;

	return data;
}

/**
 * Retrieves the data of the element at the top of the stack without removing it.
 *
 * @param self A pointer to the stack.
 * @return The data of the element at the top of the stack.
 */
void* peek(Stack* self) {
	if (isEmpty(self)) {
		printf("Can't peek an empty Stack. Exiting...\n");
		delete(self);
		exit(1);
	}

	return self->p_top->data;
}

/**
 * Tests the basics functionality of the implemented stack
 *
 * @param self A pointer to the stack.
 */
void test(Stack* self) {
	assert(isEmpty(self) == true);

	int value1 = 10;
	int value2 = 20;
	int value3 = 30;

	float value4 = 10.4F;
	float value5 = 20.5F;
	float value6 = 30.6F;

	char value7 = '7';
	char value8 = '8';
	char value9 = '9';

	push(self, &value1);
	push(self, &value2);
	push(self, &value3);
	push(self, &value4);
	push(self, &value5);
	push(self, &value6);
	push(self, &value7);
	push(self, &value8);
	push(self, &value9);

	assert(isEmpty(self) == false);

	assert(*(char*)peek(self) == '9');

	assert(*(char*)pop(self) == '9');
	assert(*(char*)pop(self) == '8');
	assert(*(char*)pop(self) == '7');
	assert(*(float*)pop(self) == 30.6F);
	assert(*(float*)pop(self) == 20.5F);
	assert(*(float*)pop(self) == 10.4F);
	assert(*(int*)pop(self) == 30);
	assert(*(int*)pop(self) == 20);
	assert(*(int*)pop(self) == 10);

	assert(isEmpty(self) == true);

	printf("Stack passed in every assertion made.\n");
}

int main(int argc, char** argv) {
	Stack* stack = (Stack*) malloc(sizeof(Stack));
	init(stack);
	test(stack);
	delete(stack);

	return 0;
}
