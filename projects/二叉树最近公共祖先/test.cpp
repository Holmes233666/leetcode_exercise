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

// 二刷
class Solution2 {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        return LCA(root, p, q);
    }

    TreeNode* LCA(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root == p || root == q || !root) return root;       // 自底向上传递当前结点的状态
        TreeNode* leftRes = LCA(root->left, p, q);
        TreeNode* rightRes = LCA(root->right, p, q);
        // 在左子树和右子树分别找到了需要的结点，那么这个结点就是最终的最近公共祖先
        if (leftRes != nullptr && rightRes != nullptr) return root;
        if (leftRes == nullptr) return rightRes;
        if (rightRes == nullptr) return leftRes;
        return nullptr;
    }
};