# Makefile for worldpath project
#
# Got rid of CMake and doing it from scratch.
#
# Feb 12, 2024
#
# Alex McColm
main: hash_table.o queue.o graph.o world.o
	gcc -I include hash_table.o queue.o graph.o world.o \
		-o worldpath -Wall -Wextra

memcheck: hash_table.o queue.o graph.o world.o
	gcc -g -I include hash_table.o queue.o graph.o world.o \
		-o worldpath -Wall -Wextra -fsanitize=address


hash_table.o: src/hash_table.c
	gcc -I include -c src/hash_table.c

queue.o: src/queue.c
	gcc -I include -c src/queue.c

graph.o: src/graph.c
	gcc -I include -c src/graph.c

world.o: src/world.c
	gcc -I include -c src/world.c

clean:
	rm *.o worldpath testdriver

test: FORCE
	gcc -g test/test.c src/hash_table.c src/queue.c \
		src/graph.c -o testdriver -lcheck -lm -lsubunit 
	./testdriver

FORCE: ;
