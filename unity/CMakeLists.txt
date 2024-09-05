cmake_minimum_required(VERSION 3.30)
project(unity)

add_library(
    ${PROJECT_NAME}
    base/unity.c
    fixture/unity_fixture.c
    memory/unity_memory.c
)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
    base
    fixture
    memory
)