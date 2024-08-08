#include<iostream>
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

// 错误解法：中序是否相同没法判断是否是轴对称的二叉树，见示例2
class Solution {
public:
    bool isSymmetric(TreeNode* root) {
        // 左中右和右中左遍历结果是否相同来判断
        vector<int> vecLeft, vecRight;
        return vecLeft == vecRight;
    }

    void leftTravel(TreeNode* root, vector<int>& vecLeft) {
        if (root != nullptr) {
            leftTravel(root->left, vecLeft);
            vecLeft.push_back(root->val);
            leftTravel(root->right, vecLeft);
        }else {
            vecLeft.push_back(-101);
        }
    }

    void rightTravel(TreeNode* root, vector<int>& vecRight) {
        if (root != nullptr) {
            leftTravel(root->left, vecRight);
            vecRight.push_back(root->val);
            leftTravel(root->right, vecRight);
        }else {
            vecRight.push_back(-102);
        }
    }
};

// 方法：递归写法
class Solution2 {
public:
    bool isSymmetric(TreeNode* root) {
        if (root == nullptr) return true;
        return ifSym(root->left, root->right);
    }

    bool ifSym(TreeNode* root1, TreeNode* root2) {
        if ((root1 == nullptr && root2 != nullptr) || (root2 == nullptr && root1 != nullptr)) {
            return false;
        }else if (root1 == nullptr && root2 == nullptr) {
            return true;
        }else {
            return ifSym(root1->left, root2->right) && ifSym(root1->right, root2->left) && (root1->val == root2->val);
        }
    }
};

// 方法2： 先拷贝一棵二叉树，然后对他进行翻转二叉树，进而判断两棵树是否相同
class Solution3 {
public:
    bool isSymmetric(TreeNode* root) {

    }

    // 先拷贝一棵树
    TreeNode* copyTree(TreeNode* root) {
        if (root != nullptr) {
            TreeNode *newRoot = new TreeNode(root->val);
            newRoot->left = copyTree(root->left);
            newRoot->right = copyTree(root->right);
            return newRoot;
        }
    }

    // 翻转二叉树
    void converTree(TreeNode* root) {
        if (root != nullptr) {
            // 分别对两个子树进行翻转
            converTree(root->left);
            converTree(root->right);
            // 然后从根节点交换两个子树
            TreeNode* temp = root->left;
            root->left = root->right;
            root->right = temp;
        }
    }

    // 判断两棵树是否相同：
    bool isSame(TreeNode *root1, TreeNode *root2) {
        if ((root1 == nullptr && root2 != nullptr) || (root2 == nullptr && root1 != nullptr)) return false;
        if (root1 == nullptr && root2 == nullptr) return true;
        if (root1 != nullptr && root2 != nullptr) {
            return isSame(root1->left, root2->left) && isSame(root1->right, root2->right);
        }
    }
};