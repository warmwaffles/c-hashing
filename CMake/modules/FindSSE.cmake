#   CMake module for check whether a SSE nstructions can be used on the machine.
#
#   - Supports SSE2/SSE3/SSSE3/SSE4.1/SSE4.2/AVX/AVX2
#   - Supports check GCC version(-msse4.2 can use on GCC 4.3 or later)
#
#   Usage
#   =====
#     SET (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
#
#     INCLUDE(FindSSE)
#     FindSSE ()
#     IF(SSE3_FOUND)
#         IF(SSSE3_FOUND)
#                 SET(CXX_DFLAGS -msse3 -mssse3)
#         ENDIF(SSSE3_FOUND)
#     ENDIF(SSE3_FOUND)
#
#     IF(SSE4_2_FOUND)
#             SET(CXX_DFLAGS -msse4.2 -mpopcnt)
#     ENDIF(SSE4_2_FOUND)
#     ADD_DEFINITIONS(${CXX_DFLAGS})
#
#   Variables
#   =========
#     - SSE2_FOUND
#     - SSE3_FOUND
#     - SSSE3_FOUND
#     - SSE4_1_FOUND
#     - SSE4_2_FOUND

IF(CMAKE_SYSTEM_NAME MATCHES "Linux")
    EXEC_PROGRAM(cat ARGS "/proc/cpuinfo" OUTPUT_VARIABLE CPUINFO)

    STRING(REGEX REPLACE "^.*(sse2).*$" "\\1" SSE_THERE ${CPUINFO})
    STRING(COMPARE EQUAL "sse2" "${SSE_THERE}" SSE2_TRUE)
    IF (SSE2_TRUE)
        set(SSE2_FOUND true CACHE BOOL "SSE2 available on host")
    ELSE (SSE2_TRUE)
        set(SSE2_FOUND false CACHE BOOL "SSE2 available on host")
    ENDIF (SSE2_TRUE)

    # /proc/cpuinfo apparently omits sse3 :(
    STRING(REGEX REPLACE "^.*[^s](sse3).*$" "\\1" SSE_THERE ${CPUINFO})
    STRING(COMPARE EQUAL "sse3" "${SSE_THERE}" SSE3_TRUE)
    IF (NOT SSE3_TRUE)
        STRING(REGEX REPLACE "^.*(T2300).*$" "\\1" SSE_THERE ${CPUINFO})
        STRING(COMPARE EQUAL "T2300" "${SSE_THERE}" SSE3_TRUE)
    ENDIF (NOT SSE3_TRUE)

    STRING(REGEX REPLACE "^.*(ssse3).*$" "\\1" SSE_THERE ${CPUINFO})
    STRING(COMPARE EQUAL "ssse3" "${SSE_THERE}" SSSE3_TRUE)
    IF (SSE3_TRUE OR SSSE3_TRUE)
        set(SSE3_FOUND true CACHE BOOL "SSE3 available on host")
    ELSE (SSE3_TRUE OR SSSE3_TRUE)
        set(SSE3_FOUND false CACHE BOOL "SSE3 available on host")
    ENDIF (SSE3_TRUE OR SSSE3_TRUE)
    IF (SSSE3_TRUE)
        set(SSSE3_FOUND true CACHE BOOL "SSSE3 available on host")
    ELSE (SSSE3_TRUE)
        set(SSSE3_FOUND false CACHE BOOL "SSSE3 available on host")
    ENDIF (SSSE3_TRUE)

    STRING(REGEX REPLACE "^.*(sse4_1).*$" "\\1" SSE_THERE ${CPUINFO})
    STRING(COMPARE EQUAL "sse4_1" "${SSE_THERE}" SSE41_TRUE)
    IF (SSE41_TRUE)
        set(SSE4_1_FOUND true CACHE BOOL "SSE4.1 available on host")
    ELSE (SSE41_TRUE)
        set(SSE4_1_FOUND false CACHE BOOL "SSE4.1 available on host")
    ENDIF (SSE41_TRUE)

    STRING(REGEX REPLACE "^.*(sse4_2).*$" "\\1" SSE_THERE ${CPUINFO})
    STRING(COMPARE EQUAL "sse4_2" "${SSE_THERE}" SSE42_TRUE)
    IF (SSE42_TRUE)
        set(SSE4_2_FOUND true CACHE BOOL "SSE4.2 available on host")
    ELSE (SSE42_TRUE)
        set(SSE4_2_FOUND false CACHE BOOL "SSE4.2 available on host")
    ENDIF (SSE42_TRUE)

    STRING(REGEX REPLACE "^.*(avx).*$" "\\1" SSE_THERE ${CPUINFO})
    STRING(COMPARE EQUAL "avx" "${SSE_THERE}" AVX_TRUE)
    IF (AVX_TRUE)
        set(AVX_FOUND true CACHE BOOL "AVX available on host")
    ELSE (AVX_TRUE)
        set(AVX_FOUND false CACHE BOOL "AVX available on host")
    ENDIF (AVX_TRUE)

    STRING(REGEX REPLACE "^.*(avx2).*$" "\\1" SSE_THERE ${CPUINFO})
    STRING(COMPARE EQUAL "avx2" "${SSE_THERE}" AVX2_TRUE)
    IF (AVX2_TRUE)
        set(AVX2_FOUND true CACHE BOOL "AVX2 available on host")
    ELSE (AVX2_TRUE)
        set(AVX2_FOUND false CACHE BOOL "AVX2 available on host")
    ENDIF (AVX2_TRUE)

ELSEIF(CMAKE_SYSTEM_NAME MATCHES "Darwin")
    EXEC_PROGRAM("/usr/sbin/sysctl -n machdep.cpu.features" OUTPUT_VARIABLE CPUINFO)

    STRING(REGEX REPLACE "^.*[^S](SSE2).*$" "\\1" SSE_THERE ${CPUINFO})
    STRING(COMPARE EQUAL "SSE2" "${SSE_THERE}" SSE2_TRUE)
    IF (SSE2_TRUE)
        set(SSE2_FOUND true CACHE BOOL "SSE2 available on host")
    ELSE (SSE2_TRUE)
        set(SSE2_FOUND false CACHE BOOL "SSE2 available on host")
    ENDIF (SSE2_TRUE)

    STRING(REGEX REPLACE "^.*[^S](SSE3).*$" "\\1" SSE_THERE ${CPUINFO})
    STRING(COMPARE EQUAL "SSE3" "${SSE_THERE}" SSE3_TRUE)
    IF (SSE3_TRUE)
        set(SSE3_FOUND true CACHE BOOL "SSE3 available on host")
    ELSE (SSE3_TRUE)
        set(SSE3_FOUND false CACHE BOOL "SSE3 available on host")
    ENDIF (SSE3_TRUE)

    STRING(REGEX REPLACE "^.*(SSSE3).*$" "\\1" SSE_THERE ${CPUINFO})
    STRING(COMPARE EQUAL "SSSE3" "${SSE_THERE}" SSSE3_TRUE)
    IF (SSSE3_TRUE)
        set(SSSE3_FOUND true CACHE BOOL "SSSE3 available on host")
    ELSE (SSSE3_TRUE)
        set(SSSE3_FOUND false CACHE BOOL "SSSE3 available on host")
    ENDIF (SSSE3_TRUE)

    STRING(REGEX REPLACE "^.*(SSE4.1).*$" "\\1" SSE_THERE ${CPUINFO})
    STRING(COMPARE EQUAL "SSE4.1" "${SSE_THERE}" SSE41_TRUE)
    IF (SSE41_TRUE)
        set(SSE4_1_FOUND true CACHE BOOL "SSE4.1 available on host")
    ELSE (SSE41_TRUE)
        set(SSE4_1_FOUND false CACHE BOOL "SSE4.1 available on host")
    ENDIF (SSE41_TRUE)

    STRING(REGEX REPLACE "^.*(SSE4.2).*$" "\\1" SSE_THERE ${CPUINFO})
    STRING(COMPARE EQUAL "SSE4.2" "${SSE_THERE}" SSE42_TRUE)
    IF (SSE42_TRUE)
        set(SSE4_2_FOUND true CACHE BOOL "SSE4.2 available on host")
    ELSE (SSE42_TRUE)
        set(SSE4_2_FOUND false CACHE BOOL "SSE4.2 available on host")
    ENDIF (SSE42_TRUE)

    STRING(REGEX REPLACE "^.*(AVX).*$" "\\1" SSE_THERE ${CPUINFO})
    STRING(COMPARE EQUAL "AVX" "${SSE_THERE}" AVX_TRUE)
    IF (AVX_TRUE)
        set(AVX_FOUND true CACHE BOOL "AVX available on host")
    ELSE (AVX_TRUE)
        set(AVX_FOUND false CACHE BOOL "AVX available on host")
    ENDIF (AVX_TRUE)

    STRING(REGEX REPLACE "^.*(AVX2).*$" "\\1" SSE_THERE ${CPUINFO})
    STRING(COMPARE EQUAL "AVX2" "${SSE_THERE}" AVX2_TRUE)
    IF (AVX2_TRUE)
        set(AVX2_FOUND true CACHE BOOL "AVX2 available on host")
    ELSE (AVX2_TRUE)
        set(AVX2_FOUND false CACHE BOOL "AVX2 available on host")
    ENDIF (AVX2_TRUE)

ELSEIF(CMAKE_SYSTEM_NAME MATCHES "Windows")
    # TODO
    set(SSE2_FOUND   true  CACHE BOOL "SSE2 available on host")
    set(SSE3_FOUND   false CACHE BOOL "SSE3 available on host")
    set(SSSE3_FOUND  false CACHE BOOL "SSSE3 available on host")
    set(SSE4_1_FOUND false CACHE BOOL "SSE4.1 available on host")
    set(SSE4_2_FOUND false CACHE BOOL "SSE4.2 available on host")
    set(AVX_FOUND false CACHE BOOL "AVX available on host")
    set(AVX2_FOUND false CACHE BOOL "AVX2 available on host")
ELSE(CMAKE_SYSTEM_NAME MATCHES "Linux")
    set(SSE2_FOUND   true  CACHE BOOL "SSE2 available on host")
    set(SSE3_FOUND   false CACHE BOOL "SSE3 available on host")
    set(SSSE3_FOUND  false CACHE BOOL "SSSE3 available on host")
    set(SSE4_1_FOUND false CACHE BOOL "SSE4.1 available on host")
    set(SSE4_2_FOUND false CACHE BOOL "SSE4.2 available on host")
    set(AVX_FOUND false CACHE BOOL "AVX available on host")
    set(AVX2_FOUND false CACHE BOOL "AVX2 available on host")
ENDIF(CMAKE_SYSTEM_NAME MATCHES "Linux")

if(SSE2_FOUND)
    MESSAGE(STATUS "SSE2 Supported")
else()
    MESSAGE(STATUS "SSE2 Not Supported")
endif(SSE2_FOUND)

if(SSE3_FOUND)
    MESSAGE(STATUS "SSE3 Supported")
else()
    MESSAGE(STATUS "SSE3 Not Supported")
endif(SSE3_FOUND)

if(SSSE3_FOUND)
    MESSAGE(STATUS "SSSE3 Supported")
else()
    MESSAGE(STATUS "SSSE3 Not Supported")
endif(SSSE3_FOUND)

if(SSE4_1_FOUND)
    MESSAGE(STATUS "SSSE4.1 Supported")
else()
    MESSAGE(STATUS "SSSE4.1 Not Supported")
endif(SSE4_1_FOUND)

if(SSE4_2_FOUND)
    MESSAGE(STATUS "SSSE4.2 Supported")
else()
    MESSAGE(STATUS "SSSE4.2 Not Supported")
endif(SSE4_2_FOUND)

if(AVX_FOUND)
    MESSAGE(STATUS "AVX Supported")
else()
    MESSAGE(STATUS "AVX Not Supported")
endif(AVX_FOUND)

if(AVX2_FOUND)
    MESSAGE(STATUS "AVX2 Supported")
else()
    MESSAGE(STATUS "AVX2 Not Supported")
endif(AVX2_FOUND)

mark_as_advanced(SSE2_FOUND SSE3_FOUND SSSE3_FOUND SSE4_1_FOUND, SSE4_2_FOUND, AVX_FOUND, AVX2_FOUND)
