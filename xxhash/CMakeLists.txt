cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

project(xxhash C)

set(SOURCES src/xxhash.c)

include_directories(include)

add_library(xxhash STATIC ${SOURCES})

target_include_directories(xxhash PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE src)

export(TARGETS xxhash FILE xxhash_config.cmake)
