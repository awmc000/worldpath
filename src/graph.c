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

#include "../include/graph.h"
#include "../include/queue.h"
#include "../include/hash_table.h"

struct Vertex * construct_vertex(int i, const char * s)
{
	struct Vertex * new_vertex = calloc(1, sizeof(struct Vertex));

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
	
	new_path->vertices = calloc(1, sizeof(struct Vertex *));

	new_path->length = 0;
}

int path_insert(struct Path * path, struct Vertex * vert)
{
	// Reallocate vertices to hold length+1
	path->vertices = realloc(path->vertices, path->length + 1);
	
	// Set vertices[length] to vert
	path->vertices[path->length] = vert;

	// Increment length
	path->length++;
}

struct Path * find_path(struct Vertex * a, struct Vertex * b)
{
	struct Path * path = construct_path();

	path_insert(path, a);

	// Base case: a ~ b / a is adjacent to b, return (a,b)
	if (are_adjacent(a, b))
	{
		path_insert(path, b);
		return path;
	}

	// Normal case: a is not adjacent to b, use BFS	
	struct Queue * queue = construct_queue(MAX_BORDERS);
	
	// Initialize a hash map marking which nodes are visited
	struct hash_table * visited = hashtable_create(300);
	
	// Mark the start node as visited
	hashtable_insert(visited, a->s_data);

	// TODO:
	//Initialize a datastructure mapping each node to its previous node
	struct hash_table * previous = dictionary_create(300);

	// Repeat until the queue is empty :
	while (!queue_empty(queue))
	{
		// Extract a node from the front of queue
		struct Vertex * next_vertex = dequeue(queue);
		
		// If the node is the target :
		if (next_vertex == b)
		{
			// Use the mapping to trace backward and extract the path
			// Return the path
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

				// Add N to the end of the queue
				enqueue(queue, N);

				// Update the mapping so that N points to the node
				dictionary_insert(previous, N->s_data, next_vertex->s_data);
			}
		}
	}
	// Return no path

}