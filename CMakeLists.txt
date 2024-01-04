cmake_minimum_required(VERSION 3.27)
project(dojo_1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_program(CCACHE_FOUND ccache)
if (CCACHE_FOUND)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
endif (CCACHE_FOUND)

option(TIDY_CHECKS "Run clang-tidy for static analyze" OFF)
if (TIDY_CHECKS)
    set(CMAKE_CXX_CLANG_TIDY clang-tidy -config-file=${CMAKE_CURRENT_LIST_DIR}/.clang-tidy;
    )
endif ()

add_subdirectory(external/fmt EXCLUDE_FROM_ALL SYSTEM)
#find_package(fmt)

set(SPDLOG_FMT_EXTERNAL ON CACHE BOOL "blah")
add_subdirectory(external/spdlog EXCLUDE_FROM_ALL SYSTEM)
#find_package(spdlog)

include_directories(include)

option(BUILD_TESTS "Build unittests" OFF)
if (BUILD_TESTS)
    add_compile_definitions(BUILD_TESTS)
    add_subdirectory(external/googletest EXCLUDE_FROM_ALL SYSTEM)
    enable_testing()
    add_subdirectory(test)
endif ()

option(BUILD_BENCHMARK "Build benchmark" OFF)
if (BUILD_BENCHMARK)
    add_compile_definitions(BUILD_BENCHMARK)
    set(BENCHMARK_ENABLE_GTEST_TESTS OFF CACHE BOOL "blah")
    add_subdirectory(external/benchmark EXCLUDE_FROM_ALL SYSTEM)
    add_subdirectory(benchmark)
endif ()

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(DEBUG=1)
else ()
    add_compile_definitions(DEBUG=0)
    add_compile_options(-O3)
endif ()

#set(BOOST_ROOT ../boost_1_82_0)
#find_package(Boost 1.82.0)
#include_directories(${Boost_INCLUDE_DIR})

add_subdirectory(src)