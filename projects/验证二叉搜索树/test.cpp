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

// 法1：中序遍历后验证
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


// 法2：自上而下判断
class Solution2 {
public:
    bool isValidBST(TreeNode* root) {
        long maxNum = INT_MAX+1, minNum = -INT_MAX-1;
        return check(root, maxNum, minNum);
    }

    bool check(TreeNode* root, long maxNum, long minNum) {
        if (root != nullptr) {
            if (maxNum < root->val || minNum > root->val) return false;
            return check(root->left, root->val, minNum) && check(root->right, maxNum, root->val);
        }
    }
};


