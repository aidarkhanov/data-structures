#ifndef VEC_H
#define VEC_H

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>

#ifndef VEC_ASSERT
    #define VEC_ASSERT(x) assert(x)
#endif

#ifndef VEC_MALLOC
    #define VEC_MALLOC(sz) malloc(sz)
#endif

#ifndef VEC_REALLOC
    #define VEC_REALLOC(ptr, sz) realloc((ptr), (sz))
#endif

#ifndef VEC_FREE
    #define VEC_FREE(ptr) free(ptr)
#endif

typedef struct Vec Vec;

Vec *vec_new(size_t capacity);
void vec_free(Vec **vec);
void vec_fit(Vec *vec);
void vec_append(Vec *vec, int value);
void vec_delete(Vec *vec, size_t index);
static inline int    vec_at(const Vec *vec, ptrdiff_t index);
static inline size_t vec_size(const Vec *vec);
static inline size_t vec_capacity(const Vec *vec);

#define vec_ptr(vec) ((int *)((vec)->data))

#ifdef VEC_IMPLEMENTATION

#include <string.h>

struct Vec {
    size_t size;
    size_t capacity;
    int *data;
};

Vec *vec_new(size_t capacity)
{
    Vec *vec = (Vec *)VEC_MALLOC(sizeof(Vec));
    VEC_ASSERT(vec != nullptr);

	vec->data = (int *)VEC_MALLOC(capacity * sizeof(int));
	VEC_ASSERT(vec->data != nullptr);

    vec->size = 0;
    vec->capacity = capacity;

    return vec;
}

void vec_free(Vec **vec)
{
	VEC_ASSERT(vec != nullptr && *vec != nullptr);

	VEC_FREE((*vec)->data);
	VEC_FREE(*vec);
	*vec = nullptr;
}

void vec_fit(Vec *vec)
{
	if (vec->size < vec->capacity) {
		int *new_data = (int *)VEC_REALLOC(vec->data, vec->size * sizeof(int));
		VEC_ASSERT(new_data != nullptr);

		vec->data = new_data;
		vec->capacity = vec->size;
	}
}

void vec_append(Vec *vec, int value)
{
	if (vec->size >= vec->capacity) {
		size_t new_capacity = vec->capacity > 0 ? vec->capacity : 1;
		new_capacity += (vec->capacity < 64) ? vec->capacity : 64;

		int *new_data = (int *)VEC_REALLOC(vec->data, new_capacity * sizeof(int));
		VEC_ASSERT(new_data != nullptr);

		vec->data = new_data;
		vec->capacity = new_capacity;
	}

    vec->data[vec->size++] = value;
}

void vec_delete(Vec *vec, size_t index)
{
	VEC_ASSERT(vec != nullptr && index < vec->size);

	// Optimization 1: if empty vector, do nothing.
	if (vec->size == 0)
		return;

	// Optimization 2: if not deleting the last element, move memory.
	if (index < vec->size - 1)
		memmove(
			&vec->data[index],
			&vec->data[index + 1],
			(vec->size - index - 1) * sizeof(int)
		);

	vec->size--;
}

static inline int vec_at(const Vec *vec, ptrdiff_t index)
{
	// If index is negative, wrap around to the end of the vector.
	if (index < 0)
		index += vec->size;

    VEC_ASSERT(index >= 0 && (size_t) index < vec->size);

	return vec->data[index];
}

static inline size_t vec_size(const Vec *vec)
{
	return vec->size;
}

static inline size_t vec_capacity(const Vec *vec)
{
	return vec->capacity;
}

#endif // VEC_IMPLEMENTATION

#endif // VEC_H
