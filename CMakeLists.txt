cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

project(hashing C)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif(NOT CMAKE_BUILD_TYPE)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

set(CMAKE_C_FLAGS_DEBUG "-std=c11 -Wall -Wextra -g")
set(CMAKE_C_FLAGS_RELEASE "-std=c11 -Wall -Wextra -O3")

if (CMAKE_BUILD_TYPE MATCHES Debug)
    add_definitions("-DDEBUG=1")
    add_definitions("-DLOG_LEVEL=5")
    add_definitions("-DLOG_VERBOSE=0")
else()
    add_definitions("-DNDEBUG=1")
    add_definitions("-DLOG_LEVEL=3")
    add_definitions("-DLOG_VERBOSE=0")
endif()

add_subdirectory(xxhash)
add_subdirectory(spooky)
add_subdirectory(murmurhash1)
add_subdirectory(murmurhash2)
