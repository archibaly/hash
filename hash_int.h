#ifndef _HASH_INT_H_
#define _HASH_INT_H_

#include "list.h"

struct hash_int_node {
	int key;
	void *value;
	struct hlist_node node;
};

int hash_int_init(int shift);
int hash_int_add(int key, void *value);
int hash_int_find(int key, struct hash_int_node **node, size_t size);
void hash_int_free_node(struct hash_int_node *node);
void hash_int_free(void);

#endif /* _HASH_INT_H_ */
