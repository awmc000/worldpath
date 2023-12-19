#include <stdlib.h>
#include <check.h>
#include "../include/graph.h"
#include "../include/queue.h"

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
	ck_assert(a_to_b->vertices[0] == a);
	ck_assert(a_to_b->vertices[1] == b);
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
	
	ck_assert_int_eq(a_to_b->length, 4);
	ck_assert(a_to_b->vertices[0] == a);
	ck_assert(a_to_b->vertices[1] == b);
	ck_assert(a_to_b->vertices[2] == d);
	ck_assert(a_to_b->vertices[3] == e);
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
	suite_add_tcase(s, tc_core);

	return s;
}

int main(void)
{
	int number_failed;
	Suite *s;
	SRunner *sr;

	s = graph_suite();
	sr = srunner_create(s);

	srunner_run_all(sr, CK_NORMAL);
	number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);
	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}