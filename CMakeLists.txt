cmake_minimum_required(VERSION 3.12)

project(WorldMapGraph VERSION 1.0)

include_directories(/include)

# test program
add_executable(worldmapgraph test/test.c src/graph.c src/queue.c src/hash_table.c)
