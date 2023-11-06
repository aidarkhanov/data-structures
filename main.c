#define VEC_IMPLEMENTATION
#include "src/vec.h"

#include <stdio.h>

int main() {
	// Create a new vector with an initial capacity of 4 integers.
	Vec *my_vec = vec_new(4);

	// Push new elements into the vector.
	for (int i = 0; i < 10; ++i) {
		vec_push(my_vec, i * i);
	}

	// Access elements by index.
	printf("Element at index 5: %d\n", vec_at(my_vec, 5));

	// Delete element at index 3.
	vec_delete(my_vec, 3);

	// Free the vector when done.
	vec_free(my_vec);
	return 0;
}
