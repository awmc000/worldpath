/*
 * Original for Readability: August 5th, 2023
 *
 * Brought into graph project for use in BFS: December 19th, 2023
 *
 * hash_table.h
 *
 * Alex McColm
 *
 * Hash table to mark vertices as visited.
 **/
#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdio.h>

#define INITIAL_SIZE 100
#define MAX_PROBES 100

struct hash_table {
	unsigned int array_size;
	unsigned int array_elems;
	unsigned int (*hash)(char *);
	char **strings;
	
	int is_dictionary;
	char **values;
};

/**
 * @return a pointer to a newly allocated hashtable or NULL if 
 * allocation failed.
 **/
struct hash_table *hashtable_create(size_t initial_size);

struct hash_table *dictionary_create(size_t initial_size);

/**
 * @brief Inserts the string `s` to the hash table `ht`. 
 * @return 1 on success and 0 on failure.
 **/
int hashtable_insert(struct hash_table *ht, char * s);

int dictionary_insert(struct hash_table *ht, char * key, char * value);

/**
 * @brief Removes the string `s` from the hash_table `ht`. 
 * @return 1 if found and removed and 0 if not found.
 **/
int hashtable_remove(struct hash_table *ht, char * s);

/**
 * @brief Removes the string `s` from the hash_table `ht`. 
 * @return 1 if found and 0 if not found.
 **/
int hashtable_contains(struct hash_table *ht, char * search_key);

char * dictionary_get_value(struct hash_table *dict, char * search_key);
/**
 * @brief Resize the hash table to the specified size.
 * Uses the C library function `realloc()`.
 **/
struct hash_table *hashtable_resize(struct hash_table *ht, size_t size);

/**
 * @brief Prints the contents of the hash table to the given file pointer.
 **/
void hashtable_print_contents(struct hash_table *ht, FILE *fp);

/**
 * @brief Frees the contents of a hash table.
 **/
void hashtable_delete(struct hash_table *ht);

void dictionary_delete(struct hash_table * dict);

#endif // HASH_TABLE_H