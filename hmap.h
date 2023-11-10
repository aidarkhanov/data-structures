/*
	hmap.h — A simple, educational hash map (hash table) implementation.

Overview:
	This hash map implementation provides a basic understanding of how hash
	tables work in C. It uses separate chaining to resolve collisions, which
	means each bucket in the table points to a linked list of entries that
	fall into the same hash bucket.

	The implementation supports operations such as creating a hash map,
	destroying it, inserting key-value pairs, deleting them, and accessing
	values by key.

Hash Function:
	A critical part of a hash table is the hash function. A simple modular hash
	function is used here, which computes the hash as the key modulo the number
	of buckets. This is a starting point for educational purposes, but
	real-world applications would typically require more complex,
	well-distributed hash functions.

Collision resolution:
	This hash map uses separate chaining for collision resolution. Each bucket
	in the hash map is the head of a linked list. When a collision occurs, the
	new entry is added to the corresponding list. This method is
	straightforward and allows the hash table to remain efficient even with a
	high load factor.

Usage:
	```c
	#define HMAP_IMPLEMENTATION
	#include "hmap.h"

	#include <stdio.h>

	int main() {
		// Create a new hash map with an initial capacity of 8 buckets.
		HashMap *my_map = hmap_new(8);

		// Insert key-value pairs into the hash map.
		hmap_insert(my_map, "key1", "value1");
		hmap_insert(my_map, "key2", "value2");
		hmap_insert(my_map, "key3", "value3");

		// Access value by key.
		char *value = hmap_get(my_map, "key2");
		if (value) {
			printf("Value: %s\n", value);
		}

		// Delete key-value pair.
		hmap_delete(my_map, "key2");

		// Free the hash map when done.
		hmap_free(my_map);
		return 0;
	}
	```

	Note: This code does not handle string duplications for keys and values,
	and it assumes that the lifetime of strings passed to the functions
	outlives the hash map usage. Proper string handling should be added for a
	more robust implementation.
*/

#ifndef HMAP_H
#define HMAP_H

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

typedef struct HashMapEntry HashMapEntry;

struct HashMapEntry {
	char *key;
	char *value;
	HashMapEntry *next;
};

typedef struct {
	size_t bucket_count;
	HashMapEntry **buckets;
} HashMap;

HashMap *hmap_new(size_t initial_buckets);
void hmap_free(HashMap *map);
bool hmap_insert(HashMap *map, const char *key, const char *value);
bool hmap_delete(HashMap *map, const char *key);
char *hmap_get(HashMap *map, const char *key);
size_t hmap_hash(const char *key, size_t bucket_count);

#ifdef HMAP_IMPLEMENTATION

// Returns a map if created, null otherwise.
// Assertion handles memory problems.
HashMap *hmap_new(size_t initial_buckets) {
	if (initial_buckets == 0) return NULL;

	HashMap *map = (HashMap *)malloc(sizeof(HashMap));
	assert(map);

	map->bucket_count = initial_buckets;
	map->buckets = (HashMapEntry **)calloc(
		initial_buckets,
		sizeof(HashMapEntry *));
	assert(map->buckets);

	return map;
}

void hmap_free(HashMap *map) {
	assert(map);

	for (size_t i = 0; i < map->bucket_count; ++i) {
		HashMapEntry *entry = map->buckets[i];
		while (entry) {
			HashMapEntry *next = entry->next;
			free(entry->key);
			free(entry->value);
			free(entry);
			entry = next;
		}
	}

	free(map->buckets);
	free(map);
}

size_t hmap_hash(const char *key, size_t bucket_count) {
	size_t hash = 0;
	while (*key) {
		hash = (hash * 31) + *(key++);
	}
	return hash % bucket_count;
}

// Returns `true` if inserted, `false` otherwise.
// Assertion handles memory problems.
bool hmap_insert(HashMap *map, const char *key, const char *value) {
	assert(map);

	char *dup_key = strdup(key), *dup_value = strdup(value);
	assert(dup_key && dup_value);

	size_t index = hmap_hash(key, map->bucket_count);
	HashMapEntry *entry = map->buckets[index];

	// Check if the key already exists and update the value.
	while (entry) {
		if (strcmp(entry->key, dup_key) == 0) {
			free(entry->key);
			free(entry->value);
			entry->key = dup_key;
			entry->value = dup_value;
			return true;
		}
		entry = entry->next;
	}

	// Key does not exist, create a new entry.
	HashMapEntry *new_entry = (HashMapEntry *)malloc(sizeof(HashMapEntry));
	assert(new_entry);

	new_entry->key = dup_key;
	new_entry->value = dup_value;
	new_entry->next = map->buckets[index];
	map->buckets[index] = new_entry;

	return false;
}

// Returns `true` if deleted, `false` otherwise.
// Assertion handles memory problems.
bool hmap_delete(HashMap *map, const char *key) {
	assert(map);

	size_t index = hmap_hash(key, map->bucket_count);
	HashMapEntry *entry = map->buckets[index];
	HashMapEntry *prev = NULL;

	while (entry) {
		if (strcmp(entry->key, key) == 0) {
			if (prev) {
				prev->next = entry->next;
			} else {
				map->buckets[index] = entry->next;
			}

			free(entry->key);
			free(entry->value);
			free(entry);
			return true;  // Entry is found and deleted using key.
		}

		prev = entry;
		entry = entry->next;
	}

	return false;
}

// Returns a value if successful, null otherwise.
// Assertion handles memory problems.
char *hmap_get(HashMap *map, const char *key) {
	assert(map);

	size_t index = hmap_hash(key, map->bucket_count);
	HashMapEntry *entry = map->buckets[index];

	while (entry) {
		if (strcmp(entry->key, key) == 0) {
			return entry->value;
		}

		entry = entry->next;
	}

	return NULL;
}

#endif // HMAP_IMPLEMENTATION

#endif // HMAP_H
