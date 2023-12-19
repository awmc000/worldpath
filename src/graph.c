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

struct Path * find_path(struct Vertex * a, struct Vertex * b)
{
	struct Queue * queue = construct_queue(MAX_BORDERS);
}

// driver code
int main(void)
{
	struct Vertex * a = construct_vertex(1, "a");
	struct Vertex * b = construct_vertex(2, "b");
	struct Vertex * c = construct_vertex(3, "c");
	add_edge(a, b);
	add_edge(a, c);
	printf("%d, %d\n", are_adjacent(a, b), are_adjacent(a, c));
	print_neighbours(a);
	return 0;
}
