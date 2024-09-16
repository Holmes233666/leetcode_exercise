#include<vector>
#include<string>

using namespace std;

class Solution {
public:
    vector<vector<int>> directions = {{0,1},{0,-1},{1,0},{-1,0}};
    vector<vector<int>> visited;
    bool exist(vector<vector<char>>& board, string word) {
        if (word == "") return false;
        string currString;
        currString += word[0];
        bool res = false;
        // 初始化访问数组
        visited = vector<vector<int>>(board.size(), vector<int>(board[0].size(), 0));
        // 尝试遍历所有第一个字母满足的点
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0;j < board[i].size(); j++) {
                if (board[i][j] == word[0]) {
                    visited[i][j] = 1;
                    res = DFS(currString, word, board, i, j);
                    visited[i][j] = 0;
                    if (res) return res;
                }
            }
        }
        return res;
    }

    bool DFS(string& currString, string& word, vector<vector<char>>& board, int currI, int currJ) {
        if (currString == word) return true;
        if (currString.size() == word.size()) return false;
        bool res = false;
        for (int i = 0; i < directions.size(); i++) {
            int nextI = currI + directions[i][0], nextJ = currJ + directions[i][1];
            if (ifValid(nextI, nextJ, currString, word, board)) {
                visited[nextI][nextJ] = 1;
                currString.push_back(board[nextI][nextJ]);
                res = DFS(currString, word, board, nextI, nextJ);
                if (res) return res;
                // 回溯
                currString.pop_back();
                visited[nextI][nextJ] = 0;
            }
        }
        return res;
    }

    //检查位置是否符合条件
    bool ifValid(int i, int j, string& s, string& word, vector<vector<char>>& board) {
        if (i >= 0 && i < visited.size() && j >=0 && j < visited[0].size() && visited[i][j] == 0) {
            // 是下一个要访问的字符
            if (board[i][j] == word[s.size()]) {
                return true;
            }
        }
        return false;
    }
};