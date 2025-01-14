#include<vector>

using namespace std;

class Node {
public:
    bool val;
    bool isLeaf;
    Node* topLeft;
    Node* topRight;
    Node* bottomLeft;
    Node* bottomRight;

    Node() {
        val = false;
        isLeaf = false;
        topLeft = NULL;
        topRight = NULL;
        bottomLeft = NULL;
        bottomRight = NULL;
    }

    Node(bool _val, bool _isLeaf) {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = NULL;
        topRight = NULL;
        bottomLeft = NULL;
        bottomRight = NULL;
    }

    Node(bool _val, bool _isLeaf, Node* _topLeft, Node* _topRight, Node* _bottomLeft, Node* _bottomRight) {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = _topLeft;
        topRight = _topRight;
        bottomLeft = _bottomLeft;
        bottomRight = _bottomRight;
    }
};

// 暴力递归
class Solution {
public:
    Node* construct(vector<vector<int>>& grid) {
        int n = grid.size();
        Node* currNode;
        createTree(0, n-1, 0, n-1, grid, currNode);
        return currNode;
    }

    void createTree(int startI, int endI, int startJ, int endJ, vector<vector<int>>& grid, Node* &currNode) {
        if (startI <= endI && startJ <= endJ) {
            currNode = new Node(false, false);
            if (!judge(startI, endI, startJ, endJ, grid)) { // 不是叶子结点，需要继续递归
                createTree(startI, (startI+endI)/2, startJ, (startJ+endJ)/2, grid, currNode->topLeft);
                createTree(startI, (startI + endI)/2, (startJ+endJ)/2+1, endJ, grid, currNode->topRight);
                createTree((startI+endI)/2+1, endI, startJ, (startJ+endJ)/2, grid, currNode->bottomLeft);
                createTree((startI+endI)/2+1, endI, (startJ+endJ)/2+1, endJ, grid, currNode->bottomRight);
            }else { // 是叶子结点
                currNode->val = grid[startI][startJ];
                currNode->isLeaf = true;
            }
        }else {
            currNode = nullptr;
        }
    }

    bool judge(int startI, int endI, int startJ, int endJ, vector<vector<int>>& grid) {
        int cmp = grid[startI][startJ];
        for (int i = startI; i <= endI ; i++) {
            for (int j = startJ; j <= endJ; j++) {
                if (grid[i][j] != cmp) return false;    // 是不是叶子结点，需要继续递归
            }
        }
        return true;    // 是叶子结点
    }
};

// 前缀和优化
class Solution2 {
public:
    vector<vector<int>> pre;
    Node* construct(vector<vector<int>>& grid) {
        int n = grid.size();
        Node* currNode;
        pre = vector<vector<int>>(n+1, vector<int>(n+1, 0));   // n+1是为了方便i==0和j==0的检查函数
        // 进行pre数组计算
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                pre[i][j] = pre[i][j-1] + pre[i-1][j] - pre[i-1][j-1] + grid[i-1][j-1];
            }
        }
        createTree(0, n-1, 0, n-1, grid, currNode);
        return currNode;
    }

    void createTree(int startI, int endI, int startJ, int endJ, vector<vector<int>>& grid, Node* &currNode) {
        if (startI <= endI && startJ <= endJ) {
            currNode = new Node(false, false);
            int prefixNum = pre[endI + 1][endJ + 1] - pre[endI + 1][startJ] - pre[startI][endJ+1] + pre[startI][startJ];
            int square = (endI - startI + 1) * (endJ - startJ + 1);
            if (prefixNum != square && prefixNum != 0) { // 不是叶子结点，需要继续递归
                createTree(startI, (startI+endI)/2, startJ, (startJ+endJ)/2, grid, currNode->topLeft);
                createTree(startI, (startI + endI)/2, (startJ+endJ)/2+1, endJ, grid, currNode->topRight);
                createTree((startI+endI)/2+1, endI, startJ, (startJ+endJ)/2, grid, currNode->bottomLeft);
                createTree((startI+endI)/2+1, endI, (startJ+endJ)/2+1, endJ, grid, currNode->bottomRight);
            }else { // 是叶子结点
                currNode->val = grid[startI][startJ];
                currNode->isLeaf = true;
            }
        }else {
            currNode = nullptr;
        }
    }
};
