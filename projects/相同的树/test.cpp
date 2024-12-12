

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
    bool isSameTree(TreeNode* p, TreeNode* q) {
        return preTravel(p, q);
    }

    bool preTravel(TreeNode *p, TreeNode *q) {
        if (p != nullptr && q != nullptr) {
            if (p->val != q->val) return false;
            bool ifleft = preTravel(p->left, q->left);
            bool ifright = preTravel(p->right, q->right);
            return ifleft & ifright;
        }
        if (p == nullptr && q == nullptr) return true;
        return false;
    }
};