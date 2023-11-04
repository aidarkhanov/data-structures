#define VEC_IMPLEMENTATION
#include "src/vec.h"

#include <stdio.h>

int main() {
    // Create a new vector with an initial capacity of 4
    Vec *vec = vec_new(4);

    // Display the initial size and capacity of the vector
    printf("Initial vector size: %zu\n", vec_size(vec));
    printf("Initial vector capacity: %zu\n", vec_capacity(vec));

    // Append 5 values to the vector to demonstrate automatic resizing
    for (size_t i = 0; i < 5; ++i) {
        vec_append(vec, (int)i + 1);
    }

    // Display the size and capacity after appending values
    printf("Vector size after append: %zu\n", vec_size(vec));
    printf("Vector capacity after append: %zu\n", vec_capacity(vec));

    // Access an element using vec_at and display it
    int val = vec_at(vec, 1);
    printf("Element at index 1: %d\n", val);

    // Modify an element directly and display it again
    vec_ptr(vec)[1] = 69; // This should be avoided; use a function to encapsulate behavior
    printf("Modified element at index 1: %d\n", vec_at(vec, 1));

    // Remove an element at a specified index
    vec_delete(vec, 1);
    printf("Element at index 1 after deletion: %d\n", vec_at(vec, 1));

    // Display the size and capacity after deletion
    printf("Vector size after deletion: %zu\n", vec_size(vec));
    printf("Vector capacity after deletion: %zu\n", vec_capacity(vec));

	// Shrink to fit the vector.
	vec_fit(vec);
    printf("Vector size after shrinking: %zu\n", vec_size(vec));
    printf("Vector capacity after shrinking: %zu\n", vec_capacity(vec));

    // Free the vector when done
    vec_free(&vec);

    return 0;
}
