cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

project(murmurhash3 C)

set(VERSION_MAJOR   0   CACHE STRING "Project major version number.")
set(VERSION_MINOR   1   CACHE STRING "Project minor version number.")
set(VERSION_PATCH   0   CACHE STRING "Project patch version number.")
mark_as_advanced(VERSION_MAJOR VERSION_MINOR VERSION_PATCH)

set(CMAKE_C_FLAGS_DEBUG "-std=c11 -Wall -Wextra -g")
set(CMAKE_C_FLAGS_RELEASE "-std=c11 -Wall -Wextra -flto -O3")

if (CMAKE_BUILD_TYPE MATCHES Debug)
    add_definitions("-DDEBUG=1")
else()
    add_definitions("-DNDEBUG=1")
endif()

set(SOURCES src/all.c)

if (${CMAKE_TARGET_ARCHITECTURES} STREQUAL "x86_64")
    list(APPEND SOURCES src/x64/murmurhash3.c)
else()
    list(APPEND SOURCES src/x86/murmurhash3.c)
endif()

include_directories(include)

add_library(murmurhash3 STATIC ${SOURCES})

target_include_directories(murmurhash3 PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE src)

export(TARGETS murmurhash3 FILE murmurhash3_config.cmake)
