#include <valarray>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// 法1：遍历，没有利用完全二叉树的特点
class Solution {
public:
    int countNodes(TreeNode* root) {
        int nodeNum = 0;
        inorderTravel(root, nodeNum);
        return nodeNum;
    }

    void inorderTravel(TreeNode* root, int& currNum) {
        if (root != nullptr) {
            inorderTravel(root->left, currNum);
            currNum++;
            inorderTravel(root->right, currNum);
        }
    }
};

// 二分查找 + 位运算
class Solution2 {
public:
    int countNodes(TreeNode* root) {
        int h = 0;
        // 首先深搜确定层数
        DFS(root, h);
        // 根据h进行结点数的确定
        int minNum = pow(2, h) , maxNum = pow(2, h+1) - 1;
        int start = 0, end = maxNum - minNum;
        return binarySearch(start, end, root, minNum);
    }

    void DFS(TreeNode* root, int& h) {
        if (root != nullptr) {
            h++;
            DFS(root->left, h);
        }
    }

    bool binarySearch(int start, int end, TreeNode* root, int minNum) {
        if (start <= end) {
            int mid = (start + end) / 2;
            int num = minNum + mid;
            num = num << 1;

        }
    }

    bool checkExist(int num) {
        if (num != 0) {

        }
    }
};