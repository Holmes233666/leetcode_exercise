cmake_minimum_required(VERSION 3.28)
project(projects)

set(CMAKE_CXX_STANDARD 11)

add_executable(projects main.cpp)

add_executable(maxcontiseq 最长连续序列/maxcontiseq.cpp
        最大子数组和/test.cpp
        合并区间/test.cpp)
add_executable(test 最小覆盖子串/test.cpp)