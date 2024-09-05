cmake_minimum_required(VERSION 3.30)
project(circular-buffer)

add_subdirectory(unity)

add_executable(
    ${PROJECT_NAME}
    main.c
    src/circular_buffer.c
    tests/circular_buffer_test.c
)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
    src
)

target_link_libraries(
    ${PROJECT_NAME}
    unity
)