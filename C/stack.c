#include "stack.h"

/**
 * Initializes a stack by setting its size to 0 and the top pointer to NULL.
 *
 * @param stack A pointer to the stack to be initialized.
 */
void initStack(Stack* stack) {
	stack->size = 0;
	stack->p_top = NULL;
}

/**
 * Deletes a stack and frees all allocated memory, including nodes and the stack itself.
 *
 * @param stack A pointer to the stack to be deleted.
 */
void deleteStack(Stack* stack) {
	while (stack->p_top != NULL) {
		NodeStack* temp = stack->p_top;
		stack->p_top = temp->p_next;

		temp->data = NULL;
		free(temp->data);
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
 * @param size The size of the data to be added to the stack.
 * @return 0 on success, -1 on failure.
 */
int pushStack(Stack* self, void* data, size_t size) {
	NodeStack* node = (NodeStack*) malloc(sizeof(NodeStack));

	if (node == NULL) {
		printf("Error allocating new node to the stack. Exiting...\n");
		deleteStack(self);
		return -1;
	}

	node->size = size;
	node->data = malloc(size);

	if (node->data == NULL) {
		printf("Error allocating new node to the stack. Exiting...\n");
		free(node->data);
		free(node);
		deleteStack(self);
		return -1;
	}

	memcpy(node->data, data, size);
	node->p_next = self->p_top;

	self->p_top = node;
	self->size++;

	return 0;
}

/**
 * Checks if a stack is empty.
 *
 * @param self A pointer to the stack.
 * @return true if the stack is empty, false otherwise.
 */
bool isStackEmpty(Stack* self) {
	return self->size == 0;
}

/**
 * Removes and returns the element at the top of the stack.
 *
 * @param self A pointer to the stack.
 * @return The data of the element removed from the stack.
 */
void* popStack(Stack* self) {
	if (isStackEmpty(self)) {
		printf("Can't pop an empty Stack. Exiting...\n");
		deleteStack(self);
		exit(1);
	}

	NodeStack* temp = self->p_top;
	void* data = temp->data;

	self->p_top = temp->p_next;
	self->size--;

	temp->data = NULL;
	free(temp->data);

	temp->p_next = NULL;
	free(temp);

	return data;
}

/**
 * Retrieves the data of the element at the top of the stack without removing it.
 *
 * @param self A pointer to the stack.
 * @return The data of the element at the top of the stack.
 */
void* peekStack(Stack* self) {
	if (isStackEmpty(self)) {
		printf("Can't peek an empty Stack. Exiting...\n");
		deleteStack(self);
		exit(1);
	}

	return self->p_top->data;
}

/**
 * Tests the basics functionality of the implemented stack
 *
 * @param self A pointer to the stack.
 */
void testStack(Stack* self) {
	assert(isStackEmpty(self) == true);

	int value1 = 10;
	int value2 = 20;
	int value3 = 30;

	float value4 = 10.4F;
	float value5 = 20.5F;
	float value6 = 30.6F;

	char value7 = '7';
	char value8 = '8';
	char value9 = '9';

	pushStack(self, &value1, sizeof(value1));
	pushStack(self, &value2, sizeof(value2));
	pushStack(self, &value3, sizeof(value3));
	pushStack(self, &value4, sizeof(value4));
	pushStack(self, &value5, sizeof(value5));
	pushStack(self, &value6, sizeof(value6));
	pushStack(self, &value7, sizeof(value7));
	pushStack(self, &value8, sizeof(value8));
	pushStack(self, &value9, sizeof(value9));

	assert(isStackEmpty(self) == false);

	assert(*(char*)peekStack(self) == '9');

	assert(*(char*)popStack(self) == '9');
	assert(*(char*)popStack(self) == '8');
	assert(*(char*)popStack(self) == '7');
	assert(*(float*)popStack(self) == 30.6F);
	assert(*(float*)popStack(self) == 20.5F);
	assert(*(float*)popStack(self) == 10.4F);
	assert(*(int*)popStack(self) == 30);
	assert(*(int*)popStack(self) == 20);
	assert(*(int*)popStack(self) == 10);

	assert(isStackEmpty(self) == true);

	printf("Stack passed in every assertion made.\n");
}

int main(void) {
	Stack* stack = (Stack*) malloc(sizeof(Stack));
	initStack(stack);
	testStack(stack);
	deleteStack(stack);

	return 0;
}
