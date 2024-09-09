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
    int kthSmallest(TreeNode* root, int k) {
        vector<int> vec;
        midTravel(root, vec, k);
        return vec[k-1];
    }

    void midTravel(TreeNode* root, vector<int>& res, int k) {
        if (root != nullptr) {
            midTravel(root->left, res, k);
            res.push_back(root->val);
            if (res.size() == k) return;
            midTravel(root->right, res, k);
        }
    }
};
