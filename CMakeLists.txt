cmake_minimum_required(VERSION 3.27)
project(dojo_1)

set(CMAKE_CXX_STANDARD 20)

set(TARGET dojo_1)
set(SOURCES src/task_1.cxx)

set(INCLUDES include/task_1.hxx)


add_subdirectory(external/fmt)
#find_package(fmt)

set (SPDLOG_FMT_EXTERNAL ON)
add_subdirectory(external/spdlog)
#find_package(spdlog)

include_directories( include )

option(BUILD_TESTS "Build unittests" OFF)
if (BUILD_TESTS)
    add_subdirectory(external/googletest )
    add_subdirectory(test)
endif ()

option(BUILD_BENCHMARK "Build benchmark" OFF)
if (BUILD_BENCHMARK)
    set(BENCHMARK_ENABLE_GTEST_TESTS OFF )
    add_subdirectory(external/benchmark )
    add_subdirectory(benchmark)
endif ()

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(DEBUG=1)
else()
    add_compile_definitions(DEBUG=0)
endif ()

add_executable(${TARGET} ${SOURCES} ${INCLUDES})
target_link_libraries(${TARGET} fmt::fmt)
target_link_libraries(${TARGET}  spdlog::spdlog )

install(TARGETS ${TARGET} RUNTIME)

