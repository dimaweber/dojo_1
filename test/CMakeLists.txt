cmake_minimum_required(VERSION 3.27)

project("dojo-1_test" LANGUAGES CXX)

add_compile_definitions(BUILD_TESTS)
enable_testing()

set(TARGET "dojo-1_test")

set(SOURCES unittest.cpp)

include_directories(../include
                    SYSTEM ${GTEST_INCLUDE_DIRS}
)

add_executable(${TARGET} ${SOURCES})

set(LIBS GTest::gtest_main)

target_link_libraries(${TARGET} ${LIBS})

include(GoogleTest)
gtest_discover_tests(${TARGET})

install(TARGETS ${TARGET} RUNTIME)
