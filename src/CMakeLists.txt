cmake_minimum_required(VERSION 3.27)
project(task_1)

set(TARGET dojo_1)
set(TARGET_LIB dojo_1_lib)

set(SOURCES main.cxx)
set(SOURCES_LIB task_1.cxx
        task_2.cxx
        task_3.cxx
)

add_library(${TARGET_LIB} STATIC ${SOURCES_LIB})
add_executable(${TARGET} ${SOURCES} ${INCLUDES})

target_link_libraries(${TARGET} fmt::fmt)
target_link_libraries(${TARGET} spdlog::spdlog)
target_link_libraries(${TARGET_LIB} fmt::fmt)
target_link_libraries(${TARGET_LIB} spdlog::spdlog)
target_link_libraries(${TARGET} ${TARGET_LIB})

install(TARGETS ${TARGET} RUNTIME)
install(TARGETS ${TARGET_LIB} LIBRARY)

