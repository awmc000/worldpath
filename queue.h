/**
 * Queue for use in pathfinding for the graph.
 * 
 * December 19th, 2023
 * 
 * Alex McColm
 **/
#ifndef QUEUE_H
#define QUEUE_H

struct Queue {
	struct Vertex **values;
	struct Vertex * head;
	struct Vertex * tail;
	int num_entries;
	int size;
};

#endif // QUEUE_H