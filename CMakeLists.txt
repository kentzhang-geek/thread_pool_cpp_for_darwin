cmake_minimum_required(VERSION 2.0)
set(CMAKE_BUILD_TYPE "Debug")

set(SRC test.cpp test2.cpp)

link_libraries(m pthread)
add_executable(test main.cpp ${SRC})

add_executable(ut ut.cc ${SRC})
include_directories(.)
find_library(GTEST libgtest.a .)
target_link_libraries(ut ${GTEST})