#include<vector>
#include<unordered_map>

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
    unordered_map<int, int> umap;
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        int start = 0, end = inorder.size()-1, postEnd = end;
        for (int i = 0; i <= end; i++) {
            umap[inorder[i]] = i;
        }
        TreeNode *root;
        createTreeRecur(inorder, postorder, start, end, postEnd, root);
        return root;
    }

    void createTreeRecur(vector<int>& inorder, vector<int>& postorder, int start, int end, int postEnd, TreeNode* &root) {
        if (start <= end) {
            int rootVal = inorder[postEnd];
            int inordIdx = umap[rootVal];   // 在中序遍历中的下标
            int rightNum = end - inordIdx;  // 右子树的节点数量
            root = new TreeNode(rootVal);
            createTreeRecur(inorder, postorder, start, inordIdx-1, postEnd - rightNum - 1, root->left);
            createTreeRecur(inorder, postorder, inordIdx+1, end, postEnd-1, root->right);
        }
    }
};