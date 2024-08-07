#include<iostream>
#include<vector>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// 中序是否相同没法判断是否是轴对称的二叉树，见示例2
class Solution {
public:
    bool isSymmetric(TreeNode* root) {
        // 左中右和右中左遍历结果是否相同来判断
        vector<int> vecLeft, vecRight;
        return vecLeft == vecRight;
    }

    void leftTravel(TreeNode* root, vector<int>& vecLeft) {
        if (root != nullptr) {
            leftTravel(root->left, vecLeft);
            vecLeft.push_back(root->val);
            leftTravel(root->right, vecLeft);
        }else {
            vecLeft.push_back(-101);
        }
    }

    void rightTravel(TreeNode* root, vector<int>& vecRight) {
        if (root != nullptr) {
            leftTravel(root->left, vecRight);
            vecRight.push_back(root->val);
            leftTravel(root->right, vecRight);
        }else {
            vecRight.push_back(-102);
        }
    }
};

// 方法：先翻转，再判断两棵树是不是同一棵树
class Solution2 {
public:
    bool isSymmetric(TreeNode* root) {
        // 左中右和右中左遍历结果是否相同来判断
        vector<int> vecLeft, vecRight;
        return vecLeft == vecRight;
    }

    // 先翻转二叉树

};

// 先拷贝一棵二叉树，然后对他进行翻转二叉树，进而判断两棵树是否相同
class Solution3 {
public:
    bool isSymmetric(TreeNode* root) {
        // 左中右和右中左遍历结果是否相同来判断
        vector<int> vecLeft, vecRight;
        return vecLeft == vecRight;
    }

    // 先翻转二叉树

};