#include<vector>

using namespace std;


class Solution {
public:
    void solve(vector<vector<char>>& board) {
        int n = board.size(), m = board[0].size();
        vector<vector<char>> visited(n, vector<char>(m, '0'));
        vector<vector<int>> dir = {{0,1}, {0,-1}, {1,0}, {-1,0}};
        // 对四条边上的X进行深搜，标记为'K'
        for (int start_i = 0; start_i < n; start_i++) {
            for (int start_j = 0; start_j < m; start_j++) {
                if (start_i != 0 && start_i != n-1 && start_j != 0 && start_j != m-1) continue;
                // 是四条边上的点
                if (visited[start_i][start_j] == '0' && board[start_i][start_j] == 'O') {
                    // 进行深搜，全部标记为‘K’
                    DFSmark(board, dir, visited, start_i, start_j, n, m);
                }
            }
        }
        // 将矩阵中所有的'O'标记为`X`
        for (int i = 0; i < n ; i++) {
            for (int j = 0; j < m; j++) {
                if (board[i][j] == 'O') {
                    board[i][j] = 'X';
                }
            }
        }
        // 将所有的'K'还原为'O'
        for (int i = 0; i < n ; i++) {
            for (int j = 0; j < m; j++) {
                if (board[i][j] == 'K') {
                    board[i][j] = 'O';
                }
            }
        }
    }

    void DFSmark(vector<vector<char>>& board, vector<vector<int>>& dir, vector<vector<char>>& visited,
        int start_i, int start_j, int n , int m) {
        visited[start_i][start_j] = '1';    // 已经访问
        board[start_i][start_j] = 'K';
        // cout << board[start_i][start_j] << endl;
        for (int i = 0; i < 4; i++) {
            int new_i = start_i + dir[i][0], new_j = start_j + dir[i][1];
            if (new_i >= 0 && new_i < n && new_j >= 0 && new_j < m
                && visited[new_i][new_j] == '0' && board[new_i][new_j] == 'O') {   // 位置有效
                DFSmark(board, dir, visited, new_i, new_j, n, m);
                }
        }
    }
};