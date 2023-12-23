gcc -g test/test.c src/graph.c src/queue.c src/hash_table.c -o testdriver -lcheck -lm -lsubunit
./testdriver
