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
int push(Stack* self, void* data, size_t size) {
	Node* node = (Node*) malloc(sizeof(Node));

	if (node == NULL) {
		printf("Error allocating new node to the stack. Exiting...\n");
		delete(self);
		return -1;
	}

	node->size = size;
	node->data = malloc(size);

	if (node->data == NULL) {
		printf("Error allocating new node to the stack. Exiting...\n");
		free(node->data);
		free(node);
		delete(self);
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

	Node* temp = self->p_top;
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

	push(self, &value1, sizeof(value1));
	push(self, &value2, sizeof(value2));
	push(self, &value3, sizeof(value3));
	push(self, &value4, sizeof(value4));
	push(self, &value5, sizeof(value5));
	push(self, &value6, sizeof(value6));
	push(self, &value7, sizeof(value7));
	push(self, &value8, sizeof(value8));
	push(self, &value9, sizeof(value9));

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
