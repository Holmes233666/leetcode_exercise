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
        // if (root == nullptr) return;
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

// 第二次刷：寻找前驱结点
class Solution3 {
public:
    void flatten(TreeNode* root) {
        TreeNode* currNode = root;
        while (currNode != nullptr) {
            if (currNode->left != nullptr) {    // 如果左子树不为空
                TreeNode* left_pre = findPre(currNode->left);
                left_pre->right = currNode->right;
                currNode->right = currNode->left;
                currNode->left = nullptr;
            }   // 如果左子树是空指针，直接进入下一个节点
            currNode = currNode->right;
        }
    }

    TreeNode* findPre(TreeNode* root) { // 由主函数flatten输入的root一定不是空指针
        if (root->right != nullptr) {
            return findPre(root->right);
        }
        if (root->left != nullptr){ // 右子树为空，那么从左子树找
            return findPre(root->left);
        }
        return root;
    }
};
