#ifndef _HASH_STR_H_
#define _HASH_STR_H_

#include "list.h"

struct hash_str_node {
	char *key;
	void *value;
	struct hlist_node node;
};

int hash_str_init(int shift);
int hash_str_add(const char *key, void *value);
int hash_str_find(const char *key, struct hash_str_node **node, size_t size);
void hash_str_print(void);
void hash_str_free_node(struct hash_str_node *node);
void hash_str_free(void);

#endif /* _HASH_STR_H_ */
