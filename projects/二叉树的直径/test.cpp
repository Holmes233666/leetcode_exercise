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

class Solution {
public:
    int diameterOfBinaryTree(TreeNode* root) {
        int maxDepth = 0;
        return getAllNodesHeights(root, maxDepth);
    }

    int getAllNodesHeights(TreeNode* root, int maxDepth) {
        // 遍历每一个节点，记录他们的最大长度
        if (root != nullptr) {
            // 假设过root节点：
            int maxDepthofRoot = calculateDepth(root->left, maxDepth) + calculateDepth(root->right, maxDepth);
            // 假设不过root节点：
            int maxDepthofLeft = diameterOfBinaryTree(root->left);
            int maxDepthofRight = diameterOfBinaryTree(root->right);
            // 返回三者中最大的
            int max_val = (maxDepthofRoot > maxDepthofLeft ? (maxDepthofRoot > maxDepthofRight ? maxDepthofRoot : maxDepthofRight) : (maxDepthofLeft > maxDepthofRight ? maxDepthofLeft : maxDepthofRight));
            return max(maxDepth-1, max_val-1);
        }
        return maxDepth;
    }

    int calculateDepth(TreeNode* root, int depth) {
        // 计算一棵树的深度
        if (root != nullptr) {
            int leftHeight =  calculateDepth(root->left, depth+1);
            int rightHeight = calculateDepth(root->right, depth+1);
            return max(leftHeight, rightHeight);
        }
        return depth;
    }
};