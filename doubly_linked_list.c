#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_t node_t;
struct node_t {
	node_t* next;
	node_t* prev;
	const char* data;
};

node_t* node_create(node_t* next, node_t* prev, const char* data) {
	node_t* node = malloc(sizeof(node_t));
	node->next = next;
	node->prev = prev;
	node->data = data;
	if (next != nullptr) {
		next->prev = node;
	}
	if (prev != nullptr) {
		prev->next = node;
	}
	return node;
}

void node_delete(node_t* node) {
	if (node != nullptr) {
		if (node->next != nullptr) {
			node->next->prev = node->prev;
		}
		if (node->prev != nullptr) {
			node->prev->next = node->next;
		}
	}
	free(node);
}

node_t* list_tail(node_t* list) {
	if (list != nullptr) {
		while (list->next != nullptr) {
			list = list->next;
		}
	}
	return list;
}

node_t* list_head(node_t* list) {
	if (list != nullptr) {
		while (list->prev != nullptr) {
			list = list->prev;
		}
	}
	return list;
}

node_t* list_insert_next(node_t* node, const char* data) {
	return node->next = node_create(node->next, node, data);
}

node_t* list_insert_prev(node_t* node, const char* data) {
	return node->prev = node_create(node, node->prev, data);
}

node_t* list_append(node_t** list, const char* data) {
	if (*list == nullptr) {
		*list = node_create(nullptr, nullptr, data);
	} else {
		list_insert_next(list_tail(*list), data);
	}
	return *list;
}

node_t* list_prepend(node_t** list, const char* data) {
	if (*list == nullptr) {
		*list = node_create(nullptr, nullptr, data);
	} else {
		list_insert_prev(list_head(*list), data);
	}
	return *list;
}

node_t* list_find(node_t* list, const char* data) {
	list = list_head(list);
	while ((list != nullptr) && strcmp(list->data, data)) {
		list = list->next;
	}
	return list;
}

void list_delete(node_t** list) {
	if (*list != nullptr) {
		while ((*list)->next != nullptr) {
			node_delete((*list)->next);
		}
		while ((*list)->prev != nullptr) {
			node_delete((*list)->prev);
		}
	}
	node_delete(*list);
}

int main() {
	node_t* list = nullptr;

	list_append(&list, "hello");
	list_append(&list, "world");
	list_append(&list, "abc");
	list_append(&list, "xyz");

	node_t* node = list;
	while (node != nullptr) {
		printf("%s\n", node->data);
		node = node->next;
	}

	printf("\n%s\n", list_find(list, "world")->data);

	list_delete(&list);
}
