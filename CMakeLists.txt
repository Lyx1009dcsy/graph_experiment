cmake_minimum_required(VERSION 3.10)

project(scenic_route_planning C)

set(CMAKE_C_STANDARD 99)

include_directories(include)

add_executable(scenic_route_planning
    src/main.c
    src/matrix_graph.c
)

set_target_properties(scenic_route_planning PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
