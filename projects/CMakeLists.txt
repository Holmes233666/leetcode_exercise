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
        合并两个有序链表/test.cpp
        两数相加/test.cpp
        删除链表的倒数第N个节点/test.cpp
        两两交换链表中的结点/test.cpp
        K个一组翻转链表/test.cpp
        随机链表的复制/test.cpp
        排序链表/test.cpp
        合并k个升序链表/test.cpp
        LRU缓存/LRU.cpp
        二叉树的中序遍历/test.cpp
        二叉树的最大深度/test.cpp
        翻转二叉树/test.cpp
        对称二叉树/test.cpp
        二叉树的直径/test.cpp
        二叉树的层序遍历/test.cpp
        将有序数组转换为二叉搜索树/test.cpp
        验证二叉搜索树/test.cpp
        二叉搜索树中第K小的元素/test.cpp
        二叉树的右视图/test.cpp
        二叉树展开为链表/test.cpp
)
add_executable(test 两两交换链表中的结点/test.cpp)
