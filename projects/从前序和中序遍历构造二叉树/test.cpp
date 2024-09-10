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
    unordered_map<int, int> ump;
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        if (preorder.size() == 0) return nullptr;
        TreeNode* root = new TreeNode(preorder[0]);
        // 将所有中序的元素放入哈希表: 值：下标
        for (int i = 0; i < inorder.size(); i++) {
            ump.emplace(inorder[i], i);
        }
        // 首先找到中序元素在Inorder中的位置
        int rootIndex = ump[preorder[0]];
        // 分别构造左子树和右子树
        createBasedInorder(preorder, inorder, root->left, 0, rootIndex-1, 1);
        createBasedInorder(preorder, inorder, root->right, rootIndex+1, inorder.size()-1,
            inorder.size()-rootIndex);
        return root;
    }

    // 基于中序，然后查询前序去构造二叉树
    void createBasedInorder(vector<int>& preorder, vector<int>& inorder, TreeNode* &newNode,
        int startInorder, int endInorder, int startPre) {
        // 如果end >= start，那么递归继续，否则递归终止
        if (endInorder >= startInorder) {
            // 先根据前序找到root结点的值和位置
            int rootVal = preorder[startPre];
            int rootIndex = ump[rootVal];
            int leftLength = rootIndex-startInorder;
            newNode = new TreeNode(rootVal);
            // 然后构造左右子树
            createBasedInorder(preorder, inorder, newNode->left, startInorder, rootIndex-1,
                startPre+1);
            createBasedInorder(preorder, inorder, newNode->right, rootIndex+1, endInorder,
                startPre+leftLength);
        }
    }
};


// 精简版
class Solution2 {
public:
    unordered_map<int, int> ump;
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        if (preorder.size() == 0) return nullptr;
        TreeNode* rootFather = new TreeNode(-1);
        // 将所有中序的元素放入哈希表: 值：下标
        for (int i = 0; i < inorder.size(); i++) {
            ump.emplace(inorder[i], i);
        }
        createBasedInorder(preorder, inorder, rootFather->left, 0, inorder.size()-1, 0);
        return rootFather->left;
    }

    // 基于中序，然后查询前序去构造二叉树
    void createBasedInorder(vector<int>& preorder, vector<int>& inorder, TreeNode* &newNode,
        int startInorder, int endInorder, int startPre) {
        // 如果end >= start，那么递归继续，否则递归终止
        if (endInorder >= startInorder) {
            // 先根据前序找到root结点的值和位置
            int rootVal = preorder[startPre];
            int rootIndex = ump[rootVal];
            int leftLength = rootIndex-startInorder;
            newNode = new TreeNode(rootVal);
            // 然后构造左右子树
            createBasedInorder(preorder, inorder, newNode->left, startInorder, rootIndex-1,
                startPre+1);
            createBasedInorder(preorder, inorder, newNode->right, rootIndex+1, endInorder,
                startPre+leftLength+1);
        }
    }
};