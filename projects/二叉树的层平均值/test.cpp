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
    vector<double> averageOfLevels(TreeNode* root) {
        vector<double> res;
        queue<TreeNode*> tq;
        if (root) tq.push(root);
        int currNum = 1;
        while (!tq.empty()) {
            int nextNum = 0;
            double sum = 0;
            for (int i = 0; i < currNum; i++) {
                TreeNode* currNode = tq.front();
                sum += currNode->val;
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
            res.push_back(sum/(currNum * 1.0));
            currNum = nextNum;
        }
        return res;
    }
};
