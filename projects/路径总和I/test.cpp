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

class Solution {
public:
    bool hasPathSum(TreeNode* root, int targetSum) {
        int currSum = 0;
        return DFS(root, targetSum, currSum);
    }

    bool DFS(TreeNode* root, int target, int currSum) {
        if (root != nullptr) {
            currSum += root->val;
            if (currSum == target && root->left == nullptr && root->right == nullptr) return true;
            return DFS(root->left, target, currSum) || DFS(root->right, target, currSum);
        }
        return false;
    }
};


