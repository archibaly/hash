#include <stdio.h>

#include "hash_int.h"
#include "hash_str.h"

int main()
{
	hash_str_init(12);

	hash_str_add("jacky", "a");
	hash_str_add("bob", "b");
	hash_str_add("bob", "c");
	hash_str_add("bob", "d");
	hash_str_add("bob", "e");
	hash_str_add("smith", "d");
	hash_str_add("alen", "e");

	hash_str_print();

	struct hash_str_node *node[8];

	int i;
	int n = hash_str_find("jacky", node, sizeof(node));
	if (n > 0) {
		for (i = 0; i < n; i++)
			printf("node[%d]->value = %s\n", i, (unsigned char *)node[i]->value);
	}

	n = hash_str_find("smith", node, sizeof(node));
	if (n > 0) {
		for (i = 0; i < n; i++)
			printf("node[%d]->value = %s\n", i, (unsigned char *)node[i]->value);
	}

	n = hash_str_find("alen", node, sizeof(node));
	if (n > 0) {
		for (i = 0; i < n; i++)
			printf("node[%d]->value = %s\n", i, (unsigned char *)node[i]->value);
	}

	n = hash_str_find("bob", node, sizeof(node));
	if (n > 0) {
		for (i = 0; i < n; i++)
			printf("node[%d]->value = %s\n", i, (unsigned char *)node[i]->value);
	}

	hash_str_free();

	n = hash_str_find("bob", node, sizeof(node));
	if (n > 0) {
		for (i = 0; i < n; i++)
			printf("node[%d]->value = %s\n", i, (unsigned char *)node[i]->value);
	} else
		printf("can not find\n");

	return 0;
}
