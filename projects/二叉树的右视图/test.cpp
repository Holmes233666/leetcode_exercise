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

// 基本思路：层序遍历，最右边的结点即一层结束的结点class Solution {
class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        if (root == nullptr) return {};
        queue<pair<TreeNode*, int>> q;
        vector<int> res;
        int currDepth = 0, lastDepth=0;
        int currValue, lastVal = -INT_MAX;
        q.emplace(root, currDepth);
        while (!q.empty()) {
            auto [t, currDepth] = q.front();
            q.pop();
            currValue = t->val;
            if (t->left != nullptr) q.emplace(t->left, currDepth+1);
            if (t->right != nullptr) q.emplace(t->right, currDepth+1);
            if (currDepth != lastDepth) {
                res.push_back(lastVal);
                lastDepth = currDepth;
            }
            lastVal = currValue;
        }
        res.push_back(lastVal);
        return res;
    }
};

// 二刷：基于层序遍历
class Solution2 {
public:
    vector<int> rightSideView(TreeNode* root) {
        queue<TreeNode*> nodes_q;
        vector<int> res;
        if (root) nodes_q.emplace(root);
        int nodesLevel = 1;
        while (!nodes_q.empty()) {
            int nextLevelNodes = 0;
            for (int i = 0; i < nodesLevel; i++) {
                TreeNode* currNode = nodes_q.front();
                nodes_q.pop();
                if (currNode->left != nullptr) {
                    nodes_q.emplace(currNode->left);
                    nextLevelNodes++;
                }
                if (currNode->right != nullptr) {
                    nodes_q.emplace(currNode->right);
                    nextLevelNodes++;
                }
                if (i == nodesLevel-1) res.push_back(currNode->val);
            }
            nodesLevel = nextLevelNodes;
        }
        return res;
    }
};
