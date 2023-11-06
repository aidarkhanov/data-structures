/*
	vec.h — A concise, educational dynamic array (vector) implementation.

Overview:
	Inspired by the simplicity of the stb libraries, vec provides an easy and
	minimalistic dynamic array for educational purposes and small projects.
	It supports basic array operations such as creation, destruction,
	insertion, deletion, and access.

	This implementation is geared towards learning and understanding how
	dynamic arrays work in a low-level language like C. Error checking is
	performed using assertions to facilitate debugging and learning.

Growth strategy:
	One critical aspect of dynamic array implementation is the growth strategy
	— how the array expands as elements are added beyond its current capacity.
	The growth factor influences the performance characteristics of the array,
	especially the amortized time complexity of insertions.

	The strategy in this implementation increases the capacity by 50% of the
	current capacity plus a small constant factor of two. This constant factor
	can help avoid overly aggressive growth when the array size is small,
	which can be particularly beneficial for arrays with a small number of
	elements, reducing the overhead of memory reallocations. As the array
	grows, the relative impact of this constant becomes negligible, and the
	growth factor asymptotically approaches 1.5.

	This growth strategy ensures that, on average, the cost of inserting a new
	element remains constant over time, which is a property known as amortized
	constant time complexity. This property is shared by many dynamic array
	implementations, including those in standard libraries of many programming
	languages.

	Another growth strategy that can be used follows the widely-used
	"golden ratio" approach, where the new capacity is 1.5 times the old
	capacity. This strategy strikes a balance between memory usage and the
	number of reallocations. Folly, an open-source C++ library developed and
	used by Facebook, uses a similar growth strategy. It ensures that
	insertions have an amortized time complexity of O(1), meaning that while
	some inserts may be costly (when reallocation happens), the average cost
	over a series of operations is constant.

Usage:
	```c
	#define VEC_IMPLEMENTATION
	#include "vec.h"

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
	```
*/
#ifndef VEC_H
#define VEC_H

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

// The vector structure
typedef struct {
	size_t size;
	size_t capacity;
	int *data;
} Vec;

// Prototypes
Vec *vec_new(size_t initial_capacity);
void vec_free(Vec *vec);
void vec_push(Vec *vec, int value);
void vec_delete(Vec *vec, size_t index);
int vec_at(const Vec *vec, size_t index);
size_t vec_size(const Vec *vec);
size_t vec_capacity(const Vec *vec);

#ifdef VEC_IMPLEMENTATION

// Internal utility functions
static inline void *_realloc(void *ptr, size_t new_size) {
	void *new_ptr = realloc(ptr, new_size);
	assert(new_ptr);

	return new_ptr;
}

static inline size_t _grow_capacity(size_t current) {
	return current + (current >> 1) + 2;
}

// Function implementations
Vec *vec_new(size_t initial_capacity) {
	Vec *vec = (Vec *)malloc(sizeof(Vec));
	assert(vec);

	vec->size = 0;
	vec->capacity = initial_capacity;
	vec->data = (int *)malloc(initial_capacity * sizeof(int));
	assert(vec->data);

	return vec;
}

void vec_free(Vec *vec) {
	assert(vec);
	free(vec->data);
	free(vec);
}

void vec_push(Vec *vec, int value) {
	if (vec->size == vec->capacity) {
		vec->capacity = _grow_capacity(vec->capacity);
		vec->data = (int *)_realloc(vec->data, vec->capacity * sizeof(int));
	}

	vec->data[vec->size++] = value;
}

void vec_delete(Vec *vec, size_t index) {
	assert(vec && index < vec->size);

	memmove(&vec->data[index], &vec->data[index + 1], (vec->size - index - 1) * sizeof(int));
	--vec->size;
}

int vec_at(const Vec *vec, size_t index) {
	assert(vec && index < vec->size);

	return vec->data[index];
}

size_t vec_size(const Vec *vec) {
	return vec->size;
}

size_t vec_capacity(const Vec *vec) {
	return vec->capacity;
}

#endif // VEC_IMPLEMENTATION

#endif // VEC_H
