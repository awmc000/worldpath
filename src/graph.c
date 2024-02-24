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
	new_vertex->neighbours = NULL;

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

	a->n_neighbours++;
	b->n_neighbours++;

	a->neighbours = realloc(a->neighbours, a->n_neighbours * sizeof(struct Vertex *));
	b->neighbours = realloc(b->neighbours, b->n_neighbours * sizeof(struct Vertex *));

	a->neighbours[a->n_neighbours - 1] = b;
	b->neighbours[b->n_neighbours - 1] = a;

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
	struct Path * new_path = calloc(1, sizeof(struct Path));
	if (new_path == NULL)
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
	path->vertices = realloc(path->vertices, (path->length + 1) * sizeof(*path->vertices));
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

	//Initialize a datastructure mapping each node to its previous node
	struct hash_table * previous = dictionary_create(300); 

	while (!queue_empty(queue))
	{
		struct Vertex * next_vertex = dequeue(queue);

		if (next_vertex == b)
		{
			// Use the mapping to trace backward and extract the path
			char * next_prev = b->s_data;
			path_insert(path, b->s_data);
			while (strcmp(next_prev, a->s_data) != 0)
			{
				next_prev = dictionary_get_value(previous, next_prev);
				path_insert(path, next_prev);
			}

			path_reverse(path);
			return path;
		}
		// For each neighbor N of the node :
		for (int i = 0; i < next_vertex->n_neighbours; i++)
		{
			struct Vertex * N = next_vertex->neighbours[i];
			// If N is unvisited :
			if (!hashtable_contains(visited, N->s_data))
			{
				// Mark N as visited
				hashtable_insert(visited, N->s_data);

				// Enqueue N
				enqueue(queue, N);

				// Update the mapping so that N points to the node
				dictionary_insert(previous, N->s_data, next_vertex->s_data); 
			}
		}
	}

	// Causes memory issues elsewhere!
	// hashtable_delete(visited);

	printf("find_path: NO PATH!\n");
	// Return no path
	return NULL;
}

int validate_path(struct Path * path, 
	struct hash_table * alpha2_to_numeric, struct Vertex * countryVertices[])
{
	// If the path has 0 or 1 node, it cannot have an invalid step.
	if (path->length < 2)
		return 1;
	
	for (int i = 0; i < path->length - 1; i++)
	{
		struct Vertex * v1 = countryVertices[
			atoi(dictionary_get_value(
				alpha2_to_numeric, 
				path->vertices[i]))];
		struct Vertex * v2 = countryVertices[
			atoi(dictionary_get_value(
				alpha2_to_numeric, 
				path->vertices[i+1]))];
		if (!are_adjacent(v1, v2))
			return 0;
	}
	return 1;
}