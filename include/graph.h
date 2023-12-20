/**
 * Graph representation designed for use
 * in a world map geography puzzle game.
 * 
 * December 18th, 2023
 * 
 * Alex McColm
 *
 **/
#ifndef GRAPH_H
#define GRAPH_H

// Max. number of countries bordering one country.
#define MAX_BORDERS 14

struct Vertex {
	int i_data; 					// integer data, country code
	char * s_data; 					// string data, country name
	int n_neighbours;				// number of neighbours
	struct Vertex ** neighbours;	// array of neighbours
};

struct Path {
	int length;
	char ** vertices;
};

/**
 * @brief Constructs a vertex on the heap to return.
 * @param i integer data, country code
 * @param s string data, country name
 * @return Pointer to vertex allocated on the heap.
 **/
struct Vertex * construct_vertex(int i, const char * s);

/**
 * @brief Frees a vertices' members and then itself.
 * @param vert Pointer to an existing vertex created with 
 * construct_vertex.
 * @return 1 on success.
 **/
int free_vertex(struct Vertex * vert);

/**
 * @brief Creates an edge connecting vertices a and b.
 * @param a Pointer to a vertex.
 * @param b Pointer to a vertex.
 * @return 1 on success.
 **/
int add_edge(struct Vertex * a, struct Vertex * b);

/**
 * @brief Returns if a is adjacent to b.
 * @param a Pointer to a vertex.
 * @param b Pointer to a vertex.
 * @return 1 if a ~ b, 0 otherwise.
 **/
int are_adjacent(struct Vertex * a, struct Vertex * b);

/**
 * @brief Given a vertex, prints its neighbours to stdout.
 **/
void print_neighbours(struct Vertex * a);

/**
 * @brief Constructs a Path object, basically an array
 * of vertices, on the heap.
 * @return Pointer to Path allocated on the heap. 
 **/
struct Path * construct_path();

/**
 * @brief Adds a string to the end of a path. TODO: make variadic.
 * @param path Pointer to path to add to.
 * @param vert Pointer to string to add to path.
 * @return 1 on success, 0 on failure.
 **/
int path_insert(struct Path * path, char * vert);

/**
 * @brief Adds a string to the beginning of a path. TODO: make variadic.
 * @param path Pointer to path to add to.
 * @param vert Pointer to string to add to path.
 * @return 1 on success, 0 on failure.
 **/
int path_prepend(struct Path * path, char * vert);

/**
 * @brief Prints the contents of a path in order.
 * @param path Pointer to a Path structure.
 **/
void path_print(struct Path * path);

/**
 * @brief Uses breadth-first search to find a path between
 * vertices a and b.
 * @param a Pointer to a vertex.
 * @param b Pointer to a vertex.
 * @return Pointer to a Path struct if a path was found, NULL 
 * otherwise.
 **/
struct Path * find_path(struct Vertex * a, struct Vertex * b);
#endif // GRAPH_H