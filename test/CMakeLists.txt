cmake_minimum_required(VERSION 3.27)

project("dojo-1_test" LANGUAGES CXX)

set(TARGET "dojo-1_test")

set(SOURCES task_1_unittest.cxx
        task_2_unittest.cxx
        task_3_unittest.cxx
        task_4_unittest.cpp
)

#include_directories(SYSTEM ${GTEST_INCLUDE_DIRS})

add_executable(${TARGET} ${SOURCES})

set(LIBS GTest::gtest_main dojo_1_lib)

target_link_libraries(${TARGET} ${LIBS})
target_link_libraries(${TARGET} spdlog::spdlog)

include(GoogleTest)
gtest_discover_tests(${TARGET})

install(TARGETS ${TARGET} RUNTIME)
