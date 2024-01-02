cmake_minimum_required(VERSION 3.27)
project(dojo_1)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(external/fmt)
#find_package(fmt)

#set (SPDLOG_FMT_EXTERNAL ON)
add_subdirectory(external/spdlog)
#find_package(spdlog)

include_directories(include)

option(BUILD_TESTS "Build unittests" OFF)
if (BUILD_TESTS)
    add_compile_definitions(BUILD_TESTS)
    add_subdirectory(external/googletest)
    enable_testing()
    add_subdirectory(test)
endif ()

option(BUILD_BENCHMARK "Build benchmark" OFF)
if (BUILD_BENCHMARK)
    add_compile_definitions(BUILD_BENCHMARK)
    set(BENCHMARK_ENABLE_GTEST_TESTS OFF)
    add_subdirectory(external/benchmark)
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