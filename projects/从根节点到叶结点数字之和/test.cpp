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

// 法1：深度优先搜索
class Solution {
public:
    int sumNumbers(TreeNode* root) {
        int curr = 0, asw = 0;
        dfs(root, curr, asw);
        return asw;
    }

    void dfs(TreeNode* root, int curr, int& asw) {
        if (root != nullptr) {
            curr = curr * 10 + root->val;
            // 如果左右子树都是空，那么值可以返回了
            if (root->left == nullptr && root->right == nullptr) {
                asw += curr;
            }else{  // 只要有一个子树不空，那么分别对左子树和右子树进行深搜
                dfs(root->left, curr, asw);
                dfs(root->right, curr, asw);
            }
        }
    }
};


