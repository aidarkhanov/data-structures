/*
	set.h — A simple, educational set implementation based on dynamic arrays.

Overview:
	set.h offers a minimalistic set for educational purposes and small projects. It supports
	basic set operations such as creation, destruction, addition, and membership checking.

	This implementation uses a basic dynamic array to store unique elements. Error checking 
	is performed using assertions to aid in learning.

Usage:
	```c
	#define SET_IMPLEMENTATION
	#include "set.h"

	#include <stdio.h>

	int main() {
		// Create a new set.
		Set *my_set = set_new();

		// Add elements to the set.
		for (int i = 0; i < 10; ++i) {
			set_add(my_set, i * i);
		}

		// Check for element's membership.
		printf("Does 16 belong to the set? %s\n", set_contains(my_set, 16) ? "Yes" : "No");

		// Remove element 9 from the set.
		set_remove(my_set, 9);

		// Free the set when done.
		set_free(my_set);
		return 0;
	}
	```
*/
#ifndef SET_H
#define SET_H

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

// The set structure
typedef struct {
	size_t size;
	size_t capacity;
	int *items;
} Set;

// Prototypes
Set *set_new();
void set_free(Set *set);
void set_add(Set *set, int item);
void set_remove(Set *set, int item);
int set_contains(const Set *set, int item);

#ifdef SET_IMPLEMENTATION

// Internal utility functions
static void set_resize(Set *set, size_t new_capacity) {
	int *new_items = realloc(set->items, new_capacity * sizeof(int));
	assert(new_items);

	set->items = new_items;
	set->capacity = new_capacity;
}

static void set_grow(Set *set) {
	if (set->size == set->capacity) {
		size_t new_capacity = set->capacity ? set->capacity * 2 : 1;
		set_resize(set, new_capacity);
	}
}

// Function implementations
Set *set_new() {
	Set *set = (Set *)malloc(sizeof(Set));
	assert(set);

	set->size = 0;
	set->capacity = 0;
	set->items = NULL;
	return set;
}

void set_free(Set *set) {
	assert(set);
	free(set->items);
	free(set);
}

void set_add(Set *set, int item) {
	if (!set_contains(set, item)) {
		set_grow(set);
		set->items[set->size++] = item;
	}
}

void set_remove(Set *set, int item) {
	for (size_t i = 0; i < set->size; ++i) {
		if (set->items[i] == item) {
			memmove(&set->items[i], &set->items[i + 1], (set->size - i - 1) * sizeof(int));
			--set->size;
			break;
		}
	}
}

int set_contains(const Set *set, int item) {
	for (size_t i = 0; i < set->size; ++i) {
		if (set->items[i] == item) {
			return 1;
		}
	}
	return 0;
}

#endif // SET_IMPLEMENTATION

#endif // SET_H
