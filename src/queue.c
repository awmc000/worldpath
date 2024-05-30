/*
    Worldpath is a homebrew geography game for the Nintendo DS.
    Copyright (C) 2024 Alex McColm

    This program is free software: you can redistribute it and/or modify 
	it under the terms of the GNU General Public License as published by 
	the Free Software Foundation, either version 3 of the License, or 
	(at your option) any later version.

    This program is distributed in the hope that it will be useful, but 
	WITHOUT ANY WARRANTY; without even the implied warranty of 
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
	General Public License for more details.

    You should have received a copy of the GNU General Public License 
	along with this program. If not, see https://www.gnu.org/licenses/.
*/
/**
 * Queue for use in pathfinding for the graph.
 * 
 * December 19th, 2023
 * 
 * Alex McColm
 **/
#include <stdlib.h>
#include "../include/queue.h"
#include "../include/graph.h"

/*
struct Queue {
	struct Vertex **values;
	int head;
	int tail;
	int num_entries;
	int size;
};
*/

struct Queue * construct_queue(int queue_size)
{
	struct Queue * new_queue = calloc(1, sizeof(*new_queue));
	
	new_queue->values = calloc(queue_size, sizeof(*new_queue->values));
	new_queue->head = 0;
	new_queue->tail = 0;
	new_queue->num_entries = 0;
	new_queue->size = queue_size;

	return new_queue;
}

void destroy_queue(struct Queue * queue)
{
	free(queue->values);
	free(queue);
}

int enqueue(struct Queue * queue, struct Vertex * value)
{
	if (queue_full(queue))
		return 0;

	// insert at tail pointer
	queue->values[queue->tail] = value;

	// increment # of entries
	queue->num_entries++;

	// increment tail, rolling back around if it hits the end
	queue->tail = (queue->tail + 1) % queue->size;

	return 1;
}

struct Vertex * dequeue(struct Queue * queue)
{

	if (queue_empty(queue))
		return NULL;

	// get element at head pointer
	struct Vertex * result = queue->values[queue->head];
	
	// decrement # of entries
	queue->num_entries--;

	// increment head, rolling back around if it hits the end
	queue->head = (queue->head + 1) % queue->size;

	return result;
}

int queue_empty(struct Queue * queue)
{
	return (queue->num_entries == 0);
}

int queue_full(struct Queue* queue)
{
	return (queue->num_entries == queue->size);
}
