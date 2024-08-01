cmake_minimum_required(VERSION 3.28)
project(projects)

set(CMAKE_CXX_STANDARD 11)

add_executable(projects main.cpp)

add_executable(maxcontiseq 最长连续序列/maxcontiseq.cpp
        最大子数组和/test.cpp
        合并区间/test.cpp
        轮转数组/test.cpp
        除自身以外数组的乘积/test.cpp
        缺失的第一个正数/test.cpp
        矩阵置零/test.cpp
        螺旋矩阵/test.cpp
        搜索二维矩阵/test.cpp
        旋转图像/test.cpp
        相交链表/test.cpp
        反转链表/test.cpp
        回文链表/test.cpp
        环形链表/test.cpp
        环形链表II/test.cpp
        合并两个有序链表/test.cpp)
add_executable(test 螺旋矩阵/test.cpp)
