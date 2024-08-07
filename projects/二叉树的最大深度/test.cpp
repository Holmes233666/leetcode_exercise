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

// 这个写法有点像记录深度：
class Solution {
public:
    int maxDepth(TreeNode* root) {
        if (root == nullptr) return 0;
        int height = 1;
        return getHeight(root, height);
    }

    int getHeight(TreeNode *root, int height) {
        int height_left = height, height_right = height;
        if (root->left != nullptr) {
            height_left = getHeight(root->left, height+1);
        }
        if (root->right != nullptr) {
            height_right = getHeight(root->right, height+1);
        }
        return max(height_left, height_right);
    }
};

// 换个写法：记录左子树高度，记录右子树高度，然后自己高度=max+1
class Solution2 {
public:
    int maxDepth(TreeNode* root) {
        if (root != nullptr) {
            int height_left = maxDepth(root->left) + 1;
            int height_right = maxDepth(root->right) + 1;
            return max(height_left, height_right);
        }else {
            return 0;
        }
    }
};
