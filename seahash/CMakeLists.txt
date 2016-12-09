cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

project(seahash C)

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

set(SOURCES src/seahash.c)

include_directories(include)

add_library(seahash STATIC ${SOURCES})

target_include_directories(seahash PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE src)

export(TARGETS seahash FILE seahash_config.cmake)

add_executable(seahash_test test/seahash_test.c)
target_link_libraries(seahash_test PUBLIC seahash)
add_test(NAME seahash_test COMMAND seahash_test)
