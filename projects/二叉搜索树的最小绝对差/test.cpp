#include<iostream>

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
    int getMinimumDifference(TreeNode* root) {
        vector<int> nums;
        inorderTravel(root, nums);
        int minNum = nums[1] - nums[0];
        for (int i = 2; i < nums.size(); i++) {
            minNum = min(minNum, nums[i]-nums[i-1]);
        }
        return minNum;
    }

    void inorderTravel(TreeNode* root, vector<int>& nums) {
        if (root) {
            inorderTravel(root->left, nums);
            nums.push_back(root->val);
            inorderTravel(root->right, nums);
        }
    }
};
