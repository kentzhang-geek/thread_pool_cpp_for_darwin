cmake_minimum_required(VERSION 2.0)

set(SRC main.cpp test.cpp test2.cpp)

link_libraries(m pthread)
add_executable(test ${SRC})

add_executable(ut ut.cc ${SRC})
find_library(GTEST libgtest.a .)
target_link_libraries(ut ${GTEST})