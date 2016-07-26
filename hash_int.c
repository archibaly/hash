#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "hash_int.h"
#include "debug.h"

/* 2^31 + 2^29 - 2^25 + 2^22 - 2^19 - 2^16 + 1 */
#define GOLDEN_RATIO_PRIME_32 0x9e370001UL

static struct hlist_head *hash_table;
static int hash_shift;

static inline uint32_t hash(uint32_t val, uint32_t bits)
{
	uint32_t hash = val * GOLDEN_RATIO_PRIME_32;

	/* high bits are more random, so use them */
	return hash >> (32 - bits);
}

static struct hash_int_node *new_hash_int_node(int key, void *value)
{
	struct hash_int_node *node;

	if (!(node = malloc(sizeof(struct hash_int_node))))
		return NULL;
	node->key = key;
	node->value = value;
	INIT_HLIST_NODE(&node->node);

	return node;
}

/*
 * @shift: hash_size = 2^shift
 */
int hash_int_init(int shift)
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

int hash_int_add(int key, void *value)
{
	struct hash_int_node *node;

	node = new_hash_int_node(key, value);
	if (!node)
		return -1;

	int offset = hash(key, hash_shift);
	debug("offset = %d", offset);
	hlist_add_head(&node->node, hash_table + offset);

	return 0;
}

/*
 * @return: the number of found nodes
 */
int hash_int_find(int key, struct hash_int_node **node, size_t size)
{
	int offset;
	size_t i = 0;
	struct hash_int_node *pos;

	if (!hash_table)
		return 0;

	offset = hash(key, hash_shift);

	hlist_for_each_entry(pos, hash_table + offset, node) {
		if (pos->key == key) {
			if (i < size)
				node[i++] = pos;
			else
				break;
		}
	}

	return i;
}

void hash_int_free_node(struct hash_int_node *node)
{
	if (!node)
		return;
	if (!hlist_unhashed(&node->node)) {
		debug("__hlist_del");
		__hlist_del(&node->node);
	}
	free(node);
}

void hash_int_free(void)
{
	size_t i;
	size_t hash_size;
	struct hash_int_node *pos;

	hash_size = 1 << hash_shift;
	for (i = 0; i < hash_size; i++) {
		hlist_for_each_entry(pos, hash_table + i, node) {
			hash_int_free_node(pos);
		}
	}
	free(hash_table);
	hash_shift = 0;
	hash_table = NULL;
}
