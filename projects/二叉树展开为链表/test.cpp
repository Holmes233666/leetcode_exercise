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
    void flatten(TreeNode* root) {
        if (root == nullptr) return;
        vector<TreeNode*> res;
        preTravel(root, res);
        TreeNode* pre = res[0];
        for (int i = 1; i < res.size(); i++) {
            TreeNode* curr = res[i];
            pre->left = nullptr;
            pre->right = curr;
            pre = curr;
        }
    }

    void preTravel(TreeNode* root, vector<TreeNode*> &res) {
        if (root != nullptr) {
            res.push_back(root);
            preTravel(root->left, res);
            preTravel(root->right, res);
        }
    }
};

class Solution2 {
public:
    void flatten(TreeNode* root) {
        if (root == nullptr) return;
        TreeNode* currNode = root;
        while (currNode != nullptr) {
            // 当当前结点的左子树不为空时：
            if (currNode->left != nullptr) {
                // 找到当前节点的左子树的最右节点
                TreeNode* pre = findMostRight(currNode->left);
                pre->right = currNode->right;
                currNode->right = currNode->left;
                currNode->left = nullptr;
            }else {
                currNode = currNode->right;
            }
        }
    }

    TreeNode* findMostRight(TreeNode* root) {
        // 递归寻找
        if (root->right != nullptr) {
            return findMostRight(root->right);
        }
        if (root->left != nullptr) {
            return findMostRight(root->left);
        }
        // 叶子结点
        return root;
    }
};