#include<vector>
#include<queue>

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
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        return DFS(root, p, q);
    }

    TreeNode* DFS(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root == nullptr || root == p || root == q) return root;
        TreeNode* leftNode = DFS(root->left, p, q);
        TreeNode* rightNode = DFS(root->right, p, q);
        if (leftNode == nullptr) return rightNode;
        if (rightNode == nullptr) return leftNode;
        return root;
    }
};