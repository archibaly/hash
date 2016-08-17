#include <stdio.h>

#include "hash.h"

int main()
{
	hash_init(32, HASH_KEY_TYPE_STR);

	hash_add("123", "value1");
	hash_add("123", "valuex");
	hash_add("aece", "value2");
	hash_add("0uej", "value3");

	struct hash_node *node[8];

	int n = hash_find("123", node, sizeof(node));

	int i;
	if (n > 0) {
		for (i = 0; i < n; i++)
			printf("node[%d]->value = %s\n", i, (char *)node[i]->value);
	} else {
		printf("can not find\n");
	}

	hash_free();

	return 0;
}
