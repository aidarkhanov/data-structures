#ifndef VEC_H
#define VEC_H

#include <stddef.h>
#include <stdlib.h>

#ifndef VEC_ASSERT
	#define VEC_ASSERT(x) assert(x)
#endif

#ifndef VEC_MALLOC
	#define VEC_MALLOC(sz) malloc(sz)
#endif

#ifndef VEC_FREE
	#define VEC_FREE(ptr) free(ptr)
#endif

typedef struct {
	int *array;
	size_t size;
	size_t capacity;
} Vec;

void init_vec(Vec *vec, size_t capacity);
void free_vec(Vec *vec);

void append(Vec *vec, int element);
void delete_element(Vec *vec, size_t index);
int get_element(const Vec *vec, size_t index);
void resize_vec(Vec *vec, size_t new_capacity);
size_t size(const Vec *vec);
size_t capacity(const Vec *vec);

#ifdef VEC_IMPLEMENTATION

#include <assert.h>
#include <string.h>

void init_vec(Vec *vec, size_t capacity)
{
	vec->array = (int *)VEC_MALLOC(capacity * sizeof(int));
	VEC_ASSERT(vec->array != NULL);
	vec->size = 0;
	vec->capacity = capacity;
}

void free_vec(Vec *vec)
{
	VEC_FREE(vec->array);
	vec->array = NULL;
	vec->size = 0;
	vec->capacity = 0;
}

void append(Vec *vec, int element)
{
	if (vec->size == vec->capacity)
		resize_vec(vec, vec->capacity * 2);

	vec->array[vec->size++] = element;
}

void delete_element(Vec *vec, size_t index)
{
	if (index < vec->size) {
		memmove(
			&vec->array[index],
			&vec->array[index+1],
			(vec->size - index - 1) * sizeof(int)
		);
		
		--vec->size;
	}
}

int get_element(const Vec *vec, size_t index)
{
	VEC_ASSERT(index < vec->size);
	return vec->array[index];
}

void resize_vec(Vec *vec, size_t new_capacity)
{
	int *new_array = (int *)VEC_MALLOC(new_capacity * sizeof(int));
	VEC_ASSERT(new_array != NULL);
	memcpy(new_array, vec->array, vec->size * sizeof(int));
	VEC_FREE(vec->array);
	vec->array = new_array;
	vec->capacity = new_capacity;
}

size_t size(const Vec *vec)
{
	return vec->size;
}

size_t capacity(const Vec *vec)
{
	return vec->capacity;
}

#endif

#endif
