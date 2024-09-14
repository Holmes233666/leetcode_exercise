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