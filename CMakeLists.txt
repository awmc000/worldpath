cmake_minimum_required(VERSION 3.12)

# enable vcpkg
set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")

project(WorldMapGraph VERSION 1.0)

include_directories(/include)

# test program
add_executable(worldmapgraph test/test.c src/graph.c src/queue.c src/hash_table.c)

find_package(check CONFIG REQUIRED)
target_link_libraries(worldmapgraph PRIVATE $<IF:$<TARGET_EXISTS:Check::check>,Check::check,Check::checkShared>)
