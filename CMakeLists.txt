cmake_minimum_required(VERSION 3.20)

project(at LANGUAGES C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_C_COMPILER_FLAGS -Wall -Wextra -Wpedantic -Werror)

if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    set(CMAKE_C_COMPILER_FLAGS ${CMAKE_C_COMPILER_FLAGS} -g -O0)
else()
    set(CMAKE_C_COMPILER_FLAGS ${CMAKE_C_COMPILER_FLAGS} -O3)
endif()

message(STATUS "CMAKE_C_COMPILER_FLAGS is ${CMAKE_C_COMPILER_FLAGS}")

add_subdirectory(lib)

add_executable(${PROJECT_NAME} main.c)
target_link_libraries(${PROJECT_NAME} PRIVATE atunnel::atunnel)
