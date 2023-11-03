#define VEC_IMPLEMENTATION
#include "vec.h"

#include <stdlib.h>
#include <stdio.h>

int main(void)
{
	Vec vec;
	size_t i = 0;

	init_vec(&vec, 4);

	append(&vec, 10);
	append(&vec, 20);
	append(&vec, 30);
	append(&vec, 40);
	append(&vec, 50);

	printf("Vector size is %zu\n", vec.size);
	printf("Vector capacity is %zu\n", vec.capacity);

	for (; i < size(&vec); ++i) {
		printf("%d ", get_element(&vec, i));
	}
	printf("\n");

	delete_element(&vec, 2);

	for (i = 0; i < size(&vec); ++i) {
		printf("%d ", get_element(&vec, i));
	}
	printf("\n");

	free_vec(&vec);

	return 0;
}
