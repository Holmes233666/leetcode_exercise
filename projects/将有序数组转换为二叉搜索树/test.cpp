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
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        TreeNode* root = nullptr;
        int start = 0, end = nums.size()-1;
        createBST(root, start, end, nums);
    }

    void createBST(TreeNode* &root, int start, int end, vector<int>& nums) {
        if (start <= end) {
            int mid = (start + end) / 2;
            TreeNode* newNode = new TreeNode(nums[mid]);
            root = newNode;
            createBST(root->left, start, mid, nums);
            createBST(root->right, mid+1, end, nums);
        }
    }
};