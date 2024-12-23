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
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        queue<TreeNode*> tq;
        vector<vector<int>> res;
        if (root) tq.push(root);
        int currNum = 1;
        int startIdx = 1;
        while (!tq.empty()) {
            int nextNum = 0;
            vector<int> temp;
            for (int i = 0; i < currNum; i++) {
                TreeNode* currNode = tq.front();
                temp.push_back(currNode->val);
                tq.pop();
                if (currNode->left) {
                    tq.push(currNode->left);
                    nextNum++;
                }
                if (currNode->right) {
                    tq.push(currNode->right);
                    nextNum++;
                }
            }
            if (startIdx == -1) {
                reverse(temp.begin(), temp.end());
            }
            startIdx *= -1;
            res.push_back(temp);
            currNum = nextNum;
        }
        return res;
    }
};