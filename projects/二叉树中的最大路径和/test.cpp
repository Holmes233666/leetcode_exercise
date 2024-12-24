#include<vector>
#include<iostream>

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
    int maxPathSum(TreeNode* root) {
        // 对于一棵子树而言，有两种情况：1.两棵子树连接起来的值 2. 只加上根，类似于最大子数组和；中间过程中保存最大值
        int maxNum = -INT_MAX;
        DFS(root, maxNum);
        return maxNum;
    }
    int DFS(TreeNode* root, int& maxNum) {
        // 返回的一定是左/右子树+根的最大值，整体的最大值由maxNum记录。
        if (root == nullptr) return 0;
        int left_root = DFS(root->left, maxNum);
        int right_root = DFS(root->right, maxNum);
        // 判断要不要加上子树高度
        if (left_root < 0) left_root = 0;
        if (right_root < 0) right_root = 0;
        // 修正后的值+根的值
        int connect = left_root + right_root + root->val;
        // 记录最大值：两种情况
        int tempMax = max(left_root+root->val, right_root+root->val);
        maxNum = max(maxNum, tempMax);
        maxNum = max(maxNum, connect);
        // 返回当前结点的+左/右子树的最大值
        if (max(left_root, right_root) > 0) {
            return max(left_root+root->val, right_root+root->val);
        }else{
            return root->val;
        }
    }
};

// 第二次刷
class Solution2 {
public:
    // 以一个结点往下的最大路径和的四种情况：左子树路径、右子树路径、左+根、右+根、左+右+根
    // 深搜，自底向上进行计算
    int maxPathSum(TreeNode* root) {
        int maxNum = -INT_MAX;
        getMaxSum(root, maxNum);
        return maxNum;
    }

    int getMaxSum(TreeNode* root, int& maxNum) {    // 递归时只需要递归计算左子树+根的值，以及右子树+根的值
        if (root ->left == nullptr && root->right == nullptr) {
            maxNum = max(root->val, maxNum);
            return root->val;
        }
        // 注意，在更新路径最大值时，只有该值非负才会可能使用
        int leftSum = max(getMaxSum(root->left, maxNum), 0);
        int rightSum = max(getMaxSum(root->right, maxNum), 0);
        int connect = leftSum + rightSum + root->val;
        maxNum = max(connect, maxNum);
        return root->val + max(leftSum, rightSum);
    }
};

// 第三次写笔记
class Solution3 {
public:
    // 以一个结点往下的最大路径和的四种情况：左子树路径、右子树路径、左+根、右+根、左+右+根
    // 深搜，自底向上进行计算
    int maxPathSum(TreeNode* root) {
        int maxNum = -INT_MAX;
        getMaxSum(root, maxNum);
        return maxNum;
    }

    int getMaxSum(TreeNode* root, int& maxNum) {    // 递归时只需要递归计算左子树+根的值，以及右子树+根的值
        if (!root) return 0;
        int leftMax = max(getMaxSum(root->left, maxNum), 0);
        int rightMax = max(getMaxSum(root->right, maxNum), 0);
        int connectSum = root->val + leftMax + rightMax;
        maxNum = max(maxNum, connectSum);
        return max(leftMax+root->val, rightMax+root->val);
    }
};