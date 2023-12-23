#include "deque.h"

/**
 * Checks if a deque is empty.
 *
 * @param self A pointer to the deque.
 * @return true if the deque is empty, false otherwise.
 */
bool isDequeEmpty(Deque* self) {
	return self->size == 0;
}

void deleteDeque(Deque* self) {
	while (self->p_head != NULL) {
		NodeDeque* temp = self->p_head;
		self->p_head = temp->p_next;

		temp->data = NULL;
		free(temp->data);
		temp->p_next = NULL;
		free(temp);

		self->size--;
	}

	self->size = 0;
	free(self);
}

/**
 * Initializes a deque by setting its size to 0, the head and the tail pointers to NULL.
 *
 * @param self A pointer to the deque to be initialized.
 */
void initDeque(Deque* self) {
	self->size = 0;
	self->p_head = self->p_tail = NULL;
}

int insertHeadOfDeque(Deque* self, void* data, size_t size) {
	NodeDeque* node = (NodeDeque*) malloc(sizeof(NodeDeque));

	if (node == NULL) {
		printf("Error allocating new node to the deque.\n");
		deleteDeque(self);
		return -1;
	}

	node->data = (void*) malloc(size);

	if (node->data == NULL) {
		printf("Error allocating new node to the deque.\n");
		free(node->data);
		free(node);
		deleteDeque(self);
		return -1;
	}

	memcpy(node->data, data, size);
	node->p_next = self->p_head;
	node->p_previous = NULL;

	self->p_head = node;
	self->size++;

	if (self->p_tail == NULL) {
		self->p_tail = self->p_head;
	}

	return 0;
}

int insertTailOfDeque(Deque* self, void* data, size_t size) {
	NodeDeque* node = (NodeDeque*) malloc(sizeof(NodeDeque));

	if (node == NULL) {
		printf("Error allocating new node to the deque.\n");
		deleteDeque(self);
		return -1;
	}

	node->data = (void*) malloc(size);

	if (node->data == NULL) {
		printf("Error allocating new node to the deque.\n");
		free(node->data);
		free(node);
		deleteDeque(self);
		return -1;
	}

	memcpy(node->data, data, size);
	node->p_previous = self->p_tail;
	node->p_next = NULL;

	self->p_tail = node;
	self->size++;

	if (self->p_head == NULL) {
		self->p_head = self->p_tail;
	}

	return 0;
}

void* removeHeadOfDeque(Deque* self) {
	if (isDequeEmpty(self)) {
		printf("Can't remove of an empty deque. Exiting...\n");
		deleteDeque(self);
		exit(1);
	}

	NodeDeque* temp = self->p_head;
	void* data = temp->data;

	self->p_head = temp->p_next;
	self->size--;

	temp->data = NULL;
	free(temp->data);

	temp->p_next = NULL;
	free(temp);

	return data;
}

void* removeTailOfDeque(Deque* self) {
	if (isDequeEmpty(self)) {
		printf("Can't remove of an empty deque. Exiting...\n");
		deleteDeque(self);
		exit(1);
	}

	NodeDeque* temp = self->p_tail;
	void* data = temp->data;

	self->p_tail = temp->p_previous;
	self->size--;

	temp->data = NULL;
	free(temp->data);

	temp->p_previous = NULL;
	free(temp);

	return data;
}

void* peekHeadOfDeque(Deque* self) {
	return self->p_head->data;
}

void* peekTailOfDeque(Deque* self) {
	return self->p_tail->data;
}

void testDeque(Deque* self) {
	assert(isDequeEmpty(self) == true);

	int value1 = 10;
	int value2 = 20;
	int value3 = 30;

	float value4 = 10.4F;
	float value5 = 20.5F;
	float value6 = 30.6F;

	char value7 = '7';
	char value8 = '8';
	char value9 = '9';

	insertHeadOfDeque(self, &value1, sizeof(value1));
	insertHeadOfDeque(self, &value2, sizeof(value2));
	insertHeadOfDeque(self, &value3, sizeof(value3));
	insertTailOfDeque(self, &value4, sizeof(value4));
	insertTailOfDeque(self, &value5, sizeof(value5));
	insertTailOfDeque(self, &value6, sizeof(value6));
	insertHeadOfDeque(self, &value7, sizeof(value7));
	insertHeadOfDeque(self, &value8, sizeof(value8));
	insertHeadOfDeque(self, &value9, sizeof(value9));
	// '9', '8', '7', 30, 20, 10, 10.4F, 20.5F, 30.6F

	assert(self->size == 9);

	assert(isDequeEmpty(self) == false);

	assert(*(char*)peekHeadOfDeque(self) == '9');

	assert(*(char*)removeHeadOfDeque(self) == '9');
	assert(*(char*)removeHeadOfDeque(self) == '8');
	assert(*(char*)removeHeadOfDeque(self) == '7');
	assert(*(float*)removeTailOfDeque(self) == 30.6F);
	assert(*(float*)removeTailOfDeque(self) == 20.5F);
	assert(*(float*)removeTailOfDeque(self) == 10.4F);
	assert(*(int*)removeHeadOfDeque(self) == 30);
	assert(*(int*)removeHeadOfDeque(self) == 20);
	assert(*(int*)removeHeadOfDeque(self) == 10);

	assert(isDequeEmpty(self) == true);

	printf("Deque passed in every assertion made.\n");
}

int main(void) {
	Deque* deque = (Deque*) malloc(sizeof(Deque));
	initDeque(deque);
	testDeque(deque);
	deleteDeque(deque);

	return 0;
}
