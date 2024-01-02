/**
 * Graph representation designed for use
 * in a world map geography puzzle game.
 * 
 * December 18th, 2023
 * 
 * Alex McColm
 *
 **/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "../include/graph.h"
#include "../include/queue.h"
#include "../include/hash_table.h"

// MSVC prefers _strdup over POSIX's strdup, as the former is a reserved name
#if defined(_WIN32)
#define strdup _strdup
#endif

struct Vertex * construct_vertex(int i, const char * s)
{
	struct Vertex * new_vertex = calloc(1, sizeof(struct Vertex));
	assert(new_vertex != NULL);
	new_vertex->i_data = i;
	new_vertex->s_data = strdup(s);
	new_vertex->n_neighbours = 0;
	new_vertex->neighbours = calloc(1, sizeof(struct Vertex *));

	return new_vertex;
}

int free_vertex(struct Vertex * vert)
{
	free(vert->s_data);
	
	if (vert->neighbours != NULL)
		free(vert->neighbours);
	
	free(vert);
	
	return 1;
}

int add_edge(struct Vertex * a, struct Vertex * b)
{
	a->neighbours[a->n_neighbours] = b;
	b->neighbours[b->n_neighbours] = a;

	a->n_neighbours++;
	b->n_neighbours++;

	a->neighbours = realloc(a->neighbours, a->n_neighbours);
	b->neighbours = realloc(b->neighbours, b->n_neighbours);

	return 1;
}

int are_adjacent(struct Vertex * a, struct Vertex * b)
{
	int found = 0;

	// check a for b
	for (int i = 0; i < a->n_neighbours; i++)
	{
		if (a->neighbours[i] == b)
			found = 1;
	}


	// check b for a (redundant)
	for (int i = 0; i < b->n_neighbours; i++)
	{
		if (b->neighbours[i] == a)
			found = 1;
	}

	return found;
}

void print_neighbours(struct Vertex * a)
{
	printf("Neighbours of [%d, %s]: ", a->i_data, a->s_data);
	for (int i = 0 ; i < a->n_neighbours; i++)
	{
		struct Vertex * curr = a->neighbours[i];
		printf("[%d, %s], ", curr->i_data, curr->s_data);
	}
	printf("\n");
}

/*
struct Path {
	int length;
	struct Vertex ** vertices;
};
*/
struct Path * construct_path()
{
	struct Path * new_path = calloc(1, sizeof(struct Path *));
	if( new_path == NULL )
		return NULL;
	
	new_path->vertices = calloc(1, sizeof(char *));
	if (new_path->vertices == NULL)
	{
		free(new_path);
		return NULL;
	}

	new_path->length = 0;

	return new_path;
}

// TODO: Make this function variadic
// O(1)
int path_insert(struct Path * path, char * vert)
{
	// Reallocate vertices to hold length+1
	path->vertices = realloc(path->vertices, path->length + 1);
	// TODO: handle realloc failure
	
	// Set vertices[length] to vert
	path->vertices[path->length] = vert;

	// Increment length
	path->length++;

	return 1;
}

void path_reverse(struct Path * path)
{
	for (int i = 0; i < path->length / 2; i++)
	{
		// A -> TEMP
		char * temp = path->vertices[i];
		// B -> A
		path->vertices[i] = path->vertices[path->length - 1 - i];
		// TEMP -> B
		path->vertices[path->length - 1 - i] = temp;
	}
}

// TODO: Make this function variadic
// O(N)
int path_prepend(struct Path * path, char * vert)
{
	// Reallocate vertices to hold length+1
	path->vertices = realloc(path->vertices, path->length + 1);
	// TODO: handle realloc failure
	
	// Copy over all existing vertices to the right one space
	for (int i = 1; i < path->length - 2; i++)
	{
		char * tmp = path->vertices[i];
		path->vertices[i] = path->vertices[i + 1];
		path->vertices[i+1] = tmp;
	}

	// Set vertices[0] to vert
	path->vertices[0] = vert;

	// Increment length
	path->length++;

	return 1;
}

// O(N)
void path_print(struct Path * path)
{
	fprintf(stderr, "printing path length %d\n", path->length);
	for (int i = 0; i < path->length; i++)
	{
		if (path->vertices[i] != NULL)
			fprintf(stderr, "[%d]: %s\n", i, path->vertices[i]);
		else
			fprintf(stderr, "%d is null\n", i);
	}
}


struct Path * find_path(struct Vertex * a, struct Vertex * b)
{
	struct Path * path = construct_path();


	// Base case: a ~ b / a is adjacent to b, return (a,b)
	if (are_adjacent(a, b))
	{
		path_insert(path, a->s_data);
		path_insert(path, b->s_data);
		return path;
	}

	// Normal case: a is not adjacent to b, use BFS	
	struct Queue * queue = construct_queue(MAX_BORDERS);
	enqueue(queue, a);

	// Initialize a hash map marking which nodes are visited
	struct hash_table * visited = hashtable_create(300);
	
	// Mark the start node as visited
	hashtable_insert(visited, a->s_data);

	// TODO:
	//Initialize a datastructure mapping each node to its previous node
	fprintf(stderr, "constructing previous hash table\n");
	struct hash_table * previous = dictionary_create(300); // seg fault occurs inside this call
	fprintf(stderr, "created previous\n");
	//fprintf(stderr, "%s\n", previous->values[0]); -- TRIGGERS SEGFAULT?
	//fprintf(stderr, "constructed previous hash table\n");
	// Repeat until the queue is empty :
	while (!queue_empty(queue))
	{
		// Extract a node from the front of queue
		struct Vertex * next_vertex = dequeue(queue);

		// If the node is the target :
		if (next_vertex == b)
		{
			// Use the mapping to trace backward and extract the path
			char * next_prev = b->s_data;
			path_insert(path, b->s_data);
			while (strcmp(next_prev, a->s_data) != 0)
			{
				next_prev = dictionary_get_value(previous, next_prev);
				//fprintf(stderr, "next_prev = %s\n", next_prev);
				path_insert(path, next_prev);
			}

			//path_print(path);

			// Reverse
			path_reverse(path);
			// Return the path
			return path;
		}
		// For each neighbor N of the node :
		for (int i = 0; i < next_vertex->n_neighbours; i++)
		{
			struct Vertex * N = next_vertex->neighbours[i];
			// If N is unvisited :
			if (!hashtable_contains(visited, N->s_data))
			{

				// fprintf(stderr, "Before visited insert: Size of visited ht is %d with %d elems\n", 
				// 	visited->array_size, visited->array_elems);

				// Mark N as visited
				hashtable_insert(visited, N->s_data);

				// fprintf(stderr, "After visited insert: Size of visited ht is %d with %d elems\n", 
				// 	visited->array_size, visited->array_elems);

				fprintf(stderr, "====\nBefore enqueuing N, Size of visited ht is %d with %d elems\n", 
					visited->array_size, visited->array_elems);
				// Add N to the end of the queue
				enqueue(queue, N); // It seems that this is where visited turns to null. But WHY?
				fprintf(stderr, "Enqueued %s\n", N->s_data);

				fprintf(stderr, "After enqueuing N, Size of visited ht is %d with %d elems\n====\n", 
					visited->array_size, visited->array_elems);

				// Update the mapping so that N points to the node
				dictionary_insert(previous, N->s_data, next_vertex->s_data);
				// fprintf(stderr, "Previous of %s is %s\n", N->s_data, next_vertex->s_data);
				// fprintf(stderr, "After inserting previous, Size of visited ht is %d with %d elems\n", 
				// 	visited->array_size, visited->array_elems);
				// Visited is becoming null somehow, and causing this print func call to access bad memory => segfault
				//hashtable_print_contents(visited, stderr); 
			}
		}
	}

	dictionary_delete(previous);
	hashtable_delete(visited);
	// Return no path
	return NULL;
}