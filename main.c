#include <stdio.h>

#include "hash.h"

int main()
{
	struct hash_table *table;
	table = hash_init(32, HASH_KEY_TYPE_STR);
	if (!table)
		return -1;

	hash_add(table, "123", "value1");
	hash_add(table, "123", "valuex");
	hash_add(table, "aece", "value2");
	hash_add(table, "0uej", "value3");

	struct hash_node *node[8];

	int n = hash_find(table, "123", node, sizeof(node));

	int i;
	if (n > 0) {
		for (i = 0; i < n; i++)
			printf("node[%d]->value = %s\n", i, (char *)node[i]->value);
	} else {
		printf("can not find\n");
	}

	hash_free(table);

	table = hash_init(32, HASH_KEY_TYPE_INT);
	if (!table)
		return -1;

	int key = 1;
	hash_add(table, &key, "value1");
	key = 1;
	hash_add(table, &key, "valuex");
	key = 3;
	hash_add(table, &key, "value2");
	key = 4;
	hash_add(table, &key, "value3");

	key = 1;
	n = hash_find(table, &key, node, sizeof(node));

	if (n > 0) {
		for (i = 0; i < n; i++)
			printf("node[%d]->value = %s\n", i, (char *)node[i]->value);
	} else {
		printf("can not find\n");
	}

	hash_free(table);

	return 0;
}
