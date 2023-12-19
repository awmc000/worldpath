cmake_minimum_required(VERSION 3.12)

project(WorldMapGraph VERSION 1.0)

include_directories(/include)

add_executable(worldmapgraph src/graph.c src/queue.c)
