#include<vector>

using namespace std;

class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        vector<vector<char>> row(9, vector<char>(9, '0'));
        vector<vector<char>> line(9, vector<char>(9, '0'));
        vector<vector<vector<char>>> matrixs(9, vector<vector<char>>(3, vector<char>(9, '0')));

        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                char currChar = board[i][j];
                if (currChar == '.') continue;
                // 检查行
                if (row[i][currChar-'0'-1] != '1') {
                    row[i][currChar-'0'-1] = '1';
                }else {
                    return false;
                }
                // 检查列
                if (line[j][currChar-'0'-1] != '1') {
                    line[j][currChar-'0'-1] = '1';
                }else {
                    return false;
                }
                // 检查矩阵
                int matRowIdx = ceil(i/3), matLineIdx = ceil(j/3);
                if (matrixs[matRowIdx][matLineIdx][currChar-'0'-1] != '1') {
                    matrixs[matRowIdx][matLineIdx][currChar-'0'-1] = '1';
                }else {
                    return false;
                }
            }
        }
        return true;
    }
};
