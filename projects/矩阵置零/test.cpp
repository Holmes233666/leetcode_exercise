#include<vector>
#include<iostream>
#include<unordered_map>

using namespace std;

class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        unordered_map<int, int> umap;
        for (int i = 0; i < matrix.size(); i++) {
            for (int j = 0; j < matrix[i].size(); j++) {
                if (matrix[i][j] == 0) {
                    umap[-i-1] = 1;
                    umap[j] = 1;
                }
            }
        }

        for (int i = 0; i < matrix.size(); i++) {
            for (int j = 0; j < matrix[i].size(); j++) {
                if (umap.count(-i-1) or umap.count(j)) {
                    matrix[i][j] = 0;
                }
            }
        }
    }
};

// 法2： 使用flag以及矩阵的第一行和第一列作为记录
class Solution2 {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int n = matrix.size(), m = matrix[0].size();
        int flag1 = 0, flag2 = 0;
        // 先扫描第一行和第一列，用两个flag记录是否需要置零
        for (int j = 0; j < m; j++) {
            if (matrix[0][j] == 0) {
                flag1 = 1;
                break;
            }
        }
        for (int i = 0; i < n; i++) {
            if (matrix[i][0] == 0) {
                flag2 = 1;
            }
        }
        // 使用矩阵的第一行和第一列作为标记
        for (int i = 1; i < n; i++) {
            for (int j = 1; j < m; j++) {
                if (matrix[i][j] == 0) {
                    matrix[0][j] = 0;
                    matrix[i][0] = 0;
                }
            }
        }
        // 扫描第一行和第一列，分别做置零操作
        for (int j = 1; j < m; j++) {
            if (matrix[0][j] == 0) {
                for (int i = 1; i < n; i++) {
                    matrix[i][j] = 0;
                }
            }
        }
        for (int i = 1; i < n; i++) {
            if (matrix[i][0] == 0) {
                for (int j = 0; j < m; j++) {
                    matrix[i][j] = 0;
                }
            }
        }
        if (flag1) {    // 第一行需要置零
            for (int j = 0; j < m; j++) {
                matrix[0][j] = 0;
            }
        }
        if (flag2) {
            for (int i = 0; i < n; i++) {
                matrix[i][0] = 0;
            }
        }
    }
};

int main() {
    vector<vector<int>> matrix = {{0,1,2,0},{3,4,5,2},{1,3,1,5}};
    Solution solution;
    solution.setZeroes(matrix);
    return 0;
}
