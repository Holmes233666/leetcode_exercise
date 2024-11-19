#include<vector>

using namespace std;

// 原地算法解决
class Solution {
public:
    void gameOfLife(vector<vector<int>>& board) {
        int n = board.size(), m = board[0].size();
        vector<vector<int>> dir = {{-1,-1}, {-1,0}, {-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};
        // 用2表示死细胞变活，用-2表示活细胞变死
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                int currCeil = board[i][j];
                int aroundLive = 0, aroundDead = 0;
                for (int k = 0; k < 8; k++) {
                    int newI = i + dir[k][0], newJ = j + dir[k][1];
                    if (newI >=0 && newI < n && newJ >= 0 && newJ < m) {    // 合法位置
                        int ifAlive = board[newI][newJ];
                        if (ifAlive == 2 || ifAlive == 0) aroundDead++;
                        if (ifAlive == -2 || ifAlive == 1) aroundLive++;
                    }
                }
                if (currCeil == 1) {    // 是活细胞
                    if (aroundLive < 2 || aroundLive > 3) {
                        board[i][j] = -2;
                    }
                }else { // 是死细胞
                    if (aroundLive == 3) {
                        board[i][j] = 2;
                    }
                }
            }
        }
        // 更新整个矩阵的状态
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (board[i][j] == 2) {
                    board[i][j] = 1;
                }else if (board[i][j] == -2) {
                    board[i][j] = 0;
                }
            }
        }
    }
};