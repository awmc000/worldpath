/**
 * December 19th, 2023
 * 
 * Test cases and test driver for world map graph
 **/
#include <stdlib.h>
#include <stdio.h>
#include <check.h>
#include "../include/graph.h"
#include "../include/queue.h"
#include "../include/hash_table.h"

START_TEST(test_graph_construct_vertex)
{
	struct Vertex * vert = construct_vertex(0, "A");
	
	ck_assert_int_eq(vert->i_data, 0);
	ck_assert_str_eq(vert->s_data, "A");

	free_vertex(vert);
}
END_TEST

START_TEST(test_graph_add_edge)
{
	struct Vertex * a = construct_vertex(0, "A");
	struct Vertex * b = construct_vertex(1, "B");

	ck_assert_int_eq(add_edge(a, b), 1);

	ck_assert_int_eq(are_adjacent(a, b), 1);

	ck_assert_msg(a->neighbours[0] == b, "A's first neighbour is B");
	ck_assert_msg(b->neighbours[0] == a, "B's first neighbour is A");

	free_vertex(a);
	free_vertex(b);
}
END_TEST

START_TEST(test_graph_find_path_adjacent)
{
	struct Vertex * a = construct_vertex(0, "A");
	struct Vertex * b = construct_vertex(1, "B");

	ck_assert_int_eq(add_edge(a, b), 1);

	struct Path * a_to_b = find_path(a, b);
	
	ck_assert_int_eq(a_to_b->length, 2);
	ck_assert_str_eq(a_to_b->vertices[0], a->s_data);
	ck_assert_str_eq(a_to_b->vertices[1], b->s_data);
}
END_TEST

START_TEST(test_graph_find_path_nonadjacent)
{
	/*
	 * Construct this graph:
	 *          A
	 *          |
	 *          B - C
	 *          |
	 *          D
	 *          |
	 *          E
	 */
	struct Vertex * a = construct_vertex(0, "A");
	struct Vertex * b = construct_vertex(1, "B");
	struct Vertex * c = construct_vertex(2, "C");
	struct Vertex * d = construct_vertex(3, "D");
	struct Vertex * e = construct_vertex(4, "E");

	ck_assert_int_eq(add_edge(a, b), 1);
	ck_assert_int_eq(add_edge(b, c), 1);
	ck_assert_int_eq(add_edge(b, d), 1);
	ck_assert_int_eq(add_edge(d, e), 1);

	struct Path * a_to_b = find_path(a, e);
	
	path_print(a_to_b);

	ck_assert_int_eq(a_to_b->length, 4);
	ck_assert_str_eq(a_to_b->vertices[0], a->s_data);
	ck_assert_str_eq(a_to_b->vertices[1], b->s_data);
	ck_assert_str_eq(a_to_b->vertices[2], d->s_data);
	ck_assert_str_eq(a_to_b->vertices[3], e->s_data);
}
END_TEST

START_TEST(test_graph_find_path_complex)
{
	/*
	 * Construct this graph:
	 *          A
	 *        / |  \
	 *       B  C---D
	 *       |     /  
	 *       E    /
	 *       |   /
	 *       F  /
	 *       | /
	 *       G/
	 */
	struct Vertex * a = construct_vertex(0, "A");
	struct Vertex * b = construct_vertex(1, "B");
	struct Vertex * c = construct_vertex(2, "C");
	struct Vertex * d = construct_vertex(3, "D");
	struct Vertex * e = construct_vertex(4, "E");
	struct Vertex * f = construct_vertex(4, "F");
	struct Vertex * g = construct_vertex(4, "G");

	ck_assert_int_eq(add_edge(a, b), 1);
	ck_assert_int_eq(add_edge(a, c), 1);
	ck_assert_int_eq(add_edge(a, d), 1);
	ck_assert_int_eq(add_edge(b, e), 1);
	ck_assert_int_eq(add_edge(e, f), 1);
	ck_assert_int_eq(add_edge(f, g), 1);
	ck_assert_int_eq(add_edge(d, g), 1);

	// We should get the path A -> D -> G
	struct Path * a_to_g = find_path(a, g);

	path_print(a_to_g);

}
END_TEST
Suite * graph_suite(void)
{
	Suite *s;
	TCase *tc_core;

	s = suite_create("Graph");

	tc_core = tcase_create("Core");

	tcase_add_test(tc_core, test_graph_construct_vertex);
	tcase_add_test(tc_core, test_graph_add_edge);
	tcase_add_test(tc_core, test_graph_find_path_adjacent);
	tcase_add_test(tc_core, test_graph_find_path_nonadjacent);
	//tcase_add_test(tc_core, test_graph_find_path_complex);
	suite_add_tcase(s, tc_core);

	return s;
}

START_TEST(test_hash_table_create)
{
	struct hash_table *ht = hashtable_create(10);
	ck_assert(ht != NULL);
}
END_TEST

START_TEST(test_hash_table_insert)
{
	struct hash_table *ht = hashtable_create(10);
	char *word = calloc(5 + 1, sizeof(char));
	strcpy(word, "Hello");
	hashtable_insert(ht, word);
	ck_assert(ht != NULL);
}
END_TEST

START_TEST(test_hash_table_find)
{
	struct hash_table *ht = hashtable_create(10);
	char *word = calloc(5 + 1, sizeof(char));
	strcpy(word, "Hello");
	hashtable_insert(ht, word);
	ck_assert(hashtable_contains(ht, "Hello"));
}
END_TEST

START_TEST(test_hash_table_find_missing)
{
	struct hash_table *ht = hashtable_create(10);
	char *word = calloc(5 + 1, sizeof(char));
	strcpy(word, "Hello");
	hashtable_insert(ht, word);
	ck_assert(!hashtable_contains(ht, "Boots"));
}
END_TEST

START_TEST(test_hash_table_remove)
{
	struct hash_table *ht = hashtable_create(10);
	char *word = calloc(5 + 1, sizeof(char));
	strcpy(word, "Hello");
	hashtable_insert(ht, word);
	hashtable_remove(ht, word);
	ck_assert(!hashtable_contains(ht, word));
}
END_TEST

START_TEST(test_hash_table_full)
{
		struct hash_table *ht = hashtable_create(100);

	char* words[100] = {
		"apple", "banana", "orange", "grape", "pineapple", "kiwi", "mango", 
		"pear", "watermelon", "strawberry", "peach", "blueberry", "cherry", 
		"apricot", "raspberry", "plum", "lemon", "lime", "coconut", 
		"pomegranate", "avocado", "blackberry", "fig", "guava", "cranberry", 
		"papaya", "melon", "tangerine", "nectarine", "kiwifruit", 
		"passionfruit", "rhubarb", "dragonfruit", "gooseberry", "lychee", 
		"boysenberry", "persimmon", "mulberry", "cantaloupe", "honeydew", 
		"date", "elderberry", "grapefruit", "starfruit", "apricot", "currant", 
		"durian", "jackfruit", "plantain", "kumquat", "tamarind", "cloudberry", 
		"pawpaw", "breadfruit", "quince", "guinep", "ackee", "pummelo", 
		"cupuacu", "salak", "rambutan", "soursop", "santol", "sapote", 
		"surinam cherry", "ugli fruit", "yuzu", "limequat", "lychee", 
		"persimmon", "pomelo", "quincerino", "tamarillo", "ugli fruit", "yuzu", 
		"feijoa", "chirimoya", "black sapote", "canistel", "abiu", "calamondin", 
		"clementine", "blood orange", "white sapote", "breadnut", "jabuticaba", 
		"white currant", "golden kiwi", "green sapote", "redcurrant", 
		"miracle fruit", "green sapote", "honeyberry", "tayberry", "yumberry", 
		"ziziphus", "acai", "safou", "breadnut", "gooseberry"
	};

	unsigned int successful_adds = 0;

	for (int i = 0; i < 100; i++)
	{
		successful_adds += (hashtable_insert(ht, words[i]));
	}

	ck_assert_int_eq(ht->array_elems, 100);
}
END_TEST

START_TEST(test_hash_table_resize)
{
	struct hash_table *ht = hashtable_create(10);

	hashtable_insert(ht, "Hello");
	hashtable_insert(ht, "Bello");
	hashtable_insert(ht, "Mello");
	hashtable_insert(ht, "Yello");
	hashtable_insert(ht, "Sello");

	ht = hashtable_resize(ht, 100);
	printf("Size now %d\n", ht->array_size);

	hashtable_print_contents(ht, stdout);

	ht = hashtable_resize(ht, 200);
	printf("Size now %d\n", ht->array_size);

	hashtable_print_contents(ht, stdout);

	ck_assert(ht->array_size == 200);

	hashtable_delete(ht);
}
END_TEST

START_TEST(test_hash_table_dictionary_create)
{
	struct hash_table *ht = dictionary_create(10);
	ck_assert(ht != NULL);
	ck_assert_int_eq(ht->is_dictionary, 1);
}
END_TEST
/*
START_TEST(test_hash_table_dictionary_insert)
{
	struct hash_table *ht = hashtable_create(10);
	char *word = calloc(5 + 1, sizeof(char));
	strcpy(word, "Hello");
	hashtable_insert(ht, word);
	ck_assert(ht != NULL);
}
END_TEST
*/
START_TEST(test_hash_table_dictionary_find)
{
	struct hash_table *ht = dictionary_create(10);
	char *key = strdup("Canada");
	char *value = strdup("United States of America");
	dictionary_insert(ht, key, value);
	ck_assert_str_eq(dictionary_get_value(ht, key), value);
}
END_TEST

Suite * hash_table_suite(void)
{
	Suite *s;
	TCase *tc_core;

	s = suite_create("Hash table");

	tc_core = tcase_create("Core");

	/*
	test_hash_table_create
	test_hash_table_insert
	test_hash_table_find
	test_hash_table_find_missing
	test_hash_table_remove
	test_hash_table_full
	test_hash_table_resize
	*/

	tcase_add_test(tc_core, test_hash_table_create);
	tcase_add_test(tc_core, test_hash_table_insert);
	tcase_add_test(tc_core, test_hash_table_find);
	tcase_add_test(tc_core, test_hash_table_find_missing);
	tcase_add_test(tc_core, test_hash_table_remove);
	tcase_add_test(tc_core, test_hash_table_full);
	//tcase_add_test(tc_core, test_hash_table_resize);
	tcase_add_test(tc_core, test_hash_table_dictionary_create);
	tcase_add_test(tc_core, test_hash_table_dictionary_find);
	suite_add_tcase(s, tc_core);

	return s;
}

START_TEST(test_queue_basic_use)
{
	// Declare pointer
	struct Queue * queue;

	// Construct
	queue = construct_queue(10);

	// Make some vertices
	struct Vertex * a = construct_vertex(1, "A");
	struct Vertex * b = construct_vertex(2, "B");
	struct Vertex * c = construct_vertex(3, "C");
	struct Vertex * d = construct_vertex(4, "D");
	struct Vertex * e = construct_vertex(5, "E");
	struct Vertex * f = construct_vertex(6, "F");
	struct Vertex * g = construct_vertex(7, "G");
	struct Vertex * h = construct_vertex(8, "H");
	struct Vertex * i = construct_vertex(9, "I");
	struct Vertex * j = construct_vertex(10, "J");

	enqueue(queue, a);
	ck_assert_int_eq(queue->num_entries, 1);

	enqueue(queue, b);
	ck_assert_int_eq(queue->num_entries, 2);

	enqueue(queue, c);
	ck_assert_int_eq(queue->num_entries, 3);

	enqueue(queue, d);
	ck_assert_int_eq(queue->num_entries, 4);

	enqueue(queue, e);
	ck_assert_int_eq(queue->num_entries, 5);

	enqueue(queue, f);
	ck_assert_int_eq(queue->num_entries, 6);

	enqueue(queue, g);
	ck_assert_int_eq(queue->num_entries, 7);

	enqueue(queue, h);
	ck_assert_int_eq(queue->num_entries, 8);

	enqueue(queue, i);
	ck_assert_int_eq(queue->num_entries, 9);

	enqueue(queue, j);
	ck_assert_int_eq(queue->num_entries, 10);
	
	ck_assert(!queue_empty(queue));
	ck_assert(queue_full(queue));

	for (int ct = 0; ct < 10; ct++)
		dequeue(queue);
	
	ck_assert(queue_empty(queue));

	dequeue(queue);

	// Destroy when done
	destroy_queue(queue);
}
END_TEST

Suite * queue_suite(void)
{
	Suite *s;
	TCase *tc_core;

	s = suite_create("Queue");

	tc_core = tcase_create("Core");

	tcase_add_test(tc_core, test_queue_basic_use);
	suite_add_tcase(s, tc_core);

	return s;
}

int main(void)
{
	int number_failed;
	Suite *s;
	SRunner *sr;

	// Graph suite first
	s = graph_suite();
	sr = srunner_create(s);

	srunner_run_all(sr, CK_NORMAL);
	number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);

	if (number_failed != 0)
	{
		return EXIT_FAILURE;
	}

	// Then hash table suite
	s = hash_table_suite();
	sr = srunner_create(s);

	srunner_run_all(sr, CK_NORMAL);
	number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);

	// Queue suite
	s = queue_suite();
	sr = srunner_create(s);
	srunner_run_all(sr, CK_NORMAL);
	number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);

	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}