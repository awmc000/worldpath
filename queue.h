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
	int head;
	int tail;
	int num_entries;
	int size;
};

/**
 * @brief
 * @param queue_size
 * @return
 **/
struct Queue * construct_queue(int queue_size);

/**
 * @brief
 * @param queue
 **/
void destroy_queue(struct Queue * queue);

/**
 * @brief
 * @param queue
 * @param value
 * @return
 **/
int enqueue(struct Queue * queue, struct Vertex * value);

/**
 * @brief
 * @param queue
 * @return
 **/
struct Vertex * dequeue(struct Queue * queue);

/**
 * @brief
 * @param queue
 * @return
 **/
int queue_empty(struct Queue * queue);

/**
 * @brief
 * @param queue
 * @return
 **/
int queue_full(struct Queue* queue);

#endif // QUEUE_H