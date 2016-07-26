#include <stdlib.h>
#include <string.h>

#include "hash_str.h"
#include "debug.h"

static struct hlist_head *hash_table;
static int hash_shift;

static size_t hash(const char *string)
{
	size_t hashval = 0;
	size_t seed = 131;	/* 31 131 1313 13131 131313 .. */

	while (*string)
		hashval = hashval * seed + (size_t)*string++;

	return hashval;
}

static struct hash_str_node *new_hash_str_node(const char *key, void *value)
{
	struct hash_str_node *node;

	if (!(node = malloc(sizeof(struct hash_str_node))))
		return NULL;
	if (!(node->key = strdup(key)))
		return NULL;
	node->value = value;
	INIT_HLIST_NODE(&node->node);

	return node;
}

int hash_str_init(int shift)
{
	size_t i;
	size_t hash_size;

	hash_shift = shift;
	hash_size = 1 << shift;

	if (!(hash_table = malloc(sizeof(struct hlist_head) * hash_size)))
		return -1;
	
	for (i = 0; i < hash_size; i++)
		INIT_HLIST_HEAD(hash_table + i);

	return 0;
}

int hash_str_add(const char *key, void *value)
{
	int offset;
	struct hash_str_node *node;

	node = new_hash_str_node(key, value);
	if (!node)
		return -1;

	offset = hash(key) % (1 << hash_shift);
	debug("offset = %d", offset);

	hlist_add_head(&node->node, hash_table + offset);

	return 0;
}

int hash_str_find(const char *key, struct hash_str_node **node, size_t size)
{
	int offset;
	size_t i = 0;
	struct hash_str_node *pos;

	if (!hash_table)
		return -1;

	offset = hash(key) % (1 << hash_shift);

	hlist_for_each_entry(pos, hash_table + offset, node) {
		if (strcmp(pos->key, key) == 0) {
			if (i < size)
				node[i++] = pos;
			else
				break;
		}
	}

	return i;
}

void hash_str_print(void)
{
	size_t i;
	size_t hash_size;
	struct hash_str_node *pos;

	hash_size = 1 << hash_shift;

	for (i = 0; i < hash_size; i++) {
		hlist_for_each_entry(pos, hash_table + i, node) {
			printf("key = %s\n", pos->key);
		}
	}
}

void hash_str_free_node(struct hash_str_node *node)
{
	if (!node)
		return;
	if (!hlist_unhashed(&node->node)) {
		debug("__hlist_del");
		__hlist_del(&node->node);
	}
	free(node->key);
	free(node);
}

void hash_str_free(void)
{
	size_t i;
	size_t hash_size;
	struct hash_str_node *pos;

	hash_size = 1 << hash_shift;

	for (i = 0; i < hash_size; i++) {
		hlist_for_each_entry(pos, hash_table + i, node) {
			hash_str_free_node(pos);
		}
	}
	free(hash_table);
	hash_shift = 0;
	hash_table = NULL;
}
