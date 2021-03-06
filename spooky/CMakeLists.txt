cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

project(spooky C)

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

set(SOURCES src/spooky.c)

include_directories(include)

add_library(spooky STATIC ${SOURCES})

target_include_directories(spooky PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE src)

export(TARGETS spooky FILE spooky_config.cmake)
