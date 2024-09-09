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
    bool isValidBST(TreeNode* root) {
        vector<int> nums;
        midTravel(root, nums);
        if (nums.size() == 0) return true;
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] <= nums[i-1]) return false;
        }
        return true;
    }

    void midTravel(TreeNode* root, vector<int>& vec) {
        if (root != nullptr) {
            midTravel(root->left, vec);
            vec.push_back(root->val);
            midTravel(root->right, vec);
        }
    }
};
