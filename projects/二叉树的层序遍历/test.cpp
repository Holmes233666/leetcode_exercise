#include<iostream>
#include<vector>
#include<queue>

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
    vector<vector<int>> levelOrder(TreeNode* root) {
        queue<pair<TreeNode*, int>> treeq;
        int currDepth = 0;
        treeq.emplace(root, 0);
        vector<vector<int>> res;
        vector<int> currRes;
        while(!treeq.empty()) {
            auto [t, depth] = treeq.front();
            if (currDepth == depth) {
                currRes.push_back(t->val);
            }else {
                currDepth++;
                res.push_back(currRes);
                currRes.clear();
                currRes.push_back(t->val);
            }
            treeq.pop();
            if (t->left != nullptr) treeq.emplace(t->left, depth+1);
            if (t->right != nullptr) treeq.emplace(t->right, depth+1);
        }
        return res;
    }
};
