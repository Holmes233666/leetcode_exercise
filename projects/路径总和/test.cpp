#include<vector>
#include<unordered_map>
#include<stack>


using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// 对于数组的前缀和，需要一个ump记录该和出现的次数即可
class Solution {
public:
    unordered_map<long, int> ump;
    int pathSum(TreeNode* root, int targetSum) {
        if (!root) return 0;
        // long表示和，int表示有该和的路径的个数
        ump[0] = 1;
        int res = 0;
        long tempSum = 0;
        DFS(root, targetSum, tempSum, res);
        return res;

    }

    void DFS(TreeNode* root, long target, long& tempSum, int& res) {
        if (root != nullptr) {
            tempSum += root->val;
            // umap中有该值
            if (ump.find(tempSum-target) != ump.end()) {
                res += ump[tempSum-target];
            }
            ump[tempSum]++;
            // 分别对左右节点进行深搜
            // 左节点进行深搜
            DFS(root->left, target, tempSum, res);
            // 深搜结束，从umap中去掉tempSum-root->val的值的频次
            if (root->left != nullptr) {
                ump[tempSum]--;
                tempSum -= root->left->val;
            }
            // 右节点进行深搜
            DFS(root->right, target, tempSum, res);
            if (root->right != nullptr) {
                ump[tempSum]--;
                tempSum -= root->right->val;
            }
        }
    }
};