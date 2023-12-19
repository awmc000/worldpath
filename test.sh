gcc test/test.c src/graph.c src/queue.c -o testdriver -lcheck -lm -lsubunit
./testdriver
rm testdriver
