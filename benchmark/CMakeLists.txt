cmake_minimum_required(VERSION 3.27)

project("dojo-1_benchmark" LANGUAGES CXX)

add_compile_definitions(BUILD_BENCHMARK)

set(TARGET "dojo-1_benchmark")

set(SOURCES task_1_benchmark.cxx
        task_2_benchmark.cxx
        task_3_benchmark.cxx
)

add_executable(${TARGET} ${SOURCES})

set(LIBS benchmark::benchmark_main dojo_1_lib)

target_link_libraries(${TARGET} ${LIBS})


install(TARGETS ${TARGET} RUNTIME)
